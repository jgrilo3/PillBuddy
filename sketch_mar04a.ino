// Motor A connections, bottom left
int enA = 9;
int in1 = 8;
int in2 = 7;

// Motor B connections, top left
int enB = 3;
int in3 = 5;
int in4 = 4;

// Motor C, bottom right
int enC = 10;
int in5 = 11;
int in6 = 2;

// Motor D, top right
int enD = 6; 
int in7 = 12;
int in8 = 13;

String command;

void setup() {
  // Set all the motor control pins to outputs
  Serial.begin(9600);
  
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(in5, OUTPUT);
  pinMode(in6, OUTPUT);
  pinMode(in7, OUTPUT);
  pinMode(in8, OUTPUT);
  pinMode(0, OUTPUT);
  
  
  // Turn off motors - Initial state
  digitalWrite(1, LOW);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  digitalWrite(in5, LOW);
  digitalWrite(in6, LOW);
  digitalWrite(in7, LOW);
  digitalWrite(in8, LOW);
}

void loop() {
  //Serial.begin(9600);
  if (Serial.available()) {
    command = Serial.readStringUntil('\n');
    command.trim();
    if (command.equals("w")) {
      approach_person();
    }
    else if (command.equals("s")) {
       stop_all();
       digitalWrite(1, HIGH);
       delay(5000);
       exit(0);
    }
  }
  else {
    seek_person();
  }
}

void seek_person() {
  forward(100);
  delay(2000);
  stop_all();
  delay(1000);
  face_right(100);
  delay(1000);
  stop_all();
  delay(3000);
}

void approach_person() {

  forward(100);
  delay(2000);
  stop_all();
  delay(1000);
  
}

void stop_all() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  digitalWrite(in5, LOW);
  digitalWrite(in6, LOW);

  digitalWrite(in7, LOW);
  digitalWrite(in8, LOW);
}

void forward(int power) {
  analogWrite(enA, power);
  analogWrite(enB, power);
  analogWrite(enC, power);
  analogWrite(enD, power);

  // Turn on motor A & B
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  digitalWrite(in5, LOW);
  digitalWrite(in6, HIGH);

  digitalWrite(in7, LOW);
  digitalWrite(in8, HIGH);
}

void backward(int power) {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  digitalWrite(in5, HIGH);
  digitalWrite(in6, LOW);

  digitalWrite(in7, HIGH);
  digitalWrite(in8, LOW);
}

void face_right(int power) {
  analogWrite(enA, power);
  analogWrite(enB, power);
  analogWrite(enC, power);
  analogWrite(enD, power);
  
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  digitalWrite(in5, HIGH);
  digitalWrite(in6, LOW);

  digitalWrite(in7, HIGH);
  digitalWrite(in8, LOW);
}

void face_left(int power) {
  analogWrite(enA, power);
  analogWrite(enB, power);
  analogWrite(enC, power);
  analogWrite(enD, power);
  
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  digitalWrite(in5, LOW);
  digitalWrite(in6, HIGH);

  digitalWrite(in7, LOW);
  digitalWrite(in8, HIGH);
}
