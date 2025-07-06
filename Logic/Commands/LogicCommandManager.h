#ifndef LOGICCOMMANDMANAGER_H
#define LOGICCOMMANDMANAGER_H

#include "ByteStream.h"
#include "LogicCommand.h"
#include "LogicBuyBuildingCommand.h"
#include <iostream>
#include <memory>

using namespace std;

class LogicCommandManager {
public:
    void decodeCommand(ByteStream& stream) {
    commandType = stream.readInt();

    shared_ptr<LogicCommand> command = createCommand();

    if (command != nullptr) {
        command->decode(stream);
    }
    }

    shared_ptr<LogicCommand> createCommand() {
        switch (commandType) {
        case 500: {
            std::cout << "[LogicCommandManager] new command " << commandType << std::endl;
            return make_shared<LogicBuyBuildingCommand>(LogicBuyBuildingCommand());
            break;
        }
        default:
            return nullptr;
        }
    }
private:
    int commandType;
};

#endif // LOGICCOMMANDMANAGER_H
