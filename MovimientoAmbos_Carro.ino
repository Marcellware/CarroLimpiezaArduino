#include <SoftwareSerial.h>

/*ALGOBACK YOUTUBE CHANNEL*/
/*CODIGO PARA CARRO QUE EVITA OBSTACULOS */

#include <Servo.h>
#include <NewPing.h>
#include <AFMotor.h>

NewPing Dist(A4, A5, 200); //(trig,echo,dist max)
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
  Serial.begin(9600);

  Motor1.setSpeed(200);  //Velocidad estándar de 250, máxima velocidad posible 255
  Motor2.setSpeed(200);
  Motor3.setSpeed(200);
  Motor4.setSpeed(200);

  myServo.attach(10); // establecer el servomotor
  //  myServo.write(0);
  //  delay(5000);
  //  myServo.write(180);
  //  delay(10000);
  //
  myServo.write(80);
}

void loop() {
Automatic:
  while (true) {
    if (Serial.available() > 0)
      command = Serial.read();
    if (command == 'M')
      goto Manual;

    distancia = medirDistancia();
    if (distancia >= 25 && distancia <= 250)
    {
      Adelante();
    }
    else if (distancia < 25 || contador == medirDistancia())
    {
      Frenar();
      delay(150);
      Reversa();
      delay(250);
      Frenar();
      delay(250);

      distanciaD = mirarDerecha();
      delay(250);

      distanciaIz = mirarIzquierda();
      delay(250);

      if (distanciaD >= distanciaIz)
      {
        GirarDerecha();
        Frenar();
      }
      else if (distanciaIz >= distanciaD)
      {
        GirarIzquierda();
        Frenar();
      }
    }
  }

Manual:
  //  if (Serial.available() > 0) {   // **** PARA MODO MANUAL
  //    //initialize with motors stoped
  //    command = Serial.read();

  while (true) {
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
        case 'A':
          goto Automatic;
          break;
      }
    }
  }
}

int mirarDerecha()
{
  myServo.write(10);
  delay(350);
  int distancia = medirDistancia();
  return distancia;
}

int mirarIzquierda()
{
  myServo.write(150);
  delay(350);
  int distancia = medirDistancia();
  delay(50);
  myServo.write(80);
  return distancia;
}

int medirDistancia()
{
  delay(10);
  int distanciaCM = Dist.ping_cm();
  if (distanciaCM <= 0 || distanciaCM >= 250)
  {
    distanciaCM = 250;
  }
  contador = distanciaCM;
  return distanciaCM;
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

void controlVelocidad() {
  for (int velocidad = 0; velocidad < 160; velocidad += 2)
  {
    Motor1.setSpeed(velocidad);
    Motor2.setSpeed(velocidad);
    Motor3.setSpeed(velocidad);
    Motor4.setSpeed(velocidad);
    delay(3);
  }
}
