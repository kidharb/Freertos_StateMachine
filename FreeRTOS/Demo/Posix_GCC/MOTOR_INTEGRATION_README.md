# FreeRTOS Motor Control State Machine Integration

## Overview

This project successfully integrates a C state machine framework with a FreeRTOS POSIX demo, creating a sophisticated motor control system that demonstrates event-driven state management in a real-time operating system environment.

## Architecture

### System Components

1. **FreeRTOS Tasks**
   - **Sender Task** ([`prvQueueSendTask()`](main_blinky.c:191)): Generates motor speed commands
   - **Timer Task** ([`prvQueueSendTimerCallback()`](main_blinky.c:220)): Generates emergency stop events
   - **Receiver Task** ([`prvQueueReceiveTask()`](main_blinky.c:239)): Processes events through motor state machine

2. **State Machine Framework**
   - **Motor State Machine** ([`Motor.c`](C_StateMachine/Motor.c)): Handles motor control logic
   - **State Engine** ([`StateMachine.c`](C_StateMachine/StateMachine.c)): Core state machine execution
   - **Memory Management** ([`sm_allocator.c`](C_StateMachine/sm_allocator.c)): Fixed block allocator

3. **Integration Layer**
   - **Motor Integration** ([`freertos_motor_integration.c`](freertos_motor_integration.c)): Bridges FreeRTOS and state machine
   - **Event Translation**: Converts queue messages to motor events

### Event Flow

```
Sender Task (200ms) ──┐
                      ├─► FreeRTOS Queue ──► Receiver Task ──► Motor State Machine
Timer (2000ms) ───────┘                                      │
                                                              ▼
                                                         Motor States:
                                                         • IDLE
                                                         • START  
                                                         • CHANGE_SPEED
                                                         • STOP
```

## Event Mapping

| Source | Message Type | Speed Value | State Machine Event |
|--------|-------------|-------------|-------------------|
| Sender Task | 100 | 50, 100, 150, 200 RPM | [`MTR_SetSpeed`](C_StateMachine/Motor.h:20) |
| Timer | 200 | 0 (unused) | [`MTR_Halt`](C_StateMachine/Motor.h:21) |

## Key Features

### Motor Speed Control
- **Speed Cycling**: Sender task cycles through 4 speed levels (50, 100, 150, 200 RPM)
- **Smooth Transitions**: State machine handles speed changes via `ST_CHANGE_SPEED` state
- **Speed Validation**: Current speed accessible via [`MTR_GetSpeed`](C_StateMachine/Motor.h:24)

### Emergency Stop System
- **Timer-Based**: Emergency stop triggered every 2 seconds
- **Immediate Response**: Motor halts regardless of current state
- **Safe Transition**: Emergency stop → `ST_STOP` → `ST_IDLE`

### Memory Management
- **Fixed Block Allocator**: Efficient memory management for event data
- **FreeRTOS Compatible**: Integrates with FreeRTOS heap management
- **Automatic Cleanup**: Event data automatically freed after processing

## Implementation Details

### Enhanced Data Structures

```c
// Queue message structure
typedef struct {
    uint32_t messageType;    // 100 = speed, 200 = emergency
    uint32_t speedValue;     // RPM value
    uint32_t sequenceId;     // Message tracking
} FreeRTOSMotorMessage;
```

### State Machine Integration

```c
// Motor instance and state machine
Motor motorInstance = { 0 };
SM_DEFINE(Motor, &motorInstance)

// Event processing
void ProcessMotorMessage(const FreeRTOSMotorMessage* pMessage);
```

### Build System Updates

- **Makefile**: Updated to include state machine source files
- **CMakeLists.txt**: Enhanced for CMake-based builds
- **Include Paths**: Added `C_StateMachine` directory
- **Fault Handler**: Custom C implementation for assertion handling

## Expected Behavior

When running the integrated system, you should see output like:

```
Motor state machine initialized
=== Motor Control Message Received ===
Processing speed command: 50 RPM (seq: 1)
Motor ST_Start: 50
Current motor speed: 50 RPM
=======================================

=== Motor Control Message Received ===
Processing speed command: 100 RPM (seq: 2)
Motor ST_ChangeSpeed: 100
Current motor speed: 100 RPM
=======================================

=== Motor Control Message Received ===
Processing emergency stop command (seq: 3)
Motor ST_Stop: 0
Motor ST_Idle
Current motor speed: 0 RPM
=======================================
```

## Files Created/Modified

### New Files
- [`freertos_motor_integration.h`](freertos_motor_integration.h): Integration interface
- [`freertos_motor_integration.c`](freertos_motor_integration.c): Integration implementation
- [`fault_handler.c`](fault_handler.c): C-compatible fault handling

### Modified Files
- [`main_blinky.c`](main_blinky.c): Updated tasks for motor control
- [`Makefile`](Makefile): Added state machine build support
- [`CMakeLists.txt`](CMakeLists.txt): Enhanced CMake configuration

## Building and Running

### Using Makefile
```bash
make clean
make USER_DEMO=BLINKY_DEMO
./build/posix_demo
```

### Using CMake
```bash
mkdir build && cd build
cmake .. -DUSER_DEMO=BLINKY_DEMO
make
./posix_demo
```

## Testing Scenarios

1. **Normal Operation**: Observe speed cycling (50→100→150→200 RPM)
2. **Emergency Stop**: Timer triggers halt every 2 seconds
3. **State Transitions**: Monitor state changes in console output
4. **Memory Management**: Verify no memory leaks during operation

## Technical Benefits

- **Separation of Concerns**: Clean separation between RTOS and state logic
- **Scalability**: Easy to add new states and events
- **Maintainability**: Well-structured, documented code
- **Reusability**: State machine framework can be used for other applications
- **Real-time Performance**: Efficient event processing suitable for embedded systems

## Future Enhancements

- Add more motor control states (ACCELERATING, DECELERATING, FAULT)
- Implement motor direction control (FORWARD, REVERSE)
- Add sensor feedback integration
- Implement PID control for precise speed regulation
- Add diagnostic and monitoring capabilities