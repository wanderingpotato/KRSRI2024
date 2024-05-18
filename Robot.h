#include "Arduino.h"
#include "KakiGroup.h"
#include "Capit.h"
#include "SensorJarakGroup.h"
#include "Kamera.h"
#include "Sweeper.h"
#include "Kompas.h"

class Robot
{
private:
  KakiGroup kaki;
  SensorJarakGroup jarak;
  Kamera kamera;
  // Sweeper sweeper;

  Kompas kompas;

public:
  Capit capit;
  // parameter robot
  int tipeLangkah = NORMAL;     // jenis langkah
  float derajatLangkah = 20;       // besar langkah kaki saat jalan
  float derajatLangkahSetPos = 10; // besar langkah kaki saat mengoreksi diri
  int height = DEFAULT;            // tinggi langkah kaki, sebaiknya tidak diubah
  int direction = FRONT;           // arah hadap robot, akan diupdate scr otomatis setiap mutar
  int offsetDirection = 5;         // kemiringan robot terhadap direction yg dihadap robot, pos ke kanan, min ke kiri
  int movingType = STAY;           // jenis gerakan STAY-MOVING-ROTATING
  int movingDirection = STAY;      // arah gerakan MAJU-MUNDUR-KIRI-KANAN
  float error = 10.0;              // toleransi selisih error yaw Real robot dengan direction robot
  int speed = 300;                 // kecepatan motor
  int delayLangkah = 10;          // delay antar langkah
  bool isHoldingKorban = false;    // Apakah robot sedang memegang korban atau tidak
  int targetSizeKorban = 35;
  int kondisiTargetJarakMin[4] = {0, 0, 0, 0}; // kondisi target dari ke-4 jarak, jika 0 abaikan
  int kondisiTargetJarakMax[4] = {0, 0, 0, 0}; // jarak sebenarnya lebih kecil daripada kondisi
  int kondisiTargetRollMin = 0;                // kondisi target dari roll, jika 0 abaikan
  int kondisiTargetRollMax = 0;
  int DeragatLengan = TNormal;
  int state = 0; // state dari robot, set MANUALMODE jika ingin diatur manual
  /*
   * yaw[0] -> depan
   * yaw[1] -> kiri
   * yaw[2] -> kanan
   * yaw[3] -> belakang
   */
  double yaw[4] = {0, 0, 0, 0}; // simpan lokasi arah robot menggunakan kompas

  Robot() {}

  void printState()
  {
    Serial3.print("S: ");
    Serial3.print(state);
    Serial3.print(" TL: ");
    Serial3.print(tipeLangkah);
    Serial3.print(" DL: ");
    Serial3.print(derajatLangkah);
    Serial3.print(" H: ");
    Serial3.print(height);
    Serial3.print(" Arah: ");
    Serial3.print(direction);
    Serial3.print(" Offset: ");
    Serial3.print(offsetDirection);
    Serial3.print(" MT: ");
    Serial3.print(movingType);
    Serial3.print(" MD: ");
    Serial3.print(movingDirection);
    Serial3.print(" E: ");
    Serial3.print(error);
    Serial3.print(" Speed: ");
    Serial3.print(speed);
    Serial3.print(" Delay: ");
    Serial3.print(delayLangkah);
    Serial3.print(" korban: ");
    Serial3.print(isHoldingKorban);
    Serial3.print(" MinU: ");
    for (int i = 0; i < 4; i++)
    {
      Serial3.print(kondisiTargetJarakMin[i]);
      Serial3.print(',');
    }
    Serial3.print(" MaxU:  ");
    for (int i = 0; i < 4; i++)
    {
      Serial3.print(kondisiTargetJarakMax[i]);
      Serial3.print(',');
    }
    Serial3.print(" MinR: ");
    Serial3.print(kondisiTargetRollMin);
    Serial3.print(" MaxR: ");
    Serial3.println(kondisiTargetRollMax);
    cetakYaw();
    Serial3.println("------------------------------");
  }

  void init()
  {
    kaki = KakiGroup();
    jarak = SensorJarakGroup();
    kamera.init();
    kompas.init();
    capit.init();
    
    jarak.init();
    kaki.init();
    // capit.turunLengan(this->DeragatLengan);
    delay(100);
    kaki.berdiri(tipeLangkah);
    // capit.turunLenganFull();
    // testDebug();
  }

  void testDebug(){
    while(1){
      // kamera.test();
      // jarak.printJarak();
      //  rotate(KaP, DEFAULT, 5, 20, this->tipeLangkah, this->speed, this->delayLangkah);
      //  kepiting(1, DEFAULT, 20, this->tipeLangkah, this->speed, this->delayLangkah);
      //  move(MAJU, DEFAULT, this->derajatLangkah, SEDANG_20, this->speed, 100);
    }
  }

  void initManualMode()
  {
    yaw[FRONT] = getYaw();

    yaw[BACK] = yaw[FRONT] + 180;
    yaw[LEFT] = yaw[FRONT] - 90;
    yaw[RIGHT] = yaw[FRONT] + 90;
  }

  void berdiri()
  {
    berdiri(this->tipeLangkah);
  }

  void berdiri(int tipeLangkah)
  {
    kaki.berdiri(tipeLangkah);
    // reset state
    this->movingType = STAY;
    this->movingDirection = STAY;
    for (int i = 0; i < 4; i++)
    {
      this->kondisiTargetJarakMin[i] = 0;
      this->kondisiTargetJarakMax[i] = 0;
    }
    this->kondisiTargetRollMin = 0;
    this->kondisiTargetRollMax = 0;
  }

  void maju()
  {
    move(MAJU, DEFAULT, this->derajatLangkah, this->tipeLangkah, this->speed, this->delayLangkah);
  }

  void mundur()
  {
    move(MUNDUR, DEFAULT, this->derajatLangkah, this->tipeLangkah, this->speed, this->delayLangkah);
  }
  void KKiri(){
    kepiting(KiP, DEFAULT, this->derajatLangkah, this->tipeLangkah, this->speed, this->delayLangkah);
  }
  void KKanan(){
    kepiting(KaP, DEFAULT, this->derajatLangkah, this->tipeLangkah, this->speed, this->delayLangkah);
  }
  void move()
  {
    switch (this->movingType)
    {
    case MOVING:
    {
      switch (this->movingDirection)
      {
        case MAJU:
        {
          maju();
          break;
        }
        case MUNDUR:
        {
          mundur();
          break;
        }
        case Kasu:
        {
          KKanan();
          // state++;
          break;
        }
        case Kari:
        {
          KKiri();
          // state++;
          break;
        }
      }
      break;
    }
    case ROTATING:
    {
      switch (this->movingDirection)
      {
        case KIRI:
        {
          kiri();
          break;
        }
        case KANAN:
        {
          kanan();
          break;
      }
      case STAY:
      {
        if (this->offsetDirection != 0)
        {
          rotateToOffSet();
        }
      }
      }
      break;
    }
    }
  }

  void move(int action, int height, float derajat, int tipeLangkah, int speed, int delayLangkah)
  {
    // USE DEFAULT UNTUK HEIGHT BILA TIDAK MAU SPECIFY
    kaki.jalan(action, tipeLangkah, derajat, height, speed, delayLangkah);
  }

  void rotate(int action, int height, int step, float derajat, int tipeLangkah, int speed, int delayLangkah)
  {
    // DEFAULT DERAJAT (15 KIRI) (16 KANAN) 5 STEP
    for (int i = 0; i < step; i++)
    {
      kaki.putar(action, tipeLangkah, derajat, height, speed, delayLangkah);
    }
  }

  void kepiting(int action, int height, float derajat, int tipeLangkah, int speed, int delayLangkah)
  {
    // USE DEFAULT UNTUK HEIGHT BILA TIDAK MAU SPECIFY
    kaki.nyamping(action, tipeLangkah, derajat, height, speed, delayLangkah);
  }
  // Arahkan robot ke depan, dan inisialisai value Yaw
   void checkPosition(){
     // kalo depan kosong -> (jarak jauh) langsung skip sekuens ini
     // kalo kanan kosong -> putar kanan
     // kalo kiri kosong -> putar kiri
     // kalo belakang kosong -> putar balik dari kiri / kanan sama aja

    if(jarak.jarakBelakang() >= 280){ // Berarti lagi ngadep belakang
      yaw[BACK] = getYaw();

      yaw[FRONT] = yaw[BACK] + 180;
      yaw[RIGHT] = yaw[BACK] - 90;
      yaw[LEFT] = yaw[BACK] + 90;
      rotate(KiP, DEFAULT, 5, 11, this->tipeLangkah, this->speed, this->delayLangkah);
      rotate(KiP, DEFAULT, 5, 11, this->tipeLangkah, this->speed, this->delayLangkah);
      setPos();
    }
    else if(jarak.jarakKiri() >= 280){ // Berarti lagi ngadep kanan
      yaw[RIGHT] = getYaw();

      yaw[LEFT] = yaw[RIGHT] + 180;
      yaw[FRONT] = yaw[RIGHT] - 90;
      yaw[BACK] = yaw[RIGHT] + 90;

      rotate(KiP, DEFAULT, 5, 11, this->tipeLangkah, this->speed, this->delayLangkah);
      setPos();
    }
    else if(jarak.jarakKanan() >= 280){ // Berarti lagi ngadep kiri
      yaw[LEFT] = getYaw();

      yaw[RIGHT] = yaw[LEFT] + 180;
      yaw[BACK] = yaw[LEFT] - 90;
      yaw[FRONT] = yaw[LEFT] + 90;

      rotate(KaP, DEFAULT, 5, 11, this->tipeLangkah, this->speed, this->delayLangkah);
      setPos();
    }
    else if(jarak.jarakDepan() >= 280){ // Ngadep depan
      yaw[FRONT] = getYaw();

      yaw[BACK] = yaw[FRONT] + 180;
      yaw[LEFT] = yaw[FRONT] - 90;
      yaw[RIGHT] = yaw[FRONT] + 90;
    }
    state++;
  }

  // Cetak value yaw dari robot
  void cetakYaw()
  {
    Serial3.print("Yaw Value: ");
    Serial3.print("F ");
    Serial3.print(yaw[0]); // depan
    Serial3.print(", ");
    Serial3.print("L ");
    Serial3.print(yaw[1]); // kiri
    Serial3.print(", ");
    Serial3.print("R ");
    Serial3.print(yaw[2]); // kanan
    Serial3.print(", ");
    Serial3.print("B ");
    Serial3.println(yaw[3]); // belakang
  }

  int getYaw()
  {
    return kompas.getCurrent().x;
  }

  int getPitch()
  {
    return kompas.getCurrent().y;
  }

  int getRoll()
  {
    return kompas.getCurrent().z;
  }

  int jarakDepan(){
    return jarak.jarakDepan();
  }

  int jarakBelakang(){
    return jarak.jarakBelakang();
  }

  int jarakKiri(){
    return jarak.jarakKiri();
  }

  int jarakKanan(){
    return jarak.jarakKanan();
  }

  bool checkKorban()
  {
    return (kamera.getX() == -1) ? false : true;
  }
  void getKorban()
  {
    getKorban(DEFAULT, 10, this->tipeLangkah, this->speed, this->targetSizeKorban);
    this->isHoldingKorban = true;
  }

  void getKorban(int height, float derajat, int tipeLangkah, int speed = 10, int targetSizeKorban = 85)
  {
    // USE " DEFAULT " JIKA TIDAK MAU SPECIFY HEIGHT
    // DEFAULT DERAJAT 10 NORMAL
    // DEFAULT DERAJAT 20 TINGGI

    int X, Y, W, H;
    X = Y = W = H = 0;
    berdiri(tipeLangkah);
    delay(200);
    
    capit.turunLengan(this->DeragatLengan);
    capit.bukaCapit();
    delay(500);
    kamera.getIndex();
    kamera.test();
    int step = 0;
    int end = 4;
    int arah = KiP;
    while (kamera.getX() == -1)
    {
      if (step == end)
      {
        if (end == 4)
        {
          step = 8;
        }
        // arah = (arah == KiP) ? KaP : KiP;
      }
      // rotate(arah, DEFAULT, 1, 7, this->tipeLangkah, this->speed, this->delayLangkah);
      // readUltrasonic();
      step++;
    }

    while (1)
    {
      X = kamera.getX();
      Y = kamera.getY();

      // Serial3.print(X);
      // Serial3.print(" ");
      // Serial3.print(Y);
      // Serial3.println(" ");
      if (X >= 175)
      {
        rotate(KaP, height, 1, 5, tipeLangkah, speed, this->delayLangkah);
        // readUltrasonic();
      }
      else if (X >= 0 && X <= 125)
      {
        rotate(KiP, height, 1, 5, tipeLangkah, speed, this->delayLangkah);
        // readUltrasonic();
      }
      else
      {
        move(MAJU, height, derajat, tipeLangkah, speed, this->delayLangkah);
        // readUltrasonic();kzc
      }

      W = kamera.getWidth();
      H = kamera.getHeight();
      
      // kamera.kameraPrintLocation();

      if (W - H >= targetSizeKorban)
      {
        if (state == 4)
        {
          break;
        }
        int count = 1;
        int max = 2;
        while (W - H >= targetSizeKorban && count <= max)
        {
          count++;
          delay(1000);
        }
        if (count > max)
        {
          break;
        }
      }
    }

    delay(500);
    capit.tutupCapit();
    berdiri(tipeLangkah);
    capit.naikLengan();
    // capit.naikLenganDikit();
    for (int i = 0; i < 2; i++)
    {
      move(MUNDUR, height, derajat, tipeLangkah, speed, this->delayLangkah);
      // readUltrasonic();
    }
    delay(50);
    // capit.naikLenganLanjutan();
    state++;
  }
  void letakanKorban()
  {
    capit.turunLengan(this->DeragatLengan);
    capit.bukaCapit();
    for (int i = 0; i < 2; i++)
    {
      move(MUNDUR, DEFAULT, this->derajatLangkah, this->tipeLangkah, this->speed, this->delayLangkah);
      // readUltrasonic();
    }
    capit.naikLengan();
    capit.tutupCapit();
    this->isHoldingKorban = false;
    state++;
  }

  void rotateToOffSet()
  {
    setPos();
    berdiri();
    state++;
  }

  void changeDirToKiri()
  {
    switch (this->direction)
    {
    case FRONT:
    {
      this->direction = LEFT;
      break;
    }
    case LEFT:
    {
      this->direction = BACK;
      break;
    }
    case RIGHT:
    {
      this->direction = FRONT;
      break;
    }
    case BACK:
    {
      this->direction = RIGHT;
      break;
    }
    }
  }

  void kiri()
  {
    rotate(KiP, DEFAULT, 4, 16, this->tipeLangkah, this->speed, this->delayLangkah);
    changeDirToKiri();
    berdiri();
    state++;
  }

  void changeDirToKanan()
  {
    switch (this->direction)
    {
    case FRONT:
    {
      this->direction = RIGHT;
      break;
    }
    case LEFT:
    {
      this->direction = FRONT;
      break;
    }
    case RIGHT:
    {
      this->direction = BACK;
      break;
    }
    case BACK:
    {
      this->direction = LEFT;
      break;
    }
    }
  }

  void kanan()
  {
    rotate(KaP, DEFAULT, 4, 16, this->tipeLangkah, this->speed, this->delayLangkah);
    changeDirToKanan();
    berdiri();
    state++;
  }

  void setPos()
  {
    setPos(this->direction, DEFAULT, this->offsetDirection, this->error, this->derajatLangkahSetPos, this->tipeLangkah, this->speed, this->delayLangkah);
  }
  /*
   * Untuk rotasi sesuai arah atau penyearah robot sesuai kompas
   * Set DEFAULT utk index, height, set, error, tipelangkah jika tidak dicustom
   * Default VALUE
   * index = 0 Depan
   * height -> tinggi default sesuai tipeLangkah
   * set 0
   * error = 2
   * tipeLangkah -> NORMAL
   * Speed = 10, tidak perlu diberi value jika tidak ingin diubah
   */
  void setPos(int index, int height, int set, int error, float derajat, int tipeLangkah, int speed, int delayLangkah)
  {

    // DEFAULT value utk error
    if (error == 0)
      error = 2;

    int simpan = getYaw();
    int simpanNext = simpan;
    int putar = 0;

    while (simpanNext < yaw[index] - error + set || simpanNext > yaw[index] + error + set)
    {
      simpanNext = getYaw();
      // Jika dari putaran kanan
      if ((simpan >= 270 && simpan <= 360) && (simpanNext >= 0 && simpanNext <= 90))
      {
        putar++;
      }
      if ((simpan >= 360 && simpan <= 450) && (simpanNext >= 270 && simpanNext <= 360))
      {
        putar--;
      }
      // jika dari putaran kiri
      if ((simpanNext >= 270 && simpanNext <= 360) && (simpan >= 0 && simpan <= 90))
      {
        putar--;
      }
      if ((simpanNext >= 360 && simpanNext <= 450) && (simpan >= 270 && simpan <= 360))
      {
        putar++;
      }
      // digunakan hanya jika dia lagi menuju ke yaw yang berada diperbatasan 360
      if (yaw[index] >= 345 && yaw[index] <= 375)
      {
        simpanNext += putar * 360;
        if (simpanNext < 90)
        {
          putar++;
          simpanNext += putar * 360;
        }
      }

      if (simpanNext < yaw[index] - error + set)
      {
        rotate(KaP, height, 1, derajat, tipeLangkah, speed, delayLangkah);
        // readUltrasonic();
      }

      if (simpanNext > yaw[index] + error + set)
      {
        rotate(KiP, height, 1, derajat, tipeLangkah, speed, delayLangkah);
        // readUltrasonic();
      }

      simpan = simpanNext;
    }
    // update state robot
    this->direction = index;
    this->offsetDirection = set;
  }

  // Untuk keperluan testing StandPoint
  void berdiriDebug(vec3_t standPoint)
  {
    kaki.berdiriDebug(standPoint);
  }
  // Untuk keperluan testing StandPoint
  void moveDebug(int action, vec3_t tinggi, float derajat, vec3_t standPoint, int speed, int delayLangkah)
  {
    // USE DEFAULT UNTUK HEIGHT BILA TIDAK MAU SPECIFY
    kaki.jalanDebug(action, standPoint, derajat, tinggi, speed, delayLangkah);
  }
  // Print kompas
  void printCurrentYPR()
  {
    kompas.printCurrent();
  }
  // print ultrasonic
  void printJarak()
  {
    jarak.printJarak();
  }

  void printKamera()
  {
    kamera.kameraPrintLocation();
  }
};
