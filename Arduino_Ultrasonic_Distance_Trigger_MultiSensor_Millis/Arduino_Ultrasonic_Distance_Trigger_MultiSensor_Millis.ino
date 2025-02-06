#include <NewPing.h>
#include <Keyboard.h>

#define bulb1 10   
#define bulb2 11  
#define bulb3 12  
#define SONAR_NUM 3
#define MAX_DISTANCE 200

NewPing sonar[SONAR_NUM] = {
  NewPing(4, 5, MAX_DISTANCE),
  NewPing(6, 7, MAX_DISTANCE),
  NewPing(8, 9, MAX_DISTANCE)
};

// Variables Triggerdistance in cm
int TriggerDistance = 50

// Variables Lightduration ONtime
const long lightDuration1 = 10000;  // Light duration (Filelänge 1)
const long lightDuration2 = 15000;  // Light duration (Filelänge 2)
const long lightDuration3 = 18000;  // Light duration (Filelänge 3)

/* Millis Variables ****************************************************/
// Variables for timing
unsigned long previousSensorMillis = 0;
const long sensorInterval = 50; 
// Variables for light timing
unsigned long light1StartTime = 0;
unsigned long light2StartTime = 0;
unsigned long light3StartTime = 0;
// Flag for Statuscheck
bool light1Active = false;
bool light2Active = false;
bool light3Active = false;


/* SETUP **************************************************************/

void setup() {
  Serial.begin(115200);
  pinMode(bulb1, OUTPUT);
  pinMode(bulb2, OUTPUT);
  pinMode(bulb3, OUTPUT);
}


/* LOOP **************************************************************/

void loop() {
  unsigned long currentMillis = millis();

  // Read sensors every sensorInterval
  if (currentMillis - previousSensorMillis >= sensorInterval) {
    previousSensorMillis = currentMillis;
    
    // Read and print sensor data
    for (uint8_t i = 0; i < SONAR_NUM; i++) {
      Serial.print(i);
      Serial.print("=");
      Serial.print(sonar[i].ping_cm());
      Serial.print("cm ");
    }
    Serial.println();

    // Check sensor 1
    if (sonar[0].ping_cm() < TriggerDistance && !light1Active && !light2Active && !light3Active) { //Checking if the TriggerDistance is bigger than and if no light is on
      light1Active = true;
      light1StartTime = currentMillis;
      digitalWrite(bulb1, HIGH);
      Keyboard.press('1'); // writes a 1 with the Keyboardemulator -> could be replaced with a Keyboard command meaningful to your Programm
      delay(50);
      Keyboard.releaseAll();

      Serial.println("Sensor 1 triggered - Light 1 ON");
    }

    // Check sensor 2
    if (sonar[1].ping_cm() < TriggerDistance && !light1Active && !light2Active && !light3Active) {
      light2Active = true;
      light2StartTime = currentMillis;
      digitalWrite(bulb2, HIGH);
      Keyboard.press('2'); 
      delay(50);
      Keyboard.releaseAll();
      
      Serial.println("Sensor 2 triggered - Light 2 ON");
    }

    // Check sensor 3
    if (sonar[2].ping_cm() < TriggerDistance && !light1Active && !light2Active && !light3Active) {
      light3Active = true;
      light3StartTime = currentMillis;
      digitalWrite(bulb3, HIGH);
      Keyboard.press('3'); 
      delay(50);
      Keyboard.releaseAll();
      
      Serial.println("Sensor 3 triggered - Light 3 ON");
    }
  }

  // Check if it's time to turn off Light 1
  if (light1Active && (currentMillis - light1StartTime >= lightDuration1)) {
    digitalWrite(bulb1, LOW);
    light1Active = false;
    Serial.println("Light 1 OFF");
  }

  // Check if it's time to turn off Light 2
  if (light2Active && (currentMillis - light2StartTime >= lightDuration2)) {
    digitalWrite(bulb2, LOW);
    light2Active = false;
    Serial.println("Light 2 OFF");
  }

  // Check if it's time to turn off Light 3
  if (light3Active && (currentMillis - light3StartTime >= lightDuration3)) {
    digitalWrite(bulb3, LOW);
    light3Active = false;
    Serial.println("Light 3 OFF");
  }
}