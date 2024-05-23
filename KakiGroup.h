#include "Kaki.h"
static float t = 0.3; // Mengatur banyak langkah dari kaki

class KakiGroup{
  private:
    Kaki LF; // Kiri Depan
    Kaki LM; // Kiri Tengah
    Kaki LB; // Kiri Belakang
    Kaki RF; // Kanan Depan
    Kaki RM; // Kanan Tengah
    Kaki RB; // Kanan Belakang

    /*change 180 (?)*/
    vec3_t standPoint[nStandPoint] = {
          {80, -68, 0}, //Normal 0 - 90
          {80, -60, 0}, // 10-80
          {80, -50, 0}, //rendah 15-75
          {80, -45, 0}, //20-70
          {0,-20, 32}, //25-65
          {0,-18, 32}  //Tinggi 30 - 60
        }; //Array titik berdiri 
    vec3_t tinggi[nStandPoint] = {
          {0,-20,0}, //Normal 0 - 90
          {0,-40,0},  // 10-80
          {0,-30,0},  //15-75
          {0,-65,0},  //20-70
          {0,-45,-4}, //25-65
          {0,-45,-3}  //Tinggi 30 - 60
      }; //Array tinggi default utk tiap StandPoint

  public:
    KakiGroup(){

      /*Thn 2023*/
      // LF = Kaki(1,2,3, KIRI, GRUP2, DEPAN); // Aslinya depan kanan RF
      // LM = Kaki(4,5,6, KIRI, GRUP1, TENGAH); // Aslinya tengah kanan RM
      // LB = Kaki(7,8,9, KIRI, GRUP2, BELAKANG); // Asllinya belakang kanan RB
      // RF = Kaki(10,11,12, KANAN, GRUP1, BELAKANG); // Aslinya belakang kiri LB
      // RM = Kaki(13,14,15, KANAN, GRUP2, TENGAH); // Aslinya tengah kiri LM 
      // RB = Kaki(16,17,18, KANAN, GRUP1, DEPAN); // Aslinya depan kiri LF
// GRUP2
// GRUP1
      /*Thn 2024*/
      LF = Kaki(16,17,18, KIRI, GRUP2, DEPAN); // Aslinya depan kanan RF
      LM = Kaki(13,14,15, KIRI, GRUP1, TENGAH); // Aslinya tengah kanan RM
      LB = Kaki(10,11,12, KIRI, GRUP2, BELAKANG); // Asllinya belakang kanan RB
      RB = Kaki(7,8,9, KANAN, GRUP1, BELAKANG); // Aslinya belakang kiri LB
      RM = Kaki(4,5,6, KANAN, GRUP2, TENGAH); // Aslinya tengah kiri LM 
      RF = Kaki(1,2,3, KANAN, GRUP1, DEPAN); // Aslinya depan kiri LF
    }
    
    void init(){
      // Set kaki ke poin 0 semua (robot akan jatuh bila tidak menumpu pada sesuatu, hati")
      LF.init();
      RF.init();
      LM.init();
      RM.init();
      LB.init();
      RB.init();
    }
    
    void setDepan(int tim){
      switch(tim){
        case 1:
          LF.setpos(KIRI);
          LB.setpos(KANAN);
          RM.setpos(KIRI);
          LM.setpos(KANAN);
          RF.setpos(KIRI);
          RB.setpos(KANAN);
          break;

        case 2:
          RF.setpos(KIRI);
          LM.setpos(KIRI);
          RB.setpos(KANAN);
          RM.setpos(KANAN);
          LF.setpos(KIRI);
          LB.setpos(KANAN);
          break;

        case 0:
          LF.setpos(KIRI); 
          LM.setpos(KIRI); 
          LB.setpos(KIRI); 
          RB.setpos(KANAN); 
          RM.setpos(KANAN);
          RF.setpos(KANAN); 
          break;
      }
    }
    void berdiri(int tipeLangkah){
      // Set kaki ke poin berdiri (standpoint)
      LF.berdiri(this->standPoint[tipeLangkah]);
      RF.berdiri(this->standPoint[tipeLangkah]);
      LM.berdiri(this->standPoint[tipeLangkah]);
      RM.berdiri(this->standPoint[tipeLangkah]);
      LB.berdiri(this->standPoint[tipeLangkah]);
      RB.berdiri(this->standPoint[tipeLangkah]);
    }

    // void berdiriSamping(int tipeLangkah){
    //   // Set kaki ke poin berdiri (standpoint)
    //   vec3_t sudutSampingL = {22,0,-10};
    //   vec3_t sudutSampingR = {-22,0,-10};
    //   vec3_t newStandPointL = this->standPoint[tipeLangkah] + sudutSampingL;
    //   vec3_t newStandPointR = this->standPoint[tipeLangkah] + sudutSampingR;
      
    //   LF.berdiri(newStandPointL);
    //   RF.berdiri(newStandPointL);
    //   LM.berdiri(this->standPoint[tipeLangkah]);
    //   RM.berdiri(this->standPoint[tipeLangkah]);
    //   LB.berdiri(newStandPointR);
    //   RB.berdiri(newStandPointR);
    // }
    
    void langkah(ArduinoQueue<vec3_t> stepsMaju, ArduinoQueue<vec3_t> stepsMundur, int speed, int delayLangkah){
      do{
        vec3_t tempMaju = stepsMaju.dequeue();
        vec3_t tempMundur = stepsMundur.dequeue();
        LF.langkah(tempMaju,tempMundur, speed);
        RF.langkah(tempMaju,tempMundur, speed);
        LM.langkah(tempMaju,tempMundur, speed);
        RM.langkah(tempMaju,tempMundur, speed);
        LB.langkah(tempMaju,tempMundur, speed);
        RB.langkah(tempMaju,tempMundur, speed);
        delay(delayLangkah);
      }while(!stepsMaju.isEmpty() && !stepsMundur.isEmpty());
    }

    void langkahPutar(ArduinoQueue<vec3_t> stepsMaju, ArduinoQueue<vec3_t> stepsMundur, int speed, int delayLangkah){
      do{
        vec3_t tempMaju = stepsMaju.dequeue();
        vec3_t tempMundur = stepsMundur.dequeue();
        LF.langkahPutar(tempMaju,tempMundur, speed);
        RF.langkahPutar(tempMaju,tempMundur, speed);
        LM.langkahPutar(tempMaju,tempMundur, speed);
        RM.langkahPutar(tempMaju,tempMundur, speed);
        LB.langkahPutar(tempMaju,tempMundur, speed);
        RB.langkahPutar(tempMaju,tempMundur, speed);
        delay(delayLangkah);
      }while(!stepsMaju.isEmpty() && !stepsMundur.isEmpty());
    }

    void Langkahnyamping(ArduinoQueue<vec3_t> stepsMaju, ArduinoQueue<vec3_t> stepsMundur, ArduinoQueue<vec3_t> stepsTMu,ArduinoQueue<vec3_t> stepsTMa,int speed, int delayLangkah){
      do{
        vec3_t tempMaju = stepsMaju.dequeue();
        vec3_t tempMundur = stepsMundur.dequeue();
        vec3_t tempTMa = stepsTMa.dequeue();
        vec3_t tempTMu = stepsTMu.dequeue();

        LF.samping(tempMaju,tempMundur,tempTMa,tempTMu, speed);
        RF.samping(tempMaju,tempMundur,tempTMa,tempTMu, speed);
        LM.samping(tempMaju,tempMundur,tempTMa,tempTMu, speed);
        RM.samping(tempMaju,tempMundur,tempTMa,tempTMu, speed);
        LB.samping(tempMaju,tempMundur,tempTMa,tempTMu, speed);
        RB.samping(tempMaju,tempMundur,tempTMa,tempTMu, speed);
        delay(delayLangkah);
      }while(!stepsMaju.isEmpty() && !stepsMundur.isEmpty());
    }
    void jalan(int dir, int tipeLangkah, float derajat, int height, int speed, int delayLangkah){
      vec3_t tinggi = this->tinggi[tipeLangkah]; // Mengatur ketinggian dari langkah
      //jika custom
      if(height > 0)
        tinggi = {0, -height, this->tinggi[tipeLangkah].z};
          
      vec3_t P1 = rotateMatrix(this->standPoint[tipeLangkah], derajat * dir);
      vec3_t P4 = rotateMatrix(this->standPoint[tipeLangkah], (-derajat) * dir);

      // Mengatur perputaran kaki saat bergerak, dapat mempercepat langkah bila lebih besar
      vec3_t naik = tinggi + this->standPoint[tipeLangkah];
      
      langkah(trajectory(P4,naik,P1), trajectory(P1,this->standPoint[tipeLangkah],P4), speed, delayLangkah);
      langkah(trajectory(P1,this->standPoint[tipeLangkah],P4), trajectory(P4,naik,P1), speed, delayLangkah);
      // Passing fungsi langsung, bila menggunakan variabel tambahan berkemungkinan error dan tidak berjalan
    }

    void putar(int dir, int tipeLangkah, float derajat, int height, int speed, int delayLangkah){
      vec3_t tinggi = this->tinggi[tipeLangkah]; // Mengatur ketinggian dari langkah
      //jika custom
      if(height > 0)
        tinggi = {0, -height, this->tinggi[tipeLangkah].z};
          
      vec3_t P1 = rotateMatrix(this->standPoint[tipeLangkah], derajat * dir);
      vec3_t P4 = rotateMatrix(this->standPoint[tipeLangkah], (-derajat) * dir);

      // Mengatur perputaran kaki saat bergerak, dapat mempercepat langkah bila lebih besar
      vec3_t naik = tinggi + this->standPoint[tipeLangkah];
      
      langkahPutar(trajectory(P4,naik,P1), trajectory(P1,this->standPoint[tipeLangkah],P4), speed, delayLangkah);
      langkahPutar(trajectory(P1,this->standPoint[tipeLangkah],P4), trajectory(P4,naik,P1), speed, delayLangkah);
    }

    void nyamping(int dir, int tipeLangkah, float derajat, int height, int speed, int delayLangkah){
      vec3_t tinggi = this->tinggi[tipeLangkah]; // Mengatur ketinggian dari langkah
      //jika custom
      if(height > 0)
        tinggi = {0, -height, this->tinggi[tipeLangkah].z};
          
      vec3_t P1 = rotateMatrix(this->standPoint[tipeLangkah], derajat * dir);
      vec3_t P5 = this->standPoint[tipeLangkah];
      P5.x-=15;
      vec3_t P4 = rotateMatrix(this->standPoint[tipeLangkah], (-derajat) * dir);

      // Mengatur perputaran kaki saat bergerak, dapat mempercepat langkah bila lebih besar
      vec3_t naik = tinggi + this->standPoint[tipeLangkah];
      
      Langkahnyamping(trajectory(P4,naik,P1), trajectory(P1,this->standPoint[tipeLangkah],P4), trajectory(naik, this->standPoint[tipeLangkah], P5),trajectory(P5, this->standPoint[tipeLangkah], naik), speed, delayLangkah);
      Langkahnyamping(trajectory(P1,this->standPoint[tipeLangkah],P4), trajectory(P4,naik,P1),trajectory(P5,this->standPoint[tipeLangkah],naik),trajectory(naik,this->standPoint[tipeLangkah],P5), speed, delayLangkah);
      // Langkahnyamping(trajectory(P4,naik,P1), trajectory(P1,this->standPoint[tipeLangkah],P4), trajectory(this->standPoint[2], this->standPoint[2], this->standPoint[2]),trajectory(this->standPoint[2], this->standPoint[2], this->standPoint[2]), speed, delayLangkah);
      // Langkahnyamping(trajectory(P1,this->standPoint[tipeLangkah],P4), trajectory(P4,naik,P1),trajectory(this->standPoint[2],this->standPoint[2],this->standPoint[2]),trajectory(this->standPoint[2],this->standPoint[2],this->standPoint[2]), speed, delayLangkah);
    }

    //Untuk keperluan testing StandPoint Baru
    void berdiriDebug(vec3_t standPoint){
      // Set kaki ke poin berdiri (standpoint)
      LF.berdiri(standPoint);
      RF.berdiri(standPoint);
      LM.berdiri(standPoint);
      RM.berdiri(standPoint);
      LB.berdiri(standPoint);
      RB.berdiri(standPoint);
    }
    
    //Untuk keperluan testing StandPoint Baru
    void jalanDebug(int dir, vec3_t standPoint, float derajat, vec3_t tinggi, int speed, int delayLangkah){
      vec3_t P1 = rotateMatrix(standPoint, derajat * dir);
      vec3_t P4 = rotateMatrix(standPoint, (-derajat) * dir);

      // Mengatur perputaran kaki saat bergerak, dapat mempercepat langkah bila lebih besar
      vec3_t naik = tinggi + standPoint;

      langkah(trajectory(P1,naik,P4), trajectory(P4,standPoint,P1), speed, delayLangkah);
      langkah(trajectory(P4,standPoint,P1), trajectory(P1,naik,P4), speed, delayLangkah);
      // Passing fungsi langsung, bila menggunakan variabel tambahan berkemungkinan error dan tidak berjalan
    }
};
