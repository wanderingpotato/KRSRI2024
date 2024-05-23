//Vector
#include <vector_type.h>

//Arduino
#include <Arduino.h>
#include <math.h> 
#include <ArduinoQueue.h>

// Invers Kinematik
#include "InversKinematik.h"

//Kamera
#include <Pixy2.h>

// Kompas dan Gyro
// #include <MPU6050.h>
#include <VL53L0X.h>
#include <Wire.h>
#include <I2Cdev.h>
#include "MPU6050_6Axis_MotionApps20.h"

// Servo Baru
// #include <Servo.h>

// Servo Lama
#include <SoftwareSerial.h>
#include <Dynamixel2Arduino.h>
#include <SoftwareSerial.h>
SoftwareSerial soft_serial(7, 8);
#define DXL_SERIAL   Serial
#define DEBUG_SERIAL soft_serial
const int DXL_DIR_PIN = 2;
const float DXL_PROTOCOL_VERSION = 2.0;
Dynamixel2Arduino dxl(DXL_SERIAL, DXL_DIR_PIN);
using namespace ControlTableItem;

// // #include "AX12A.h"

// #define DirectionPin   (10u)
// #define BaudRate      (1000000ul)
// #define ID (1u)

//Movement
#define MAJU 1
#define MUNDUR -1
#define Kasu 2
#define Kari 3

#define KANAN 1
#define KIRI -1

#define STAY 0 
#define MOVING 1
#define ROTATING 2

//Putar
#define KaP -1 //Kanan
#define KiP 1 //Kiri

//Arah robot
#define FRONT 0
#define LEFT 1
#define RIGHT 2
#define BACK 3

//PART ROBOT
#define GRUP1 1
#define GRUP2 -1

#define DEPAN 1
#define TENGAH 2
#define BELAKANG 3

//Keycolor kamera
#define ORANGE 1
#define PUTIH 2

//StandPoint Robot
#define nStandPoint 6

#define NORMAL 0
#define SEDANG_10 1
#define SEDANG_15 2
#define SEDANG_20 3
#define SEDANG_25 4
#define TINGGI 5

#define DEFAULT 0

#define DNormal 0
#define DKiri 1
#define DKanan 2

#define MANUALMODE 123

// Untuk Deragat Lengan
#define Atas 90
#define TNormal 15
#define TSedang_10 20
#define TSedang_15 30
#define TFull 5