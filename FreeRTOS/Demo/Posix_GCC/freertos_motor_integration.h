#ifndef _FREERTOS_MOTOR_INTEGRATION_H
#define _FREERTOS_MOTOR_INTEGRATION_H

#include <stdint.h>
#include "Motor.h"
#include "StateMachine.h"

// Enhanced queue message structure for motor control
typedef struct
{
    uint32_t messageType;    // 100 = speed command, 200 = emergency stop
    uint32_t speedValue;     // RPM value (50, 100, 150, 200)
    uint32_t sequenceId;     // For tracking message order
} FreeRTOSMotorMessage;

// Motor control message types
#define MOTOR_SPEED_COMMAND     100UL
#define MOTOR_EMERGENCY_STOP    200UL

// Speed values for cycling
#define MOTOR_SPEED_LOW         50
#define MOTOR_SPEED_MEDIUM      100
#define MOTOR_SPEED_HIGH        150
#define MOTOR_SPEED_MAX         200

// Motor instance declaration
extern Motor motorInstance;
extern SM_StateMachine motorStateMachine;

// Function declarations
void InitializeMotorStateMachine(void);
void ProcessMotorMessage(const FreeRTOSMotorMessage* pMessage);

#endif // _FREERTOS_MOTOR_INTEGRATION_H