

#include<AFMotor.h>
#include <SoftwareSerial.h>


//note: The delays in this program can be edited to suit your requirement for turning times


int isObstaclePin1 = 22;
int isObstaclePin2 = 23;
int isObstacle1 = HIGH;
int isObstacle2 = HIGH;// HIGH MEANS NO OBSTACLE
const int ustrigPin = 24;
const int usechoPin = 25;
long duration;
int distance;
int analogPin = 8;
int readValue = 0;
float temperature = 0;
float temperatureF = 0;



AF_DCMotor motor1(4, MOTOR12_64KHZ);
AF_DCMotor motor2(2, MOTOR12_64KHZ);
AF_DCMotor motor3(1, MOTOR12_64KHZ);
AF_DCMotor motor4(3, MOTOR12_64KHZ);

SoftwareSerial BTSerial(0,1); // RX | TX
char INBYTE;
char BTBYTE;
int  LED = 13; // LED on pin 13
int state;
void setup() {
  pinMode(ustrigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(usechoPin, INPUT); // Sets the echoPin as an Input
  state =1;
  pinMode(LED, OUTPUT);
  pinMode(isObstaclePin1, INPUT);
  pinMode(isObstaclePin2, INPUT);
  
  motor1.setSpeed(255);
  motor2.setSpeed(255);
  motor3.setSpeed(255);
  motor4.setSpeed(255); 
  Serial.begin(9600);
  BTSerial.begin(2400); 
  pinMode(LED, OUTPUT);
  BTSerial.println("Hello World");
  Serial.println("Im alive!");
  Serial.println("Press 1 to turn Arduino pin 13 LED ON or 0 to turn it OFF:");
  BTSerial.println("Press 1 to turn Arduino pin 13 LED ON or 0 to turn it OFF:");
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void maketurn1()
{
   motor1.run(FORWARD);
   motor2.run(BACKWARD);
   motor3.run(BACKWARD);
   motor4.run(FORWARD);
   delay(2900);
   motor2.run(FORWARD);
   motor3.run(FORWARD);
   delay(2000);
   motor1.run(BACKWARD);
   motor2.run(FORWARD);
   motor3.run(FORWARD);
   motor4.run(BACKWARD);
   delay(2900);
   
}


void maketurn2()
{
   motor1.run(BACKWARD);
   motor2.run(FORWARD);
   motor3.run(FORWARD);
   motor4.run(BACKWARD);
   delay(2000);
   motor1.run(FORWARD);
   motor2.run(FORWARD);
   delay(2000);
   motor1.run(FORWARD);
   motor2.run(BACKWARD);
   motor3.run(BACKWARD);
   motor4.run(FORWARD);
   delay(2000);
   
}

void loop() {
                
                

                if (BTSerial.available())
                {
                  BTBYTE = BTSerial.read();
                  Serial.println(BTBYTE);  //There is some issue with this on Arduino IDE, use tera term for both BT and normal serial.
                }    
                if (Serial.available())
                {
                   INBYTE = Serial.read();
                   BTSerial.println(INBYTE);
                }
 
 /* if((INBYTE == '0' || BTBYTE == '0'))
  {
    digitalWrite(LED, LOW) ;
    
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor3.run(RELEASE);
    motor4.run(RELEASE);  
  }
  
  if((INBYTE == '1' || BTBYTE == '1'))
  {
    digitalWrite(LED, HIGH); 
    
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);  
  
  
  }
  */


  if(INBYTE=='1' && state ==1)
  {
       motor1.run(FORWARD);
       motor2.run(FORWARD);
       motor3.run(FORWARD);
       motor4.run(FORWARD);
       delay(90000);
       motor1.run(FORWARD);
       motor2.run(BACKWARD);
       motor3.run(BACKWARD);
       motor4.run(FORWARD);
       delay(5800);
       motor1.run(FORWARD);
       motor2.run(FORWARD);
       motor3.run(FORWARD);
       motor4.run(FORWARD);
       delay(90000);
       motor1.run(BACKWARD);
       motor2.run(FORWARD);
       motor3.run(FORWARD);
       motor4.run(BACKWARD);
       delay(2900);
       motor1.run(FORWARD);
       motor2.run(FORWARD);
       motor3.run(FORWARD);
       motor4.run(FORWARD);
       delay(4000);
       motor1.run(BACKWARD);
       motor2.run(FORWARD);
       motor3.run(FORWARD);
       motor4.run(BACKWARD);
       state = 2;
       
  }
  delay(50);
 if(INBYTE=='2')
 {
  
  isObstacle1 = digitalRead(isObstaclePin1);
  isObstacle2 = digitalRead(isObstaclePin2);
  digitalWrite(ustrigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(ustrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(ustrigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(usechoPin, HIGH);
  // Calculating the distance
  distance= duration*0.034/2;
  // Prints the distance on the Serial Monitor
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  if(distance <30)
  {
    Serial.println("OBSTACLE!!, OBSTACLE!!");
    digitalWrite(LED, HIGH);
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor3.run(RELEASE);
    motor4.run(RELEASE);
    delay(2000);
    maketurn1();
    
    
  }
  /*
 else if (isObstacle1 == LOW && isObstacle2 == HIGH)
  {
    Serial.println("OBSTACLE!!, OBSTACLE!!");
    digitalWrite(LED, HIGH);
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor3.run(RELEASE);
    motor4.run(RELEASE);
    delay(2000);
    maketurn1();
    
  }
  else if(isObstacle1 == HIGH && isObstacle2 == LOW)
  {
    
    Serial.println("OBSTACLE!!, OBSTACLE!!");
    digitalWrite(LED, HIGH);
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor3.run(RELEASE);
    motor4.run(RELEASE);
    delay(2000);
    maketurn2();
  }

  else if
  (isObstacle1 == LOW && isObstacle2 == LOW)
  {
     
    Serial.println("OBSTACLE!!, OBSTACLE!!");
    digitalWrite(LED, HIGH);
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor3.run(RELEASE);
    motor4.run(RELEASE);
    delay(2000);
    maketurn1();
    
  }*/
  
 }
 if(INBYTE=='3')
 {
  isObstacle1 = digitalRead(isObstaclePin1);
  isObstacle2 = digitalRead(isObstaclePin2);
  digitalWrite(ustrigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(ustrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(ustrigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(usechoPin, HIGH);
  // Calculating the distance
  distance= duration*0.034/2;
  // Prints the distance on the Serial Monitor
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  if(distance <12)
  {
    Serial.println("OBSTACLE!!, OBSTACLE!!");
    digitalWrite(LED, HIGH);
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor3.run(RELEASE);
    motor4.run(RELEASE);
    delay(2000);
    maketurn1();
    
    
  }
 else if (isObstacle1 == LOW && isObstacle2 == HIGH)
  {
    Serial.println("OBSTACLE!!, OBSTACLE!!");
    digitalWrite(LED, HIGH);
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor3.run(RELEASE);
    motor4.run(RELEASE);
    delay(2000);
    maketurn1();
    
  }
  else if(isObstacle1 == HIGH && isObstacle2 == LOW)
  {
    
    Serial.println("OBSTACLE!!, OBSTACLE!!");
    digitalWrite(LED, HIGH);
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor3.run(RELEASE);
    motor4.run(RELEASE);
    delay(2000);
    maketurn2();
  }

  else if
  (isObstacle1 == LOW && isObstacle2 == LOW)
  {
     
    Serial.println("OBSTACLE!!, OBSTACLE!!");
    digitalWrite(LED, HIGH);
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor3.run(RELEASE);
    motor4.run(RELEASE);
    delay(2000);
    maketurn1();
    
  }
       
 }
 if(INBYTE == '4')
 {
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(BACKWARD);
  delay(2900);
  motor1.run(FORWARD);
  motor4.run(FORWARD);
  delay(2000);
  motor1.run(BACKWARD);
  motor4.run(BACKWARD);
  state = 5;
 }
 if(state == 5)
 {
  
 }

 if(INBYTE=='8')
 {
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(BACKWARD);
  delay(6000);
  INBYTE='2';
 }

 if(INBYTE=='9')
 {
  readValue = analogRead(analogPin);
//Serial.println(readValue);
temperature = (readValue * 0.0049);
temperature = temperature * 100;
temperatureF = (temperature * 1.8) + 32;
Serial.print("Temperature: ");
Serial.print(temperature);
Serial.print("C ");
Serial.print(temperatureF);
Serial.println("F");
delay(1000);
 }
}

