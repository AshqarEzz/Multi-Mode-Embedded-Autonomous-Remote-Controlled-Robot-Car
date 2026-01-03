#include <Servo.h>
#include <NewPing.h>
#include <IRremote.h>
#include <SoftwareSerial.h>

// ================== PINS ==================
// Motors
const int LF = 7;
const int LB = 6;
const int RF = 5;
const int RB = 4;

// Ultrasonic
#define TRIG A1
#define ECHO A2
#define MAX_DIST 200

// IR
#define IR_PIN 11

// Bluetooth
SoftwareSerial bt(2, 3); // RX, TX

// Servo
Servo servo;

// ================== IR CODES ==================
#define IR_UP     0xE718FF00
#define IR_DOWN   0xAD52FF00
#define IR_LEFT   0xF708FF00
#define IR_RIGHT  0xA55AFF00
#define IR_OK     0xE31CFF00
#define IR_HASH   0xF20DFF00   // IR MODE
#define IR_STAR   0xE916FF00   // AUTO MODE

// ================== OBJECTS ==================
NewPing sonar(TRIG, ECHO, MAX_DIST);

// ================== MODES ==================
enum Mode { AUTO, IR_MODE, BT_MODE };
Mode currentMode = AUTO;

// ================== SETUP ==================
void setup() {
  pinMode(LF, OUTPUT);
  pinMode(LB, OUTPUT);
  pinMode(RF, OUTPUT);
  pinMode(RB, OUTPUT);

  servo.attach(9);
  servo.write(115);

  Serial.begin(9600);
  bt.begin(9600);
  IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);
}

// ================== LOOP ==================
void loop() {

  // -------- BLUETOOTH --------
  if (bt.available()) {
    char c = bt.read();

    if (c == 'A') currentMode = AUTO;
    else if (c == 'I') currentMode = IR_MODE;
    else if (c == 'M') currentMode = BT_MODE;

    if (currentMode == BT_MODE) {
      if (c == 'F') moveForward();
      else if (c == 'B') moveBackward();
      else if (c == 'L') turnLeft();
      else if (c == 'R') turnRight();
      else if (c == 'S') moveStop();
    }
  }

  // -------- IR --------
  if (IrReceiver.decode()) {
    unsigned long code = IrReceiver.decodedIRData.decodedRawData;

    if (code == IR_STAR) currentMode = AUTO;
    if (code == IR_HASH) currentMode = IR_MODE;
    if (code == IR_OK) moveStop();

    if (currentMode == IR_MODE) {
      if (code == IR_UP) moveForward();
      else if (code == IR_DOWN) moveBackward();
      else if (code == IR_LEFT) turnLeft();
      else if (code == IR_RIGHT) turnRight();
    }
    IrReceiver.resume();
  }

  // -------- AUTO --------
  if (currentMode == AUTO) autonomous();
}

// ================== AUTO MODE ==================
void autonomous() {
  int d = readPing();

  if (d <= 45) {
    moveStop();
    delay(200);
    moveBackward();
    delay(300);
    moveStop();

    int right = lookRight();
    int left = lookLeft();

    if (right > left) turnRight();
    else turnLeft();
  } else {
    moveForward();
  }
}

// ================== ULTRASONIC ==================
int lookRight() {
  servo.write(50);
  delay(400);
  int d = readPing();
  servo.write(115);
  return d;
}

int lookLeft() {
  servo.write(170);
  delay(400);
  int d = readPing();
  servo.write(115);
  return d;
}

int readPing() {
  delay(70);
  int cm = sonar.ping_cm();
  if (cm == 0) cm = 250;
  return cm;
}

// ================== MOTORS ==================
void moveForward() {
  digitalWrite(LF, HIGH); digitalWrite(RF, HIGH);
  digitalWrite(LB, LOW);  digitalWrite(RB, LOW);
}

void moveBackward() {
  digitalWrite(LB, HIGH); digitalWrite(RB, HIGH);
  digitalWrite(LF, LOW);  digitalWrite(RF, LOW);
}

void turnLeft() {
  digitalWrite(LB, HIGH); digitalWrite(RF, HIGH);
  digitalWrite(LF, LOW);  digitalWrite(RB, LOW);
  delay(600);
}

void turnRight() {
  digitalWrite(LF, HIGH); digitalWrite(RB, HIGH);
  digitalWrite(LB, LOW);  digitalWrite(RF, LOW);
  delay(600);
}

void moveStop() {
  digitalWrite(LF, LOW); digitalWrite(RF, LOW);
  digitalWrite(LB, LOW); digitalWrite(RB, LOW);
}
