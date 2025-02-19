//		Rowan Perry		//
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <fstream> //used for reading and writing into files 
using namespace std;

const int LENOFTOPPINGS = 8; //used to decrease magic numbers
const string toppingsNames[ LENOFTOPPINGS ] = { "cheese", "butter", "garlic-butter","beans", "curry-sauce","mushrooms", "onions","extra-special-cheese" };
const double toppings[ LENOFTOPPINGS ] = { 1.00, 0.40, 0.50, 0.75, 1.20, 0.80, 0.40, 1.50 };

const int LENOFEXTRAS = 6; //used to decrease magic numbers 
const string extrasNames[ LENOFEXTRAS ] = {"salad-box", "hot-dog", "fizzy-drink", "water", "tea", "coffee"};
const double extras[ LENOFEXTRAS ] = {1.50, 4.00, 1.20, 0.80, 1.00, 1.20};

void title(string text) {
	cout << "----------------------------------------------------------------" << endl;
	cout << "             " << text << endl;
	cout << "----------------------------------------------------------------" << endl;
}
//formating function; displays text in a Menu like style easily

void display(double Icredits, double ItotalCredits, bool clear) {
	cout << endl << "Your Credits balance is: " << Icredits;
	cout << endl << "Your Order Currently costs: " << ItotalCredits << endl << endl;
	if (clear) {
		system("pause");
		system("cls");
	}
}
//formatting function; displays the current order status, if clear is passed as true it will clear the screen as well 

string ToLower(string myString) {
	string lowerString;
	for (auto c : myString) lowerString += tolower(c);
	return lowerString;
}
//converts inputs to lower case - (provided by ollie)

void inputFile(string inputString) {
	fstream myfile;
	myfile.open("Orders.txt", fstream::app);	//fstream::app makes amends the file so that it will no write over it
	myfile << inputString;
	myfile.close();
}
//inputs passed string into the file then closes it

int isInputInList(bool arrayCheck[], const string array[],  const double arrayPrice[], int MAX) {
	int temp = 0;
	string inputString;
	cin >> inputString;
	ToLower(inputString);
	for (int i=0; i<MAX; i++) {
		if (inputString == array[i]) {
			temp = i;
			break; //skips to the if statment below
		}
	}
	if (temp >= 0 && temp < MAX) {
		if (!arrayCheck[temp]) {
			cout << "You chose the " << array[temp] << ", it Costs: " << arrayPrice[temp] << endl;
			inputFile(array[temp]);
			inputFile(", ");
			arrayCheck[temp] = true;
			return temp;
		}
		else {
			cout << "You already chose that!" << endl;
			return -1;
		}
	}
	return -1;
}
//takes user input and checks the input with all the array contents in the passed array
//returns the place in the array, or -1 for not found
//uses the inputFile function to add chosen topping into the file

void addCredits(double& number) {
	double input = 0.0;
	title("Enter Credits: ");
	cin >> input;
	while (cin.fail() || input < 0) {
		cin.clear();
		cin.ignore(80, '\n');

		cout << "Please Enter a valid credits number: " << endl;
		cin >> input;
	}
	number = number + input;
	cout << fixed << setprecision(2);
	cout << "You entered in an additional " << input << " credits" << endl;
	cout << "You now have " << number << " credits" << endl;
	cout << endl << "Your Credits balance: " << number << endl << endl;
	//Credit entry and validation, accepts doubles but not non numbers
	//set precision makes the decimals truncate to two points so the credits can act as currency
}
 
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
//used to stop the repeat of y/n questions in code, returns true or false respective of result

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

void outputFile() {
	system("pause");
	system("cls");
	title("Previous Orders");
	ifstream f("Orders.txt");		//opens the file

	if (f.is_open()) {
		cout << f.rdbuf();		//outputs the contents
	}
	else {
		cout << "Error Opening File!" << endl;
	}
	cout << endl;
}

void menu(double& number, bool& loop, bool& loopMenu) {
	int choice = 0;
	title("Hot Potato \n             Please Choose an Option... ");
	cout << endl;
	title("\n             (1)Enter Credits\n             (2)Make Order\n             (3)View Past Orders\n             (4)Exit\n");
	//start menu
	cin >> choice;
	while (cin.fail() || choice <= 0 || choice >= 5) {
		cin.clear();
		cin.ignore(80, '\n');

		cout << "Please Enter a valid choice number: " << endl;
		cin >> choice;
	}
	//validate user input of the menu choice

	if (choice == 1) {
		addCredits(number);
		//runs the credit function, with credits passed through
	}
	else if (choice == 2) {
		loopMenu = true;
		//loopmenu meanns that the whole ordering loop in main is actaully run, if 2 isnt chosen it will skip it and return back to the menu screen
	}
	else if (choice == 3){
		outputFile();
	}
	else if (choice == 4) {
		loop = false;
		loopMenu = true;
		//loop menu means the whole project will not loop as the menu isnt called again and exits the project
	}
	system("pause");
	system("cls");
	//used to clear screen
}

void resetArray(bool array[], int MAX) {
	for (int i = 0;i < MAX;i++) {
		array[i] = false;
	}
}
//sets all values of a passed array to false, used to reset between orders

//--------------------------------//                      
        //MAIN CODE BLOCK//
//--------------------------------//
int main() {
	double credits = 0.0;
	double totalCredits = 0.0;	//order cost
	cout << fixed << setprecision(2); //makes the two above doubles act like currency, without this they will display as whole numbers if credits arnt entered fist
	string size;
	bool validated = false;
	bool continueLoop = true;

	bool toppingsHasOrdered[LENOFTOPPINGS] = { false,false,false,false,false,false,false,false };
	bool extraHasOrdered[LENOFEXTRAS] = { false,false,false,false,false,false };
	// toppings / extra arrays, to stop multiple toppings orders
	
	title("Welcome to...");
	do {
		menu(credits, continueLoop, validated);
		//main menu screen, passed the credits to be changed if chosen
	} while (!validated);
	//this keeps the while loop on so that if a user chooses to add credits they can go back choose another option

	while (continueLoop) {
		title("Size Selection");
		inputFile("		-Order: ");

		fstream myfile;
		myfile.open("OrderNUM.txt");
		int orderNUM;
		myfile >> orderNUM;
		myfile.close();
		//above block opens orderNUM file which contains a single number which is used to hold the value of the current order
		
		orderNUM++;
		inputFile(to_string(orderNUM));
		//adds order number to the actaul orders file after upping it by one

		ofstream myfile2;
		myfile2.open("OrderNUM.txt");
		myfile2 << to_string(orderNUM);
		myfile2.close();
		//rights over the orderNUM file so that the value is changed
		//gets a unqiue number for each order that increases everytime by changing the file contents without amending

		validated = false;
		do {
			title("What Size would you like...\n             -small (5.00)\n             -medium (8.50)\n             -large (10.25)... ?");
			cin >> size;
			size = ToLower(size);
			if (size == "small") {
				totalCredits = totalCredits + 5.00;
				validated = true;
			}
			else if (size == "medium") {
				totalCredits = totalCredits + 8.50;
				validated = true;
			}
			else if (size == "large") {
				totalCredits = totalCredits + 10.25;
				validated = true;
			}
			else {
				size = "";
			}
		} while (!validated);
		//takes and converts input into lower case, then compares it the the sizes and adds the prices of which to TotalCredits
		cout << "You chose " << size << ", that comes to " << totalCredits << endl;
		inputFile("\nSize:     ");
		inputFile(size);
		display(credits, totalCredits, true);
		//clears page and displays order status, used often ^^^

		title("Topping's Selection");
		display(credits, totalCredits, false);
		inputFile("\nToppings: ");

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
		
		inputFile("\nExtras:   ");
		while (!validated) {
			title("Which Extra would you like?");
			listOutput(extraHasOrdered, extrasNames, extras, LENOFEXTRAS);
			//outputs all the extras

			int extrasNum = isInputInList(extraHasOrdered, extrasNames, extras, LENOFEXTRAS);
			totalCredits = totalCredits + toppings[extrasNum];

			display(credits, totalCredits, false);
			cout << "Would you like to add another Extra ? ";
			validated = yesOrNoFUNC();
		}
		display(credits, totalCredits, true);
		validated = false;
		//extra's selecting code

		title("Payment Screen");
		display(credits, totalCredits, false);
		bool paymentSuccess = false;
		// ^^ used for 'adding credits' loop so the user cannot leave that screen until they pay

		do {
			system("pause");
			if (totalCredits > credits) {
				cout << endl << "ERROR, Not Enough Funds!" << endl;
				cout << "Would you like to enter more credits to pay for the order? ";
				validated = yesOrNoFUNC();
				//lets user add more credits if they do not have enough
				while (!validated) {
					addCredits(credits);
					cout << "You now have " << credits << " credits" << endl;
					display(credits, totalCredits, false);
					validated = true;
					//takes input of the new credits entered, adds them to toal then displays the new values
				}
			}
			else if (totalCredits <= credits) {
				title("Payment Successful!");
				cout << "Remaining Credits: " << credits - totalCredits << endl;
				inputFile("\nPrice:    ");
				
				ofstream myfile("Orders.txt", ifstream::app); //append doesnt overwrite file
				cout << fixed << setprecision(2);
				myfile << totalCredits;
				//seperate entry for totalcredits as a double cannot be passed through the input file function
				myfile.close();

				inputFile("\n\n");
				paymentSuccess = true;
				credits = credits - totalCredits;
			}
			//adds orders to the file so that users can view past orders
			
		} while (!paymentSuccess);
		//check for payment, repeat asking user to add more credits to pay or cancel order
		
		validated = false;
		paymentSuccess = false;
		resetArray(toppingsHasOrdered, LENOFTOPPINGS);
		resetArray(extraHasOrdered, LENOFEXTRAS);
		totalCredits = 0.0;
		//reset values for a new potato to be ordered

		cout << endl;
		title("Return to menu...");
		system("pause");
		system("cls");
		do {
			menu(credits, continueLoop, validated);
		} while (!validated);
		//this goes to the menu where the customer can order another potato, add more credits or exit
	}

	title("Goodbye!\n             See you soon...");
	cout << endl;
	title("\n             Enjoy your Meal\n");
	//end screen
}
