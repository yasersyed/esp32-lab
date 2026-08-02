# ESP32 Lab

Health checks, tests, and miscellaneous examples for getting started with ESP32 and Arduino.

## Structure

- `01_blink_serial/esp32_board_test.ino` — basic upload test (LED + Serial)
- `02_health_check/esp32_health_check.ino` — chip info, flash info, Wi-Fi scan, LED heartbeat

## Requirements

- ESP32 dev board
- Arduino IDE 2.x
- ESP32 core (`esp32 by Espressif Systems`)

Board Manager URL:

`https://espressif.github.io/arduino-esp32/package_esp32_index.json`

## Upload notes (Arch Linux)

If you hit serial permission errors (`/dev/ttyUSB0`), add your user to serial groups:

```bash
sudo usermod -aG uucp $USER
sudo usermod -aG lock $USER
```

Then log out and back in, reopen Arduino IDE, and upload again.

## Example: Blink + Serial

Open `01_blink_serial/esp32_board_test.ino`, select your ESP32 board and port, upload, then open Serial Monitor at `115200`.

## Example: Health Check

Open `02_health_check/esp32_health_check.ino`, upload, and read diagnostics in Serial Monitor (`115200`).
