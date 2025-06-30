#ifndef MESSAGING_H
#define MESSAGING_H

#include <boost/asio.hpp>
#include <memory>
#include <vector>
#include <string>
#include <cstdint>
#include "Header.h"
#include "PiranhaMessage.h"
#include "Rc4.h"

using namespace boost::asio;
using ip::tcp;

using namespace std;

class Messaging {
private:
    shared_ptr<tcp::socket> client;
    RC4Encrypter rc4;
public:
    Messaging(shared_ptr<tcp::socket> client, string key) : rc4(key, "nonce") {
        this->client = client;
    }
    Header readHeader(vector<uint8_t>& buffer) {
        Header header;

        header.messageType =
            (static_cast<unsigned char>(buffer[0]) << 8) |
            static_cast<unsigned char>(buffer[1]);

        header.encodingLength =
            (static_cast<unsigned char>(buffer[2]) << 16) |
            (static_cast<unsigned char>(buffer[3]) << 8) |
            static_cast<unsigned char>(buffer[4]);

        header.messageVersion =
            (static_cast<unsigned char>(buffer[5]) << 8) |
            static_cast<unsigned char>(buffer[6]);

        return header;
    }

    void writeHeader(vector<uint8_t>& buffer, shared_ptr<PiranhaMessage> message, size_t length) {
        int messageType = message->getMessageType();
        int messageVersion = message->getMessageVersion();

        buffer[0] = (messageType >> 8) & 0xFF;
        buffer[1] = messageType & 0xFF;
        buffer[2] = (length >> 16) & 0xFF;
        buffer[3] = (length >> 8) & 0xFF;
        buffer[4] = length & 0xFF;
        buffer[5] = (messageVersion >> 8) & 0xFF;
        buffer[6] = messageVersion & 0xFF;
    }

    void sendMessage(shared_ptr<PiranhaMessage> message) {
        message->encode();

        vector<uint8_t> encodingBytes = message->getByteStream().getByteArray();
        encodingBytes.resize((message->getEncodingLength()));

        vector<uint8_t> encEncodingBytes = rc4.encrypt(encodingBytes);

        vector<uint8_t> buffer(encEncodingBytes.size() + 7);

        Messaging::writeHeader(buffer, message, encEncodingBytes.size());

        std::copy(encEncodingBytes.begin(), encEncodingBytes.end(), buffer.begin() + 7);

        cout << "Buffer size: " << buffer.size() << endl;

        boost::system::error_code error;
        boost::asio::write(*client, boost::asio::buffer(buffer), error);

        if (error) {
            std::cerr << "[Messaging] Error sending message: " << error.message() << std::endl;
        } else {
            std::cout << "[Messaging] Sent message type " << message->getMessageType() << std::endl;
        }
    }
};

#endif // MESSAGING_H
