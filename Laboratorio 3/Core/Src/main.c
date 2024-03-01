/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <math.h>
#include <stdbool.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/*uint16_t count = 0;*/
uint16_t counter =0;
bool status = false;
uint16_t button_counter;
int hours = 0;
int minutes = 0;
int seconds = 0;
float actual_minute;
//int a=10;
char est=0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
void mode_set();
void mode_run();
void real_time();
void time_boton();
void show_minutes(GPIO_TypeDef* port,uint16_t Pin);
void show_hours(int h);
void shut_down();


/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

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
  /* USER CODE BEGIN 2 */
 /* while(1){
	  HAL_Delay(a);
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET);
	  HAL_Delay(a);
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);


  }/*
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  HAL_Delay(1);
	  counter++;
	  real_time(); // actualiza las variables de tiempo (hours, minutes, seconds)
	  while(!(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5) == 0))
	  {
	      if (status == false) {
	          counter = 0;
	          status = true;
	      }
	      HAL_Delay(1);
	      counter++;
	      button_counter++;//tiempo seleccion boton
	      real_time();// actualiza las variables de tiempo (hours, minutes, seconds)
	  }

	  if ((button_counter >= 400) && (button_counter < 2000))
	  {

		  button_counter = 0;
		  mode_run();
		  button_counter = 0;

	  }

	  else if (button_counter > (2000))
	  {
		  button_counter = 0;
	      mode_set();
	      button_counter = 0;
	  }


	  button_counter = 0;
	  status = false;

  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5
                          |GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_9|GPIO_PIN_10
                          |GPIO_PIN_11|GPIO_PIN_12, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_15|GPIO_PIN_5, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA2 PA4 PA5 PA6
                           PA7 PA9 PA10 PA11
                           PA12 */
  GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6
                          |GPIO_PIN_7|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
                          |GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PA3 */
  GPIO_InitStruct.Pin = GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB15 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PB5 */
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void mode_run() {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
    HAL_Delay(1);
    counter++;//tiempo
    button_counter++;//cuanto llevo
    real_time(); // actualiza las variables de tiempo (hours, minutes, seconds)
    while( button_counter <= 400)
    {
    	HAL_Delay(1);
    	button_counter++;
    	counter++;
    	real_time(); // actualiza las variables de tiempo (hours, minutes, seconds)
    }
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);

    show_hours(hours);

    actual_minute = (float)minutes / 5;
    switch ((int)round(actual_minute)) {
        case 0:
            show_minutes(GPIOA, GPIO_PIN_2);
            break;
        case 1:
            show_minutes(GPIOA, GPIO_PIN_12);
            break;
        case 2:
            show_minutes(GPIOA, GPIO_PIN_11);
            break;
        case 3:
            show_minutes(GPIOA, GPIO_PIN_10);
            break;
        case 4:
            show_minutes(GPIOA, GPIO_PIN_9);
            break;
        case 5:
            show_minutes(GPIOB, GPIO_PIN_15);
            break;
        case 6:
            show_minutes(GPIOB, GPIO_PIN_0);
            break;
        case 7:
            show_minutes(GPIOA, GPIO_PIN_7);
            break;
        case 8:
            show_minutes(GPIOB, GPIO_PIN_1);
            break;
        case 9:
            show_minutes(GPIOA, GPIO_PIN_6);
            break;
        case 10:
            show_minutes(GPIOA, GPIO_PIN_5);
            break;
        case 11:
            show_minutes(GPIOA, GPIO_PIN_4);
            break;
        default:
            break;
    }

    shut_down();
}

void mode_set() {

	est=0;


 for (int i = 0; i < 4; i++)
 {
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, !(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3)));// Encender LED MINUTO
	button_counter = 0;
	while( button_counter <= 400)
	    {
	HAL_Delay(1);
	button_counter++;
	counter++;
	real_time(); // actualiza las variables de tiempo (hours, minutes, seconds)
	    }
 }


 while(est == 0)
 {
	 show_hours(hours);

	 // Encender LED MINUTO
	 button_counter = 0;


	 while(!(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5) == 0))
	 	  {
	 	      if (status == false) {
	 	          counter = 0;
	 	          status = true;
	 	      }
	 	      HAL_Delay(1);
	 	      counter++;
	 	      button_counter++;//tiempo seleccion boton
	 	      real_time();// actualiza las variables de tiempo (hours, minutes, seconds)
	 	  }

	 if ((button_counter >= 10) && (button_counter < 2000))
	 	  {

	 		  button_counter = 0;
	 		  hours = hours+1;
	 		  button_counter = 0;

	 		  if(hours >11){
	 			  hours =0;
	 		  }

	 		  shut_down();

	 	  }

	 else if (button_counter > (2000))
	 	  {
	 		  button_counter = 0;
	 		  est=1;
	 	      button_counter = 0;
	 	      shut_down();
	 	  }

 }

 while(est == 1)
 {
	 actual_minute = (float)minutes / 5;
	 show_hours(actual_minute);

	// Encender LED MINUTO
	 button_counter = 0;



	 while(!(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5) == 0))
	 	  {
	 	      if (status == false) {
	 	          counter = 0;
	 	          status = true;
	 	      }
	 	      HAL_Delay(1);
	 	      counter++;
	 	      button_counter++;//tiempo seleccion boton
	 	      real_time();// actualiza las variables de tiempo (hours, minutes, seconds)
	 	  }

	 if ((button_counter >= 10) && (button_counter < 2000))
	 	 	  {

	 	 		  button_counter = 0;
	 	 		  minutes = minutes+5;
	 	 		  button_counter = 0;

	 	 		if(minutes >55){
					  minutes =0;
				  }

				  shut_down();

	 	 	  }

	 	 else if (button_counter > (2000))
	 	  {
	 		  button_counter = 0;
	 		  est=3;
	 	      button_counter = 0;
	 	      shut_down();
	 	  }

 }

 mode_run();


}

void real_time()
{
    if(counter >= 400)
    {
        seconds++;
        if (seconds >= 60)
        {
            seconds = 0;
            minutes++;
            if (minutes >= 60)
            {
                minutes = 0;
                hours++;
                if (hours >= 11)
                {
                    hours = 0;
                }
            }
        }
        counter=0;
    }
}


void show_hours(int h) {
	switch (h) {
	        case 0:
	        	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, 1);

	            break;
	        case 1:
	        	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 1);
	            break;
	        case 2:
	        	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 1);
	            break;
	        case 3:
	        	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 1);
	            break;
	        case 4:
	        	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, 1);
	            break;
	        case 5:
	        	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, 1);
	            break;
	        case 6:
	        	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 1);
	            break;
	        case 7:
	        	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 1);
	            break;
	        case 8:
	        	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, 1);
	            break;
	        case 9:
	        	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 1);
	            break;
	        case 10:
	        	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
	            break;
	        case 11:
	        	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1);
	            break;
	        default:
	            break;
	    }
}

void show_minutes(GPIO_TypeDef* port, uint16_t Pin)
{
    for (int i = 0; i < 10; i++)
    {
    	HAL_GPIO_WritePin(port, Pin, !(HAL_GPIO_ReadPin(port, Pin))); // Encender LED MINUTO
        button_counter = 0;
        while( button_counter <= 300)
		{
			HAL_Delay(1);
			button_counter++;
			counter++;
			real_time(); // actualiza las variables de tiempo (hours, minutes, seconds)
		}
    }
}




void shut_down() {
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
