#include "LogicLong.h"
#include "ByteStream.h"

void LogicLong::decode(ByteStream& stream) {
    highInteger = stream.readInt();
    lowInteger = stream.readInt();
}

void LogicLong::encode(ByteStream& stream) const {
    stream.writeInt(highInteger);
    stream.writeInt(lowInteger);
}
