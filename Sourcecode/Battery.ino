void GetBattery() {
  Bat.Voltage = ( ESP.getVcc() / 1000.0 ) + Bat.Offset ;
  Bat.Percent = map( ESP.getVcc() + 700, 3200, 4170, 0, 100); // 3,5V switch, Gemessen 3,22V tot    // 4170
  Bat.Symbol  = map( ESP.getVcc() + 700, 3200, 4170, 0, 6);                                         // 4170

  RecordingBattery();

  if (Bat.Symbol == 0) {
    u8g2.setContrast(1);
  } else {
    u8g2.setContrast(255);
  }

  return;
}

void RecordingBattery() {
  if(Bat.ArrayShifter == 128) {
    for(int i = 1; i < Bat.ArrayShifter; i++) {
      Bat.Recording[i - 1] = Bat.Recording[i];
    }
    Bat.ArrayShifter = 127;
  }
  
  Bat.Recording[Bat.ArrayShifter] = Bat.Percent;
  Bat.ArrayShifter++;
  return;
}
