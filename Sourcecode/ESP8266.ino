void InitESP() {
  Serial.begin(PC_BAUDRATE);
  Serial.print("\nSerial          : Ready @ ");
  Serial.println(PC_BAUDRATE);

  Serial.print("Software Serial : ");
  ss.begin(GPS_BAUDRATE);
  Serial.print("Ready @ ");
  Serial.println(GPS_BAUDRATE);

  pinMode(ESP_Button, INPUT);
  Serial.print("I²C             : ");

  // D:\Benutzer\Martin&Elena\Documents\ArduinoData\packages\esp8266\hardware\esp8266\2.4.1\cores\esp8266
  twi_setClock(WIRECLOCK);
  //Wire.setClock(WIRECLOCK);
  Serial.print("Ready @ ");
  Serial.println(WIRECLOCK);

  return;
}

void InitESPWiFi() {
  // WiFi.mode(WIFI_STA);
  // WiFi.begin(ssid, password);

  Serial.print("Connecting      : ");

  WiFi.begin(ssid, password);
  //while (WiFi.status() != WL_CONNECTED) {
  //  delay(250);
  //}

  //Serial.println(WiFi.localIP());

  return;
}

void GetAll() {
  GetGPS();
  GetBattery();
  GetBME();
  GetGyro();

  return;
}

void Input() {
  if (digitalRead(ESP_Button) == LOW) {             // When pressing the button...
    if (canBtnPress) canBtnPress = false;           // ...change state
  } else if (!canBtnPress) {
    canBtnPress = true;

    if ( (State + 1) > MAXPAGES ) {
      State = 0;
    } else {
      State++;
    }
  }

  return;
}
