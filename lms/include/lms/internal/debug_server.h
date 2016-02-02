#ifndef LMS_INTERNAL_DEBUG_SERVER_H
#define LMS_INTERNAL_DEBUG_SERVER_H

#include <string>
#include <vector>
#include <memory>
#include <thread>
#include <queue>

#include "lms/logger.h"
#include "protocol.h"

namespace lms {
namespace internal {

class DebugServer {
public:
    DebugServer();
    ~DebugServer();

    bool useUnix(std::string const& path);

    bool useIPv4(uint16_t port);

    bool useIPv6(uint16_t port);

    bool useDualstack(uint16_t port);

    void startThread();

    void broadcast(Datagram const& datagram);
private:
    void enableReuseAddr(int sock);

    void enableIPv6Only(int sock);

    void startListening(int sock);

    void enableNonBlock(int sock);

    struct Client {
        Client() : valid(false), buffer(4096),
                   bufferUsed(0), sendMask(0), outOffset(0) {}

        int sockfd;
        bool valid;
        std::vector<std::uint8_t> buffer;
        size_t bufferUsed;

        uint8_t sendMask;
        std::queue<Datagram> outBuffer;
        size_t outOffset;

        bool enabledSend(ServerMessageType type);
    };

    logging::Logger logger;

    std::vector<int> m_server;
    fd_set m_readRfds;
    fd_set m_writeRfds;
    std::vector<Client> m_clients;
    std::thread m_thread;
    bool m_shutdown;

    std::mutex m_outMutex;

    void processWrites();
    void processReads();
    void processServer(int sockfd);
    void processClient(Client & client);
    void processOutqueue(Client &client);

    static constexpr size_t HEADER_SIZE = 5;
};

}  // namespace internal
}  // namespace lms

#endif // LMS_INTERNAL_DEBUG_SERVER_H
