// Implementation file for car.h

#include "cartype.h"
#include <algorithm>

CarType::CarType(){
	year = 0;
	mileage = 0;
	model = "BLANK";
	ID = 0;
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
void CarType::SetID(int idInput)
{
	ID = idInput;
}
ostream& operator<<(ostream& out, const CarType car){
	out << "Car model: " << car.model << endl;
	out << "Car year: " << car.year << endl;
	out << "Car mileage: " << car.mileage << endl;
	return out;
}
