#ifndef LMS_INTERNAL_PROTOCOL_H
#define LMS_INTERNAL_PROTOCOL_H

#include "lms/logger.h"

namespace lms {
namespace internal {

enum class ServerMessageType : std::uint8_t {
    LOGGING = 0, PROFILING = 1
};

enum class ClientMessageType : std::uint8_t {
    SET_SEND_MASK = 0, COMMAND = 1
};

class Datagram {
public:
    uint8_t* data();
    size_t size() const;
    void size(size_t size);
private:
    std::vector<uint8_t> m_data;
};

struct

struct Header {
    uint32_t len;
    uint8_t type;
};

/**
 * @brief Logging message with log level
 */
struct LoggingMessage {
    logging::Level logLevel;
    std::string tag;
    std::string text;
};

struct ProfilingMessage {
    Header header;
    uint8_t flag;
    int64_t timestamp;
    uint8_t labelLen;
};

struct SendMaskMessage {
    Header header;
    uint8_t mask;
};

template<typename T>
void serializeMessage(T const& message, Datagram & datagram);
template<>
void serializeMessage<LoggingMessage>(LoggingMessage const& message, Datagram & datagram);

}  // namespace internal
}  // namespace lms

#endif // LMS_INTERNAL_PROTOCOL_H
