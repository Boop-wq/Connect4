#pragma once

#include <array>

#include "IGame.h"
#include "GameEnums.h"


class Board : 
{
public:
		Board();

		void Clear();
		bool IsInside(int32_t column, int32_t row) const;
		bool IsFull(int32_t column) const;
		EPiece GetPieceAt(int32_t column, int32_t row) const;
	
}