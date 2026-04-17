#!/usr/bin/env python3
import cv2
import apriltag
import numpy as np
import os
import sys

# =========================
# USER SETTINGS
# =========================

# Physical side length of the AprilTag in METERS.
TAG_SIZE_METERS = 0.055

VIDEO_SOURCE = "tcp://127.0.0.1:8888"

# =========================
# CALIBRATION FILES
# =========================

BASE_DIR = os.path.dirname(os.path.abspath(__file__))
CALIB_DIR = os.path.join(BASE_DIR, "calibrationFiles")

CAMERA_MATRIX_FILE = os.path.join(CALIB_DIR, "cameraMatrix.txt")
DIST_COEFFS_FILE = os.path.join(CALIB_DIR, "cameraDistortion.txt")

if not os.path.exists(CAMERA_MATRIX_FILE):
    print(f"Missing file: {CAMERA_MATRIX_FILE}")
    sys.exit(1)

if not os.path.exists(DIST_COEFFS_FILE):
    print(f"Missing file: {DIST_COEFFS_FILE}")
    sys.exit(1)

camera_matrix = np.loadtxt(CAMERA_MATRIX_FILE, delimiter=',')
dist_coeffs = np.loadtxt(DIST_COEFFS_FILE, delimiter=',')

dist_coeffs = np.array(dist_coeffs, dtype=np.float64).reshape(-1, 1)

print("Loaded camera calibration.")
print("Camera matrix:\n", camera_matrix)
print("Distortion coefficients:\n", dist_coeffs.ravel())

# =========================
# APRILTAG DETECTOR
# =========================

detector = apriltag.Detector()

# 3D model points of the tag corners in the tag frame
# Order matters and should match the detector corner order.
half = TAG_SIZE_METERS / 2.0
object_points = np.array([
    [-half, -half, 0.0],
    [ half, -half, 0.0],
    [ half,  half, 0.0],
    [-half,  half, 0.0]
], dtype=np.float32)

# =========================
# OPEN VIDEO SOURCE
# =========================

cap = cv2.VideoCapture(VIDEO_SOURCE)

if not cap.isOpened():
    print(f"Could not open video source: {VIDEO_SOURCE}")
    sys.exit(1)

print("Video source opened.")
print("Press 'q' to quit.")

# =========================
# MAIN LOOP
# =========================

while True:
    ret, frame = cap.read()
    if not ret or frame is None:
        continue

    # Undistort frame using calibration results
    frame_undist = cv2.undistort(frame, camera_matrix, dist_coeffs)

    # Grayscale for AprilTag detector
    gray = cv2.cvtColor(frame_undist, cv2.COLOR_BGR2GRAY)

    # Detect tags
    results = detector.detect(gray)

    # Horizontal center of image
    img_h, img_w = gray.shape[:2]
    center_x_axis = img_w // 2

    for tag in results:
        # Corners from detector
        image_points = np.array(tag.corners, dtype=np.float32)

        # Pose estimation
        success, rvec, tvec = cv2.solvePnP(
            object_points,
            image_points,
            camera_matrix,
            dist_coeffs,
            flags=cv2.SOLVEPNP_ITERATIVE
        )

        # Draw tag outline
        corners_int = np.int32(tag.corners)
        for i in range(4):
            pt1 = tuple(corners_int[i])
            pt2 = tuple(corners_int[(i + 1) % 4])
            cv2.line(frame_undist, pt1, pt2, (255, 0, 0), 2)

        # Draw center
        tag_center_x = int(tag.center[0])
        tag_center_y = int(tag.center[1])
        cv2.circle(frame_undist, (tag_center_x, tag_center_y), 5, (0, 255, 0), -1)

        # Pixel offset from image center
        pixel_offset = tag_center_x - center_x_axis

        # Draw image center reference line
        cv2.line(frame_undist, (center_x_axis, 0), (center_x_axis, img_h), (0, 255, 255), 1)

        if success:
            x = float(tvec[0][0])   # left/right offset in meters
            y = float(tvec[1][0])   # up/down offset in meters
            z = float(tvec[2][0])   # forward distance in meters
            dist_3d = float(np.linalg.norm(tvec))

            # Draw pose text
            text1 = f"Tag ID: {tag.tag_id}"
            text2 = f"X={x:.3f}m  Y={y:.3f}m  Z={z:.3f}m"
            text3 = f"3D Dist={dist_3d:.3f}m  Pixel Offset={pixel_offset}"

            cv2.putText(frame_undist, text1, (tag_center_x + 10, tag_center_y - 30),
                        cv2.FONT_HERSHEY_SIMPLEX, 0.55, (0, 255, 0), 2)
            cv2.putText(frame_undist, text2, (tag_center_x + 10, tag_center_y - 10),
                        cv2.FONT_HERSHEY_SIMPLEX, 0.55, (0, 255, 0), 2)
            cv2.putText(frame_undist, text3, (tag_center_x + 10, tag_center_y + 10),
                        cv2.FONT_HERSHEY_SIMPLEX, 0.55, (0, 255, 0), 2)

            print(
                f"Tag {tag.tag_id} | "
                f"X={x:.3f} m | Y={y:.3f} m | Z={z:.3f} m | "
                f"3D={dist_3d:.3f} m | PixelOffset={pixel_offset}"
            )
        else:
            cv2.putText(frame_undist, f"Tag ID: {tag.tag_id} | pose failed",
                        (tag_center_x + 10, tag_center_y),
                        cv2.FONT_HERSHEY_SIMPLEX, 0.55, (0, 0, 255), 2)

    cv2.imshow("AprilTag Pose Test", frame_undist)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
