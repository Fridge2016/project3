#ifndef REQUESTQUEUE_H
#define REQUESTQUEUE_H

#include <queue>
#include "Request.h"

/**
 * @brief The RequestQueue class represents a queue of requests.
 */
class RequestQueue {
private:
    std::queue<Request> queue; /**< Queue of requests. */

public:
    /**
     * @brief Adds a request to the queue.
     * @param req The request to add.
     */
    void enqueue(const Request& req);

    /**
     * @brief Removes and returns the front request from the queue.
     * @return The front request in the queue.
     */
    Request dequeue();

    /**
     * @brief Checks if the queue is empty.
     * @return True if the queue is empty, false otherwise.
     */
    bool isEmpty() const;

    /**
     * @brief Gets the size of the queue.
     * @return The size of the queue.
     */
    size_t size() const;
};

#endif // REQUESTQUEUE_H
