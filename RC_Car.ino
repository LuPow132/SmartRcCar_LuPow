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
int RXValue;
int RYValue;
int LXValue;
int LYValue; 

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

  //define every motorDriverPin as Output
  pinMode(PWMPin, OUTPUT);
  pinMode(PinADrive, OUTPUT);
  pinMode(PinBDrive, OUTPUT); 
  pinMode(PinASteering, OUTPUT);
  pinMode(PinBSteering, OUTPUT);
}

void loop() {
  // get value of each channel
  RXValue = readChannel(CH1, -100, 100, 0);
  RYValue = readChannel(CH2, -100, 100, 0);
  LXValue = readChannel(CH3, -100, 100, 0);
  LYValue = readChannel(CH4, -100, 100, 0);

  Serial.println(RXValue);
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

  //we will use +- 10 as center
  //If less than -10 then user wanna move robot backward
  if (RXValue < -20){
    //drive motor to turn right
    digitalWrite(PinASteering, HIGH);
    digitalWrite(PinBSteering, LOW);
  }
  //If more than 10 then user wanna turn right
  else if(RXValue > 20){
    //drive motor to turn left
    digitalWrite(PinASteering, LOW);
    digitalWrite(PinBSteering, HIGH);
  }
  //else if value is between 10 and -10 then we will stop the motor
  else{
    digitalWrite(PinASteering, LOW);
    digitalWrite(PinBSteering, LOW);
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
