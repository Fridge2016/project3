#include "../include/WebServer.h"

WebServer::WebServer() : idle(true), remainingTime(0) {}

bool WebServer::isIdle() const {
    return idle;
}

void WebServer::processRequest(const Request& req) {
    idle = false;
    remainingTime = req.time;
    // Process the request here...
}

void WebServer::update() {
    if (!idle) {
        remainingTime--;
        if (remainingTime == 0) {
            idle = true;
        }
    }
}
