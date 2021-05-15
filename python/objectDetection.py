import jetson.inference
import jetson.utils
import numpy as np
import serial
from datetime import datetime
from datetime import timedelta


net = jetson.inference.detectNet("ssd-mobilenet-v2", threshold=0.5)
camera = jetson.utils.videoSource("csi://0",["--input-width=640", "--input-height=320"])      # '/dev/video0' for V4L2 , CSI-> csi://0
display = jetson.utils.videoOutput("rtp://192.168.1.120:1234") # 'my_video.mp4' for file


start_time = datetime.now()

pid = [0.4, 0.4, 0]
pError = 0
index=0

def millis():
   dt = datetime.now() - start_time
   ms = (dt.days * 24 * 60 * 60 + dt.seconds) * 1000 + dt.microseconds / 1000.0
   return ms


ser = serial.Serial(
        port='/dev/ttyUSB0', #Replace ttyS0 with ttyAM0 for Pi1,Pi2,Pi0
        baudrate = 115200,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        bytesize=serial.EIGHTBITS,
        timeout=1
)

while True:
    img = camera.Capture()
    detections = net.Detect(img, overlay="box,labels,conf")
    #print("detected {:d} objects in image".format(len(detections)))
    for detection in detections:
        index = detections[0].ClassID
        width = (detections[0].Width)
        height = (detections[0].Height)
        left = (detections[0].Left)
        right = (detections[0].Right)
        locationX = (detections[0].Center[0])
        locationY = (detections[0].Center[1])
        confidence = (detections[0].Confidence)
        
    #print index of item, width and horizonal location
    #print("detection:")
    #print(index)
    #print(width)
    #print(height)
    #print(left)
    #print(right)
    #print(locationX)
    #print(locationY)
    #print(net.GetClassDesc(index))
    #print(confidence)
    #error = left - 460//2
    #yaw = pid[0] * error + pid[1] * (error - pError)
    #yaw = int(np.clip(yaw, -100, 100))
    #print(yaw)

    if millis()>250:
        print(millis())
        start_time = datetime.now()
        if index==1:
            print("detected with confidence:{:f}".format(confidence*100))
            if (confidence*100) >70:
                print(width)
                if left >150 and left < 250:
                    print("middle")
                    if width < 400:
                        print("GO")
                        ser.write(b'<GO>')
                    else:
                        print("STOP")
                        ser.write(b'<STOP>')
                if left <=150:
                    print("LEFT")
                    ser.write(b'<LEFT>')
                if left >= 250:
                    print("RIGHT")
                    ser.write(b'<RIGHT>')
            else:
                print("Low confidence")
                ser.write(b'<STOP>')
        else:
            print("No Person")
            ser.write(b'<STOP>')
    
    # render the image
    display.Render(img)
    # update the title bar
    display.SetStatus("Object Detection | Network {:.0f} FPS".format(net.GetNetworkFPS()))
    # exit on input/output EOS
    if not camera.IsStreaming() or not display.IsStreaming():
        break
