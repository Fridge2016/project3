#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <string>
#include "Request.h"

/**
 * @brief The WebServer class represents a web server that can process requests.
 */
class WebServer {
private:
    bool idle;          /**< Flag indicating if the server is idle. */
    int remainingTime;  /**< Remaining processing time for the current request. */

public:
    /**
     * @brief Default constructor for WebServer.
     */
    WebServer();

    /**
     * @brief Checks if the server is idle.
     * @return True if the server is idle, false otherwise.
     */
    bool isIdle() const;

    /**
     * @brief Processes a request.
     * @param req The request to process.
     */
    void processRequest(const Request& req);

    /**
     * @brief Updates the server's state.
     */
    void update();
};

#endif // WEBSERVER_H
