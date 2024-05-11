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
      depan(41,01),
      belakang(35,02),
      KiD(47,03),
      KaD(45,04),
      KiB(49,05),
      KaB(51,06)
    {}
    void init(){
      delay(100);
      SetInitAll();
      delay(100);
      depan.setAddress();
      delay(100);
      belakang.setAddress();
      delay(100);
      KiD.setAddress();
      delay(100);
      KaD.setAddress();
      delay(100);
      KiB.setAddress();
      delay(100);
      KaB.setAddress();
      delay(100);
      
      StartAll();

      // SetHighAll();
      // delay(100);
      
      
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
    void StartAll(){
      depan.Start();
      belakang.Start();
      KiD.Start();
      KaD.Start();
      KiB.Start();
      KaB.Start();
    }
    void SetInitAll(){
      depan.init();
      belakang.init();
      KiD.init();
      KaD.init();
      KiB.init();
      KaB.init();
    }
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
      Serial.print("Kanan Belakang: ");
      Serial.print(KaB.bacaJarak());
      Serial.print(", ");
      Serial.print("Depan: ");
      Serial.print(depan.bacaJarak());
      Serial.print(", ");
      Serial.print("Belakang: ");
      Serial.println(belakang.bacaJarak());
    }
};
