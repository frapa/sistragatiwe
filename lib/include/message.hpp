#ifndef MESSAGE
#define MESSAGE

#include <vector>
#include <list>
#include <queue>

enum message_type {
    
};

// forward declaration
struct Message;

// this is meant to be subclassed...
class Receiver {
public:
    Receiver() {
        
    }

    // must be redefinded to receive messages
    virtual void onMessage(Message& message) {}
};

class MessageHandler {
private:
    std::queue<Message*, std::list<Message*>> messages;
    std::vector<Receiver*> receivers;

    // singleton design
    MessageHandler() {}
    MessageHandler(MessageHandler const&);
    void operator=(MessageHandler const&);

public:
    static MessageHandler& getInstance() {
        static MessageHandler instance;

        return instance;
    }

    // dispatches events
    void dispatch();
    
    void registerReceiver(Receiver& receiver);
    // copies messages to the queue
    void receive(Message& message);
};

// also meant to be subclassed
struct Message {
    message_type type;

    // sends the message to whoever will recieve it :-)
    void send();
};

#endif
