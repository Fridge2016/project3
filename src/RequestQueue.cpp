#include "../include/RequestQueue.h"

void RequestQueue::enqueue(const Request& req) {
    queue.push(req);
}

Request RequestQueue::dequeue() {
    Request req = queue.front();
    queue.pop();
    return req;
}

bool RequestQueue::isEmpty() const {
    return queue.empty();
}

size_t RequestQueue::size() const {
    return queue.size();
}
