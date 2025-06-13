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
int sp = 70;
long durationl, durationc, durationr;
long lcm = 0, ccm = 0, rcm = 0;

void setup() {
  Serial.begin(9600);

  pinMode(trigPinl, OUTPUT);
  pinMode(echoPinl, INPUT);
  pinMode(trigPinc, OUTPUT);
  pinMode(echoPinc, INPUT);
  pinMode(trigPinr, OUTPUT);
  pinMode(echoPinr, INPUT);

  // Motor driver pins setup
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void loop() {
  digitalWrite(trigPinl, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPinl, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinl, LOW);

  durationl = pulseIn(echoPinl, HIGH);
  lcm = (durationl / 2) / 29.1;

  digitalWrite(trigPinc, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPinc, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinc, LOW);

  durationc = pulseIn(echoPinc, HIGH);
  ccm = (durationc / 2) / 29.1;

  digitalWrite(trigPinr, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPinr, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinr, LOW);

  durationr = pulseIn(echoPinr, HIGH);
  rcm = (durationr / 2) / 29.1;

  if (lcm >= 15 && rcm >= 15 && ccm >= 10) {
    moveForward();
  }
  else if (lcm >= 15 && rcm <= 15 && ccm >= 10) {
    turnRight();
  }
  else if (lcm <= 15 && rcm >= 15 && ccm >= 10) {
    turnRight();
  }
  else if (lcm >= 15 && rcm >= 15 && ccm <= 10) {
    if (lcm < rcm) {
      turnRight();
      delay(500);
      moveForward();
      }
    else {
      turnLeft();
      delay(500);
      moveForward();
    }
  }
  else if (lcm <= 15 && rcm >= 15 && ccm <= 10) {
    stopBot();
    delay(500);
    turnRight();
    delay(1500);
  }
  else if (lcm >= 15 && rcm <= 15 && ccm <= 10) {
    stopBot();
    delay(500);
    turnLeft();
    delay(1500);
  }
  else if (lcm <= 15 && rcm <= 15 && ccm >= 10) {
    if (lcm < rcm) {
      turnRight();
      delay(500);
      moveForward();
      }
    else {
      turnLeft();
      delay(500);
      moveForward();
    }
  }
  else {
    moveForward();
  }
}

void moveForward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, sp);
  analogWrite(enB, sp);
}
void turnLeft() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, sp);
  analogWrite(enB, sp);
}
void turnRight() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA, sp);
  analogWrite(enB, sp);
}
void stopBot() {
  digitalWrite(in1, LOW);  
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);  
  digitalWrite(in4, LOW);
  analogWrite(enA, 0);
  analogWrite(enB, 0);
}
