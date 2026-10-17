#ifndef GAMETHREAD_H
#define GAMETHREAD_H

#include <QThread>
#include "game.h"

class GameThread : public QThread {
    Q_OBJECT
private:
    Game* game;

public:
    explicit GameThread(Game* game, QObject *parent = nullptr)
        : QThread(parent), game(game) {}

    void run() override {
        game->initialize(1);
        std::cout<<".........2"<<std::endl;
        game->run();
    }

    Game* getGame() { return game; }
};

#endif // GAMETHREAD_H
