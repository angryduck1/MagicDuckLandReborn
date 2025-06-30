#ifndef LOGICCLIENTAVATAR_H
#define LOGICCLIENTAVATAR_H

#include "PiranhaMessage.h"
#include <vector>

using namespace std;

class LogicClientAvatar : public PiranhaMessage {
public:
    LogicClientAvatar() : PiranhaMessage(0) {
        resources = {3000001, 3000002, 3000003};
        tutor = {21000000, 21000001, 21000002, 21000003, 21000004, 21000005, 21000006, 21000007, 21000008, 21000009, 21000010, 21000011, 21000012, 21000013};
    }

    void encode() override {
        stream.writeLong(LogicLong(1, 1));
        stream.writeLong(LogicLong(1, 1));
        stream.writeBoolean(false);
        stream.writeBoolean(false);
        stream.writeBoolean(false);
        stream.writeInt(0);
        stream.writeInt(0);
        stream.writeInt(0);
        stream.writeInt(0);
        stream.writeInt(0);
        stream.writeString("reborn++"); // Name
        stream.writeString("");
        stream.writeInt(1);
        stream.writeInt(0);
        stream.writeInt(25000); // Diamonds
        stream.writeInt(0);
        stream.writeInt(0);
        stream.writeInt(0);
        stream.writeInt(0);
        stream.writeInt(0);
        stream.writeInt(0);
        stream.writeInt(0);
        stream.writeInt(0);
        stream.writeBoolean(false);
        stream.writeInt(0);

        stream.writeInt(0);
        stream.writeInt(resources.size());

        for (auto i : resources) {
            stream.writeInt(i);
            stream.writeInt(5000);
        }

        stream.writeInt(0);
        stream.writeInt(0);
        stream.writeInt(0);
        stream.writeInt(0);
        stream.writeInt(0);
        stream.writeInt(0);
        stream.writeInt(0);
        stream.writeInt(0);

        stream.writeInt(tutor.size());

        for (auto i : tutor) {
            stream.writeInt(i);
        }

        stream.writeInt(0);
        stream.writeInt(0);
        stream.writeInt(0);
        stream.writeInt(0);
        stream.writeInt(0);
    }

    int getMessageType() const override {
        return 0;
    }


private:
    vector<int> resources;
    vector<int> tutor;
};

#endif // LOGICCLIENTAVATAR_H
