# Product Context

This file provides a high-level overview of the project and the expected product that will be created. Initially it is based upon projectBrief.md (if provided) and all other available project-related information in the working directory. This file is intended to be updated as the project evolves, and should be used to inform all other modes of the project's goals and context.
2025-08-07 22:28:06 - Initial Memory Bank creation for FreeRTOS State Machine Integration project.

## Project Goal

Integrate a C state machine framework with a FreeRTOS POSIX demo program. The goal is to modify the existing FreeRTOS blinky demo to use the state machine framework for event processing, creating a more sophisticated event-driven system.

## Key Features

* FreeRTOS POSIX-aware demo running on x86 laptop
* Two FreeRTOS tasks: one for message generation, one for message reception
* Software timer for periodic event generation
* C state machine framework with Motor example implementation
* Integration of state machine event processing into the receiver task
* Event simulation capabilities from sender task and timer

## Overall Architecture

* **Base System**: FreeRTOS blinky demo with queue-based inter-task communication
* **State Machine Framework**: Robust C implementation with macros for state definition
* **Integration Point**: Receiver task ([`prvQueueReceiveTask()`](main_blinky.c:231)) will be modified to process events through state machine
* **Event Sources**: Sender task and timer will generate different event types for state machine processing
* **Memory Management**: State machine uses configurable allocator (fixed block or heap)