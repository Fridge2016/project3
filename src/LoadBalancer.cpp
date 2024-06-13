#include "../include/LoadBalancer.h"
#include <iostream>

LoadBalancer::LoadBalancer(int numServers) : servers(numServers), minServers(numServers) {}

void LoadBalancer::addRequest(const Request& req) {
    requestQueue.enqueue(req);
}

void LoadBalancer::distributeRequest() {
    for (auto& server : servers) {
        server.update();
        if (server.isIdle() && !requestQueue.isEmpty()) {
            server.processRequest(requestQueue.dequeue());
        }
    }
}

void LoadBalancer::balanceLoad() {
    // Log starting queue size
    size_t startingQueueSize = requestQueue.size();
    std::cout << "Starting Queue Size: " << startingQueueSize << std::endl;

    size_t busyServers = 0;
    for (const auto& server : servers) {
        if (!server.isIdle()) {
            busyServers++;
        }
    }

    if (requestQueue.isEmpty() && busyServers < servers.size()) {
        servers.pop_back();
    } else if (!requestQueue.isEmpty() && busyServers == servers.size()) {
        servers.emplace_back();
    }

    while (servers.size() < minServers) {
        servers.emplace_back();
    }

    // Log ending queue size
    size_t endingQueueSize = requestQueue.size();
    std::cout << "Ending Queue Size: " << endingQueueSize << std::endl;

    // Log range for task times
    std::cout << "Range for Task Times: 1-" << minServers << std::endl;
}


size_t LoadBalancer::getRequestQueueLength() const {
    return requestQueue.size();
}
