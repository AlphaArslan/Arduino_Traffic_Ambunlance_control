
/********************************** Debug Keys ***********************************/
#define       ENABLE_US                            // UnComment this line to Enable Ultrasonic
#define       ENABLE_RF                            // UnComment this line to Enable RF communication

/************************************ Include ************************************/
#ifdef ENABLE_RF
#include <RH_ASK.h>
#endif

#ifdef RH_HAVE_HARDWARE_SPI
#include <SPI.h> 
#endif

/********************************* control Panel *********************************/
#define       street_width          10              //in CM 
#define       sidewalk_width        3               //in CM
#define       delay_time            1000            //in ms
#define       rounds                19              //time =  delay_time * rounds
#define       rounds_min            0
#define       blink_time            250

/*********************************** Pin Config **********************************/

#define       RF_data_PIN           11      //by default 

// led connections 
#define       side1_green           2
#define       side1_yellow          3
#define       side1_red             4

#define       side2_green           5
#define       side2_yellow          6
#define       side2_red             7

#define       side3_green           8
#define       side3_yellow          9
#define       side3_red             10

#define       side4_green           14
#define       side4_yellow          15
#define       side4_red             16

//Ultrasonic connection 
#define       TrigBase              22 
#define       EchoBase              23 
#define       LedBase               17
/************************* Trig ****************** Echo ************* LED ************* 
 * Ultrasonic1              22                      23                17
 * Ultrasonic2              24                      25                18
 * Ultrasonic3              26                      27                19
 * Ultrasonic4              28                      29                20
 */



/*********************************** global var **********************************/
#ifdef ENABLE_RF
RH_ASK        driver;
//driver(2000, RX, Tx)
#endif

uint16_t      global_cntr = 0;


/************************************* setup *************************************/
void setup(){
    #ifdef ENABLE_RF
    #ifdef RH_HAVE_SERIAL
        Serial.begin(9600);    // Debugging only
    #endif
        if (!driver.init())
    #ifdef RH_HAVE_SERIAL
             Serial.println("init failed");
    #else
      ;
    #endif
    #endif

    pinMode( side1_green,  OUTPUT);
    pinMode( side1_yellow, OUTPUT);
    pinMode( side1_red,    OUTPUT);
    pinMode( side2_green,  OUTPUT);
    pinMode( side2_yellow, OUTPUT);
    pinMode( side2_red,    OUTPUT);
    pinMode( side3_green,  OUTPUT);
    pinMode( side3_yellow, OUTPUT);
    pinMode( side3_red,    OUTPUT);
    pinMode( side4_green,  OUTPUT);
    pinMode( side4_yellow, OUTPUT);
    pinMode( side4_red,    OUTPUT);

    digitalWrite( side1_green,  0);
    digitalWrite( side1_yellow, 0);
    digitalWrite( side1_red,    0);
    digitalWrite( side2_green,  0);
    digitalWrite( side2_yellow, 0);
    digitalWrite( side2_red,    0);
    digitalWrite( side3_green,  0);
    digitalWrite( side3_yellow, 0);
    digitalWrite( side3_red,    0);
    digitalWrite( side4_green,  0);
    digitalWrite( side4_yellow, 0);
    digitalWrite( side4_red,    0);


    #ifdef ENABLE_US
    pinMode(TrigBase + 0,  OUTPUT);
    pinMode(TrigBase + 2,  OUTPUT);
    pinMode(TrigBase + 4,  OUTPUT);
    pinMode(TrigBase + 6,  OUTPUT);
    pinMode(EchoBase + 0,  INPUT);
    pinMode(EchoBase + 2,  INPUT);
    pinMode(EchoBase + 4,  INPUT);
    pinMode(EchoBase + 6,  INPUT);
    pinMode(LedBase  + 0,  OUTPUT);
    pinMode(LedBase  + 1,  OUTPUT);
    pinMode(LedBase  + 2,  OUTPUT);
    pinMode(LedBase  + 3,  OUTPUT);
    #endif
}

/************************************* loop **************************************/
void open_side1();
void open_side2();
void open_side3();
void open_side4();
void reset_lights();
bool is_side_busy(char side);
bool is_all_empty();
void check_Ambulance();

#ifdef ENABLE_US
float USgetDistance(char side);
#endif

/*********************************************************************************/

/************************************* loop **************************************/
void loop(){
  open_side1();

  open_side2();
  
  open_side3();
  
  open_side4();
}

/*********************************** real deal **********************************/
void open_side1(){
    reset_lights();
    digitalWrite(side1_green , HIGH);
    digitalWrite(side2_yellow , HIGH);
    digitalWrite(side3_red , HIGH);
    digitalWrite(side4_red , HIGH);

      
    delay_function(1);
}

void open_side2(){
    reset_lights();
    digitalWrite(side2_green , HIGH);
    digitalWrite(side3_yellow , HIGH);
    digitalWrite(side4_red , HIGH);
    digitalWrite(side1_red , HIGH);

      
    delay_function(2);
}

void open_side3(){
    reset_lights();
    digitalWrite(side3_green , HIGH);
    digitalWrite(side4_yellow , HIGH);
    digitalWrite(side1_red , HIGH);
    digitalWrite(side2_red , HIGH);

      
    delay_function(3);
}

void open_side4(){
    reset_lights();
    digitalWrite(side4_green , HIGH);
    digitalWrite(side1_yellow , HIGH);
    digitalWrite(side2_red , HIGH);
    digitalWrite(side3_red , HIGH);

    
    delay_function(4);
}

void delay_function(char side){
    delay(rounds_min * delay_time);
    if(is_side_busy(side)){
        for(int i=0; i<rounds; i++){
            delay(delay_time);
            check_Ambulance();
            if(!is_side_busy(side)){
                break;
            }
        }
    }else if(is_all_empty()){
        for(int i=0; i<rounds; i++){
            delay(delay_time);
            check_Ambulance();
            if(!is_all_empty()){
                break;
            }
        }
    }
}

bool is_side_busy(char side){
    
    #ifdef ENABLE_US
    if( USgetDistance(side) < street_width-sidewalk_width){
      digitalWrite(LedBase + side -1, HIGH);
      delay(blink_time);
      digitalWrite(LedBase + side -1, LOW);
      return true ;
    }
    #endif
    
    return false ;
}


#ifdef ENABLE_US
float USgetDistance(char side){
    digitalWrite(TrigBase + (side-1)*2, LOW);
    delayMicroseconds(2);
    digitalWrite(TrigBase + (side-1)*2, HIGH);
    delayMicroseconds(10);
    digitalWrite(TrigBase + (side-1)*2, LOW);
    return (pulseIn(EchoBase + (side-1)*2, HIGH)*0.034/2);
    //It returns CM
}
#endif


void reset_lights(){
    digitalWrite( side1_red ,LOW);
    digitalWrite( side1_yellow ,LOW);
    digitalWrite( side1_green ,LOW);
    
    digitalWrite( side2_red ,LOW);
    digitalWrite( side2_yellow ,LOW);
    digitalWrite( side2_green ,LOW);
    
    digitalWrite( side3_red ,LOW);
    digitalWrite( side3_yellow ,LOW);
    digitalWrite( side3_green ,LOW);
    
    digitalWrite( side4_red ,LOW);
    digitalWrite( side4_yellow ,LOW);
    digitalWrite( side4_green ,LOW);
    
}

bool is_all_empty(){
    if(    !is_side_busy(1) 
       &&  !is_side_busy(2)  
       &&  !is_side_busy(3)  
       &&  !is_side_busy(4)  ){

            return true;
       }
     return false;
}

void check_Ambulance(){
    #ifdef ENABLE_RF
    uint8_t buf[1] ;
    uint8_t buflen = sizeof(buf);
    if(driver.recv(buf, &buflen)){
      switch(buf[0]){
          case 1:     open_side1();     break;
          case 2:     open_side2();     break;
          case 3:     open_side3();     break;
          case 4:     open_side4();     break;
      }
    }
    #endif
}
