// TowerHannoiGame.cpp : Defines the entry point for the console application.
//

#include "StackQueue.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class TowersOfHannoiGame
{
public:
	TowersOfHannoiGame(int disks) : m_GameEnded(false), numDisks(disks) //loads the towers for the game
	{
		for (int i = numDisks; i >= 1; i--){
			towers[0].push(i);
		}
		
	}

	bool IsGameEnded() { return m_GameEnded; } //checks if game has ended

	void PrintTowers()
{
    for (int i = 0; i < 3; i++)
    {
        std::cout << "Tower " << i + 1 << ": ";

        ArrayBasedStack& tower = towers[i];
        ArrayBasedStack tempStack;  // Create a temporary stack to hold the elements

        while (!tower.isEmpty())
        {
            int disk = tower.peek();
			tower.pop();
            tempStack.push(disk);  // Push elements to the temporary stack
        }

        while (!tempStack.isEmpty())
        {
            int disk = tempStack.peek();
			tempStack.pop();  // Pop elements back to the original stack
			std::cout << disk << " ";
		    tower.push(disk);
        }

        if (tower.isEmpty())
        {
            std::cout << "Empty";
        }

        std::cout << std::endl;
    }
}

	
	void startGame() {
	cout << "Enter in moves to make for Towers  of  Hannoi" << endl;
	cout << "Progam will exit once towers have  been successfully moved of" << endl;
	cout << "or string of -1 is entered. Moves must be entired in format of" << endl;
	cout << "<disk>,<column from>,<column to>   NOTE no spaces!!!!" << endl;

	

	bool receivedEndToken = false;

	while (!receivedEndToken && !IsGameEnded()) //checks if game has ended. if game is going, asks user to enter move. 
	{
		std::string inputLine;
		PrintTowers();
		cout << "Enter Move: " << endl;
		getline(cin, inputLine);
		if (inputLine == "-1") //if game is over, sets the EndToken to true and ends the game.
		{
			receivedEndToken = true;
		}
		else
		{
			std::vector<std::string> output;
			std::string::size_type prev_pos = 0, pos = 0;
			// Snippet from https://stackoverflow.com/questions/5167625/splitting-a-c-stdstring-using-tokens-e-g
			// tokenizing a string
			while ((pos = inputLine.find(",", pos)) != std::string::npos)
			{
				std::string substring(inputLine.substr(prev_pos, pos - prev_pos));
				output.push_back(substring);
				prev_pos = ++pos;
			}
			//Need to get last token
			output.push_back(inputLine.substr(prev_pos, pos - prev_pos)); // Last word

			if (output.size() != 3)
			{
				receivedEndToken = true;
				cout << "Invalid input recieved = " + inputLine << endl;
			}
			else
			{
				std::string disk = output[0];
				std::string from = output[1];
				std::string to = output[2];

				if (disk.size() == 0 || from.size() == 0 || to.size() == 0) //checks to see if input is valid
				{
					receivedEndToken = true;
					cout << "Invalid input recieved = " + inputLine << endl;
				}

				int diskId = atoi(disk.c_str()); 
				int fromId = atoi(from.c_str());
				int toId = atoi(to.c_str());
				//if any number is zero we didn't have a integer
				if (diskId == 0 || fromId == 0 || toId == 0)
				{
					receivedEndToken = true;
					cout << "Invalid input recieved = " + inputLine << endl;
				}
				moveDisk(diskId, fromId, toId);
				cout << "Disk " << diskId << " From " << fromId << " To " << toId << endl;
				

				

			}
		}



	}
	printMovestoFile("moves.txt");
	};

	bool moveDisk(int diskId, int fromId, int toId){
		if (diskId <= 0 || diskId > numDisks || fromId < 1 || fromId > 3 || toId < 1 || toId > 3 || fromId == toId) {
        return false;
    }

    ArrayBasedStack& startTower = towers[fromId - 1];
    ArrayBasedStack& destinationTower = towers[toId - 1];

    // Check if the source tower is empty or if the move violates the rules (larger disk on top of a smaller disk)
    if (startTower.isEmpty() || (!destinationTower.isEmpty() && startTower.peek() > destinationTower.peek())) {
		return false; // Invalid move
    }

    // Move the disk from the source tower to the destination tower
    int diskToMove = startTower.peek();
	startTower.pop();
    destinationTower.push(diskToMove);

    // Update the move queue with the move information
    std::string moveInfo = std::to_string(diskToMove) + "," + std::to_string(fromId) + "," + std::to_string(toId);
    moveQueue.enQueue(moveInfo);

    // Check if the game is won (all disks moved to another tower)
    if (towers[2].size() == numDisks) {
		cout << "You win!" << endl;
        m_GameEnded = true;
    }

    return true; // Valid move
}
	
	void printMovestoFile(const std::string moves){ //prints the moves to the required file
		std::ofstream outputFile(moves.c_str());

		if (outputFile.is_open()){ //checks if output file os open, if it is prints all the moves to the file.
			while (!moveQueue.isEmpty()){
				std::string move = std::to_string(moveQueue.deQueue());
				outputFile << move << std::endl;
			}
			outputFile.close();
			std::cout << "Moves have been saved to " << moves << std::endl;
		}else { 
			std::cerr << "Unable to open file " << moves << std::endl;
		}
	}


	

private:
	bool m_GameEnded;
	int numDisks;
	ArrayBasedStack towers[3];
	ArrayBasedQueue moveQueue;

};

int main()
{
	int numDisks = 4;
	TowersOfHannoiGame game(numDisks);
	game.startGame();
	
    return 0;
}

