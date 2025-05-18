#include <AccelStepper.h>

#define MOTOR_PIN_1 2
#define MOTOR_PIN_2 3
#define MOTOR_PIN_3 4
#define MOTOR_PIN_4 5

const float STEPS_PER_REVOLUTION = 1600.0; // Resolução com microstepping de 8x
const float DEGREES_PER_OUTPUT_REVOLUTION = 36.0;

AccelStepper stepper(AccelStepper::FULL4WIRE, MOTOR_PIN_1, MOTOR_PIN_3, MOTOR_PIN_2, MOTOR_PIN_4);

void setup() {
  stepper.setMaxSpeed(2000.0);  
  stepper.setAcceleration(1000.0);  
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    int command = Serial.parseInt(); // Lê o número digitado
    
    switch (command) {
      case 1:
        moveDegrees(1);
        break;
      case 2:
        moveDegrees(-1);
        break;
      case 3:
        Serial.println("Digite a quantidade de graus a avançar:");
        while (!Serial.available()) {
          // Aguarda entrada da quantidade de graus
        }
        int numDegrees = Serial.parseInt(); // Lê o número de graus a mover
        moveDegrees(numDegrees);
        break;
      default:
        break;
    }
    // Limpa o buffer da porta serial
    while (Serial.available() > 0) {
      char _ = Serial.read();
    }
  }
}

void moveDegrees(int degrees) {
  float targetPosition = stepper.currentPosition() + (STEPS_PER_REVOLUTION / DEGREES_PER_OUTPUT_REVOLUTION) * degrees;
  stepper.moveTo(targetPosition);
  
  while (stepper.isRunning()) {
    stepper.run();
  }
}
