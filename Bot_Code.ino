int trigPinl = 8;
int echoPinl = 9;
int trigPinc = 10;
int echoPinc = 11;
int trigPinr = 12;
int echoPinr = 13;

int enA = 3;
int in1 = 2;
int in2 = 4;

int enB = 6;
int in3 = 5;
int in4 = 7;

long durationl, durationc, durationr;
float lcm, ccm, rcm;

int baseSpeed = 100;

// PID constants
float Kp = 5.0;
float Ki = 0.01;
float Kd = 2.0;

float error = 0;
float previousError = 0;
float integral = 0;

void setup() {
  Serial.begin(9600);

  pinMode(trigPinl, OUTPUT);
  pinMode(echoPinl, INPUT);

  pinMode(trigPinc, OUTPUT);
  pinMode(echoPinc, INPUT);

  pinMode(trigPinr, OUTPUT);
  pinMode(echoPinr, INPUT);

  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  moveForward();
}

void loop() {

  lcm = getDistance(trigPinl, echoPinl);
  ccm = getDistance(trigPinc, echoPinc);
  rcm = getDistance(trigPinr, echoPinr);

  Serial.print("L=");
  Serial.print(lcm);
  Serial.print(" C=");
  Serial.print(ccm);
  Serial.print(" R=");
  Serial.println(rcm);

  // Obstacle directly ahead
  if (ccm < 15) {

    stopBot();
    delay(200);

    if (lcm > rcm) {
      rotateLeft();
    } else {
      rotateRight();
    }

    delay(400);
    return;
  }

  // PID wall following
  error = lcm - rcm;

  integral += error;

  float derivative = error - previousError;

  float pidOutput =
      Kp * error +
      Ki * integral +
      Kd * derivative;

  previousError = error;

  int leftMotorSpeed  = baseSpeed - pidOutput;
  int rightMotorSpeed = baseSpeed + pidOutput;

  leftMotorSpeed = constrain(leftMotorSpeed, 0, 255);
  rightMotorSpeed = constrain(rightMotorSpeed, 0, 255);

  setMotorSpeed(leftMotorSpeed, rightMotorSpeed);

  delay(50);
}

float getDistance(int trigPin, int echoPin) {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);

  return (duration * 0.0343) / 2.0;
}

void moveForward() {

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void setMotorSpeed(int leftSpeed, int rightSpeed) {

  moveForward();

  analogWrite(enA, leftSpeed);
  analogWrite(enB, rightSpeed);
}

void rotateLeft() {

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  analogWrite(enA, 120);
  analogWrite(enB, 120);
}

void rotateRight() {

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  analogWrite(enA, 120);
  analogWrite(enB, 120);
}

void stopBot() {

  analogWrite(enA, 0);
  analogWrite(enB, 0);

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
