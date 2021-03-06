#ifndef LMS_SERVICE_HANDLE_H
#define LMS_SERVICE_HANDLE_H

#include <memory>
#include <mutex>

#include "lms/service.h"
#include "internal/service_wrapper.h"

namespace lms {

template<class T>
class ServiceHandle {
public:
    ServiceHandle(std::shared_ptr<internal::ServiceWrapper> wrapper) :
        m_wrapper(wrapper), m_lock(wrapper->mutex()), m_valid(true) {
    }

    ServiceHandle() : m_valid(false) {}

    T* operator -> () {
        return static_cast<T*>(m_wrapper->instance());
    }

    operator bool() const {
        return m_valid;
    }

    bool isValid() const {
        return m_valid;
    }
private:
    std::shared_ptr<internal::ServiceWrapper> m_wrapper;
    std::unique_lock<std::mutex> m_lock;
    bool m_valid;
};

}  // namespace lms

#endif // LMS_SERVICE_HANDLE_H
