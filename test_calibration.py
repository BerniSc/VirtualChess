import cv2
import numpy as np

# Global variables
points = []
clicked = False

# The Order in which the points have to be clicked is TL TR BR BL

# Callback function for mouse events
def mouse_callback(event, x, y, flags, param):
    global clicked, points

    if event == cv2.EVENT_LBUTTONDOWN:
        points.append((x, y))
        clicked = True
        if len(points) == 4:
            clicked = False

# Capture video from the default camera
cap = cv2.VideoCapture(0)

# Create a window and set the mouse callback function
cv2.namedWindow("Perspective Transform")
cv2.setMouseCallback("Perspective Transform", mouse_callback)

# Terminate with Ctrl-C after calling like python3 pythontest.yp or by pressing ESC
while True:
    ret, frame = cap.read()

    if not ret:
        break

    if clicked and len(points) < 4:
        cv2.circle(frame, points[-1], 5, (0, 255, 0), -1)

    if len(points) == 4:
        # Define the target points for the perspective transform
        target_points = np.array([(0, 0), (616, 0), (616, 616), (0, 616)], dtype=np.float32)

        # Get the perspective transform matrix
        matrix = cv2.getPerspectiveTransform(np.float32(points), target_points)

        # Apply the perspective transform
        result = cv2.warpPerspective(frame, matrix, (616, 616))

        # Display the original and transformed frames side by side
        cv2.imshow("Original Frame", frame)
        cv2.imshow("Perspective Transform", result)

    else:
        cv2.imshow("Perspective Transform", frame)

    key = cv2.waitKey(1) & 0xFF
    if key == 27:  # Press 'Esc' to exit
        break

# Release the camera and close all windows
cap.release()
cv2.destroyAllWindows()

