#ifndef StringUtils_h
#define StringUtils_h

#include <stdio.h>
#include <string.h>

namespace CCMessageWindow {
    class Utils {
    public:
        static std::string substringUTF8(const char* str, int from, int length);
    };
}

#endif /* StringUtils_hpp */
