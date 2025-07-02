#ifndef LOGICMAGICMESSAGEFACTORY_H
#define LOGICMAGICMESSAGEFACTORY_H

#include <map>
#include <memory>
#include <functional>
#include "PiranhaMessage.h"
#include "LoginMessage.h"

class LogicMagicMessageFactory {
public:
    static std::unique_ptr<PiranhaMessage> createMessageByType(int messageType) {
        const auto& creators = getCreators();
        auto it = creators.find(messageType);

        if (it != creators.end()) {
            if (it->first == 10101) {
                cout << "[LogicMagicMessageFactory] Created new message " << messageType << endl;
            }
            return it->second();
        } else {
            return nullptr;
        }
    }

private:
    static const std::map<int, std::function<std::unique_ptr<PiranhaMessage>()>>& getCreators() {
        static const std::map<int, std::function<std::unique_ptr<PiranhaMessage>()>> creators = {
            {10101, [](){ return std::make_unique<LoginMessage>(); }}
        };
        return creators;
    }
};

#endif // LOGICMAGICMESSAGEFACTORY_H
