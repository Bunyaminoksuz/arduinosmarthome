/*
 * AD8232 ECG Sensor Monitor
 * Arduino sketch for real-time ECG monitoring using AD8232 module
 * 
 * Author: Arduino Smart Home Project
 * Description: Monitors live ECG data and displays on serial monitor
 * with leads-off detection and error handling
 * 
 * Hardware Requirements:
 * - Arduino Uno/Nano
 * - AD8232 ECG Sensor Module
 * - ECG electrodes (3x)
 * 
 * Pin Connections:
 * - AD8232 OUTPUT -> Arduino A3 (analog input)
 * - AD8232 LO- -> Arduino D2 (leads-off negative)
 * - AD8232 LO+ -> Arduino D3 (leads-off positive) 
 * - AD8232 3.3V -> Arduino 3.3V
 * - AD8232 GND -> Arduino GND
 */

// Pin definitions for AD8232 ECG sensor
const int ECG_SIGNAL_PIN = A3;    // Analog pin for ECG signal
const int LO_MINUS_PIN = 2;       // Leads-off detection (negative)
const int LO_PLUS_PIN = 3;        // Leads-off detection (positive)

// ECG processing variables
int ecgValue = 0;                 // Raw ECG reading
bool leadsConnected = true;       // Leads connection status
unsigned long lastDisplayTime = 0; // For timing serial output
const unsigned long DISPLAY_INTERVAL = 50; // Display every 50ms (20Hz)

// Calibration and filtering
int baselineValue = 512;          // Baseline calibration (mid-scale for 10-bit ADC)
bool isCalibrated = false;        // Calibration status
int calibrationSamples = 0;       // Sample counter for calibration
long calibrationSum = 0;          // Sum for baseline calculation

void setup() {
  // Initialize serial communication
  Serial.begin(115200); // Higher baud rate for better real-time display
  
  // Configure pin modes
  pinMode(ECG_SIGNAL_PIN, INPUT);
  pinMode(LO_MINUS_PIN, INPUT);
  pinMode(LO_PLUS_PIN, INPUT);
  
  // Print header information
  Serial.println("===============================================");
  Serial.println("    AD8232 ECG Sensor Monitor - v1.0");
  Serial.println("===============================================");
  Serial.println();
  Serial.println("Initializing ECG sensor...");
  Serial.println();
  Serial.println("Pin Configuration:");
  Serial.print("- ECG Signal: A");
  Serial.println(ECG_SIGNAL_PIN - A0);
  Serial.print("- LO- (Leads Off -): D");
  Serial.println(LO_MINUS_PIN);
  Serial.print("- LO+ (Leads Off +): D");
  Serial.println(LO_PLUS_PIN);
  Serial.println();
  
  // Wait for sensor stabilization
  Serial.println("Sensor stabilizing... Please wait 3 seconds");
  delay(3000);
  
  // Perform baseline calibration
  performBaselineCalibration();
  
  Serial.println("===============================================");
  Serial.println("ECG Monitor Ready - Connect electrodes now");
  Serial.println("===============================================");
  Serial.println("Format: Timestamp(ms) | ECG_Value | Status");
  Serial.println("-----------------------------------------------");
}

void loop() {
  // Check leads-off detection
  checkLeadsConnection();
  
  // Read ECG signal only if leads are connected
  if (leadsConnected) {
    // Read the ECG signal
    ecgValue = analogRead(ECG_SIGNAL_PIN);
    
    // Display ECG data at specified interval
    if (millis() - lastDisplayTime >= DISPLAY_INTERVAL) {
      displayECGData();
      lastDisplayTime = millis();
    }
  } else {
    // Display leads-off message
    if (millis() - lastDisplayTime >= 500) { // Show message every 500ms
      Serial.println("! LEADS OFF - Please check electrode connections");
      lastDisplayTime = millis();
    }
  }
  
  // Small delay to prevent overwhelming the serial port
  delay(5);
}

void checkLeadsConnection() {
  // Read leads-off detection pins
  // Both pins should be LOW when leads are properly connected
  bool loMinus = digitalRead(LO_MINUS_PIN);
  bool loPlus = digitalRead(LO_PLUS_PIN);
  
  // Leads are connected when both LO pins are LOW
  leadsConnected = (!loMinus && !loPlus);
}

void performBaselineCalibration() {
  Serial.println("Performing baseline calibration...");
  Serial.println("Please ensure electrodes are connected but patient is relaxed");
  
  calibrationSum = 0;
  calibrationSamples = 0;
  
  // Collect samples for baseline calculation
  for (int i = 0; i < 100; i++) {
    // Only calibrate if leads are connected
    checkLeadsConnection();
    if (leadsConnected) {
      int reading = analogRead(ECG_SIGNAL_PIN);
      calibrationSum += reading;
      calibrationSamples++;
      delay(50);
      
      // Show progress
      if (i % 20 == 0) {
        Serial.print("Calibration progress: ");
        Serial.print((i * 100) / 100);
        Serial.println("%");
      }
    } else {
      Serial.println("Leads disconnected during calibration - retrying...");
      i--; // Retry this sample
      delay(100);
    }
  }
  
  // Calculate baseline if we have samples
  if (calibrationSamples > 0) {
    baselineValue = calibrationSum / calibrationSamples;
    isCalibrated = true;
    Serial.print("Baseline calibration complete: ");
    Serial.println(baselineValue);
  } else {
    Serial.println("Calibration failed - using default baseline");
    baselineValue = 512; // Default mid-scale value
    isCalibrated = false;
  }
  
  Serial.println();
}

void displayECGData() {
  // Calculate adjusted ECG value (remove baseline)
  int adjustedECG = ecgValue - baselineValue;
  
  // Create timestamp
  unsigned long timestamp = millis();
  
  // Format: Timestamp | Raw_Value | Adjusted_Value | Visual_Bar
  Serial.print(timestamp);
  Serial.print(" | ");
  Serial.print(ecgValue);
  Serial.print(" | ");
  Serial.print(adjustedECG);
  Serial.print(" | ");
  
  // Create a simple visual representation
  createVisualECG(adjustedECG);
  
  // Add status indicators
  if (!isCalibrated) {
    Serial.print(" [UNCALIBRATED]");
  }
  
  Serial.println();
}

void createVisualECG(int adjustedValue) {
  // Create a simple bar chart representation
  // Scale the value to fit in a reasonable range for display
  int scaledValue = adjustedValue / 4; // Scale down for display
  
  // Limit range for display
  if (scaledValue > 20) scaledValue = 20;
  if (scaledValue < -20) scaledValue = -20;
  
  // Create the visual bar
  if (scaledValue == 0) {
    Serial.print("|");
  } else if (scaledValue > 0) {
    // Positive values - show bars to the right
    Serial.print("|");
    for (int i = 0; i < scaledValue; i++) {
      Serial.print("=");
    }
    Serial.print(">");
  } else {
    // Negative values - show bars to the left
    Serial.print("<");
    for (int i = 0; i < -scaledValue; i++) {
      Serial.print("=");
    }
    Serial.print("|");
  }
}

// Function to print diagnostic information (call manually via serial commands if needed)
void printDiagnostics() {
  Serial.println("\n=== ECG SENSOR DIAGNOSTICS ===");
  Serial.print("Baseline Value: ");
  Serial.println(baselineValue);
  Serial.print("Calibration Status: ");
  Serial.println(isCalibrated ? "CALIBRATED" : "NOT CALIBRATED");
  Serial.print("Leads Connected: ");
  Serial.println(leadsConnected ? "YES" : "NO");
  Serial.print("LO- Pin State: ");
  Serial.println(digitalRead(LO_MINUS_PIN) ? "HIGH" : "LOW");
  Serial.print("LO+ Pin State: ");
  Serial.println(digitalRead(LO_PLUS_PIN) ? "HIGH" : "LOW");
  Serial.print("Current ECG Reading: ");
  Serial.println(analogRead(ECG_SIGNAL_PIN));
  Serial.println("==============================\n");
}