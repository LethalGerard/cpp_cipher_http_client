#include "http/Request.h"
#include <sstream>

Request::Request(const std::string& host, int port, const std::string& path)
    : host_(host), port_(port), path_(path) {}

std::string Request::build() const {
    std::ostringstream oss;
    oss << "GET " << path_ << " HTTP/1.1\r\n"
        << "Host: " << host_ << ":" << port_ << "\r\n"
        << "Connection: close\r\n"
        << "\r\n";
    return oss.str();
}
