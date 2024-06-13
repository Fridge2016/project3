#include <iostream>
#include <cstdlib>
#include <ctime>
#include "../include/LoadBalancer.h"
#include <fstream>

std::string generateRandomIP() {
    return std::to_string(rand() % 256) + "." + std::to_string(rand() % 256) + "." + std::to_string(rand() % 256) + "." + std::to_string(rand() % 256);
}

Request generateRandomRequest() {
    std::string ipIn = generateRandomIP();
    std::string ipOut = generateRandomIP();
    int time = rand() % 100; // Random time between 0 and 99
    return Request(ipIn, ipOut, time);
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

    // Open log file for writing
    std::ofstream logfile("logs/simulation.log");
    if (!logfile.is_open()) {
        std::cerr << "Error: Could not open log file for writing." << std::endl;
        return 1;
    }

    // Redirect stdout to log file
    std::streambuf *coutbuf = std::cout.rdbuf(); // Save old cout buffer
    std::cout.rdbuf(logfile.rdbuf()); // Redirect cout to log file

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

    std::cout << "Simulation complete. Log file saved as simulation.log" << std::endl;
    return 0;
}
