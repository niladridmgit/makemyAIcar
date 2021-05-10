#include <CheapStepper.h>
#include<Servo.h>
#include <NewPing.h>

#define TRIGGER_PIN   2 
#define ECHO_PIN      3 
#define MAX_DISTANCE 200 

typedef enum DIRECTION
{
  CRS_STOP = 0,
  CRS_GO,
  CRS_BACK,
  CRS_RIGHT,
  CRS_LEFT
};


// Motor pin definitions
#define motor1Pin1  4     // IN1 on the ULN2003 driver 1
#define motor1Pin2  5     // IN2 on the ULN2003 driver 1
#define motor1Pin3  6     // IN3 on the ULN2003 driver 1
#define motor1Pin4  7     // IN4 on the ULN2003 driver 1

#define motor2Pin1  8     // IN1 on the ULN2003 driver 2
#define motor2Pin2  9     // IN2 on the ULN2003 driver 2
#define motor2Pin3  10    // IN3 on the ULN2003 driver 2
#define motor2Pin4  11    // IN4 on the ULN2003 driver 2

CheapStepper stepper1 (motor1Pin1,motor1Pin2,motor1Pin3,motor1Pin4);  
CheapStepper stepper2 (motor2Pin1,motor2Pin2,motor2Pin3,motor2Pin4);
Servo sr04_servo;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

unsigned int pingSpeed = 1000; 
unsigned long pingTimer;     

unsigned int servo_pos = 40;

bool moveClockwise = true;

unsigned int robot_dir = 0;

const byte numChars = 10;
char receivedChars[numChars];
boolean newData = false;

void clearInputBuffer();
void recvSerialcmd();
void showSerialcmd();
void stepperControl();
void sensorData();
void echoCheck();
void crs_go();
void crs_stop();
void crs_back();
void crs_right();
void crs_left();

void setup() {

  sr04_servo.attach(12);
  sr04_servo.write(90);
  stepper1.setRpm(14);
  Serial.begin(115200);
  Serial.print("stepper1 RPM: "); Serial.print(stepper1.getRpm());
  Serial.println();
  Serial.print("stepper2 RPM: "); Serial.print(stepper2.getRpm());
  Serial.println();
  Serial.print("stepper1 delay (micros): "); Serial.print(stepper1.getDelay());
  Serial.println();
  Serial.print("stepper2 delay (micros): "); Serial.print(stepper2.getDelay()); 
  Serial.println();
  stepper1.newMoveToDegree(moveClockwise, 180);
  stepper2.newMoveToDegree(moveClockwise, 180);
  clearInputBuffer();
  pingTimer = millis(); // Start now.
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
    Serial.println(receivedChars);
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
    else if(strcmp(receivedChars, "SERVO") ==0) 
    {
      servo_pos = servo_pos+10;
      sr04_servo.write(servo_pos);
      if(servo_pos>=130)
          servo_pos=40;
    }
    newData = false;
  }
}

void crs_go()
{
    stepper1.run();
    stepper2.run();
    int stepsLeft = stepper1.getStepsLeft();
    if(stepsLeft)
      stepsLeft = stepper2.getStepsLeft();
    //Serial.println(stepsLeft);
    if (stepsLeft == 0){
      moveClockwise = true;
      Serial.print("stepper1_moveClockwise: ");Serial.println(moveClockwise);
      stepper1.newMoveDegrees (moveClockwise, 360);
      moveClockwise = false;
      Serial.print("stepper2_moveClockwise: ");Serial.println(moveClockwise);
      stepper2.newMoveDegrees (moveClockwise, 360);
    }
}

void crs_stop()
{
  //Serial.print("Stop_moveClockwise: ");Serial.println(moveClockwise);
  //Serial.print("stepper position: "); Serial.println(stepper1.getStep());
  stepper1.stop();
  stepper2.stop();
}

void crs_back()
{
    stepper1.run();
    stepper2.run();
    int stepsLeft = stepper1.getStepsLeft();
    if(stepsLeft)
      stepsLeft = stepper2.getStepsLeft();
    //Serial.println(stepsLeft);
    if (stepsLeft == 0){
      moveClockwise = false;
      Serial.print("stepper1_moveClockwise: ");Serial.println(moveClockwise);
      stepper1.newMoveDegrees (moveClockwise, 360);
      moveClockwise = true;
      Serial.print("stepper2_moveClockwise: ");Serial.println(moveClockwise);
      stepper2.newMoveDegrees (moveClockwise, 360);
    }
}

void crs_right()
{
    stepper1.run();
    stepper2.run();
    int stepsLeft = stepper1.getStepsLeft();
    if(stepsLeft)
      stepsLeft = stepper2.getStepsLeft();
    //Serial.println(stepsLeft);
    if (stepsLeft == 0){
      moveClockwise = true;
      Serial.print("stepper1_moveClockwise: ");Serial.println(moveClockwise);
      stepper1.newMoveDegrees (moveClockwise, 360);
      moveClockwise = true;
      Serial.print("stepper2_moveClockwise: ");Serial.println(moveClockwise);
      stepper2.newMoveDegrees (moveClockwise, 360);
    }
}
void crs_left()
{
    stepper1.run();
    stepper2.run();
    int stepsLeft = stepper1.getStepsLeft();
    if(stepsLeft)
      stepsLeft = stepper2.getStepsLeft();
    //Serial.println(stepsLeft);
    if (stepsLeft == 0){
      moveClockwise = false;
      Serial.print("stepper1_moveClockwise: ");Serial.println(moveClockwise);
      stepper1.newMoveDegrees (moveClockwise, 360);
      moveClockwise = false;
      Serial.print("stepper2_moveClockwise: ");Serial.println(moveClockwise);
      stepper2.newMoveDegrees (moveClockwise, 360);
    }
}
void stepperControl()
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

void echoCheck() { 
  if (sonar.check_timer()) { 
    Serial.print("Ping: ");
    int disttance = sonar.ping_result / US_ROUNDTRIP_CM;
    Serial.print(disttance); 
    Serial.println("cm");
    if(disttance<15)
    {
      robot_dir=CRS_BACK;
    }
    else if(disttance>50)
    {
      robot_dir=CRS_GO;
    }
    else if(disttance>40 && disttance<50)
    {
      robot_dir=CRS_STOP;
    }
  }
}

void sensorData()
{
  if (millis() >= pingTimer) {   
    pingTimer += pingSpeed;      
    sonar.ping_timer(echoCheck);
  }
}

void loop() {

  recvSerialcmd();
  showSerialcmd();
  stepperControl();
  //sensorData();
 
}
