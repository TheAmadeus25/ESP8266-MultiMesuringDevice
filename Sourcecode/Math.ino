void Unit10(int Value) {
  if (Value < 10) {
    u8g2.print("0");
  }
  
  return;
}

void UnitKilometer(float Value) {
  if (Value >= 1000) {
    u8g2.print(Value / 1000, 2);
    u8g2.print("km");
  } else {
    u8g2.print(Value, 0);
    u8g2.print("m");
  }
  
  return;
}

int CheckMaxValue(int Array[], int ArraySize) {
  int MaxValue = 0;

  for(int i = 0; i < ArraySize; i++) {
    if( Array[i] > MaxValue) {
      MaxValue = Array[i];
    }
  }

  return MaxValue;
}

int CheckMinValue(int Array[], int ArraySize) {
  int MinValue = 8192;

  for(int i = 0; i < ArraySize; i++) {
    if( Array[i] < MinValue) {
      MinValue = Array[i];
    }
  }

  return MinValue;
}
