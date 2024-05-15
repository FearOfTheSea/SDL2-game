#pragma once

class TurnCounter 
{
public:
    TurnCounter(int turn) : turn(turn) {}
    TurnCounter() = default;
    void increment() 
    {
        turn++;
    }
    int getTurn() const { return turn; }
private:
    int turn;
};