class SensorJarak {
  private:
    int infraPin;
    VL53L0X sensor;
    
    // float *buffer;
    // int bufferSize = 5;
    // int bufferIndex;
  
  public:
    float jarak;
    
    SensorJarak(int infraPin) {
      
      // buffer = new float[bufferSize];
      // bufferIndex = 0;
      jarak = 0;
      this->infraPin=infraPin;
    }
    void init(){
      pinMode(infraPin, OUTPUT);
      digitalWrite(infraPin, LOW);
      delay(400);
      digitalWrite(infraPin, HIGH);
      delay(150);
      if (!sensor.init())
      {
        Serial.print(infraPin);
        Serial.println("Failed to detect and initialize sensor!");
        // while (1) {}
      }
      sensor.setTimeout(500);
      delay(100);
      sensor.setAddress((uint8_t)infraPin);
      sensor.startContinuous();
    }
    float bacaJarak() {

      return sensor.readRangeContinuousMillimeters();
      // float duration = pulseIn(echoPin, HIGH);
      // int d = duration * 0.034 / 2 * 10;

      // // Add reading to buffer and calculate moving average
      // buffer[bufferIndex] = d;
      // bufferIndex = (bufferIndex + 1) % bufferSize;

      // float average = 0;

      // for (int i = 0; i < bufferSize; i++) 
      //   average += buffer[i];

      // average += d;
      
      // average /= bufferSize + 1;
      // this->jarak = average;
    }
};
