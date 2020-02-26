#ifndef GAME_H /* Include guard */
#define GAME_H

class Game
{
public:
    Game(unsigned short int windowWidth = 800, unsigned short int windowHeight = 600, int flags = 0);
    void play() const;
};

#endif