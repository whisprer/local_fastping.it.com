// simple_linux_beacon.cpp - Linux version of your Windows beacon
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <cstring>

const char* TARGET_IP = "127.0.0.1";  // Change this as needed
const int TARGET_PORT = 9876;         // Changed to match your listener
const int BEACON_INTERVAL_MS = 10000; // 10 seconds

int main() {
    std::cout << "🚀 Simple Linux Beacon Starting...\n";
    std::cout << "📡 Target: " << TARGET_IP << ":" << TARGET_PORT << "\n";
    std::cout << "⏰ Interval: " << BEACON_INTERVAL_MS/1000 << " seconds\n\n";

    // Create socket
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        std::cerr << "❌ Socket creation failed\n";
        return 1;
    }

    // Set destination
    sockaddr_in dest;
    dest.sin_family = AF_INET;
    dest.sin_port = htons(TARGET_PORT);
    dest.sin_addr.s_addr = inet_addr(TARGET_IP);

    const char* message = "{\"status\":\"alive\",\"id\":\"beacon-002\",\"time\":1234567890}";
    int beacon_count = 0;

    while (true) {
        beacon_count++;
        
        int sent = sendto(sock, message, strlen(message), 0, (sockaddr*)&dest, sizeof(dest));
        
        if (sent > 0) {
            std::cout << "[" << beacon_count << "] 📤 Beacon sent to " 
                     << TARGET_IP << ":" << TARGET_PORT << "\n";
        } else {
            std::cout << "[" << beacon_count << "] ❌ Beacon failed\n";
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(BEACON_INTERVAL_MS));
    }

    close(sock);
    return 0;
}
