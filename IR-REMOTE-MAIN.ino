#include <Servo.h>
#include <NewPing.h>
#include <IRremote.h>

// ===== MOTOR PINS (L298N) =====
const int LeftMotorForward = 7;
const int LeftMotorBackward = 6;
const int RightMotorForward = 5;
const int RightMotorBackward = 4;

// ===== ULTRASONIC =====
#define trig_pin A1
#define echo_pin A2
#define maximum_distance 200

// ===== SERVO =====
Servo servo_motor;

// ===== IR =====
#define IR_PIN 11

// ===== IR CODES (YOUR REMOTE) =====
#define IR_UP     0xE718FF00
#define IR_DOWN   0xAD52FF00
#define IR_LEFT   0xF708FF00
#define IR_RIGHT  0xA55AFF00
#define IR_OK     0xE31CFF00
#define IR_HASH   0xF20DFF00   // MANUAL
#define IR_STAR   0xE916FF00   // AUTO

NewPing sonar(trig_pin, echo_pin, maximum_distance);

// ===== GLOBALS =====
bool manualMode = false;
int distance = 100;

// ================= SETUP =================
void setup() {
  Serial.begin(9600);

  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorForward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);

  servo_motor.attach(9);
  servo_motor.write(115);

  IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);
}

// ================= LOOP =================
void loop() {

  // ---- IR CHECK (ALWAYS ACTIVE) ----
  if (IrReceiver.decode()) {
    unsigned long code = IrReceiver.decodedIRData.decodedRawData;

    if (code == IR_HASH) manualMode = true;   // MANUAL
    if (code == IR_STAR) manualMode = false;  // AUTO
    if (code == IR_OK) moveStop();

    if (manualMode) handleIR(code);

    IrReceiver.resume();
  }

  // ---- AUTO MODE ----
  if (!manualMode) {
    obstacleAvoid();
  }
}

// ================= IR CONTROL =================
void handleIR(unsigned long code) {
  if (code == IR_UP) moveForward();
  else if (code == IR_DOWN) moveBackward();
  else if (code == IR_LEFT) turnLeft();
  else if (code == IR_RIGHT) turnRight();
}

// ================= AUTO MODE =================
void obstacleAvoid() {
  distance = readPing();

  if (distance <= 45) {
    moveStop();
    delay(200);
    moveBackward();
    delay(300);
    moveStop();

    int right = lookRight();
    int left  = lookLeft();

    if (right > left) turnRight();
    else turnLeft();
  } else {
    moveForward();
  }
}

// ================= ULTRASONIC =================
int lookRight() {
  servo_motor.write(50);
  delay(400);
  int d = readPing();
  servo_motor.write(115);
  return d;
}

int lookLeft() {
  servo_motor.write(170);
  delay(400);
  int d = readPing();
  servo_motor.write(115);
  return d;
}

int readPing() {
  delay(70);
  int cm = sonar.ping_cm();
  if (cm == 0) cm = 250;
  return cm;
}

// ================= MOTORS =================
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
  delay(600);
  
}

void turnRight() {
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW);
  delay(600);
  
}

void moveStop() {
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
}
