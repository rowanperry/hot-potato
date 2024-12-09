#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

const int LENOFTOPPINGS = 8;
const string toppingsNames[LENOFTOPPINGS] = { "cheese", "butter", "garlic-butter","beans", "curry-sauce","mushrooms", "onions","extra-special-cheese" };
const double toppings[LENOFTOPPINGS] = { 1.0, 0.4, 0.5, 0.75, 1.20, 0.8, 0.4, 1.5 };

const int LENOFEXTRAS = 6; 
const string extrasNames[LENOFEXTRAS] = {"salad-box", "hot-dog", "fizzy-drink", "water", "tea", "coffee"};
const double extras[LENOFEXTRAS] = {1.50, 4.0, 1.2, 0.8, 1.0, 1.2};

void title(string text) {
	cout << "----------------------------------------------------------------" << endl;
	cout << "             " << text << endl;
	cout << "----------------------------------------------------------------" << endl;
}
//formating function displays text in a Menu like style easily

void display(double Icredits, double ItotalCredits, bool clear) {
	cout << endl << "Your Credits balance is: " << Icredits;
	cout << endl << "Your Order Currently costs: " << ItotalCredits << endl << endl;
	if (clear) {
		system("pause");
		system("cls");
	}
}
//formatting function displays the current order status, is clear is passed as true it will clear the screen as well 

string ToLower(string myString) {
	string lowerString;
	for (auto c : myString) lowerString += tolower(c);
	return lowerString;
}
//converts inputs to lower case

int isInputInList(bool arrayCheck[], const string array[],  const double arrayPrice[], int MAX) {
	int temp = 0;
	string inputString;
	cin >> inputString;
	ToLower(inputString);
	for (int i=0;i<MAX;i++) {
		if (inputString == array[i]) {
			temp = i;
			break;
		}
	}
	if (temp >= 0 && temp < MAX) {
		cout << "You chose the " << array[temp] << ", it Costs: " << arrayPrice[temp] << endl;
		arrayCheck[temp] = true;
		return temp;
	}
	return -1;
}
//takes user input and checks the input with all the array contents in the passed array
//returns the place in the array, or -1 for not found
 
bool yesOrNoFUNC() {
	bool funcValidated = false;
	string yesORno;
	do {
		cout << "y/n" << endl;
		cin >> yesORno;
		yesORno = ToLower(yesORno);
		if (yesORno == "y") {
			return false;
			funcValidated = true;
		}
		else if (yesORno == "n") {
			return true;
			funcValidated = true;
		}
	} while (!funcValidated);
}
//used to stop the repeat of y/n questions code 

void listOutput(bool arrayCheck[], const string array[], const double arrayPrice[], int MAX) {
	for (int i = 0;i < MAX;i++) {
		if (arrayCheck[i] == false) {
			cout << "             -" << array[i] << " = " << arrayPrice[i] << endl;
		}
	}
	cout << "----------------------------------------------------------------" << endl;
}
//outputs the list of items; arraycheck checks if that item has been orderd doesnt display it if it has, 
//array displays the name of the item, arrayPrice displays the price, and MAX is used to represent the size of the array how many loops are needed

//--------------------------------//                      
        //MAIN CODE BLOCK//
//--------------------------------//
int main() {
	double credits;
	double totalCredits = 0.0;
	string size;
	bool validated = false;

	bool toppingsHasOrdered[LENOFTOPPINGS] = { false,false,false,false,false,false,false,false };
	bool extraHasOrdered[LENOFEXTRAS] = { false,false,false,false,false,false };
	//toppings arrays

	while (!validated) {
		title("Hot Potato \n             Enter Credits: ");
		cin >> credits;
		while (cin.fail() || credits < 0) {
			cin.clear();
			cin.ignore(80, '\n');

			cout << "Please Enter a valid credits number: "<< endl;
			cin >> credits;
		}
		cout << fixed << setprecision(2);
		cout << endl << "Your Credits balance: " << credits << endl << endl;
		validated = true;
		//Credit entry and validation, accepts doubles but not non numbers
		//set precision makes the decimals truncate to two points so the credits can act as currency
	}
	system("pause");
	system("cls");
	//used to clear screen

	title("Size Selection");
	validated = false;
	do {
		title("What Size would you like...\n             small (5.00) / medium (8.50) / large (10.25)... ?");
		cin >> size;
		size = ToLower(size);
		if (size == "small") {
			totalCredits = totalCredits + 5.0;
			validated = true;
		}
		if (size == "medium") {
			totalCredits = totalCredits + 8.5;
			validated = true;
		}
		if (size == "large") {
			totalCredits = totalCredits + 10.25;
			validated = true;
		}
		else {
			size = "";
		}
	} while (!validated);
	//takes and converts input into lower case, then compares it the the sizes and adds the prices of which to your TotalCredits
	cout << "You chose " << size << ", that comes to " << totalCredits << endl;
	display(credits, totalCredits, true);
	//clears page and displays order status, used often ^^^

	title("Topping's Selection");
	display(credits, totalCredits, false);

	validated = false;
	do {
		title("Which topping would you like?...");
		listOutput(toppingsHasOrdered, toppingsNames, toppings, LENOFTOPPINGS);
		//outputs all the toppings

		int toppingNum = isInputInList(toppingsHasOrdered, toppingsNames, toppings, LENOFTOPPINGS);
		totalCredits = totalCredits + toppings[toppingNum];
		//checks if string entered is in the toppings array, if it is then it returns the place in the array that it is so the price can be added
		//adds the price of the selected topping onto the totalcredits and marks the topping as true so it isnt displayed again
		
		display(credits, totalCredits, false);
		cout << "Would you like to add another topping ? ";
		validated = yesOrNoFUNC();
		//function returns wether or not to repeat the toppings loop again
	} while (!validated);
	display(credits, totalCredits, true);

	title("Extra's Selection");
	cout << "Do you want to add an extra? ";
	validated = yesOrNoFUNC();
	//returns wether next block is ran as the extras are optional
	
	while (!validated) {
		title("Which Extra would you like?");
		listOutput(extraHasOrdered, extrasNames, extras, LENOFEXTRAS);
		//outputs all the extras
		int extrasNum = isInputInList(extraHasOrdered, extrasNames, extras, LENOFEXTRAS);
		totalCredits = totalCredits + toppings[extrasNum];
		validated = true;
	}
	display(credits, totalCredits, true);
	validated = false;
	//extra's selecting code

	title("Payment Screen");
	display(credits, totalCredits, false);
	bool paymentSuccess = false;
	// ^^ used for adding credits loop
	
	do {
		if (totalCredits > credits) {
			cout << endl << "ERROR, Not Enough Funds!" << endl;
			cout << "Would you like to enter more credits? ";
			validated = yesOrNoFUNC();
			//lets user add more credits if they do not have enough
			while (!validated) {
				double MoreCredits;
				title("Enter Credits: ");
				cin >> MoreCredits;
				while (cin.fail() || credits < 0) {
					cin.clear();
					cin.ignore(80, '\n');

					cout << "Please Enter a valid credits number: " << endl;
					cin >> MoreCredits;
				}
				cout << "You entered in an additional  " << MoreCredits << " credits" << endl;
				credits = credits + MoreCredits;
				cout << "You now have " << credits << " credits" << endl;
				display(credits, MoreCredits, false);
				validated = true;
			}
		}
		else {
			title("    Payment Successful");
			cout << "Remaining Credits: " << credits - totalCredits << endl;
			paymentSuccess = true;
		}
	} while (!paymentSuccess);
	//check for payment, repeat asking user to add more credits to pay or cancel order
	paymentSuccess = false; //resets so the payment loop can be used be again for new orders/



	//TO ADD//
	// - let customer add more toppings										-----(DONE)-----
	// - add the EXTRAS														-----(DONE)-----
	// - dont display topppings they alr have								-----(DONE)-----
	// - dont display contdicting toppings (e.g butter and garlic butter)
	// - find out a way to not need '-' in two word toppings
	// - make a file and save order (LATE STUFF)
	// - add an overarching menu 
	// - comment and format code better, right now its messy and hard to read
	// - refer to brief
	//TO ADD//
}