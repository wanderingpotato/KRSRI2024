#include "SensorJarak.h"

class SensorJarakGroup {
  private:
    SensorJarak depan;
    SensorJarak belakang;
    SensorJarak KiD;
    SensorJarak KaD;
    SensorJarak KiB;
    SensorJarak KaB;

  public:
    SensorJarakGroup() :
      depan(44),
      belakang(45),
      KiD(47),
      KaD(46),
      KiB(48),
      KaB(49)
    {}

    int jarakKiri() {
      return kiri.jarak;
    }
    
    int jarakKanan() {
      return kanan.jarak;
    }

    int jarakDepan() {
      return depan.jarak;
    }

    int jarakBelakang() {
      return belakang.jarak;
    }

    void readAllJarak(){
      depan.resetTrigger();
      belakang.resetTrigger();
      // kiri.resetTrigger();
      // kanan.resetTrigger();
      delayMicroseconds(2);
      depan.highTrigger();
      belakang.highTrigger();
      kiri.highTrigger();
      kanan.highTrigger();
      delayMicroseconds(10);
      depan.bacaJarak();
      belakang.bacaJarak();
      kiri.bacaJarak();
      kanan.bacaJarak();
    }
    
    void printJarak() {
      // Serial.print("Kiri: ");
      // Serial.print(jarakKiri());
      // Serial.print(", ");
      // Serial.print("Kanan: ");
      // Serial.print(jarakKanan());
      Serial.print(", ");
      Serial.print("Belakang: ");
      Serial.print(jarakBelakang());
      Serial.print(", ");
      Serial.print("Depan: ");
      Serial.println(jarakDepan());
    }
};
