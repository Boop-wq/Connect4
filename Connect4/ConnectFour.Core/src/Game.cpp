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

	if (m_state != EGameState::Playing)
		NotifyGameOver();

	return EMoveResult::Success;

}


void Game::Restart()
{
	m_board.Clear();
	m_currentPlayer = EPiece::Red;
	m_state = EGameState::Playing;

	NotifyGameRestarted();	
}

EPiece Game::GetPieceAt(int row, int column) const
{
	return m_board.GetPiece(row, column);
}

EPiece Game::GetCurrentPlayer() const
{
	return m_currentPlayer;
}

EGameState Game::GetState() const
{
	return m_state;
}

void Game::AddListener(IGameListener *listener)
{
	if(listener==nullptr)
		return;
	auto it = std::find(m_listeners.begin(), m_listeners.end(), listener);
	if (it != m_listeners.end())
		m_listeners.push_back(listener);
	else {
		return;
	}	
}

void Game::RemoveListener(IGameListener *listener)
{
	if(listener==nullptr)
		return;
	auto it = std::find(m_listeners.begin(), m_listeners.end(), listener);
	if(it != m_listeners.end())
		m_listeners.erase(it);
	else {
		return;
	}
}

