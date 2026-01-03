#include <IRremote.h>

// ===== IR =====
#define IR_PIN 11

// ===== MOTOR PINS (L298N) =====
const int LeftMotorForward = 7;
const int LeftMotorBackward = 6;
const int RightMotorForward = 5;
const int RightMotorBackward = 4;

// ===== IR CODES (YOUR REMOTE) =====
#define IR_UP     0xE718FF00
#define IR_DOWN   0xAD52FF00
#define IR_LEFT   0xF708FF00
#define IR_RIGHT  0xA55AFF00
#define IR_OK     0xE31CFF00

void setup() {
  Serial.begin(9600);

  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorForward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);

  IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);
}

void loop() {
  if (IrReceiver.decode()) {

    unsigned long code = IrReceiver.decodedIRData.decodedRawData;
    Serial.println(code, HEX);

    if (code == IR_UP) {
      moveForward();
    }
    else if (code == IR_DOWN) {
      moveBackward();
    }
    else if (code == IR_LEFT) {
      turnLeft();
    }
    else if (code == IR_RIGHT) {
      turnRight();
    }
    else if (code == IR_OK) {
      moveStop();
    }

    IrReceiver.resume();
  }
}

// ===== MOTOR FUNCTIONS =====
void moveForward() {
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
}

void moveBackward() {
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);
}

void turnLeft() {
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
}

void turnRight() {
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW);
}

void moveStop() {
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
}
