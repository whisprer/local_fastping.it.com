// simple_linux_listener.cpp - Linux version of your Windows listener
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

int main() {
    std::cout << "🔊 Simple Linux Listener Starting...\n";
    std::cout << "📡 Listening on port 9876...\n\n";

    // Create socket (Linux way)
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        std::cerr << "❌ Socket creation failed\n";
        return 1;
    }

    // Allow address reuse
    int opt = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(9876); // same port as beacon target
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sock, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "❌ Bind failed\n";
        close(sock);  // Linux uses close(), not closesocket()
        return 1;
    }

    char buffer[512];
    sockaddr_in clientAddr;
    socklen_t addrLen = sizeof(clientAddr);  // Linux uses socklen_t, not int

    std::cout << "✅ Listening for packets...\n";

    while (true) {
        int recvLen = recvfrom(sock, buffer, sizeof(buffer) - 1, 0, (sockaddr*)&clientAddr, &addrLen);
        if (recvLen > 0) {
            buffer[recvLen] = '\0';
            
            // Get sender IP
            char senderIP[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &clientAddr.sin_addr, senderIP, INET_ADDRSTRLEN);
            
            std::cout << "📨 Received from " << senderIP << ": " << buffer << "\n";
        }
    }

    close(sock);  // Linux cleanup
    return 0;
}
