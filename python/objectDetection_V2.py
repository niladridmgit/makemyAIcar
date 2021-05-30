#export LD_PRELOAD=/usr/lib/aarch64-linux-gnu/libgomp.so.1
import jetson.inference
import jetson.utils
import cv2
import numpy as np
from csi_camera import CSI_Camera
from dcMotorControl import dcMotorControl
from adafruit_servokit import ServoKit
from datetime import datetime

#net = jetson.inference.detectNet("facenet-120", threshold=0.5)
net = jetson.inference.detectNet("ssd-mobilenet-v2", threshold=0.5)
display = jetson.utils.videoOutput("rtp://192.168.1.120:1234")

dc_motor = dcMotorControl()


DISPLAY_WIDTH=640
DISPLAY_HEIGHT=480
SENSOR_MODE_1080=2
SENSOR_MODE_720=3

pid = [0.4,0.4,0]
pError = 0

def millis(start_time):
   dt = datetime.now() - start_time
   ms = (dt.days * 24 * 60 * 60 + dt.seconds) * 1000 + dt.microseconds / 1000.0
   return ms

def show_camera():
    left_camera = CSI_Camera()
    left_camera.create_gstreamer_pipeline(
            sensor_id=0,
            sensor_mode=SENSOR_MODE_720,
            framerate=30,
            flip_method=2,
            display_height=DISPLAY_HEIGHT,
            display_width=DISPLAY_WIDTH,
    )
    left_camera.open(left_camera.gstreamer_pipeline)
    left_camera.start()
    cv2.namedWindow("img show", cv2.WINDOW_AUTOSIZE)
    if (
        not left_camera.video_capture.isOpened()
     ):
        # Cameras did not open, or no camera attached

        print("Unable to open any cameras")
        # TODO: Proper Cleanup
        SystemExit(0)
    try:
        # Start counting the number of frames read and displayed
        left_camera.start_counting_fps()
        start_time = datetime.now()
        cam_servo = ServoKit(channels=16)
        pan_angle = 90
        pitch_angle=90
        cam_servo.servo[0].angle=pan_angle
        cam_servo.servo[1].angle=pitch_angle
        step = 1
        while cv2.getWindowProperty("img show", 0) >= 0 :
            _ ,img=left_camera.read()
            imgCuda=jetson.utils.cudaFromNumpy(img)
            detections = net.Detect(imgCuda)
            for d in detections:
                #print(net.GetClassDesc(d.ClassID))
                #print(d.ClassID)
                if d.ClassID==1: #47:
                    x1,y1,x2,y2 = int(d.Left),int(d.Top),int(d.Right),int(d.Bottom)
                    #className = net.GetClassDesc(d.ClassID)
                    #print(d.ClassID)
                    cv2.rectangle(img,(x1,y1),(x2,y2),(255,255,255),2)
                    #cv2.putText(img,str(className)+", fps:"+format(net.GetNetworkFPS(), '.2f'),(x1+5,y1+20),cv2.FONT_HERSHEY_DUPLEX,0.75,(255,0,255),2)
                    #cv2.putText(img,format(net.GetNetworkFPS(), '.2f'),(x1+5,y1+45),cv2.FONT_HERSHEY_DUPLEX,0.75,(255,0,255),2)
                    #print("Object Detection | Network {:.0f} FPS".format(net.GetNetworkFPS()))
                    w= x2-x1
                    h= y2-y1
                    area = w*h
                    cv2.putText(img,str(area),(x1+5,y1+15),cv2.FONT_HERSHEY_DUPLEX,0.75,(255,0,255),2)
                    x_c = x1 + w/2
                    y_c = y1+ h/2
                    cv2.line(img,(int(x_c),y1),(int(x_c),y2),(255,255,0),2)
                    cv2.line(img,(x1,int(y_c)),(x2,int(y_c)),(255,255,0),2)
                    cv2.circle(img,(int(x_c),int(y_c)),3,(255.255,255),2)
                    cv2.line(img,(int(x_c),int(y_c)),(int(DISPLAY_WIDTH/2),int(y_c)),(0,0,255),2)
                    cv2.line(img,(int(x_c),int(y_c)),(int(x_c),int(DISPLAY_HEIGHT/2)),(255,0,0),2)

                if millis(start_time)>50:
                    process = 0
                    for person in detections:
                        if person.ClassID==1:
                            process=1

                    if process==1:
                        #print(millis(start_time))
                        pan = (DISPLAY_WIDTH/2) - x_c
                        pitch = (DISPLAY_HEIGHT/2) - y_c
                        print("pan {} pitch {}".format(pan,pitch))
                        if pan>50:
                            if (pan_angle - step) < 170:
                                if pan>50:
                                    pan_angle += step
                                    pan_angle += step
                                    pan_angle += step
                                    pan_angle += step
                                    pan_angle += step
                                pan_angle += step
                                # Camera PAN Right#
                                #cam_servo.servo[0].angle = pan_angle
                            # DC Motor Right #
                            dc_motor.sendCmd(2)
                            print('Left')
                        elif pan<-50:
                            if (pan_angle - step) > 10:
                                if pan<-50:
                                    pan_angle -= step
                                    pan_angle -= step
                                    pan_angle -= step
                                    pan_angle -= step
                                    pan_angle -= step
                                pan_angle -= step
                                # Camera PAN Left#
                                #cam_servo.servo[0].angle=pan_angle
                            # DC Motor Left #
                            dc_motor.sendCmd(3)
                            print('Right')
                        elif area < 200000 :
                            dc_motor.sendCmd(0)
                            print('Go')
                        elif area > 240000 :
                            dc_motor.sendCmd(4)
                            print('Back')
                        else:
                            dc_motor.sendCmd(1)
                            print('Stop') 

                        
                        if pitch<-15:
                            if (pitch_angle - step) > 60:
                                if pitch_angle<-50:
                                    pitch_angle-=step
                                    pitch_angle-=step
                                    pitch_angle-=step
                                    pitch_angle-=step
                                    pitch_angle-=step
                                pitch_angle-=step
                            cam_servo.servo[1].angle=pitch_angle
                        elif pitch>15:
                            if (pitch_angle - step) < 160:
                                if pitch_angle>50:
                                    pitch_angle+=step
                                    pitch_angle+=step
                                    pitch_angle+=step
                                    pitch_angle-=step
                                    pitch_angle-=step
                                pitch_angle+=step
                            cam_servo.servo[1].angle=pitch_angle

                        start_time = datetime.now()
                    else:
                        dc_motor.sendCmd(1)
                        print('Stop') 
                   

            cv2.line(img,(int(DISPLAY_WIDTH/2),0),(int(DISPLAY_WIDTH/2),DISPLAY_HEIGHT),(0,0,255),2)
            cv2.line(img,(0,int(DISPLAY_HEIGHT/2)),(DISPLAY_WIDTH,int(DISPLAY_HEIGHT/2)),(255,0,0),2)
            cv2.circle(img,(int(DISPLAY_WIDTH/2),int(DISPLAY_HEIGHT/2)),3,(255.255,255),2)
            display.Render(imgCuda)
            cv2.imshow("img show", img)
            keyCode = cv2.waitKey(1) & 0xFF
            # Stop the program on the ESC key
            if keyCode == 27:
                break
    finally:
        left_camera.stop()
        left_camera.release()
        cv2.destroyAllWindows()


if __name__ == "__main__":
    show_camera()