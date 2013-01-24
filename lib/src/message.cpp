#include "../include/message.hpp"

void MessageHandler::dispatch() {
    Message* message;
    while (messages.size() != 0) {
        message = messages.front();

        for (Receiver* receiver: receivers) {
            receiver->onMessage(*message);
        }

        messages.pop();
    }
}

void MessageHandler::registerReceiver(Receiver& receiver) {
    receivers.push_back(&receiver);
}

void MessageHandler::receive (Message& message) {
    messages.push(new Message(message));
}

void Message::send() {
    hub.receive(*this);
}
