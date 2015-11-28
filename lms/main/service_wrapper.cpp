#include "lms/service_wrapper.h"

namespace lms {

std::string ServiceWrapper::name() const {
    return m_name;
}

void ServiceWrapper::name(std::string const& name) {
    m_name = name;
}

ModuleConfig& ServiceWrapper::getConfig(std::string const& name) {
    return m_configs[name];
}

Runtime* ServiceWrapper::runtime() {
    return m_runtime;
}

Service* ServiceWrapper::instance() {
    return m_service.get();
}

std::mutex& ServiceWrapper::mutex() {
    return m_mutex;
}

bool ServiceWrapper::checkHashCode(size_t hashCode) {
    return m_service && (m_service->hashCode() == hashCode);
}

}  // namespace lms
