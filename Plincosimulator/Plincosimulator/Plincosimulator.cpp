/*Joseph Steed, Section 003, josephsteed177@gmail.com, I did true pair programming with 
Ronald Christian Ahrens, Section 006, cahrens8100@gmail.com I did true pair programming with Joseph Steed. 
We developed this in Visual studio.
*/


#include<iostream>
#include<cstdlib>
#include <iomanip>

using namespace std;



int main() {
	

	const int DROP_SINGLE_CHIP = 1;
	const int DROP_MUL_CHIP = 2;
	const int SHOW_MENU = 3;
	const int QUIT = 4;
	const int RANDOM_SEED = 42;
	const double Winnings08 = 100.00;
	const double Winnings17 = 500.00;
	const double Winnings26 = 1000.00;
	const double Winnings35 = 0.00;
	const double Winnings4 = 10000.00;
	const double chipLeft = -0.5;
	const double chipRight = 0.5;
	double chipPath = 0.0;
	int userInput = 3;
	
	cout << "Welcome to the Plinko simulator!  Enter 3 to see options." << endl;
	cout << endl;
	srand(RANDOM_SEED);

	do {
		int tempInt;
		cout << "Enter your selection now: " << endl;
		cout << endl;
		cin >> tempInt; 
		userInput = tempInt; 
		cin.ignore();
		
		if (userInput == DROP_SINGLE_CHIP) {
			cout << "*** Drop a single chip ***" << endl; 
			cout << endl;
			cout << "Which slot do you want to drop the chip in (0-8)? " << endl;
			cout << endl;
			int chipSlot; 
			cin >> chipSlot; 
			if (chipSlot >= 0 && chipSlot <= 8) {
				cout << "*** Dropping chip into slot " << chipSlot << " ***" << endl;
				cout << endl; 
				chipPath = static_cast<double>(chipSlot);
				cout << "Path: [" << fixed << setprecision(1) << chipPath;
				for (int i = 0; i < 12; ++i) {
					if (chipPath == 8.0) {
						chipPath = chipPath + chipLeft;
					}
					else if (chipPath == 0.0) {
						chipPath = chipPath + chipRight;
					}
					else {
						int rand01; 
						rand01 = rand() % 2;
						if (rand01 == 0) {
							chipPath = chipPath + chipLeft;
						}
						else if (rand01 == 1) {
							chipPath = chipPath + chipRight; 
						}
					}
					cout << fixed << setprecision(1) << ", " << chipPath; 
				}
				cout << "]" << endl; 
				cout << "Winnings: $";
				if (chipPath == 0.0|| chipPath == 8.0) {
					cout << fixed << setprecision(2) << Winnings08 << endl;
				}
				else if (chipPath == 1.0 || chipPath == 7.0) {
					cout << fixed << setprecision(2) << Winnings17 << endl;
				}
				else if (chipPath == 2.0 || chipPath == 6.0) {
					cout << fixed << setprecision(2) << Winnings26 << endl;
				}
				else if (chipPath == 3.0 || chipPath == 5.0) {
					cout << fixed << setprecision(2) << Winnings35 << endl;
				}
				else{
					cout << fixed << setprecision(2) << Winnings4 << endl;
				}
				cout << endl;
			}
			else {
				cout << "Invalid slot." << endl; 
				cout << endl; 
			}	

		}
		else if (userInput == DROP_MUL_CHIP) {
			cout << "*** Drop multiple chips ***" << endl; 
			cout << endl;
			int numChips = 1;
			cout << "How many chips do you want to drop (>0)? " << endl;
			cout << endl; 
			cin >> numChips;
			if (numChips > 0) {
				cout << "Which slot do you want to drop the chip in (0-8)? " << endl;
				cout << endl;
				int chipSlot;
				cin >> chipSlot;
				if (chipSlot >= 0 && chipSlot <= 8) { 
					double sumWinnings = 0.0;
					double winnings = 0.0;
					for (int i = 0; i < numChips; ++i) {
						chipPath = static_cast<double>(chipSlot);
						for (int i = 0; i < 12; ++i) {
							if (chipPath == 8.0) {
								chipPath = chipPath + chipLeft;
							}
							else if (chipPath == 0.0) {
								chipPath = chipPath + chipRight;
							}
							else {
								int rand01;
								rand01 = rand() % 2;
								if (rand01 == 0) {
									chipPath = chipPath + chipLeft;
								}
								else if (rand01 == 1) {
									chipPath = chipPath + chipRight;
								}
							}
							if (chipPath == 0.0 || chipPath == 8.0) {
								winnings = Winnings08; 
						
							}
							else if (chipPath == 1 || chipPath == 7) {
								winnings = Winnings17; 
							}
							else if (chipPath == 2 || chipPath == 6) {
								winnings = Winnings26;
							}
							else if (chipPath == 3 || chipPath == 5) {
								winnings = Winnings35; 
							}
							else {
								winnings = Winnings4; 
							}
							
						}
						sumWinnings = sumWinnings + winnings; 
					}
					cout << "Total winnings on " << numChips << " chips: $";
						cout << fixed << setprecision(2) << sumWinnings << endl;
					double aveWinning = (sumWinnings) / numChips; 
					cout << "Average winnings per chip: $" << aveWinning << endl;
					cout << endl;
				}
				else {
					cout << "Invalid slot." << endl;
					cout << endl;
				}
			
			}
			else {
				cout << "Invalid number of chips." << endl;
				cout << endl;
			}
		} 
		else if (userInput == SHOW_MENU) {
			cout << "Menu: Please select one of the following options: " << endl; 
			cout << endl; 
			cout << "1 - Drop a single chip into one slot" << endl;
			cout << "2 - Drop multiple chips into one slot" << endl;
			cout << "3 - Show the options menu" << endl;
			cout << "4 - Quit the program" << endl;
			cout << endl;
		}
		else if (userInput <= 0 || userInput >= 5){
			cout << "Invalid selection. Enter 3 to see options." << endl;
			cout << endl;
		}
	}
	while (userInput != QUIT);
		cout << "Goodbye!";
		//system("PAUSE");
	
	return 0; 
	
}

