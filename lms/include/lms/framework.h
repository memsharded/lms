#ifndef LMS_FRAMEWORK_H
#define LMS_FRAMEWORK_H

#include <lms/datamanager.h>
#include <lms/signalhandler.h>
#include <lms/argumenthandler.h>
#include <lms/executionmanager.h>
#include <lms/logger.h>
#include "lms/clock.h"
#include "pugixml.hpp"
#include "lms/extra/file_monitor.h"

/**
 *TODO: Framework config that contains max threads for executionManager etc.
 */
namespace lms {

/**
 * @brief Main entry point into the lightweight module system.
 *
 * Create an object of this class and you will start the framwork.
 */
class Framework : public SignalHandler::Listener {
public:
    /**
     * @brief executionPath absolute path to running framework (folder that contains core and external)
     */
    static std::string programDirectory();

    /**
     * @brief Framework::externalDirectory absolute path to the external directory
     */
    static std::string externalDirectory;
    /**
     * @brief Framework::configsDirectory absolute path to the configs directory
     */
    static std::string configsDirectory;

    /**
     * @brief Instantiate the framework, initiate datamanager and
     * execution manager and start the main loop.
     *
     * @param arguments parsed command line arguments
     */
    Framework(const ArgumentHandler& arguments);

    /**
     * @brief Destroy execution manager.
     */
    ~Framework();

    struct ModuleToLoad {
        std::string name;
        logging::LogLevel logLevel;
    };

    enum class LoadConfigFlag {
        LOAD_EVERYTHING,
        ONLY_MODULE_CONFIG
    };

private:

    logging::RootLogger rootLogger;
    logging::ChildLogger logger;

    ArgumentHandler argumentHandler;
    ExecutionManager executionManager;

    bool clockEnabled;
    Clock clock;

    /**
     * @brief running just for main-while-loop if it's set to false, the programm will terminate
     */
    bool running;

    std::vector<ModuleToLoad> tempModulesToLoadList;

    extra::FileMonitor monitor;
    bool monitorEnabled;

    /**
     * @brief signal called by the system (Segfaults etc)
     * @param s
     */
    void signal(int s);
    /**
     * @brief parseConfig parses the framework-config
     */
    void parseConfig(LoadConfigFlag flag);
    void parseFile(const std::string &file, LoadConfigFlag flag);
    void parseExecution(pugi::xml_node rootNode);
    void parseModulesToEnable(pugi::xml_node rootNode);
    void parseModules(pugi::xml_node rootNode, const std::string &currentFile,
                      LoadConfigFlag flag);
    void parseModuleConfig(pugi::xml_node node, const std::string &key,
                                      type::ModuleConfig &config);
    void parseIncludes(pugi::xml_node rootNode, const std::string &currentFile,
                       LoadConfigFlag flag);

    /**
     * @brief Pause the framework execution if 'p' was pressed on stdin.
     * The framework will then pause until 'r' was pressed.
     */
    void pauseIfRequested();
};

}  // namespace lms

#endif /* LMS_FRAMEWORK_H */
