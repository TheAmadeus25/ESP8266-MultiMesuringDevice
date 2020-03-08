void InitGyro() {
  Serial.print("MPU9250         : ");
  IMU.begin();

  // setting the accelerometer full scale range to +/-8G
  IMU.setAccelRange(MPU9250::ACCEL_RANGE_8G);
  // setting the gyroscope full scale range to +/-500 deg/s
  IMU.setGyroRange(MPU9250::GYRO_RANGE_500DPS);
  // setting DLPF bandwidth to 20 Hz
  IMU.setDlpfBandwidth(MPU9250::DLPF_BANDWIDTH_20HZ);
  // setting SRD to 19 for a 50 Hz update rate
  IMU.setSrd(19);

  /*
    IMU.setAccelRange(MPU9250::ACCEL_RANGE_4G);
    IMU.setGyroRange(MPU9250::GYRO_RANGE_2000DPS);
    IMU.setDlpfBandwidth(MPU9250::DLPF_BANDWIDTH_184HZ);
    IMU.setSrd(0);  //Data Output Rate = 1000 / (1 + SRD)
  */

  Serial.println("Ready");
  
  return;
}

void GetGyro() {
  IMU.readSensor();

  MPU.AccX  = IMU.getAccelX_mss();
  MPU.AccY  = IMU.getAccelY_mss();
  MPU.AccZ  = IMU.getAccelZ_mss();

  MPU.GyroX = IMU.getGyroX_rads();
  MPU.GyroY = IMU.getGyroY_rads();
  MPU.GyroZ = IMU.getGyroZ_rads();

  MPU.MagX  = IMU.getMagX_uT();
  MPU.MagY  = IMU.getMagY_uT();
  MPU.MagZ  = IMU.getMagZ_uT();

  MPU.Temperature = IMU.getTemperature_C() - 1.8;

  MPU.AccRoot = sqrt( pow(MPU.AccX, 2) + pow(MPU.AccY, 2) + pow(MPU.AccZ, 2) );
  MPU.GForce  = MPU.AccRoot / 9.80665;

  Rad2Deg();
  GetDirection();

  return;
}

void Rad2Deg() {
  MPU.Radian = atan2( MPU.MagY , MPU.MagX ) + MPU.declinationAngle; //-------------------------------------
  MPU.Degrees = (MPU.Radian * 180 / M_PI);

  if (MPU.Degrees < 0) {
    MPU.Degrees += 360;
  }

  return;
}

void GetDirection() {
  float val = round( (MPU.Degrees - 11.25 ) / 22.5 );
  String Cardinal[17] = {"N", "NNE", "NE", "ENE", "E", "ESE", "SE", "SSE", "S", "SSW", "SW", "WSW", "W", "WNW", "NW", "NNW"};

  MPU.Direction = Cardinal[abs(val)];

  return;
}
