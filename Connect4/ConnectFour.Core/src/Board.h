#pragma once

#include <array>

#include "GameEnums.h"
#include "IGame.h"

class Board
{
public:
    Board();   

    void Clear();
    bool IsInside(int row, int column) const;
    EPiece GetPiece(int row, int column) const;
    bool IsFull() const;

    bool IsColumnFull(int column) const;
    int DropPiece(int column, EPiece piece);
    bool IsWinningMove(int row, int column) const;

private:
    int CountInDirection(int row, int column, int dRow, int dColumn) const;

    static constexpr int kWinLength = 4;

    std::array<std::array<EPiece, IGame::kColumns>, IGame::kRows> m_cells;
};