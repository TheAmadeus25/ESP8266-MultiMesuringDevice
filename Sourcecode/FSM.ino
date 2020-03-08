void FSM() {
  u8g2.clearBuffer();
  
  switch(State) {
    case  0: Page_0();  ShowBattery();  ShowGPS();  ShowWiFi();   break;                                // Main
    case  1: Page_1();  ShowBattery();  break;                                                          // BME Temperature
    case  2: Page_2();  ShowBattery();  break;                                                          // BME Temperature Gauge
    case  3: Page_3();  ShowBattery();  break;                                                          // Battery Voltage Dots
    case  4: Page_4();  ShowBattery();  break;                                                          // Battery Voltage Filled
    case  5: Page_5();  ShowBattery();  ShowGPS();  break;                                              // GPS Speed
    case  6: Page_6();  ShowBattery();  ShowGPS();  break;                                              // GPS Speed Gauge km/h
    case  7: Page_7();  ShowBattery();  ShowGPS();  break;                                              // GPS Speed Gauge m/h
    case  8: Page_8();  ShowBattery();  break;                                                          // Compass
    case  9: Page_9();  ShowBattery();  ShowGPS();  break;                                              // Clock
    case 10: Page_10(); ShowBattery();  ShowGPS();  break;                                              // Clock Oldscool
    default: ErrorPage();               ShowBattery();      break;
  }

  switch(State) {
    case  0: BME280.refresh_delay = 500;   MPU.refresh_delay = 250;    Bat.refresh_delay = 2000; uBlox.Enabled = true;   break;    // Main
    case  1: BME280.refresh_delay = 250;   MPU.refresh_delay = 500;    Bat.refresh_delay = 2000; uBlox.Enabled = false;  break;    // BME Temperature
    case  2: BME280.refresh_delay = 0;     MPU.refresh_delay = 1000;   Bat.refresh_delay = 2000; uBlox.Enabled = false;  break;    // BME Temperature Gauge
    case  3: BME280.refresh_delay = 500;   MPU.refresh_delay = 1000;   Bat.refresh_delay = 1000; uBlox.Enabled = false;  break;    // Battery Voltage Dots
    case  4: BME280.refresh_delay = 500;   MPU.refresh_delay = 1000;   Bat.refresh_delay = 1000; uBlox.Enabled = false;  break;    // Battery Voltage Filled
    case  5: BME280.refresh_delay = 500;   MPU.refresh_delay = 50;     Bat.refresh_delay = 2000; uBlox.Enabled = true;   break;    // GPS Speed
    case  6: BME280.refresh_delay = 500;   MPU.refresh_delay = 1000;   Bat.refresh_delay = 2000; uBlox.Enabled = true;   break;    // GPS Speed Gauge km/h
    case  7: BME280.refresh_delay = 500;   MPU.refresh_delay = 1000;   Bat.refresh_delay = 2000; uBlox.Enabled = true;   break;    // GPS Speed Gauge m/h
    case  8: BME280.refresh_delay = 1000;  MPU.refresh_delay = 0;      Bat.refresh_delay = 2000; uBlox.Enabled = false;  break;    // Compass
    case  9: BME280.refresh_delay = 1000;  MPU.refresh_delay = 0;      Bat.refresh_delay = 2000; uBlox.Enabled = true;   break;    // Clock
    case 10: BME280.refresh_delay = 1000;  MPU.refresh_delay = 0;      Bat.refresh_delay = 2000; uBlox.Enabled = true;   break;    // Clock Oldscool
    default: BME280.refresh_delay = 1000;  MPU.refresh_delay = 1000;   Bat.refresh_delay = 2000; uBlox.Enabled = false;  break;    // Missing Page
  }
  
  u8g2.sendBuffer();
  
  return;
}
