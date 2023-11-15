/*
Plan to use returned deck from the shuffledeck function as a parameter for main game, 
will look cool or sum idk
*/

#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <ctime>


int menu();
int gameLoop(bool dbgFlag);
int instructions();
int exit();

struct Card {
	char cardName[6]{" "};
	char cardSuit[9]{" "};
	int cardValue{0};

};





int main() {
	menu();

	return 0;
}

int menu() {
	char userChoice{ 0 };  //option for the menu
	bool stillDeciding{ true }; 
	bool debugFlag{ false };  //true when user selects debug mode

	int userMoneyPot{ 200 };


	while (stillDeciding)
	{

		std::cout << std::endl << "Menu" << std::endl
			<< "Type 1 to play" << std::endl << "Type 2 for instructions" << std::endl << "type 3 for debug" << std::endl << "type 4 to exit" << std::endl;
		std::cin >> userChoice;
		
		

		switch (userChoice)
		{
		case '1':
		{
			std::cout << std::endl;

			int result{ 0 };
			bool betNotValid{ true };

			//place bet
			int bet{ 0 };
			
			while (betNotValid)
			{
				std::cin.clear();
				std::cin.ignore();


				std::cout << "You have " << userMoneyPot << " in your moneypot" << std::endl;
				std::cout << "\nPlace a bet\n";

				std::cin >> bet;
				if (bet <= 0 || bet > userMoneyPot || std::cin.bad())
				{
					std::cout << "\nInvalid Input\n";     //happens when user doesn't enter an integer, enter less than 0 or more than what they have
					std::cin.clear();
				}
				else
				{
					betNotValid = false;
				}
			}

			
			

			result = gameLoop(debugFlag);		//store the result of the game in a variable 

			switch (result)
			{
			case 1:
				std::cout << "You win!" << std::endl;
				userMoneyPot += bet;
				std::cout << bet << " has been added to your moneypot " << std::endl;
				break;

			case 2:
				std::cout << "You loose" << std::endl;
				userMoneyPot -= bet;
				std::cout << bet << " has been taken from your moneypot " << std::endl;
				break;

			case 3:
				std::cout << "You got the same number as the dealer, you draw" << std::endl;
				break;

			case 4:
				std::cout << "You won with blackjack!" << std::endl;
				userMoneyPot += int(bet * 1.5);
				std::cout << int(bet * 1.5) << " has been added to your moneypot " << std::endl;
				break;

			default:
				break;
			}

			break;
		}

		case '2':
		{
			instructions();
			break;
		}

		case '3':
		{
			debugFlag = true;
			std::cout << "Debug mode turned on";
			break;
		}

		case '4':
		{
			stillDeciding = false;
			exit();
			break;
		}

		default:
			std::cout << "Please enter a valid number" << std::endl;
			userChoice = std::getchar();
			break;
		}
	}



	
	return 0;

}

void createDeck(Card Deck[52]) {
	
	for (int Suit = 0; Suit < 52; Suit += 13)
	{
		for (int Card = 0; Card < 13; Card++)
		{
			if (Card > 9) { Deck[Suit + Card].cardValue = 10; }
			else { Deck[Suit + Card].cardValue = Card + 1; }
			if (Suit == 0) { strcpy_s(Deck[Suit + Card].cardSuit, "Hearts"); }
			if (Suit == 13) { strcpy_s(Deck[Suit + Card].cardSuit, "Diamonds"); }
			if (Suit == 26) { strcpy_s(Deck[Suit + Card].cardSuit, "Clubs"); }
			if (Suit == 39) { strcpy_s(Deck[Suit + Card].cardSuit, "Spades"); }
			switch (Card)
			{
			case 0: {strcpy_s(Deck[Suit + Card].cardName, "Ace"); Deck[Suit + Card].cardValue += 10;  break; }
			case 1: {strcpy_s(Deck[Suit + Card].cardName, "Two"); break; }
			case 2: {strcpy_s(Deck[Suit + Card].cardName, "Three"); break; }
			case 3: {strcpy_s(Deck[Suit + Card].cardName, "Four"); break; }
			case 4: {strcpy_s(Deck[Suit + Card].cardName, "Five"); break; }
			case 5: {strcpy_s(Deck[Suit + Card].cardName, "Six"); break; }
			case 6: {strcpy_s(Deck[Suit + Card].cardName, "Seven"); break; }
			case 7: {strcpy_s(Deck[Suit + Card].cardName, "Eight"); break; }
			case 8: {strcpy_s(Deck[Suit + Card].cardName, "Nine"); break; }
			case 9: {strcpy_s(Deck[Suit + Card].cardName, "Ten"); break; }
			case 10: {strcpy_s(Deck[Suit + Card].cardName, "Jack"); break; }
			case 11: {strcpy_s(Deck[Suit + Card].cardName, "Queen"); break; }
			case 12: {strcpy_s(Deck[Suit + Card].cardName, "King"); break; }
			default: break;
			}
			}
		}

}

void shuffleDeck(Card Deck[52]) {
	srand(time(0));
	int i{ 0 };
	int n{ 0 };
	Card tempCard{ 0 };

	for (i=0; i < 10; i++) {
		

		for ( n = 0; n < 52; n++)
		{
			int r = rand() % 52;

			//save card to a temporary card
			strcpy_s(tempCard.cardName, Deck[n].cardName);
			strcpy_s(tempCard.cardSuit, Deck[n].cardSuit);
			tempCard.cardValue = Deck[n].cardValue;

			//swap cards
			strcpy_s(Deck[n].cardName, Deck[r].cardName);
			strcpy_s(Deck[n].cardSuit, Deck[r].cardSuit);
			Deck[n].cardValue = Deck[r].cardValue;

			strcpy_s(Deck[r].cardName, tempCard.cardName);
			strcpy_s(Deck[r].cardSuit, tempCard.cardSuit);
			Deck[r].cardValue = tempCard.cardValue;
			
		}
		
	}
}



int gameLoop(bool dbgFlag) {

/*
Returns 0 as default
		1 if the player wins
		2 if the delear wins
		3 for a draw
		4 if the player wins with blackjack


		Sleep() function used to stop an overwhleming amount of text being displayed to the user all at once 
*/

	//Create and shuffle the deck
	Card Deck[52];
	createDeck(Deck);
	shuffleDeck(Deck);

	int topOfDeck{ 0 };
	
	//give cards to dealer and player
	Card dealerCards[10]{0};
	Card playerCards[10]{0};

	dealerCards[0] = Deck[0];
	playerCards[0] = Deck[1];
	dealerCards[1] = Deck[2];
	playerCards[1] = Deck[3];

	topOfDeck = 4;
	
	int playerTotal = playerCards[0].cardValue + playerCards[1].cardValue;
	int dealerTotal = dealerCards[0].cardValue + dealerCards[1].cardValue;

	/*
	for (int i = 0; i < 52; i++) {
		std::cout << Deck[i].cardSuit;
		std::cout << Deck[i].cardName;
	}
	*/

	//tell the player what cards are on the table
	std::cout << "the dealer has a " << dealerCards[0].cardName << " of " << dealerCards[0].cardSuit << " and another hidden card" << std::endl;

	std::cout << "your cards are " << playerCards[0].cardName << " of " << playerCards[0].cardSuit << " and " << playerCards[1].cardName << " of " << playerCards[1].cardSuit
		<< std::endl << "for a total of: " << playerTotal << std::endl;

	if (dbgFlag)
	{
		std::cout << std::endl << "Delear: " << dealerCards[0].cardValue << " " << dealerCards[1].cardValue << std::endl
			<< "Player: " << playerCards[0].cardValue << " " << playerCards[1].cardValue << std::endl << std::endl;
	}
	
	Sleep(1000);

	//stage one: the player's turns 
	int p_numOfAces{ 0 };

	int nextPlayerCard{ 2 };

	bool stand{ false };  //set to true if user decides to stand with their cards

	char playerChoice{'x'};
	
	while (playerTotal < 21 && stand == false)
	{

		std::cout << "Would you like another card: y/n" << std::endl;
		std::cin >> playerChoice;

		try {


			switch (playerChoice)
			{
			case 'y':
				playerCards[nextPlayerCard] = Deck[topOfDeck];

				for (int i = nextPlayerCard; i < 10; i++)
				{
					playerTotal += playerCards[i].cardValue;

					if (playerCards[i].cardName[0] == 'A')
					{
						p_numOfAces++;
					}
				}

				if (playerTotal > 21 && p_numOfAces != 0) //if they have an ace and are over 21 the ace will be converted from 11 to 1
				{
					playerTotal -= 10;
					p_numOfAces -= 1;
				}

				std::cout << "Your new card is " << playerCards[nextPlayerCard].cardName << " of " << playerCards[nextPlayerCard].cardSuit << " for a total of: " << playerTotal << std::endl
					<< std::endl;

				Sleep(1000);

				nextPlayerCard++;
				topOfDeck++;

				break;


			case 'n':

				stand = true;

				break;


			default:
				throw 101;
				break;

			}
		}

		catch(int wrongInp) {
			std::cout << "please only enter either y or n" << std::endl << std::endl;

		}



	}

	if (playerTotal > 21) //check if player has gone bust
	{
		return 2;
	}

	std::cout << "Moving on..." << std::endl << std::endl;
	

	//Stage 2: the dealer's turns 
	
	int d_numOfAces{ 0 };

	int nextDealerCard{ 2 };
	
	std::cout << "the dealer's cards are: " << dealerCards[0].cardName << " of " << dealerCards[0].cardSuit << " and the " <<
		dealerCards[1].cardName << " of " << dealerCards[1].cardSuit << std::endl
		<< "giving them a total of " << dealerTotal << std::endl << std::endl;

	Sleep(1000);

	while (dealerTotal < 17) //the dealer takes a new card if they are below 17
	{
		dealerCards[nextDealerCard] = Deck[topOfDeck];
		dealerTotal += dealerCards[nextDealerCard].cardValue;

		Sleep(1000);   

		std::cout << "The dealer has pulled " << dealerCards[nextDealerCard].cardName << " of " << dealerCards[nextDealerCard].cardSuit
			<< std::endl << "This brings their total to " << dealerTotal << std::endl << std::endl;


		for (int i = nextDealerCard; i < 10; i++)
		{

			if (dealerCards[i].cardName[0] == 'A')
			{
				d_numOfAces++;
			}
		}

		

		if (dealerTotal > 21 && d_numOfAces != 0)  //if the dealer is over 21 but has an ace
		{
			dealerTotal -= 10;
			d_numOfAces--;

		}

		nextDealerCard++;
		topOfDeck++;
	}

	Sleep(1000);

	if (dealerTotal > 21)   //check if dealer has gone bust
	{
		return 1;
	}

	//stage 3: deciding who has won (if no one has lost)
	if (playerTotal > dealerTotal)
	{
		if (playerTotal == 21)
		{
			return 4;
		}
		else {
			return 1;
		}
		
	}

	if (playerTotal < dealerTotal)
	{
		return 2;
	}

	if (playerTotal == dealerTotal)
	{
		return 3;
	}
	else
	{
		return 0;
	}

	
}

int instructions() {
	std::cout << "The goal of the game is to get close to or reach 21 without going over it." << std::endl
		<< "You will be given two cards and will be given the choice to pick up another card." << std::endl;
	menu();
	return 0;
}

int exit() {
	std::cout << "Okay, goodbye!";
	return 0;
}	