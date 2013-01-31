#ifndef MESSAGE
#define MESSAGE

#include <iostream>
#include <list>
#include <map>
#include <string>
#include <algorithm>
#include <typeinfo>
#include <SFML/Graphics.hpp>

// forward declaration
template <typename T> class Receiver;

template <typename T>
class MessageHandler {
private:
    std::list<Receiver<T>*> receivers;

    // singleton design
    MessageHandler() {}
    MessageHandler(MessageHandler<T> const&);
    void operator=(MessageHandler<T> const&);

public:
    static MessageHandler<T>& getInstance() {
        static MessageHandler<T> instance;

        return instance;
    }

    void registerReceiver(Receiver<T>* receiver) {
        receivers.push_back(receiver);
    }

    void deleteReceiver(Receiver<T>* receiver) {
        auto r = std::find(receivers.begin(), receivers.end(), receiver);

        receivers.erase(r);
    }

    // receives a message and sends it to the receivers
    void receive(T& message) {
        for (Receiver<T>* receiver: receivers) {
            receiver->onMessage(message);
        }
    }
};

// This is meant to be subclassed...
// It as an abstrac base class with pure virtual
// member functions.
template <typename T>
class Receiver {
public:
    Receiver<T>() {
        MessageHandler<T>::getInstance().registerReceiver(this);
    }

    ~Receiver<T>() {
        MessageHandler<T>::getInstance().deleteReceiver(this);
    }

    // must be redefinded to receive messages
    virtual void onMessage(T& message) = 0;
};


// Meant to be specialized by other implementations.
// It is an abstract base class with pure virtual functions.
struct Message {
    Message() {}

    // sends the message to whoever will recieve it :-)
    virtual void send() = 0;
};

#endif
