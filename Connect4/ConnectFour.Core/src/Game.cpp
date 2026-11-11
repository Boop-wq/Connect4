#include"Game.h"
#include"Board.h"

Game::Game()
{

}

EMoveResult Game:: MakeMove(int column) const
{
	if (m_state != EGameState::Playing)
		return EMoveResult::GameOver;
	if (!m_board.IsInside(0, column))
		return EMoveResult::InvalidColumn;
	if (m_board.IsColumnFull(column))
		return EMoveResult::ColumnFull;

	EPiece piece = m_currentPlayer;
	int row = m_board.DropPiece(column, piece);

	UpdateState(row, column);

	if (m_state == EGameState::Playing)
		SwitchPlayer();
	
	NotifyMoveMade(row, column, piece);

	if (m_state != EGamePlaying)
		NotifyGameOver();

	return EMoveResult::Success;

}


void Game : Restart()
{
	m_board.
}

