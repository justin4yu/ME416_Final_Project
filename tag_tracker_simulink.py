#!/usr/bin/env python3
import cv2
import apriltag
import numpy as np
import socket
from picamera2 import Picamera2

# =========================
# USER SETTINGS
# =========================

# Actual physical AprilTag side length in meters.
# Example:
# 33 mm -> 0.033
# 55 mm -> 0.055
TAG_SIZE_METERS = 0.055

# Calibration files from your camera calibration
CAMERA_MATRIX_FILE = "/home/oj/video2calibration/calibrationFiles/cameraMatrix.txt"
DIST_COEFFS_FILE   = "/home/oj/video2calibration/calibrationFiles/cameraDistortion.txt"

# UDP destination
# If Simulink is on the same Pi, leave 127.0.0.1
# If Simulink is on your laptop, replace with your laptop IP
UDP_IP = "127.0.0.1"
UDP_PORT = 5005

# AprilTag family
TAG_FAMILY = "tag36h11"

# Camera resolution
FRAME_WIDTH = 640
FRAME_HEIGHT = 480

# Show debug window
SHOW_WINDOW = True

# =========================
# LOAD CALIBRATION
# =========================

camera_matrix = np.loadtxt(CAMERA_MATRIX_FILE, delimiter=',')
dist_coeffs = np.loadtxt(DIST_COEFFS_FILE, delimiter=',')
dist_coeffs = np.array(dist_coeffs, dtype=np.float64).reshape(-1, 1)

print("Loaded camera calibration.")
print("Camera matrix:\n", camera_matrix)
print("Distortion coefficients:\n", dist_coeffs.ravel())

# =========================
# APRILTAG DETECTOR
# =========================

# This matches the Python binding you compiled earlier
detector = apriltag.apriltag(TAG_FAMILY)

half = TAG_SIZE_METERS / 2.0
object_points = np.array([
    [-half, -half, 0.0],
    [ half, -half, 0.0],
    [ half,  half, 0.0],
    [-half,  half, 0.0]
], dtype=np.float32)

# =========================
# UDP SOCKET
# =========================

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# =========================
# CAMERA
# =========================

picam2 = Picamera2()
config = picam2.create_video_configuration(
    main={"size": (FRAME_WIDTH, FRAME_HEIGHT), "format": "RGB888"}
)
picam2.configure(config)
picam2.start()

print(f"AprilTag UDP tracker running. Sending UDP to {UDP_IP}:{UDP_PORT}")
print("Packet format: found,tag_id,x_m,y_m,z_m,pixel_offset")
print("Press q in the image window to quit.")

# =========================
# MAIN LOOP
# =========================

while True:
    frame_rgb = picam2.capture_array()
    if frame_rgb is None:
        continue

    # Convert Picamera2 RGB -> OpenCV BGR
    frame_bgr = cv2.cvtColor(frame_rgb, cv2.COLOR_RGB2BGR)

    # Undistort
    frame_bgr = cv2.undistort(frame_bgr, camera_matrix, dist_coeffs)

    gray = cv2.cvtColor(frame_bgr, cv2.COLOR_BGR2GRAY)

    # Detect tags
    results = detector.detect(gray)

    img_h, img_w = gray.shape[:2]
    center_x_axis = img_w // 2

    found_any = 0
    best_payload = "0,-1,0,0,0,0"

    if results:
        for tag in results:
            found_any = 1

            # For this apriltag binding, corners and fields are dict-style
            corners = np.array(tag["lb-rb-rt-lt"], dtype=np.float32)
            center = tag["center"]
            tag_id = int(tag["id"])

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

            # Draw outline
            corners_int = np.int32(corners)
            for i in range(4):
                pt1 = tuple(corners_int[i])
                pt2 = tuple(corners_int[(i + 1) % 4])
                cv2.line(frame_bgr, pt1, pt2, (255, 0, 0), 2)

            # Draw center and camera center line
            cv2.circle(frame_bgr, (tag_center_x, tag_center_y), 5, (0, 255, 0), -1)
            cv2.line(frame_bgr, (center_x_axis, 0), (center_x_axis, img_h), (0, 255, 255), 1)

            if success:
                x = float(tvec[0][0])   # left/right offset [m]
                y = float(tvec[1][0])   # up/down offset [m]
                z = float(tvec[2][0])   # forward distance [m]

                best_payload = f"1,{tag_id},{x:.4f},{y:.4f},{z:.4f},{pixel_offset}"
                sock.sendto(best_payload.encode(), (UDP_IP, UDP_PORT))

                print(best_payload)

                if SHOW_WINDOW:
                    cv2.putText(frame_bgr, f"ID={tag_id}", (tag_center_x + 10, tag_center_y - 25),
                                cv2.FONT_HERSHEY_SIMPLEX, 0.55, (0, 255, 0), 2)
                    cv2.putText(frame_bgr, f"X={x:.2f}m Y={y:.2f}m Z={z:.2f}m",
                                (tag_center_x + 10, tag_center_y - 5),
                                cv2.FONT_HERSHEY_SIMPLEX, 0.55, (0, 255, 0), 2)
                    cv2.putText(frame_bgr, f"PixOff={pixel_offset}",
                                (tag_center_x + 10, tag_center_y + 15),
                                cv2.FONT_HERSHEY_SIMPLEX, 0.55, (0, 255, 0), 2)
            else:
                best_payload = f"1,{tag_id},0,0,0,{pixel_offset}"
                sock.sendto(best_payload.encode(), (UDP_IP, UDP_PORT))
                print(best_payload)

    else:
        sock.sendto(best_payload.encode(), (UDP_IP, UDP_PORT))
        print(best_payload)

    if SHOW_WINDOW:
        cv2.imshow("AprilTag UDP Tracker", frame_bgr)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

if SHOW_WINDOW:
    cv2.destroyAllWindows()

picam2.stop()
