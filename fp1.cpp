//******************************************************************************
// Author:			Mike Winebarger
// Assignment:		Final Practice 1
// Date:			March 15, 2022
// Description:		This program simulates a shopping cart
// Input:			Char array name; Float cost; Integer qty, option, choice
// Output:			Various textual outputs
// Sources:			Final Practice 1 Documentation
//******************************************************************************
#include "Cart.h"
#include <iostream>
#include <cstring>
using namespace std;

int main() {
	Product cart[MAX];
	int numItems = 0;
	int option = 0;
	bool didCheck = false;
	double total = 0.0;

	welcome();

	while (option != 6) {
		printMenu();
		getOption(option);

		switch (option) {
		case 1:
			addItem(cart, numItems, total, didCheck);
			break;
		case 2:
			removeItem(cart, numItems, total, didCheck);
			break;
		case 3:
			modifyItem(cart, numItems, total);
			break;
		case 4:
			printCart(cart, numItems, total);
			break;
		case 5:
			checkout(cart, numItems, didCheck, total);
			break;
		case 6:
			// Forces checkout if user tries to leave with unpaid balance
			if ((numItems > 0) && !didCheck) {
				cout << "\nTHIEF!! YOU MUST CHECKOUT BEFORE LEAVING THE STORE!!\n" << endl;
				checkout(cart, numItems, didCheck, total);
			}
			else {
				goodbye();
			}
		default:
			break;
		}
	}
}