# Sample ECG Serial Monitor Output

Below is an example of what you would see in the Arduino IDE Serial Monitor when running the AD8232 ECG sensor:

```
===============================================
    AD8232 ECG Sensor Monitor - v1.0
===============================================

Initializing ECG sensor...

Pin Configuration:
- ECG Signal: A3
- LO- (Leads Off -): D2
- LO+ (Leads Off +): D3

Sensor stabilizing... Please wait 3 seconds
Performing baseline calibration...
Calibration progress: 0%
Calibration progress: 20%
Calibration progress: 40%
Calibration progress: 60%
Calibration progress: 80%
Baseline calibration complete: 517

===============================================
ECG Monitor Ready - Connect electrodes now
===============================================
Format: Timestamp(ms) | ECG_Value | Status
-----------------------------------------------
5234 | 523 | 6 | |=>
5284 | 498 | -19 | <==|
5334 | 515 | -2 | |
5384 | 529 | 12 | |===>
5434 | 541 | 24 | |=====>
5484 | 556 | 39 | |========>
5534 | 578 | 61 | |============>
5584 | 592 | 75 | |===============>
5634 | 601 | 84 | |=================>
5684 | 595 | 78 | |================>
5734 | 580 | 63 | |=============>
5784 | 558 | 41 | |========>
5834 | 532 | 15 | |===>
5884 | 509 | -8 | <=|
5934 | 498 | -19 | <==|
5984 | 492 | -25 | <===|
6034 | 495 | -22 | <=|
6084 | 504 | -13 | <=|
6134 | 513 | -4 | |
6184 | 518 | 1 | |
6234 | 520 | 3 | |
6284 | 519 | 2 | |
6334 | 517 | 0 | |
6384 | 516 | -1 | |
6434 | 518 | 1 | |
6484 | 519 | 2 | |
6534 | 521 | 4 | |
6584 | 524 | 7 | |=>
6634 | 531 | 14 | |===>
6684 | 545 | 28 | |======>
6734 | 567 | 50 | |==========>
6784 | 589 | 72 | |==============>
6834 | 603 | 86 | |=================>
6884 | 608 | 91 | |==================>
6934 | 599 | 82 | |================>
6984 | 582 | 65 | |=============>
7034 | 559 | 42 | |========>
7084 | 534 | 17 | |===>
7134 | 511 | -6 | |
7184 | 495 | -22 | <=|
7234 | 488 | -29 | <===|
7284 | 490 | -27 | <===|
7334 | 499 | -18 | <=|
7384 | 510 | -7 | |
7434 | 516 | -1 | |

! LEADS OFF - Please check electrode connections
! LEADS OFF - Please check electrode connections
! LEADS OFF - Please check electrode connections

7934 | 520 | 3 | |
7984 | 522 | 5 | |=>
8034 | 518 | 1 | |
8084 | 515 | -2 | |
8134 | 517 | 0 | |
```

## Output Explanation

### Header Section
- Shows initialization messages and pin configuration
- Displays calibration progress during startup
- Indicates when the system is ready for monitoring

### Data Format
Each line contains:
- **Timestamp**: Milliseconds since Arduino started
- **Raw Value**: Direct ADC reading (0-1023 range) 
- **Adjusted Value**: ECG signal after baseline removal
- **Visual Bar**: ASCII representation of ECG waveform
  - `|` = baseline (zero point)
  - `=>` = positive deflection (R-wave peak)
  - `<=` = negative deflection (S-wave)
  - Length indicates signal amplitude

### ECG Pattern Recognition
The sample above shows typical ECG characteristics:
- **Baseline periods**: Small values around zero
- **R-wave peaks**: Large positive spikes (QRS complex)
- **S-wave dips**: Negative deflections after peaks
- **Recovery**: Return to baseline between heartbeats

### Error Handling
- `! LEADS OFF` messages appear when electrodes are disconnected
- Normal readings resume when connection is restored

### Typical Patterns
- **Normal heart rate**: ~60-100 BPM (1-1.7 second intervals between peaks)
- **Signal amplitude**: Usually 50-200 units after baseline correction
- **Noise levels**: Should be minimal with proper electrode contact

This real-time display allows immediate visualization of heart rhythm and detection of irregularities for educational purposes.