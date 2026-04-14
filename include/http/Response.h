#pragma once
#include <string>

// Holds a parsed HTTP response.
struct Response {
    int         statusCode = 0;   // e.g. 200, 404, 501
    std::string body;             // everything after the blank line (\r\n\r\n)
};

// Splits a raw HTTP response string into a Response struct.
// The body is returned as-is (plain text or JSON string).
Response parseResponse(const std::string& raw);
