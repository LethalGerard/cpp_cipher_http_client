// ============================================================
//  Cipher CTF — student starter template
//
//  HOW THIS FILE IS ORGANISED
//  --------------------------
//  1. sendRequest()  — opens a TCP socket, sends the request,
//                      reads the full response, closes the socket.
//                      Real Winsock calls are shown; pseudocode
//                      sections are marked with  /* PSEUDO: ... */
//
//  2. main()         — calls sendRequest() for every endpoint,
//                      parses the JSON body, and prints the
//                      raw cipher text.  Decryption is left for you.
//
//  BUILD (Windows / MinGW or MSVC):
//    cmake -S . -B build && cmake --build build
//    build\cipher_client.exe
// ============================================================

#include <iostream>
#include <string>
#include <optional>
#include <vector>

#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")
#else // POSIX
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
#endif

#include "http/Request.h"
#include "http/Response.h"
#include "json/JsonParser.h"

std::optional<std::string> sendRequest(const std::string& host,
                                       int                port,
                                       const std::string& path)
{
    /**
     * ----------------------------------------------------------
     * STEP 1 - Create a TCP Socket
     * This is a file descriptor that the OS use to represent our
     * end of a network connection.
     * ----------------------------------------------------------
     */

     SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
     if (sock == INVALID_SOCKET)
     {
        std::cout << "Failed to create socket: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return std::nullopt;
     }

    /**
     * ----------------------------------------------------------)

    /**
     * ----------------------------------------------------------
     * STEP 2 - Fill in the server address struct
     * The sockaddr_in struct describes and IPv4 endpoint, with
     */

     sockaddr_in server;
     server.sin_family = AF_INET;
     server.sin_port = htons(8080);
     InetPtonA(AF_INET, "172.20.203.149", &server.sin_addr.S_un.S_addr);

     if (connect(sock, (SOCKADDR*)&server, sizeof(server)) == SOCKET_ERROR)
     {
        std::cout << "Failed to connect: " << WSAGetLastError << std::endl;
        closesocket(sock);
        WSACleanup();
        return std::nullopt;
     }

     /*
       * STEP 3 - Connect to the server
     * connect() performs the TCP three-way handshake, when this
     * succeeds - the socket is ready for I/O.
     * ----------------------------------------------------------
     */

     const std::string request = "GET /test HTTP/1.1\r\nHost: 172.20.203.149\r\nConnection: close\r\n\r\n";
     
     if (send(sock, request.c_str(), (int)request.length(), 0) == SOCKET_ERROR)
     {
        std::cout << "Failed to send request: " << WSAGetLastError() << std::endl;
        closesocket(sock);
        WSACleanup();
        return std::nullopt;
     }

    /**
     * ----------------------------------------------------------
     * STEP 4 - Build and send the HTTP request
     * Use the Request class to build a HTTP request, then use
     * send() to write raw bytes from a buffer into the TCP
     * stream.
     * ----------------------------------------------------------
     */
    /** 
     * ----------------------------------------------------------
     * STEP 5 - Read the response
     * recv() reads the bytes from the TCP stream into a buffer.
     * You can expect the following from recv():
     * - returns > 0 = there are more bytes to be read.
     * - returns 0 = all bytes have been read
     * - else = something went wrong.
     */

     char buffer[2048];
     std::string response;
     while (true)
     {
        memset(buffer, 0, sizeof(buffer));
        int bytesReceived = recv(sock, buffer, sizeof(buffer) - 1, 0);
        if (bytesReceived > 0) {
            response.append(buffer, bytesReceived);
        } else if (bytesReceived == 0) {
            break;
        } else {
            std::cout << "Failed to receive response: " << WSAGetLastError() << std::endl;
            break;
        }
     }

    /**
     * ----------------------------------------------------------
     * STEP 6 - Close the socket
     * Always clean up the - remember to close the socket!
     */

     std::cout << "Request sent to: " << host << ":" << port << path << std::endl;
     return response;
}

int main() {
    const std::string HOST = "192.168.0.106";
    const int         PORT = 8080;

    // Initialise Winsock (Windows only — must be done before any socket call).
    #ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "[error] WSAStartup failed\n";
        return 1;
    }
    #endif

    /**
     * ----------------------------------------------------------
     * STEP 1 - Implement the sendRequest() function
     * Start off by implementing the sendRequest() function and
     * then try it by using "/clear-text" endpoint.
     * 
     * Parse the response and then print out the result!
     * ----------------------------------------------------------
     */

    /**
     * ----------------------------------------------------------
     * STEP 2 - Decrypt the ciphertext!
     * Start trying to decrypt the ciphertext by sending requests
     * the the endpoints down below and decrypt them using the
     * KEY and CIPHERTEXT in the payload.
     * 
     * You can expect a payload in JSON format like this:
     * { "key": "...", "cipherText": "..." }
     * 
     * Suggested workflow:
     *      1. Send a GET request to the related endpoint
     *      2. Parse the Response to get the body
     *      3. Parse the body through JsonParser to extract the key + cipher text
     *      4. Decrypt the ciphertext and save the result in a file with the endpoint name
     */

    const std::vector<std::string> endpoints = {
        "/inverse-cipher",
        "/rot13-cipher",
        "/atbash-cipher",
        "/ceasar-cipher",
        "/base64-cipher",
        "/xor-cipher",
        "/rail-fence-cipher",
        "/substitution-cipher",
        "/columnar-transposition-cipher",
        "/vigenere-cipher",
        "/affine-cipher",
        "/monome-cipher",
        "/playfair-cipher",
    };

    for (const auto& path : endpoints) {
        /**
         * CODE
         */

        sendRequest(HOST, PORT, path);
    }
    #ifdef _WIN32
    WSACleanup();
    #endif
    return 0;
}
