#include "../include/Request.h"

Request::Request() : IP_in("0.0.0.0"), IP_out("0.0.0.0"), time(0) {}

Request::Request(std::string in, std::string out, int t) : IP_in(in), IP_out(out), time(t) {}
