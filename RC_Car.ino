//////////////////////////////////////////////////////////
//  This code write by LuPow for Smart RC car project   //
//  Feel free to read and review my code. all diagram   //
//  Will upload to github                               //
//             LuPow 2023 @ STBUU IROBOT                //          
//////////////////////////////////////////////////////////


#include <ESP32Servo.h>

Servo SteeringServo;
//define all PIN

//INPUT PIN
#define CH1 19 //RX
#define CH2 18 //RY
#define CH3 5  //LX
#define CH4 17 //LY
#define CH5 16 // Toggle Switch

//OUTPUT PIN
#define PWMPin 4
#define PinADrive 0
#define PinBDrive 2
#define SteeringServoPin 15

//Variable
int RXValue;
int RYValue;
int LXValue;
int LYValue; 
bool LedSwitch;

//function
int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue){
  int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}

// Read the switch channel and return a boolean value
bool readSwitch(byte channelInput, bool defaultValue){
  int intDefaultValue = (defaultValue)? 100: 0;
  int ch = readChannel(channelInput, 0, 100, intDefaultValue);
  return (ch > 50);
}

//Start run
void setup() {
  Serial.begin(115200);
  // define every CH pin as input
  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);
  pinMode(CH3, INPUT);
  pinMode(CH4, INPUT);
  pinMode(CH5, INPUT);

  //define every motorDriverPin as Output
  pinMode(PWMPin, OUTPUT);
  pinMode(PinADrive, OUTPUT);
  pinMode(PinBDrive, OUTPUT); 

  SteeringServo.attach(SteeringServoPin);

}

void loop() {
  // get value of each channel
  RXValue = readChannel(CH1, -100, 100, 0);
  RYValue = readChannel(CH2, -100, 100, 0);
  LXValue = readChannel(CH3, -100, 100, 0);
  LYValue = readChannel(CH4, -100, 100, 0);
  LedSwitch = readSwitch(CH5, false);

  //Forward/Backward
  //////////////////////////////////////////////////////////////////////

  //we will use +- 10 as center 
  //If more than 10 then user wanna move robot forward
  if (RYValue > 10){
    //drive motor forward with mapping value for PWM
    int PWMValue = map(abs(RYValue), 0, 100, 0, 255);
    analogWrite(PWMPin, PWMValue);
    digitalWrite(PinADrive, LOW);
    digitalWrite(PinBDrive, HIGH);
  }
  //If less than -10 then user wanna move robot backward
  else if(RYValue < -10){
    //drive motor backward with mapping value for PWM
    int PWMValue = map(abs(RYValue), 0, 100, 0, 255);
    analogWrite(PWMPin, PWMValue);
    digitalWrite(PinADrive, HIGH);
    digitalWrite(PinBDrive, LOW);
  }
  //else if value is between 10 and -10 then we will stop the motor
  else{
    digitalWrite(PinADrive, LOW);
    digitalWrite(PinBDrive, LOW);
  }
  //////////////////////////////////////////////////////////////////////

  //Left/Right
  //////////////////////////////////////////////////////////////////////

  //we will use +- 15 as center
  //If less than -15 or more than 20 then user wanna turn robot left or right
  if (RXValue < -15 || RXValue > 15){
    int SteeringValue = map(RXValue, -100, 100, 0, 180);
    SteeringServo.write(SteeringValue);

  //else if value is between 20 and -20 then we wnt servo to be at center
  }else{
    SteeringServo.write(90);
  }
  //////////////////////////////////////////////////////////////////////

  //For Debug Value Toggle this
  // Serial.print("Ch1: ");
  // Serial.print(ch1Value);
  // Serial.print(" | Ch2: ");
  // Serial.print(ch2Value);
  // Serial.print(" | Ch3: ");
  // Serial.print(ch3Value);
  // Serial.print(" | Ch4: ");
  // Serial.print(ch4Value);

}
