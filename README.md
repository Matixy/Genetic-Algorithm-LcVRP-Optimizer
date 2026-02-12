# Genetic-Algorithm-LcVRP-Optimizer
A C++ object-oriented implementation of a Genetic Algorithm designed to solve the Limited Capacitated Vehicle Routing Problem (LcVRP), featuring custom memory management and strict architectural constraints.

> **Project Description**
> This project is a modular C++ implementation of a Genetic Algorithm (GA) designed to solve the **Limited Capacitated Vehicle Routing Problem (LcVRP)**. It features a strictly layered architecture with a custom `CConsoleInterface` controller and a robust, exception-free error handling system based on the **Result Pattern**.

## 🚀 Key Features

*   **Robust Error Handling (Result Pattern)**
    Instead of standard exceptions, the project uses a custom `CResult<T, E>` template system. Every major operation (Configuration, Initialization, Execution) returns a result object that enforces success checks before proceeding, ensuring stability even with invalid parameters.
*   **Layered Architecture**
    The code is organized into distinct modules:
    *   **Interface Layer:** `CConsoleInterface` handles user output and flow control.
    *   **Optimizer Layer:** `CGeneticAlgorithm`, `CEvaluator`, and `CIndividual` encapsulate the evolutionary logic.
    *   **Data Layer:** `CFileLoader` and `CDataInstance` handle file I/O and problem parsing.
*   **Genetic Operations**
    Implements standard evolutionary steps: Tournament Selection, Crossover, and Mutation to evolve solutions for the LcVRP problem.
*   **Restricted C++ Environment**
    Written in **C++11**, avoiding standard smart pointers and exceptions to demonstrate manual memory management and low-level control.

## 🛠 Technical Details

### Workflow
The application follows a strict execution pipeline managed by `CConsoleInterface`:

1.  **Configuration:** The `CEvaluator` loads problem data (e.g., `P-n16-k8.lcvrp`) and validates the format.
2.  **Initialization:** The `CGeneticAlgorithm` attempts to initialize the population. It validates parameters (population size, probabilities) – invalid values (e.g., negative probabilities) are caught immediately, returning an error state instead of crashing.
3.  **Execution:** If initialization succeeds, the algorithm runs the evolutionary loop.
4.  **Reporting:** Results or detailed error logs are printed to the console.

### Code Structure
The project is organized into logical namespaces/folders:
*   `consoleInterface/` - Handles application flow and stdout/stderr communication.
*   `optimizer/` - Core GA logic (`CGeneticAlgorithm`), fitness evaluation (`CEvaluator`), and genotype logic (`individual/`).
*   `files/` - File loading and data parsing utilities.
*   `errors/` - Custom `CError` classes for the Result pattern.

## 💻 Usage

The entry point is simplified to delegate control to the interface class.

**Code Example (`main.cpp`):**
```cpp
#include "consoleInterface/CConsoleInterface.h"

int main() {
    // The interface handles the entire lifecycle including
    // configuration, error catching, and result display.
    CConsoleInterface interface;
    interface.vRun();
    
    return 0;
}
