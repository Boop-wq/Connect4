#include"Game.h"
#include"Board.h"

Game::Game():
	m_currentPlayer(EPiece::Red),
	m_state(EGameState::Playing)
{

}

EMoveResult Game::MakeMove(int column)
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
	if (it == m_listeners.end())
		m_listeners.push_back(listener);
		
}

void Game::RemoveListener(IGameListener *listener)
{
	if(listener==nullptr)
		return;
	auto it = std::find(m_listeners.begin(), m_listeners.end(), listener);
	if(it != m_listeners.end())
		m_listeners.erase(it);
	
}

void Game::SwitchPlayer()
{
	if (m_currentPlayer == EPiece::Red)
		m_currentPlayer = EPiece::Yellow;
	else
		m_currentPlayer = EPiece::Red;
}

void Game::UpdateState(int row, int column)
{
	if (m_board.IsWinningMove(row, column))
		m_state = (m_currentPlayer == EPiece::Red) ? EGameState::RedWon : EGameState::YellowWon;
	else if (m_board.IsFull())
		m_state = EGameState::Draw;

}

void Game::NotifyMoveMade(int row, int column, EPiece piece)
{
	for (IGameListener* listener : m_listeners)
	{
		listener->OnMoveMade(row, column, piece);
	}
}

void Game::NotifyGameOver()
{
	for (IGameListener* listener : m_listeners)
	{
		listener->OnGameOver(m_state);
	}
}

void Game::NotifyGameRestarted()
{
	for (IGameListener* listener : m_listeners)
	{
		listener->OnGameRestarted();
	}
}

std::shared_ptr<IGame> Game::Create()
{
	return std::make_shared<Game>();
}