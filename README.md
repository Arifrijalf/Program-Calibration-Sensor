# 🛠️ ESP32 Sensor Diagnostic & Calibration Tool

Repository ini berisi *source code* untuk melakukan pengujian cepat (*sanity check*) dan kalibrasi berbagai modul sensor elektronik menggunakan **ESP32 DOIT DevKit V1**.

Alat ini sangat berguna untuk memastikan komponen berfungsi dengan baik sebelum dipasang ke proyek utama atau Tugas Akhir.

## 📋 Fitur Utama
Program `Multi_Sensor_Tester_ESP32.ino` memungkinkan pengujian simultan untuk:
1.  **Ultrasonic (HC-SR04)**: Mengukur jarak dan validasi respon sensor.
2.  **Servo Motor (SG90/MG995)**: Melakukan *sweep* otomatis (0°-180°) untuk cek gear.
3.  **Analog Sensors (Soil Moisture, Rain, LDR, Flex)**: Membaca nilai ADC 12-bit (0-4095) dan tegangan.
4.  **Digital Sensors (IR Obstacle, Flame, Button)**: Cek logika HIGH/LOW.

## 🔌 Wiring (Pinout Konfigurasi)
Program ini dikonfigurasi untuk **ESP32 DOIT DevKit V1** (38 Pin).

| Komponen | Pin Sensor | Pin ESP32 (GPIO) | Keterangan |
| :--- | :--- | :--- | :--- |
| **Ultrasonic** | VCC | VIN / 5V | Butuh 5V |
| | GND | GND | - |
| | Trig | **D5** (GPIO 5) | Output Trigger |
| | Echo | **D18** (GPIO 18) | Input Echo |
| **Servo** | VCC | VIN / 5V | Kabel Merah |
| | GND | GND | Kabel Coklat |
| | Signal | **D13** (GPIO 13) | Kabel Oranye |
| **Analog Test** | OUT | **D34** (GPIO 34) | *Input Only Pin* (Aman untuk ADC) |
| **Digital Test** | OUT | **D4** (GPIO 4) | Universal I/O |

> ⚠️ **PERHATIAN:** Pastikan tegangan input ke Pin GPIO ESP32 tidak melebihi 3.3V secara berlebihan. Gunakan *voltage divider* jika perlu, meskipun untuk sensor standar biasanya aman.

## 🚀 Cara Menggunakan
1.  Install **Arduino IDE**.
2.  Install Board ESP32 di *Board Manager*.
3.  Install Library **ESP32Servo** by Kevin Harrington via *Library Manager*.
4.  Buka file `.ino` dan upload ke board (Baudrate upload: **115200**).
5.  Buka **Serial Monitor** dan set baudrate ke **115200**.

## 📊 Contoh Output Serial Monitor
```text
Jarak: 45 cm | A0(IO34): 2048 (1.65V) | D4: 1 | Servo: 90
Jarak: 44 cm | A0(IO34): 1023 (0.82V) | D4: 0 | Servo: 100
...