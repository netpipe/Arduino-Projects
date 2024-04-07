#include <Stepper.h>
#include <math.h>

// Define motor steps per revolution
const int STEPS_PER_REVOLUTION = 4096;  // 28BYJ-48 stepper motor with 64:1 gear reduction

// Define arm dimensions
const float L1 = 10.0; // Length of the main axis
const float L2 = 8.0;  // Length of the arm segment connected to the main axis
const float L3 = 6.0;  // Length of the arm segment connected to the end-effector

// Define steps per inch calibration numbers
const float STEPS_PER_INCH[3] = {200, 200, 200};  // Adjust for each axis

// Define motor pins
const int motorPins[3][4] = {
  {8, 9, 10, 11},  // Base motor pins: IN1, IN2, IN3, IN4
  {12, 13, 14, 15}, // Secondary motor pins: IN1, IN2, IN3, IN4
  {16, 17, 18, 19}  // Z-axis motor pins: IN1, IN2, IN3, IN4
};

// Create stepper motor objects for each axis
Stepper steppers[3] = {
  Stepper(STEPS_PER_REVOLUTION, motorPins[0][0], motorPins[0][1], motorPins[0][2], motorPins[0][3]),
  Stepper(STEPS_PER_REVOLUTION, motorPins[1][0], motorPins[1][1], motorPins[1][2], motorPins[1][3]),
  Stepper(STEPS_PER_REVOLUTION, motorPins[2][0], motorPins[2][1], motorPins[2][2], motorPins[2][3])
};

// Function to calculate inverse kinematics
void calculateIK(float x, float y, float z, float& theta1, float& theta2, float& theta3) {
  // Calculate theta1
  theta1 = atan2(y, x);

  // Calculate r and s
  float r = sqrt(x * x + y * y) - L1;
  float s = sqrt(r * r + z * z);

  // Calculate theta2
  theta2 = acos((L2 * L2 + s * s - L3 * L3) / (2.0 * L2 * s)) + atan2(z, r);

  // Calculate theta3
  theta3 = M_PI - acos((L2 * L2 + L3 * L3 - s * s) / (2.0 * L2 * L3));
}

void setup() {
  // Set motor speed and acceleration
  for (int i = 0; i < 3; ++i) {
    steppers[i].setSpeed(100); // Adjust speed as needed
  }

  // Example XYZ position in inches (adjust as needed)
  float x_inches = 12.0;
  float y_inches = 5.0;
  float z_inches = 8.0;

  // Convert inches to steps using steps per inch calibration
  long steps[3] = {
    lround(x_inches * STEPS_PER_INCH[0]),
    lround(y_inches * STEPS_PER_INCH[1]),
    lround(z_inches * STEPS_PER_INCH[2])
  };

  // Move motors to calculated positions
  for (int i = 0; i < 3; ++i) {
    steppers[i].step(steps[i]);
  }
}

void loop() {
  // Empty loop
}

