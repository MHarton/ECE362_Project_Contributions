#ifndef WEATHER
#define WEATHER
#include "stm32f0xx_hal.h"
#include "stdlib.h"





//Initialization
extern const char status[] = "AT\r\n";
extern const char echoff[] = "ATE0\r\n";
extern const char choosemod[]= "AT+CWMODE=1\r\n";
extern const char connect[] = "AT+CWJAP=\"NetworkName\",\"password\"\r\n";

//Further initialiation
extern const char enable_multcha[] = "AT+CIPMUX=1\r\n";//Enable multiple channel connections 
extern const char datamode[] = "AT+CIPMODE=1\r\n";


//General
extern const char weather_pull[] = "api.openweathermap.org/data/2.5/find?q=\"West Lafayette\"&units=imperial"



void HAL_UART_RxCpltCallback (UART_HandleTypeDef * huart);
int initialize_WIFI();



#endif
