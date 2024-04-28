float CalcuateWaterFlowSensor_1(){
 
  currentTime_1 = millis();
   // Every second, calculate and print litres/hour
   if(currentTime_1 >= (cloopTime_1 + 1000))
   {
    cloopTime_1 = currentTime_1; // Updates cloopTime
    if(flow_frequency_1 != 0){
      // Pulse frequency (Hz) = 7.5Q, Q is flow rate in L/min.
      minute_1 = (flow_frequency_1 / 7.5); // (Pulse frequency x 60 min) / 7.5Q = flowrate in L/hour
      minute_1 = minute_1/60;
      minute_1 = minute_1*1000;
      vol_1 = vol_1 +minute_1;
      flow_frequency_1 = 0; // Reset Counter
//      Serial.print("flow rate of S1 = ");
//      Serial.print(minute_1, DEC); // Print litres/hour
//      Serial.print(" L/Sec\n");
//      Serial.println("Called waterflow broooooooooo ");
      return minute_1;
    }
    else {
      
      minute_1=0;
      return minute_1;
   }
  }
 }
