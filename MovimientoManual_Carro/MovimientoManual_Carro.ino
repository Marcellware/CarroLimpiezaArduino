#include <SoftwareSerial.h>
#include <Servo.h>
#include <NewPing.h>
#include <AFMotor.h>

Servo myServo;

int distancia = 0;
int distanciaD = 0;
int distanciaIz = 0;
boolean Booleano = true;

int contador;
char command;

AF_DCMotor Motor1(1);
AF_DCMotor Motor2(2);
AF_DCMotor Motor3(3);
AF_DCMotor Motor4(4);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    Frenar(); //initialize with motors stoped
    command = Serial.read();

    switch (command) {
      case 'F':
        //        forward();
        Adelante();
        break;
      case 'B':
        //        back();
        Reversa();
        break;
      case 'L':
        //        left();
        GirarIzquierda();
        break;
      case 'R':
        //        right();
        GirarDerecha();
        break;
    }
  }
}

void Frenar() {
  Motor1.run(RELEASE);
  Motor2.run(RELEASE);
  Motor3.run(RELEASE);
  Motor4.run(RELEASE);
}

void Adelante() {
  if (Booleano == false)
  {
    Booleano = true;
    Motor1.run(FORWARD);
    Motor2.run(FORWARD);
    Motor3.run(FORWARD);
    Motor4.run(FORWARD);
    // controlVelocidad();
  }
}

void Reversa() {
  Booleano = false;
  Motor1.run(BACKWARD);
  Motor2.run(BACKWARD);
  Motor3.run(BACKWARD);
  Motor4.run(BACKWARD);
  // controlVelocidad();
}

void GirarDerecha() {
  Motor1.run(FORWARD);
  Motor1.run(FORWARD);

  Motor2.run(FORWARD);
  Motor2.run(FORWARD);


  Motor3.run(BACKWARD);
  Motor3.run(BACKWARD);

  Motor4.run(BACKWARD);
  Motor4.run(BACKWARD);
  delay(400);
}

void GirarIzquierda() {
  Motor1.run(BACKWARD);
  Motor1.run(BACKWARD);

  Motor2.run(BACKWARD);
  Motor2.run(BACKWARD);


  Motor3.run(FORWARD);
  Motor3.run(FORWARD);

  Motor4.run(FORWARD);
  Motor4.run(FORWARD);
  delay(400);
}
