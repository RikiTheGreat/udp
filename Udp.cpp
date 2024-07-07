//
// Created by mahdi on 7/7/24.
//

#include "Udp.hpp"


std::uint16_t udp::calculate_checksum(std::uint16_t* buf, int n) noexcept
{
    std::uint64_t sum{};

    for (; n > 0; --n)
        sum += *buf++;

    sum = (sum >> 16) + (sum & 0xFFF);
    sum += (sum >> 16);
    return (~sum);
}

std::unique_ptr<char[]> udp::build_udp_packet(std::string const& data, sockaddr_in const& source,
                                              sockaddr_in const& dest) noexcept
{
    auto iph = std::make_unique<IPHeader>();
    auto udph = std::make_unique<UDPHeader>();

    iph->internet_header_length = 5;
    iph->version = 4;
    iph->type_of_service = 0;
    iph->total_ip_lengh = htons(sizeof(IPHeader) + sizeof(UDPHeader));
    iph->id = htonl(54321);
    iph->offset = 0;
    iph->protocol = IPPROTO_UDP;
    iph->ttl = 255;
    iph->src = source.sin_addr;
    iph->dest = dest.sin_addr;
    iph->checksum = 0;

    udph->checksum = 0;
    udph->src_port = source.sin_port;
    udph->dest_port = dest.sin_port;
    udph->length = htons(sizeof(UDPHeader) + data.size());

    // build data
    auto buffer = std::make_unique<char[]>(4096);

    std::memcpy(buffer.get(), iph.get(), sizeof(IPHeader));
    std::memcpy(buffer.get() + sizeof(IPHeader), udph.get(), sizeof(UDPHeader));
    std::memcpy(buffer.get() + sizeof(IPHeader) + sizeof(UDPHeader), data.c_str(), data.size());

    return buffer;
}

void udp::send_udp_packet(int fd, std::unique_ptr<char[]> buffer, int len, sockaddr_in const& dest) noexcept
{
    if (sendto(fd, buffer.get(), len, 0, reinterpret_cast<sockaddr const*>(&dest), sizeof(dest)) < 0)
    {
        perror("sendto failed");
        exit(EXIT_FAILURE);
    }
}
