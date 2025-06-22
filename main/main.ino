#include <PS4Controller.h>
#include <ESP32Servo.h>

// Claw servo.
Servo myservo;

// Servo Capit
#define CLAW_FRONT 13
#define ARM_FRONT 14
#define CLAW_BACK 15
#define ARM_BACK 25

// Motor Kiri
#define PWM_LEFT 22
#define IN1_LEFT 5
#define IN2_LEFT 18

// Motor Kanan
#define PWM_RIGHT 23
#define IN1_RIGHT 19
#define IN2_RIGHT 21

// Input bindings.
#define ACCELERATE PS4.Cross()
#define BRAKE 0
#define REVERSE PS4.Triangle()
#define CLAW_CLOSE PS4.R2()
#define CLAW_OPEN PS4.L2()

// Other constants.
unsigned int motorSpeed = 100;

void setup() {
  Serial.begin(115200);

  // Might want to 
  PS4.begin();

  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  // myservo.setPeriodHertz(50);
  // myservo.attach(SERVO1, 500, 2400);  
  
  pinMode(PWM_LEFT, OUTPUT);
  pinMode(PWM_RIGHT, OUTPUT);
  pinMode(IN1_LEFT, OUTPUT);
  pinMode(IN2_LEFT, OUTPUT);
  pinMode(IN1_RIGHT, OUTPUT);
  pinMode(IN2_RIGHT, OUTPUT);

  Serial.println("PS4 controller Ready.");

  // Initial state.
  motorOff(IN1_LEFT, IN2_LEFT);
  motorOff(IN1_RIGHT, IN2_RIGHT);
}

void loop() {
  if (PS4.isConnected()) {

    // LstickY = map(LstickY, -127, 127, 0, 180);     // scale it to use it with the servo
    // Serial.println(LstickY);  //Print the angle to the Serial Monitor
    // myservo.write(LstickY);  //write the Lstickue to the servo
    // Serial.println(Cross);
    // Serial.println(Triangle);

    // TODO: Claw inputs.
    if (CLAW_CLOSE) {

    }
    else if (CLAW_OPEN) {

    }

    // Calculate motor speed based on mode.

    // Calculate motor speeds for turning from left stick.

    // It seems stick values range from -128 to 127, but this will need to be tested.
    int lx = PS4.LStickX();

    // Left stick should determine whether right or left motor is faster.
    // Full right would mean only left motor is working.
    // Full left would mean only right motor is working.
    // Everything else linearly interpolated.
    // Can be changed if not intuitive for players.
    int leftMotorSpeed = map(lx + 128, 0, 255, 0, motorSpeed);
    int rightMotorSpeed = map(127 - lx, 0, 255, 0, motorSpeed);

    analogWrite(PWM_LEFT, leftMotorSpeed);
    analogWrite(PWM_RIGHT, rightMotorSpeed);

    // Order determines priority of commands.
    if (BRAKE) {
      // Could do actual braking, but for now this will be fine.
      motorOff(IN1_LEFT, IN2_LEFT);
      motorOff(IN1_RIGHT, IN2_RIGHT);
    }
    if (REVERSE) {
      motorReverse(IN1_LEFT, IN2_LEFT);
      motorReverse(IN1_RIGHT, IN2_RIGHT);
    }
    else if (ACCELERATE) {
      motorForward(IN1_LEFT, IN2_LEFT);
      motorForward(IN1_RIGHT, IN2_RIGHT);
    }
    // Turn off if no input.
    else {
      motorOff(IN1_LEFT, IN2_LEFT);
      motorOff(IN1_RIGHT, IN2_RIGHT);
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

inline void motorOff(int pin1, int pin2) {
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, HIGH);
}

inline void motorForward(int pin1, int pin2) {
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, LOW);
}

inline void motorReverse(int pin1, int pin2) {
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, HIGH);
}

// Jangan sering dipakai, takut motor overheat.
inline void motorBrake(int pin1, int pin2) {
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, HIGH);
}

inline void clawClose() {

}