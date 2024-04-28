  void doRTC(){       
  
    DateTime now = rtc.now();
//  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    HOUR=now.hour();
    if(now.hour()>12) 
   { Serial.print(now.hour()-12, DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    MINUTE=now.minute();
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.print(" PM\n");
   }
    else 
   { Serial.print(now.hour(), DEC);  
    Serial.print(':');
    MINUTE=now.minute();
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.print(" PM\n");
   }

    Serial.print("Temperature: ");
    Serial.print(rtc.getTemperature());
    Serial.println(" C");


}



long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}
    
long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}
