/*
 ******************************************************************************
 * @file           	: TB6612FNG.h
 * @brief          	: header file for TB6612FNG.c
 * @author			: Lawrence Stanton
 * @revised			: May 2020
 ******************************************************************************
 * @attention		: © LD Stanton 2020
 ******************************************************************************
 */

#ifndef INC_TB6612FNG_H_
#define INC_TB6612FNG_H_

#include "stm32f0xx_hal.h"

/* Basic Conventions */
#define HIGH	1
#define LOW		0

/* Structures & Enums */

/*
 * @brief	Simple identifier for TB6612FNG_Motor.
 */
typedef enum{
	TB6612FNG_Motor_A,
	TB6612FNG_Motor_B
}TB6612FNG_MotorNameTypedef;

/*
 * @brief	Compacted structure for determining the GPIO settings.
 */
typedef struct{
	unsigned short I1_STATE:1;		// GPIO Input 1 state
	unsigned short I2_STATE:1;		// GPIO Input 2 state
}TB6612FNG_MotorDirectionTypedef;

/* Convenient definitions for TB6612FNG_MotorDirectionTypedef */
#define FORWARD (TB6612FNG_MotorDirectionTypedef){HIGH, LOW}
#define REVERSE (TB6612FNG_MotorDirectionTypedef){LOW, HIGH}
#define BREAK 	(TB6612FNG_MotorDirectionTypedef){HIGH, HIGH}
#define STOP 	(TB6612FNG_MotorDirectionTypedef){LOW, LOW}

/*
 * @brief	Used for checking arguments for the Timer Channel.
 */
typedef enum{
	CHANNEL_1 = TIM_CHANNEL_1,
	CHANNEL_2 = TIM_CHANNEL_2,
	CHANNEL_3 = TIM_CHANNEL_3,
	CHANNEL_4 = TIM_CHANNEL_4
}HAL_TimerChannelTypedef;

/*
 * @brief 	Simple pin structure for easy referencing.
 */
typedef struct{
	GPIO_TypeDef * Port;
	uint16_t Pin;
}TB6612FNG_Pin;

/*
 * @brief 	Simple PWM timer structure for easy referencing.
 * @member	htim	The HAL timer object associated with the parent motor.
 * @member	channel	The PWM timer channel associated with the parent motor.
 */
typedef struct{
	TIM_HandleTypeDef * htim;
	HAL_TIM_StateTypeDef channel;
}TB6612FNG_Timer;

/*
 * @brief 	Primary structure used for setup and issuing commands.
 * @member	MOTOR	Used for identifying the motor (empty otherwise).
 * @member	I1*		The Pin for GPIO input 1
 * @member	I2*		The Pin for GPIO input 2
 * @member 	TIMER*	The Timer being used for PWM
 */
typedef struct{
	TB6612FNG_MotorNameTypedef MOTOR;

	TB6612FNG_Pin * I1;
	TB6612FNG_Pin * I2;

	TB6612FNG_Timer * TIMER;
}TB6612FNG_Motor;

/* Public function prototypes */
void setupTB6612FNG(TIM_HandleTypeDef * , TB6612FNG_Motor * , TB6612FNG_Motor * , TB6612FNG_Pin * );

void startTB6612FNG(void);
void stopTB6612FNG(void);

void motorState(TB6612FNG_Motor * , TB6612FNG_MotorDirectionTypedef);

void setMotorDutyCycle(TB6612FNG_Motor *, float);

#endif /* INC_TB6612FNG_H_ */
