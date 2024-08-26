#include "header.h"
#include "Robot.h"

Robot KSR2024;
void cekKondisi();
void setup(){
    // digitalRead()
    Wire.begin();
    Serial3.begin(9600);
    pinMode(10, INPUT);
    // Serial.begin(9600);
    // Serial.println("test");
    // KSR2024.init();
    // delay(1000);
    //Untuk mulai dari state tertentu
   
//     KSR2024.state = 18;
  DEBUG_SERIAL.begin(115200);
  dxl.begin(57600);
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);
  KSR2024.init();
}

void loop(){
  switch(KSR2024.state){
    //init
    case -1 : {
      while(!digitalRead(10)){

      }
      if(digitalRead(10)){
        KSR2024.state++;
      }
    }
    case 0:{
        // KSR2024.initManualMode();
        // KSR2024.delayLangkah = 100;
        // KSR2024.tipeLangkah = SEDANG_20;
        // KSR2024.changeDirToKiri();
        // KSR2024.changeDirToKiri();
        // KSR2024.state=22;
        KSR2024.checkPosition();
        break;
    }
    //menuju korban
    case 1:{
        KSR2024.kondisiTargetJarakMin[BACK] = 560;
        KSR2024.movingType = MOVING;
        KSR2024.movingDirection = MAJU;
        break; 
    }
    //hadap korban
    case 2:{
        KSR2024.movingType = ROTATING;
        KSR2024.movingDirection = KIRI;
        KSR2024.offsetDirection = 0;
        break; 
    }
    //mundur utk meluruskan
    case 3:{
        KSR2024.kondisiTargetJarakMax[BACK] = 100;
        KSR2024.movingType = MOVING;
        KSR2024.movingDirection = MUNDUR;
        KSR2024.derajatLangkah = 10;
        break; 
    }
    //ambil korban pertama
    case 4:{
        KSR2024.derajatLangkah = 10;
        KSR2024.getKorban();
        break; 
    }
    //mundur menyesuaikan dengan jalan retak
    case 5:{
        KSR2024.kondisiTargetJarakMax[BACK] = 130;
        KSR2024.movingType = MOVING;
        KSR2024.movingDirection = MUNDUR;
        KSR2024.derajatLangkah = 10;
        break; 
    }
    //hadap depan
    case 6:{
        KSR2024.movingType = ROTATING;
        KSR2024.movingDirection = KANAN;
        KSR2024.derajatLangkah = 20;
        break; 
    }
    //maju sampai mentok
    case 7:{
        KSR2024.kondisiTargetJarakMin[BACK] = 590;
        KSR2024.movingType = MOVING;
        KSR2024.movingDirection = MAJU;
        break; 
    }
    //maju jalan retak
    case 8:{
        KSR2024.offsetDirection = 15;
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
    //masuk jalan miring
    case 9:{
        KSR2024.offsetDirection = 10;
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
    //masuk jalan batu
    case 10:{
        KSR2024.offsetDirection = 0;
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
    //belok kanan hadap safezone
    case 11:{
        // KSR2024.movingType = ROTATING;
        KSR2024.changeDirToKanan();
        KSR2024.offsetDirection = -50;
        KSR2024.state++;
        break;
    }
    //letakkan korban pertama
    case 12:{    
        KSR2024.letakanKorban();
        KSR2024.offsetDirection = 0;
        KSR2024.error = 5;
        KSR2024.derajatLangkahSetPos = 5;
        break; 
    }
    //miring kanan jika kurang kiri atau mundur aja
    case 13: {
        KSR2024.error = 10;
        KSR2024.derajatLangkahSetPos = 10;
        KSR2024.derajatLangkah = 15;
        if(KSR2024.jarakKiri() >= 190){
          KSR2024.movingType = MOVING;
          KSR2024.movingDirection = Kari;
        }
        else{
          KSR2024.state++;
        }
        break;
    }
    //Jalan Mundur Masuk Ke Guli
    case 14:{
        KSR2024.tipeLangkah = SEDANG_20;
        KSR2024.derajatLangkah = 20;
        KSR2024.kondisiTargetJarakMin[FRONT] = 525;
        KSR2024.movingType = MOVING;
        KSR2024.movingDirection = MUNDUR;
        break;
    }
    //Putar Kanan Ngadep Korban
    case 15:{
        KSR2024.movingType = ROTATING;
        KSR2024.movingDirection = KANAN; 
        break;
    }
    //Mundur Dikit Deteksi Korban
    case 16:{
      // KSR2024.kondisiTargetJarakMin[BACK] = 155;
      // KSR2024.movingType = MOVING;
      // KSR2024.movingDirection = MUNDUR;
      KSR2024.state=22;
      break;
    }
    //Ambil Korban
    case 17:{
        // KSR2024.tipeLangkah = SEDANG_20;
        // KSR2024.getKorban2();
        KSR2024.state++;
        break;
    }
    //Mundur Menjauh Dari Korban
    case 18:{
        // KSR2024.tipeLangkah = SEDANG_20;
        // KSR2024.kondisiTargetJarakMin[BACK] = 155;
        // KSR2024.movingType = MOVING;
        // KSR2024.movingDirection = MUNDUR;
        KSR2024.state++;
        break;
    }
    //Ngadep Ke Safezone Korban
    case 19:{
        KSR2024.movingType = ROTATING;
        KSR2024.movingDirection = KANAN;
        break;
    }
    //Maju Ke Safezone
    case 20:{
        // KSR2024.kondisiTargetJarakMin[BACK] = 500;
        // KSR2024.movingType = MOVING;
        // KSR2024.movingDirection = MAJU;
        KSR2024.state=22;
        break;
    }
    //Letakan Korban
    case 21:{
        //letak
        KSR2024.state++;
        break;
    }
    //Ngadep Keluar Dari Kelereng
    case 22:{
        // KSR2024.changeDirToKiri();
        KSR2024.offsetDirection = 55;
        KSR2024.state++;
        break;
    }
    //Maju Keluar Kelereng
    case 23:{
        KSR2024.kondisiTargetJarakMin[BACK] = 700;// from 625 to 700
        KSR2024.movingType = MOVING;
        KSR2024.movingDirection = MAJU;
        break;
    }
    //Lurusin Lagi
    case 24:{
        KSR2024.error = 5;
        KSR2024.derajatLangkahSetPos = 5;
        KSR2024.offsetDirection = 15;
        KSR2024.state++;
        break;
    }
    //Maju Sampe Mentok
    case 25:{
        KSR2024.error = 10; //from 14 to 10
        KSR2024.derajatLangkahSetPos = 10; //from 14 to 10
        KSR2024.kondisiTargetJarakMin[BACK] = 680;
        KSR2024.movingType = MOVING;
        KSR2024.movingDirection = MAJU;
        break;
    }
    //Jalan Nyamping Sampe Mentok
    // case 26:{
    //     KSR2024.offsetDirection = -30;
    //     KSR2024.kondisiTargetJarakMin[BACK] = 650;
    //     KSR2024.error = 12;
    //     KSR2024.derajatLangkahSetPos = 12;
    //     KSR2024.movingType = MOVING;
    //     KSR2024.movingDirection = MAJU;
    //     break;
    // }
    case 26:{
        KSR2024.delayLangkah = 50;
        KSR2024.derajatLangkah = 10;
        KSR2024.tipeLangkah = NORMAL;
        KSR2024.kondisiTargetJarakMax[LEFT] = 225; 
        KSR2024.movingType = MOVING;
        KSR2024.movingDirection = Kari;
        break;
    }
    //Masuk Retak 2
    case 27:{
        KSR2024.tipeLangkah = SEDANG_20;
        KSR2024.offsetDirection = 18; // from 18 to 15
        // KSR2024.kondisiTargetJarakMin[BACK] = 1000;
        KSR2024.derajatLangkah = 20;
        KSR2024.delayLangkah = 100;
        KSR2024.movingType = MOVING;
        KSR2024.movingDirection = MAJU;
        if(KSR2024.jarakDepan() > 200 && KSR2024.jarakDepan() < 500){
          KSR2024.state++;
        }
        break;
    }
    //Masih Di dalam Retak 2
    case 28:{
        // KSR2024.kondisiTargetJarakMax[FRONT] = 225;
        KSR2024.offsetDirection = 38; // from 35 to 38
        KSR2024.movingType = MOVING;
        KSR2024.movingDirection = MAJU;
        break;
    }
    //Ngarah Nyamping
    case 29:{
        // KSR2024.tipeLangkah = SEDANG_15;
        KSR2024.offsetDirection = 45;
        KSR2024.state++;
        break;
    }
    //Maju Sampe Selesai
    case 30:{
        KSR2024.kondisiTargetJarakMin[BACK] = 650;
        KSR2024.movingType = MOVING;
        KSR2024.movingDirection = MAJU;
        break;
    }
    //Meluruskan Kembali
    case 31:{
        KSR2024.offsetDirection = 0;
        KSR2024.state++;
        break;
    }
    //Maju Sampe Keluar 
    case 32:{
        KSR2024.kondisiTargetJarakMin[BACK] = 600;
        KSR2024.movingType = MOVING;
        KSR2024.movingDirection = MAJU;
        break;
    }
     //Mode Manual
    //  case MANUALMODE:{
    //     KSR2024.initManualMode();
    //     manualMod();
    //     break;
    //  }
  }
  //Print kondisi robot, dikomen jika sudah tidak perlu debuging
  //  KSR2024.printCurrentYPR();
  //  KSR2024.printJarak();
  //  KSR2024.printState();
  if(KSR2024.movingType != STAY){
    cekKondisi(); //mengecek kondisi sudah terpenuh atau tidak
    KSR2024.move(); //jika blm, jalankan
  }
  KSR2024.setPos(); //rapikan 

//keamanan
//  keamanan();
//  //Manual Mode di comment aja jika tidak dipakai
//   if(Serial.available() > 0){
//     KSR2024.state = MANUALMODE;
//     Serial.println("Manual mode actived...");
//     String dump = Serial.readString(); //buang inputan pertama user
//     manualMod();
//   }
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
