// Implementation file for car.h

#include "cartype.h"
#include <iostream>
#include <algorithm>

// Default Constructor
CarType::CarType() {
	year = 1990 + (rand() % 32);				// Year is random from 1990 to 2022

	int age = 2022 - year;
	mileage = 0;								// Randomly generated; 10-12k miles per year
	for (int i = 0; i < age; i++)
		mileage += 10000 + (rand() % 2000);

	// Use enum/int to pull the correct string. We should keep these as strings so users can enter their own.
	MakeType getMake = MakeType(rand() % 6);	// Get random make.
	make = makes[getMake];						// Then pull a model name based on make.
	model = models[getMake][rand() % 5];

	color = ColorType(rand() % 9);				// Assign a random color
	
	ID = rand() % 999999;						// Assign a random 6 digit ID number
	// ID will later be its own IDType class, consisting of either an int, or string.
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

int CarType::GetYear(){
	return year;
}

int CarType::GetMileage(){
	return mileage;
}

string CarType::GetModel(){
	return model;
}

string CarType::GetMake(){
	return make;
}

void CarType::SetYear(int inputYear){
	year = inputYear;
}

void CarType::SetMileage(int inputMileage){
	mileage = inputMileage;
}

void CarType::SetModel(string inputModel){
	model = inputModel;
}

void CarType::SetMake(string inputMake){
	make = inputMake;
}

void CarType::SetID(int idInput){
	ID = idInput;
}

ostream& operator<<(ostream& out, const CarType car){
	out << "Car: " << car.make << " " << car.model << endl;
	out << "Car year: " << car.year << endl;
	out << "Car color: " << colors[car.color] << endl;
	out << "Car mileage: " << car.mileage << endl;
	return out;
}
