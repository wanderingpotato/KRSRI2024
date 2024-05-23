#include "header.h"
#include "Robot.h"

Robot KSR2024;
void cekKondisi();
void setup(){
    // digitalRead()
    // ax12a.begin(BaudRate, DirectionPin, &Serial3); // inisialisasi AX12A
    Wire.begin();
    Serial3.begin(9600);
    // Serial.begin(9600);
    // Serial.println("test");
    // KSR2024.init();
    // delay(1000);
    //Untuk mulai dari state tertentu
//     KSR2024.initManualMode();
//     KSR2024.state = 18;
  DEBUG_SERIAL.begin(115200);
  dxl.begin(57600);
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);
  KSR2024.init();
  // KSR2024.state = 13; //
  // KSR2024.tipeLangkah=SEDANG_10;
}

void loop(){
  // KSR2024.printJarak();
  switch(KSR2024.state){
    //init

     case 0:{
        KSR2024.checkPosition();
        // delay(500);
        // KSR2024.state=13;
        break;
     }
//      //menuju korban
     case 1:{
        KSR2024.kondisiTargetJarakMin[BACK] = 540;
        KSR2024.movingType = MOVING;
        KSR2024.movingDirection = MAJU;
        break; 
     }
//      //hadap korban
     case 2:{
        KSR2024.movingType = ROTATING;
        KSR2024.movingDirection = KIRI;
        KSR2024.offsetDirection = 0;
        break; 
     }
//      //mundur utk meluruskan
     case 3:{
        KSR2024.kondisiTargetJarakMax[BACK] = 130;
        KSR2024.movingType = MOVING;
        KSR2024.movingDirection = MUNDUR;
        KSR2024.derajatLangkah = 10;
        break; 
     }
//      //ambil korban pertama
     case 4:{
        KSR2024.derajatLangkah = 10;
        KSR2024.getKorban();
        break; 
     }
//      //mundur menyesuaikan dengan jalan retak
     case 5:{
        KSR2024.kondisiTargetJarakMax[BACK] = 130;
        KSR2024.movingType = MOVING;
        KSR2024.movingDirection = MUNDUR;
        KSR2024.derajatLangkah = 10;
        break; 
     }
//      //hadap depan
     case 6:{
        KSR2024.movingType = ROTATING;
        KSR2024.movingDirection = KANAN;
        KSR2024.derajatLangkah = 20; // direset kembali
        break; 
     }
//      //maju sampai mentok
     case 7:{
        KSR2024.kondisiTargetJarakMin[BACK] = 580;
        KSR2024.movingType = MOVING;
        KSR2024.movingDirection = MAJU;
        break; 
     }
//      //maju jalan retak
     case 8:{
        KSR2024.kondisiTargetRollMax = -12;
        KSR2024.tipeLangkah = SEDANG_20;
        KSR2024.derajatLangkah = 20;
        KSR2024.delayLangkah = 100;
        KSR2024.error = 12;
        KSR2024.derajatLangkahSetPos = 12;
        KSR2024.movingType = MOVING;
        KSR2024.movingDirection = MAJU;
        break; 
     }
//      //masuk jalan miring
     case 9:{
        KSR2024.kondisiTargetRollMin = -3;
        KSR2024.tipeLangkah = SEDANG_15;
        KSR2024.derajatLangkah = 20;
        KSR2024.delayLangkah = 100;
        KSR2024.error = 8;
        KSR2024.derajatLangkahSetPos = 8;
        KSR2024.movingType = MOVING;
        KSR2024.movingDirection = MAJU;
        break; 
     }
//      //masuk jalan batu
     case 10:{
        KSR2024.kondisiTargetJarakMax[FRONT] = 190;
        KSR2024.tipeLangkah = SEDANG_15;
        KSR2024.derajatLangkah = 20;
        KSR2024.delayLangkah = 100;
        KSR2024.error = 8;
        KSR2024.derajatLangkahSetPos = 8;
        KSR2024.movingType = MOVING;
        KSR2024.movingDirection = MAJU;
        break; 
     }
//      //belok kanan hadap safezone
     case 11:{
        // KSR2024.movingType = ROTATING;
        KSR2024.changeDirToKanan();
        KSR2024.offsetDirection = -55;
        KSR2024.state++;
        break;
     }
//       //maju sampai aman untuk letakkan korban
//      //letakkan korban pertama
     case 12:{
        
        KSR2024.letakanKorban();
        KSR2024.offsetDirection = 0;
        KSR2024.error = 5;
        KSR2024.derajatLangkahSetPos = 5;
        break; 
     }
//      //miring kanan jika kurang kiri atau mundur aja
     case 13: {
      
      KSR2024.error = 10;
      KSR2024.derajatLangkahSetPos = 10;
      KSR2024.derajatLangkah = 15;
       if(KSR2024.jarakKiri() >= 200){
          
          // KSR2024.PindahGroup(DKanan);
          KSR2024.movingType = MOVING;
          KSR2024.movingDirection = Kari;
       }
       else{
          KSR2024.state++;
       }
       break;
     }
     case 14:{
      KSR2024.tipeLangkah = SEDANG_20;
        // KSR2024.PindahGroup(0);
        KSR2024.derajatLangkah = 20;
        KSR2024.kondisiTargetJarakMin[FRONT] = 450;
        KSR2024.movingType = MOVING;
        KSR2024.movingDirection = MUNDUR;
        break;
     }
     case 15:{
        KSR2024.movingType = ROTATING;
        KSR2024.movingDirection = KANAN;
        break;
     }
     case 16:{
      KSR2024.kondisiTargetJarakMin[BACK] = 140;
      KSR2024.movingType = MOVING;
      KSR2024.movingDirection = MUNDUR;
      break;
     }
     case 17:{
        KSR2024.tipeLangkah = SEDANG_20;
        // KSR2024.getKorban2();
        KSR2024.state++;
        break;
     }
     case 18:{
        KSR2024.tipeLangkah = SEDANG_20;
        KSR2024.kondisiTargetJarakMin[BACK] = 140;
        KSR2024.movingType = MOVING;
        KSR2024.movingDirection = MUNDUR;
        break;
     }
     case 19:{
        KSR2024.movingType = ROTATING;
        KSR2024.movingDirection = KANAN;
        break;
     }
     case 20:{
        KSR2024.kondisiTargetJarakMin[BACK] = 500;
        KSR2024.movingType = MOVING;
        KSR2024.movingDirection = MAJU;
        break;
     }
     case 21:{
        //letak
        KSR2024.state++;
        break;
     }
     case 22:{
        KSR2024.changeDirToKiri();
        KSR2024.offsetDirection = -45;
        KSR2024.state++;
        break;
     }
     case 23:{
        KSR2024.kondisiTargetJarakMin[FRONT] = 150;
        KSR2024.movingType = MOVING;
        KSR2024.movingDirection = MAJU;
        break;
     }
     case 24:{
        KSR2024.tipeLangkah = NORMAL;
        KSR2024.offsetDirection = 0;
        KSR2024.state++;
        break;
     }
//      case 16:{
//         KSR2024.tipeLangkah = SEDANG_25;
//         KSR2024.derajatLangkah = 18;
//         KSR2024.delayLangkah = 150;
//         KSR2024.kondisiTargetJarakMax[LEFT] = 80;
//         KSR2024.movingType = MOVING;
//         KSR2024.movingDirection = MUNDUR;
//         KSR2024.error = 8;
//         KSR2024.derajatLangkahSetPos = 20;
//         break;  
//      }      
//      //Masuk ke kelereng
//      case 17:{
//         KSR2024.offsetDirection = 5;
//         KSR2024.tipeLangkah = SEDANG_25;
//         KSR2024.derajatLangkah = 18;
//         KSR2024.delayLangkah = 150;
//         KSR2024.kondisiTargetJarakMin[FRONT] = 400;
//         KSR2024.movingType = MOVING;
//         KSR2024.movingDirection = MUNDUR;
//         KSR2024.error = 8;
//         KSR2024.derajatLangkahSetPos = 10;
//         break;
//      }
//      //hadap ke boneka
//      case 18:{
//         KSR2024.offsetDirection = -10;
//         KSR2024.movingType = ROTATING;
//         KSR2024.movingDirection = KANAN;
//         KSR2024.error = 8;
//         KSR2024.derajatLangkahSetPos = 8;
//         break;
//      }
//      case 19:{
//         KSR2024.kondisiTargetJarakMin[BACK] = 130;
//         KSR2024.movingType = MOVING;
//         KSR2024.movingDirection = MAJU;
//         break;
//      }
//      //jalan ke boneka dan ambil
//      case 20:{
//         KSR2024.tipeLangkah = SEDANG_10;
//         KSR2024.derajatLangkah = 8;      
//         KSR2024.speed = 300;
//         KSR2024.delayLangkah = 10;
//         KSR2024.targetSizeKorban = 110;
//         KSR2024.getKorban();
//         break;
//      }
//      //mundur sampai dekat tembok untuk safe zone
//      case 21:{
//         KSR2024.tipeLangkah = SEDANG_25;
//         KSR2024.derajatLangkah = 18;
//         KSR2024.delayLangkah = 150;
//         KSR2024.kondisiTargetJarakMax[BACK] = 180;
//         KSR2024.movingType = MOVING;
//         KSR2024.movingDirection = MUNDUR;
//         KSR2024.error = 3;
//         KSR2024.derajatLangkahSetPos = 3;
//         break;
//      }
//      //hadap kanan keluar dari rintangan kelereng
//      case 22:{
//         KSR2024.movingType = ROTATING;
//         KSR2024.movingDirection = KANAN;
//         KSR2024.error = 5;
//         KSR2024.derajatLangkahSetPos = 5;
//         break;
//      }
//      //transisi
//      case 23:{
//         if(KSR2024.checkKorban()){
//           //dapat korban
//            KSR2024.state = 23;
//         }else{
//           //tidak dapat korban
//           KSR2024.offsetDirection = -35;
//           KSR2024.state = 26;
//         }
//         break;
//      }
//      //maju deket tembok safezone 2
//      case 24:{
//         KSR2024.offsetDirection = -10;
//         KSR2024.kondisiTargetJarakMax[FRONT] = 240;
//         KSR2024.movingType = MOVING;
//         KSR2024.movingDirection = MAJU;
//         break;
//      }
//      //hadap miring 35 derajat ke kanan untuk letakkin boneka
//      case 25:{
//         KSR2024.offsetDirection = 25;
//         KSR2024.movingType = ROTATING;
//         KSR2024.movingDirection = STAY;
//         break; 
//      }
//      //maju sampai aman untuk letakkan korban
//      //letakkin korban
//      case 26:{
//         KSR2024.letakanKorban();
//         break; 
//      }
//      case 27:{
//         KSR2024.rotate(KIRI, DEFAULT, 2, 11, KSR2024.tipeLangkah, KSR2024.speed, KSR2024.delayLangkah);
//         KSR2024.offsetDirection = -30;
//         KSR2024.movingType = ROTATING;
//         KSR2024.movingDirection = STAY;
//         break;
//      }
//      //maju sampai dekat sebelum ke jalan retak 2
//      case 28:{
//         KSR2024.kondisiTargetJarakMax[FRONT] = 120; 
//         KSR2024.movingType = MOVING;
//         KSR2024.movingDirection = MAJU;
//         KSR2024.error = 8;
//         KSR2024.derajatLangkahSetPos = 8;  
//         break;
//      }
//      //belok ke kiri
//      case 29:{
//         KSR2024.offsetDirection = 10;
//         KSR2024.changeDirToKiri();
//         KSR2024.movingType = ROTATING;
//         KSR2024.movingDirection = STAY;
//         KSR2024.speed = 300;
//         KSR2024.delayLangkah = 80;
//         KSR2024.error = 5;
//         KSR2024.derajatLangkahSetPos = 5; 
//         break;
//      }
//      case 30:{
//         KSR2024.kondisiTargetJarakMin[BACK] = 450; 
//         KSR2024.movingType = MOVING;
//         KSR2024.movingDirection = MAJU;
//         break;
//      }
//      //miringkan dikit
//      case 31:{
//         KSR2024.offsetDirection = -45;
//         KSR2024.movingType = ROTATING;
//         KSR2024.movingDirection = STAY;
//         break;
//      }
//      //maju teruss sampai jalan retak
//      case 32:{
//         KSR2024.tipeLangkah = TINGGI;
//         KSR2024.derajatLangkah = 18;
//         KSR2024.kondisiTargetJarakMax[LEFT] = 130;
//         KSR2024.movingType = MOVING;
//         KSR2024.movingDirection = MAJU;
//         KSR2024.speed = 300;
//         KSR2024.delayLangkah = 120;
//         KSR2024.error = 8;
//         KSR2024.derajatLangkahSetPos = 8;
//         break;
//      }
//      //luruskan kalau mentok
//      //maju ke depan sampai mentok
//      case 33:{
//         KSR2024.offsetDirection = 20;
//         KSR2024.kondisiTargetJarakMin[RIGHT] = 500;
//         KSR2024.movingType = MOVING;
//         KSR2024.movingDirection = MAJU;
//         break;
//      }
//      //Mode Manual
//      case MANUALMODE:{
//         KSR2024.initManualMode();
//         manualMod();
//         break;
//      }
  }
//   //Print kondisi robot, dikomen jika sudah tidak perlu debuging
  //  KSR2024.printCurrentYPR();
  //  KSR2024.printJarak();
  //  KSR2024.printState();
  if(KSR2024.movingType != STAY){
    cekKondisi(); //mengecek kondisi sudah terpenuh atau tidak
    KSR2024.move(); //jika blm, jalankan
  }
  KSR2024.setPos(); //rapikan 

//   //keamanan
// //  keamanan();
// //  //Manual Mode di comment aja jika tidak dipakai
// //   if(Serial.available() > 0){
// //     KSR2024.state = MANUALMODE;
// //     Serial.println("Manual mode actived...");
// //     String dump = Serial.readString(); //buang inputan pertama user
// //     manualMod();
// //   }
// }

// void keamanan(){
//   if(KSR2024.movingType == MOVING && KSR2024.movingDirection == MAJU && KSR2024.jarakDepan() <= 20){
//     KSR2024.berdiri();
//     KSR2024.state = 404;
//   }
//   if(KSR2024.movingType == MOVING && KSR2024.movingDirection == MUNDUR && KSR2024.jarakBelakang() <= 20){
//     KSR2024.berdiri();
//     KSR2024.state = 404;
//   }
}

void cekKondisi(){
  if(KSR2024.kondisiTargetJarakMin[FRONT] != 0 && KSR2024.jarakDepan() >= KSR2024.kondisiTargetJarakMin[FRONT]){
      KSR2024.berdiri();
      KSR2024.state++;
    }
    if(KSR2024.kondisiTargetJarakMin[BACK] != 0 && KSR2024.jarakBelakang() >= KSR2024.kondisiTargetJarakMin[BACK]){
      KSR2024.berdiri();
      KSR2024.state++;
    }
    if(KSR2024.kondisiTargetJarakMin[LEFT] != 0 && KSR2024.jarakKiri() >= KSR2024.kondisiTargetJarakMin[LEFT]){
      KSR2024.berdiri();
      KSR2024.state++;
    }
    if(KSR2024.kondisiTargetJarakMin[RIGHT] != 0 && KSR2024.jarakKanan() >= KSR2024.kondisiTargetJarakMin[RIGHT]){
      KSR2024.berdiri();
      KSR2024.state++;
    }
    if(KSR2024.kondisiTargetJarakMax[FRONT] != 0 && KSR2024.jarakDepan() <= KSR2024.kondisiTargetJarakMax[FRONT]){
      KSR2024.berdiri();
      KSR2024.state++;
    }
    if(KSR2024.kondisiTargetJarakMax[BACK] != 0 && KSR2024.jarakBelakang() <= KSR2024.kondisiTargetJarakMax[BACK]){
      KSR2024.berdiri();
      KSR2024.state++;
    }
    if(KSR2024.kondisiTargetJarakMax[LEFT] != 0 && KSR2024.jarakKiri() <= KSR2024.kondisiTargetJarakMax[LEFT]){
      KSR2024.berdiri();
      KSR2024.state++;
    }
    if(KSR2024.kondisiTargetRollMin != 0 && KSR2024.getRoll() >= KSR2024.kondisiTargetRollMin){
      KSR2024.berdiri();
      KSR2024.state++;
    }
    if(KSR2024.kondisiTargetRollMax != 0 && KSR2024.getRoll() <= KSR2024.kondisiTargetRollMax){
      KSR2024.berdiri();
      KSR2024.state++;
    }
}

// //Mode Manual robot
// void manualMod(){
//   Serial.println("Fetching current robot state...");
//   KSR2024.printCurrentYPR();
//   KSR2024.printJarak();
//   KSR2024.printState();
//   do{
      
//       if(Serial.available() > 0){
//         int step = 1;
//         String input = Serial.readString();
//         if(input.startsWith("END")){
//           KSR2024.state = 0;
//           printData();
//           return;
//         }
//         if(input.startsWith("MAJU")){
//           step = getValue(input, '-',1).toInt();
//           for(int i = 0; i < step; i++){
//             KSR2024.maju();
//             KSR2024.setPos();
//           }
//           printData();
//           continue;
//         }
//         if(input.startsWith("MUNDUR")){
//           step = getValue(input, '-',1).toInt();
//           for(int i = 0; i < step; i++){
//             KSR2024.mundur();
//             KSR2024.setPos();
//           }
//           printData();
//           continue;
//         }
//         if(input.startsWith("KIRI")){
//           KSR2024.kiri();
//           KSR2024.setPos();
//           printData();
//           continue;
//         }
//         if(input.startsWith("KANAN")){
//           KSR2024.kanan();
//           KSR2024.setPos();
//           printData();
//           continue;
//         }
//         if(input.startsWith("GET")){
//           KSR2024.getKorban();
//           printData();
//           continue;
//         }
//         if(input.startsWith("PUT")){
//           KSR2024.letakanKorban();
//           printData();
//           continue;
//         }

//         //konversi parameter
//         /*  FORMAT set parameter
//          *  tipeLangkah-derajatLangkah-height-offsetDirection-direction-speed-error
//          *  tipeLangkah: 0-5 (6 abaikan)
//          *  derajatLangkah: 1-18 (0 abaikan)
//          *  height: 0 <= (0 DEFAULT) //Sebaiknya tidak diubah
//          *  offsetDirection: 0 <= (0 DEFAULT)
//          *  direction: 0-3 (4 abaikan)
//          *  speed: 0 <= (0 DEFAULT)
//          *  error: 1 <= (0 abaikan)
//          */
//         int tipeLangkah = getValue(input, '-',0).toInt();
//         int derajatLangkah = getValue(input, '-',1).toInt();
//         int height = getValue(input, '-',2).toInt();
//         int offsetDirection = getValue(input, '-',3).toInt();;
//         int direction = getValue(input, '-',4).toInt();
//         int speed = getValue(input, '-',5).toInt();
//         int error = getValue(input, '-',6).toInt();
        
//         if(tipeLangkah <= 5){
//           KSR2024.tipeLangkah = tipeLangkah;
//           KSR2024.berdiri();
//           printData();
//         }
//         if(derajatLangkah > 0 && derajatLangkah <= 18){
//           KSR2024.derajatLangkah = derajatLangkah;
//           printData();
//         }
//         if(height >= 0){
//           KSR2024.height = height;
//           printData();
//         }
//         if(offsetDirection >= 0){
//           KSR2024.offsetDirection = offsetDirection;
//           printData();
//         }
//         if(direction >= 0 && direction <= 3){
//           KSR2024.direction = direction;
//           printData();
//         }
//         if(speed >= 0){
//           KSR2024.speed = speed;
//           printData();
//         }
//         if(error > 0){
//           KSR2024.error = error;
//           printData();
//         }
//         KSR2024.setPos();
//       }
//     }while(1);
// }

// void printData(){
//   //update Buffer
//   KSR2024.readUltrasonic();
//   KSR2024.printCurrentYPR();
//   KSR2024.printJarak();
//   KSR2024.printState();
// }

// String getValue(String data, char separator, int index)
// {
//   int found = 0;
//   int strIndex[] = {0, -1};
//   int maxIndex = data.length()-1;

//   for(int i=0; i<=maxIndex && found<=index; i++){
//     if(data.charAt(i)==separator || i==maxIndex){
//         found++;
//         strIndex[0] = strIndex[1]+1;
//         strIndex[1] = (i == maxIndex) ? i+1 : i;
//     }
//   }

//   return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
// }

// //Panggil di setup untuk mengetes langkah
// void testJalanStandPoint(int tipeLangkah){
//   KSR2024.init();
//   delay(2000);
//   KSR2024.berdiri(tipeLangkah); //Untuk test jalan
//   delay(500);
//   for(int i = 0; i < 10; i++){
//     KSR2024.move(MAJU, DEFAULT, 15, tipeLangkah, 300, 40);
//   }
//   delay(500);
//   KSR2024.berdiri(tipeLangkah);
// }

// //Panggil di setup jika ingin mencari standPoint baru
// void debugNewStandPoint(){
//     //Untuk testing stand point
//     //cariStandpoint(); //untuk mencari value standPoint baru
//     vec3_t tinggiDebug = {12,0,-6}; //tinggi maks langkah dari standPointDebug
//     vec3_t standPointDebug = {0, -28, 18}; //standPoint baru ingin ditext
//     vec3_t masuk = {-2,2,-4};
//     vec3_t naik = {0,-20,-10};
//     vec3_t geser = {-30,-10,-30};
// //    KSR2024.init();
// //    KSR2024.kaki.berdiriSamping(NORMAL);
//     //untuk test di satu kaki (gunakan untuk mencari value tinggiDebug
//     vec3_t naikDebug = tinggiDebug + standPointDebug + masuk;
//     Kaki(1,2,3, KIRI, GRUP2, DEPAN).moveToPointSecond(naikDebug);
    
//     //test jalan
// //    KSR2024.berdiriDebug(standPointDebug); //test berdiri
// //    for(int i = 0; i < 10; i++){
// //      KSR2024.moveDebug(MAJU, tinggiDebug, 10, standPointDebug, 500);
// //    }
// //    KSR2024.berdiriDebug(standPointDebug);
// }

// // ini dibawah sebelumnya untuk nyari standpoint yg pas :v
// void cariStandpoint(){
//   Serial.println("Mulai");
//   for(int i = -200 ; i < 200 ; i++){
//       for(int j = -200 ; j < 200 ; j++){
//         for(int k = -200; k < 200; k++){
//           vec3_t miring = {22,0,-10}; //tinggi maks langkah dari standPointDebug
//           vec3_t standPointDebug = {0, -42, 37}; //standPoint baru ingin ditext
//           vec3_t standPointTinggi = {i, j, k};
//           vec3_t result = miring + standPointDebug + standPointTinggi;
//           vec3_t deggs = InversKinematik(result);
//           /*
//            * Gunakan relasi y dan z berupa y = 90 - z untuk mencari standPoint
//            * Contoh: y = 30 & z = 60
//           */
//           if((deggs.y > -1 && deggs.y < 1) && (deggs.x > 39 && deggs.x < 41) && (deggs.z < -50 && deggs.z > -70) ){
//             Serial.print("TEST "); Serial.println(i); Serial.print(" i: "); Serial.print(i); Serial.print(" j: "); Serial.print(j); Serial.print(" k: "); Serial.print(k);Serial.println();          
//             Serial.println();
//             Serial.print(deggs.x);
//             Serial.print(" , ");
//             Serial.print(deggs.y);
//             Serial.print(" , ");
//             Serial.println(deggs.z);
//           }
//         }
//       }
//   }
//   Serial.println("Selesai");
// }
