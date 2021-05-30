#include<Servo.h>
#include <AFMotor.h>

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

typedef enum DIRECTION
{
  CRS_STOP = 0,
  CRS_GO,
  CRS_BACK,
  CRS_RIGHT,
  CRS_LEFT
};

#define SERVO1_pin  9
#define SERVO2_pin  10

Servo servo1_cam_yaw;
Servo servo2_cam_pitch;


unsigned int servo_pos_cam_yaw = 20;
unsigned int servo_pos_cam_pitch = 50;

bool moveClockwise = true;

unsigned int robot_dir = 0;

const byte numChars = 15;
char receivedChars[numChars];
boolean newData = false;

void clearInputBuffer();
void recvSerialcmd();
void showSerialcmd();
void dcMotorControl();
void crs_go();
void crs_stop();
void crs_back();
void crs_right();
void crs_left();

void setup() {

  // Servo Setup //
  servo1_cam_yaw.attach(SERVO1_pin);
  servo1_cam_yaw.write(90);
  servo2_cam_pitch.attach(SERVO2_pin);
  servo2_cam_pitch.write(90);
  Serial.begin(115200);
  //Serial.flush();

  motor1.setSpeed(100);
  motor1.run(RELEASE);
  motor2.setSpeed(100);
  motor2.run(RELEASE);
  motor3.setSpeed(100);
  motor3.run(RELEASE);
  motor4.setSpeed(100);
  motor4.run(RELEASE);
  
  clearInputBuffer();
  //robot_dir=CRS_GO;
  
}

void clearInputBuffer() {
   while (Serial.available() > 0) {
        Serial.read();
   }
}

void recvSerialcmd() {
  static boolean recvInProgress = false;
  static byte ndx = 0;
  char startMarker = '<';
  char endMarker = '>';
  char rc;
  
  if (Serial.available() > 0) {
    while (Serial.available() > 0 && newData == false) { // <<== NEW - get all bytes from buffer
      rc = Serial.read();

      if (recvInProgress == true) {
        if (rc != endMarker) {
          receivedChars[ndx] = rc;
          ndx++;
          if (ndx >= numChars) {
            ndx = numChars - 1;
          }
        }
        else {
          receivedChars[ndx] = '\0'; // terminate the string
          recvInProgress = false;
          ndx = 0;
          newData = true;
        }
      }

      else if (rc == startMarker) {
        recvInProgress = true;
      }
    } 
  }
}

void showSerialcmd() {
  if (newData == true) {
    Serial.print("Received: ");
    //Serial.println(receivedChars);
    if(strcmp(receivedChars, "GO") ==0)
    {
      crs_stop();
      robot_dir=CRS_GO;
    }
    else if(strcmp(receivedChars, "STOP") ==0) 
    {
      crs_stop();
      robot_dir=CRS_STOP;
    }
    else if(strcmp(receivedChars, "BACK") ==0) 
    {
      crs_stop();
      robot_dir=CRS_BACK;
    }
    else if(strcmp(receivedChars, "RIGHT") ==0) 
    {
      crs_stop();
      robot_dir=CRS_RIGHT;
    }
    else if(strcmp(receivedChars, "LEFT") ==0) 
    {
      crs_stop();
      robot_dir=CRS_LEFT; 
    }
    else if(strncmp(receivedChars, "SERVO1",6) ==0) 
    {
      String get_servo_pos = receivedChars;
      int servo_pos = get_servo_pos.indexOf(',');
      if(servo_pos)
      {
        String rx_servo_pos = get_servo_pos.substring(servo_pos+1);
        if(rx_servo_pos.length()>0)
        {
          int rx_servo_pos_int = (int)rx_servo_pos.toInt();
          Serial.println(rx_servo_pos_int);
          if(rx_servo_pos_int>=30 && rx_servo_pos_int<=160)
          {
            servo1_cam_yaw.write(rx_servo_pos_int);
          }
        }
      }
      
    }
    else if(strncmp(receivedChars, "SERVO2",6) ==0) 
    {
      String get_servo_pos = receivedChars;
      int servo_pos = get_servo_pos.indexOf(',');
      if(servo_pos)
      {
        String rx_servo_pos = get_servo_pos.substring(servo_pos+1);
        if(rx_servo_pos.length()>0)
        {
          int rx_servo_pos_int = (int)rx_servo_pos.toInt();
          Serial.println(rx_servo_pos_int);
          if(rx_servo_pos_int>=60 && rx_servo_pos_int<=140)
          {
            servo2_cam_pitch.write(rx_servo_pos_int);
          }
        }
      }
    }
    newData = false;
  }
}

void crs_go()
{

  motor1.setSpeed(240);
  motor1.run(FORWARD);
  motor2.setSpeed(240);
  motor2.run(FORWARD);
  motor3.setSpeed(240);
  motor3.run(FORWARD);
  motor4.setSpeed(240);
  motor4.run(FORWARD);
   
}

void crs_stop()
{
  motor1.setSpeed(50);
  motor1.run(RELEASE);
  motor2.setSpeed(50);
  motor2.run(RELEASE);
  motor3.setSpeed(50);
  motor3.run(RELEASE);
  motor4.setSpeed(50);
  motor4.run(RELEASE);
}

void crs_back()
{
  motor1.setSpeed(240);
  motor1.run(BACKWARD);
  motor2.setSpeed(240);
  motor2.run(BACKWARD);
  motor3.setSpeed(240);
  motor3.run(BACKWARD);
  motor4.setSpeed(240);
  motor4.run(BACKWARD);
   
}

void crs_right()
{

  motor1.setSpeed(240);
  motor1.run(BACKWARD);
  motor2.setSpeed(240);
  motor2.run(FORWARD);
  motor3.setSpeed(240);
  motor3.run(BACKWARD);
  motor4.setSpeed(240);
  motor4.run(FORWARD);
    
}
void crs_left()
{

  motor1.setSpeed(240);
  motor1.run(FORWARD);
  motor2.setSpeed(240);
  motor2.run(BACKWARD);
  motor3.setSpeed(240);
  motor3.run(FORWARD);
  motor4.setSpeed(240);
  motor4.run(BACKWARD);
    
}
void dcMotorControl()
{
  if(robot_dir==CRS_GO)
  {
    crs_go();
  }
  else if(robot_dir==CRS_STOP)
  {
    crs_stop();
  }
  else if(robot_dir==CRS_BACK)
  {
    crs_back();
  }
  else if(robot_dir==CRS_RIGHT)
  {
    crs_right();
  }
  else if(robot_dir==CRS_LEFT)
  {
    crs_left();
  }
}

void loop() {
  recvSerialcmd();
  showSerialcmd();
  dcMotorControl();
}
