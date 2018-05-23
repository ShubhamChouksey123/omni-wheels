17// code foe line follower with three LSA08 in analog mode , and using omni four wheeled drive
//  consider a drive with LSA1 in front ,LSA2 in right and LSA3 in left
 const byte analogPin1 = 0;   // Connect AN output of LSA1 to analog pin 0
 const byte junctionPulse1 = 28; // Connect JPULSE of LSA1 to pin 28
 const byte analogPin2 = 1;   // Connect AN output of LSA2 to analog pin 1
 const byte junctionPulse2 = 29; // Connect JPULSE of LSA2 to pin 29
 const byte analogPin3 = 2;   // Connect AN output of LSA3 to analog pin 2
 const byte junctionPulse3 = 30; // Connect JPULSE of LSA3 to pin 30

const byte REARdir1 = 31;   // Connect DIR1 of motor driver to digital pin 31 (of rear wheels )
const byte REARdir2 = 32;   // Connect DIR2 of motor driver to digital pin 32 (of rear wheels )
const byte REARpwm1 = 2;   // Connect PWM1 of motor driver to pwm pin 2 (of rear wheels )
const byte REARpwm2 = 3;   // Connect PWM2 of motor driver to pwm pin 3 (of rear wheels )

const byte FRONTdir1 = 33;   // Connect DIR1 of motor driver to digital pin 33 (of front wheels )
const byte FRONTdir2 = 34;   // Connect DIR2 of motor driver to digital pin 34 (of front wheels )
const byte FRONTpwm1 = 4;   // Connect PWM1 of motor driver to pwm pin 4 (of front wheels )
const byte FRONTpwm2 = 5;   // Connect PWM2 of motor driver to pwm pin 5 (of front wheels )

int readValue1,readValue2,readValue3,positionValue1,positionValue2,positionValue3;    // Variables to store analog and line position value
unsigned int junctionCount = 0;   // Variable to store junction count value

void setup() {
  // put your setup code here, to run once:
  pinMode(junctionPulse1,INPUT);
  pinMode(junctionPulse2,INPUT);
  pinMode(junctionPulse3,INPUT);

  for(byte i=2;i<=5;i++){
    pinMode(i,OUTPUT);
  }
  for(byte j=31;j<=34;j++){
    pinMode(j,OUTPUT);
  }
  digitalWrite(REARpwm1,LOW);
  digitalWrite(REARpwm2,LOW);
  digitalWrite(REARdir1,HIGH); // if clockwise then ok , otherwise LOW
  digitalWrite(REARdir2,HIGH);

  digitalWrite(FRONTpwm1,LOW);
  digitalWrite(FRONTpwm2,LOW);
  digitalWrite(FRONTdir1,HIGH);
  digitalWrite(FRONTdir2,HIGH);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(junctionPulse1)) {
    while(digitalRead(junctionPulse1)) {
      moveForward();
    }
    // Increment junction count by 1 after the junction
    // You can do whatever you want with the junction count
    junctionCount++;
  }

  readValue1 = analogRead(analogPin1);    // Read value from analog pin A0 (of LSA1)
  readValue2 = analogRead(analogPin2);    // Read value from analog pin A1 (of LSA1)
  readValue3 = analogRead(analogPin3);    // Read value from analog pin A2 (of LSA1)

  positionValue1 = ((float)readValue1/921)*70;
  positionValue2 = ((float)readValue2/921)*70;
  positionValue3 = ((float)readValue3/921)*70;
  
  if((positionValue1 >=0 && positionValue1 <= 70) && (positionValue2 >= 0 && positionValue2 <= 70) && (positionValue3 >= 0 && positionValue3 <= 70)) {
    moveForward();
  }
  if((positionValue1 >=0 && positionValue1 <= 70) && (positionValue2 < 0 || positionValue2 >70) && (positionValue3 < 0 || positionValue3 > 70)) {
    moveForward();
  }
  if((positionValue1 >= 0 && positionValue1 <=70) && (positionValue2 >= 0 && positionValue2 <=70) && (positionValue3 < 0 || positionValue3 >70) ){
    moveRight();
  }
  if( (positionValue1 >= 0 && positionValue1 <=70) && (positionValue2 < 0 || positionValue2 > 70) && (positionValue3 >= 0 && positionValue3 <=70)){
    moveLeft();
  }
  if( (positionValue1 < 0 || positionValue1 > 70) && (positionValue2 >= 0 && positionValue2 <=70) && (positionValue3 < 0 || positionValue3 > 70)){
    moveRight();
  }
  if( (positionValue1 < 0 || positionValue1 > 70) && (positionValue2 < 0 || positionValue2 > 70) && (positionValue3 >= 0 && positionValue3 <= 70)){
    moveLeft();
  }
  if((positionValue1 < 0 || positionValue1 > 70) && (positionValue2 >= 0 && positionValue2 <= 70) && (positionValue3 >= 0 && positionValue3 <= 70)) {
    moveLeft();
  }
  else{
    moveForward();
  }
}

void moveForward(){
  delay(1);
  digitalWrite(REARdir1,HIGH); 
  digitalWrite(REARdir2,LOW);
  digitalWrite(FRONTdir1,HIGH);
  digitalWrite(FRONTdir2,LOW);

  delay(1);
  analogWrite(REARpwm1,90);
  analogWrite(REARpwm2,90);
  analogWrite(FRONTpwm1,90);
  analogWrite(FRONTpwm2,90);
    
}
void moveRight(){
  delay(1);
  digitalWrite(REARdir1,LOW); 
  digitalWrite(REARdir2,LOW);
  digitalWrite(FRONTdir1,HIGH);
  digitalWrite(FRONTdir2,HIGH);

  delay(1);
  analogWrite(REARpwm1,90);
  analogWrite(REARpwm2,90);
  analogWrite(FRONTpwm1,90);
  analogWrite(FRONTpwm2,90);
}
void moveLeft(){
  delay(1);
  digitalWrite(REARdir1,HIGH); 
  digitalWrite(REARdir2,HIGH);
  digitalWrite(FRONTdir1,LOW);
  digitalWrite(FRONTdir2,LOW);

  delay(1);
  analogWrite(REARpwm1,90);
  analogWrite(REARpwm2,90);
  analogWrite(FRONTpwm1,90);
  analogWrite(FRONTpwm2,90);
}
void wait(){
  delay(1);
  analogWrite(REARpwm1,0);
  analogWrite(REARpwm2,0);
  analogWrite(FRONTpwm1,0);
  analogWrite(FRONTpwm2,0);
}

