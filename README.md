# Arduino-Pomodoro-Timer-RTC-Clock

A compact **Arduino-based Pomodoro Timer and Real-Time Clock** using a 4-digit TM1637 display, rotary encoder controls, and an RTC module.
The device can work in two modes: **Pomodoro Timer Mode** for productivity sessions and **Clock Mode** to display the current time.

The system uses a rotary encoder for setting the timer and controlling start/pause, along with dedicated buttons for **mode switching** and **timer reset**.

# Features

1. Pomodoro Timer Mode

  * Adjustable timer (1–99 minutes) using a rotary encoder
  * Start, pause, and resume using encoder button
  * Reset timer using a dedicated reset button
  * Audible buzzer alert when the timer finishes
2. Real-Time Clock Mode

  * Displays current time in **HH:MM** format
  * Uses an RTC module for accurate timekeeping
  * Automatically updates RTC time if power was lost
3. Mode Switching

  * Dedicated button toggles between:
    * Pomodoro Timer
    * Clock Display
      
* 💡 **4-Digit LED Display**

  * Uses TM1637 display for clear time visualization
  * Displays **MM:SS** in timer mode and **HH:MM** in clock mode

---

## Hardware Components

* Arduino (Uno / Nano / compatible)
* TM1637 4-digit 7-segment display
* Rotary encoder with push button
* RTC module (DS3231 recommended)
* Active buzzer
* 2 push buttons (Mode & Reset)
* Jumper wires

---

## Pin Configuration

| ComponentArduino Pin |    |
| -------------------- | -- |
| TM1637 CLK           | 2  |
| TM1637 DIO           | 3  |
| Buzzer               | 8  |
| Encoder CLK          | 5  |
| Encoder DT           | 4  |
| Encoder SW           | 9  |
| Mode Button          | 6  |
| Reset Button         | 7  |
| RTC SDA              | A4 |
| RTC SCL              | A5 |

---

## Controls

| ControlFunction |                                         |
| --------------- | --------------------------------------- |
| Rotate Encoder  | Adjust timer minutes                    |
| Encoder Button  | Start / Pause / Resume timer            |
| Mode Button     | Switch between Clock and Pomodoro modes |
| Reset Button    | Reset the timer                         |

---

## How It Works

1. **Pomodoro Mode**

   * Rotate encoder to set the desired session length.
   * Press the encoder button to start the countdown.
   * Press again to pause or resume.
   * When the timer finishes, the buzzer sounds.
2. **Clock Mode**

   * Displays the current time from the RTC module.
   * Time continues running even if Arduino power is removed (RTC battery).
3. **RTC Auto Sync**

   * If the RTC module loses power, the time automatically resets to the sketch compile time.

---

## Libraries Used

* TM1637Display
* RTClib
* Wire

Installing them via **Arduino Library Manager**.

## Possible Improvements

* Automatic Pomodoro cycles (25 min work / 5 min break)
* EEPROM storage for last mode
* Brightness auto-adjust based on time of day
* Alarm functionality
* Non-blocking firmware improvements

## License

Open-source project – free to modify and improve.
