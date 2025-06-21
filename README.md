# Cara Download Library untuk Support `main.ino`

Agar kode `main.ino` dapat berjalan dengan baik di ESP32, Anda perlu menginstal beberapa library berikut di Arduino IDE:

## 1. PS4Controller Library

Digunakan untuk menghubungkan ESP32 dengan controller PS4 via Bluetooth.

**Cara install:**
1. Buka Arduino IDE.
2. Pilih menu **Sketch > Include Library > Manage Libraries...**
3. Pada kolom pencarian, ketik: `PS4Controller`
4. Pilih **PS4Controller by jvpernis** lalu klik **Install**.

Atau bisa juga install manual:
- Download dari [https://github.com/aed3/PS4-esp32](https://github.com/aed3/PS4-esp32)
- Ekstrak dan copy folder ke `Documents/Arduino/libraries`

## 2. ESP32Servo Library

Digunakan untuk mengontrol servo motor dengan ESP32.

**Cara install:**
1. Buka **Library Manager** seperti langkah di atas.
2. Cari: `ESP32Servo`
3. Pilih **ESP32Servo by John Bennett** lalu klik **Install**.

Atau manual:
- Download dari [https://github.com/jkb-git/ESP32Servo](https://github.com/jkb-git/ESP32Servo)
- Ekstrak dan copy ke folder `libraries`.

## 3. Board ESP32

Pastikan sudah menambahkan board ESP32 di Arduino IDE:
1. Buka **File > Preferences**
2. Pada **Additional Boards Manager URLs**, tambahkan.



# Cara connect PS4 controller ke ESP32

1. Download **sixaxis pair tool**
2. Cari tau MAC Address ESP32 nya. Biasaya pas run sisaxis ini, bakal auto kedetect buat mad addressnya
3. Sambungin ESP32 ke komputer dan juga PS4 controller ke komputer melalui kabel data
4. Nyalain ESP32 nya trus nyalain jg PS4 controllernya
5. Harusnya udah kesambung abis ini