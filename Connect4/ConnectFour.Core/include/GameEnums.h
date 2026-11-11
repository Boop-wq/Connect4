#pragma once

enum class EPiece
{
	None,
	Red,
	Yellow
};

enum class EGameState
{
	Playing,
	RedWon,
	YellowWon,
	Draw
};

enum class EMoveResult
{
	Success,
	InvalidColumn,
	ColumnFull,
	GameOver

};