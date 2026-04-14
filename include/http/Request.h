#pragma once
#include <string>

// Builds a raw HTTP/1.1 GET request string that can be sent directly
// over a TCP socket — no HTTP library involved.
//
// Example usage:
//   Request req("127.0.0.1", 8080, "/rot13-cipher");
//   std::string raw = req.build();
//   // send raw over your socket
class Request {
public:
    Request(const std::string& host, int port, const std::string& path);

    // Returns the fully-formed request string, ready to write to a socket.
    // The string includes the terminating \r\n\r\n blank line.
    std::string build() const;

private:
    std::string host_;
    int         port_;
    std::string path_;
};
