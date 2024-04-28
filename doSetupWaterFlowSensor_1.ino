
 void doSetupWaterFlowSensor_1(){  
   pinMode(flowsensor_1, INPUT);
   digitalWrite(flowsensor_1, HIGH); // Optional Internal Pull-Up
   attachInterrupt(digitalPinToInterrupt(flowsensor_1), flow_1, RISING); // Setup Interrupt
   currentTime_1 = millis();
   cloopTime_1 = currentTime_1;
 }
