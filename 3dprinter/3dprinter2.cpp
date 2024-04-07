#include <Servo.h>
#include <math.h>

#define X_STEP_PIN          54
#define X_DIR_PIN           55
#define X_ENABLE_PIN        38
#define Y_STEP_PIN          60
#define Y_DIR_PIN           61
#define Y_ENABLE_PIN        56
#define Z_STEP_PIN          46
#define Z_DIR_PIN           48
#define Z_ENABLE_PIN        62
#define E_STEP_PIN          26
#define E_DIR_PIN           28
#define E_ENABLE_PIN        24

#define EXTRUDER_PIN        9

#define COMMAND_BUFFER_SIZE 64

char commandBuffer[COMMAND_BUFFER_SIZE];
int commandIndex = 0;

Servo extruderServo;

void setup() {
  Serial.begin(115200);

  pinMode(X_STEP_PIN, OUTPUT);
  pinMode(X_DIR_PIN, OUTPUT);
  pinMode(X_ENABLE_PIN, OUTPUT);
  pinMode(Y_STEP_PIN, OUTPUT);
  pinMode(Y_DIR_PIN, OUTPUT);
  pinMode(Y_ENABLE_PIN, OUTPUT);
  pinMode(Z_STEP_PIN, OUTPUT);
  pinMode(Z_DIR_PIN, OUTPUT);
  pinMode(Z_ENABLE_PIN, OUTPUT);
  pinMode(E_STEP_PIN, OUTPUT);
  pinMode(E_DIR_PIN, OUTPUT);
  pinMode(E_ENABLE_PIN, OUTPUT);

  extruderServo.attach(EXTRUDER_PIN);

  digitalWrite(X_ENABLE_PIN, LOW);
  digitalWrite(Y_ENABLE_PIN, LOW);
  digitalWrite(Z_ENABLE_PIN, LOW);
  digitalWrite(E_ENABLE_PIN, LOW);

  extruderServo.write(0);
}

void loop() {
  if (Serial.available() > 0) {
    char c = Serial.read();
    if (c == '\n' || c == '\r') {
      commandBuffer[commandIndex] = '\0';
      processCommand(commandBuffer);
      commandIndex = 0;
    } else {
      commandBuffer[commandIndex] = c;
      commandIndex++;
      if (commandIndex >= COMMAND_BUFFER_SIZE) {
        commandIndex = 0;
      }
    }
  }
}

void processCommand(char* command) {
  switch (command[0]) {
    case 'G':
      executeGCodeCommand(command);
      break;
    default:
      break;
  }
}

void executeGCodeCommand(char* command) {
  int code = atoi(command + 1);
  switch (code) {
    case 0:
    case 1:
      executeMovementCommand(command);
      break;
    case 2:
    case 3:
      executeInterpolationCommand(command);
      break;
    case 28:
      homeAllAxes();
      break;
    default:
      break;
  }
}

void executeMovementCommand(char* command) {
  float x = 0, y = 0, z = 0, e = 0;
  sscanf(command, "G%d X%f Y%f Z%f E%f", &code, &x, &y, &z, &e);
  int xSteps = x * DEFAULT_STEPS_MM;
  int ySteps = y * DEFAULT_STEPS_MM;
  int zSteps = z * DEFAULT_STEPS_MM;
  int eSteps = e * DEFAULT_STEPS_MM;

  moveStepper(X_STEP_PIN, xSteps);
  moveStepper(Y_STEP_PIN, ySteps);
  moveStepper(Z_STEP_PIN, zSteps);
  extrudeFilament(eSteps);
}

void executeInterpolationCommand(char* command) {
  // Extract interpolation parameters
  float x = 0, y = 0, z = 0, i = 0, j = 0, e = 0;
  sscanf(command, "G%d X%f Y%f Z%f I%f J%f E%f", &code, &x, &y, &z, &i, &j, &e);

  // Current position
  float currentX = getCurrentPosition(X_STEP_PIN);
  float currentY = getCurrentPosition(Y_STEP_PIN);

  // Center of the circle
  float centerX = currentX + i;
  float centerY = currentY + j;

  // Radius of the circle
  float radius = sqrt(pow(x - centerX, 2) + pow(y - centerY, 2));

  // Angle from current position to destination
  float angleStart = atan2(currentY - centerY, currentX - centerX);
  float angleEnd = atan2(y - centerY, x - centerX);

  // Number of steps for the arc
  int numSteps = ceil(fabs(angleEnd - angleStart) * radius * DEFAULT_STEPS_MM);

  // Calculate intermediate points along the arc
  for (int step = 0; step <= numSteps; step++) {
    float angle = angleStart + (angleEnd - angleStart) * step / numSteps;
    float nextX = centerX + cos(angle) * radius;
    float nextY = centerY + sin(angle) * radius;

    int xSteps = (nextX - currentX) * DEFAULT_STEPS_MM;
    int ySteps = (nextY - currentY) * DEFAULT_STEPS_MM;

    moveStepper(X_STEP_PIN, xSteps);
    moveStepper(Y_STEP_PIN, ySteps);

    currentX = nextX;
    currentY = nextY;
  }

  extrudeFilament(e * DEFAULT_STEPS_MM);
}

float getCurrentPosition(int stepPin) {
  // You need to implement this function to read current position from stepper motor driver
}

void moveStepper(int stepPin, int steps) {
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(500);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(500);
}

void extrudeFilament(int steps) {
  extruderServo.write(90);
  moveStepper(E_STEP_PIN, steps);
  extruderServo.write(0);
}

void homeAllAxes() {
  // Implement homing functionality
}
