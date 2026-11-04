#pragma once

#include <memory>

#include "GameEnums.h"
#include "IGameListener.h"

class IGame
{
public:

	static const int32_t NUM_COLUMNS = 7;
	static const int32_t NUM_ROWS = 6;

	static std::unique_ptr<IGame> Create();

	virtual ~IGame() = default;
	virtual void Restart() = 0;

	virtual EMoveResult MakeMove(int32_t column) = 0;

	virtual EGameState GetState() const = 0;
	virtual EPiece GetCurrentPlayer() const = 0;
	virtual EPiece GetPieceAt(int32_t column, int32_t row) const = 0;

	virtual void AddListener(IGameListener* listener) = 0;
	virtual void RemoveListener(IGameListener* listener) = 0;
}