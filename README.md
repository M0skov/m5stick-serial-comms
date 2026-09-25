# M5Stick Serial Communication

Lab 2 (ELEE 2045): two-part lab on embedded serial communication with the M5Stick (ESP32).

## Part 1 - Stopwatch

Arduino firmware implementing a stopwatch on the M5Stick.

- `stopwacth/m5stopwatch.ino`

Demo: https://youtube.com/shorts/NuDEeFgo3Bs

## Part 2 - Bidirectional communication

Two-way serial link between a PC and the M5Stick:

- `Bidirectional communication/resource_monitor.py` - Python script that reads PC resource stats (CPU, memory, battery via `psutil`) and exchanges data with the M5Stick over serial
- `Bidirectional communication/m5resource.ino.ino` - M5Stick firmware for the serial exchange

Demo: https://youtube.com/shorts/fCa9zhUqMy4

## Setup

```bash
pip install pyserial psutil
```

Flash the `.ino` files to the M5Stick with the Arduino IDE (M5StickC board support), then run the Python script and select the M5Stick's serial port when prompted.
