#ifndef HEADER_H
#define HEADER_H

#include <cstdint>

struct Header {
    int messageType;
    int encodingLength;
    int messageVersion;
};

#endif
