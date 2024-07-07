#include <iostream>
#include <memory.h>
#include "Udp.hpp"

int main()
{
   int sock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
    if (sock < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Enable IP_HDRINCL to tell the kernel that headers are included in the packet
    int one = 1;
    if (setsockopt(sock, IPPROTO_IP, IP_HDRINCL, &one, sizeof(one)) < 0) {
        perror("setsockopt IP_HDRINCL failed");
        exit(EXIT_FAILURE);
    }



    struct sockaddr_in source = {}, destination{};
    source.sin_family = AF_INET;
    source.sin_addr.s_addr = inet_addr("127.0.0.1");
    source.sin_port = htons(12345);

    destination.sin_family = AF_INET;
    destination.sin_addr.s_addr = inet_addr("127.0.0.1");
    destination.sin_port = htons(4444);

    // Data to send
    std::string data = "udp goesss brrrr";

    // Build the packet
    auto buffer = udp::build_udp_packet(data, source, destination);
    udp::send_udp_packet(sock, std::move(buffer), sizeof(udp::IPHeader) + sizeof(udp::UDPHeader) + data.size(), destination);

    close(sock);
    return 0;
}
