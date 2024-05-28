#include <Common.h>

const int pwmPin = 14; // GPIO 14 as PWM output
const int freq = 50; // Frequency of 50 Hz (standard for many ESCs)
const int pwmChannel = 0;
const int resolution = 16; // 16-bit resolution for precise control

void setup() {
  // Start serial communication for debugging
  Serial.begin(115200);

  // Configure the PWM function
  ledcSetup(pwmChannel, freq, resolution);
  ledcAttachPin(pwmPin, pwmChannel);

  // Start with a low duty cycle (motor off)
  ledcWrite(pwmChannel, 3277); // Neutral point for bidirectional ESCs
  delay(5000); // Wait for ESC to initialize and calibrate

  // Safe start duty cycle
  ledcWrite(pwmChannel, 3277); // Neutral point
  delay(2000);
}

void loop() {
  // Slowly accelerate the motor forward
  for (int dutyCycle = 3277; dutyCycle <= 6553; dutyCycle += 50) { // Neutral to forward
    ledcWrite(pwmChannel, dutyCycle);
    delay(100); // Wait before increasing the duty cycle
  }

  // Hold the motor at a stable forward speed
  delay(5000); // Motor runs forward for 5 seconds

  // Slowly decelerate the motor
  for (int dutyCycle = 6553; dutyCycle >= 3277; dutyCycle -= 50) { // Forward to neutral
    ledcWrite(pwmChannel, dutyCycle);
    delay(100); // Wait before decreasing the duty cycle
  }

  // Slowly accelerate the motor in reverse
  for (int dutyCycle = 3277; dutyCycle >= 0; dutyCycle -= 50) { // Neutral to reverse
    ledcWrite(pwmChannel, dutyCycle);
    delay(100); // Wait before increasing the duty cycle
  }

  // Hold the motor at a stable reverse speed
  delay(5000); // Motor runs in reverse for 5 seconds

  // Slowly decelerate the motor from reverse
  for (int dutyCycle = 0; dutyCycle <= 3277; dutyCycle += 50) { // Reverse to neutral
    ledcWrite(pwmChannel, dutyCycle);
    delay(100); // Wait before decreasing the duty cycle
  }

  // Turn off the motor
  ledcWrite(pwmChannel, 3277); // Neutral point
  delay(5000); // Motor off for 5 seconds
}