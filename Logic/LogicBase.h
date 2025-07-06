#ifndef LOGICBASE_H
#define LOGICBASE_H

#include "ChecksumEncoder.h"

class LogicBase {
public:
    virtual void encode(ChecksumEncoder& encoder) {
        encoder.writeInt(0);
    }
};

#endif // LOGICBASE_H
