#include "Utils.h"
#include "cocos2d.h"

namespace CCMessageWindow {
    
    std::string Utils::substringUTF8(const char* str, int from, int length)
    {
        std::u16string utf16String;
        cocos2d::StringUtils::UTF8ToUTF16(str, utf16String);
        auto splitted = cocos2d::StringUtils::getChar16VectorFromUTF16String(utf16String);
        
        size_t dataSize = length + 1;
        char16_t *array = static_cast<char16_t *>(malloc(sizeof(char16_t) * dataSize));
        for (int idx = 0; idx < length; ++idx) {
            *(array + sizeof(char16_t) * idx) = splitted[from + idx];
        }
        *(array + length) = '\0';
        
        std::string outUTF8String;
        std::u16string u16String(array);
        
        cocos2d::StringUtils::UTF16ToUTF8(u16String, outUTF8String);
        free(array);
        return std::move(outUTF8String);
    }
    
}