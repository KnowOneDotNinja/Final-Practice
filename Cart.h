#pragma once

const int MAX = 21;

// Struct for array items
struct Product {
	char name[MAX];
	float cost;
	int qty;
};

// Function declarations
void welcome();
void printMenu();
void getOption(int&);
void addItem(Product[], int&, double&, bool&);
void removeItem(Product[], int&, double&, bool&);
void modifyItem(Product[], int, double&);
void printCart(Product[], int, double);
void checkout(Product[], int, bool&, double&);
void goodbye();