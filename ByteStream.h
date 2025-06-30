#ifndef BYTESTREAM_H
#define BYTESTREAM_H

#include <vector>
#include <string>
#include <cstdint>
#include <stdexcept>
#include <algorithm>
#include "ChecksumEncoder.h"
#include "LogicLong.h"
#include <iostream>

class ByteStream : public ChecksumEncoder {
private:
    std::vector<uint8_t> buffer;
    size_t offset = 0;
    size_t length = 0;
    int bitIndex = 0;

    void ensureCapacity(size_t capacity) {
        if (offset + capacity > buffer.size()) {
            buffer.resize(buffer.size() + capacity + 100);
        }
    }

public:
    explicit ByteStream(size_t capacity = 1024) {
        buffer.resize(capacity);
        offset = 0;
        length = 0;
        bitIndex = 0;
    }

    void destruct() {
        offset = 0;
        length = 0;
        bitIndex = 0;
        buffer.clear();
    }

    const std::vector<uint8_t>& getByteArray() const {
        return buffer;
    }

    size_t getCapacityIncrement() const {
        return 100;
    }

    uint8_t getDataPointer() const {
        if (offset >= buffer.size()) throw std::out_of_range("getDataPointer out of range");
        return buffer[offset];
    }

    size_t getLength() const {
        return (offset < length) ? length : offset;
    }

    size_t getOffset() const {
        return offset;
    }

    bool isAtEnd() const {
        return offset >= length;
    }

    bool isCheckSumOnlyMode() const override {
        return false;
    }

    bool readBoolean() {
        if (bitIndex == 0) {
            ++offset;
        }
        if (offset == 0) throw std::out_of_range("readBoolean offset underflow");
        bool value = (buffer[offset - 1] & (1 << bitIndex)) != 0;
        bitIndex = (bitIndex + 1) & 7;
        return value;
    }

    uint8_t readByte() {
        bitIndex = 0;
        if (offset >= buffer.size()) throw std::out_of_range("readByte out of range");
        return buffer[offset++];
    }

    std::vector<uint8_t> readBytes(int length, int maxCapacity) {
        bitIndex = 0;
        if (length < 0) {
            if (length != -1) {
                throw std::runtime_error("Negative readBytes length encountered.");
            }
            return {};
        }
        if (length <= maxCapacity) {
            if (offset + length > buffer.size()) throw std::out_of_range("readBytes out of range");
            std::vector<uint8_t> result(buffer.begin() + offset, buffer.begin() + offset + length);
            offset += length;
            return result;
        }
        throw std::runtime_error("readBytes too long array, max " + std::to_string(maxCapacity));
    }

    int32_t readBytesLength() {
        return readInt();
    }

    void setByteArray(const std::vector<uint8_t>& buf, size_t len, size_t /*BufferLength*/) {
        offset = 0;
        length = len;
        bitIndex = 0;
        buffer = buf;
    }

    int32_t readInt() {
        bitIndex = 0;
        if (offset + 4 > buffer.size()) throw std::out_of_range("readInt out of range");
        int32_t value = (buffer[offset] << 24) | (buffer[offset + 1] << 16) | (buffer[offset + 2] << 8) | buffer[offset + 3];
        offset += 4;
        return value;
    }

    LogicLong readLong() {
        LogicLong val;
        val.decode(*this);
        return val;
    }

    int16_t readShort() {
        bitIndex = 0;
        if (offset + 2 > buffer.size()) throw std::out_of_range("readShort out of range");
        int16_t value = (buffer[offset] << 8) | buffer[offset + 1];
        offset += 2;
        return value;
    }

    std::string readString(int maxCapacity = 900001) {
        int32_t length = readBytesLength();
        if (length == -1) {
            return "";
        }
        if (length > maxCapacity) {
            std::cerr << "Too long String encountered, max " << maxCapacity << std::endl;
            return "";
        }
        if (offset + length > buffer.size()) {
            std::cerr << "readString out of range" << std::endl;
            return "";
        }
        std::string result(buffer.begin() + offset, buffer.begin() + offset + length);
        offset += length;
        return result;
    }


    std::string readStringReference(int maxCapacity = 900000) {
        int length = readBytesLength();
        if (length < 0) {
            throw std::runtime_error("Negative String length encountered.");
        }
        if (length > maxCapacity) {
            throw std::runtime_error("Too long String encountered, max " + std::to_string(maxCapacity));
        }
        if (offset + length > buffer.size()) throw std::out_of_range("readStringReference out of range");
        std::string result(buffer.begin() + offset, buffer.begin() + offset + length);
        offset += length;
        return result;
    }

    void removeByteArray() {
        buffer.clear();
    }

    void resetOffset() {
        offset = 0;
        bitIndex = 0;
    }

    void setOffset(size_t newOffset) {
        if (newOffset > buffer.size()) throw std::out_of_range("setOffset out of range");
        offset = newOffset;
        bitIndex = 0;
    }

    void writeBoolean(bool value) override {
        ChecksumEncoder::writeBoolean(value);
        if (bitIndex == 0) {
            ensureCapacity(1);
            buffer[offset] = 0;
            ++offset;
        }
        if (value) {
            buffer[offset - 1] |= (1 << bitIndex) & 0xFF;
        }
        bitIndex = (bitIndex + 1) & 7;
    }

    void writeByte(uint8_t value) override {
        ChecksumEncoder::writeByte(value);
        bitIndex = 0;
        ensureCapacity(1);
        buffer[offset] = value;
        ++offset;
    }

    void writeBytes(const std::vector<uint8_t>& data, size_t length) override {
        ChecksumEncoder::writeBytes(data, length);
        if (data.empty()) {
            writeInt(-1);
        } else {
            ensureCapacity(length + 4);
            writeInt(static_cast<int32_t>(length));
            std::copy(data.begin(), data.begin() + length, buffer.begin() + offset);
            offset += length;
        }
    }

    void writeIntToByteArray(int32_t value) {
        ensureCapacity(4);
        bitIndex = 0;
        buffer[offset] = (value >> 24) & 0xFF;
        buffer[offset + 1] = (value >> 16) & 0xFF;
        buffer[offset + 2] = (value >> 8) & 0xFF;
        buffer[offset + 3] = value & 0xFF;
        offset += 4;
    }

    void writeInt(int32_t value) override {
        ChecksumEncoder::writeInt(value);
        writeIntToByteArray(value);
    }

    void writeShort(int16_t value) override {
        ChecksumEncoder::writeShort(value);
        ensureCapacity(2);
        bitIndex = 0;
        buffer[offset] = (value >> 8) & 0xFF;
        buffer[offset + 1] = value & 0xFF;
        offset += 2;
    }

    void writeString(const std::string& value) override {
        ChecksumEncoder::writeString(value);
        if (value.empty()) {
            writeInt(-1);
            return;
        }
        size_t length = value.size();
        if (length > 900001) {
            writeInt(-1);
            return;
        }
        ensureCapacity(length + 4);
        writeInt(static_cast<int32_t>(length));
        std::copy(value.begin(), value.end(), buffer.begin() + offset);
        offset += length;
    }

    void writeStringReference(const std::string& value) override {
        ChecksumEncoder::writeStringReference(value);
        size_t length = value.size();
        if (length > 900001) {
            writeInt(-1);
            return;
        }
        ensureCapacity(length + 4);
        writeIntToByteArray(static_cast<int32_t>(length));
        std::copy(value.begin(), value.end(), buffer.begin() + offset);
        offset += length;
    }

    void clear(size_t capacity) {
        buffer.clear();
        offset = 0;
        length = 0;
        bitIndex = 0;
        if (capacity > UINT32_MAX) {
            capacity = UINT32_MAX;
        }
        buffer.resize(capacity);
    }
};

#endif // BYTESTREAM_H
