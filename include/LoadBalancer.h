#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <vector>
#include "WebServer.h"
#include "RequestQueue.h"

/**
 * @brief The LoadBalancer class manages the load balancing of requests among web servers.
 */
class LoadBalancer {
private:
    std::vector<WebServer> servers; /**< Vector of web servers. */
    RequestQueue requestQueue;      /**< Request queue for incoming requests. */
    size_t minServers;              /**< Minimum number of servers to maintain. */

public:
    /**
     * @brief Constructor for LoadBalancer.
     * @param numServers The number of web servers to create.
     */
    LoadBalancer(int numServers);

    /**
     * @brief Adds a request to the load balancer.
     * @param req The request to add.
     */
    void addRequest(const Request& req);

    /**
     * @brief Distributes requests among web servers.
     */
    void distributeRequest();

    /**
     * @brief Balances the load among web servers.
     */
    void balanceLoad();

    /**
     * @brief Gets a reference to a web server.
     * @param index The index of the web server to get.
     * @return Reference to the web server.
     */
    const WebServer& getServer(int index) const;

    /**
     * @brief Gets the length of the request queue.
     * @return The length of the request queue.
     */
    size_t getRequestQueueLength() const;
};

#endif // LOADBALANCER_H
