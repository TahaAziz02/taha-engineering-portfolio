/*
  Smart Cooling System - Prototype Control Firmware

  Project Type:
  Internship engineering project / embedded cooling control system

  Description:
  Arduino Nano firmware for a CNC machine cooling control system. The system
  monitors pump-side temperature, allows the user to adjust a temperature
  threshold using a potentiometer, activates a relay-controlled coolant pump
  when the threshold is exceeded, checks for coolant flow using a flow sensor,
  and provides user feedback through a TM1637 4-digit display and buzzer.

  Documentation Note:
  This code represents an early/prototype version of the project firmware.
  The final system was completed and functional, but full final documentation
  was not archived because the project was completed before this portfolio was
  created.
*/


//4 segment display
#include <TM1637Display.h>

#define CLK_PIN 4    // Clock pin
#define DIO_PIN 5    // Data pin

TM1637Display display(CLK_PIN, DIO_PIN);

bool displayState = true;

//Blinking timing
const int blinkInterval = 100; // Blink interval in milliseconds
unsigned long previousTimeBlink = 0;
unsigned long blinkTimer = 0;
bool ledState = false;
unsigned long currentTime = 0;
int counter = 0; 

// Flow Sensor Delay
const int FlowInterval = 500; 
unsigned long FlowDelay = 0; 

//Temperature Sensor 
#include <OneWire.h> 
#include <DallasTemperature.h>

#define Room_Temp_PIN 11
#define Pump_Temp_PIN 12

OneWire onewire1(Room_Temp_PIN);
DallasTemperature sensors1(&onewire1); 
OneWire onewire2(Pump_Temp_PIN);
DallasTemperature sensors2(&onewire2);

float roomTemp = 0.0; 
float pumpTemp = 0.0; 

//Buzzer  
#define Buzz_PIN 10
#define Num_Of_Buzz 3
int beep_loop = 0;

const unsigned long buzzerOnTime = 1000;
const unsigned long buzzerOffTime = 500; 
boolean BuzzerArmed = true; 
unsigned long previousTime = 0; 

//Potentiometer 
#define Pot_PIN A0 

//Relay
#define Relay_PIN 8

//Button 
#define Button_PIN 6
int buttonVal; 

//Pump & Flow Sensor 
#include <stdbool.h>
#define PUMP 2 
int flowSensorState = LOW; 
bool pumpStatus = false; 
int pumpTrigger = HIGH; 
int flowState_Old; 
int flowState_New; 
int fluctNum;

//Flow Error Message 
const uint8_t letterE[] = {
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G   // "E"
};

const uint8_t letterR[] = {
  SEG_A | SEG_E | SEG_F   // "R"
};

const uint8_t letterF[] = {
  SEG_A | SEG_E | SEG_F | SEG_G   // "F"
};

const uint8_t letterL[] = {
  SEG_D| SEG_E | SEG_F    // "L"
};

const uint8_t letterO[] = { 
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F 
};

int pumpScan = 0; 
//POT data smoothing 
#define Hysteresis 1
int Set_Temp_New, Set_Temp_Old; 
const int NUM_READINGS = 5; // Number of readings to average
int readings[NUM_READINGS]; // Array to store the readings
int index = 0; // Current index in the readings array

void setup() {

  Serial.begin(9600);
  //Pin initialization
  pinMode(Buzz_PIN, OUTPUT); 
  digitalWrite(Buzz_PIN, LOW); 
  pinMode(Pot_PIN, INPUT);


  //Temperature Sensor Start-Up
  sensors1.begin(); 
  sensors2.begin(); 

  //Button Set up 
  pinMode(Button_PIN, INPUT); 
  digitalWrite(Button_PIN, HIGH); 

  //Set_Temp initialization 
  Set_Temp_New = SetTemp();
  Set_Temp_Old = Set_Temp_New; 

  // Set the brightness level (0-7, 0 being the dimmest)
  display.setBrightness(7);  

  //Relay Start-Up 
  //NOTE: Ensure that secondary circuit is connected to the NC (Normally Closed) terminal of the relay. 
  pinMode(Relay_PIN, OUTPUT);
  digitalWrite(Relay_PIN, LOW); 
  delay(10); 
}

void loop() { //MAIN LOOP
  sensors1.requestTemperatures(); 
  sensors2.requestTemperatures(); 
  roomTemp = sensors1.getTempCByIndex(0); 
  pumpTemp = sensors2.getTempCByIndex(0); 

  buttonVal = digitalRead(Button_PIN); 
  Set_Temp_New = SetTemp();
  Serial.println("Start"); 


  if (buttonVal == LOW) {
    counter = 0; 
    while (buttonVal == LOW && counter < 110) {
      delay(10);
      counter++;
      if (counter == 100) { 
        DisplaySetTemp(); 
      }
    }
  }  
  else if (SetTemp() < int(pumpTemp)) {  
    pumpScan++;  
    digitalWrite(Relay_PIN, pumpTrigger); //Turns on relay
    WarningBeep(); 
    if (pumpStatus != true || pumpScan >= 2) { 
      pumpScan = 0;
      if (Flow_Read() < 1) {
        Flow_Error(); 
        pumpStatus = false; 
        pumpTrigger = HIGH; //Keeps pump on (HIGH) or turns pump off (LOW) when failure 
        }
      else { 
        pumpStatus = true; 
        pumpTrigger = HIGH; 
        display.showNumberDec(pumpTemp, false); 
      }
    }
  }
  else {
    beep_loop = 0; 
    BuzzerArmed = true; 
    pumpStatus = false;
    digitalWrite(Relay_PIN, LOW); //Turns off relay
    digitalWrite(Buzz_PIN, LOW); 
    display.showNumberDec(pumpTemp, false); 
  } 

}

//Noise reduction from Potentiometer 
int SetTemp() {
  // Read the value from the potentiometer
  int potValue = map(analogRead(Pot_PIN), 0, 1024, roomTemp, 101);

  // Add the reading to the array
  readings[index] = potValue;

  // Move to the next index, wrapping around if necessary
  index = (index + 1) % NUM_READINGS;

  // Calculate the average of the readings
  int averageValue = 0;
  for (int i = 0; i < NUM_READINGS; i++) {
    averageValue += readings[i];
  }
  averageValue /= NUM_READINGS;

  if (averageValue >= roomTemp) {
    return averageValue; 
  }
  else { 
    return roomTemp; 
  }
}

 
//Displays new set temperature threshold 
void DisplaySetTemp () {
  while (true) {
    Serial.println("DisplaySetTemp"); 
    display.showNumberDec(SetTemp(), false);
    Set_Temp_Old = Set_Temp_New; 
    Set_Temp_New = SetTemp();
    // Update the display if it's turned on

    if (digitalRead(Button_PIN) == LOW) {
      counter = 0; 
      while (digitalRead(Button_PIN) == LOW && counter < 110) {
        Serial.print("DigitalRead2"); 
        Serial.print("\t");
        Serial.println(digitalRead(Button_PIN)); 
        DisplayBlink(); 
        delay(10);
        counter++;
        if (counter == 100) { 
          display.showNumberDec(pumpTemp, false); 
          return; 
        }
      }
    }
    DisplayBlink(); 
  }
}

void DisplayBlink() { 
unsigned long currentTime = millis();

    if (currentTime - previousTimeBlink >= blinkInterval) {
    previousTimeBlink = currentTime;
    ledState = !ledState;
      if (ledState) { 
        display.showNumberDec(SetTemp(), false);  
      }
      else {
        display.clear();   
      }
    }
}

void WarningBeep() {
  unsigned long currentTime = millis();
  static unsigned long previousTime = 0;
  static int beep_loop = 0;
  static bool buzzerState = LOW;

  if (BuzzerArmed) {
    if (currentTime - previousTime >= 500) {
      previousTime = currentTime;
      if (beep_loop < 3) {
        if (buzzerState == LOW) {
          digitalWrite(Buzz_PIN, HIGH);
          buzzerState = HIGH;
        } else {
          digitalWrite(Buzz_PIN, LOW);
          buzzerState = LOW;
          beep_loop++;
        }
      } else {
        BuzzerArmed = false;
      }
    }
  } else {
    digitalWrite(Buzz_PIN, LOW);
  }
}

//Displays Error Message
void Flow_Error() { 
  display.clear(); 
  display.setSegments(letterE, 1, 0);   // Display "E" on the first digit
  display.setSegments(letterR, 1, 1);   // Display "R" on the second digit
  display.setSegments(letterR, 1, 2);   // Display "F" on the fourth digit

  digitalWrite(Buzz_PIN, HIGH); 


  delay(1000); 

  digitalWrite(Buzz_PIN, LOW); 

  display.clear();   
  delay(1000);       

  display.setSegments(letterF, 1, 0);   // Display "E" on the first digit
  display.setSegments(letterL, 1, 1);   // Display "R" on the second digit
  display.setSegments(letterO, 1, 2);   // Display "F" on the fourth digit

  digitalWrite(Buzz_PIN, HIGH); 

  delay(1000);   

  digitalWrite(Buzz_PIN, LOW); 

  display.clear();   
  delay(1000);   

}

//Checks if flow in sensor
int Flow_Read() { 
  fluctNum = 0;  
  for (int h = 0; h < 15; h++) {
    flowState_Old = flowState_New; 
    flowState_New = digitalRead(PUMP);
    if (flowState_New != flowState_Old) { 
      fluctNum++; 
    }
    delay(10); 
  }
  return fluctNum; 
}