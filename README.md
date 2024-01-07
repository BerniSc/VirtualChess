# VirtualChess
BernSoftAGs First Software Programm Application, Ähhhmm, Game. Ich bin grad dumm.

Current Version of Processing and Output can be found on branch be/integration (Input on "localtest Version", meaning Image is not meant to be displayed on Beamer, but can be controlled by using Finger-Motion in the local Webcam)

Programm can be started by calling ```make; make run``` in the Folder GuiChess and call the Python-Script client.py like ```python3 client.py``` in the folder MediapipeInput.<br>
In case it does not detect the fingers as expected, change the comparison-factors in the Function "bool ofApp::checkDistance()" in GuiChess/src/ofApp.cpp.

Requirements:
  - OpenFrameworks installation
  - Python3
  - MediaPipe
