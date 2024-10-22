import cv2
import mediapipe as mp
import math

# Initialize MediaPipe Face Mesh
mp_face_mesh = mp.solutions.face_mesh
mp_drawing = mp.solutions.drawing_utils

# Function to calculate the mouth openness
def is_mouth_open(landmarks):
    top_lip = landmarks[13]
    bottom_lip = landmarks[14]
    distance = math.sqrt((bottom_lip.x - top_lip.x) ** 2 + (bottom_lip.y - top_lip.y) ** 2)
    threshold = 0.02  # Adjust this threshold based on your needs
    return distance > threshold

# Start video capture from IP camera
cap = cv2.VideoCapture(0)  # Adjust if necessary

# Desired width and height for UniHiker board
desired_width = 640
desired_height = 480

with mp_face_mesh.FaceMesh(max_num_faces=1) as face_mesh:
    while cap.isOpened():
        success, image = cap.read()
        if not success:
            print("Ignoring empty camera frame.")
            continue
        
        # Resize the image to match the UniHiker dimensions
        image = cv2.resize(image, (desired_width, desired_height))

        # Flip the image horizontally and convert the BGR image to RGB
        image = cv2.cvtColor(cv2.flip(image, 1), cv2.COLOR_BGR2RGB)
        results = face_mesh.process(image)

        # Draw face mesh
        image = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)
        if results.multi_face_landmarks:
            for face_landmarks in results.multi_face_landmarks:
                mp_drawing.draw_landmarks(
                    image, face_landmarks, mp_face_mesh.FACEMESH_TESSELATION,
                    mp_drawing.DrawingSpec(color=(255, 0, 0), thickness=1, circle_radius=1),
                    mp_drawing.DrawingSpec(color=(0, 255, 0), thickness=1, circle_radius=1)
                )
                
                # Check if the mouth is open
                if is_mouth_open(face_landmarks.landmark):
                    cv2.putText(image, "Mouth is OPEN", (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 2)
                    print("MO")
                else:
                    cv2.putText(image, "Mouth is CLOSED", (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)
                    print("MC")

        # Display the image in fullscreen
        cv2.namedWindow('Mouth Openness Detection', cv2.WND_PROP_FULLSCREEN)
        cv2.setWindowProperty('Mouth Openness Detection', cv2.WND_PROP_FULLSCREEN, cv2.WINDOW_FULLSCREEN)
        cv2.imshow('Mouth Openness Detection', image)

        if cv2.waitKey(5) & 0xFF == 27:  # Press 'ESC' to exit
            break

cap.release()
cv2.destroyAllWindows()
