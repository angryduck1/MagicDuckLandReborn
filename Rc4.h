#ifndef RC4_H
#define RC4_H

#include <string>
#include <vector>
#include <iostream>
#include <cstdint>

class RC4Encrypter {
public:
    RC4Encrypter(const std::string& base_key, const std::string& nonce)
        : key(base_key + nonce), lengthKey(key.size()) {
        if (lengthKey == 0) {
            std::cerr << "Error, key equal zero" << std::endl;
        }
        initializeState();
    }

    std::vector<uint8_t> encrypt(const std::vector<uint8_t>& message) {
        std::vector<uint8_t> result;
        result.reserve(message.size());

        for (uint8_t byte : message) {
            x = (x + 1) % 256;
            y = (y + s[x]) % 256;
            std::swap(s[x], s[y]);
            uint8_t keyStreamByte = s[(s[x] + s[y]) % 256];
            result.push_back(byte ^ keyStreamByte);
        }
        return result;
    }

    std::vector<uint8_t> decrypt(const std::vector<uint8_t>& message) {
        return encrypt(message);
    }

private:
    std::string key;
    size_t lengthKey;
    uint8_t s[256];
    int x = 0;
    int y = 0;

    void initializeState() {
        for (int i = 0; i < 256; i++) s[i] = i;

        int j = 0;
        for (int i = 0; i < 256; i++) {
            j = (j + s[i] + static_cast<uint8_t>(key[i % lengthKey])) % 256;
            std::swap(s[i], s[j]);
        }

        for (size_t i = 0; i < lengthKey; i++) {
            x = (x + 1) % 256;
            y = (y + s[x]) % 256;
            std::swap(s[x], s[y]);
        }
    }
};

#endif // RC4_H
