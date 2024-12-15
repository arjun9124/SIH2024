// Include necessary libraries
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// OLED display settings
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET -1    // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< OLED I2C address

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Temperature sensor settings
#define ONE_WIRE_BUS 4
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// Hydrogen sensor settings
#define AOUTpin A0 // Analog pin for hydrogen sensor
#define DOUTpin 8  // Digital pin for hydrogen sensor
#define ledPin 13  // LED pin

int limit = 10;
int value;
float background = 0;
void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Initialize sensors
  sensors.begin();
  pinMode(DOUTpin, INPUT);
  pinMode(ledPin, OUTPUT);

  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("Initializing..."));
  display.display();
  delay(2000);
}

void loop() {
  // Read temperature from Dallas sensor
  sensors.requestTemperatures();
  float temperature = sensors.getTempCByIndex(0);

  // Read hydrogen concentration
  value = analogRead(AOUTpin);
  float concentration = value - background;

  // Read digital limit
  limit = digitalRead(DOUTpin);

  // Display data on OLED
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print(F("Temp: "));
  display.print(temperature);
  display.println(F(" C"));
  display.print(F("H2 Conc: "));
  display.print(concentration);
  display.println(F(" ppm"));
  display.print(F("Limit: "));
  display.println(limit == HIGH ? F("HIGH") : F("LOW"));
  display.display();

  // Print data to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" C, H2 Concentration: ");
  Serial.print(concentration);
  Serial.print(" %, Limit: ");
  Serial.println(limit == HIGH ? "HIGH" : "LOW");

  // Send data to Serial Plotter
  Serial.print(temperature);
  Serial.print(",");
  Serial.println(concentration);

  delay(1000); // Wait 1 second
}
