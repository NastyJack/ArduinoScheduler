float CalcuateWaterFlowSensor_2(){

  currentTime_2 = millis();
   // Every second, calculate and print litres/hour
   if(currentTime_2 >= (cloopTime_2 + 1000))
   {
    cloopTime_2 = currentTime_2; // Updates cloopTime
    if(flow_frequency_2 != 0){
      // Pulse frequency (Hz) = 7.5Q, Q is flow rate in L/min.
      minute_2 = (flow_frequency_2 / 7.5); // (Pulse frequency x 60 min) / 7.5Q = flowrate in L/hour
      minute_2 = minute_2/60;
      minute_2 = minute_2*1000;
      vol_2 = vol_2 +minute_2;

      flow_frequency_2 = 0; // Reset Counter
 //     Serial.print("flow rate of S1 = ");
  //    Serial.print(minute_2, DEC); // Print litres/hour
   //   Serial.print(" L/Sec\n");
      return minute_2;
    }
    else {
        minute_2=0;
      return minute_2;
   }
  }
 }
