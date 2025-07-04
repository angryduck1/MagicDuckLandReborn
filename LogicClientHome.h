#ifndef LOGICCLIENTHOME_H
#define LOGICCLIENTHOME_H

#include <string>
#include "LogicBase.h"
#include "LogicLong.h"
#include "ChecksumEncoder.h"

class LogicClientHome : public LogicBase {
public:
    LogicClientHome() = default;

    void encode(ChecksumEncoder& encoder) override {
        LogicBase::encode(encoder);

        const std::string homeJson = R"({"buildings":[{"data":1000001,"lvl":0,"x":21,"y":20},{"data":1000004,"lvl":0,"x":20,"y":16,"res_time":8992},{"data":1000000,"lvl":0,"x":26,"y":19,"units":[],"storage_type":0},{"data":1000015,"lvl":0,"x":18,"y":20},{"data":1000014,"lvl":0,"locked":true,"x":25,"y":32}],"obstacles":[{"data":8000007,"x":5,"y":13},{"data":8000007,"x":15,"y":29},{"data":8000008,"x":7,"y":7},{"data":8000005,"x":29,"y":4},{"data":8000006,"x":15,"y":37},{"data":8000000,"x":20,"y":4},{"data":8000008,"x":15,"y":22},{"data":8000005,"x":37,"y":18},{"data":8000007,"x":6,"y":4},{"data":8000003,"x":26,"y":10},{"data":8000004,"x":21,"y":9},{"data":8000008,"x":32,"y":21},{"data":8000005,"x":20,"y":36},{"data":8000003,"x":29,"y":34},{"data":8000005,"x":5,"y":29},{"data":8000005,"x":8,"y":10},{"data":8000005,"x":5,"y":17},{"data":8000002,"x":4,"y":33},{"data":8000002,"x":5,"y":21},{"data":8000002,"x":10,"y":32},{"data":8000008,"x":5,"y":37},{"data":8000001,"x":9,"y":4},{"data":8000001,"x":13,"y":31},{"data":8000001,"x":7,"y":35},{"data":8000007,"x":4,"y":9},{"data":8000004,"x":9,"y":23},{"data":8000004,"x":6,"y":26},{"data":8000003,"x":35,"y":21},{"data":8000005,"x":32,"y":28},{"data":8000005,"x":34,"y":13},{"data":8000001,"x":14,"y":18},{"data":8000001,"x":35,"y":5},{"data":8000012,"x":24,"y":30},{"data":8000012,"x":31,"y":10},{"data":8000010,"x":26,"y":38},{"data":8000010,"x":14,"y":5},{"data":8000013,"x":34,"y":33},{"data":8000013,"x":13,"y":9},{"data":8000014,"x":10,"y":17},{"data":8000014,"x":24,"y":7},{"data":8000006,"x":36,"y":26},{"data":8000011,"x":23,"y":34},{"data":8000011,"x":24,"y":37},{"data":8000000,"x":27,"y":35},{"data":8000000,"x":25,"y":35},{"data":8000000,"x":26,"y":30},{"data":8000007,"x":23,"y":32},{"data":8000001,"x":28,"y":31},{"data":8000014,"x":28,"y":29}],"traps":[],"decos":[],"respawnVars":{"secondsFromLastRespawn":0,"respawnSeed":1529463799,"obstacleClearCounter":0},"cooldowns":[]})";

        encoder.writeLong(LogicLong(1, 1)); // Id
        encoder.writeString(homeJson);      // Home JSON
        encoder.writeInt(0);                 // ShieldDurationSeconds
        encoder.writeInt(0);                 // DefenseRating
        encoder.writeInt(0);                 // DefenseKFactor
    }

    int getMessageType() {
        return 0;
    }
};

#endif // LOGICCLIENTHOME_H
