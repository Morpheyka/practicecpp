/* ==============================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Nikita Zelentzoff $
   $Notice: $
   =============================================================== */

#include <iostream>
#include <stdint.h>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::string;
using std::vector;

typedef int8_t int8; // NOTE(Nikita): I don't know if you need to use a smaller integer type.
#define global_const const static

global_const int N_SQUARES = 9;
global_const char x = 'x';
global_const char o = 'o';
global_const char EMPTY = ' ';
global_const char DRAW = 'D';
global_const char PLAY = 'P';


void 
ShowInstructions()
{
	cout << "Welcome to the ultimate man-machine showdown: Tic-Tac-Toe.\n";
	cout << "--where human brain is pit against silicon processor\n\n";
	cout << "Make your move known bу entering a number, 0 - 8. The number\n";
	cout << "corresponds to the desired board position, as illustrated:\n\n";
	cout << " 1 | 2 | 3\n";
	cout << " ---------\n";
	cout << " 4 | 5 | 6\n";
	cout << " ---------\n";
	cout << " 7 | 8 | 9\n\n";
	cout << "Prepare yourself, human, The battle is about to begin.\n\n";
}

char
AskQuestion(string question)
{
	char answer = ' ';

	while (answer != 'y' && answer != 'n')
	{
		cout << question << " (y/n)";
		cin >> answer;
	}

	return answer;
}

int
AskCellNumber(string question)
{
	int number;

	do
	{
		cout << question << " (" << 1 << " - " << N_SQUARES << "): ";
		cin >> number;
	} while (number < 0 || number > N_SQUARES - 1);

	return --number;
}

char
SideSelection()
{
	char firstTurn = AskQuestion("Do you require the first move?");
	if (firstTurn == 'y')
	{
		cout << "\nThen take the first move. You will need it.\n";
		return x;
	}
	else
	{
		cout << "\nYour bravery will be your undoing...I will go first.\n";
		return o;
	}
}

char
ChangeTurn(char turn)
{
	if (turn == 'x')
	{
		return o;
	}
	else
	{
		return x;
	}
}

void
ShowBoard(const vector<char>& board)
{
	cout << "\n\t" << board[0] << " | " << board[1] << " | " << board[2];
	cout << "\n\t" << "---------";
	cout << "\n\t" << board[3] << " | " << board[4] << " | " << board[5];
	cout << "\n\t" << "---------";
	cout << "\n\t" << board[6] << " | " << board[7] << " | " << board[8];
	cout << "\n\n";
}

char
WhoWinner(const vector<char>& board)
{
	const int TOTAL_ROWS = 8;
	const int WINNING_ROWS[TOTAL_ROWS][3] = {
	{0, 1, 2},
	{3, 4, 5},
	{6, 7, 8},
	{0, 3, 6},
	{1, 4, 7},
	{2, 5, 8},
	{0, 4, 8},
	{2, 4, 6} };

	for (int row = 0; row < TOTAL_ROWS; row++)
	{
		if ((board[WINNING_ROWS[row][0]] != EMPTY) &&
			(board[WINNING_ROWS[row][0]] == board[WINNING_ROWS[row][1]]) &&
			(board[WINNING_ROWS[row][1]] == board[WINNING_ROWS[row][2]]))
		{
			return board[WINNING_ROWS[row][0]];
		}
	}

	if (count(board.begin(), board.end(), EMPTY) == 0)
	{
		return DRAW;
	}

	return PLAY;
}

bool
IsLegal(int move, vector<char>& board)
{
	return (board[move] == EMPTY);
}

int
HumanMove(vector<char>& board)
{
	int move = AskCellNumber("Where will you move?");
	while (!IsLegal(move, board))
	{
		cout << "\nThat square is already occupied, foolish human.\n";
		int move = AskCellNumber("Where will you move?");
	}
	cout << "Fine...\n";

	return move;
}

int
EnemyMove(vector<char> board, char computer)
{
	int move = 0;
	bool found = false;

	while (!found && move < board.size())
	{
		if (IsLegal(move, board))
		{
			board[move] = computer;
			found = (WhoWinner(board) == computer);
			board[move] = EMPTY;
		}
		if (!found)
		{
			++move;
		}
	}

	if (!found)
	{
		move = 0;
		char human = ChangeTurn(computer);

		while(!found && move < board.size())
		{
			if (IsLegal(move, board))
			{
				board[move] = human;
				found = (WhoWinner(board) == human);
				board[move] = EMPTY;
			}
			if (!found)
			{
				++move;
			}
		}
	}

	if (!found)
	{
		move = 0;
		int i = 0;
		const int BEST_MOVES[] = { 4, 0, 2, 6, 8, 1, 3, 5, 7 };

		while (!found && i < board.size())
		{
			move = BEST_MOVES[i];
			if (IsLegal(move, board))
			{
				found = true;
			}
			++i;
		}
	}
	cout << "I shall take square number " << move+1 << "\n";

	return move;
}

void
GameOver(char whoWinner, char human, char enemy)
{
	if (whoWinner == enemy)
	{
		cout << whoWinner << "'s won!\n";
		cout << "As I predicted, human. I am triumphant once more -- proof\n";
		cout << "that computers are superior to humans in all regards.\n";
	}
	else if (whoWinner == human)
	{
		cout << whoWinner << "s won!\n";
		cout << "No, по! It cannot №е! Somehow you tricked me, human. \n";
		cout << "But never again! I, the computer, so swear it!\n";
	}
	else
	{
		cout << "It's a draw.\n";
		cout << "You were most lucky, human, and somehow managed to tie me.\n";
		cout << "Celebrate ... for this is the best you will ever achieve.\n";
	}
}


int main() {
	vector<char> board(N_SQUARES, EMPTY);

	ShowInstructions();
	
	char human = SideSelection();
	char enemy = ChangeTurn(human);
	char turn = 'x';
	int move;

	while (WhoWinner(board) == PLAY) 
	{
		if (turn == human) 
		{
			move = HumanMove(board);
			board[move] = human;
		} 
		else 
		{
			move = EnemyMove(board, enemy);
			board[move] = enemy;
		}
		ShowBoard(board);
		turn = ChangeTurn(turn);
	}

	GameOver(WhoWinner(board), human, enemy);

	return 0;
}
