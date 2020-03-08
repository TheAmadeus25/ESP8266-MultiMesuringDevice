#ifndef A_Variable_h
#define A_Variable_h

// Variables will change:
int ledState = HIGH;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
//---

unsigned long previousMillis = 0;
const long interval = 100;

const char* ssid = "...";
const char* password = "...";

struct {
  float Temperature, Tmin, Tmax;
  float Pressure;
  float Altitude;
  float StartAltitude;
  short Humidity;
  unsigned long last_refresh  = 0;
  long          refresh_delay;
} BME280;

struct {
  double AccX;
  double AccY;
  double AccZ;
  double AccRoot;

  double GyroX;
  double GyroY;
  double GyroZ;
  //float GyroRoot;

  double MagX;
  double MagY;
  double MagZ;
  //float MagRoot;

  float  Temperature;
  double GForce;

  double Radian;
  double Degrees;
  const double declinationAngle = 32.58 / 1000; //http://www.magnetic-declination.com/
  double Comp_X, Comp_Y, Comp_Z;
  String Direction;

  unsigned long last_refresh  = 0;
  long          refresh_delay;
} MPU;

struct {
  float         Voltage;
  int           Percent;
  float         Offset = 0.7;
  short         Status = 0;
  short         Symbol = 0;
  unsigned long last_refresh  = 0;
  long          refresh_delay = 2000;
  unsigned long last_refresh_low = 0;
  long          refresh_delay_low = 750;
  bool          low_battery = false;
  int           Recording[Display_X + 2];
  int           ArrayShifter = 0;
} Bat;

struct {
  double Lat = 0;
  double Lon = 0;

  short Sat = 0;

  float AltMeter = 0;
  float AltMiles = 0;
  float AltFeet  = 0;

  float StartAltMeter = 0;

  float KMH  = 0;
  float KNTS = 0;
  float MPH  = 0;
  float MPS  = 0;

  float KMH_Max  = 0;
  float KNTS_Max = 0;
  float MPH_Max  = 0;
  float MPS_Max  = 0;

  unsigned int YY = 1970;
  unsigned int MO = 1;
  unsigned int DD = 1;

  int HH = 0;
  int MM = 0;
  int SS = 0;
  int CC = 0;

  int AnalogueHH = 0;

  int Course;
  String Direction;

  int CourseTo;
  String DirectionTo;

  float DistHome = -1;

  bool Enabled = true;
} uBlox;

bool Startup = false;
bool canBtnPress = true;
short State = 0;


#endif
