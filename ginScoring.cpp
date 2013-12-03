
#include "ginScoring.h"
#include <iostream>

using namespace std;

    int winner = 0;
	double bet;
	double winnings;

    void ginScoring::calcScore(ginPlayer &human, ginPlayer &computer){
		int humanWood = human.calcDeadwood();
		int compWood = computer.calcDeadwood();
        if (human.knockers == true){
                if(humanWood < compWood && humanWood == 0){  //bonus awarded if knocker doesn't have any deadwood cards
                    human.score += (compWood - humanWood) + 25;
                }
                else if(humanWood < compWood){
                    human.score += (compWood - humanWood);
                }
                else if(humanWood >= compWood){
                    computer.score += (humanWood - compWood);
                    computer.score += 10;
                }
        }
        if (computer.knockers == true){
                if(compWood < humanWood && compWood == 0){
                    computer.score += (humanWood - compWood) + 25;
                }
                else if(compWood < humanWood){
                    computer.score += humanWood - compWood;
                }
                else if(compWood >= humanWood){
                    human.score += compWood - humanWood;
                    human.score += 10;
                }
        }
     }



    void ginScoring::calcPoints(ginPlayer &human, ginPlayer &computer){
        if(human.score >= 100 && computer.score == 0){
            //cout << "Golly! " << human.name << " wins by a landslide, 200 bonus points awarded, " << endl;
            winner = 1;
            human.score = (human.score + 200);
        }
        else if(human.score >= 100){
            //cout << "Golly! " << human.name << " wins, 100 bonus points awarded" << endl;
            winner = 1;
            human.score = (human.score + 100);
        }

        else if(computer.score >= 100 && human.score == 0){
            //cout << "Golly! " << computer.name << " wins by a landslide, 200 bonus points awarded" << endl;
            winner = 2;
            computer.score = (computer.score + 200);
        }
        else if(computer.score >= 100){
            //cout << "Golly! " << computer.name << " wins, 100 bonus points awarded" << endl;
            winner = 2;
            computer.score = (computer.score + 100);
        }


    }

    void ginScoring::placeBet(ginHuman &player, display &interface, ginDeck &d){
        stringstream messageString;
		string betString;
		char betKey;

		messageString.str("");
		messageString << "Please enter your bet with [0-9] and hit [enter] when you're done" << endl;
		interface.bannerBottom(messageString.str());
		interface.bannerIndex = 1;

		betKey;
		int betNumber;

		while(betKey != '\n') {

			betKey = player.getKey(interface, d);
			betNumber = betKey - '0';

			while(0 <= betNumber && betNumber <= 9 || betKey == '.') {
				betString += betKey;

				messageString.str("");
				messageString << "$" << betString << endl;
				interface.bannerBet(messageString.str());

				betKey = player.getKey(interface, d);
				betNumber = betKey - '0';
			}
		}

		interface.bannerBetClear("");

		bet = atof(betString.c_str());

		messageString.str("");
		messageString << "     Current pot: $" << 2*bet << endl;
		interface.displayText(messageString.str(), 0, 28);
    }


    void ginScoring::calcPayout(ginPlayer &human, ginPlayer &computer, display &interface){
		stringstream messageString;
		messageString.str("");

        if (winner == 1){
            winnings = 2*bet;
            messageString << "Congratulations, " << human.name << "! You win $" << winnings << ". Press any key to quit." << endl;
        }
        else if (winner == 2){
            winnings = 2*bet;
            messageString << "Congratulations, " << computer.name << "! You win $" << winnings << ". Press any key to quit." << endl;
        }
        else{
			messageString << "Nobody has won yet." << endl;
        }

		interface.bannerBottom(messageString.str());
    }

	double ginScoring::getBet() {
		return bet;
	}

	int ginScoring::getWinner(){
		return winner;
	}
