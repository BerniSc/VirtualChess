"""Small example OSC client

This program sends 10 random values between 0.0 and 1.0 to the /filter address,
waiting for 1 seconds between each value.
"""
import argparse
import random
import time

from pythonosc import udp_client
import cv2
import mediapipe as mp

import numpy as np

mp_drawing = mp.solutions.drawing_utils
mp_hands = mp.solutions.hands


# Fkt. / Vars für Kalibrierung
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




if __name__ == "__main__":
  parser = argparse.ArgumentParser()
  parser.add_argument("--ip", default="127.0.0.1",
      help="The ip of the OSC server")
  parser.add_argument("--port", type=int, default=5005,
      help="The port the OSC server is listening on")
  args = parser.parse_args()

  client = udp_client.SimpleUDPClient(args.ip, args.port)
  clientB = udp_client.SimpleUDPClient("100.83.140.1", args.port)


  # Kalibrierung
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
  #cap.release()
  cv2.destroyAllWindows()






  # For webcam input:
  #cap = cv2.VideoCapture(2)
  #cap.set(cv2.CAP_PROP_FRAME_WIDTH, 1600)
  #cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 1200)
  
  with mp_hands.Hands(
      min_detection_confidence=0.5,
      min_tracking_confidence=0.5) as hands:
  
      # Define the target points for the perspective transform
      target_points = np.array([(0, 0), (616, 0), (616, 616), (0, 616)], dtype=np.float32)  
      # Get the perspective transform matrix
      matrix = cv2.getPerspectiveTransform(np.float32(points), target_points)
      
      while cap.isOpened():
          success, image = cap.read()
 
          # Apply the perspective transform
          result = cv2.warpPerspective(image, matrix, (616, 616))

          if not success:
              print("Ignoring empty camera frame.")
              # If loading a video, use 'break' instead of 'continue'.
              continue

          # Flip the image horizontally for a later selfie-view display, and convert
          # the BGR image to RGB.

          # Mit Spiegelung
          #image = cv2.cvtColor(cv2.flip(result, 1), cv2.COLOR_BGR2RGB)

          # Ohne Spiegelung
          image = cv2.cvtColor(result, cv2.COLOR_BGR2RGB)

          # To improve performance, optionally mark the image as not writeable to
          # pass by reference.
          image.flags.writeable = False
          results = hands.process(image)
          image_height, image_width, _ = image.shape  # Draw the hand annotations on the image.
          image.flags.writeable = True
          image = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)
          if results.multi_hand_landmarks:
              for hand_landmarks in results.multi_hand_landmarks:
                  # Here is How to Get All the Coordinates
                  for ids, landmrk in enumerate(hand_landmarks.landmark):
                      # print(ids, landmrk)
                      # Nr.4 ist Daumen und Nr. 8 ist Zeigefinger
                      cx, cy = landmrk.x * image_width, landmrk.y * image_height
                      if ids == 4:
                          print('Daumen:', cx, cy)
                          client.send_message("/daumen", [ids, cx, cy])
                          clientB.send_message("/daumen", [ids, cx, cy])

                      if ids == 8:
                          print('Zeigefinger:', cx, cy)
                          client.send_message("/zeigefinger", [ids, cx, cy])
                          clientB.send_message("/zeigefinger", [ids, cx, cy])

                      mp_drawing.draw_landmarks(image, hand_landmarks, mp_hands.HAND_CONNECTIONS)
          cv2.imshow('MediaPipe Hands', image)
          if cv2.waitKey(5) & 0xFF == 27:
              break
  cap.release()