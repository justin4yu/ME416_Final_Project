#!/usr/bin/env python3
import cv2
import apriltag
import numpy as np
import socket
from picamera2 import Picamera2

# =========================
# SETTINGS
# =========================

# Actual AprilTag side length in meters
# Example: 55 mm = 0.055
TAG_SIZE_METERS = 0.055

# Path to calibration files
CAMERA_MATRIX_FILE = "/home/oj/video2calibration/calibrationFiles/cameraMatrix.txt"
DIST_COEFFS_FILE   = "/home/oj/video2calibration/calibrationFiles/cameraDistortion.txt"

# Optional UDP output for Simulink later
SEND_UDP = False
UDP_IP = "127.0.0.1"
UDP_PORT = 5005

# =========================
# LOAD CALIBRATION
# =========================

camera_matrix = np.loadtxt(CAMERA_MATRIX_FILE, delimiter=',')
dist_coeffs = np.loadtxt(DIST_COEFFS_FILE, delimiter=',')
dist_coeffs = np.array(dist_coeffs, dtype=np.float64).reshape(-1, 1)

print("Loaded calibration.")
print("Camera matrix:\n", camera_matrix)
print("Dist coeffs:\n", dist_coeffs.ravel())

# =========================
# APRILTAG DETECTOR
# =========================

detector = apriltag.apriltag("tag36h11")

half = TAG_SIZE_METERS / 2.0
object_points = np.array([
    [-half, -half, 0.0],
    [ half, -half, 0.0],
    [ half,  half, 0.0],
    [-half,  half, 0.0]
], dtype=np.float32)

# =========================
# CAMERA
# =========================

picam2 = Picamera2()
config = picam2.create_video_configuration(main={"size": (640, 480), "format": "RGB888"})
picam2.configure(config)
picam2.start()

# =========================
# UDP SOCKET (optional)
# =========================

if SEND_UDP:
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

print("Tracker running. Press q to quit.")

while True:
    frame = picam2.capture_array()
    if frame is None:
        continue

    # Picamera2 gives RGB, OpenCV likes BGR for drawing
    frame_bgr = cv2.cvtColor(frame, cv2.COLOR_RGB2BGR)

    # Undistort using calibration
    frame_bgr = cv2.undistort(frame_bgr, camera_matrix, dist_coeffs)

    gray = cv2.cvtColor(frame_bgr, cv2.COLOR_BGR2GRAY)

    results = detector.detect(gray)

    img_h, img_w = gray.shape[:2]
    center_x_axis = img_w // 2

    if results:
        for tag in results:
            corners = np.array(tag["lb-rb-rt-lt"], dtype=np.float32)
            center = tag["center"]
            tag_id = tag["id"]

            success, rvec, tvec = cv2.solvePnP(
                object_points,
                corners,
                camera_matrix,
                dist_coeffs,
                flags=cv2.SOLVEPNP_ITERATIVE
            )

            tag_center_x = int(center[0])
            tag_center_y = int(center[1])
            pixel_offset = tag_center_x - center_x_axis

            corners_int = np.int32(corners)
            for i in range(4):
                pt1 = tuple(corners_int[i])
                pt2 = tuple(corners_int[(i + 1) % 4])
                cv2.line(frame_bgr, pt1, pt2, (255, 0, 0), 2)

            cv2.circle(frame_bgr, (tag_center_x, tag_center_y), 5, (0, 255, 0), -1)
            cv2.line(frame_bgr, (center_x_axis, 0), (center_x_axis, img_h), (0, 255, 255), 1)

            if success:
                x = float(tvec[0][0])
                y = float(tvec[1][0])
                z = float(tvec[2][0])
                dist_3d = float(np.linalg.norm(tvec))

                msg = f"FOUND=1 ID={tag_id} X={x:.3f} Y={y:.3f} Z={z:.3f} DIST={dist_3d:.3f} PIXOFF={pixel_offset}"
                print(msg)

                if SEND_UDP:
                    payload = f"1,{tag_id},{x:.3f},{y:.3f},{z:.3f},{pixel_offset}"
                    sock.sendto(payload.encode(), (UDP_IP, UDP_PORT))

                cv2.putText(frame_bgr, f"ID={tag_id}", (tag_center_x + 10, tag_center_y - 25),
                            cv2.FONT_HERSHEY_SIMPLEX, 0.55, (0, 255, 0), 2)
                cv2.putText(frame_bgr, f"Z={z:.2f}m X={x:.2f}m", (tag_center_x + 10, tag_center_y - 5),
                            cv2.FONT_HERSHEY_SIMPLEX, 0.55, (0, 255, 0), 2)
                cv2.putText(frame_bgr, f"PixOff={pixel_offset}", (tag_center_x + 10, tag_center_y + 15),
                            cv2.FONT_HERSHEY_SIMPLEX, 0.55, (0, 255, 0), 2)
            else:
                print(f"FOUND=1 ID={tag_id} POSE_FAIL")
    else:
        print("FOUND=0")
        if SEND_UDP:
            sock.sendto(b"0,-1,0,0,0,0", (UDP_IP, UDP_PORT))

    cv2.imshow("AprilTag Tracker", frame_bgr)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cv2.destroyAllWindows()
picam2.stop()
