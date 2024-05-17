class Kaki{
  private:
    int coxaID; // ID COXA
    int fermurID; // ID FERMUR
    int thibiaID; // ID THIBIA
    int pos; // KIRI / KANAN
    int grup; // GRUP 1 / 2
    int letak; // DEPAN / TENGAH / BELAKANG

  public:    
    Kaki(){}
    
    Kaki(int coxaID,int fermurID, int thibiaID, int pos, int grup, int letak){
      // Constructor kaki untuk memasukan ID dari servo sesuai bagian kaki, posisi, group dan letak kaki
      this->coxaID = coxaID;
      this->fermurID = fermurID;
      this->thibiaID = thibiaID; 
      this->pos = pos;
      this->grup = grup;
      this->letak = letak;
    }

    void langkah(vec3_t pointMaju, vec3_t pointMundur, int speed){
        if(this->grup == GRUP1){
          pointMaju.z*=this->pos;
          moveToPoint(pointMaju, speed);
        }
        else{
          pointMundur.z*=this->pos;
          moveToPoint(pointMundur, speed);
        }
        delayMicroseconds(10);
    }

    void samping(vec3_t pointMaju, vec3_t pointMundur,vec3_t pointTMa, vec3_t pointTMu,int speed){
      // DEFAULT DERAJAT 10
        if(this->letak== BELAKANG){
          pointMaju.z*=-1;
          pointMundur.z*=-1;
        }

        
        if(this->grup == GRUP1){
          if(this->letak == TENGAH){
            pointTMa.z*=this->pos;
            moveToPoint(pointTMa, speed);
          }else{
            // pointMaju.z*=this->pos;
            moveToPoint(pointMaju, speed);
          }
        }
        else{
          if(this->letak == TENGAH){
            pointTMu.z*=this->pos;
            moveToPoint(pointTMu, speed);
          }else{
            
            // pointMundur.z*=this->pos;
            moveToPoint(pointMundur, speed);
          }
        }
        delayMicroseconds(10);
    }


    void langkahPutar(vec3_t pointMaju, vec3_t pointMundur, int speed){ 
        if(this->grup == GRUP1){
          // pointMaju.z*=this->pos;
          moveToPoint(pointMaju, speed);
        }
        else{
          // pointMundur.z*=this->pos;
          moveToPoint(pointMundur, speed);
        }
        delayMicroseconds(10);
    }



    void moveToPoint(vec3_t target, int speed = 300){
        vec3_t deggs = InversKinematik(target);
        // *this->pos

        dxl.setGoalPosition(coxaID,(deggs.x)+180,UNIT_DEGREE);
        dxl.setGoalPosition(fermurID,(deggs.y*-1)+180,UNIT_DEGREE);
        dxl.setGoalPosition(thibiaID,(deggs.z*this->pos)+180,UNIT_DEGREE);
    }
    
    void init(){
        dxl.torqueOff(coxaID);
        dxl.setOperatingMode(coxaID, OP_POSITION);
        dxl.torqueOn(coxaID);
        dxl.torqueOff(fermurID);
        dxl.setOperatingMode(fermurID, OP_POSITION);
        dxl.torqueOn(fermurID);
        dxl.torqueOff(thibiaID);
        dxl.setOperatingMode(thibiaID, OP_POSITION);
        dxl.torqueOn(thibiaID);
        delay(10);
        dxl.setGoalPosition(coxaID, 180, UNIT_DEGREE);
        dxl.setGoalPosition(fermurID, 180, UNIT_DEGREE);
        dxl.setGoalPosition(thibiaID, 180, UNIT_DEGREE);
    }
    
    void berdiri(vec3_t standPoint){
      // Mini function untuk berdiri
      moveToPoint(standPoint);
    }
};
