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
      depan(45),
      belakang(44),
      KiD(44),
      KaD(47),
      KiB(45),
      KaB(48)
    {}
    void init(){
      depan.init();
      belakang.init();
      KiD.init();
      KaD.init();
      KiB.init();
      KaB.init();
    }
    // int jarakKiri() {
    //   return kiri.jarak;
    // }
    
    // int jarakKanan() {
    //   return kanan.jarak;
    // }

    // int jarakDepan() {
    //   return depan.jarak;
    // }

    // int jarakBelakang() {
    //   return belakang.jarak;
    // }

    // void readAllJarak(){
    //   depan.bacaJarak();
    //   belakang.bacaJarak();
    //   kiri.bacaJarak();
    //   kanan.bacaJarak();
    // }
    
    void printJarak() {
      Serial.print("Kiri Depan: ");
      Serial.print(KiD.bacaJarak());
      Serial.print(", ");
      Serial.print("Kiri Bekakang: ");
      Serial.print(KiB.bacaJarak());
      Serial.print(", ");
      Serial.print("Kanan Depan: ");
      Serial.print(KaD.bacaJarak());
      Serial.print(", ");
      Serial.print("Kanan Depan: ");
      Serial.print(KaB.bacaJarak());
      Serial.print(", ");
      Serial.print("Depan: ");
      Serial.print(depan.bacaJarak());
      Serial.print(", ");
      Serial.print("Belakang: ");
      Serial.println(belakang.bacaJarak());
    }
};
