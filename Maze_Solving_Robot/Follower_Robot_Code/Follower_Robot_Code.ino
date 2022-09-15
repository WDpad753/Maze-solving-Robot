#include<SoftwareSerial.h> 
 
const int rxPin = 0; 
const int txPin = 1; 
SoftwareSerial mySerial(rxPin,txPin); //RX,TX. 
byte packet; 
int LEDPin = 13; 
 
void setup()  
{   
  pinMode(LEDPin, OUTPUT);   
  Serial.begin(9600);   
  mySerial.begin(9600); 
  Serial.print("Received Maze Map:"); 
  Serial.print("\n"); 
} 
 
 
void loop() 
{ 
  if(mySerial.available() != 0) 
  { 
    digitalWrite(LEDPin, HIGH);       // Turn LED on     
    char inData = mySerial.read();     
    Serial.print(inData);     
    packet ++;     
    digitalWrite(LEDPin, LOW);       // Turn LED off 
    if (inData == 'L') 
    { 
      Left(); 
    } 
    if (inData == 'F') 
    { 
      Forward(); 
    } 
    if (inData == 'R') 
    { 
      Right(); 
    } 
    if (inData == 'B') 
    { 
     Backward(); 
    } 
  } 
}

//=====Functions Declarations=====// 
// Moving Forward Function // 
void Forward() 
{ 
  Serial.print("Both Motor ON"); 
  Serial.print("\n"); 
} 
 
// Moving Right Function // 
void Right() 
{ 
  Serial.print("Left Motor ON"); 
  Serial.print("\n"); 
} 
 
// Moving Left Function // 
void Left() 
{ 
  Serial.print("Right Motor ON"); 
  Serial.print("\n"); 
} 
 
// Moving Backward Function // 
void Backward() 
{ 
  Serial.print("Left Motor ON");   
  Serial.print("\n"); 
} 
