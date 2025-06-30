#ifndef CHECKSUMENCODER_H
#define CHECKSUMENCODER_H

#include <cstdint>
#include <cstddef>
#include <string>
#include <vector>
#include "LogicLong.h"

class ChecksumEncoder {
protected:
    uint32_t checksum = 0;
    uint32_t snapshotChecksum = 0;
    bool enabled = true;
public:
    virtual ~ChecksumEncoder() = default;
    ChecksumEncoder() = default;

    void enableCheckSum(bool enable) {
        if (!enabled || enable) {
            if (!enabled && enable) {
                checksum = snapshotChecksum;
                enabled = enable;
            }
        } else {
            snapshotChecksum = checksum;
            enabled = false;
        }
    }

    uint32_t getCheckSum() const {
        return checksum;
    }

    virtual bool isCheckSumOnlyMode() const {
        return false;
    }

    void resetCheckSum() {
        checksum = 0;
    }

    static uint32_t rotateRight(uint32_t value, int count) {
        return (value >> count) | (value << (32 - count));
    }


    virtual void writeBoolean(bool value) {
        if (value) {
            checksum += 13;
        } else {
            checksum += 7;
        }
        checksum += rotateRight(checksum, 31);
    }

    virtual void writeByte(uint8_t value) {
        checksum = value + rotateRight(checksum, 31) + 11;
    }

    virtual void writeBytes(const std::vector<uint8_t>& data, size_t length) {
        checksum = (length + 28) + rotateRight(checksum, 31);
    }

    virtual void writeInt(int32_t value) {
        checksum = value + rotateRight(checksum, 31) + 9;
    }

    virtual void writeShort(int16_t value) {
        checksum = value + rotateRight(checksum, 31) + 19;
    }

    virtual void writeString(const std::string& value) {
        checksum = (value.size() + 28) + rotateRight(checksum, 31);
    }

    virtual void writeStringReference(const std::string& value) {
        checksum = (value.size() + 38) + rotateRight(checksum, 31);
    }

    virtual void writeLong(const LogicLong& value) {
        writeInt(value.highInteger);
        writeInt(value.lowInteger);
    }
};

#endif // CHECKSUMENCODER_H
