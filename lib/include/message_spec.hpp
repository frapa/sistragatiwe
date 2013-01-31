#ifndef MESSAGE_SPEC
#define MESSAGE_SPEC

#include "message.hpp"
#include "player.hpp"

///////////////////////////////////////////
// MESSAGES SPECIALIZATION
///////////////////////////////////////////

struct ResMessage: public Message {
    Player& player;

    ResMessage(Player& _player):
        player(_player)
    {}

    virtual void send()
    {
        MessageHandler<ResMessage>::getInstance().receive(*this);
    }
};

struct EventMessage: public Message {
    sf::Event event;

    EventMessage(sf::Event& _event):
        event(_event)
    {}

    virtual void send()
    {
        MessageHandler<EventMessage>::getInstance().receive(*this);
    }
};

#endif
