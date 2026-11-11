#pragma once

#include <vector>
#include<algorithm>

#include "IGame.h"
#include "Board.h"

class Game : public IGame
{
public:
    Game();

    EMoveResult MakeMove(int column) override;
    void Restart() override;

    EPiece GetPieceAt(int row, int column) const override;
    EPiece GetCurrentPlayer() const override;
    EGameState GetState() const override;

    void AddListener(IGameListener* listener) override;
    void RemoveListener(IGameListener* listener) override;

private:
    void SwitchPlayer();
    void UpdateState(int row, int column);
    void NotifyMoveMade(int row, int column, EPiece piece);
    void NotifyGameOver();
    void NotifyGameRestarted();


    Board m_board;
    EPiece m_currentPlayer;
    EGameState m_state;
    std::vector<IGameListener*> m_listeners;
};