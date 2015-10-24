#include <lms/loader.h>
#include <lms/module.h>

namespace lms {

std::string Loader::getModulePath(const std::string &libname) {
    return libname + ".dll";
}

bool Loader::checkSharedLibrary(const std::string &libpath) {
	logger.error("checkSharedLibrary") << "Not implemented on Win32";
	return false;
}

void Loader::load(ModuleWrapper *entry) {
    logger.error("load") << "Not implemented on Win32";
}

void Loader::unload(ModuleWrapper *entry) {
    logger.error("unload") << "Not implemented on Win32";
}

}  // namespace lms
