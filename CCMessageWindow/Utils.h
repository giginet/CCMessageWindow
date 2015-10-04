#ifndef StringUtils_h
#define StringUtils_h

#include <stdio.h>
#include <string.h>

namespace CCMessageWindow {
    class Utils {
    public:
        static std::string substringUTF8(const char* str, int from, int length);
        static std::vector<std::string> split(const std::string& input, char delimiter);
        static std::string replace(std::string base, std::string src, std::string dst);
    };
}

#endif /* StringUtils_hpp */
