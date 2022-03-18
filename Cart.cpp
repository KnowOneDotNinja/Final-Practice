#include "Cart.h"
#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

// Name:			welcome()
// Description:		Prints welcome message
// Parameters:		None
// Input:			None
// Output:			Textual message
// Return:			None
void welcome() {
	cout << "     Welcome to your Shopping Cart!\n" << endl;
	cout << "\nThis program allows you to add items to a virtual shopping cart" << endl;
}


// Name:			printMenu()
// Description:		Prints the menu
// Parameters:		None
// Input:			None
// Output:			Textual menu
// Return:			None
void printMenu() {
	cout << "\nPlease select from the options below (1-6):\n" << endl;
	cout << "1) Add Item" << endl <<
		"2) Remove Item" << endl <<
		"3) Modify Item" << endl <<
		"4) List Cart Contents" << endl <<
		"5) Checkout" << endl <<
		"6) Leave store" << endl;
}


// Name:			getOption()
// Description:		Gets and verifies menu choice
// Parameters:		Integer option by reference
// Input:			Integer option
// Output:			Error message on failed input
// Return:			None
void getOption(int &option) {
	cout << ">> ";
	cin >> option;

	// Validate user option
	while (!option || (option <= 0) || (option > 6)) {
		cout << "Invalid choice. Please enter 1-6." << endl;
		cin.clear();
		cin.ignore(100, '\n');
		cout << ">> ";
		cin >> option;
	}
}


// Name:			addItem()
// Description:		Adds a new item to the cart
// Parameters:		Product array cart, Integer numItems by reference
// Input:			Product data
// Output:			Textual prompts
// Return:			None
void addItem(Product cart[], int &numItems, double &total, bool &didCheck) {
	Product newItem;

	// Get and verify user input to populate struct
	cin.ignore(1, '\n');
	cout << "\nEnter name of item to add: ";
	cin.getline(newItem.name, MAX);

	cout << "Enter price of item to add: $";
	cin >> newItem.cost;
	while (!newItem.cost || (newItem.cost < 0)) {
		cout << "Please enter 0 or greater: $";
		cin.clear();
		cin.ignore(100, '\n');
		cin >> newItem.cost;
	}

	cout << "Enter quantity of item to add: ";
	cin >> newItem.qty;
	while (!newItem.qty || (newItem.qty < 1)) {
		cout << "Please enter 1 or more: ";
		cin.clear();
		cin.ignore(100, '\n');
		cin >> newItem.qty;
	}

	// Add cost to total
	total += static_cast<double>(newItem.cost) * newItem.qty;

	// Add to cart
	cart[numItems] = newItem;

	numItems++;
}


// Name:			removeItem()
// Description:		Removes an item from the cart
// Parameters:		Product array cart, Integer numItems by reference
// Input:			Integer removeChoice
// Output:			Product array cart, Textual prompts
// Return:			None
void removeItem(Product cart[], int &numItems, double &total, bool &didCheck) {
	int choice = 0, remIndex = 0;

	// Print cart for user reference
	printCart(cart, numItems, total);

	cout << "Which item would you like to remove: ";
	cin >> choice;

	// Verify user choice
	while ((choice > numItems) || (choice < 1)) {
		cout << "Invalid option. Please enter 1-" << numItems << ": ";
		cin.clear();
		cin.ignore(100, '\n');
		cin >> choice;
	}

	// Set index of item to remove
	remIndex = choice - 1;

	// Update total
	total = total - static_cast<double>(cart[remIndex].cost) * cart[remIndex].qty;

	// Shift elements in struct array
	for (remIndex; remIndex < numItems; ++remIndex) {
		cart[remIndex] = cart[remIndex + 1];
		numItems--;
	}

	// Print cart to verify removal
	printCart(cart, numItems, total);
	cout << "\nItem removed!" << endl;
}


// Name:			modifyItem()
// Description:		Modifies item in the cart
// Parameters:		Product array cart, Integer numItems
// Input:			Product data
// Output:			Textual prompts
// Return:			None
void modifyItem(Product cart[], int numItems, double &total) {
	int num = 0, modIndex = 0;

	// Print cart for user reference
	printCart(cart, numItems, total);
	cout << "Which item would you like to modify: ";
	
	cin >> num;

	// Verify user choice
	while (!num || (num < 1) || (num > numItems)) {
		cout << "Invalid item number. Please enter 1-" << numItems << ": ";
		cin.clear();
		cin.ignore(100, '\n');
		cin >> num;
	}

	// Set index of item to modify
	modIndex = num - 1;

	// Update total to prepare for re-entry
	total -= static_cast<double>(cart[modIndex].cost) * cart[modIndex].qty;

	// Re-populate the proper struct object
	cin.ignore(1, '\n');
	cout << "Enter name: ";
	cin.getline(cart[modIndex].name, MAX);

	cout << "Enter price of item to add: $";
	cin >> cart[modIndex].cost;
	while (!cart[modIndex].cost || (cart[modIndex].cost < 0)) {
		cout << "Please enter 0 or greater: $";
		cin.clear();
		cin.ignore(100, '\n');
		cin >> cart[modIndex].cost;
	}

	cout << "Enter quantity of item to add: ";
	cin >> cart[modIndex].qty;
	while (!cart[modIndex].qty || (cart[modIndex].qty < 1)) {
		cout << "Please enter 1 or more: ";
		cin.clear();
		cin.ignore(100, '\n');
		cin >> cart[modIndex].qty;
	}

	// Update total
	total += static_cast<double>(cart[modIndex].cost) * cart[modIndex].qty;
}


// Name:			printCart()
// Description:		Prints the items in the cart
// Parameters:		Product array cart, Integer numItems
// Input:			None
// Output:			Product array cart
// Return:			None
void printCart(Product cart[], int numItems, double total) {
	// Variable to facilitate printing a numbered list
	int itemNum = 1;

	// Print the header
	cout << fixed << showpoint << setprecision(2);
	cout << setw(3) << left << "#" << setw(19) << left << "Name:" << setw(10) << left <<
		" Cost:" << setw(8) << left << "Qty:" << setw(10) << left << "Total:" << endl;
	cout << "----------------------------------------------" << endl;

	// Print cart elements in a numbered list
	for (int i = 0; i < numItems; ++i) {
		cout << setw(3) << left << itemNum << setw(20) << left << cart[i].name <<
			setw(10) << left << cart[i].cost <<	setw(7) << left << cart[i].qty <<
			setw(9) << left << cart[i].cost * cart[i].qty << endl;
		itemNum++;
	}

	// Print cart total
	cout << "\nCart Total: $" << total << endl;

	// Edge case for items paid before printing cart
	if ((numItems > 0) && (total == 0.0)) {
		cout << "You have already paid for these items." << endl;
	}
}


// Name:			checkout()
// Description:		Runs a checkout system
// Parameters:		Product array cart, Integer numItems, Bool didCheck
// Input:			Double payAmt
// Output:			Textual prompts
// Return:			None
void checkout(Product cart[], int numItems, bool &didCheck, double &total) {
	cout << fixed << showpoint << setprecision(2);

	// Print cart
	printCart(cart, numItems, total);

	// Display checkout message
	cout << "\nYour account has been charged $" << total <<
		". You are free to go!" << endl;

	// Set referenced variables for other functions
	total = 0.0;
	didCheck = true;
}


// Name:			goodbye()
// Description:		Prints goodbye message
// Parameters:		None
// Input:			None
// Output:			Textual message
// Return:			None
void goodbye() {
	cout << "\nThank you for using Your Shopping Cart!" << endl;
}