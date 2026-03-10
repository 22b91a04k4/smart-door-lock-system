Smart Door Lock System is an IoT-based security project using Arduino Uno, RFID authentication, and distance sensing. The system checks for a nearby person, asks for RFID verification, and unlocks the door only for an authorized card.

![Smart Door Lock Setup](smart-door-lock-system%20(2).png)

## Hardware Code Explanation (`hardware.c`)

### Libraries Used
- `SPI.h` and `MFRC522.h`: RFID card reading with RC522 module
- `Servo.h`: Door lock/unlock control using servo motor
- `Wire.h` and `LiquidCrystal_I2C.h`: 16x2 I2C LCD display

### Pin Configuration
- RFID: `SS_PIN = 10`, `RST_PIN = 9`
- Servo: pin `8`
- Ultrasonic sensor: `trigPin = 6`, `echoPin = 7`
- Indicators: `greenLED = 3`, `redLED = 4`, `buzzer = 5`

### Authentication Logic
- Authorized RFID UID is stored as:
	- `byte authorizedUID[4] = {0xA3, 0x12, 0xBC, 0x44};`
- In `checkCard()`, scanned UID bytes are compared one-by-one.
- Match -> `accessGranted()`
- No match -> `accessDenied()`

### System Working Flow
1. System initializes RFID, servo, LCD, LEDs, buzzer, and ultrasonic sensor.
2. Door starts in locked state (`myServo.write(0)`).
3. Ultrasonic sensor measures distance continuously.
4. If person is within `100 cm`, LCD shows **Verify Your ID**.
5. RFID card is scanned:
	 - Authorized: green LED ON, short buzzer beep, servo opens to `90°` for 5 seconds, then locks again.
	 - Unauthorized: red LED blinks with buzzer alert 3 times.
6. If no person nearby, LCD shows **No Person Near**.

---

## HTML Page Explanation (`index.html`)

### Structure
- Uses a single centered section (`.section`) to display project details.
- Includes title, project image, overview text, component list, and working principle.

### Styling
- Clean card-style layout with white background and rounded corners.
- Responsive width using `max-width: 900px` and mobile viewport meta tag.
- Simple button styling for navigation link.

### Content Sections
- **Project Overview**: Brief intro to RFID + servo-based smart lock.
- **Components Used**: Full hardware list.
- **Working Principle**: Step-by-step behavior for authorized and unauthorized access.

### Important Note
- In `index.html`, image source is currently `smart-door-lock-system.png`.
- Current workspace image file is `smart-door-lock-system (2).png`.
- Update the `img src` filename in HTML if you want the image to display correctly.

---

## Folder Structure

```text
smart door project/
├── hardware.c
├── index.html
├── README.md
├── smart-door-lock-system (2).png
└── smart-door-lock-system/
		└── README.md
```

## Summary

This project combines physical sensing (ultrasonic), identity verification (RFID), and actuator control (servo) to create a practical smart door lock prototype with clear visual/audio feedback.
