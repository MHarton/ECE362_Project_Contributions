/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f0xx_hal.h"

/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "jsonParser.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
//init


//New
unsigned char status[] = "AT\r\n";
unsigned char echoff[] = "ATE0\r\n";
unsigned char choosemod[]= "AT+CWMODE=1\r\n";
unsigned char connect[] = "AT+CWJAP=\"lynksys\",\"\"\r\n";
unsigned char rset[]  = "AT+RST\r\n";
unsigned char start_sock_test[] ="AT+CIPSTART=\"TCP\",\"httpbin.org\",80\r\n";
unsigned char start_sock_weather[] ="AT+CIPSTART=\"TCP\",\"api.openweathermap.org\",80\r\n";

unsigned char send_msg[] = "GET /ip HTTP/1.1\r\nHost: httpbin.org\r\n\r\n\r\n";
unsigned char set_msg_size[80];
unsigned char close_socket[] = "AT+CIPCLOSE\r\n";

//Further initialiation
unsigned char datamode[] = "AT+CIPMODE=0\r\n";
unsigned char enable_multcha[] = "AT+CIPMUX=0\r\n";//Enable multiple channel connections


//General
unsigned char weather_pull_test[] = "GET api.openweathermap.org/data/2.5/weather?q=London,uk&APPID=975daa4a57ff020908bd5a9a4e15c846\r\nHost: api.openweathermap.org\r\n\r\n\r\n";
unsigned char weather_pull_test_2[] = "GET /data/2.5/weather?q=West Lafayette,us&units=imperial&APPID=975daa4a57ff020908bd5a9a4e15c846 HTTP/1.1\r\nHost: api.openweathermap.org\r\n\r\n\r\n";

unsigned char weather_pull[] = "api.openweathermap.org/data/2.5/find?q=\"West Lafayette\"&units=imperial";
unsigned char list_wifi[] = "AT+CWLAP\r\n";

//Tests
char *raw_weather;

//Utility
char pdata[20];
uint8_t tdata;
int pos;
char buffer[500];
//flags
int buff_flag;

//
wdata *curr_weather;
jtable *jTabby;
char *jstr;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
int initialize_WIFI();
int grab_Weather();
int test_Weather_UART();
int free_everything();
int close_and_check();
/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

int main(void)

{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();

  /* USER CODE BEGIN 2 */


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

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	  printf('lol');

  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USART1 init function */
static void MX_USART1_UART_Init(void)
{

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, LD4_Pin|LD3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LD4_Pin LD3_Pin */
  GPIO_InitStruct.Pin = LD4_Pin|LD3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

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
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char * file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler_Debug */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
