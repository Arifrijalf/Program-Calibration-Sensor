# 🛠️ Universal Sensor Diagnostic & Calibration Tool (Arduino & ESP32)

Repository ini berisi kumpulan *source code* untuk melakukan pengujian cepat (*sanity check*), kalibrasi, dan pengecekan kondisi berbagai modul sensor elektronik.

Mendukung dua *platform* mikrokontroler paling populer:
1.  **Arduino Uno** (ATmega328P) - 5V Logic
2.  **ESP32** (DOIT DevKit V1) - 3.3V Logic

## 📂 Struktur Folder
* `/arduino_uno_version`: Kode khusus untuk Arduino Uno.
* `/esp32_version`: Kode khusus untuk ESP32 (menggunakan library berbeda).

## 📋 Fitur Utama
Program ini ("All-in-One Tester") memungkinkan pengujian simultan untuk:
1.  **Ultrasonic (HC-SR04)**: Mengukur jarak dan validasi respon sensor.
2.  **Servo Motor (SG90/MG995)**: Melakukan *sweep* otomatis (0°-180°) untuk cek gear.
3.  **Analog Sensors (Soil Moisture, Rain, LDR, Flex)**: Membaca nilai mentah (Raw) dan voltase.
4.  **Digital Sensors (IR Obstacle, Flame, Button)**: Cek logika HIGH/LOW.

---

## 🔌 Wiring (Konfigurasi Pin)

### 1. Versi Arduino Uno (5V)
| Komponen | Pin Sensor | Pin Arduino | Keterangan |
| :--- | :--- | :--- | :--- |
| **Ultrasonic** | Trig | **Pin 9** | Output |
| | Echo | **Pin 10** | Input |
| **Servo** | Signal | **Pin 6** | Pin PWM |
| **Analog Test** | OUT | **Pin A0** | Universal Analog Input |
| **Digital Test** | OUT | **Pin 2** | Universal Digital Input |

### 2. Versi ESP32 (3.3V)
| Komponen | Pin Sensor | Pin ESP32 (GPIO) | Keterangan |
| :--- | :--- | :--- | :--- |
| **Ultrasonic** | Trig | **D5** (GPIO 5) | Output |
| | Echo | **D18** (GPIO 18) | Input |
| **Servo** | Signal | **D13** (GPIO 13) | Output PWM |
| **Analog Test** | OUT | **D34** (GPIO 34) | *Input Only* (Aman untuk ADC) |
| **Digital Test** | OUT | **D4** (GPIO 4) | Universal I/O |

> ⚠️ **PERHATIAN TEGANGAN:**
> * **Arduino Uno:** Bekerja pada logika **5V**. Aman untuk hampir semua sensor standar.
> * **ESP32:** Bekerja pada logika **3.3V**. Hati-hati saat menghubungkan sensor yang mengeluarkan output 5V. Gunakan *voltage divider* jika ragu.

---

## 🚀 Cara Menggunakan

### Untuk Arduino Uno:
1.  Buka folder `arduino_uno_version`.
2.  Buka file `.ino` di Arduino IDE.
3.  Pilih Board: **Arduino Uno**.
4.  Upload & Buka Serial Monitor (Baudrate: **9600**).

### Untuk ESP32:
1.  Buka folder `esp32_version`.
2.  Install Library **ESP32Servo** via *Library Manager*.
3.  Pilih Board: **DOIT ESP32 DEVKIT V1**.
4.  Upload & Buka Serial Monitor (Baudrate: **115200**).

## 📊 Perbedaan Pembacaan ADC
* **Arduino Uno:** Nilai 0 - 1023 (10-bit resolution).
* **ESP32:** Nilai 0 - 4095 (12-bit resolution).

---
*Dibuat oleh Arif Rijal Fadhilah*