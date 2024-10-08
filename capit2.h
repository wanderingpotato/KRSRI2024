#include <Dynamixel2Arduino.h> // Harus ada library Servo.h

// Pin Capit sesuaikan dengan yang ada di arduino
#define pinLengan 
#define pinCapitan 2

class Capit{
  private:
    Servo lengan;
    Servo capitan;

  public:
    Capit(){}
    
    // Inisialisasi capit langsung ke point awal (atas) dari capit
    void init(){
      lengan.attach(pinLengan);
      // capitan.attach(pinCapitan);
      delay(10);
      // Bagian atas untuk attach servo ke pin

      lengan.write(0);
      // capitan.write(0);
      delay(200);

      // Bagian atas untuk mengset langsung servo ke posisi awal
    }

    void tutupCapit(){
      capitan.write(0);
      delay(200);
      // Menutup Capit dengan sudut 0 derajat
    }

    void bukaCapit(){
      capitan.write(65);
      delay(200);
      // Membuka Capit dengan sudut 60 derajat
    }

    void naikLengan(){ 
      for(int pos = 135 ; pos >= 0 ; pos -= 5){
          lengan.write(pos);
          delay(65);
      }
      // Prosedur untuk menaikan lengan secara perlahan dengan kecepatan 5 derajat per 65ms sampai 135 derajat maksimal
    }

     void naikLenganDikit(){ 
      for(int pos = 135 ; pos >= 110 ; pos -= 5){
          lengan.write(pos);
          delay(65);
      }
      // Prosedur untuk menaikan lengan secara perlahan dengan kecepatan 5 derajat per 65ms sampai 135 derajat maksimal
    }

    void naikLenganLanjutan(){
      for(int pos = 110 ; pos >= 0 ; pos -= 5){
          lengan.write(pos);
          delay(65);
      }
    }

    void turunLengan(){
      for(int pos = 0 ; pos <= 135 ; pos += 5){
          lengan.write(pos);
          delay(65);
      }
      // Prosedur untuk menurunkan lengan secara perlahan dengan kecepatan 5 derajat per 65ms sampai 135 derajat maksimal
    }
};
