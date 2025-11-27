# Drift-bandit-fura 🏎️💨

**Drift-bandit-fura** is a remote-controlled drift car project developed for a university assignment. The system consists of a custom-built vehicle and a handheld remote pilot, both powered by the **Raspberry Pi Pico 2 W**. The car features wireless control, high-performance brushless drift mechanics, a custom lighting system, and integrated sound effects.



## 📋 Features

- **Wireless Communication**: Utilizes the Raspberry Pi Pico 2 W (RP2350) for robust low-latency control between the pilot and the car.
- **Brushless Power**: High-speed drifting capabilities using a Brushless DC motor and ESC.
- **Interactive Lighting**: Remotely controlled Headlights, Brake Lights, and Underglow.
- **On-Demand Audio**: Sound effects triggered manually via remote buttons.
- **Dual-Role Architecture**: Single codebase supporting both Pilot and Car modes via configuration.

## 🛠️ Hardware Requirements

### 🚗 Car Unit
- **Microcontroller**: Raspberry Pi Pico 2 W
- **Drive System**: 
  - 1x Brushless DC Motor (BLDC)
  - 1x ESC (Electronic Speed Controller)
- **Steering**: 1x Servo Motor
- **Lighting**:
    - White LEDs (Headlights)
    - Red LEDs (Brake Lights)
    - LED Strip / NeoPixels (Underglow)
- **Audio**: Speaker or Buzzer (via PWM or Amplifier)
- **Power**: Li-Po Battery (2S or 3S)

### 🎮 Pilot Unit (Remote)
- **Microcontroller**: Raspberry Pi Pico 2 W
- **Input**: 
  - Analog Joystick (Steering & Throttle)
  - Push Buttons (Light toggles & Sound triggers)
- **Power**: Portable power bank or Li-Ion battery

## 📂 Project Structure

```text
├── include/        # Header files and helper functions
├── src/            # Main source code for Car and Pilot logic
├── config.hpp      # Configuration: Pin definitions, WiFi settings, and Role selection
├── CMakeLists.txt  # CMake build configuration
└── LICENSE         # MIT License

⚙️ Installation & Build

Prerequisites

    CMake (3.13+)

    GCC for Arm Embedded Processors (arm-none-eabi-gcc)

    Raspberry Pi Pico SDK (Version 2.0.0+ required for Pico 2 support)

Building the Project

    Clone the repository:
    Bash

git clone [https://github.com/Weno1/Drift-bandit-fura.git](https://github.com/Weno1/Drift-bandit-fura.git)
cd Drift-bandit-fura

Configure the Role: Open config.hpp to define whether you are compiling for the Car or the Pilot.
C++

// config.hpp
#define ROLE_CAR      // Uncomment for Car firmware
// #define ROLE_PILOT // Uncomment for Pilot firmware

Build:
Bash

    mkdir build
    cd build
    cmake ..
    make

    Flash the Firmware:

        Hold the BOOTSEL button on your Pico 2 W while plugging it in.

        Drag and drop the generated .uf2 file onto the RPI-RP2 drive.

🔌 Pin Configuration

Define specific pins in config.hpp. Typical setup:
Component	Role	Description
ESC Signal	Car	PWM Output for Brushless Motor
Steering Servo	Car	PWM Output for Steering
Headlights	Car	GPIO Output (White LEDs)
Brake Lights	Car	GPIO Output (Red LEDs)
Underglow	Car	GPIO/PWM Output (LED Strip)
Speaker	Car	PWM Audio Output
Joystick X/Y	Pilot	ADC Inputs (Steering/Throttle)
Buttons	Pilot	GPIO Inputs (Pull-up)

🚀 Usage

    Power On: Switch on the Pilot remote first, then the Car.

    ESC Arming: Wait for the ESC initialization beeps (ensure throttle is neutral).

    Controls:

        Joystick: Controls acceleration and steering.

        Button [1]: Toggle Headlights & Underglow.

        Button [2]: Toggle Brake Lights (or Manual Brake).

        Button [3]: Play Sound Effect / Horn.

    Drift: Use the burst of brushless power to initiate a slide and counter-steer to maintain the drift.

📜 License

This project is licensed under the MIT License - see the LICENSE file for details.