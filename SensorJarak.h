class SensorJarak {
  private:
    int infraPin;
    VL53L0X sensor;
    uint8_t address;
    // float *buffer;
    // int bufferSize = 5;
    // int bufferIndex;
  
  public:
    float jarak;
    
    SensorJarak(int infraPin,uint8_t address) {
      jarak = 0;
      this->address= address;
      this->infraPin=infraPin;


    }
    void setAddress(){

      setHigh();
      delay(150);
      
      if (!sensor.init())
      {
        Serial.print(this->infraPin);
        Serial.println("Failed to detect and initialize sensor!");
        // while (1) {}
      }
      delay(150);
      sensor.setAddress(this->address);
      // sensor.setTimeout(500);
    }

    void init(){
      pinMode(this->infraPin, OUTPUT);
      setLow();
      delay(10);
      setHigh();
      delay(10);
      setLow();
    }
    void Start(){
      sensor.startContinuous();
    }
    float bacaJarak() {
      return sensor.readRangeContinuousMillimeters();
    }
    void setLow(){
      digitalWrite(this->infraPin, LOW);
    }
    void setHigh(){
      digitalWrite(this->infraPin, HIGH);
    }
};
