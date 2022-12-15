/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define		INCREMENTO	200 // TEMPO PARA O INCREMENTADO NO DISPLAY
#define 	COMUTA		10   // TEMPO DE COMUTACAO
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint32_t incremento = 0, comuta = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

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
	uint8_t disp7seg[16][7] = {
		 // {A,B,C,D,E,F,G}
			{1,1,1,1,1,1,0},    // 0
			{0,1,1,0,0,0,0},    // 1
			{1,1,0,1,1,0,1},    // 2
			{1,1,1,1,0,0,1},    // 3
			{0,1,1,0,0,1,1},    // 4
			{1,0,1,1,0,1,1},    // 5
			{1,0,1,1,1,1,1},    // 6
			{1,1,1,0,0,0,0},    // 7
			{1,1,1,1,1,1,1},    // 8
			{1,1,1,1,0,1,1},    // 9

		 // {A,B,C,D,E,F,G}
	};
		uint8_t flag = 0;
		uint8_t unid = 0;
		uint8_t dez = 0;
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

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  if ((HAL_GetTick() - comuta) > COMUTA){
	  	  		  comuta = HAL_GetTick();
	  	  	  		  if (flag == 0){
	  	  	  			  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,!disp7seg[unid][0]); //seg_A
	  	  	  			  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,!disp7seg[unid][1]); //seg_B
	  	  	  			  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,!disp7seg[unid][2]); //seg_C
	  	  	  			  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,!disp7seg[unid][3]); //seg_D
	  	  	  			  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,!disp7seg[unid][4]); //seg_E
	  	  	  			  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,!disp7seg[unid][5]); //seg_F
	  	  	  			  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9,!disp7seg[unid][6]);  //seg_G

	  	  	  			  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,1); 	// Desliga Display dezena
	  	  	  			  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,0); 	// Liga Display Unidade
	  	  	  			  flag = 1;
	  	  	  		  }else{
	  	  	  			  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,!disp7seg[dez][0]); //seg_A
	  	  	  			  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,!disp7seg[dez][1]); //seg_B
	  	  	  			  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,!disp7seg[dez][2]); //seg_C
	  	  	  			  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,!disp7seg[dez][3]); //seg_D
	  	  	  			  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,!disp7seg[dez][4]); //seg_E
	  	  	  			  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,!disp7seg[dez][5]); //seg_F
	  	  	  			  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9,!disp7seg[dez][6]);  //seg_G

	  	  	  			  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,1); 	// Desliga Display unidade
	  	  	  			  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,0); 	// Liga Display dezena
	  	  	  			  flag = 0;
	  	  	  		  }
	  	  	  	  }
	  if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_8) == 0){
			  unid++;
			  if (unid > 9){
				  unid = 0;
				  dez++;
			  }
			  if (dez == 4 && unid==9){
				 unid = 8;
				 dez = 4;
			  }
		  }
	  if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7) == 0){
				  unid--;
				  if (unid < 0){
					  unid = 9;
					  dez--;
				  }
				  if (dez == 0 && unid==0){
					 unid = 0;
					 dez = 0;
				  }
		  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_10|GPIO_PIN_11
                          |GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15
                          |GPIO_PIN_5|GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pins : PB0 PB1 PB10 PB11
                           PB12 PB13 PB14 PB15
                           PB5 PB9 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_10|GPIO_PIN_11
                          |GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15
                          |GPIO_PIN_5|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB6 PB7 PB8 */
  GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

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
