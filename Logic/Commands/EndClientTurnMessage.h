#ifndef ENDCLIENTTURNMESSAGE_H
#define ENDCLIENTTURNMESSAGE_H

#include "PiranhaMessage.h"
#include "LogicCommandManager.h"
#include "iostream"

class EndClientTurnMessage : public PiranhaMessage {
public:
    EndClientTurnMessage() : PiranhaMessage(0) {
        commandCount = 0;
        subTick = 0;
        checksum = 0;
        commandManager = LogicCommandManager();
    }

    void encode() override {

    }

    void decode() override {
        PiranhaMessage::decode();

        subTick = stream.readInt();
        checksum = stream.readInt();

        commandCount = stream.readInt();

        std::cout << commandCount << std::endl;

        if (commandCount <= 512) {
            if (commandCount > 0) {
                for (int i = 0; i < commandCount; i++) {
                    commandManager.decodeCommand(stream);
                }
            }
        } else {
            std::cerr << "EndClientTurnMessage command count is too high! " << commandCount << std::endl;
        }
    }

    int getMessageType() const override {
        return 14102;
    }
private:
    int commandCount; // this + 12
    int subTick; // this + 13
    int checksum; // this + 14
    LogicCommandManager commandManager;
};

#endif // ENDCLIENTTURNMESSAGE_H
