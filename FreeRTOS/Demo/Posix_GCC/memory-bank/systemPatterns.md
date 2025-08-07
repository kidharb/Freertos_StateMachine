# System Patterns *Optional*

This file documents recurring patterns and standards used in the project.
It is optional, but recommended to be updated as the project evolves.
2025-08-07 22:30:04 - Initial system patterns documentation.

## Coding Patterns

* FreeRTOS task creation using [`xTaskCreate()`](main_blinky.c:147)
* Queue-based inter-task communication using [`xQueueSend()`](main_blinky.c:207) and [`xQueueReceive()`](main_blinky.c:244)
* State machine macro-based definitions using [`STATE_DEFINE()`](C_StateMachine/Motor.c:57)
* Event handling through transition maps using [`BEGIN_TRANSITION_MAP`](C_StateMachine/Motor.c:35)

## Architectural Patterns

* Producer-Consumer pattern: Sender task and timer produce events, receiver task consumes
* State Machine pattern: Event-driven state transitions with data encapsulation
* Memory management abstraction: [`SM_XAlloc()`](C_StateMachine/StateMachine.h:29) for configurable allocation strategy
* Separation of concerns: State logic separated from FreeRTOS task management

## Testing Patterns

* Console output for state transitions and event processing
* Periodic event generation for predictable testing
* Timer-based events for timeout scenarios