# Robotic Joint Manager 🤖

A robust, dynamic memory management system written in pure C for tracking and controlling robotic manipulator joints.

## Overview
This project simulates the control unit of a robotic arm. It uses a dynamic linked-list architecture to manage an arbitrary number of motor joints, preventing memory waste and allowing real-time addition or removal of axes. 

It includes safety checks to prevent software-commanded positions from exceeding physical mechanical limits (jog limits).

## Architecture
The system is modularized for scalability and maintainability:
* `robot.h`: System interface, data structures (Nodes and Motor states), and function prototypes.
* `robot.c`: Core logic implementation (memory allocation, list traversal, I/O sanitization).
* `main.c`: User interface and operational loop.
* `Makefile`: Automated build system.

## Features
- **Dynamic Allocation:** Add/Remove joints on the fly without static array limits.
- **Safety Protocol:** Real-time limit checking on position updates to prevent mechanical failure.
- **I/O Sanitization:** Buffer-clearing loops to prevent infinite crashes on wrong user inputs.
- **Persistent Storage:** Save current manipulator configuration to a local file and reload it on boot.


## Future Improvements
* Porting the core logic to C++ using Object-Oriented Principles.

* Encapsulating the application within a Docker container for cross-platform deployment.

## Build and Run (Linux / MacOS)
To compile the system using the provided Makefile:
```bash
make
./robot_manager

