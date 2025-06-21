#include <PS4Controller.h>
#include <ESP32Servo.h>

Servo myservo;
int Lstick = 90;    // variable to read the Lstickue from the analog pin
int Rstick;    // variable to read the Lstickue from the analog pin
int Down;
int Right;
int Up;
int Left;
int Square;
int Cross;
int Circle;
int Triangle;
int L1;
int R1;
int L2;
int R2;

// Servo Capit
#define servo1 13;
#define servo2 14;
#define servo3 15;
#define servo4 25;

// Motor Kiri
#define ENA 22
#define IN1 5
#define IN2 18

// Motor Kanan
#define ENB 23
#define IN3 19
#define IN4 21

void setup() {
  Serial.begin(115200);
  PS4.begin();
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  myservo.setPeriodHertz(50);
  myservo.attach(servo1, 500, 2400);  
  
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.println("PS4 controller Ready.");
}

void loop() {
  if (PS4.isConnected()) {
    Lstick = PS4.LStickY();
    Rstick = PS4.RStickY();
    Down = PS4.Down();
    Right = PS4.Right();
    Up = PS4.Up();
    Left = PS4.Left();
    Square = PS4.Square();
    Cross = PS4.Cross();
    Circle = PS4.Circle();
    Triangle = PS4.Triangle();
    L1 = PS4.L1();
    R1 = PS4.R1();   
    L2 = PS4.L2();   
    R2 = PS4.R2();

    Lstick = map(Lstick, -127, 127, 0, 180);     // scale it to use it with the servo
    Serial.println(Lstick);  //Print the angle to the Serial Monitor
    myservo.write(Lstick);  //write the Lstickue to the servo
    Serial.println(Cross);
    Serial.println(Triangle);

    // ini masih coba coba
    if(Cross){
        Lstick = 180;
        myservo.write(180);
    }

    if(Triangle){
        Lstick = 0;
        myservo.write(0);
    }

    // Son, sabi dibuatin dl buat movement roda motornya dari source code ini:
    // Kalo bisa, sesuai aja ama controller setting kek game balapan. Misalnya R2 buat maju gitu gitu dsb
    /*
     if (Up) {  // Maju cepat
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      speed = 255;
      manual = true;
    } else if (Down) {  // Mundur cepat
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      speed = 255;
      manual = true;
    } else if (Left) {  // Putar kiri
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      speed = 200;
      manual = true;
    } else if (Right) {  // Putar kanan
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      speed = 200;
      manual = true;
    } else if (Square) {  // Rem darurat
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      speed = 0;
      manual = true;
    } else if (Triangle) {  // Full maju
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      speed = 255;
      manual = true;
    } else if (Cross) {  // Full mundur
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      speed = 255;
      manual = true;
    } else if (Circle) {  // Mode idle
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      speed = 0;
      manual = true;
    } else if (L1) {  // Hanya motor kiri maju
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      speed = 200;
      manual = true;
    } else if (R1) {  // Hanya motor kanan maju
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      speed = 200;
      manual = true;
    } else if (L2) {  // Hanya motor kiri mundur
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      speed = 200;
      manual = true;
    } else if (R2) {  // Hanya motor kanan mundur
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      speed = 200;
      manual = true;
    }

    if (!manual) {
      // Kontrol dari joystick (default)
      if (y < -5) { // Maju
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
      } else if (y > 5) { // Mundur
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
      } else if (x < -5) { // Belok kiri
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
      } else if (x > 5) { // Belok kanan
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
      } else {
        // Stop
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
        speed = 0;
      }
    }

    analogWrite(ENA, speed);  // PWM motor kiri
    analogWrite(ENB, speed);  // PWM motor kanan
    }
    */

    delay(10);
  }
}