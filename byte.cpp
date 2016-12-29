#include "byte.h"

#include <sstream>
#include <iomanip>

std::string ToString(const Bytes& bytes) {
    std::stringstream ss;
    for (auto it = bytes.begin(); it != bytes.end(); ++it)
        ss << std::setfill('0') << std::setw(2) << std::hex << static_cast<unsigned int>(*it) << ' ';
    return ss.str();
}
