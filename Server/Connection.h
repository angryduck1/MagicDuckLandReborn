#ifndef CONNECTION_H
#define CONNECTION_H

#include <boost/asio.hpp>
#include <iostream>
#include <cstdint>
#include <memory>
#include "Messaging.h"
#include "MessageManager.h"
#include "Header.h"
#include "Rc4.h"
#include "PiranhaMessage.h"
#include "LogicMagicMessageFactory.h"

using namespace boost::asio;
using ip::tcp;

using namespace std;

class Connection {
public:
    Messaging messaging;

    Connection(shared_ptr<tcp::socket> client, string key) : client(client), rc4(key, "nonce"), messaging(client, key), manager(&messaging) {
    }

    vector<uint8_t> recv(size_t n) {
        vector<uint8_t> data;
        data.reserve(n);
        size_t total_read = 0;

        boost::system::error_code error;

        while (total_read < n) {
            size_t to_read = n - total_read;
            vector<uint8_t> buffer(to_read);

            size_t length = client->read_some(boost::asio::buffer(buffer), error);
            if (error) {
                if (error == boost::asio::error::eof) {
                    break;
                } else if (error == boost::asio::error::would_block) {
                    continue;
                } else {
                    cerr << "Error reading from socket: " << error.message() << endl;
                    break;
                }
            }

            data.insert(data.end(), buffer.begin(), buffer.begin() + length);
            total_read += length;
        }

        if (data.size() < n) {
            return {};
        }

        return data;
    }

    int run() {
        while (true) {
            vector<uint8_t> handle = recv(7);

            if (handle.size() == 7) {
                Header header = messaging.readHeader(handle);

                int messageType = header.messageType;
                int encodingLength = header.encodingLength;
                int messageVersion = header.messageVersion;

                vector<uint8_t> payload = recv(encodingLength);

                if (payload.size() < encodingLength) {
                    cerr << "Error reading payload" << endl;
                    continue;
                }

                shared_ptr<PiranhaMessage> message = LogicMagicMessageFactory::createMessageByType(messageType);

                if (message != nullptr && messageType != 14102) {
                    message->setMessageVersion(messageVersion);

                    std::vector<uint8_t> decPayload = rc4.decrypt(payload);

                    message->getByteStream().setByteArray(decPayload, encodingLength);

                    message->decode();

                    manager.receiveMessage(message);
                } else if (messageType == 14102) {
                    message->setMessageVersion(messageVersion);

                    std::vector<uint8_t> decPayload = rc4.decrypt(payload);

                    message->getByteStream().setByteArray(decPayload, encodingLength);

                    manager.receiveMessage(message);
                } else {
                    cout << "[Connection] Ignoring message of unknown type " << messageType << endl;
                }
            } else {
                client->close();
                cout << "Client disconnected" << endl;
                break;
            }
        }

        return 1;
    }


private:
    shared_ptr<tcp::socket> client;
    RC4Encrypter rc4;
    MessageManager manager;

};

#endif
