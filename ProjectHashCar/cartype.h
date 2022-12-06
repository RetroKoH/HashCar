#ifndef CAR_TYPE
#define CAR_TYPE

// Author: Benjamin Hoppe
// Date 12/02/2022

#include <iostream>		// cout
#include <algorithm>
#include <stdlib.h>		// rand
using namespace std;
const int MAX_CARS = 20;

// Colors
enum ColorType { WHITE, BLACK, GRAY, RED, GREEN, BLUE, GOLD, SILVER, BROWN };
const string colors[9] = { "White", "Black", "Gray", "Red", "Green", "Blue", "Gold", "Silver", "Brown" };

// Makes and Models
enum MakeType { CHEVY, FORD, TOYOTA, VOLKSWAGEN, HONDA, DODGE };
const string makes[6] = { "Chevy", "Ford", "Toyota", "Volkswagen", "Honda", "Dodge"};

// Car model names (Each make has 5 default model names)
const string models[6][5] = {
	{ "Corvette", "Suburban", "Camaro", "Malibu", "Tahoe" },
	{ "Fiesta", "Escort", "Taurus", "Mustang", "Explorer" },
	{ "Camry", "Corolla", "Tacoma", "Crown", "Century" },
	{ "Santana", "Polo", "Beetle", "Jetta", "Passat" },
	{ "Civic", "Accord", "Legend", "Integra", "City" },
	{ "Challenger", "Charger", "Neon", "Viper", "Ram" }
};

class CarType
{
public:
	// Constructors
	CarType();					// Default constructor
	CarType(int, int, string, string, ColorType, int);

	// Methods
	void Clear();				// Function: Resets values of CarType
	int GetYear();				// Function: Returns year
	int GetMileage();			// Function: Returns mileage
	string GetMake();			// Function: Returns make
	string GetModel();			// Function: Returns model
	ColorType GetColor();		// Function: Returns color
	int GetID();				// Function: Returns ID
	void SetYear(int);			// Function: Sets year
	void SetMileage(int);		// Function: Sets mileage
	void SetMake(string);		// Function: Sets make
	void SetModel(string);		// Function: Sets model
	void SetColor(ColorType);	// Function: Sets color
	void SetID(int);			// Function: Sets ID

	// Overloaded operators
	friend bool operator==(const CarType&, const CarType&);	// Function: Compares ID to other Car's ID
	friend bool operator==(const CarType&, const int);		// Function: Compares ID to immediate integer
	friend ostream& operator<<(ostream&, const CarType);	// Function: Outputs Car data to console

private:
	int year;        // Holds the year.
	int mileage;     // Holds the mileage.
	string make;     // Holds the make.
	string model;    // Holds the model.
	ColorType color; // Holds the color.
	int ID;          // Holds the ID used for hashing.
};
#endif

CarType::CarType() {
	// Default Constructor

	year = 2022;
	mileage = 0;
	make = "BLANK";
	model = "BLANK";
	color = BLACK;
	ID = -1;			// Empty Item
}

CarType::CarType(int inYear, int inMileage, string inMake, string inModel,
				 ColorType inColor, int inID) {
	// Secondary Constructor -- For Add Car feature

	year = inYear;
	mileage = inMileage;
	make = inMake;
	model = inModel;
	color = inColor;
	ID = inID;
}

void CarType::Clear() {
	// Function: Resets values of CarType
	// Pre:		 CarType has been initialized.
	// Post:	 Members have been reverted to default values.

	year = 2022;
	mileage = 0;
	make = "BLANK";
	model = "BLANK";
	color = BLACK;
	ID = -1;			// Empty Item
}

int CarType::GetYear() {
	// Function: Returns year
	// Pre:		 Object has been initialized.
	// Post:	 Returns class member year.

	return year;
}

int CarType::GetMileage() {
	// Function: Returns mileage
	// Pre:		 Object has been initialized.
	// Post:	 Returns class member mileage.

	return mileage;
}

string CarType::GetMake() {
	// Function: Returns make
	// Pre:		 Object has been initialized.
	// Post:	 Returns class member make.

	return make;
}

string CarType::GetModel() {
	// Function: Returns model
	// Pre:		 Object has been initialized.
	// Post:	 Returns class member model.

	return model;
}

ColorType CarType::GetColor() {
	// Function: Returns color
	// Pre:		 Object has been initialized.
	// Post:	 Returns class member color.

	return color;
}

int CarType::GetID() {
	// Function: Returns ID number
	// Pre:		 Object has been initialized.
	// Post:	 Returns class member ID.

	return ID;
}

void CarType::SetYear(int inputYear) {
	// Function: Sets year
	// Pre:		 Object has been initialized.
	// Post:	 Sets value of class member year.

	year = inputYear;
}

void CarType::SetMileage(int inputMileage) {
	// Function: Sets mileage
	// Pre:		 Object has been initialized.
	// Post:	 Sets value of class member mileage.

	mileage = inputMileage;
}

void CarType::SetMake(string inputMake) {
	// Function: Sets make
	// Pre:		 Object has been initialized.
	// Post:	 Sets value of class member make.

	make = inputMake;
}

void CarType::SetModel(string inputModel) {
	// Function: Sets model
	// Pre:		 Object has been initialized.
	// Post:	 Sets value of class member model.

	model = inputModel;
}

void CarType::SetColor(ColorType colInput) {
	// Function: Sets color
	// Pre:		 Object has been initialized.
	// Post:	 Sets value of class member color.

	color = colInput;
}

void CarType::SetID(int idInput) {
	// Function: Sets ID
	// Pre:		 Object has been initialized.
	// Post:	 Sets value of class member ID.

	ID = idInput;
}

bool operator==(const CarType& lhs, const CarType& rhs) {
	// Function: Compares ID to other Car's ID
	// Pre:  Both objects have been initialized.
	// Post: Retruns true if ID's are equal. False otherwise.

	return (lhs.ID == rhs.ID);
}

bool operator==(const CarType& lhs, const int val) {
	// Function: Compares ID to immediate integer
	// Pre:  Object has been initialized.
	// Post: Retruns true if ID == val. False otherwise.

	return (lhs.ID == val);
}

ostream& operator<<(ostream& out, const CarType car) {
	// Function: Outputs Car data to console
	// Pre:  Object has been initialized.
	// Post: Prints out CarType members.

	out << "#" << car.ID << endl;
	out << "Car: " << car.make << " " << car.model << endl;
	out << "Car year: " << car.year << endl;
	out << "Car color: " << colors[car.color] << endl;
	out << "Car mileage: " << car.mileage << endl;
	return out;
}