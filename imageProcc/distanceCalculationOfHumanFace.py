import cv2
import time
from config import *
# import serialCommunication

# Colors define
GREEN = (0, 255, 0)
RED = (0, 0, 255)
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)

Distance = 9

# Set the resolution based on the UniHiker board
SCREEN_WIDTH = 640  # replace with your actual width
SCREEN_HEIGHT = 480  # replace with your actual height

# Defining the fonts
fonts = cv2.FONT_HERSHEY_COMPLEX

# Face detector object
face_detector = cv2.CascadeClassifier("haarcascade_frontalface_default.xml")

# Focal length finder function
def Focal_Length_Finder(measured_distance, real_width, width_in_rf_image):
    focal_length = (width_in_rf_image * measured_distance) / real_width
    return focal_length

# Distance estimation function
def Distance_finder(Focal_Length, real_face_width, face_width_in_frame):
    distance = (real_face_width * Focal_Length) / face_width_in_frame
    return distance

def face_data(image):
    face_width = 0  # Initialize face width to zero

    # Convert color image to gray scale
    gray_image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    
    # Detect faces in the image
    faces = face_detector.detectMultiScale(gray_image, 1.3, 5)

    for (x, y, h, w) in faces:
        # Draw rectangle on the face
        cv2.rectangle(image, (x, y), (x + w, y + h), GREEN, 2)
        face_width = w  # Get face width in pixels
        
    return face_width

# Reading reference image from directory
ref_image = cv2.imread("Ref_image.png")
print(ref_image)

# Find the face width (pixels) in the reference image
ref_image_face_width = face_data(ref_image)
print("ref_image_face_width: ", ref_image_face_width)
time.sleep(3)

# Get the focal length
Focal_length_found = Focal_Length_Finder(Known_distance, Known_width, ref_image_face_width)
print("Focal_length_found: ", Focal_length_found)

# Show the reference image
if not RASPBERRY:
    cv2.imshow("Reference Image", ref_image)

# Initialize the camera object
cap = cv2.VideoCapture(0)  # Use "0" for webcam or adjust as needed

def findDistance():
    global Distance, human_detect_flag
    _, frame = cap.read()

    # Resize the frame to fit the screen
    frame = cv2.resize(frame, (SCREEN_WIDTH, SCREEN_HEIGHT))

    face_width_in_frame = face_data(frame)
    print("face_width: ", face_width_in_frame)

    if face_width_in_frame != 0:
        Distance = Distance_finder(Focal_length_found, Known_width, face_width_in_frame)

        # Resize text position and size based on screen size
        text_position = (int(SCREEN_WIDTH * 0.05), int(SCREEN_HEIGHT * 0.05))
        cv2.line(frame, (30, 30), (230, 30), RED, 32)
        cv2.line(frame, (30, 30), (230, 30), BLACK, 28)

        # Drawing Text on the screen
        cv2.putText(
            frame, f"Distance: {round(Distance, 2)} CM", text_position,
            fonts, 0.6 * (SCREEN_WIDTH / 640), GREEN, 2  # Scale text size
        )

        print("Human face Distance: ", Distance)
        if Distance < human_detect_threshold:
            human_detect_flag = True
#             serialCommunication.sendCmd("HD\n")
        else:
            human_detect_flag = False
#             serialCommunication.sendCmd("NHD\n")

    if not RASPBERRY:
        # Create a window with a specific size
        cv2.namedWindow("Frame", cv2.WND_PROP_FULLSCREEN)
        cv2.setWindowProperty("Frame", cv2.WND_PROP_FULLSCREEN, cv2.WINDOW_FULLSCREEN)
        cv2.imshow("Frame", frame)

if __name__ == "__main__":
    while True:
        findDistance()
        # Quit the program if you press 'q' on the keyboard
        if cv2.waitKey(1) == ord("q"):
            break

    # Closing the camera
    cap.release()
    # Closing the windows that are opened
    cv2.destroyAllWindows()
