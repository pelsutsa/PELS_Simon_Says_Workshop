// SECTION 1: LIBRARIES FOR THE OLED DISPLAY

// Allows the Arduino to communicate with the OLED
#include <Wire.h>
// Provides functions to draw text on the OLED
#include <Adafruit_GFX.h>
// Controls the OLED display
#include <Adafruit_SSD1306.h>

// SECTION 2: OLED DISPLAY SETTINGS

// OLED screen dimensions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// OLED does not use a dedicated reset pin
#define OLED_RESET -1

// Create the OLED display object
Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  OLED_RESET
);

// SECTION 3: LED CONNECTIONS

// LED order: Red, Green, Blue, Yellow
const byte ledPins[4] = {2, 4, 6, 8};

// SECTION 4: BUTTON CONNECTIONS

// Each button corresponds to an LED
// Red = D3, Green = D5
// Blue = D7, Yellow = D9

const byte buttonPins[4] = {3, 5, 7, 9};

// SECTION 5: BUZZER SETTINGS

// Buzzer connected to digital pin 10
const byte buzzerPin = 10;

// Each LED has a different sound frequency
// Red = 330 Hz
// Green = 392 Hz
// Blue = 440 Hz
// Yellow = 523 Hz

const int buzzerTones[4] = {
  330, 392, 440, 523
};

// SECTION 6: GAME VARIABLES

// Maximum number of rounds
const int MAX_ROUNDS = 100;

// Stores the randomly generated LED sequence
byte sequence[MAX_ROUNDS];

// Current round number
int roundNumber = 1;

// Number of completed rounds
int score = 0;

// SECTION 7: OLED MESSAGE FUNCTION

// Displays a title, message, and score
void showScreen(const char* title, const char* message) {
  // Erase previous screen contents
  display.clearDisplay();

  // Set text color to white
  display.setTextColor(SSD1306_WHITE);

  // Display large title
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.println(title);

  // Display smaller message
  display.setTextSize(1);
  display.setCursor(0, 30);
  display.println(message);

  // Display player's current score
  display.setCursor(0, 50);
  display.print("Score: ");
  display.print(score);

  // Send everything to the OLED
  display.display();
}

// SECTION 8: OLED SCORE AND ROUND DISPLAY

// Updates the current round and score
void updateOLED() {

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  // Game title
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.println("SIMON");

  // Current round
  display.setTextSize(1);
  display.setCursor(0, 28);
  display.print("Round: ");
  display.println(roundNumber);

  // Current score
  display.setCursor(0, 42);
  display.print("Score: ");
  display.println(score);

  display.display();
}

// SECTION 9: LED AND BUZZER FUNCTION

// Turns on an LED and plays its matching sound
void flashLED(byte color, int duration) {

  // Turn on selected LED
  digitalWrite(ledPins[color], HIGH);

  // Play selected LED's sound
  tone(buzzerPin, buzzerTones[color]);

  // Keep LED and sound on
  delay(duration);

  // Turn off LED
  digitalWrite(ledPins[color], LOW);

  // Stop buzzer
  noTone(buzzerPin);

  // Short pause before next LED
  delay(180);
}

// SECTION 10: BUTTON INPUT FUNCTION

// Detects which button the player presses
int readButton() {

  // Check each of the four buttons
  for (int i = 0; i < 4; i++) {

    // LOW means button is pressed
    if (digitalRead(buttonPins[i]) == LOW) {

      // Wait briefly to prevent button bounce
      delay(25);

      // Confirm button is still pressed
      if (digitalRead(buttonPins[i]) == LOW) {

        // Light up corresponding LED
        digitalWrite(ledPins[i], HIGH);

        // Play corresponding buzzer pitch
        tone(buzzerPin, buzzerTones[i]);

        // Wait until player releases button
        while (digitalRead(buttonPins[i]) == LOW) {
          delay(5);
        }

        // Turn off LED
        digitalWrite(ledPins[i], LOW);

        // Stop sound
        noTone(buzzerPin);

        // Short debounce delay
        delay(25);

        // Return button number (0 to 3)
        return i;
      }
    }
  }

  // -1 means no button was pressed
  return -1;
}

// SECTION 11: WAIT FOR BUTTON FUNCTION

// Waits until the player presses any button
int waitForButton() {

  int pressed = -1;

  // Keep checking until a button is pressed
  while (pressed == -1) {
    pressed = readButton();
  }

  return pressed;
}
// SECTION 12: PLAY SIMON SEQUENCE

// Arduino shows the LED pattern to the player
void playSequence() {

  // LEDs become faster in later rounds
  int speed = 600 - (roundNumber - 1) * 20;

  // Prevent LEDs from becoming too fast
  if (speed < 200) {
    speed = 200;
  }

  // Tell player to watch the sequence
  showScreen("WATCH", "Remember colors");

  // Wait 2 seconds before starting
  delay(1000);

  // Flash LEDs in the stored order
  for (int i = 0; i < roundNumber; i++) {

    flashLED(sequence[i], speed);
  }

  // Show round and score afterward
  updateOLED();
}

// SECTION 13: CHECK PLAYER'S ANSWER

// Checks whether player repeats sequence correctly
bool checkSequence() {

  // Check each button in the sequence
  for (int i = 0; i < roundNumber; i++) {

    // Wait for player to press a button
    int pressed = waitForButton();

    // Compare button to expected color
    if (pressed != sequence[i]) {

      // Wrong button
      return false;
    }
  }

  // Every button was correct
  return true;
}

// SECTION 14: START A NEW GAME

// Resets score and generates a new sequence
void startNewGame() {

  // Reset game progress
  score = 0;
  roundNumber = 1;

  // Generate 100 random LED colors
  for (int i = 0; i < MAX_ROUNDS; i++) {

    // Random number between 0 and 3
    sequence[i] = random(0, 4);
  }

  // Update OLED
  updateOLED();

  delay(500);
}

// SECTION 15: ARDUINO SETUP

// Runs once when Arduino powers on
void setup() {

  // Configure LEDs and buttons
  for (int i = 0; i < 4; i++) {

    // LEDs are outputs
    pinMode(ledPins[i], OUTPUT);

    // Buttons use internal pull-up resistors
    pinMode(buttonPins[i], INPUT_PULLUP);
  }

  // Set buzzer as output
  pinMode(buzzerPin, OUTPUT);

  // Create different random sequences
  randomSeed(analogRead(A0));

  // Start I2C communication
  Wire.begin();

  // Initialize OLED at address 0x3C
  if (!display.begin(
      SSD1306_SWITCHCAPVCC, 0x3C)) {

    // Stop if OLED cannot be initialized
    while (true) {
    }
  }

  // Starting screen
  showScreen("SIMON", "Press any button");

  // Wait for player to begin
  waitForButton();

  // Start first game
  startNewGame();
}

// SECTION 16: MAIN GAME LOOP

// Repeats continuously while Arduino is powered
void loop() {

  // Arduino displays LED sequence
  playSequence();

  // Check if player repeats it correctly
  if (checkSequence()) {

    // Increase score
    score++;

    // Check if maximum round is reached
    if (roundNumber >= MAX_ROUNDS) {

      showScreen("YOU WIN!", "All rounds done!");

      // Wait for restart
      waitForButton();
      startNewGame();

      return;
    }

    // Correct answer message
    showScreen("CORRECT!", "Next round...");

    delay(900);

    // Advance to next round
    roundNumber++;

    // Update score and round on OLED
    updateOLED();

    delay(500);
  }

  else {

    // Wrong answer ends the game
    showScreen("GAME OVER", "Press to restart");

    // Wait for player to restart
    waitForButton();

    // Reset game with new random sequence
    startNewGame();
  }
}
