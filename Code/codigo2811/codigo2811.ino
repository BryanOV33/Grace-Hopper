#include <Servo.h>

// Pin del boton
const int Pin4 = 11;  // Botón de inicio para ambas bombas

// SERVO
int angulo = 0;
int pos;

// Pines de los relés que controlan las bombas
const int relayPin1 = 13;      // Relé de la bomba 1 (agua)
const int relayPin2 = 12;      // Relé de la bomba 2 (leche)

// Pin para el relé del motor DC
const int relayMotorPin = 10;  // Relé del motor DC

// Configuración del servomotor
Servo myServo;
const int servoPin = 9;        // Pin para el control del servo

int lastPin4 = HIGH;  // Estado previo del botón(HIGH debido al INPUT_PULLUP)

void setup() {
  // Configuración de los pines de entrada para los botones
  pinMode(Pin4, INPUT_PULLUP);

  // Configuración de los pines de salida para los relés
  pinMode(relayPin1, OUTPUT);
  pinMode(relayPin2, OUTPUT);
  pinMode(relayMotorPin, OUTPUT);

  // Configuración del servomotor
  myServo.attach(servoPin);

  // Asegura que las bombas y el motor estén apagados al iniciar
  digitalWrite(relayPin1, HIGH);  // Bombas apagadas
  digitalWrite(relayPin2, HIGH);  // Bombas apagadas
  digitalWrite(relayMotorPin, HIGH); // Motor apagado
  myServo.write(0);

  Serial.begin(9600);  // Iniciar comunicación serial
}

void loop() {
  int currentPin4 = digitalRead(Pin4);   // Leer el estado actual del botón
  if (currentPin4 == LOW && lastPin4 == HIGH) { // Detectar el cambio de estado del botón
    delay(1000);  // Pequeña espera para evitar rebotes

    Serial.println("Activando bombas...");

    Serial.println("Vertiendo Agua");    // Activar la bomba 1 (agua)
    digitalWrite(relayPin1, LOW);  // Enciende la bomba 1
    delay(25000);  // Tiempo de activación
    digitalWrite(relayPin1, HIGH); // Apaga la bomba 1
    delay(1000);

    Serial.println("Vertiendo Leche"); // Activar la bomba 2 (leche)
    digitalWrite(relayPin2, LOW);  // Enciende la bomba 2
    delay(4000);  // Tiempo de activación
    digitalWrite(relayPin2, HIGH); // Apaga la bomba 2
    delay(1000);

    Serial.println("Moviendo servo...");    // Control del servomotor
    for (pos = 0; pos <= 55; pos += 1) {
      myServo.write(pos);  // Mover servo a la posición 'pos'
      delay(15);
    }
    for (pos = 55; pos >= 0; pos -= 1) {
      myServo.write(pos);  // Mover servo a la posición inicial
      delay(15);
    }
    delay(1000);  // Esperar antes de activar el motor

    Serial.println("Activando motor DC por 3 segundos");// Activar el motor DC por 3 segundos
    digitalWrite(relayMotorPin, LOW);   // Enciende el motor
    delay(5000);  // El motor corre por 3 segundos
    digitalWrite(relayMotorPin, HIGH);  // Apaga el motor
    Serial.println("Motor DC apagado");
  }
  // Actualizar el estado previo del botón
  lastPin4 = currentPin4;
  delay(100);  // Pequeña espera para evitar lecturas repetidas del botón
}
