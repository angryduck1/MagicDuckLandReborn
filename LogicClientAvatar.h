#ifndef LOGICCLIENTAVATAR_H
#define LOGICCLIENTAVATAR_H

#include <vector>
#include <iostream>
#include "LogicBase.h"
#include "LogicLong.h"
#include "ChecksumEncoder.h"

class LogicClientAvatar : public LogicBase {
public:
    LogicClientAvatar() {
        resources = {3000001, 3000002, 3000003};
        for (int i = 21000000; i < 21000013; ++i) {
            tutorialSteps.push_back(i);
        }
    }

    void encode(ChecksumEncoder& encoder) override {
        LogicBase::encode(encoder);

        encoder.writeLong(LogicLong(1, 1));
        encoder.writeLong(LogicLong(1, 1));
        encoder.writeBoolean(false);
        encoder.writeBoolean(false);
        encoder.writeBoolean(false);
        encoder.writeInt(0);
        encoder.writeInt(0);
        encoder.writeInt(0);
        encoder.writeInt(0);
        encoder.writeInt(0);
        encoder.writeString("reborn++"); // Name
        encoder.writeString("");
        encoder.writeInt(1);
        encoder.writeInt(0);
        encoder.writeInt(25000);
        encoder.writeInt(0);
        encoder.writeInt(0);
        encoder.writeInt(0);
        encoder.writeInt(0);
        encoder.writeInt(0);
        encoder.writeInt(0);
        encoder.writeInt(0);
        encoder.writeInt(0);
        encoder.writeBoolean(false);
        encoder.writeInt(0);

        encoder.writeInt(0);
        encoder.writeInt(static_cast<int>(resources.size()));
        for (int item : resources) {
            encoder.writeInt(item);
            encoder.writeInt(5000);
        }

        encoder.writeInt(0);
        encoder.writeInt(0);
        encoder.writeInt(0);
        encoder.writeInt(0);
        encoder.writeInt(0);
        encoder.writeInt(0);
        encoder.writeInt(0);
        encoder.writeInt(0);

        encoder.writeInt(static_cast<int>(tutorialSteps.size()));
        for (int step : tutorialSteps) {
            encoder.writeInt(step);
        }

        encoder.writeInt(0);
        encoder.writeInt(0);
        encoder.writeInt(0);
        encoder.writeInt(0);
        encoder.writeInt(0);
    }

private:
    std::vector<int> resources;
    std::vector<int> tutorialSteps;
};

#endif // LOGICCLIENTAVATAR_H
