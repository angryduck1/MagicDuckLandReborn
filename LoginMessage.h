#ifndef LOGINMESSAGE_H
#define LOGINMESSAGE_H

#include <string>
#include "PiranhaMessage.h"
#include "LogicLong.h"

using namespace std;

class LoginMessage : public PiranhaMessage {
public:
    LogicLong AccountID;
    int ClientMajorVersion;
    int ClientBuild;
    string passToken;
    string resourceSha;

    LoginMessage() : PiranhaMessage(0) {
        AccountID = LogicLong();
        passToken = "";
        ClientMajorVersion = -1;
        ClientBuild = -1;
        resourceSha = "";
    }

    int getClientMajorVersion() {
        return ClientMajorVersion;
    }

    int getClientBuild() {
        return ClientBuild;
    }

    void encode() override {

    }

    void decode() override {
        PiranhaMessage::decode();
        AccountID = stream.readLong();
        passToken = stream.readString();
        ClientMajorVersion = stream.readInt();
        stream.readInt();
        ClientBuild = stream.readInt();
        resourceSha = stream.readString();
    }

    int getMessageType() const override {
        return 10101;
    }
};

#endif
