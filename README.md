# Quantum Radar
## Overview

This project is a C++ implementation of a traffic radar processing system, designed to handle incoming data from a physical radar and evaluate it against a set of traffic rules. The system detects violations, issues itemized fines, and aggregates statistical data across all observations.

This project was built to satisfy the requirements of the Fawry Quantum Internship Challenge.

## System Architecture

The system is built with extensibility and maintainability in mind, heavily utilizing Object-Oriented Design (OOD) principles.

To satisfy the requirement that new rules can be added *without* modifying the core `radar` class, the project implements the **Strategy Design Pattern**.

* **`IRule` Interface:** An abstract base class that defines the contract for any traffic rule.
* **Concrete Rules:** Individual classes (`truck_speed`, `private_speed`, `seatbelt`) inherit from `IRule` and implement their specific validation logic (`check_violation`).
* **Radar Engine:** The core system maintains a collection of generic `IRule` pointers. It blindly evaluates incoming observations against all registered rules, making it completely decoupled from the specific rule logic.

## Features

* **Observation Processing:** Parses data including plate number, date, car type (Private, Truck, Bus), speed, and seatbelt status.
* **Dynamic Violation Detection:**
* Restricts truck speeds to a maximum of 60 km/h.
* Restricts private car speeds to a maximum of 80 km/h.
* Enforces seatbelt requirements across all vehicle types.


* **Itemized Ticketing:** Generates accurate fine reports detailing the specific violations and their individual fees in EGP.
* **Data Aggregation:**
* Tracks and maps total fine amounts to specific vehicle plate numbers.
* Maintains a statistical count of how many times each specific rule was violated.



## Prerequisites

To build and run this project, you will need:

* A C++ compiler that supports C++20 or higher (GCC, Clang, or MSVC).
* CMake (if building via an IDE like CLion or using CMake build scripts).

## Build and Execution

**Using a standard G++ compiler:**

```bash
# Compile the source code
g++ -std=c++20 main.cpp -o quantum_radar

# Run the executable
./quantum_radar

```

**Using CMake (e.g., CLion):**

1. Ensure your `CMakeLists.txt` is properly configured to include `main.cpp`.
2. Build the project using your IDE's build button.
3. Run the generated executable located in your `cmake-build-*/` directory.

## Example Output

When processing an observation that triggers multiple violations, the system outputs the fine exactly as requested:

```text
Traffic fine for car PRV-1004
Total amount: 400 EGP
Violations:
speed of 120 exceeded max allowed 80: 300 EGP
Seatbelt not fastned : 100 EGP
-----------------------------------

```

It also generates the required summary reports:

```text
--- All Fines by Plate Number ---
PRV-1004 : 400 EGP
TRK-2003 : 600 EGP

--- Violated Rules Count ---
Private Car Speed Limit : 1
Seatbelt Requirement : 2
Truck Speed Limit : 1

```