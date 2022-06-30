#include <NewPing.h> 
#include <Servo.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F,20,4);
//servo 
Servo ourservo;

//sensor pins
#define maximum_distance 200
int dis_F,dis_R,dis_L; //distances
const int buzzer = 5; //buzzer to arduino pin 5
NewPing sonar(10, 7, 30);//sensor function Trig Echo
void setup(){
  pinMode(12, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 6 as an output
  ourservo.attach(6);
  Serial.begin(9600);
// initialiser LCD
  lcd.init();                      
  lcd.init();
  lcd.backlight();
}
void loop(){
   ourservo.write(20);
  dis_F = readPing();
  delay(100);
  Serial.println("Distance For :");
    Serial.println(dis_F);
  if (dis_F <= 20){
    moveStop();
    affi();
    br();
    
    ourservo.write(65);
    delay(20);
    dis_L = readPing();
    delay(100);
    Serial.println("Distance Left :");
    Serial.println(dis_L);
    delay(500);
    ourservo.write(-65);
    delay(20);
    dis_R = readPing();
    delay(100);
    Serial.println("Distance Right :");
    Serial.println(dis_R);
    delay(500);
    ourservo.write(20);
    delay(20);
    if(dis_L > dis_R){
      moveLeft();
      delay(1600);
      }else if(dis_L < dis_R){
          moveRight();
          delay(1600);
        }else{
            moveRight();
            delay(1600);
          }
  }
  else if (dis_F >20){
    moveForward();
    delay(30);
  }
  
}
//fonction de lecture de distance
int readPing(){
  delay(500);
  int cm;
  cm = sonar.ping_cm();
  if(cm==0){
      cm = 255;
    }
  return cm;
}
//fonction d'affichage en LCD
void affi(){
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("L'obstacle est");
  lcd.setCursor(3,1);
  lcd.print("a :");
  lcd.setCursor(9,1);
  lcd.print(dis_F);
  lcd.setCursor(12,1);
  lcd.print("cm");
  }
  
//fonction buzzer
void br(){
  digitalWrite(buzzer,HIGH);
  delay(800);
  digitalWrite(buzzer,LOW);
  delay(500);   
  digitalWrite(buzzer,HIGH);
  delay(500);
  digitalWrite(buzzer,LOW);
  delay(500);
  }

//fonctions do mobilisation
void moveStop(){
  digitalWrite(12, LOW);
  digitalWrite(9, HIGH);
  digitalWrite(13, LOW);
  digitalWrite(8, HIGH);
}

void moveForward(){
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);
  digitalWrite(9, LOW);
  digitalWrite(8, LOW);
  analogWrite(11, 230); //right
  analogWrite(3, 250);
}
void moveBackward(){
  digitalWrite(9, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  analogWrite(11, 127);
  analogWrite(3, 127);
}
void moveRight(){
  digitalWrite(12, LOW);  
  digitalWrite(9, LOW); 
  digitalWrite(13, HIGH); 
  digitalWrite(8, LOW);   
  analogWrite(11, 200);   
  analogWrite(3, 200);  
}
void moveLeft(){
  digitalWrite(12, HIGH);  
  digitalWrite(9, LOW); 
  digitalWrite(13, LOW); 
  digitalWrite(8, LOW);   
  analogWrite(11, 200);   
  analogWrite(3, 200);
}
