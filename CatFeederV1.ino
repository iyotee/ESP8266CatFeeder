/*
 * 
 * CAT FEEDER V1 - 2020.06.21 
 * Written by Jérémy Noverraz
 * 
 * 
 * This code is able to control a servo motor  to open a cat feeder door
 */

/* ------ INCLUDE DEPENDENCIES LIBRARIES ------- */
#include <Servo.h>
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

/* ---- CONSTANTES ----*/
const char *ssid     = "SwissLabsBox2";
const char *password = "JP3YMhAdx4rbvyru3S";

/* ---- DECLARATION ET INITIALISATION DES VARIABLES ---- */
int pos = 0;

/* ---- DECLARATION ET INITIALISATION DES FONCTIONS ---- */ 
Servo CatFeeder_servo;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 3600, 60000);

void setup() {
  
  /* ---- INITIALISATION DE LA CONSOLE ---- */
  Serial.begin(115200);


  /*---- SERVO SETUP ----*/
  CatFeeder_servo.attach(2);
  CatFeeder_servo.write(pos);
  
  /*---- WIFI SETUP ----*/
  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );  
  }

  /* ------- NTP SETUP + OFFSET 2H --------- */
  timeClient.begin();
  timeClient.setTimeOffset(7200);
  
}

void loop() {

  /* -------------- NTP LOOP ------------ */

  
  while(!timeClient.update()) {
    timeClient.forceUpdate();
  }

  Serial.println(timeClient.getFormattedTime());
  timeClient = timeClient + 2;
  Serial.println(timeClient.getFormattedTime());


  /* ---------- SERVO LOOP ----------- */

  
  Serial.println("openend");
  CatFeeder_servo.write(180);
  delay(2000);
  Serial.println("closed");
  CatFeeder_servo.write(pos);
  delay(3000);
  
}
