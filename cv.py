import cv2
from picamera2 import Picamera2
import serial
import time
ser=serial.Serial('/dev/ttyACM0',9600,timeout=2)
ser2=serial.Serial('/dev/ttyACM1',9600,timeout=2)
ser.flush()
ser2.flush()

# Load the cascade
face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')
#eye_cascade = cv2.CascadeClassifier(cv2.data.haarcascades +'haarcascades\haarcascade_eye_tree_eyeglasses.xml')
eye_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_eye.xml')
# To capture video from webcam.
picam = Picamera2()
picam.start()
# To use a video file as input
# cap = cv2.VideoCapture('filename.mp4')
detections = 0
foundPerson = False
numframes = 0
sentK = False
sentW = False
while True:
    # Read the frame
    img=picam.capture_array()
    #_, img = cap.read()
    # Convert to grayscale
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    # Detect the faces
    faces = face_cascade.detectMultiScale(gray, 1.1, 4)
    # Draw the rectangle around each face
    for (x, y, w, h) in faces:
        cv2.rectangle(img, (x, y), (x+w, y+h), (255, 0, 0), 2)
   
        roi_gray = gray[y:y+h, x:x+w]
        roi_color = img[y:y+h, x:x+w]
       
           # detects eyes of within the detected face area (roi)
        eyes = eye_cascade.detectMultiScale(roi_gray)

           # draw a rectangle around eyes
        for (ex,ey,ew,eh) in eyes:
            cv2.rectangle(roi_color,(ex,ey),(ex+ew,ey+eh),(0,255,255),2)
    # Display
    cv2.imshow('img', img)
    
    if foundPerson == True:
        time.sleep(1)
        numframes += 1
        if (len(faces)>0):
            detections += 1
        if sentW == False:
            ser.write(b'w\n')
            sentW = True
            print("sent w")
        if (numframes >= 10 and detections / numframes > 0.7):
            foundPerson = True
        elif numframes >= 10 and detections / numframes <= 0.7: 
            ser.write(b's\n')
            print("sent s")
            while True:
                ser.write(b's\n')
                time.sleep(3)
                ser2.write(b'a\n')
            break
        
    print(foundPerson)
    print(len(faces))
    if (len(faces) > 0) and foundPerson == False:
        print(foundPerson)
        foundPerson = True
        ser.write(b'w\n')
        print("sent w")
        time.sleep(1)
    elif foundPerson == False and sentK == False:
        sentK = True
        ser.write(b'k\n')
        print("sent k")
        detections = 0
            
    # Stop if escape key is pressed
    k = cv2.waitKey(30) & 0xff
    if k==27:
        break
        

