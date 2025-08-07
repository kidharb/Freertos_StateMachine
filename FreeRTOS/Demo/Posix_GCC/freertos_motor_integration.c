#include "freertos_motor_integration.h"
#include "console.h"
#include <stdio.h>

// Motor instance and state machine
Motor motorInstance = { 0 };
SM_DEFINE(Motor, &motorInstance)

void InitializeMotorStateMachine(void)
{
    // Initialize motor instance
    motorInstance.currentSpeed = 0;
    
    // Initialize state machine to IDLE state
    MotorObj.currentState = 0; // ST_IDLE
    MotorObj.newState = 0;
    MotorObj.eventGenerated = FALSE;
    MotorObj.pEventData = NULL;
    
    console_print("Motor state machine initialized\n");
}

void ProcessMotorMessage(const FreeRTOSMotorMessage* pMessage)
{
    if (pMessage == NULL)
    {
        console_print("Error: NULL message received\n");
        return;
    }
    
    switch (pMessage->messageType)
    {
        case MOTOR_SPEED_COMMAND:
        {
            // Create motor data for speed command
            MotorData* pMotorData = (MotorData*)SM_XAlloc(sizeof(MotorData));
            if (pMotorData != NULL)
            {
                pMotorData->speed = pMessage->speedValue;
                console_print("Processing speed command: %d RPM (seq: %d)\n", 
                             pMessage->speedValue, pMessage->sequenceId);
                
                // Send SetSpeed event to motor state machine
                SM_Event(Motor, MTR_SetSpeed, pMotorData);
            }
            else
            {
                console_print("Error: Failed to allocate memory for motor data\n");
            }
            break;
        }
        
        case MOTOR_EMERGENCY_STOP:
        {
            console_print("Processing emergency stop command (seq: %d)\n", 
                         pMessage->sequenceId);
            
            // Send Halt event to motor state machine
            SM_Event(Motor, MTR_Halt, NULL);
            break;
        }
        
        default:
        {
            console_print("Unknown message type: %d\n", pMessage->messageType);
            break;
        }
    }
}