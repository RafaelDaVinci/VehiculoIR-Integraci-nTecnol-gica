// Librería para recibir señales IR
#include <IRremote.hpp>

// Códigos HEX del control remoto
#define Power     0xFD00FF 
#define Derecha   0xFD609F
#define Izquierda 0xFD20DF
#define Centro    0xFD10EF

// Librería para controlar el servomotor
#include <Servo.h>

// Pin donde está conectado el sensor IR
#define IR_RECEIVE_PIN 5 

// Configuración de los pines y el servo
Servo servoA;
int pinServo = 10;
int Adelante = 7;
int anguloServoInicial = 90;

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  pinMode(Adelante, OUTPUT);
  pinMode(pinServo, OUTPUT);
  servoA.attach(pinServo);
  servoA.write(anguloServoInicial);
  delay(200);
}

void loop() {
  if (IrReceiver.decode()){
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);

    if (IrReceiver.decodedIRData.decodedRawData == Power) {
      // Invierte el estado del motor (ON→OFF o OFF→ON)
      digitalWrite(Adelante, !digitalRead(Adelante));
    }
    
    if (IrReceiver.decodedIRData.decodedRawData == Derecha) {
      // Gira el servo 45° hacia la derecha
      servoA.write(45);
    }
    if (IrReceiver.decodedIRData.decodedRawData == Izquierda) {
      // Gira el servo 45° hacia la izquierda 
      servoA.write(135);
    }
    if (IrReceiver.decodedIRData.decodedRawData == Centro) {
      // Reinicia el servo asi queda recto
      servoA.write(90);
    }
    IrReceiver.resume();
  }
  delay(100);
}