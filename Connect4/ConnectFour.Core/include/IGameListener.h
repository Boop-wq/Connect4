#pragma once

#include "GameEnums.h"

class IGameListener
{
public:
	virtual ~IGameListener() = default;
	virtual void OnGameRestarted() = 0;
	virtual void OnGameOver(EGameState state) = 0;
	virtual void OnMoveMade(int32_t column, int32_t row, EPiece piece) = 0;

}
