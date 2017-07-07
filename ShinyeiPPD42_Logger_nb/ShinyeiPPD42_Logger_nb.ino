


/*
  Interface to Shinyei Model PPD42NS Particle Sensor
  Program by Christopher Nafis
  Written April 2012

  http://www.seeedstudio.com/depot/grove-dust-sensor-p-1050.html
  http://www.sca-shinyei.com/pdf/PPD42NS.pdf

  JST Pin 1 (Black Wire)  => Arduino GND
  JST Pin 3 (Red wire)    => Arduino 5VDC
  JST Pin 4 (Yellow wire) => Arduino Digital Pin 8
*/
#include "DHT.h"
#include "RTClib.h"
#include <SPI.h>
#include "SdFat.h"
#include <Wire.h>

// SD chip select pin.  Be sure to disable any other SPI devices such as Enet.
const uint8_t chipSelect = 4;

// Interval between data records in milliseconds.
const uint32_t SAMPLE_INTERVAL_MS = 30000;

// Log file base name.  Must be six characters or less.
#define FILE_BASE_NAME "data"

//==============================================================================
// Logging Variables
// File system object.
SdFat sd;

// Log file.
SdFile file;

// Time in millis for next data record.
uint32_t logTime;

// RTC object
RTC_PCF8523 RTC;

//==============================================================================
//  Variables for Shinyei PPD42
int shinPin = 5;
unsigned long duration;
unsigned long starttime;
unsigned long sampletime_ms = 30000;
unsigned long lowpulseoccupancy = 0;
float ratio = 0;
float concentration = 0;

//==============================================================================
// DHT22 Variables
const int DHTPIN = 6;
DHT dht(DHTPIN, DHT22);

//==============================================================================
// Blink
int RXLED = 17;

void blink(int i) {
  for (int j = 0; j < i; j++) {
    digitalWrite(RXLED, LOW);
    delay(150);
    digitalWrite(RXLED, HIGH);
    delay(150);
  }
}

//==============================================================================
// User functions.  Edit writeHeader() and logData() for your requirements.
//------------------------------------------------------------------------------
// Write data header.
void writeHeader() {
  file.print(F("time,"));
  file.print(F("temp,"));
  file.print(F("humidity,"));
  file.print(F("ug/m3,"));
  file.print(F("ratio"));
  file.println();
}

//------------------------------------------------------------------------------
// Log a data record.
void logData() {

  // Write data to file.  Start with log time
  DateTime now = RTC.now();
  int year = now.year();
  int month = now.month();
  int day = now.day();
  int hour = now.hour();
  int minute = now.minute();

  char datetime[20] = "";
  sprintf(datetime, "%.4d-%.2d-%.2d %.2d:%.2d", year, month, day, hour, minute);

  float temp = dht.readTemperature();
  float humid = dht.readHumidity();

  // Calculate Shinyei PM25 duty cycle and concentration.
  ratio = lowpulseoccupancy / (sampletime_ms * 10.0); // Integer percentage 0=>100
  concentration = (0.01237 * ratio) + 1.5;

  file.print(datetime);
  file.print(F(", "));

  //logTemp();
  file.print(temp);
  file.print(F(", "));
  file.print(humid);
  file.print(F(", "));

  // Log PM
  file.print(ratio);
  file.print(F(", "));
  file.print(concentration);
  lowpulseoccupancy = 0;

  file.println();

  // Write data to Serial ///////////////
  Serial.print(datetime);
  Serial.print(F(", "));

  //logTemp();
  Serial.print(temp);
  Serial.print(F(", "));
  Serial.print(humid);
  Serial.print(F(", "));
  
  // Log PM
  Serial.print(ratio);
  Serial.print(F(", "));
  Serial.print(concentration);
  Serial.println();
}

//==============================================================================
// Error messages stored in flash.
#define error(msg) sd.errorHalt(F(msg))

//------------------------------------------------------------------------------
void setup() {

  pinMode(shinPin, INPUT);
  pinMode(RXLED, OUTPUT);
  TXLED0;  // Turn off the TX LED.

  Wire.begin();

  if (!RTC.begin()) {
    file.println("RTC failed");
  }
  const uint8_t BASE_NAME_SIZE = sizeof(FILE_BASE_NAME) - 1;
  char fileName[13] = FILE_BASE_NAME "00.txt";

  Serial.begin(9600);
  // Wait for USB Serial
  delay(1000);

  // Initialize at the highest speed supported by the board that is
  // not over 50 MHz. Try a lower speed if SPI errors occur.
  if (!sd.begin(chipSelect, SD_SCK_MHZ(50))) {
    sd.initErrorHalt();
  }

  // Find an unused file name.
  if (BASE_NAME_SIZE > 6) {
    error("FILE_BASE_NAME too long");
  }
  while (sd.exists(fileName)) {
    if (fileName[BASE_NAME_SIZE + 1] != '9') {
      fileName[BASE_NAME_SIZE + 1]++;
    } else if (fileName[BASE_NAME_SIZE] != '9') {
      fileName[BASE_NAME_SIZE + 1] = '0';
      fileName[BASE_NAME_SIZE]++;
    } else {
      error("Can't create file name");
    }
  }
  if (!file.open(fileName, O_CREAT | O_WRITE | O_EXCL)) {
    error("file.open");
  }
  // Read any Serial data.
  do {
    delay(10);
  } while (Serial.available() && Serial.read() >= 0);

  Serial.print(F("Logging to: "));
  Serial.println(fileName);


  writeHeader();
  dht.begin();

 // Blink for joy, things are working.
  blink(10);
  
  // Start on a multiple of the sample interval.
  // This will only be useful if we use a button and an ISR
  logTime = millis() / SAMPLE_INTERVAL_MS + 1;
  logTime *= SAMPLE_INTERVAL_MS;


}

void loop() {
  // Time for next record.
  logTime += SAMPLE_INTERVAL_MS;

  // Wait for log time.
  int32_t diff;
  do {
    // Read signal from Shinyei for duration of sampletime_ms.
    duration = pulseIn(shinPin, LOW);
    lowpulseoccupancy = lowpulseoccupancy + duration;

    diff = millis() - logTime;
  } while (diff < 0);

  // Check for data rate too high.
  if (diff > 2000) {
    error("Missed data record");
  }

  logData();

  // Force data to SD and update the directory entry to avoid data loss.
  if (!file.sync() || file.getWriteError()) {
    error("write error");
  }
  delay(10);
  blink(1);
}
