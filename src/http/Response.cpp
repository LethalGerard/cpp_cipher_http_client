#include "http/Response.h"
#include <string>

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
