#pragma once

class TurnCounter 
{
public:
    TurnCounter() : turn(0) {}

    void increment() 
    {
        turn++;
    }

    int getTurn() const { return turn; }

private:
    int turn;
};