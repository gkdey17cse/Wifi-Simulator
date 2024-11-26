#include <iostream>
#include <limits>
#include "WiFi4Simulator.hpp"
#include "WiFi5Simulator.hpp"
#include "WiFi6Simulator.hpp"

void displayMenu()
{
    std::cout << "===============================\n";
    std::cout << " WiFi Communication Simulator\n";
    std::cout << "===============================\n";
    std::cout << "Select Communication Type:\n";
    std::cout << "1. WiFi 4 (CSMA/CA)\n";
    std::cout << "2. WiFi 5 (MU-MIMO)\n";
    std::cout << "3. WiFi 6 (OFDMA)\n";
    std::cout << "0. Exit\n";
    std::cout << "Enter your choice: ";
}

// Utility function for validated integer input
int getValidatedInput(const std::string &prompt, int min = 0, int max = std::numeric_limits<int>::max())
{
    int value;
    while (true)
    {
        std::cout << prompt;
        std::cin >> value;

        // Check for invalid input or out-of-range values
        if (std::cin.fail() || value < min || value > max)
        {
            std::cin.clear();                                                   // Clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            std::cout << "Invalid input. Please enter a number between " << min << " and " << max << ".\n";
        }
        else
        {
            break;
        }
    }
    return value;
}

int main()
{
    int choice = -1;

    while (choice != 0)
    {
        displayMenu();
        choice = getValidatedInput("", 0, 3); // Valid choices are 0 to 3

        if (choice == 0)
        {
            std::cout << "Exiting WiFi Simulator. Goodbye!" << std::endl;
            break;
        }

        int numUsers = getValidatedInput("Enter the number of users: ", 1); // Minimum 1 user
        int bandwidth = 20;                                                 // Assuming 20 MHz bandwidth for all cases

        switch (choice)
        {
        case 1:
        {
            std::cout << "\nInitializing WiFi 4 Simulation...\n\n";
            try
            {
                WiFi4Simulator wifi4Simulator(numUsers, bandwidth);
                wifi4Simulator.runSimulation();
            }
            catch (const std::exception &e)
            {
                std::cerr << "Error during WiFi 4 Simulation: " << e.what() << "\n";
            }
            break;
        }
        case 2:
        {
            std::cout << "\nInitializing WiFi 5 Simulation...\n";
            try
            {
                WiFi5Simulator wifi5Simulator(numUsers, bandwidth);
                wifi5Simulator.runSimulation();
            }
            catch (const std::exception &e)
            {
                std::cerr << "Error during WiFi 5 Simulation: " << e.what() << "\n";
            }
            break;
        }
        case 3:
        {
            std::cout << "\nInitializing WiFi 6 Simulation...\n";
            try
            {
                WiFi6Simulator wifi6Simulator(numUsers, bandwidth);
                wifi6Simulator.runSimulation();
            }
            catch (const std::exception &e)
            {
                std::cerr << "Error during WiFi 6 Simulation: " << e.what() << "\n";
            }
            break;
        }
        default:
            std::cerr << "Unexpected error. This should never happen.\n";
        }

        std::cout << "===============================\n\n";
    }

    return 0;
}
