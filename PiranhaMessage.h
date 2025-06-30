#ifndef PIRANHAMESSAGE_H
#define PIRANHAMESSAGE_H

#include "ByteStream.h"

class PiranhaMessage {
protected:
    ByteStream stream;
    int messageVersion;
public:
    explicit PiranhaMessage(int messageVersion)  {
        stream = ByteStream(10);
        this->messageVersion = messageVersion;
    }
    virtual ~PiranhaMessage();

    virtual void encode();

    virtual void decode();

    int isClientToServerMessage() {
        return (getMessageType() - 10000) < 10000;
    }

    int isServerToClientMessage() {
        return (getMessageType() - 20000) < 10000;
    }

    std::vector<uint8_t> getMessageBytes() const {
        return stream.getByteArray();
    }

    ByteStream& getByteStream() {
        return stream;
    }

    size_t getEncodingLength() const {
        return stream.getLength();
    }

    virtual int getMessageType() const = 0;

    int getMessageVersion() const {
        return messageVersion;
    }

    void setMessageVersion(int version) {
        messageVersion = version;
    }

    void destruct() {
        stream.destruct();
    }

    void clear(size_t capacity) {
        stream.clear(capacity);
    }

};

#endif // PIRANHAMESSAGE_H
