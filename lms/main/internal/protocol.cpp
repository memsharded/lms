#include "lms/internal/protocol.h"

namespace lms {
namespace internal {

size_t Datagram::size() const {
    return m_data.size();
}

uint8_t* Datagram::data() {
    return m_data.data();
}

void Datagram::size(size_t size) {
    m_data.reserve(size);
}

template<>
void serializeMessage<LoggingMessage>(LoggingMessage const& message, Datagram & datagram) {
    constexpr std::uint8_t MAX_LEN = std::numeric_limits<std::uint8_t>::max();

    std::string text = message.text;
    std::string tag = message.tag;

    uint8_t tagLen = std::min(size_t(MAX_LEN), tag.size());
    uint8_t textLen = std::min(size_t(MAX_LEN), text.size());

    // Format: Level + Tag Size + Tag + Message Size + Message
    uint32_t len = 3 + tagLen + textLen;

    internal::DebugServer::Datagram datagram(internal::ServerMessageType::LOGGING, len);

    datagram.data()[0] = static_cast<std::uint8_t>(message.level);
    datagram.data()[1] = tagLen;
    datagram.data()[2] = textLen;
    std::copy(tag.begin(), tag.begin() + tagLen, &datagram.data()[3]);
    std::copy(text.begin(), text.begin() + textLen, &datagram.data()[3 + tagLen]);
}

}  // namespace internal
}  // namespace lms
