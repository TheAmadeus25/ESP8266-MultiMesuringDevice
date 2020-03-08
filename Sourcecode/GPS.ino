void GetGPS() {
  if (ss.available() && uBlox.Enabled == true ) {
    gps.encode( ss.read() );
    ParseGPS();
    Startup = true;
  }

  SmartDelay(50);

  return;
}

static void SmartDelay(unsigned long ms) {
  unsigned long start = millis();
  do {
    while ( ss.available()) {
      gps.encode( ss.read() );
    }
    
    ParseGPS();
  } while (millis() - start < ms);

return;
}

void ParseGPS() {
  uBlox.Lat       = gps.location.lat();
  uBlox.Lon       = gps.location.lng();

  uBlox.Sat       = gps.satellites.value();

  uBlox.AltMeter  = gps.altitude.meters();
  uBlox.AltMiles  = gps.altitude.miles();
  uBlox.AltFeet   = gps.altitude.feet();

  uBlox.KMH       = gps.speed.kmph();
  uBlox.KNTS      = gps.speed.knots();
  uBlox.MPH       = gps.speed.mph();
  uBlox.MPS       = gps.speed.mps();

  uBlox.YY        = gps.date.year();
  uBlox.MO        = gps.date.month(),
  uBlox.DD        = gps.date.day();

  uBlox.HH        = gps.time.hour() + TIMEZONE;
  uBlox.MM        = gps.time.minute();
  uBlox.SS        = gps.time.second();
  uBlox.CC        = gps.time.centisecond();

  uBlox.Course    = gps.course.deg();
  uBlox.Direction = gps.cardinal(uBlox.Course);

  uBlox.CourseTo    = gps.courseTo(uBlox.Lat, uBlox.Lon, Home_LAT, Home_LNG);
  uBlox.DirectionTo = gps.cardinal(uBlox.CourseTo);

  uBlox.DistHome  = (unsigned long)gps.distanceBetween(uBlox.Lat, uBlox.Lon, Home_LAT, Home_LNG);

  if (uBlox.HH + TIMEZONE >= 24) {
    uBlox.HH = 0;
    uBlox.DD++;
  } else if (uBlox.HH + TIMEZONE < 0) {
    uBlox.HH = 24 - TIMEZONE;
    uBlox.DD--;
  }
  
  //--- http://www.gebaerdenschrift.de/images/download/Monatsnamen%20Quiz.pdf
  
  
  if (uBlox.KMH > uBlox.KMH_Max) {
    uBlox.KMH_Max = uBlox.KMH;
  }

  if (uBlox.Sat == 0) {
    uBlox.KMH = 0;
  }

  if (uBlox.HH > 12) {
    uBlox.AnalogueHH = uBlox.HH - 12;
  } else {
    uBlox.AnalogueHH = uBlox.HH;
  }

  return;
}
