#include "../include/fatum/debug.h"
using namespace fatum;

void Logger::entry(const std::string_view message) {
#ifdef _LOGGER
    std::printf("%s\n", list.emplace_back(message).formatted().c_str());
#endif
}

void Logger::entryCrash(const std::string_view msg){
 /*
#ifdef _LOGGER 
    std::string report{ std::format("CRASH REPORT\nTime: %s [%s] %s%s\n",
         buffer, _source.data(), msg,""
    ) };

   // std::ifstream report{ std::filesystem::current_path().append("/logs/crash/")};

    std::printf("%s    \n%s",report, std::filesystem::current_path().append("/logs/crash/").c_str());
#endif
    */
}
const std::string Logger::Data::formatted() const {
    return std::format("[{:%Y%m%d%H%M}] {}", time, text);
}