#include "http/Response.h"
#include <string>

// Parses a raw HTTP response into a Response struct.
//
// A raw HTTP response looks like:
//
//   HTTP/1.1 200 OK\r\n
//   Content-Type: application/json\r\n
//   \r\n
//   {"key":"...","cipherText":"..."}
//
// We only care about the status code and the body — everything between
// the blank line and the end of the string.
Response parseResponse(const std::string& raw) {
    Response res;

    // --- Extract status code ---
    // The status line always starts with "HTTP/1.1 " followed by 3 digits.
    const std::string httpPrefix = "HTTP/1.1 ";
    size_t statusStart = raw.find(httpPrefix);
    if (statusStart != std::string::npos) {
        statusStart += httpPrefix.size();
        res.statusCode = std::stoi(raw.substr(statusStart, 3));
    }

    // --- Extract body ---
    // The blank line separating headers from body is "\r\n\r\n".
    const std::string separator = "\r\n\r\n";
    size_t bodyStart = raw.find(separator);
    if (bodyStart != std::string::npos) {
        res.body = raw.substr(bodyStart + separator.size());
    }

    return res;
}
