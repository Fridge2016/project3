#ifndef REQUEST_H
#define REQUEST_H

#include <string>

/**
 * @brief The Request struct represents a request with source and destination IP addresses and a processing time.
 */
struct Request {
    std::string IP_in;  /**< Source IP address. */
    std::string IP_out; /**< Destination IP address. */
    int time;           /**< Processing time in clock cycles. */

    /**
     * @brief Default constructor for Request.
     */
    Request();

    /**
     * @brief Parameterized constructor for Request.
     * @param in Source IP address.
     * @param out Destination IP address.
     * @param t Processing time.
     */
    Request(std::string in, std::string out, int t);
};

#endif // REQUEST_H
