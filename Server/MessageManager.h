#ifndef MESSAGEMANAGER_H
#define MESSAGEMANAGER_H

#include <iostream>
#include <memory>
#include "Messaging.h"
#include "LoginMessage.h"
#include "PiranhaMessage.h"
#include "LoginOkMessage.h"
#include "OwnHomeDataMessage.h"
#include "EndClientTurnMessage.h"

using namespace std;

class MessageManager {
private:
    Messaging* messaging;
public:
    MessageManager(Messaging* messaging) {
        this->messaging = messaging;
    }

    void receiveMessage(shared_ptr<PiranhaMessage> message) {
        int messageType = message->getMessageType();

        if (messageType == 10101) {
            shared_ptr<LoginMessage> loginMsg = dynamic_pointer_cast<LoginMessage>(message);

            if (loginMsg) {
                onLoginMessage(loginMsg);
            } else {
                std::cerr << "Received message of wrong type for onLoginMessage" << std::endl;
            }
        } else if (messageType == 14102) {
            shared_ptr<EndClientTurnMessage> endTurnMessage = dynamic_pointer_cast<EndClientTurnMessage>(message);

            if (endTurnMessage) {
                OnEndClientTurnMessage(endTurnMessage);
            } else {
                std::cerr << "Received message of wrong type for OnEndClientTurnMessage" << std::endl;
            }
        }
        else {
            std::cerr << "Unknown message type: " << messageType << std::endl;
        }
    }

    void onLoginMessage(shared_ptr<LoginMessage> loginMessage) {
        std::cout << "[MessageManager] Logged in! AccountId: " << loginMessage->AccountID.toString()
        << " PassToken: " << loginMessage->passToken
        << " ClientMajorVersion: " << loginMessage->getClientMajorVersion()
        << " ClientBuild: " << loginMessage->getClientBuild()
        << " ResourceSha: " << loginMessage->resourceSha
        << std::endl;

       messaging->sendMessage(std::make_shared<LoginOkMessage>());
       messaging->sendMessage(std::make_shared<OwnHomeDataMessage>());

       std::cout << "Login message received" << std::endl;
    }

    void OnEndClientTurnMessage(shared_ptr<EndClientTurnMessage> endTurnMessage) {
        endTurnMessage->decode();
    }
};

#endif // MESSAGEMANAGER_H
