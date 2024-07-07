//
// Created by mahdi on 7/7/24.
//

#ifndef UDP_HPP
#define UDP_HPP

#include <cstdint>
#include <iostream>
#include <memory>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <memory.h>
#include<cstring>

namespace udp
{
    struct IPHeader
    {
        std::uint8_t internet_header_length : 4{}; // determine where the data protion of packet begins
        std::uint8_t version : 4{}; // ipv4 or ipv6
        std::uint8_t type_of_service{}; // trafic control mechanisms.
        std::uint16_t total_ip_lengh{};
        std::uint16_t id{};
        std::uint16_t offset{}; // where in the packet this fragment belongs
        std::int8_t ttl{};
        std::uint8_t protocol{}; // tcp or udp
        std::uint16_t checksum{}; // header checksum. checks if error happend
        in_addr src{}, dest{};
    };

    struct UDPHeader
    {
        std::uint16_t src_port{};
        std::uint16_t dest_port{};
        std::uint16_t length{};
        std::uint16_t checksum{};
    };

    /**
     * @param buf pointer to the header
     * @param n number of elements in buffer
     * @return encode checksum
     */
    [[nodiscard]] std::uint16_t calculate_checksum(std::uint16_t* buf, int n) noexcept;

    /**
     *
     * @param buffer
     * @param data
     * @param source
     * @param dest
     */
    std::unique_ptr<char[]> build_udp_packet(std::string const& data,
                                             sockaddr_in const& source, sockaddr_in const& dest) noexcept;

    /**
     *
     * @param fd socket
     * @param buffer udp packet
     * @param len size of packet
     * @param dest
     */
    void send_udp_packet(int fd, std::unique_ptr<char[]> buffer, int len, sockaddr_in const& dest) noexcept;
}


#endif //UDP_HPP
