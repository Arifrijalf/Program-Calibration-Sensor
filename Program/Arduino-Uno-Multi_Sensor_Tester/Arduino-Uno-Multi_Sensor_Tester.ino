/*
  PROJECT: ALL-IN-ONE SENSOR DIAGNOSTIC TOOL
  AUTHOR: Arif Rijal Fadhilah
  REPO: https://github.com/Arifrijalf/Program-Calibration-Sensor
  
  DESKRIPSI:
  Program ini dirancang untuk menguji fungsionalitas dasar dari berbagai 
  jenis komponen input/output secara bersamaan.
  
  FITUR:
  1. Cek Jarak Ultrasonic (HC-SR04)
  2. Cek Gerakan Servo (Sweep 0-180)
  3. Cek Nilai Analog (Untuk Soil Moisture, LDR, Flex, Rain Sensor)
  4. Cek Logika Digital (Untuk IR Obstacle, Flame Sensor, Button)
*/

#include <Servo.h>

// --- KONFIGURASI PIN ---
#define TRIG_PIN    9   // Pin Trig Ultrasonic
#define ECHO_PIN    10  // Pin Echo Ultrasonic
#define SERVO_PIN   6   // Pin PWM Servo
#define ANALOG_TEST A0  // Slot Test Sensor Analog (Universal)
#define DIGITAL_TEST 2  // Slot Test Sensor Digital (Universal)

Servo myServo;
int servoPos = 0;
bool servoDirection = true; // true = naik, false = turun

void setup() {
  Serial.begin(9600);
  
  // Setup Ultrasonic
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  // Setup Sensor Lain
  pinMode(ANALOG_TEST, INPUT);
  pinMode(DIGITAL_TEST, INPUT);
  
  // Setup Servo
  myServo.attach(SERVO_PIN);
  
  Serial.println("=============================================");
  Serial.println("   ALAT DIAGNOSA SENSOR & MODUL ELEKTRONIK   ");
  Serial.println("=============================================");
  delay(1000);
}

void loop() {
  // --- 1. TEST ULTRASONIC ---
  long duration, distance;
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2;

  // --- 2. TEST ANALOG (Universal) ---
  int analogVal = analogRead(ANALOG_TEST);
  float voltage = analogVal * (5.0 / 1023.0);

  // --- 3. TEST DIGITAL (Universal) ---
  int digitalState = digitalRead(DIGITAL_TEST);

  // --- 4. TEST SERVO (Gerak perlahan setiap loop) ---
  // Logic ini membuat servo bergerak tanpa blocking (tanpa for loop yang lama)
  if (servoDirection) {
    servoPos += 10;
    if (servoPos >= 180) servoDirection = false;
  } else {
    servoPos -= 10;
    if (servoPos <= 0) servoDirection = true;
  }
  myServo.write(servoPos);

  // --- TAMPILAN SERIAL MONITOR ---
  Serial.print("ULTRASONIC: ");
  if (distance > 400 || distance == 0) Serial.print("Out of Range");
  else { Serial.print(distance); Serial.print(" cm"); }
  
  Serial.print(" \t| ANALOG (A0): ");
  Serial.print(analogVal);
  Serial.print(" ("); Serial.print(voltage); Serial.print("V)");
  
  Serial.print(" \t| DIGITAL (D2): ");
  Serial.print(digitalState == HIGH ? "HIGH (1)" : "LOW (0)");
  
  Serial.print(" \t| SERVO: ");
  Serial.println(servoPos);

  delay(200); // Delay agar pembacaan stabil dan tidak terlalu cepat yang mengakibatkan Error
}