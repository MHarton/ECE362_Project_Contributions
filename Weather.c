#include "Weather.h"


int control_unit()
{

  pos = 0;
  //Weather and JSON setup
  curr_weather = (wdata *)malloc(sizeof(wdata));
  sprintf(set_msg_size, "AT+CIPSEND=%d\r\n", strlen(weather_pull_test_2));
  initialize_WIFI();
  grab_Weather();
  test_Weather_UART();
 // HAL_Delay(5000);
  close_and_check();
  free_everything();
  return 1;
}

int initialize_WIFI()
{
	  HAL_UART_Receive_IT(&huart1, pdata, 1);
	  HAL_UART_Transmit(&huart1, rset, strlen(rset), 800);
	  HAL_UART_Receive_IT(&huart1, pdata, 1);
	  HAL_Delay(500);
	  while(strncmp(buffer, "ready", 5))
	  {
	     buff_flag = 1;
	  }
	  HAL_UART_Transmit(&huart1, connect, strlen(connect), 800);
	  HAL_UART_Receive_IT(&huart1, pdata, 1);
	  HAL_Delay(500);
	  while(strncmp(buffer, "OK", 2))
	  {
	     buff_flag = 1;
	  }
	  return 1;
}
int grab_Weather()
{
	  HAL_UART_Transmit(&huart1, start_sock_weather, strlen(start_sock_weather), 800);
	  HAL_UART_Receive_IT(&huart1, pdata, 1);
	  HAL_Delay(500);
	  while(strncmp(buffer, "OK", 2))
	  {
	     buff_flag = 1;
	  }
	  HAL_UART_Transmit(&huart1, set_msg_size, strlen(set_msg_size), 800);
	  HAL_UART_Receive_IT(&huart1, pdata, 1);
	  HAL_Delay(500);
	  while(strncmp(buffer, ">", 1))
	  {
	     buff_flag = 1;
	  }
	  HAL_UART_Transmit(&huart1, weather_pull_test_2, strlen(weather_pull_test_2), 800);
	  HAL_UART_Receive_IT(&huart1, pdata, 1);
	  HAL_Delay(1000);
	  while(strncmp(buffer, "{\"coord\"", 7))
	  {
	     buff_flag = 1;
	  }
	  jstr = (char *)malloc(sizeof(char)*strlen(buffer));
	  strncpy(jstr, buffer, strlen(buffer));
	  jTabby = split_a_string(buffer);
	  jsonParse(*jTabby, curr_weather);
	  HAL_Delay(1000);

	  return 1;
}


int test_Weather_UART()
{
	  HAL_UART_Transmit(&huart1, curr_weather->weather, strlen(curr_weather->weather), 800);
	  HAL_UART_Receive_IT(&huart1, pdata, 1);
	  while(strncmp(buffer, "ERROR", 5))
	  {
	     buff_flag = 1;
	  }
	  HAL_UART_Transmit(&huart1, curr_weather->temp, strlen(curr_weather->temp), 800);
	  HAL_UART_Receive_IT(&huart1, pdata, 1);
	  while(strncmp(buffer, "ERROR", 5))
	  {
	     buff_flag = 1;
	  }
	  return 1;
}

int free_everything()
{
	  free_jTable(jTabby);
	  free(jstr);
	  return 1;
}

int free_weather()
{
	  clean_Weather(curr_weather);
	  free_Weather(curr_weather);
    return 1;
}

int close_and_check()
{
	  HAL_UART_Transmit(&huart1, close_socket, strlen(close_socket), 1000);
	  HAL_UART_Receive_IT(&huart1, pdata, 1);
	  HAL_Delay(100);
	  while(strncmp(buffer, "OK", 2)){}
	  HAL_UART_Transmit(&huart1, status, strlen(status), 800);
	  HAL_UART_Receive_IT(&huart1, pdata, 1);
	  HAL_Delay(500);
	  if(!strncmp(buffer, "OK", 2) || !strncmp(buffer, "AT", 2))
	  {
	     return 1;
	  }
	  return 0;

}

