#ifndef CAR_TYPE
#define CAR_TYPE

#include <iostream>		// cout
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