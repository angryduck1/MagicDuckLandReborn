#ifndef LOGICLONG_H
#define LOGICLONG_H

#include <cstdint>
#include <string>

class ByteStream;

class LogicLong {
public:
    int32_t highInteger = 0;
    int32_t lowInteger = 0;

    LogicLong() = default;
    LogicLong(int32_t high, int32_t low) : highInteger(high), lowInteger(low) {}

    void decode(ByteStream& stream);
    void encode(ByteStream& stream) const;

    std::string toString() const {
        return std::to_string(highInteger) + "-" + std::to_string(lowInteger);
    }
};


#endif // LOGICLONG_H
