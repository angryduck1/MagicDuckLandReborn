#ifndef LOGICCOMMAND_H
#define LOGICCOMMAND_H

#include "ByteStream.h"

class LogicCommand {
public:
    LogicCommand() {
        ExecuteSubTick = -1;
    }

    virtual void encode(ByteStream& stream) {
        stream.writeInt(ExecuteSubTick);
    }

    virtual void decode(ByteStream& stream) {
        ExecuteSubTick = stream.readInt();
    }

    virtual int getCommandType() {
        return 0;
    }

    void setExecuteSubTick(int executeSubTick) {
        ExecuteSubTick = executeSubTick;
    }

    int getExecuteSubTick(int executeSubTick) {
        return ExecuteSubTick;
    }

    void destruct() {
        ExecuteSubTick = -1;
    }

private:
    int ExecuteSubTick;
};

#endif // LOGICCOMMAND_H
