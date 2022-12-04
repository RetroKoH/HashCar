#ifndef CAR_TYPE
#define CAR_TYPE

#include <iostream>		// cout
#include <algorithm>
#include <stdlib.h>		// rand
using namespace std;

// Colors
enum ColorType { WHITE, BLACK, GRAY, RED, GREEN, BLUE, GOLD, SILVER, BROWN };
const string colors[9] = { "White", "Black", "Gray", "Red", "Green", "Blue", "Gold", "Silver", "Brown" };

// Makes and Models
enum MakeType { CHEVY, FORD, TOYOTA, VOLKSWAGEN, HONDA, DODGE };
const string makes[6] = { "Chevy", "Ford", "Toyota", "Volkswagen", "Honda", "Dodge"};

// Car model names
const string models[6][5] = {
	{ "Corvette", "Suburban", "Camaro", "Malibu", "Tahoe" },
	{ "Fiesta", "Escort", "Taurus", "Mustang", "Explorer" },
	{ "Camry", "Corolla", "Tacoma", "Crown", "Century" },
	{ "Santana", "Polo", "Beetle", "Jetta", "Passat" },
	{ "Civic", "Accord", "Legend", "Integra", "City" },
	{ "Challenger", "Charger", "Neon", "Viper", "Ram" }
};

// Used in the hashing process (comparing IDs)
enum RelationType { LESS, GREATER, EQUAL };

class CarType
{
public:
	CarType();
	CarType(int year, int mileage, string make, string model, ColorType color, int ID);
	void Clear();
	int GetYear();
	int GetMileage();
	string GetMake();
	string GetModel();
	ColorType GetColor();
	int GetID();
	void SetYear(int inputYear);
	void SetMileage(int inputMileage);
	void SetMake(string inputMake);
	void SetModel(string inputModel);
	void SetColor(ColorType color);
	void SetID(int idInput);

	friend bool operator==(const CarType& lhs, const CarType& rhs);
	friend bool operator==(const CarType& lhs, const int val);
	friend ostream& operator<<(ostream& out, const CarType car);

private:
	int year;
	int mileage;
	string make;
	string model;
	ColorType color;
	int ID;				// Change to IDType object
};
#endif

// Default Constructor
CarType::CarType() {
	year = 2022;
	mileage = 0;
	make = "BLANK";
	model = "BLANK";
	color = BLACK;
	ID = -1;			// Empty Item
}

// Manually generate a car, if we'd like to.
CarType::CarType(int year, int mileage, string make, string model, ColorType color, int ID) {
	this->year = year;
	this->mileage = mileage;
	this->make = make;
	this->model = model;
	this->color = color;
	this->ID = ID;
}

void CarType::Clear() {
	year = 2022;
	mileage = 0;
	make = "BLANK";
	model = "BLANK";
	color = BLACK;
	ID = -1;			// Empty Item
}

int CarType::GetYear() {
	return year;
}

int CarType::GetMileage() {
	return mileage;
}

string CarType::GetMake() {
	return make;
}

string CarType::GetModel() {
	return model;
}

ColorType CarType::GetColor() {
	return color;
}

int CarType::GetID() {
	return ID;
}

void CarType::SetYear(int inputYear) {
	year = inputYear;
}

void CarType::SetMileage(int inputMileage) {
	mileage = inputMileage;
}

void CarType::SetMake(string inputMake) {
	make = inputMake;
}

void CarType::SetModel(string inputModel) {
	model = inputModel;
}

void CarType::SetColor(ColorType colInput) {
	color = colInput;
}

void CarType::SetID(int idInput) {
	ID = idInput;
}

// Added == operators for comparing IDs when working with HashTable
bool operator==(const CarType& lhs, const CarType& rhs) {
	return (lhs.ID == rhs.ID);
}

bool operator==(const CarType& lhs, const int val) {
	return (lhs.ID == val);
}

ostream& operator<<(ostream& out, const CarType car) {
	out << "#" << car.ID << endl;
	out << "Car: " << car.make << " " << car.model << endl;
	out << "Car year: " << car.year << endl;
	out << "Car color: " << colors[car.color] << endl;
	out << "Car mileage: " << car.mileage << endl;
	return out;
}