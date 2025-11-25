# FSS-PROJECT
# GSM Signal Strength Monitor

This Arduino project monitors the signal strength (RSSI) of a GSM module and prints the results to the Serial Monitor. It is ideal for testing network coverage and optimizing antenna placement.

---

## Features

- Reads GSM signal strength every 10 seconds.  
- Converts RSSI values to **dBm** for easier interpretation.  
- Displays signal quality with intuitive symbols:  
  - ✗ NO SIGNAL / MOVE ANTENNA  
  - ⚠ Too weak  
  - △ Weak but may work  
  - ○ Fair  
  - ● Good  
  - ✓ Excellent  
- Simple Serial Monitor output for easy reading.  
- Helps determine optimal antenna placement.

---

## Hardware Requirements

- Arduino board (Uno, Nano, Mega, etc.)  
- GSM module (SIM800, SIM900, etc.)  
- Jumper wires  
- Optional: external antenna for better reception  

---

## Pin Connections

| GSM Module | Arduino |
|------------|---------|
| TX         | Pin 10  |
| RX         | Pin 11  |
| GND        | GND     |
| VCC        | 5V / 3.7V LiPo |

> Make sure the GSM module voltage matches your Arduino’s requirements.

---

## Software Requirements

- Arduino IDE (1.8+ recommended)  
- `SoftwareSerial` library (built-in with Arduino IDE)  

---

## Usage

1. Connect your GSM module to the Arduino according to the table above.  
2. Upload the code to your Arduino.  
3. Open the **Serial Monitor** at 9600 baud.  
4. You will see an initial message:
=== SIGNAL STRENGTH MONITOR ===
This will check signal every 10 seconds
Try moving antenna/module to different locations
Target: RSSI > 5 (minimum), RSSI > 10 (good)
5. Every 10 seconds, the module will report RSSI and signal quality:
exemple : Time: 15s - RSSI: 12 (-89 dBm) - ● Good

6. Adjust antenna placement if the signal is weak.

---

## How It Works

1. The Arduino communicates with the GSM module via **SoftwareSerial** (pins 10 and 11).  
2. Every 10 seconds, it sends the `AT+CSQ` command to request signal strength.  
3. The module responds with `+CSQ: <rssi>,<ber>`.  
4. RSSI is extracted and converted to dBm using:

dBm = -113 + (RSSI * 2) 

5. The code displays RSSI, dBm, and signal quality on the Serial Monitor.

---

## Signal Interpretation

| RSSI Value | Quality            | Comment                 |
|------------|------------------|------------------------|
| 0 or 99    | NO SIGNAL ✗      | Move antenna           |
| 1–4        | Too weak ⚠       | Unreliable connection  |
| 5–9        | Weak △           | May work, unstable     |
| 10–14      | Fair ○           | Decent connection      |
| 15–19      | Good ●           | Reliable connection    |
| 20+        | Excellent ✓      | Strong signal          |

---

## Notes & Limitations

- Code uses blocking loops, so the Arduino cannot perform other tasks during signal reading.  
- Uses `String` objects which may cause memory issues over long periods.  
- Thresholds for signal quality are approximate and may vary by network.  
- Ensure your GSM module has adequate power for reliable operation.  
- Designed for basic monitoring; for production, consider non-blocking code and data logging.
