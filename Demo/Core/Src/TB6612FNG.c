/*
 ******************************************************************************
 * @file        : TB6612FNG.c
 * @brief       : Driver for the TB6612FNG Motor Driver IC.
 *                Some methods rely on the STM32 HAl platform.
 * @author		: Lawrence Stanton
 * @revised		: May 2020
 ******************************************************************************
 * @attention	: © LD Stanton 2020
 ******************************************************************************
 * @instructions
 *
 * 1.	This file requires setup. Construct the necessary arguments using the provided enums
 * 		and other HAL typedefs and pass these into setupTB6612FNG. See the note on this method
 * 		for single motor use.
 * 2.	Start the motor using startTB6612FNG. This starts the PWM lines and enables the STBY line.
 * 3.	Control the motor using three basic commands:
 * 		a. Master control for start/stop operation. (Changing the STBY line, amongst others).
 * 		b. State control, effectively determining the direction of the motors.
 * 		c. PWM (speed) control.
 * 		These commands should be introduced and removed in this hierarchy, this is enforced in a, but not b.
 *
 * As the TB6612FNG does not provide feedback, neither do these methods. Some parameter checking is done, but
 * typedefs are used to mitigate errors. Other parameters will likely trigger a hard fault.
 */

#include "TB6612FNG.h"

/* Conditional rough estimates for safe operation */
#define TB6612FNG_BREAK_DELAY_MS	100

/* Pointers imported and held for ease of access
 * — must be instantiated in parent file. */

static TIM_HandleTypeDef 	* htim;
static TB6612FNG_Motor 		* MOTOR_A;
static TB6612FNG_Motor 		* MOTOR_B;
static TB6612FNG_Pin 		* STBY;

/* Private method prototypes. */
static void setPWM(TB6612FNG_Motor * , unsigned int);

/* Setup Methods */

/*
 * @bruef	Saves the necessary variables for start/stop operations.
 * @note	Pass the same motor into both motorA and motorB if i=only 1 motor used.
 * 			The other motor will remain in the default state without throwing errors.
 */
void setupTB6612FNG(TIM_HandleTypeDef * tim, TB6612FNG_Motor * motorA, TB6612FNG_Motor * motorB, TB6612FNG_Pin * stby){
	htim = tim;

	MOTOR_A = motorA;
	MOTOR_B = motorB;

	STBY = stby;
}

/* Master Control */

/*
 * @brief	Starts the PWM channels and enables the STBY line.
 * @note	Resets the PWM to 0% Duty Cycle and sets motor states to BREAK
 */
void startTB6612FNG(){
	/* Break both motors */
	setMotorDutyCycle(MOTOR_A, 0.0);
	setMotorDutyCycle(MOTOR_B, 0.0);
	motorState(MOTOR_A, BREAK);
	motorState(MOTOR_B, BREAK);

	/* Start PWM */
	HAL_TIM_PWM_Start(MOTOR_A->TIMER->htim, MOTOR_A->TIMER->channel);
	HAL_TIM_PWM_Start(MOTOR_B->TIMER->htim, MOTOR_B->TIMER->channel);

	/* Enable the STBY Line */
	HAL_GPIO_WritePin(STBY->Port, STBY->Pin, HIGH);
}

void stopTB6612FNG(){
	// Short break both motors.
	motorState(MOTOR_A, BREAK);
	motorState(MOTOR_B, BREAK);

	// Remove the PWM
	setMotorDutyCycle(MOTOR_A, 0.0);
	setMotorDutyCycle(MOTOR_B, 0.0);

	// Delay for some safety
	HAL_Delay(TB6612FNG_BREAK_DELAY_MS);

	// Set both motor states to STOP
	motorState(MOTOR_A, STOP);
	motorState(MOTOR_B, STOP);

	// Disable the STBY line.
	HAL_GPIO_WritePin(STBY->Port, STBY->Pin, LOW);
}

/* State Control */

/*
 * @brief	Sets the state of a motor to FORWARD, REVERSE, BREAK or STOP
 * @note	Does not slow. Careful changing direction suddenly.
 */
void motorState(TB6612FNG_Motor * MOTOR, TB6612FNG_MotorDirectionTypedef STATE){
	HAL_GPIO_WritePin(MOTOR->I1->Port, 	MOTOR->I1->Pin, 	STATE.I1_STATE);
	HAL_GPIO_WritePin(MOTOR->I2->Port, 	MOTOR->I2->Pin, 	STATE.I2_STATE);
}

/* PWM Control */

/*
 * @brief	Sets the speed of the motor according to a duty cycle.
 */
void setMotorDutyCycle(TB6612FNG_Motor * MOTOR, float D){
	/* Parameter Chancing */
	if((D > 1.0) || (D < 0)) D = 0.0;		// Reject and set to 0 if invalid number

	unsigned int ARR = __HAL_TIM_GET_AUTORELOAD(htim);	// Get the ARR value
	setPWM(MOTOR, (unsigned int)(D * ARR));				// Set with the count proportional to the ARR
}


static void setPWM(TB6612FNG_Motor * MOTOR, unsigned int counter){
	__HAL_TIM_SET_COMPARE(MOTOR->TIMER->htim, MOTOR->TIMER->channel, counter);	// Set PWM compare value
}
