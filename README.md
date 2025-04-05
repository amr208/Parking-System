# Ultrasonic Distance Measurement System

## Description
This project implements an ultrasonic distance measurement system using an ATmega32 microcontroller. The system measures distances using an HC-SR04 ultrasonic sensor and provides visual and audible feedback through LEDs and a buzzer based on the measured distance.

## Features
- **Distance Measurement**: Accurate distance measurement from 2cm to 400cm
- **Visual Feedback**: RGB LED indicates different distance ranges
- **Audible Alarm**: Buzzer activates when object is too close (≤5cm)
- **LCD Display**: Shows real-time distance measurements in centimeters
- **Multiple Alert Levels**: Progressive warning system as object approaches

## Hardware Components
- **Microcontroller**: ATmega32
- **Sensors**:
  - HC-SR04 Ultrasonic Sensor
- **Output Devices**:
  - RGB LED
  - Buzzer
  - 16x2 LCD Display
- **Other**: Input Capture Unit (ICU) for precise timing measurements

## System Architecture
### Main Components
1. **Ultrasonic Sensor Driver**:
   - Generates trigger pulse
   - Measures echo pulse width using ICU
   - Calculates distance in centimeters

2. **ICU Driver**:
   - Captures rising and falling edges of echo signal
   - Measures time between edges with high precision

3. **Feedback System**:
   - RGB LED for visual distance indication
   - Buzzer for close-proximity warning
   - LCD for numerical distance display

## Distance Ranges and Responses
| Distance Range | LED State          | Buzzer | LCD Message |
|----------------|--------------------|--------|-------------|
| ≥20cm         | All OFF            | OFF    | -           |
| 16-20cm       | Red ON             | OFF    | -           |
| 11-16cm       | Red + Green ON     | OFF    | -           |
| 6-11cm        | All LEDs ON        | OFF    | -           |
| ≤5cm          | Blinking All LEDs  | ON     | "STOP"      |

## Technical Specifications
- **Measurement Principle**: Time-of-flight calculation
- **Resolution**: ~1cm
- **Update Rate**: Continuous measurement cycle
- **ICU Configuration**:
  - Rising/Falling edge detection
  - No prescaling for maximum timing resolution
- **PWM**: Not used in this implementation

## Key Functions
1. **`Ultrasonic_edgeProcessing()`**:
   - ICU interrupt service routine
   - Captures echo pulse timing
   - Manages edge detection transitions

2. **Main Control Loop**:
   - Triggers new measurements
   - Updates LCD display
   - Controls LED and buzzer outputs
   - Handles distance-based logic

## Usage
1. Power on the system
2. The LCD will display real-time distance measurements
3. LEDs will illuminate based on object distance:
   - Green: Safe distance
   - Yellow: Caution
   - Red: Warning
4. Buzzer sounds when object is within 5cm
5. "STOP" message appears at critical distance

## Safety Features
- Clear visual indicators at all distance ranges
- Audible warning at dangerous proximity
- Explicit "STOP" warning on LCD

## Expansion Possibilities
- Add wireless data transmission
- Implement distance logging
- Create adjustable threshold settings
- Add temperature compensation for improved accuracy

## Dependencies
- AVR Libc
- Standard C libraries
- Custom drivers for:
  - LCD
  - ICU
  - Ultrasonic sensor
  - GPIO

## Files
- `Main_App.c`: Main application logic
- Peripheral drivers:
  - LCD, ICU, Ultrasonic, Buzzer, LED
- Header files:
  - `std_types.h`, `common_macros.h`

## Important Notes
- System requires precise 8MHz or 16MHz clock
- Ultrasonic sensor must have clear line of sight
- Measurements may be affected by temperature/humidity
- Ensure proper power supply for stable operation
