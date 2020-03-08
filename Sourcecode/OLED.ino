void InitOLED() {
  //u8g2.setBusClock(400000);
  Serial.print("Display         : ");
  u8g2.begin();

  u8g2.setContrast(255);
  u8g2.clearBuffer();
  drawLogo();
  //drawURL();
  u8g2.sendBuffer();
  //delay(1);

  u8g2.enableUTF8Print();
  Serial.println("Ready");

  return;
}

void drawLogo(void) {
  u8g2.setFontMode(1);  // Transparent
#ifdef MINI_LOGO

  u8g2.setFontDirection(0);
  u8g2.setFont(u8g2_font_inb16_mf);
  u8g2.drawStr(0, 22, "U");

  u8g2.setFontDirection(1);
  u8g2.setFont(u8g2_font_inb19_mn);
  u8g2.drawStr(14, 8, "8");

  u8g2.setFontDirection(0);
  u8g2.setFont(u8g2_font_inb16_mf);
  u8g2.drawStr(36, 22, "g");
  u8g2.drawStr(48, 22, "\xb2");

  u8g2.drawHLine(2, 25, 34);
  u8g2.drawHLine(3, 26, 34);
  u8g2.drawVLine(32, 22, 12);
  u8g2.drawVLine(33, 23, 12);
#else

  u8g2.setFontDirection(0);
  u8g2.setFont(u8g2_font_inb24_mf);
  u8g2.drawStr(0, 30, "U");

  u8g2.setFontDirection(1);
  u8g2.setFont(u8g2_font_inb30_mn);
  u8g2.drawStr(21, 8, "8");

  u8g2.setFontDirection(0);
  u8g2.setFont(u8g2_font_inb24_mf);
  u8g2.drawStr(51, 30, "g");
  u8g2.drawStr(67, 30, "\xb2");

  u8g2.drawHLine(2, 35, 47);
  u8g2.drawHLine(3, 36, 47);
  u8g2.drawVLine(45, 32, 12);
  u8g2.drawVLine(46, 33, 12);

#endif
}

void drawURL(void) {
#ifndef MINI_LOGO
  u8g2.setFont(u8g2_font_4x6_tr);
  if ( u8g2.getDisplayHeight() < 59 ) {
    u8g2.drawStr(89, 20, "github.com");
    u8g2.drawStr(73, 29, "/olikraus/u8g2");
  } else {
    u8g2.drawStr(1, 54, "github.com/olikraus/u8g2");
  }
#endif
}

void ShowBattery() {
  u8g2.setFont(u8g2_font_battery19_tn);
  u8g2.setFontDirection(1);

  switch (Bat.Symbol) {
    case 1:   u8g2.drawGlyph(Display_X - 19, 0, 0x0031);  break;  // 1/5
    case 2:   u8g2.drawGlyph(Display_X - 19, 0, 0x0032);  break;  // 2/5
    case 3:   u8g2.drawGlyph(Display_X - 19, 0, 0x0033);  break;  // 3/5
    case 4:   u8g2.drawGlyph(Display_X - 19, 0, 0x0034);  break;  // 4/5
    case 5:   u8g2.drawGlyph(Display_X - 19, 0, 0x0035);  break;  // 4/5
    case 6:   u8g2.drawGlyph(Display_X - 19, 0, 0x0035);  break;  // Full or USB
    default:                                                      // Empty and Flashing
      if ( millis() - Bat.last_refresh_low > Bat.refresh_delay_low ) {
        Bat.low_battery = !Bat.low_battery;
        Bat.last_refresh_low = millis();
      }

      if (Bat.low_battery) u8g2.drawGlyph(Display_X - 19, 0, 0x0030);
      break;
  }

  u8g2.setFontDirection(0);

  return;
}

void ShowGPS() {
  if (uBlox.Sat != 0) {
    u8g2.setFont(u8g2_font_open_iconic_all_1x_t);
    u8g2.drawGlyph(Display_X - 28, 8, 0x00C9);
  }

  return;
}

void ShowWarning() {
  u8g2.setFont(u8g2_font_open_iconic_all_1x_t);
  u8g2.drawGlyph(Display_X - 28, 8, 0x0118);

  return;
}

void ShowTooHot() {
  u8g2.setFont(u8g2_font_open_iconic_all_1x_t);
  u8g2.drawGlyph(Display_X - 28, 8, 0x00A8);

  return;
}

void ShowTooCold() {
  u8g2.setFont(u8g2_font_open_iconic_all_1x_t);
  u8g2.drawGlyph(Display_X - 28, 8, 0x008D);

  return;
}

void ShowWiFi() {
  u8g2.setFont(u8g2_font_open_iconic_all_1x_t);
  //u8g2.drawGlyph(Display_X - 36, 8, 0x0119);

  if ( (WiFi.status() == WL_CONNECTED) && (uBlox.Sat != 0) ) {
    u8g2.drawGlyph(Display_X - 36, 8, 0x0119);
    //u8g2.drawGlyph(Display_X - 28, 8, 0x0119);
  } else if ( WiFi.status() == WL_CONNECTED ) {
    u8g2.drawGlyph(Display_X - 28, 8, 0x0119);
  }

  return;
}

void ShowVoltage() {
  u8g2.setFont(u8g2_font_open_iconic_all_1x_t);
  //u8g2.drawGlyph(Display_X - 36, 8, 0x0119);
  u8g2.drawGlyph(Display_X - 28, 8, 0x00AA);

  return;
}

void ShowVoltage2() {
  u8g2.setFont(u8g2_font_open_iconic_all_1x_t);
  //u8g2.drawGlyph(Display_X - 36, 8, 0x0119);
  u8g2.drawGlyph(Display_X - 28, 8, 0x0060);

  return;
}

void ShowSpeed() {
  u8g2.setFont(u8g2_font_open_iconic_all_1x_t);
  u8g2.drawGlyph(Display_X - 36, 8, 0x010D);
  //u8g2.drawGlyph(Display_X - 28, 8, 0x010D);

  return;
}

void ShowGauge(int x, byte y, byte r, byte p, float v, float minVal, float maxVal, byte t) {
  int n = (r / 100.00) * p; // calculate needle percent lenght

  switch (t) {
    case 0: { //left quarter
        float gs_rad = -1.572; //-90 degrees in radiant
        float ge_rad = 0;
        float i = ((v - minVal) * (ge_rad - gs_rad) / (maxVal - minVal) + gs_rad);
        int xp = x + (sin(i) * n);
        int yp = y - (cos(i) * n);
        u8g2.drawCircle(x, y, r, U8G2_DRAW_UPPER_LEFT );
        u8g2.drawLine(x, y, xp, yp);
      }
      break;
    case 1: { //right quarter, needle anticlockwise

        float gs_rad = 0;
        float ge_rad = 1.572; //90 degrees in radiant
        float i = ((v - minVal) * (ge_rad - gs_rad) / (maxVal - minVal) + gs_rad);
        int xp = x + (cos(i) * n);
        int yp = y - (sin(i) * n);
        u8g2.drawCircle(x, y, r, U8G2_DRAW_UPPER_RIGHT );
        u8g2.drawLine(x, y, xp, yp);
      }
      break;
    case 2: { //upper half
        float gs_rad = -1.572;
        float ge_rad = 1.572;
        float i = ((v - minVal) * (ge_rad - gs_rad) / (maxVal - minVal) + gs_rad);
        int xp = x + (sin(i) * n);
        int yp = y - (cos(i) * n);
        u8g2.drawCircle(x, y, r, U8G2_DRAW_UPPER_LEFT | U8G2_DRAW_UPPER_RIGHT );
        u8g2.drawLine(x, y, xp, yp);
      }
      break;
    case 3: { //three quarter starting at -180
        float gs_rad = -3.142;
        float ge_rad = 1.572;
        float i = ((v - minVal) * (ge_rad - gs_rad) / (maxVal - minVal) + gs_rad);
        int xp = x + (sin(i) * n);
        int yp = y - (cos(i) * n);
        u8g2.drawCircle(x, y, r, U8G2_DRAW_UPPER_LEFT | U8G2_DRAW_UPPER_RIGHT | U8G2_DRAW_LOWER_LEFT );
        u8g2.drawLine(x, y, xp, yp);
      }
      break;
    case 4: { //three quarter starting at -90
        float gs_rad = -1.572;
        float ge_rad = 3.141;
        float i = ((v - minVal) * (ge_rad - gs_rad) / (maxVal - minVal) + gs_rad);
        int xp = x + (sin(i) * n);
        int yp = y - (cos(i) * n);
        u8g2.drawCircle(x, y, r, U8G2_DRAW_UPPER_LEFT | U8G2_DRAW_UPPER_RIGHT | U8G2_DRAW_LOWER_RIGHT );
        u8g2.drawLine(x, y, xp, yp);
      }
      break;
    case 5: {
        float gs_rad = 0;
        float ge_rad = 2 * 3.141;
        float i = ((v - minVal) * (ge_rad - gs_rad) / (maxVal - minVal) + gs_rad);
        int xp = x + (sin(i) * n);
        int yp = y - (cos(i) * n);
        u8g2.drawCircle(x, y, r);
        u8g2.drawLine(x, y, xp, yp);
      }
      break;
  }

  return;
}

void ShowHistoryGraph(int Array[], int ArraySize, int y_start, int y_end, bool filled, char Unit) {
  int MaxValue, MinValue;

  MaxValue = CheckMaxValue(Array, ArraySize);
  MinValue = CheckMinValue(Array, ArraySize);

  u8g2.setFont(u8g2_font_profont10_mf);
  u8g2.setCursor(0, y_start + 9);
  u8g2.print(MaxValue);
  u8g2.print(Unit);
  u8g2.setCursor(0, y_end);
  u8g2.print(MinValue);
  u8g2.print(Unit);

  for (int i = 0; i < ArraySize; i++) {
    if (filled) {
      u8g2.drawLine(i, map(Array[i], MinValue, MaxValue, y_end - 9, y_start + 10), i, y_end - 9);
    } else {
      u8g2.drawPixel(i, map(Array[i], MinValue, MaxValue, y_end - 9, y_start + 10) );
    }

  }

  return;
}

void ErrorPage() {
  u8g2.setFont(u8g2_font_inr19_mn);
  u8g2.setCursor(0, 19);
  u8g2.print(State);

  u8g2.setFont(u8g2_font_open_iconic_all_2x_t);
  u8g2.drawGlyph(Display_X / 2 - 7, Display_Y / 2 + 8, 0x0079);   // Cross Symbol

  return;
}

void ErrorNoGPS() {
  u8g2.setFont(u8g2_font_open_iconic_all_2x_t);
  u8g2.drawGlyph(Display_X / 2 - 16, Display_Y / 2 + 8, 0x00C9);  // GPS Symbol
  u8g2.drawGlyph(Display_X / 2, Display_Y / 2 + 8, 0x00F0);       // '?'

  return;
}

void ErrorNoTemperature() {
  u8g2.setFont(u8g2_font_open_iconic_all_2x_t);
  u8g2.drawGlyph(Display_X / 2 - 16, Display_Y / 2 + 8, 0x008D);
  u8g2.drawGlyph(Display_X / 2, Display_Y / 2 + 8, 0x00F0);       // '?'

  return;
}

void ErrorNoGyroscope() {
  u8g2.setFont(u8g2_font_open_iconic_all_2x_t);
  u8g2.drawGlyph(Display_X / 2 - 16, Display_Y / 2 + 8, 0x0088);
  u8g2.drawGlyph(Display_X / 2, Display_Y / 2 + 8, 0x00F0);       // '?'

  return;
}

void ErrorVoltage() {
  u8g2.setFont(u8g2_font_open_iconic_all_2x_t);
  u8g2.drawGlyph(Display_X / 2 - 16, Display_Y / 2 + 8, 0x00AA);
  u8g2.drawGlyph(Display_X / 2, Display_Y / 2 + 8, 0x00F0);       // '?'

  return;
}

void ErrorVoltage2() {
  u8g2.setFont(u8g2_font_open_iconic_all_2x_t);
  u8g2.drawGlyph(Display_X / 2 - 16, Display_Y / 2 + 8, 0x0060);
  u8g2.drawGlyph(Display_X / 2, Display_Y / 2 + 8, 0x00F0);       // '?'

  return;
}

void Page_0() {
  //u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_5x8_mf);
  u8g2.setCursor(0, 7);
  u8g2.print("Main | ");

  Unit10(uBlox.HH);
  u8g2.print(uBlox.HH);
  u8g2.print(":");

  Unit10(uBlox.MM);
  u8g2.print(uBlox.MM);
  u8g2.print(":");

  Unit10(uBlox.SS);
  u8g2.print(uBlox.SS);

  u8g2.setCursor(0, 15);
  u8g2.print(BME280.Temperature);
  u8g2.print("°C | ");
  u8g2.print(MPU.Temperature);
  u8g2.print("°C | ");
  u8g2.print( (BME280.Temperature - MPU.Temperature) );

  u8g2.setCursor(0, 23);
  u8g2.print(BME280.Altitude);
  u8g2.print("m | ");
  u8g2.print(BME280.Humidity);
  u8g2.print("% | ");
  u8g2.print(BME280.Pressure, 1);
  u8g2.print("hPa");

  u8g2.setCursor(0, 31);
  u8g2.print("DtH ");
  UnitKilometer(uBlox.DistHome);

  u8g2.setCursor(0, 39);
  u8g2.print(uBlox.KMH);
  u8g2.print("km/h | ");
  u8g2.print( (uBlox.KMH / 3.6) );
  u8g2.print("m/s");

  u8g2.setCursor(0, 47);
  u8g2.print("Alt ");
  UnitKilometer(uBlox.AltMeter);
  u8g2.print(" | ");
  UnitKilometer(BME280.Altitude);

  u8g2.setCursor(0, 55);
  u8g2.print("Deg ");
  u8g2.print((int)MPU.Degrees);
  u8g2.print("° ");
  u8g2.print(MPU.Direction);
  u8g2.print(" | ");
  u8g2.print((int)uBlox.Course);
  u8g2.print("° ");
  u8g2.print(uBlox.Direction);

  u8g2.setCursor(0, 63);
  u8g2.print("Lat ");
  u8g2.print(uBlox.Lat, 5);
  u8g2.print(" Lng ");
  u8g2.print(uBlox.Lon, 5);

  return;
}

void Page_1() {
  CheckBME();

  u8g2.setFont(u8g2_font_profont12_mf);
  u8g2.setCursor(0, 9);
  u8g2.print(MPU.Temperature);
  u8g2.print("°C");

  u8g2.setFont(u8g2_font_profont29_mf);
  u8g2.setCursor(0, 33);
  u8g2.print(BME280.Temperature);
  u8g2.print("°C");

  u8g2.setFont(u8g2_font_profont12_mf);
  u8g2.setCursor(0, 45);
  u8g2.print("Humi ");
  u8g2.print(BME280.Humidity);
  u8g2.print("%");

  u8g2.setCursor(0, 54);
  u8g2.print("Pres ");
  u8g2.print(BME280.Pressure);
  u8g2.print("hPa");

  u8g2.setCursor(0, 63);
  u8g2.print("Alti ");
  UnitKilometer(BME280.Altitude);


  return;
}

void Page_2() {
  CheckBME();

  if (BME280.Tmin == BME280.Tmax) {
    ErrorNoTemperature();
  } else {
    ShowGauge(63, 52, 52, 90, BME280.Temperature, BME280.Tmin, BME280.Tmax, 2); // X center, Y center, radius, percent, Value, low, max, case
  }

  u8g2.setFont(u8g2_font_profont12_mf);
  u8g2.setCursor(0, 10);
  u8g2.print("°C");

  u8g2.setCursor(0, 63);
  u8g2.print(BME280.Tmin);

  u8g2.setCursor(47, 63);

  u8g2.print(BME280.Temperature);

  u8g2.setCursor(95, 63);
  u8g2.print(BME280.Tmax);

  return;
}

void Page_3() {
  u8g2.setFont(u8g2_font_profont10_mf);
  u8g2.setCursor(0, 8);
  u8g2.print(Bat.Voltage);
  u8g2.print("V | ");
  u8g2.print(Bat.Percent);
  u8g2.print("%");

  ShowHistoryGraph(Bat.Recording, Display_X + 1, 6, Display_Y, 0, '%');

  return;
}

void Page_4() {
  u8g2.setFont(u8g2_font_profont10_mf);
  u8g2.setCursor(0, 8);
  u8g2.print(Bat.Voltage);
  u8g2.print("V | ");
  u8g2.print(Bat.Percent);
  u8g2.print("%");

  ShowHistoryGraph(Bat.Recording, Display_X + 1, 6, Display_Y, 1, '%');

  return;
}

void Page_5() {
  u8g2.setFont(u8g2_font_profont12_mf);
  u8g2.setCursor(0, 9);
  u8g2.print( (uBlox.KMH) / 3.6 );
  u8g2.print("m/s");

  u8g2.setFont(u8g2_font_profont29_mf);
  u8g2.setCursor(0, 33);
  u8g2.print(uBlox.KMH, 1);

  u8g2.setFont(u8g2_font_profont12_mf);
  u8g2.setCursor(0, 45);
  u8g2.print("Max ");
  u8g2.print(uBlox.KMH_Max, 3);
  u8g2.print(" | ");
  u8g2.print( (uBlox.KMH_Max) / 3.6 , 2);


  u8g2.setCursor(0, 54);
  u8g2.print("DtH ");
  if (uBlox.DistHome >= 1000) {
    u8g2.print((uBlox.DistHome / 1000) , 2);
    u8g2.print("km");
  } else {
    u8g2.print(uBlox.DistHome , 0);
    u8g2.print("m");
  }

  u8g2.setCursor(0, 63);
  u8g2.print("GPS ");
  u8g2.print((int)uBlox.Course);
  u8g2.print("° ");
  u8g2.print(uBlox.Direction);
  u8g2.print("|");
  u8g2.print((int)MPU.Degrees);
  u8g2.print("° ");
  u8g2.print(MPU.Direction);

  return;
}

void Page_6() {
  if (uBlox.KMH_Max == 0) {
    ErrorNoGPS();
  } else {
    ShowGauge(63, 52, 52, 90, uBlox.KMH, 0, uBlox.KMH_Max, 2); // X center, Y center, radius, percent, Value, low, max, case
  }

  u8g2.setFont(u8g2_font_profont12_mf);
  u8g2.setCursor(0, 10);
  u8g2.print("km/h");

  u8g2.setCursor(0, 63);
  u8g2.print(0.00);

  u8g2.setCursor(47, 63);

  if (uBlox.KMH < 10) {
    u8g2.print(" ");
  }
  u8g2.print(uBlox.KMH, 2);

  u8g2.setCursor(95, 63);
  if (uBlox.KMH_Max < 10) {
    u8g2.print(" ");
  }
  u8g2.print(uBlox.KMH_Max, 2);

  return;
}

void Page_7() {
  if (uBlox.KMH_Max == 0) {
    ErrorNoGPS();
  } else {
    ShowGauge(63, 52, 52, 90, uBlox.KMH / 3.6, 0, uBlox.KMH_Max / 3.6, 2); // X center, Y center, radius, percent, Value, low, max, case
  }

  u8g2.setFont(u8g2_font_profont12_mf);
  u8g2.setCursor(0, 10);
  u8g2.print("m/s");

  u8g2.setCursor(0, 63);
  u8g2.print(0.00);

  u8g2.setCursor(47, 63);
  if (uBlox.KMH / 3.6 < 10) {
    u8g2.print(" ");
  }
  u8g2.print(uBlox.KMH / 3.6, 2);

  if ( (uBlox.KMH_Max / 3.6) < 10) {
    u8g2.print(" ");
  }
  u8g2.setCursor(95, 63);
  if ( (uBlox.KMH_Max / 3.6) < 10) {
    u8g2.print(" ");
  }
  u8g2.print(uBlox.KMH_Max / 3.6, 2);

  return;
}

void Page_8() {
  u8g2.setFont(u8g2_font_profont12_mf);
  u8g2.setCursor(0, 10);
  u8g2.print((int)MPU.Degrees);
  u8g2.print("°");
  u8g2.setCursor(0, 20);
  u8g2.print(MPU.Direction);

  u8g2.drawCircle(63, 32, 31);
  u8g2.drawPixel(63, 32);

  MPU.Comp_X = -31 * cos(MPU.Radian - M_PI / 2); // +
  MPU.Comp_Z = -31 * cos(MPU.Radian - M_PI / 2); // +
  MPU.Comp_Y = -31 * sin(MPU.Radian - M_PI / 2); // -


  u8g2.drawLine(63, 32, 63 - MPU.Comp_X, 32 - MPU.Comp_Y);
  //u8g2.drawLine(63, 32, 63 - MPU.Comp_Z, 32 - MPU.Comp_Y);

  return;
}

void Page_9() {
  u8g2.setFont(u8g2_font_freedoomr25_tn);
  u8g2.setCursor((Display_X / 2) - (2 * 18) - 7 , (Display_Y / 2) + 16);

  Unit10(uBlox.HH);
  u8g2.print(uBlox.HH);

  if ( (uBlox.SS % 2) == 0) {
    u8g2.print(":");
  } else {
    u8g2.setCursor((Display_X / 2) + 6, (Display_Y / 2) + 16);
  }

  Unit10(uBlox.MM);
  u8g2.print(uBlox.MM);
  /*u8g2.print(":");

    Unit10(uBlox.SS);
    u8g2.print(uBlox.SS);*/

  //u8g2.drawLine(Display_X / 2, 0, Display_X / 2, Display_Y);
  //u8g2.drawLine(0, Display_Y / 2, Display_X, Display_Y / 2);

  return;
}

void Page_10() {
  u8g2.setFont(u8g2_font_profont12_mf);
  u8g2.setCursor(0, 10);
  Unit10(uBlox.HH);
  u8g2.print(uBlox.HH);
  u8g2.setCursor(0, 20);
  Unit10(uBlox.MM);
  u8g2.print(uBlox.MM);
  u8g2.setCursor(0, 30);
  Unit10(uBlox.SS);
  u8g2.print(uBlox.SS);

  ShowGauge( Display_X / 2, Display_Y / 2, (Display_Y / 2) - 2, 100, uBlox.SS,          0, 59, 5); // X center, Y center, radius, percent, Value, low, max, case
  ShowGauge( Display_X / 2, Display_Y / 2, (Display_Y / 2) - 2,  50, uBlox.AnalogueHH + (uBlox.MM / 59),  0, 11, 5); // X center, Y center, radius, percent, Value, low, max, case
  ShowGauge( Display_X / 2, Display_Y / 2, (Display_Y / 2) - 2,  85, uBlox.MM,          0, 59, 5); // X center, Y center, radius, percent, Value, low, max, case

  //u8g2.drawCircle(63, 32, 31);
  //u8g2.drawPixel(63, 32);

  /*MPU.Comp_X = -31 * cos(MPU.Radian - M_PI / 2); // +
    MPU.Comp_Y = -31 * sin(MPU.Radian - M_PI / 2); // -

    u8g2.drawLine(63, 32, 63 - MPU.Comp_X, 32 - MPU.Comp_Y);
    //u8g2.drawLine(63, 32, 63 - MPU.Comp_Z, 32 - MPU.Comp_Y);
  */

  return;
}
