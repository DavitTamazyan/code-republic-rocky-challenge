class TicTacToe
{
private:
	struct Move
	{
		size_t row = 0;
		size_t col = 0;

		Move(){}

		Move(size_t row_, size_t col_) : row(row_), col(col_){}

		bool IsValid()
		{
			return ((row >= 0 && row <= 3) && (col >= 0 && col <= 3));
		}
	};

public:

	TicTacToe()
	{
		m_size = 3;
		m_turn = true;
		m_bot = false;
		m_xcount = 0;
		m_ycount = 0;
		m_winner = ' ';
		m_table.push_back({ '-','-' ,'-' });
		m_table.push_back({ '-','-' ,'-' });
		m_table.push_back({ '-','-' ,'-' });
		PlayGame();
	}

	~TicTacToe()
	{

	}

	/// Game
	void PlayGame()
	{
		//SetBotSide();
		std::cout << "Game Started" << std::endl;
		Move curMove;
		bool endGame = false;
		while (!endGame)
		{
			Print();
			curMove = ReadCommand();
			if (CheckCommand(curMove))
			{
				MoveTo(curMove);
			}
			else
			{
				std::cout << "Invalid Move" << std::endl;
			}
			endGame = IsEnd(curMove);
		}
		Print();
		std::cout << m_winner << " Wins" << std::endl;
		std::cout << "Game Ended" << std::endl;
	}

	Move ReadCommand() /// Bug in impl
	{
		Move curMove;
		if (m_turn)
		{
			std::cout << "Xs turn ";
		}
		else
		{
			std::cout << "Ys turn ";
			std::cout << std::endl;
		}
		if (m_turn == m_bot)
		{
			curMove = BotGame();
		}
		else
		{
			std::string command;
			std::cin >> command;
			curMove.row = (command.size() != 2) ? 3 : command[0] - 48;
			curMove.col = (command.size() != 2) ? 3 : command[1] - 48;
		}
		
		return curMove;
	}

	bool CheckCommand(Move comm)
	{
		if (comm.IsValid() && m_table[comm.row][comm.col] == '-')
		{
			return true;
		}
		return false;
	}

	void Print()
	{
		std::cout << "_____" << std::endl;
		for (size_t i = 0; i < m_size; ++i)
		{
			for (size_t j = 0; j < m_size; ++j)
			{
				std::cout << m_table[i][j] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << "_____" << std::endl;
	}

	void SetBotSide()
	{
		std::cout << "Set Bot" << std::endl;
		std::string txt;
		std::cin >> txt;
		if ((txt.size() == 1) && txt == "X")
		{
			m_bot = true;
		}
	}

	/// Move
	void MoveTo(Move move)
	{
		//std::cout << "Called MoveTo   " << move.row << " " << move.col << std::endl;
		m_table[move.row][move.col] = (m_turn) ? 'X' : 'O';
		m_turn = !m_turn;
	}

	void MoveBack(Move move)
	{
		//std::cout << "Called MoveBack " << move.row << " " << move.col << std::endl;
		m_table[move.row][move.col] = '-';
		m_winner = ' ';
		m_turn = !m_turn;
	}

	/// Result
	bool IsEnd(Move move)
	{
		return Vertical(move) || Diagonal(move) || Draw();
	}

	bool Vertical(Move move)
	{
		bool colMach = true;
		bool rowMach = true;
		for (size_t i = 0; i < m_size - 1; ++i)
		{
			if ((colMach && m_table[i][move.col] != m_table[i + 1][move.col]) || m_table[i][move.col] == '-')
			{
				colMach = false;
			}
			if ((rowMach && m_table[move.row][i] != m_table[move.row][i + 1]) || m_table[move.row][i] == '-')
			{
				rowMach = false;
			}
		}
		if (colMach)
		{
			m_winner = m_table[0][move.col];
		}
		else if (rowMach)
		{
			m_winner = m_table[move.row][0];
		}
		return colMach || rowMach;
	}

	bool Diagonal(Move move)
	{
		bool mainDiagonal = true;
		bool secondDiagonal = true;

		for (size_t i = 0; i < m_size - 1; ++i)
		{
			if ((mainDiagonal && m_table[i][i] != m_table[i + 1][i + 1]) || m_table[i][i] == '-')
			{
				mainDiagonal = false;
			}
			if ((secondDiagonal && m_table[i][m_size - 1 - i] != m_table[i + 1][m_size - 1 - i - 1]) || m_table[i][m_size - 1 - i] == '-')
			{
				secondDiagonal = false;
			}
		}
		if (mainDiagonal || secondDiagonal)
		{
			m_winner = m_table[1][1];
		}
		return mainDiagonal || secondDiagonal;
	}

	bool Draw()
	{
		for (size_t i = 0; i < m_size; ++i)
		{
			for (size_t j = 0; j < m_size; ++j)
			{
				if (m_table[i][j] == '-')
				{
					return false;
				}
			}
		}
		m_winner = '-';
		return true;
	}

	/// MinMax Algorithm
	Move BotGame()
	{
		Move BestMove; 
		int maxResult = -11000;
		int curCount = 0;
		int gamesCount = 10;
		CalcMinMax(maxResult, curCount, BestMove, true, gamesCount);
		std::cout << "BestMove = " << BestMove.row << " " << BestMove.col << std::endl;
		return BestMove;
	}

	void CalcMinMax(int& maxResult, int& curCount, Move& BestMove, bool mainRoot, int& gamesCount) /// Delete depth
	{
		//Print();
		for (size_t i = 0; i < m_size; ++i)
		{
			for (size_t j = 0; j < m_size; ++j)
			{
				if ('-' == m_table[i][j])
				{
					Move curMove(i, j);
					MoveTo(curMove);

					if (IsEnd(curMove))
					{
						curCount += gamesCount * ((m_winner == 'O') ? 1 : (m_winner == 'X') ? -1 : 0);
					}
					else
					{
						CalcMinMax(maxResult, curCount, BestMove, false, --gamesCount);
					}

					if (mainRoot && curCount > maxResult)
					{
						maxResult = curCount;
						BestMove = curMove;
					}
					if (mainRoot)
					{
						std::cout << i << " " << j << " -> " << curCount << std::endl;
					}
					curCount = (mainRoot) ? 0 : curCount;
					gamesCount = (mainRoot) ? 10 : gamesCount;
					MoveBack(curMove);
				}
			}
		}
	}

private:
	std::vector<std::vector<char>> m_table;
	size_t m_size;
	bool m_turn;
	bool m_bot;
	uint8_t m_xcount;
	uint8_t m_ycount;
	char m_winner;
};