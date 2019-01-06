#include <iostream>
#include <string>
#include <random>
#include <ctime>

typedef unsigned int uint;

using std::cin;
using std::cout;
using std::string;	

int main() 
{	
	enum fields {WORD, HINT, N_FIELDS };
	const int N_WORDS = 5;
	const string WORDS[N_WORDS][N_FIELDS] = {
	{"wall", "Do you feel you're banging your head againts something?"},
	{"glasses", "These might help you see the answer. "},
	{"labored", "Going slowly. Is it?"},
	{"persisten", "Кеер at it."},
	{"jumble", "It's what the game is all about."}
};

	std::mt19937 rndSeed(time(0));
	std::uniform_int_distribution<uint> uidWords(0, N_WORDS-1);
	int choice = uidWords(rndSeed);
	string theWord = WORDS[choice][WORD]; 
	string theHint = WORDS[choice][HINT];

	string jumble = theWord;
	int length = jumble.size();
	std::uniform_int_distribution<uint> uidLenght(0, --length);
	for (int i = 0; i < length; i++)
	{
			int index1 = uidLenght(rndSeed);
			int index2 = uidLenght(rndSeed);
			char temp = jumble[index1];
			jumble[index1] = jumble[index2];
			jumble[index2] = temp;
	}

	cout << "\t\t\tWelcome to Word Jumble!\n\n";
	cout << "Unscramble the letters to make a word. \n";
	cout << "Enter 'hint' for a hint. \n";
	cout << "Enter 'quit' to quit the game. \n\n";
	cout << "The jumble is: " << jumble;
	string guess;
	cout << "\n\nYour guess: ";
	cin>>guess;

	while ((guess != theWord) && (guess != "quit"))
	{
		if (guess == "hint")
		{
			cout << theHint;
		} 
		else 
		{
			cout << "Sorry. that's not it. ";
		}
		cout << "\n\nYour guess: ";
		cin >> guess;
	}

	if (guess == theWord)
	{
		cout << "\nThat's it! You guessed it!\n";
	}
	cout << "\nThanks for playing.\n\n";

	system("pause");
	return 0;
}