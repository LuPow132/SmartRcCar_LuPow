//////////////////////////////////////////////////////////
//  This code write by LuPow for Smart RC car project   //
//  Feel free to read and review my code. all diagram   //
//  Will upload to github soon                          //
//             LuPow 2023 @ STBUU IROBOT                //          
//////////////////////////////////////////////////////////

//define all PIN

//INPUT PIN
#define CH1 19 //RX
#define CH2 18 //RY
#define CH3 5  //LX
#define CH4 17 //LY

//OUTPUT PIN
#define PWMPin 16
#define PinADrive 4
#define PinBDrive 0
#define PinASteering 2
#define PinBSteering 15

//Variable
int ch1Value;
int ch2Value;
int ch3Value;
int ch4Value; 

//function
int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue){
  int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}

//Start run
void setup() {
  // define every CH pin as input
  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);
  pinMode(CH3, INPUT);
  pinMode(CH4, INPUT);

  //define every motorDriverPin as Output
  pinMode(PWMPin, OUTPUT);
  pinMode(PinADrive, OUTPUT);
  pinMode(PinBDrive, OUTPUT); 
  pinMode(PinASteering, OUTPUT);
  pinMode(PinBSteering, OUTPUT);
}

void loop() {
  // get value of each channel
  ch1Value = readChannel(CH1, -100, 100, 0);
  ch2Value = readChannel(CH2, -100, 100, 0);
  ch3Value = readChannel(CH3, -100, 100, -10  0);
  ch4Value = readChannel(CH4, -100, 100, 0);

  //Forward/Backward
  //////////////////////////////////////////////////////////////////////

  //we will use +- 10 as center 
  //If more than 10 then user wanna move robot forward
  if (ch2Value > 10){
    //drive motor forward with mapping value for PWM
    int PWMValue = map(abs(ch2Value), 0, 100, 0, 255);
    analogWrite(PWMPin, PWMValue);
    digitalWrite(PinADrive, HIGH);
    digitalWrite(PINBDrive, LOW);
  }
  //If less than -10 then user wanna move robot backward
  else if(ch2Value < -10){
    //drive motor backward with mapping value for PWM
    int PWMValue = map(abs(ch2Value), 0, 100, 0, 255);
    analogWrite(PWMPin, PWMValue);
    digitalWrite(PinADrive, LOW);
    digitalWrite(PINBDrive, HIGH);
  }
  //else if value is between 10 and -10 then we will stop the motor
  else{
    digitalWrite(PinADrive, LOW);
    digitalWrite(PINBDrive, LOW);
  }
  //////////////////////////////////////////////////////////////////////

  //Left/Right
  //////////////////////////////////////////////////////////////////////

  //we will use +- 10 as center
  //If more than 10 then user wanna turn right
  if (ch1Value > 10){
    //drive motor to turn right
    digitalWrite(PinASteering, HIGH);
    digitalWrite(PINBSteering, LOW);
  }
  //If less than -10 then user wanna move robot backward
  else if(ch1Value < -10){
    //drive motor to turn left
    digitalWrite(PinASteering, LOW);
    digitalWrite(PINBSteering, HIGH);
  }
  //else if value is between 10 and -10 then we will stop the motor
  else{
    digitalWrite(PinASteering, LOW);
    digitalWrite(PINBSteering, LOW);
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
