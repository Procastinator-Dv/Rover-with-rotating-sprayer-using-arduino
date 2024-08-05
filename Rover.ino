#include <SoftwareSerial.h>
#include <Servo.h>

Servo myservo;

// Pin Definitions
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 10
#define RELAY1 11
#define RELAY2 12
#define SERVO_PIN 6

char command;

void setup() {

  // Set pin modes
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  
  // Attach servo
  myservo.attach(SERVO_PIN);
  
  // Start serial communication
  Serial.begin(9600);

  // Initialize relay states
  digitalWrite(RELAY1, HIGH); // Ensure relay is initially off
  digitalWrite(RELAY2, HIGH); // Ensure relay is initially off
  
  // Debugging output
  Serial.println("Setup complete.");
}

void loop() {
    if (Serial.available() > 0) {
    command = Serial.read();
    executeCommand(command);
  }
}

void executeCommand(char command) {
  Serial.print("Received command: ");
  Serial.println(command);
  
  switch (command) {
    case 'F':
      moveForward();
      break;
    case 'B':
      moveBackward();
      break;
    case 'L':
      turnLeft();
      break;
    case 'R':
      turnRight();
      break;
    case 'N':
      stopMotors();
      break;
    case 'M':
      toggleServo();
      break;
    case 'P':
      digitalWrite(RELAY1, LOW);
      Serial.println("LED ON");
      break;
    case 'I':
      digitalWrite(RELAY1, HIGH);
      Serial.println("LED OFF");
      break;
    case 'S':
      digitalWrite(RELAY2, LOW);
      Serial.println("PUMP ON");
      break;
    case 'O':
      digitalWrite(RELAY2, HIGH);
      Serial.println("PUMP OFF");
      break;
    default:
      break;
  }
}

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void moveBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void toggleServo(){
  for(int pos=15; pos<=165; pos++){  
      myservo.write(pos);
      delay(5);
    }      
  for (int pos = 165; pos>15; pos-- ){
      myservo.write(pos);
      delay(5);
    }
}