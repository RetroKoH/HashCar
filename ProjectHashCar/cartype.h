#ifndef CAR_TYPE
#define CAR_TYPE

#include <iostream>
using namespace std;

class CarType
{
public:
	CarType();
	int GetYear();
	int GetMileage();
	string GetModel();
	string GetMake();
	void SetYear(int inputYear);
	void SetMileage(int inputMileage);
	void SetModel(string inputModel);
	void SetMake(string inputMake);
	void SetID(int idInput);
	friend ostream& operator<<(ostream& out, const CarType car);

private:
	int year;
	int mileage;
	int ID;
	string model;
	string make;
};
#endif