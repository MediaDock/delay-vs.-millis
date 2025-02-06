#include <NewPing.h>
#include <Keyboard.h> // einbinden der Keyboard.h

#define bulb1 10   
#define bulb2 11
#define bulb3 12   
#define SONAR_NUM 3      // Number of sensors.
#define MAX_DISTANCE 200 // Maximum distance (in cm) to ping.

NewPing sonar[SONAR_NUM] = {   // Sensor object array.
  NewPing(4, 5, MAX_DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping.
  NewPing(6, 7, MAX_DISTANCE),
  NewPing(9, 10, MAX_DISTANCE)
};

// Variables Triggerdistance in cm
int TriggerDistance = 50;

// Variables Lightduration ONtime
const long lightDuration1 = 3000;  // Light duration (Filelänge 1)
const long lightDuration2 = 5000;  // Light duration (Filelänge 2)
const long lightDuration3 = 8000;  // Light duration (Filelänge 3)

/* SETUP **************************************************************/

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  pinMode(bulb1, OUTPUT);
  pinMode(bulb2, OUTPUT);
  pinMode(bulb3, OUTPUT);
}

/* LOOP **************************************************************/

void loop() {
  for (uint8_t i = 0; i < SONAR_NUM; i++) { // Loop through each sensor and display results. 
    delay(50); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
    Serial.print(i);
    Serial.print("=");
    Serial.print(sonar[i].ping_cm());
    Serial.print("cm ");
  }
  Serial.println();

  if(sonar[1].ping_cm() < TriggerDistance) {
      Light1();
      Keyboard.press('1'); // writes a 1 with the Keyboardemulator -> could be replaced with a Keyboard command meaningful to your Programm
      delay(50);           // keeps the Key pressed for 50ms
      Keyboard.releaseAll();
      Serial.println("Sensor 1 smaller then TriggerDistance Light1 ON");

  } else if(sonar[2].ping_cm() < TriggerDistance) {
      Light2();
      Keyboard.press('2');
      delay(50);
      Keyboard.releaseAll();
      Serial.println("Sensor 2 smaller then TriggerDistance Light2 ON");

  } else if(sonar[3].ping_cm() < TriggerDistance) {
      Light3();
      Keyboard.press('3');
      delay(50);
      Keyboard.releaseAll();
      Serial.println("Sensor 3 smaller then TriggerDistance Light3 ON");

  } else {
      Serial.println("All sensors smaller then 150");
  }
}


void Light1()                            //Start the Light subroutine
  {
  digitalWrite(bulb1, HIGH);             //turn on the light
  delay (lightDuration1);                //wait xxx seconds
  digitalWrite(bulb1, LOW);              //turn off the light
  }

void Light2()                            
  {
  digitalWrite(bulb2, HIGH);             
  delay (lightDuration2);                
  digitalWrite(bulb2, LOW);              
  }

void Light3()
  {
  digitalWrite(bulb3, HIGH);             
  delay (lightDuration3);                
  digitalWrite(bulb3, LOW);              
  }

