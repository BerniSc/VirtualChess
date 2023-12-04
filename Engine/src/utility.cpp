#include "utility.hpp"

std::vector<std::string> split(const std::string string, const std::string regexString) {
    std::regex regex(regexString);
    return {
        std::sregex_token_iterator(string.begin(), string.end(), regex, -1),
        std::sregex_token_iterator()
    };
}