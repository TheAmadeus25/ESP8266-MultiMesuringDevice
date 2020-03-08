void InitBME() {
  Serial.print("BME280          : ");
  bool status = bme.begin();

  if (!status) {
    Serial.println("Failed");
    while (1);
  }

  bme.setSampling(Adafruit_BME280::MODE_NORMAL,
                  Adafruit_BME280::SAMPLING_X2,  // temperature
                  Adafruit_BME280::SAMPLING_X16, // pressure
                  Adafruit_BME280::SAMPLING_X1,  // humidity
                  Adafruit_BME280::FILTER_X16);
  delay(100);

  BME280.Temperature = bme.readTemperature();
  BME280.Tmax = BME280.Temperature;
  BME280.Tmin = BME280.Temperature;
  
  Serial.println("Ready");

  return;
}

void GetBME() {
  BME280.Temperature = bme.readTemperature();
  BME280.Pressure    = bme.readPressure() / 100.0F;
  BME280.Altitude    = bme.readAltitude(SEALEVELPRESSURE_HPA);
  BME280.Humidity    = bme.readHumidity();

  if ( BME280.Temperature > BME280.Tmax) {
    BME280.Tmax = BME280.Temperature;
  }

  if ( BME280.Temperature < BME280.Tmin) {
    BME280.Tmin = BME280.Temperature;
  }

  return;
}
void CheckBME() { //https://cdn-shop.adafruit.com/datasheets/BST-BME280_DS001-10.pdf
  if (BME280.Temperature < -40.00) {
    ShowTooCold();  // Out of Operation Range
  } else if (BME280.Temperature > 85.00) {
    ShowTooHot();   // Out of Operation Range
  } else if ( (BME280.Temperature < 0.00 && BME280.Temperature > -40.00) || (BME280.Temperature > 65.00 && BME280.Temperature < 85.00) ) {
    ShowWarning();  // Out of High Accuracy
  }

  return;
}
