#include <string>

#include "lms/internal/module_wrapper.h"
#include <lms/module.h>
#include <lms/lms_exports.h>
#include "lms/internal/datamanager.h"
#include "lms/config.h"
#include "lms/internal/runtime.h"
#include "lms/internal/executionmanager.h"
#include "lms/internal/framework.h"

namespace lms{
    bool Module::initializeBase(std::shared_ptr<internal::ModuleWrapper> wrapper,
        logging::Level minLogLevel) {

        m_datamanager = &wrapper->runtime()->dataManager();
        m_executionManager = &wrapper->runtime()->executionManager();
        m_messaging = &m_executionManager->messaging();
        m_wrapper = wrapper;

        logger.name = wrapper->runtime()->name() + "." + wrapper->name();
        logger.threshold = minLogLevel;

        return true;
    }

    lms_EXPORT std::string Module::getName() const{
        return m_wrapper->name();
    }

    lms_EXPORT ExecutionType Module::getExecutionType() const {
        return m_wrapper->executionType;
    }

    lms_EXPORT std::string Module::getChannelMapping(const std::string &mapFrom) const{
        return m_wrapper->getChannelMapping(mapFrom);
    }

    lms_EXPORT int Module::getChannelPriority(const std::string &name) const {
        return m_wrapper->getChannelPriority(getChannelMapping(name));
    }

    lms_EXPORT const Config* Module::getConfig(const std::string &name){
        return &config(name);
    }

    lms_EXPORT const Config& Module::config(const std::string &name){
        return m_wrapper->configs[name];
    }

    lms_EXPORT bool Module::hasConfig(const std::string &name){
        return m_wrapper->configs.find(name) != m_wrapper->configs.end();
    }

    int Module::cycleCounter() {
        return m_executionManager->cycleCounter();
    }

    bool Module::pauseRuntime(std::string const& name) {
        if(! m_wrapper->runtime()->framework().hasRuntime(name)) {
            return false;
        }

        m_wrapper->runtime()->framework().getRuntimeByName(name)->pause();
        return true;
    }

    void Module::pauseRuntime() {
        return m_wrapper->runtime()->pause();
    }

    bool Module::resumeRuntime(std::string const& name, bool reset) {
        if(! m_wrapper->runtime()->framework().hasRuntime(name)) {
            return false;
        }

        m_wrapper->runtime()->framework().getRuntimeByName(name)->resume(reset);
        return true;
    }

    bool Module::isEnableSave() const {
        return m_wrapper->runtime()->framework().isEnableSave();
    }

    bool Module::isEnableLoad() const {
        return m_wrapper->runtime()->framework().isEnableLoad();
    }

    std::string Module::saveLogFile(std::string const& name) {
        return m_wrapper->runtime()->framework().saveLogObject(name, false);
    }

    std::string Module::loadLogFile(std::string const& name) {
        return m_wrapper->runtime()->framework().loadLogObject(name, false);
    }

    std::string Module::saveLogDir(std::string const& name) {
        return m_wrapper->runtime()->framework().saveLogObject(name, true);
    }

    std::string Module::loadLogDir(std::string const& name) {
        return m_wrapper->runtime()->framework().loadLogObject(name, true);
    }
}
