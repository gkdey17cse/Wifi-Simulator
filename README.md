# Modeling and Simulation of WiFi Communication

---

## Project Description

This project models and simulates WiFi communication using object-oriented programming principles. The simulator incorporates key features such as **inheritance**, **data abstraction**, **data hiding**, and **polymorphism** to represent and simulate WiFi 4, WiFi 5, and WiFi 6 technologies.

---

### Communication Types

1. **WiFi 4 Communication (CSMA/CA)**

   - Simulates communication via a single access point (AP) and a set of users.
   - Implements sniffing of the channel and random backoff times for collision avoidance.
   - Evaluates **throughput**, **average latency**, and **maximum latency** for:
     - 1 user and 1 AP
     - 10 users and 1 AP
     - 100 users and 1 AP
   - Assumptions:
     - 20 MHz bandwidth
     - 256-QAM modulation with a coding rate of 5/6
     - 1 KB packet size

2. **WiFi 5 Communication (MU-MIMO)**

   - Allows parallel transmissions after a broadcast packet and sequential **channel state information (CSI)** transmissions.
   - Simulates **round-robin scheduling** of users.
   - Evaluates **throughput**, **average latency**, and **maximum latency** for:
     - 1 user and 1 AP
     - 10 users and 1 AP
     - 100 users and 1 AP

3. **WiFi 6 Communication (OFDMA)**
   - Enables subdivision of a 20 MHz channel into 2 MHz, 4 MHz, or 10 MHz sub-channels.
   - Supports parallel communication across sub-channels for 5 ms intervals.
   - Simulates **round-robin scheduling** of users.
   - Evaluates **throughput**, **average latency**, and **maximum latency** for:
     - 1 user and 1 AP
     - 10 users and 1 AP
     - 100 users and 1 AP

---

## Directory Structure

````plaintext
WiFiSimulator/
├── include/                # Header files
│   ├── Simulator.hpp       # Base class for all WiFi simulations
│   ├── WiFi4Simulator.hpp  # WiFi 4-specific header
│   ├── WiFi5Simulator.hpp  # WiFi 5-specific header
│   ├── WiFi6Simulator.hpp  # WiFi 6-specific header
│   ├── AccessPoint.hpp     # Access Point abstraction
|   ├── Channel.hpp         # Channel abstraction
│   ├── Packet.hpp          # Packet abstraction
|   ├── User.hpp            # User abstraction
│
├── src/                    # Source files
│   ├── Simulator.cpp       # Base class implementation
│   ├── WiFi4Simulator.cpp  # WiFi 4-specific implementation
│   ├── WiFi5Simulator.cpp  # WiFi 5-specific implementation
│   ├── WiFi6Simulator.cpp  # WiFi 6-specific implementation
│   ├── AccessPoint.cpp     # Access Point implementation
│   └── main.cpp            # Entry point for the simulator
│   ├── User.cpp            # User Class implementation
│   └── Packet.cpp          # Packet Class implementation
│   ├── Channel.cpp         # Channel Class implementation
│
├── build/                  # Compiled object files and executable
│   ├── *.o                 # Object files
│   └── WiFiSimulator_opt   # Final executable
│   └── WiFiSimulator_debug # Final debug file
│
├── Makefile                # Build configuration
└── README.md               # Documentation (this file)

````

## Compilation and Execution Using Makefile

The `Makefile` automates the compilation process for both debug and optimized builds of all three parts of the system. Here’s how to use it:

### Build Commands

1. Compile all debug and optimized binaries:
   ```bash
   make
    ````

### To Run Files

1. To run debug version :
   ```bash
   ./build/WiFiSimulator_debug
   ```
2. To run Question1.cpp optimized version :
   ```bash
   ./build/WiFiSimulator_opt
   ```

### Clean Compiled Files

1. Clean all debug and optimized binaries:
   ```bash
   make clean
   ```

## Note

This project was developed with the assistance of OpenAI's ChatGPT and references from various open-source platforms. The insights, explanations, and code snippets provided by ChatGPT were instrumental in understanding and implementing the WiFi communication simulation. Additionally, open-source resources were used for ideas and inspiration in building this educational project.

Special acknowledgment to OpenAI and the open-source community for their invaluable contributions and support.
