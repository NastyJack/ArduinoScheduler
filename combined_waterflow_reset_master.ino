// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include "RTClib.h"

RTC_DS3231 rtc;
extern volatile unsigned long timer0_millis;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

const int TriggerPin1 = 4; // Trigger Pin of Ultrasonic Sensor 1
const int EchoPin1 = 5; // Echo Pin of Ultrasonic Sensor 1

const int Relay_Motor = 6;
const int Relay_Valve = 7; 

long duration,randNumber;
float randFloat;

int HOUR,MINUTE,counter1=0,counter2=0,counter3=0;
bool ValveFlow=false,DrumFull=false,RoofTankFull=false,doOnce=false;
const int timerLimit=5;
long counterElse=0;

//WaterFlow Sensor Declarations ====================================================

volatile int flow_frequency_1; // Measures flow sensor pulses_1
// Calculated litres/hour
float vol_1 = 0.0,minute_1;
unsigned char flowsensor_1 = 2; // Sensor Input_1
unsigned long currentTime_1;
unsigned long cloopTime_1;
void flow_1 (); // Interrupt function_1

volatile int flow_frequency_2; // Measures flow sensor pulses_2
// Calculated litres/hour
float vol_2 = 0.0,minute_2;
unsigned char flowsensor_2 = 3; // Sensor Input_2
unsigned long currentTime_2;
unsigned long cloopTime_2;
void flow_2 (); // Interrupt function_2

//==================================================================================

void(* resetFunc) (void) = 0; //declare reset function @ address 0

void setup () {
Serial.begin(57600);

doSetup();
doSetupWaterFlowSensor_1();
doSetupWaterFlowSensor_2();


    digitalWrite(Relay_Valve ,HIGH);  //Valve OFF
    digitalWrite(Relay_Motor ,HIGH); //Motor OFF
doRTC();

  randomSeed(analogRead(14));
  randNumber = random(10800, 21600); //random number of seconds b/w 3 hrs and 6 hrs
}

void loop () {

doRTC();


if(RoofTankFull==false 
&& ValveFlow==false
 && DrumFull==false ){
 
 
//  if((HOUR==6&&MINUTE<=45) || (HOUR==17&&MINUTE<=45))
 if((HOUR==6&&MINUTE<=45) || (HOUR==17&&MINUTE<=45))
   {doOnce=true;  } else {doOnce=false; }
}
 if((HOUR==6&&MINUTE<=45) || (HOUR==17&&MINUTE<=45)){


   if(doOnce){
    
    digitalWrite(LED_BUILTIN, HIGH);  
    digitalWrite(Relay_Valve ,LOW);  //Valve ON
    digitalWrite(Relay_Motor ,HIGH); //Motor OFF
                           doOnce = !doOnce;

    
                }

   

   
  //Measure Ultrasonic Sensor 1 ============================================================
  digitalWrite(TriggerPin1, LOW);          // Clears the trigPin condition
  delayMicroseconds(2);                    // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(TriggerPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TriggerPin1, LOW);          // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(EchoPin1, HIGH);      // Calculating the distance
  int Drum_depth = duration * 0.034 / 2;   // Speed of sound wave divided by 2 (go and back)
  //======================================================================================


  //Measure WaterFLow Sensor 1 ===========================================================
   float Valve_flowing = 5; 
  //  CalcuateWaterFlowSensor_1();
   
  //======================================================================================


  //Measure WaterFLow Sensor 2 ===========================================================
    float Roof_tank_flowing = CalcuateWaterFlowSensor_2();
  //======================================================================================

   


   Serial.print("ULTS_1 Depth             : "); Serial.print(Drum_depth);             Serial.println(" cm."); 
   Serial.print("WFS_1  Valve flowing     : "); Serial.print(Valve_flowing, DEC);     Serial.println(" L/sec");
   Serial.print("WFS_2  Roof tank flowing : "); Serial.print(Roof_tank_flowing, DEC); Serial.println(" L/sec");
   
   if(!digitalRead(Relay_Valve)) Serial.println("Valve ON"); else  Serial.println("Valve OFF");  
   if(!digitalRead(Relay_Motor)) Serial.println("Motor ON"); else  Serial.println("Motor OFF");  
   
   Serial.print("\n\n");
   if((Valve_flowing>0)||counter2>timerLimit){ counter2++;   if(counter2>timerLimit)         
          

             ValveFlow=true;
             }
             
   if((Drum_depth>3&&Drum_depth<=29)||counter1>timerLimit){ counter1++;      if(counter1>timerLimit)  DrumFull=true;  }       
   if(Roof_tank_flowing>0||counter3>timerLimit){ counter3++; if(counter3>(timerLimit+120))  RoofTankFull=true;}

  if(ValveFlow) { Serial.println("Water flow detected at Valve");  }    
  if(DrumFull)  {Serial.println("Drum full");  digitalWrite(Relay_Valve ,HIGH);   }    // Valve OFF 
  if(RoofTankFull)  {Serial.println("Roof tank full");  Serial.println("Counter = "); Serial.println(counter3);  }   

 if(!RoofTankFull&&ValveFlow) //roof tank not flowing AND valve is flowing    true AND false
  digitalWrite(Relay_Motor ,LOW);                    // Motor ON  
  if(RoofTankFull) digitalWrite(Relay_Motor ,HIGH);  // Motor OFF
  delay(1000);

}
else {
 
      digitalWrite(LED_BUILTIN, LOW);  

      digitalWrite(Relay_Valve ,HIGH);  //Valve OFF
      digitalWrite(Relay_Motor ,HIGH); //Motor OFF
      Serial.println("Time not 06:00 - 06:35 AM OR 05:00 - 05:35 PM");
      Serial.print("Resets every ");
      randFloat = randNumber/60/60;
      Serial.print(randFloat);
      Serial.print(" hours");
      Serial.print("\n\n\n\n\n\n\n\n\n");

   // counterElse++;
 //   if(counterElse>randNumber)  
 // { Serial.println("RESETTING----------!-!-!-!-!-!-!-!-!-!_!_1_1_1_!");
  //  delay(1000);   
  //  if((HOUR!=6) && (HOUR!=17))
   // resetFunc();  //call reset  
 //   else randFloat = randNumber/60/60;
 //   }
          
delay(1000); 
counter1=0;
counter2=0;
counter3=0;
ValveFlow=false;DrumFull=false;RoofTankFull=false;
counterElse=0;
}
}

void flow_1 () { flow_frequency_1++; } // Interrupt function_1 

void flow_2 () { flow_frequency_2++; } // Interrupt function_2
