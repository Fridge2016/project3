#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include "../include/LoadBalancer.h"

std::string generateRandomIP() {
    return std::to_string(rand() % 256) + "." + std::to_string(rand() % 256) + "." + std::to_string(rand() % 256) + "." + std::to_string(rand() % 256);
}

Request generateRandomRequest() {
    std::string ipIn = generateRandomIP();
    std::string ipOut = generateRandomIP();
    int time = rand() % 100; // Random time between 0 and 99
    return Request(ipIn, ipOut, time);
}

std::string getCurrentTime() {
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);
    std::ostringstream oss;
    oss << std::put_time(localTime, "%m%d%H%M%S");
    return oss.str();
}

int main() {
    srand(time(0));

    int numServers, simulationTime;
    std::cout << "Enter the number of web servers: ";
    std::cin >> numServers;
    std::cout << "Enter the simulation time: ";
    std::cin >> simulationTime;

    LoadBalancer loadBalancer(numServers);

    // Generate initial queue of requests
    for (int i = 0; i < numServers * 100; ++i) {
        loadBalancer.addRequest(generateRandomRequest());
    }

    // Generate unique log file name using current time
    std::string logFileName = "simulation_" + getCurrentTime() + ".log";
    std::ofstream logfile("logs/" + logFileName);
    if (!logfile.is_open()) {
        std::cerr << "Error: Could not open log file for writing." << std::endl;
        return 1;
    }

    // Redirect stdout to log file
    std::streambuf *coutbuf = std::cout.rdbuf(); // Save old cout buffer
    std::cout.rdbuf(logfile.rdbuf()); // Redirect cout to log file

    // Log initial queue size and range for task times
    std::cout << "Initial Queue Size: " << loadBalancer.getRequestQueueLength() << std::endl;
    std::cout << "Range for Task Times: 0-99" << std::endl;

    // Run the simulation
    for (int time = 0; time < simulationTime; ++time) {
        loadBalancer.distributeRequest();
        loadBalancer.balanceLoad(); // Balance the load periodically

        // Add new requests at random times
        if (rand() % 10 < 3) { // 30% chance to add a new request
            loadBalancer.addRequest(generateRandomRequest());
        }

        // Print server and queue status to log file
        std::cout << "Time: " << time << std::endl;
        std::cout << "Server Status:" << std::endl;
        for (int i = 0; i < numServers; ++i) {
            std::cout << "Server " << i << ": ";
            if (loadBalancer.getServer(i).isIdle()) {
                std::cout << "Idle" << std::endl;
            } else {
                std::cout << "Processing request" << std::endl;
            }
        }
        std::cout << "Queue Length: " << loadBalancer.getRequestQueueLength() << std::endl;
        std::cout << std::endl;
    }

    // Close log file and restore stdout
    logfile.close();
    std::cout.rdbuf(coutbuf); // Restore old cout buffer

    std::cout << "Simulation complete. Log file saved as " << logFileName << std::endl;
    return 0;
}
