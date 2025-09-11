# AD8232 ECG Sensor Integration Guide

## Overview

This documentation provides complete instructions for integrating the AD8232 ECG sensor module with Arduino to monitor live ECG (electrocardiogram) data. The AD8232 is a specialized analog front-end designed for ECG and other biopotential measurement applications.

## Hardware Requirements

### Components Needed
- Arduino Uno/Nano/Pro Mini
- AD8232 ECG Sensor Module
- ECG electrodes (3x disposable gel electrodes)
- Jumper wires
- Breadboard (optional)
- Computer with Arduino IDE

### AD8232 Module Specifications
- **Supply Voltage**: 3.3V
- **Operating Current**: 170µA (typical)
- **Gain**: 1100V/V (configurable)
- **Bandwidth**: 0.5Hz to 40Hz (configurable)
- **Output**: Single-ended analog signal
- **Lead-off Detection**: Built-in with digital outputs

## Pin Connections

### Arduino to AD8232 Wiring

```
AD8232 Module    |    Arduino Board
-----------------|------------------
GND              |    GND
3.3V             |    3.3V
OUTPUT           |    A3 (Analog Pin)
LO-              |    D2 (Digital Pin)
LO+              |    D3 (Digital Pin)
```

### Connection Diagram

```
    Arduino Uno                    AD8232 Module
    +---------+                    +-------------+
    |         |                    |             |
    |     3.3V|-------- 3.3V ------|3.3V         |
    |      GND|-------- GND -------|GND          |
    |      A3 |-------- SIGNAL ----|OUTPUT       |
    |      D2 |-------- LO- -------|LO-          |
    |      D3 |-------- LO+ -------|LO+          |
    |         |                    |             |
    +---------+                    +-------------+
                                           |
                                    Electrode Pads
                                    +-------------+
                                    |    RA (R)   |
                                    |    LA (L)   |  
                                    |   RL (Ref)  |
                                    +-------------+
```

## Electrode Placement

### Standard 3-Lead ECG Configuration

1. **RA (Right Arm)** - Connect to right wrist or below right collarbone
2. **LA (Left Arm)** - Connect to left wrist or below left collarbone  
3. **RL (Reference/Ground)** - Connect to right leg, right ankle, or right hip

### Electrode Connection to AD8232
- **Red wire** → RA electrode
- **Yellow wire** → LA electrode
- **Green wire** → RL electrode (reference/ground)

### Placement Tips
- Clean skin with alcohol before applying electrodes
- Ensure good electrode contact with skin
- Avoid placing electrodes over bone or muscle
- For best results, place on relatively flat areas of skin

## Software Implementation

### Main Features
- **Real-time ECG monitoring** at 20Hz sampling rate
- **Leads-off detection** with automatic error handling
- **Baseline calibration** for accurate readings
- **Visual representation** of ECG waveform in serial monitor
- **Diagnostic information** for troubleshooting

### Key Functions

#### `setup()`
- Initializes serial communication at 115200 baud
- Configures pin modes for ECG signal and leads-off detection
- Performs sensor stabilization and baseline calibration

#### `loop()`
- Continuously monitors leads connection
- Reads ECG signal when leads are properly connected
- Displays real-time data at 20Hz refresh rate
- Handles error conditions with appropriate messages

#### `checkLeadsConnection()`
- Monitors LO+ and LO- pins for electrode disconnection
- Returns connection status for error handling

#### `performBaselineCalibration()`
- Calculates baseline ECG value for accurate measurements
- Requires stable connection during calibration period
- Improves signal quality and removes DC offset

## Usage Instructions

### 1. Hardware Setup
1. Wire the AD8232 module to Arduino as shown in the connection diagram
2. Upload the `ecg_ad8232_monitor.ino` sketch to your Arduino
3. Connect ECG electrodes to the AD8232 module

### 2. Patient Preparation
1. Clean electrode placement areas with alcohol
2. Apply electrodes according to the placement guide
3. Ensure patient is relaxed and comfortable
4. Minimize movement during monitoring

### 3. Software Operation
1. Open Arduino IDE Serial Monitor
2. Set baud rate to **115200**
3. Reset Arduino to start fresh calibration
4. Wait for "ECG Monitor Ready" message
5. Observe real-time ECG data stream

### 4. Reading the Output

The serial monitor displays data in this format:
```
Timestamp(ms) | Raw_Value | Adjusted_Value | Visual_Bar
12350 | 520 | 8 | |===>
12400 | 485 | -27 | <===|
12450 | 512 | 0 | |
```

- **Timestamp**: Milliseconds since Arduino start
- **Raw_Value**: Direct ADC reading (0-1023)
- **Adjusted_Value**: Baseline-corrected ECG signal
- **Visual_Bar**: Simple waveform visualization

## Troubleshooting

### Common Issues

#### "LEADS OFF" Message
- **Cause**: Electrodes not properly connected
- **Solution**: Check electrode adhesion, wire connections, and skin contact

#### Noisy Signal
- **Cause**: Poor electrode contact, movement, or electrical interference
- **Solution**: 
  - Ensure proper electrode placement
  - Minimize patient movement
  - Keep away from electrical devices
  - Check wire connections

#### Flat/No Signal
- **Cause**: Incorrect wiring or faulty module
- **Solution**:
  - Verify pin connections
  - Check power supply (3.3V)
  - Test with known good electrodes

#### Calibration Failed
- **Cause**: Leads disconnected during calibration
- **Solution**: Ensure stable electrode connection before starting

### Diagnostic Commands

The sketch includes diagnostic functions for troubleshooting:
- Monitor LO+ and LO- pin states
- Check baseline calibration values
- Verify raw ADC readings

## Technical Specifications

### Signal Processing
- **ADC Resolution**: 10-bit (0-1023)
- **Sampling Rate**: 20Hz (50ms intervals)
- **Baseline Correction**: Automatic during startup
- **Lead-off Detection**: Hardware-based with digital outputs

### Performance Characteristics
- **Bandwidth**: Suitable for ECG monitoring (0.5-40Hz)
- **Gain**: High gain amplification for small biopotential signals
- **Noise Rejection**: Common-mode rejection for clean signals

## Safety Considerations

⚠️ **IMPORTANT SAFETY NOTES** ⚠️

1. **Not for Medical Use**: This is for educational/experimental purposes only
2. **No Isolation**: Direct connection to Arduino - not medically isolated
3. **Battery Operation**: Use battery-powered Arduino for patient safety
4. **Supervision Required**: Always have qualified supervision for ECG monitoring
5. **Emergency Protocols**: Have proper medical emergency procedures in place

## Advanced Features

### Customization Options

#### Adjust Sampling Rate
Change `DISPLAY_INTERVAL` constant:
```cpp
const unsigned long DISPLAY_INTERVAL = 25; // 40Hz sampling
```

#### Modify Visual Scale
Adjust scaling in `createVisualECG()` function:
```cpp
int scaledValue = adjustedValue / 2; // More sensitive
```

#### Extended Monitoring
Add data logging to SD card or wireless transmission for extended monitoring applications.

## References and Resources

- [AD8232 Datasheet](https://www.analog.com/media/en/technical-documentation/data-sheets/AD8232.pdf)
- [ECG Electrode Placement Guidelines](https://www.alivecor.com/guide-to-ecg-electrode-placement/)
- [Arduino Analog Input Documentation](https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/)

## License

This project is open source and available under the MIT License. See the main repository LICENSE file for details.