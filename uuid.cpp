#include "./uuid.h"

/*
#include <sstream>

class UuidImpl {
 public:
    virtual std::string ToString() const = 0;
    virtual bool IsShort() const = 0;
};

class ShortUuid
    : public UuidImpl {
 private:
    std::string ToString() const {
        std::stringstream result;
        result << std::setfill(L'0') << std::setw(4) << std::hex << value_;
        return result.str();
    }

    bool std::IsShort() const {
        return true;
    }

    std::uint16_t value_ = 0;
}

class LongUuid
   : public UuidImpl {
 private:
    std::string ToString() const {
        boost::lexical_cast<std::string>(value_);
    }

    bool std::IsShort() const {
        return false;
    }

    boost::uuids::uuid value_;
}

*/