//TODO remove unused imports
#include <limits.h>
#include <cstring>
#include <core/framework.h>
#include <unistd.h>
#include <sys/stat.h>
#include <algorithm>
#include <string>
#include <Windows.h>

#include <core/loader.h>
#include <core/module.h>
#include <core/logger.h>
namespace lms{
template<typename _Target>
union converter {
    void* src;
    _Target target;
};
std::string Framework::programDirectory(){
    static std::string directory;

    if(directory.empty()) {
        HMODULE hModule = GetModuleHandleW(NULL);
        WCHAR path[MAX_PATH];
        GetModuleFileNameW(hModule, path, MAX_PATH);
        //wide char array

        //convert from wide char to narrow char array
        char ch[260];
        char DefChar = ' ';
        WideCharToMultiByte(CP_ACP,0,path,-1, ch,260,&DefChar, NULL);

        //A std:string  using the char* constructor.
        std::string ss(ch);
        directory = ss;
        //get programmdirectory
        // TODO optimize this a bit
    /*
        directory = path;
        directory = directory.substr(0, directory.rfind("/"));
        directory = directory.substr(0, directory.rfind("/"));
        */
     }

    std::cout << "ProgramDirectory: " << directory << std::endl;

     //return directory; // TODO did not work with this line
    return "";
}
}
