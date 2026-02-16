/*
  PROJECT: ESP32 ALL-IN-ONE SENSOR DIAGNOSTIC TOOL
  BOARD: ESP32 DOIT DevKit V1
  AUTHOR: Arif Rijal Fadhilah
  
  DESKRIPSI:
  Alat diagnosa sensor menggunakan ESP32.
  
  CATATAN PENTING:
  - ESP32 menggunakan logika 3.3V.
  - Resolusi ADC adalah 12-bit (Nilai 0 - 4095).
*/

#include <ESP32Servo.h>

// --- KONFIGURASI PIN (SESUAI GAMBAR PINOUT) ---
#define TRIG_PIN    5    // GPIO 5
#define ECHO_PIN    18   // GPIO 18
#define SERVO_PIN   13   // GPIO 13
#define ANALOG_TEST 34   // GPIO 34 (ADC1_CH6) - Input Only Pin, Sangat aman untuk Analog
#define DIGITAL_TEST 4   // GPIO 4

Servo myServo;
int servoPos = 0;
bool servoDirection = true; 

void setup() {
  Serial.begin(115200); // ESP32 biasanya pakai baudrate lebih cepat
  
  // Setup Ultrasonic
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  // Setup Sensor Lain
  pinMode(ANALOG_TEST, INPUT);
  pinMode(DIGITAL_TEST, INPUT); // Gunakan INPUT_PULLUP jika butuh internal resistor
  
  // Setup Servo
  // ESP32Servo butuh alokasi timer, ini standar untuk ESP32
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  myServo.setPeriodHertz(50); // Standard 50hz servo
  myServo.attach(SERVO_PIN, 500, 2400); // 500-2400us pulse width (Standar SG90)
  
  Serial.println("=== ESP32 DIAGNOSTIC TOOL START ===");
  delay(1000);
}

void loop() {
  // --- 1. TEST ULTRASONIC ---
  long duration;
  float distance; // Pakai float biar presisi
  
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  duration = pulseIn(ECHO_PIN, HIGH);
  // Rumus jarak: durasi * 0.034 / 2
  distance = duration * 0.034 / 2;

  // --- 2. TEST ANALOG (Universal - ADC 12-bit) ---
  int analogVal = analogRead(ANALOG_TEST);
  // Konversi ke tegangan (3.3V referensi, 4095 resolusi)
  float voltage = analogVal * (3.3 / 4095.0);

  // --- 3. TEST DIGITAL (Universal) ---
  int digitalState = digitalRead(DIGITAL_TEST);

  // --- 4. TEST SERVO (Non-blocking sweep) ---
  if (servoDirection) {
    servoPos += 10;
    if (servoPos >= 180) servoDirection = false;
  } else {
    servoPos -= 10;
    if (servoPos <= 0) servoDirection = true;
  }
  myServo.write(servoPos);

  // --- TAMPILAN SERIAL MONITOR ---
  Serial.print("Jarak: ");
  if (distance > 400 || distance <= 0) Serial.print("---");
  else { Serial.print(distance); Serial.print(" cm"); }
  
  Serial.print(" | A0(IO34): ");
  Serial.print(analogVal); // Akan tampil 0 sampai 4095
  Serial.print(" ("); Serial.print(voltage); Serial.print("V)");
  
  Serial.print(" | D4: ");
  Serial.print(digitalState);
  
  Serial.print(" | Servo: ");
  Serial.println(servoPos);

  delay(200); 
}