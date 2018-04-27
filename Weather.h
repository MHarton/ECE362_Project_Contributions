#ifndef WEATHER
#define WEATHER
#include "stm32f0xx_hal.h"
#include "stdlib.h"
#include "jsonParser.h"
//Characters and so forth

extern unsigned char status[0];
extern unsigned char echoff[80]; 
extern unsigned char choosemod[80];
extern unsigned char connect[80];
extern unsigned char rset[8];  
extern unsigned char start_sock_test[80];
extern unsigned char start_sock_weather[80]; 

extern unsigned char send_msg[80];  
extern unsigned char set_msg_size[80];
extern unsigned char close_socket[80];= 

//Further initialiation
extern unsigned char datamode[80]; = 
extern unsigned char enable_multcha[80]; 


//General
extern unsigned char weather_pull_test[150]; 
extern unsigned char weather_pull_test_2[150];
extern unsigned char weather_pull[80]; 
extern unsigned char list_wifi[80]; 


extern char *raw_weather;

//Utility
extern char pdata[20];
extern uint8_t tdata;
extern int pos;
extern char buffer[500];
//flags
extern int buff_flag;

//
extern wdata *curr_weather;
extern jtable *jTabby;
extern char *jstr;


//Functions
int control_unit();
int initialize_WIFI();
int grab_Weather();
int test_Weather_UART();
int free_everything();
int free_weather();
int close_and_check();


#endif
