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

mp_drawing = mp.solutions.drawing_utils
mp_hands = mp.solutions.hands

#Bernhard Ip: 100.83.65.154
if __name__ == "__main__":
  parser = argparse.ArgumentParser()
  parser.add_argument("--ip", default="127.0.0.1",
      help="The ip of the OSC server")
  parser.add_argument("--port", type=int, default=5005,
      help="The port the OSC server is listening on")
  args = parser.parse_args()

  client = udp_client.SimpleUDPClient(args.ip, args.port)
  clientB = udp_client.SimpleUDPClient("100.83.65.154", args.port)

  #hier war for-Schleife

  # For webcam input:
  cap = cv2.VideoCapture(0)
  with mp_hands.Hands(
          min_detection_confidence=0.5,
          min_tracking_confidence=0.5) as hands:
      while cap.isOpened():
          success, image = cap.read()
          if not success:
              print("Ignoring empty camera frame.")
              # If loading a video, use 'break' instead of 'continue'.
              continue

          # Flip the image horizontally for a later selfie-view display, and convert
          # the BGR image to RGB.
          image = cv2.cvtColor(cv2.flip(image, 1), cv2.COLOR_BGR2RGB)
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
                      # Nr.4 ist Daumen und Nr. 8 ist Zeigefinger, theoretisch Mittelfinger ist Nr.12
                      cx, cy = landmrk.x * image_width, landmrk.y * image_height
                      if ids == 4:
                          print('Daumen:', cx, cy)
                          client.send_message("/daumen", [ids, cx, cy])
                          clientB.send_message("/daumen", [ids, cx, cy])

                      if ids == 8:
                          print('Zeigefinger:', cx, cy)
                          client.send_message("/zeigefinger", [ids, cx, cy])
                          clientB.send_message("/zeigefinger", [ids, cx, cy])

                      # print (ids, cx, cy)
                      mp_drawing.draw_landmarks(image, hand_landmarks, mp_hands.HAND_CONNECTIONS)
          cv2.imshow('MediaPipe Hands', image)
          if cv2.waitKey(5) & 0xFF == 27:
              break
  cap.release()