#include <RH_ASK.h>
#ifdef RH_HAVE_HARDWARE_SPI
#include <SPI.h> // Not actually used but needed to compile
#endif

/************************** Pin Config *************************/
#define           side1_switch          3
#define           side2_switch          4
#define           side3_switch          5
#define           side4_switch          6
#define           RF_data_pin           12
/**************************************************************/

RH_ASK driver;

void setup()
{
    #ifdef RH_HAVE_SERIAL
        Serial.begin(9600);    // Debugging only
    #endif
        if (!driver.init())
    #ifdef RH_HAVE_SERIAL
             Serial.println("init failed");
    #else
      ;
    #endif
}

void loop()
{
    if(digitalRead(side1_switch) == HIGH){
          const char msg[1] = {1}; 
          driver.send((uint8_t *)msg, strlen(msg));
          driver.waitPacketSent();
          delay(1200);
    }
    if(digitalRead(side2_switch) == HIGH){
          const char msg[1] = {2}; 
          driver.send((uint8_t *)msg, strlen(msg));
          driver.waitPacketSent();
          delay(1200);
    }
    if(digitalRead(side3_switch) == HIGH){
          const char msg[1] = {3}; 
          driver.send((uint8_t *)msg, strlen(msg));
          driver.waitPacketSent();
          delay(1200);
    }
    if(digitalRead(side4_switch) == HIGH){
          const char msg[1] = {4}; 
          driver.send((uint8_t *)msg, strlen(msg));
          driver.waitPacketSent();
          delay(1200);
    }
    
}
