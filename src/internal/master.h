#pragma once

#include <string>
#include <vector>
#include <memory>

#include "protobuf_socket.h"
#include "messages.pb.h"

namespace lms {
namespace internal {

class MasterServer {
public:
    MasterServer();
    int useUnix(const std::string &path);
    int useIPv4(int port);
    void start();

private:
    struct Client {
        Client(int fd, const std::string &peer);
        ProtobufSocket sock;
        std::string peer;
        bool isAttached;
        pid_t attachedRuntime;
    };

    struct Server {
        Server(int fd);
        int fd;
    };

    struct Runtime {
        pid_t pid;
        ProtobufSocket sock;
        std::string config_file;
    };

    std::vector<Server> m_servers;
    std::vector<Client> m_clients;
    std::vector<Runtime> m_runtimes;
    bool m_running;

    enum class ClientResult { exit, attached };

    void enableNonBlock(int sock);
    ClientResult processClient(Client &client, const lms::Request &message);
    void runFramework(Client &client, const Request_Run &options);
};

class MasterClient {
public:
    static MasterClient fromUnix(const std::string &path);
    ~MasterClient();
    int fd() const;

private:
    int m_sockfd;
    MasterClient(int fd);
};

void connectToMaster(int argc, char *argv[]);
}
}