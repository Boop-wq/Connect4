#include"Board.h"

Board::Board()
{

}

void Board::Clear()
{
	for(auto& row: m_cells)
	{
		r.fill(EPiece::None);
	}
}
bool Board::IsInside(int row, int column) const
{
	return row >= 0 && row < IGame::NUM_ROWS && column >= 0 && column < IGame::NUM_COLUMNS;
}

EPiece Board::GetPiece(int row, int column) const
{
	if(!IsInside(row, column))
	{
		return EPiece::None;
	}
	return m_cells[row][column];
}

bool Board::IsFull() const
{
	for(int column = 0; column < IGame::NUM_COLUMNS; ++column)
	{
		if(!IsColumnFull(column))
		{
			return false;
		}
	}
	return true;
}

bool Board::IsColumnFull(int column) const
{
	return m_cells[0][column] != EPiece::None;
}

int Board::DropPiece(int column, EPiece piece)
{
	if(IsColumnFull(column))
	{
		return -1;
	}
	for(int row = IGame::NUM_ROWS - 1; row >= 0; --row)
	{
		if(m_cells[row][column] == EPiece::None)
		{
			m_cells[row][column] = piece;
			return row;
		}
	}
	return -1;
}

bool Board::IsWinningMove(int row, int column) const
{
	EPiece piece = GetPiece(row, column);
	if(piece == EPiece::None)
	{
		return false;
	}
	return CountInDirection(row, column, 1, 0) + CountInDirection(row, column, -1, 0) - 1 >= kWinLength ||
		   CountInDirection(row, column, 0, 1) + CountInDirection(row, column, 0, -1) - 1 >= kWinLength ||
		   CountInDirection(row, column, 1, 1) + CountInDirection(row, column, -1, -1) - 1 >= kWinLength ||
		   CountInDirection(row, column, 1, -1) + CountInDirection(row, column, -1, 1) - 1 >= kWinLength;
}

int Board::CountInDirection(int row, int column, int dRow, int dColumn) const
{
	EPiece piece = GetPiece(row, column);
	int count = 0;
	while(IsInside(row, column) && GetPiece(row, column) == piece)
	{
		++count;
		row += dRow;
		column += dColumn;
	}
	return count;
}


