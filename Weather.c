#include "Weather.h"



void HAL_UART_RxCpltCallback (UART_HandleTypeDef * huart)
{
	if(!strcmp(pdata, "\r") || !strcmp(pdata, "\n"))
	{
		pos = 0;
		buff_flag = 1;
	}
	else
	{
		buffer[pos++] = pdata[0];
	}
	HAL_UART_Receive_IT(&huart1, pdata, 1);
}


int initialize_WIFI()
{
		HAL_UART_Transmit(&huart1, choosemod, strlen(choosemod), 1000);
	    HAL_UART_Receive_IT(&huart1, pdata, 1);
	  	if(strncmp(pdata, "OK", 2))
        {       
           return 0; 
        }
		HAL_UART_Transmit(&huart1, connect, strlen(connect), 1000);
	    HAL_UART_Receive_IT(&huart1, pdata, 1);
	  	if(strncmp(pdata, "OK", 2))
        {       
           return 0; 
        }
		HAL_UART_Transmit(&huart1, enable_multcha, strlen(enable_multcha), 1000);
	    HAL_UART_Receive_IT(&huart1, pdata, 1);
	  	if(strncmp(pdata, "OK", 2))
        {       
           return 0; 
        }
		HAL_UART_Transmit(&huart1, datamode, strlen(datamode), 1000);
	    HAL_UART_Receive_IT(&huart1, pdata, 1);
	  	if(strncmp(pdata, "OK", 2))
        {       
           return 0; 
        }
        return 1;
}
