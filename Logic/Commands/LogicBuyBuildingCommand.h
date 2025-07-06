#ifndef LOGICBUYBUILDINGCOMMAND_H
#define LOGICBUYBUILDINGCOMMAND_H

#include "LogicCommand.h"
#include "iostream"

class LogicBuyBuildingCommand : public LogicCommand  {
public:
    void decode(ByteStream& stream) override {
        x = stream.readInt();
        y = stream.readInt();

        std::cout << "X: " << x << std::endl;
        std::cout << "Y: " << y << std::endl;

    }
    int getCommandType() override {
        return 500;
    }
private:
    int x;
    int y;
};

#endif // LOGICBUYBUILDINGCOMMAND_H
