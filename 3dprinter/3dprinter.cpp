#include <Servo.h>

// Define pins for stepper motor drivers
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

// Define constants for movement speeds and steps per millimeter
#define DEFAULT_FEEDRATE    4000  // Default feedrate in mm/min
#define DEFAULT_STEPS_MM    80    // Default steps per millimeter

// Define servo pin for controlling extruder
#define EXTRUDER_PIN        9

// Define command buffer size
#define COMMAND_BUFFER_SIZE 64

char commandBuffer[COMMAND_BUFFER_SIZE];
int commandIndex = 0;

Servo extruderServo;

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Initialize stepper motor pins
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

  // Initialize servo pin
  extruderServo.attach(EXTRUDER_PIN);

  // Disable steppers and servo initially
  digitalWrite(X_ENABLE_PIN, LOW);
  digitalWrite(Y_ENABLE_PIN, LOW);
  digitalWrite(Z_ENABLE_PIN, LOW);
  digitalWrite(E_ENABLE_PIN, LOW);

  // Move extruder to starting position
  extruderServo.write(0);
}

void loop() {
  // Check for incoming commands
  if (Serial.available() > 0) {
    char c = Serial.read();
    if (c == '\n' || c == '\r') {
      commandBuffer[commandIndex] = '\0'; // Null-terminate the string
      processCommand(commandBuffer);
      commandIndex = 0; // Reset command buffer index
    } else {
      commandBuffer[commandIndex] = c;
      commandIndex++;
      // Check for buffer overflow
      if (commandIndex >= COMMAND_BUFFER_SIZE) {
        commandIndex = 0;
      }
    }
  }
}

void processCommand(char* command) {
  // Parse and execute G-code commands
  switch (command[0]) {
    case 'G':
      executeGCodeCommand(command);
      break;
    default:
      // Unsupported command
      break;
  }
}

void executeGCodeCommand(char* command) {
  // Extract command parameters
  int code = atoi(command + 1); // Extract G-code number
  switch (code) {
    case 0: // G0 - Rapid Movement
    case 1: // G1 - Controlled Movement
      executeMovementCommand(command);
      break;
    case 28: // G28 - Home all axes
      homeAllAxes();
      break;
    default:
      // Unsupported G-code command
      break;
  }
}

void executeMovementCommand(char* command) {
  // Extract movement parameters
  float x = 0, y = 0, z = 0, e = 0;
  sscanf(command, "G%d X%f Y%f Z%f E%f", &code, &x, &y, &z, &e);
  // Calculate steps to move
  int xSteps = x * DEFAULT_STEPS_MM;
  int ySteps = y * DEFAULT_STEPS_MM;
  int zSteps = z * DEFAULT_STEPS_MM;
  int eSteps = e * DEFAULT_STEPS_MM;

  // Move to specified coordinates
  moveStepper(X_STEP_PIN, xSteps);
  moveStepper(Y_STEP_PIN, ySteps);
  moveStepper(Z_STEP_PIN, zSteps);
  extrudeFilament(eSteps);
}

void moveStepper(int stepPin, int steps) {
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(500); // Adjust delay as needed for your stepper motor
  digitalWrite(stepPin, LOW);
  delayMicroseconds(500); // Adjust delay as needed for your stepper motor
}

void extrudeFilament(int steps) {
  extruderServo.write(90); // Open extruder
  moveStepper(E_STEP_PIN, steps);
  extruderServo.write(0); // Close extruder
}

void homeAllAxes() {
  // Move all axes to their home positions
  // You need to implement this function according to your printer's setup
}

