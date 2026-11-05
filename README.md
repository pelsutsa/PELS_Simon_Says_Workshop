# PELS Simon Game Workshop

## Project Overview
This project is a hardware-based **Simon Says memory game** built using an **Arduino Nano**, four colored LEDs, four push buttons, a passive buzzer, and an OLED display. The objective is to memorize and repeat an increasingly long sequence of colored LEDs and corresponding sounds. Each successful round adds another random color to the sequence, while the LED playback gradually increases in speed to make the game more challenging. The **OLED display** tracks the player's current score, round number, and game status. This project demonstrates concepts in **embedded systems, microcontroller programming, digital electronics, and hardware-software integration**.

## Project Objectives
- Design and build an interactive memory game using an Arduino Nano.
- Control LEDs and detect push-button inputs.
- Generate random LED sequences for each new game.
- Produce different sound frequencies using a passive buzzer.
- Display scores and game information on an OLED.
- Increase game difficulty as players advance.
- Implement scoring, game-over, and restart functionality.

## Hardware Components
- **1× Arduino Nano** → Main microcontroller
- **4× LEDs** → Red, Green, Blue, Yellow
- **4× Push Buttons** → Player input
- **1× Passive Buzzer** → Audio feedback
- **1× 128×64 OLED Display** → Score and game information
- **4× Resistors** → LED current limiting
- **1× Breadboard** → Circuit assembly
- **Jumper Wires** → Electrical connections

## Pin Configuration

### LEDs and Buttons
- **Red**
  - LED → D2
  - Button → D3

- **Green**
  - LED → D4
  - Button → D5

- **Blue**
  - LED → D6
  - Button → D7

- **Yellow**
  - LED → D8
  - Button → D9

### Passive Buzzer
- Positive (+) → D10
- Negative (-) → GND

### OLED Display
- SDA → A4
- SCL → A5
- VCC → +5V
- GND → GND
Buttons use `INPUT_PULLUP`, so each button connects its input pin to GND when pressed.

## Software Requirements
### Development Environment
- Arduino IDE
- Arduino Nano 

### Required Libraries
- `Wire.h` → I2C communication
- `Adafruit_GFX.h` → Graphics and text rendering
- `Adafruit_SSD1306.h` → OLED display control
The Adafruit libraries can be installed through the **Arduino IDE Library Manager**.

## How the Game Works
### 1. Starting the Game
When the Arduino powers on, the OLED displays:
```text
SIMON
Press any button
```
Pressing any button starts a new game with a randomly generated sequence.

### 2. Displaying the Sequence
The Arduino flashes LEDs in a random order.
Each LED produces a unique sound through the buzzer.
The player must memorize the sequence before attempting to repeat it.

### 3. Player Input
After the sequence finishes, the player repeats the pattern using the four push buttons.
Each button activates its corresponding LED and buzzer sound.

### 4. Scoring System
When the player successfully repeats the entire sequence:
- Score increases by **1 point**.
- Round number increases by **1**.
- One new color is added to the sequence.
- LED playback becomes faster.

### 5. Increasing Difficulty
The LED playback becomes progressively faster as the player advances.
- **Round 1** → 600 ms
- **Round 5** → 520 ms
- **Round 10** → 420 ms
- **Round 15** → 320 ms
- **Round 20** → 220 ms
- **Round 21+** → 200 ms
The LED illumination time decreases by **20 milliseconds per round** until reaching a minimum of **200 milliseconds**.
There is also a fixed **180 ms pause** between LED flashes.

### 6. Game Over
If the player presses an incorrect button, the game ends.
The OLED displays:
```text
GAME OVER
Press to restart
Score: XX
```
The final score remains visible until the player presses another button.

### 7. Restarting
Pressing any button after Game Over:
- Resets the score to zero.
- Resets the round number to one.
- Generates a new random sequence.
- Starts a new game.

## Buzzer Frequencies
Each LED is assigned a unique frequency using the Arduino `tone()` function.
- **Red** → 330 Hz (E4)
- **Green** → 392 Hz (G4)
- **Blue** → 440 Hz (A4)
- **Yellow** → 523 Hz (C5)


## Competition Rules
This Simon Says game is designed for a **12-minute memory challenge competition**.
Each participant has their own Arduino-based Simon Says game.

### Rules
1. All participants begin when the 12-minute timer starts.
2. Players attempt to complete as many rounds as possible.
3. A wrong button ends the current game.
4. Players may restart and attempt to improve their score.
5. Players must show their score to an organizer before restarting.
6. Unverified scores do not count.
7. Only completed rounds before the timer expires count.
8. The participant with the highest verified score wins.

## Getting Started
### Step 1: Assemble the Circuit
Connect the LEDs, buttons, buzzer, and OLED according to the pin configuration.

### Step 2: Install Arduino IDE
Download the [Arduino IDE](https://www.arduino.cc/en/software).

### Step 3: Install Libraries
Open the Arduino IDE and navigate to:
**Sketch → Include Library → Manage Libraries**
Install:
- Adafruit GFX Library
- Adafruit SSD1306

### Step 4: Upload the Code
1. Connect the Arduino Nano to your computer.
2. Open the project's `.ino` file.
3. Select **Arduino Nano** under Tools → Board.
4. Select the correct processor and serial port.
5. Click **Upload**.

### Step 5: Start Playing
1. Press any button to start.
2. Watch the LED sequence.
3. Repeat the sequence using the buttons.
4. Continue completing rounds until a mistake is made.
