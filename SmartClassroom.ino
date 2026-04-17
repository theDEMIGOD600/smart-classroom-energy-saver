#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

// ---------------- OLED ----------------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// ---------------- DHT ----------------
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// ---------------- PINS ----------------
#define IR_IN 13
#define IR_OUT 14

#define LED1 25
#define LED2 26
#define LED3 27
#define LED4 32

#define LDR_PIN 34

// ---------------- VARIABLES ----------------
int peopleCount = 0;
bool inState = LOW;
bool outState = LOW;

// ---------------- SETUP ----------------
void setup() {
  Serial.begin(115200);

  pinMode(IR_IN, INPUT);
  pinMode(IR_OUT, INPUT);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);

  dht.begin();

  // OLED init
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED Failed");
    while(true);
  }

  display.setTextColor(WHITE);

  // -------- STARTUP SCREENS --------
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(15,20);
  display.println("WELCOME TO");
  display.setCursor(0,35);
  display.println("SMART CLASSROOM");
  display.display();
  delay(2000);

  display.clearDisplay();
  display.setCursor(20,30);
  display.println("Getting Ready...");
  display.display();
  delay(2000);

  display.clearDisplay();
  display.setCursor(20,30);
  display.println("SYSTEM IDLE");
  display.display();
  delay(1500);
}

// ---------------- LOOP ----------------
void loop() {

  // -------- IR ENTRY --------
  if(digitalRead(IR_IN) == LOW && inState == LOW) {
    peopleCount++;
    inState = HIGH;
  }
  if(digitalRead(IR_IN) == HIGH) {
    inState = LOW;
  }

  // -------- IR EXIT --------
  if(digitalRead(IR_OUT) == LOW && outState == LOW) {
    if(peopleCount > 0) peopleCount--;
    outState = HIGH;
  }
  if(digitalRead(IR_OUT) == HIGH) {
    outState = LOW;
  }

  // -------- READ SENSORS --------
  float temp = dht.readTemperature();
  int ldrValue = analogRead(LDR_PIN);

  // -------- AC LOGIC (UPDATED) --------
  String acStatus;

  if(peopleCount == 0) {
    acStatus = "OFF";
  }
  else {
    if(temp < 24) acStatus = "24C";
    else if(temp < 26) acStatus = "22C";
    else if(temp < 28) acStatus = "20C";
    else if(temp < 30) acStatus = "18C";
    else if(temp < 32) acStatus = "16C";
    else acStatus = "LOW";
  }

  // -------- LIGHT LOGIC --------
  int ledLevel = 0;

  if(ldrValue > 3000) ledLevel = 4;      // Dark
  else if(ldrValue > 2000) ledLevel = 3; // Dim
  else if(ldrValue > 1000) ledLevel = 2; // Normal
  else ledLevel = 1;                     // Bright

  // -------- SYSTEM OFF CONDITION --------
  if(peopleCount == 0) {
    ledLevel = 0;
  }

  digitalWrite(LED1, ledLevel >= 1);
  digitalWrite(LED2, ledLevel >= 2);
  digitalWrite(LED3, ledLevel >= 3);
  digitalWrite(LED4, ledLevel >= 4);

  // -------- OLED DISPLAY --------
  display.clearDisplay();

  // Title
  display.setTextSize(1);
  display.setCursor(0,0);
  display.println("SMART CLASSROOM");
  display.println("----------------");

  // Students
  display.setCursor(0,16);
  display.print("STUDENTS: ");
  display.println(peopleCount);

  // AC + Temp
  display.setCursor(0,28);
  display.print("AC:");
  display.print(acStatus);
  display.print("  T:");
  display.print(temp);
  display.println("C");

  // LDR
  display.setCursor(0,40);
  display.print("LUX: ");
  display.println(ldrValue);

  // Light bar
  display.setCursor(0,50);
  display.print("LIGHT: [");
  for(int i=0;i<4;i++){
    if(i < ledLevel) display.print((char)219); // █
    else display.print(" ");
  }
  display.println("]");

  // Status
  display.setCursor(0,58);
  if(peopleCount == 0)
    display.println("SYSTEM IDLE");
  else
    display.println("SYSTEM ACTIVE");

  display.display();

  delay(500);
}