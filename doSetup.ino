void doSetup(){
 pinMode(LED_BUILTIN, OUTPUT);
 digitalWrite(LED_BUILTIN, LOW);
   
 pinMode(A3, OUTPUT);
 pinMode(A2, OUTPUT);
 digitalWrite(A3, HIGH);
 digitalWrite(A2, LOW); 
 
 pinMode(TriggerPin1, OUTPUT);
 pinMode(EchoPin1, INPUT); 
  
 pinMode(Relay_Valve , OUTPUT);
 pinMode(Relay_Motor , OUTPUT);

#ifndef ESP8266
  while (!Serial); // wait for serial port to connect. Needed for native USB
#endif

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }

// if (rtc.lostPower()) {
    //Serial.println("RTC lost power, let's set the time!");
  //   rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
// }
  
   

  }
