#include <TM1637Display.h>
#include <Wire.h>
#include <RTClib.h>

// --------------------
// Display + buzzer pins
// --------------------
#define DISP_CLK 2
#define DISP_DIO 3
#define BUZZER   8

// Rotary encoder pins
#define ENC_CLK 5
#define ENC_DT  4
#define ENC_SW  9

// Extra buttons
#define MODE_BTN   11
#define RESET_BTN  12

TM1637Display display(DISP_CLK, DISP_DIO);
RTC_DS3231 rtc;

// --------------------
volatile int lastStateCLK;
volatile int currentStateCLK;

int setMinutes = 25;
bool running = false;
bool paused = false;

unsigned long startMillis = 0;
unsigned long pausedAt = 0;
unsigned long totalSeconds = 0;

int mode = 0;   // 0 = Pomodoro, 1 = Clock

// =====================================================
// SETUP
// =====================================================
void setup() {

  Serial.begin(9600);

  pinMode(ENC_CLK, INPUT);
  pinMode(ENC_DT, INPUT);
  pinMode(ENC_SW, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);

  pinMode(MODE_BTN, INPUT_PULLUP);
  pinMode(RESET_BTN, INPUT_PULLUP);

  lastStateCLK = digitalRead(ENC_CLK);

  display.setBrightness(7);

  Wire.begin();

  if (!rtc.begin()) {
    while (1); // stop if RTC not found
  }

  // Auto set RTC time ONLY if it lost power
  if (rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  showTime(setMinutes * 60);
}

// =====================================================
// LOOP
// =====================================================
void loop() {

  // --------------------
  // MODE BUTTON
  // --------------------
  if (digitalRead(MODE_BTN) == LOW) {
    delay(200);
    mode = !mode;
    running = false;
    paused = false;
  }

  // --------------------
  // CLOCK MODE
  // --------------------
  if (mode == 1) {

    DateTime now = rtc.now();
    int value = now.hour() * 100 + now.minute();

    display.showNumberDecEx(value, 0b01000000, true);
    delay(200);
    return;
  }

  // --------------------
  // RESET BUTTON (Pomodoro)
  // --------------------
  if (digitalRead(RESET_BTN) == LOW) {
    delay(200);
    running = false;
    paused = false;
    showTime(setMinutes * 60);
  }

  // --------------------
  // ROTARY ENCODER (Set Minutes)
  // --------------------
  currentStateCLK = digitalRead(ENC_CLK);

  if (!running && currentStateCLK != lastStateCLK && currentStateCLK == LOW) {

    if (digitalRead(ENC_DT) != currentStateCLK) {
      setMinutes++;
    } else {
      setMinutes--;
    }

    if (setMinutes < 1) setMinutes = 1;
    if (setMinutes > 99) setMinutes = 99;

    showTime(setMinutes * 60);
  }

  lastStateCLK = currentStateCLK;

  // --------------------
  // START / PAUSE
  // --------------------
  if (digitalRead(ENC_SW) == LOW) {
    delay(200);

    if (!running) {
      running = true;
      paused = false;
      totalSeconds = setMinutes * 60;
      startMillis = millis();
    }
    else if (!paused) {
      paused = true;
      pausedAt = millis();
    }
    else {
      startMillis += (millis() - pausedAt);
      paused = false;
    }
  }

  // --------------------
  // COUNTDOWN
  // --------------------
  if (running && !paused) {

    unsigned long elapsed = (millis() - startMillis) / 1000;

    if (elapsed >= totalSeconds) {
      running = false;
      beepDone();
      showTime(setMinutes * 60);
    } else {
      showTime(totalSeconds - elapsed);
    }
  }
}

// =====================================================
// DISPLAY FUNCTION
// =====================================================
void showTime(unsigned long seconds) {
  int minutes = seconds / 60;
  int secs = seconds % 60;
  int value = minutes * 100 + secs;
  display.showNumberDecEx(value, 0b01000000, true);
}

// =====================================================
// BUZZER ALERT
// =====================================================
void beepDone() {
  for (int i = 0; i < 5; i++) {
    tone(BUZZER, 1000);
    delay(2000);
    noTone(BUZZER);
    delay(200);
  }
}