// Libraries Declarations // 
#include <Servo.h> 
#include <SD.h> 
 
// Initialising Map //
char UnknownMaze[11][11] =  
{  
{'.', '-', '-', '-', '-', '-', '-', '-', '-', '-', '.'}, 
{'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'}, 
{'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'}, 
{'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'}, 
{'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'}, 
{'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'}, 
{'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'}, 
{'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'}, 
{'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'}, 
{'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'}, 
{'.', '-', '-', '-', '-', '-', '-', '-', '-', '-', '.'}, 
}; 

char SolvedMaze[11][11] =  
{  
{'.', '-', '-', '-', '-', '-', '-', '-', '-', '-', '.'}, 
{'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'}, 
{'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'}, 
{'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'}, 
{'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'}, 
{'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'}, 
{'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'}, 
{'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'}, 
{'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'}, 
{'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'}, 
{'.', '-', '-', '-', '-', '-', '-', '-', '-', '-', '.'}, 
}; 
 
// Initalising and declaring varaibles //
int servoPin = 2; 
Servo servo; 
const int pingPin = 3; 
unsigned int duration,inches; 
int leftscan,centerscan,rightscan; 
boolean scan = true; 
int LEDPin =  53;                  // Status LED connected to digital pin 13 
int row = 0; 
int column = 0; 
int columnrobot = 1; 
int rowrobot = 10; 
int uTurn = 0; 
int Movement = 0; 
int MinimumSafeDistance = 10; 
char Direction; 
 
// Unknown Maze Function // 
void UnknownMap() 
{ 
// Making an 2D array of the unknown Maze // 
row = 0; column = 0; 
for(row = 0;row < 11;row++) 
{ 
  for(column = 0;column < 11;column++) 
  { 
  Serial.print(UnknownMaze[row][column]); 
  Serial.print(' '); 
  Serial1.write(UnknownMaze[row][column]); 
  Serial1.write(' '); 
  Serial2.write(UnknownMaze[row][column]); 
  Serial2.write(' '); 
  } 
  Serial.print("\n"); 
  Serial1.write("\n"); 
  Serial2.write("\n"); 
} 
Serial.print("\n"); 
Serial1.write("\n"); 
Serial2.write("\n"); 
} 
 
// Solved Maze Function // void SolvedMap() 
{ 
// Making an 2D array of the Solved Maze // 
row = 0; column = 0; 
for(row = 0;row < 11;row++) 
{ 
  for(column = 0;column < 11;column++) 
  { 
  Serial.print(SolvedMaze[row][column]); 
  Serial.print(' '); 
  Serial1.write(SolvedMaze[row][column]); 
  Serial1.write(' '); 
  Serial2.write(SolvedMaze[row][column]); 
  Serial2.write(' '); 
  } 
  Serial.print("\n"); 
  Serial1.write("\n"); 
  Serial2.write("\n"); 
  } 
  Serial.print("\n"); 
  Serial1.write("\n"); 
  Serial2.write("\n"); 
} 
 
// Main Program where it's being performed once: 
void setup() 
{ 
  pinMode(LEDPin, OUTPUT);         // Set the Pin to output    
  servo.attach(servoPin);          // Set the Servo pin to output   
  Serial.begin(9600);              // Setting the baud for serial monitor 
  Serial1.begin(9600);             // Setting the baud for bluetooth   
  Serial2.begin(9600);             // Setting the baud for OpenLog   
  delay(1000);                     // Wait a second for OpenLog to initiate  
  // Printing Unknown Maze map 
  Serial.print("Unknown MAZE"); 
  Serial.print("\n"); 
  Serial1.write("Unknown MAZE");   Serial1.write("\n"); 
  Serial2.write("Unknown MAZE"); 
  Serial2.write("\n"); 
  UnknownMaze[10][1] = 'E';        // Set the entrance of the robot 
  UnknownMaze[0][9] = 'T';        // Set the exit of the robot   
  UnknownMap();                   // Call the unknown map Function   
  delay(2000); 
  // Printing Solved Maze map 
  Serial.print("Solved Maze"); 
  Serial.print("\n"); 
  Serial1.write("Solved Maze");   
  Serial1.write("\n"); 
  Serial2.write("Solved Maze"); 
  Serial2.write("\n"); 
  SolvedMap();                    // Call the solved map Function 
}  
// Main Program where it's being performed in a loop: void loop() 
{ 
  while(rowrobot != 0 && columnrobot != 9) 
  { 
   // Initialising Varaibles //     
   int leftscan;    
   int centerscan;    
   int rightscan; 
    
   // Scanning the Perimeter // 
   // Scan Left //    
   servo.write(180);                      // Rotating the servo to 180 degrees    
   delay(2000);                           // Adding Delay to extend the durtation for the servo motor to be at an angle of 180 degrees 
   leftscan = Sensor();                   // Using the Sensor function to detect if there is wall or not    
   leftscan = inches;                     // Equating the distance to the leftscan variable 
   Serial.print("LeftScan: "); 
   Serial.println(leftscan);    
   // Scan Center //    
   servo.write(90);                       // Rotating the servo to 90 degrees    
   delay(2000);                           // Adding Delay to extend the durtation for the servo motor to be at an angle of 90 degrees    
   centerscan = Sensor();                 // Using the Sensor function to detect if there is wall or not 
   centerscan = inches;                   // Equating the distance to the centerscan variable 
   Serial.print("CenterScan: "); 
   Serial.println(centerscan); 
   // Scan Right //    
   servo.write(0);                        // Rotating the servo to 0 degrees    
   delay(2000);                           // Adding Delay to extend the durtation for the servo motor to be at an angle of 0 degrees    
   rightscan = Sensor();                  // Using the Sensor function to detect if there is wall or not    
   rightscan = inches;                    // Equating the distance to the rightscan variable 
   Serial.print("RightScan: "); 
   Serial.println(rightscan);    
   // Return To Center //    
   servo.write(90);                       // Rotating the servo to 90 degrees    
   delay(5000);                           // Adding Delay to extend the durtation for the servo motor to be at an angle of 90 degrees 
    
    // Movement of the Robot //     
    // Current Direction // 
    if (leftscan > MinimumSafeDistance) 
    { 
      Direction = 'L'; 
      Serial.print("Direction: "); 
      Serial.println(Direction); 
      Left(); 
      Serial1.write(Direction); 
      Forward(); 
      // Showing the Movement of the Robot: 
      SolvedMaze[rowrobot][columnrobot] = 'X'; 
      SolvedMaze[rowrobot][columnrobot-1] = 'X';       
      SolvedMaze[rowrobot][columnrobot-2] = 'X';       
      columnrobot = columnrobot-3; 
      SolvedMaze[rowrobot][columnrobot] = '<';       
      // Printing the Movement:       
      digitalWrite(LEDPin, HIGH);       // Turn LED on to indicate that data is being transmitted       
      SolvedMap();                      // Call the solved map Function       
      digitalWrite(LEDPin, LOW);        // Turn LED off to indicate that data is transmitted       
      delay(3000);
      
      // Scanning the Perimeter // 
      // Scan Left //        
      servo.write(180);                      // Rotating the servo to 180 degrees        
      delay(2000);                           // Adding Delay to extend the durtation for the servo motor to be at an angle of 180 degrees        
      leftscan = Sensor();                   // Using the Sensor function to detect if there is wall or not 
      leftscan = inches;                     // Equating the distance to the leftscan variable 
      Serial.print("LeftScan: "); 
      Serial.println(leftscan);        
      // Scan Center //        
      servo.write(90);                       // Rotating the servo to 90 degrees        
      delay(2000);                           // Adding Delay to extend the durtation for the servo motor to be at an angle of 90 degrees        
      centerscan = Sensor();                 // Using the Sensor function to detect if there is wall or not 
      centerscan = inches;                   // Equating the distance to the centerscan variable 
      Serial.print("CenterScan: "); 
      Serial.println(centerscan); 
      // Scan Right //        
      servo.write(0);                        // Rotating the servo to 0 degrees        
      delay(2000);                           // Adding Delay to extend the durtation for the servo motor to be at an angle of 0 degrees        
      rightscan = Sensor();                  // Using the Sensor function to detect if there is wall or not 
      rightscan = inches;                    // Equating the distance to the rightscan variable 
      Serial.print("RightScan: "); 
      Serial.println(rightscan); 
      // Return To Center //        
      servo.write(90);                       // Rotating the servo to 90 degrees        
      delay(5000);                           // Adding Delay to extend the durtation for the servo motor to be at an angle of 90 degrees 
      // Turning the Robot: 
      Serial.print("Turning");       
      Serial.print("\n");       
      if (leftscan > MinimumSafeDistance) 
      { 
        Direction = 'B'; 
        Serial.print("Turning Direction:"); 
        Serial.print("\t"); 
        Left(); 
        // Showing the Movement of the Robot:         
        SolvedMaze[rowrobot][columnrobot] = 'v';         
        delay(2000); 
        Forward(); 
        // Showing the Movement of the Robot after turning: 
        SolvedMaze[rowrobot][columnrobot] = 'X';         
        SolvedMaze[rowrobot+1][columnrobot] = 'X';         
        rowrobot = rowrobot+2; 
        SolvedMaze[rowrobot][columnrobot] = 'V'; 
      } 
      else if (centerscan > MinimumSafeDistance) 
      { 
        Direction = 'F'; 
        Serial.print("Facing Forward"); 
        Serial.print("\n"); 
        SolvedMaze[rowrobot][columnrobot] = '<';         
        delay(2000); 
        Forward(); 
        // Showing the Movement of the Robot after turning: 
        SolvedMaze[rowrobot][columnrobot] = 'X';         
        SolvedMaze[rowrobot][columnrobot-1] = 'X';         
        columnrobot = columnrobot-2; 
        SolvedMaze[rowrobot][columnrobot] = '<'; 
      } 
      else if (rightscan > MinimumSafeDistance) 
      { 
        Direction = 'R'; 
        Serial.print("Turning Direction:"); 
        Serial.print("\t"); 
        Left(); 
        // Showing the Movement of the Robot:         
        SolvedMaze[rowrobot][columnrobot] = '^';         
        delay(2000); 
        Forward(); 
        // Showing the Movement of the Robot after turning: 
        SolvedMaze[rowrobot][columnrobot] = 'X';         
        SolvedMaze[rowrobot-1][columnrobot] = 'X';         
        rowrobot = rowrobot-2; 
        SolvedMaze[rowrobot][columnrobot] = '^'; 
      }       else 
      { 
        Direction = 'L'; 
        Serial.print("Turning Direction:"); 
        Serial.print("\t"); 
        Right(); 
        SolvedMaze[columnrobot][rowrobot] = '^';         
        delay(2000); 
        Forward(); 
        // Showing the Movement of the Robot after turning: 
        SolvedMaze[rowrobot][columnrobot] = 'X';         
        SolvedMaze[rowrobot-1][columnrobot] = 'X';         
        rowrobot = rowrobot-2; 
        SolvedMaze[rowrobot][columnrobot] = '^'; 
      } 
      digitalWrite(LEDPin, HIGH);       // Turn LED on to indicate that data is being transmitted       
      SolvedMap();                      // Call the solved map Function       
      digitalWrite(LEDPin, LOW);        // Turn LED off to indicate that data is transmitted       
      delay(5000); 
    } 
 
   // Current Direction // 
   else if (centerscan > MinimumSafeDistance) 
   { 
      Direction = 'F'; 
      Serial.print("Direction: "); 
      Serial.println(Direction); 
      Forward(); 
      Serial1.write(Direction); 
      // Showing the Movement of the Robot: 
      SolvedMaze[rowrobot][columnrobot] = 'X'; 
      SolvedMaze[rowrobot-1][columnrobot] = 'X';       
      SolvedMaze[rowrobot-2][columnrobot] = 'X';       
      rowrobot = rowrobot-3; 
      SolvedMaze[rowrobot][columnrobot] = '^';       
      // Printing the Movement:       
      digitalWrite(LEDPin, HIGH);       // Turn LED on to indicate that data is being transmitted       
      SolvedMap();                      // Call the solved map Function       
      digitalWrite(LEDPin, LOW);        // Turn LED off to indicate that data is transmitted       
      delay(3000); 
      
      // Scanning the Perimeter // 
      // Scan Left //        
      servo.write(180);                      // Rotating the servo to 180 degrees        
      delay(2000);                           // Adding Delay to extend the durtation for the servo motor to be at an angle of 180 degrees        
      leftscan = Sensor();                   // Using the Sensor function to detect if there is wall or not 
      leftscan = inches;                     // Equating the distance to the leftscan variable 
      Serial.print("LeftScan: "); 
      Serial.println(leftscan);        
      // Scan Center //        
      servo.write(90);                       // Rotating the servo to 90 degrees        
      delay(2000);                           // Adding Delay to extend the durtation for the servo motor to be at an angle of 90 degrees        
      centerscan = Sensor();                 // Using the Sensor function to detect if there is wall or not 
      centerscan = inches;                   // Equating the distance to the centerscan variable 
      Serial.print("CenterScan: "); 
      Serial.println(centerscan); 
      // Scan Right //        
      servo.write(0);                        // Rotating the servo to 0 degrees        
      delay(2000);                           // Adding Delay to extend the durtation for the servo motor to be at an angle of 0 degrees        
      rightscan = Sensor();                  // Using the Sensor function to detect if there is wall or not 
      rightscan = inches;                    // Equating the distance to the rightscan variable 
      Serial.print("RightScan: "); 
      Serial.println(rightscan);       
      // Return To Center //        
      servo.write(90);                       // Rotating the servo to 90 degrees        
      delay(5000);                           // Adding Delay to extend the durtation for the servo motor to be at an angle of 90 degrees 
      // Turning the Robot: 
      Serial.print("Turning");       
      Serial.print("\n");       
      if (centerscan > MinimumSafeDistance) 
      { 
        Direction = 'F'; 
        Serial.print("Facing Forward"); 
        Serial.print("\n"); 
        SolvedMaze[rowrobot][columnrobot] = '^';         
        delay(2000); 
        // Showing the Movement of the Robot after turning: 
        Forward(); 
        SolvedMaze[rowrobot][columnrobot] = 'X';         
        SolvedMaze[rowrobot-1][columnrobot] = 'X';         
        rowrobot = rowrobot-2; 
        SolvedMaze[rowrobot][columnrobot] = '^'; 
      } 
      else if (leftscan > MinimumSafeDistance) 
      { 
        Direction = 'L'; 
        Serial.print("Turning Direction:"); 
        Serial.print("\t"); 
        Left(); 
        SolvedMaze[rowrobot][columnrobot] = '<'; 
        delay(2000); 
        // Showing the Movement of the Robot after turning: 
        Forward(); 
        SolvedMaze[rowrobot][columnrobot] = 'X';         
        SolvedMaze[rowrobot][columnrobot-1] = 'X';         
        columnrobot = columnrobot-2; 
        SolvedMaze[rowrobot][columnrobot] = '<'; 
      } 
      else if (rightscan > MinimumSafeDistance) 
      { 
        Direction = 'R'; 
        Serial.print("Turning Direction:"); 
        Serial.print("\t"); 
        Right(); 
        SolvedMaze[rowrobot][columnrobot] = '>';         
        delay(2000); 
        Forward(); 
        // Showing the Movement of the Robot after turning: 
        SolvedMaze[rowrobot][columnrobot] = 'X';         
        SolvedMaze[rowrobot][columnrobot+1] = 'X';         
        columnrobot = columnrobot+2; 
        SolvedMaze[rowrobot][columnrobot] = '>'; 
      }       
      else 
      { 
        Direction = 'B'; 
        Serial.print("Turning Direction:"); 
        Serial.print("\t"); 
        Backward(); 
        SolvedMaze[rowrobot][columnrobot] = 'V';         
        delay(2000); 
        Forward(); 
        // Showing the Movement of the Robot after turning: 
        SolvedMaze[rowrobot][columnrobot] = 'X';         
        SolvedMaze[rowrobot+1][columnrobot] = 'X';         
        rowrobot = rowrobot+2; 
        SolvedMaze[rowrobot][columnrobot] = 'V'; 
      } 
      digitalWrite(LEDPin, HIGH);       // Turn LED on to indicate that data is being transmitted       
      SolvedMap();                      // Call the solved map Function       
      digitalWrite(LEDPin, LOW);        // Turn LED off to indicate that data is transmitted       
      delay(5000); 
    } 
     
    // Current Direction //     
    else if (rightscan > MinimumSafeDistance) 
    { 
      Direction = 'R'; 
      Serial.print("Direction: "); 
      Serial.println(Direction); 
      Right(); 
      Serial1.write(Direction); 
      Forward(); 
      // Showing the Movement of the Robot: 
      SolvedMaze[rowrobot][columnrobot] = 'X'; 
      SolvedMaze[rowrobot][columnrobot+1] = 'X';       
      SolvedMaze[rowrobot][columnrobot+2] = 'X';       
      columnrobot = columnrobot+3; 
      SolvedMaze[rowrobot][columnrobot] = '>';       // Printing the Movement:       
      digitalWrite(LEDPin, HIGH);       // Turn LED on to indicate that data is being transmitted       
      SolvedMap();                      // Call the solved map Function       
      digitalWrite(LEDPin, LOW);        // Turn LED off to indicate that data is transmitted       
      delay(3000);        
      
      // Scanning the Perimeter // 
      // Scan Left //        
      servo.write(180);                      // Rotating the servo to 180 degrees        
      delay(2000);                           // Adding Delay to extend the durtation for the servo motor to be at an angle of 180 degrees        
      leftscan = Sensor();                   // Using the Sensor function to detect if there is wall or not 
      leftscan = inches;                     // Equating the distance to the leftscan variable 
      Serial.print("LeftScan: "); 
      Serial.println(leftscan); 
      // Scan Center // 
      servo.write(90);                       // Rotating the servo to 90 degrees        
      delay(2000);                           // Adding Delay to extend the durtation for the servo motor to be at an angle of 90 degrees        
      centerscan = Sensor();                 // Using the Sensor function to detect if there is wall or not 
      centerscan = inches;                   // Equating the distance to the centerscan variable 
      Serial.print("CenterScan: "); 
      Serial.println(centerscan); 
      // Scan Right //        
      servo.write(0);                        // Rotating the servo to 0 degrees        
      delay(2000);                           // Adding Delay to extend the durtation for the servo motor to be at an angle of 0 degrees        
      rightscan = Sensor();                  // Using the Sensor function to detect if there is wall or not 
      rightscan = inches;                    // Equating the distance to the rightscan variable 
      Serial.print("RightScan: "); 
      Serial.println(rightscan);        
      // Return To Center //        
      servo.write(90);                       // Rotating the servo to 90 degrees        
      delay(5000);                           // Adding Delay to extend the durtation for the servo motor to be at an angle of 90 degrees  
      // Turning the Robot: 
      Serial.print("Turning");       
      Serial.print("\n");       
      if (leftscan > MinimumSafeDistance) 
      { 
        Direction = 'F'; 
        Serial.print("Turning Direction:"); 
        Serial.print("\t"); 
        Right(); 
        // Showing the Movement of the Robot:         
        SolvedMaze[columnrobot][rowrobot] = '^';         
        delay(2000); 
        Forward(); 
        // Showing the Movement of the Robot after turning: 
        SolvedMaze[rowrobot][columnrobot] = 'X'; 
        SolvedMaze[rowrobot-1][columnrobot] = 'X'; 
        rowrobot = rowrobot-2; 
        SolvedMaze[rowrobot][columnrobot] = '^'; 
      } 
      else if (centerscan > MinimumSafeDistance) 
      { 
        Direction = 'R'; 
        Serial.print("Facing Forward"); 
        SolvedMaze[rowrobot][columnrobot] = '>';         
        delay(2000); 
        Forward(); 
        // Showing the Movement of the Robot after turning: 
        SolvedMaze[rowrobot][columnrobot] = 'X';         
        SolvedMaze[rowrobot][columnrobot+1] = 'X';         
        columnrobot = columnrobot+2; 
        SolvedMaze[rowrobot][columnrobot] = '>'; 
      } 
      else if (rightscan > MinimumSafeDistance) 
      { 
        Direction = 'B'; 
        Serial.print("Turning Direction:"); 
        Serial.print("\t"); 
        Left(); 
        // Showing the Movement of the Robot:         
        SolvedMaze[rowrobot][columnrobot] = 'v';         
        delay(2000); 
        Forward(); 
        // Showing the Movement of the Robot after turning: 
        SolvedMaze[rowrobot][columnrobot] = 'X';         
        SolvedMaze[rowrobot+1][columnrobot] = 'X';         
        rowrobot = rowrobot+2; 
        SolvedMaze[rowrobot][columnrobot] = 'V'; 
      }       
      else 
      { 
        Direction = 'L'; 
        Serial.print("Turning Direction:"); 
        Serial.print("\t"); 
        Right(); 
        SolvedMaze[columnrobot][rowrobot] = '^';         
        delay(2000); 
        Forward(); 
        // Showing the Movement of the Robot after turning: 
        SolvedMaze[rowrobot][columnrobot] = 'X';         
        SolvedMaze[rowrobot-1][columnrobot] = 'X';         
        rowrobot = rowrobot-2; 
        SolvedMaze[rowrobot][columnrobot] = '^'; 
      } 
      digitalWrite(LEDPin, HIGH);       // Turn LED on to indicate that data is being transmitted       
      SolvedMap();                      // Call the solved map Function       
      digitalWrite(LEDPin, LOW);        // Turn LED off to indicate that data is transmitted       
      delay(5000); 
    } 
 
    // Current Direction //     
    else 
    { 
      Direction = 'B'; 
      Serial.print("Direction: "); 
      Serial.println(Direction); 
      Backward(); 
      Serial1.write(Direction); 
      // Showing the Movement of the Robot: 
      SolvedMaze[rowrobot][columnrobot] = '*';       
      SolvedMaze[rowrobot+1][columnrobot] = '*';       
      rowrobot = rowrobot+2; 
      SolvedMaze[rowrobot][columnrobot] = 'v';       // Printing the Movement:       
      digitalWrite(LEDPin, HIGH);       // Turn LED on to indicate that data is being transmitted       
      SolvedMap();                      // Call the solved map Function       
      digitalWrite(LEDPin, LOW);        // Turn LED off to indicate that data is transmitted       
      delay(3000); 
      // Turning the Robot: 
      Serial.print("Turning");       
      Serial.print("\n");       
      if (leftscan > MinimumSafeDistance) 
      { 
        Direction = 'L'; 
        Serial.print("Turning Direction:"); 
        Serial.print("\t"); 
        Left(); 
        // Showing the Movement of the Robot: 
        SolvedMaze[rowrobot][columnrobot] = '>'; 
      } 
      else if (centerscan > MinimumSafeDistance) 
      { 
        Direction = 'F'; 
        Serial.print("Moving Forward"); 
        Serial.print("\n"); 
        SolvedMaze[rowrobot][columnrobot] = 'V'; 
      } 
      else if (rightscan > MinimumSafeDistance) 
      { 
        Direction = 'R'; 
        Serial.print("Turning Direction:"); 
        Serial.print("\t"); 
        Left(); 
        // Showing the Movement of the Robot: 
        SolvedMaze[rowrobot][columnrobot] = '<'; 
      }       else 
      { 
        Direction = 'L'; 
        Serial.print("Turning Direction:"); 
        Serial.print("\t"); 
        Right(); 
        SolvedMaze[columnrobot][rowrobot] = '>'; 
      } 
    } 
    Movement++; 
    digitalWrite(LEDPin, HIGH);       // Turn LED on to indicate that data is being transmitted     
    SolvedMap();                      // Call the solved map Function     
    digitalWrite(LEDPin, LOW);        // Turn LED off to indicate that data is transmitted     
    delay(5000); 
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
 
// PING Sensor Function // 
int Sensor() 
{ 
  pinMode(pingPin, OUTPUT);          
  // Set pin to OUTPUT   
  digitalWrite(pingPin, LOW);        
  // Ensure pin is low   
  delayMicroseconds(2);   
  digitalWrite(pingPin, HIGH);       // Start ranging   
  delayMicroseconds(5);              // with 5 microsecond burst   
  digitalWrite(pingPin, LOW);        // End ranging   
  pinMode(pingPin, INPUT);           // Set pin to INPUT   
  duration = pulseIn(pingPin, HIGH); // Read echo pulse   
  inches = duration / 74 / 2;        // Convert to inches   
  delay(25);                         // Short delay 
} 
 
// Conversion Function // 
long microsecondsToInches(long microseconds)  
{ 
  // According to Parallax's datasheet for the PING))), there are 
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per 
  // second).  This gives the distance travelled by the ping, outbound   
  // and return, so we divide by 2 to get the distance of the obstacle.   
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf   
  return microseconds / 74 / 2; 
} 

long microsecondsToCentimeters(long microseconds)  
{ 
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.   
  // The ping travels out and back, so to find the distance of the   
  // object we take half of the distance travelled.   
  return microseconds / 29 / 2; 
} 
