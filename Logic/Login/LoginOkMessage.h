#ifndef LOGINOKMESSAGE_H
#define LOGINOKMESSAGE_H

#include <string>
#include "PiranhaMessage.h"
#include "LogicLong.h"

using namespace std;

class LoginOkMessage : public PiranhaMessage {
public:
    LoginOkMessage() : PiranhaMessage(0) {}

    void encode() override {
        stream.writeLong(LogicLong(1, 1));
        stream.writeLong(LogicLong(1, 1));
        stream.writeString("PassToken");
        stream.writeString("FacebookAppId");
        stream.writeString("GamecenterId");
        stream.writeInt(5);
        stream.writeInt(2);
        stream.writeInt(4);
        stream.writeString("dev");
        stream.writeInt(1);
        stream.writeInt(1);
        stream.writeInt(0);
        stream.writeString("FacebookAppId");
        stream.writeString("ServerTime");
        stream.writeString("AccountCreatedDate");
        stream.writeInt(0);
        stream.writeString("GoogleServiceId");
    }

    int getMessageType() const override {
        return 20104;
    }
};

#endif
