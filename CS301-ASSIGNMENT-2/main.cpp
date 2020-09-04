// Guan Ce Looa
// CS 301 Summer 2020
// Assignment 2: Clinic Scheduler

#include <iostream>
#include <iomanip>
#include "Clinic.h"
using namespace std;

void doctorIn(Room* room);
void doctorOut(Room* room);
void patientIn(Room* room);
void patientOut(Room* room);

int main()
{
	Room room[20]; // Initialize 20 clinic rooms.

	int run = 1; // Master switch.
	string usertype;
	string usercico;

	cout << "Welcome to clinic scheduler." << endl;
	while (run != 0)
	{
		cout << "Enter D for doctor, or P for patient: ";
		cin >> usertype;
		cout << "Enter I for check-in, or O for check-out: ";
		cin >> usercico;

		if (usertype == "D" && usercico == "I")
		{
			doctorIn(room);
		}
		else if (usertype == "D" && usercico == "O")
		{
			doctorOut(room);
		}
		else if (usertype == "P" && usercico == "I")
		{
			patientIn(room);
		}
		else if (usertype == "P" && usercico == "O")
		{
			patientOut(room);
		}
		else
		{
			cout << "Invalid input. Input is case-sensitive. Try again." << endl;
		}
		cout << "Enter 1 to restart or 0 to end: ";
		cin >> run; // Master switch, 1 continues the loop, 0 exits the loop.
		cout << endl;
	}
	cout << "Press any key to end program." << endl;
	cin.get();
	cin.get();
	return 0;
}

void doctorIn(Room* room)
{
	string name;
	string spec;
	int num;

	cout << endl << "Doctor check-in initialized." << endl;
	cout << "Enter name: ";
	cin >> name;
	cout << "Enter specialty code: ";
	cin >> spec;
	cout << "Enter room number: ";
	cin >> num;

	Doctor* doc = new Doctor(name, spec, num);
	if (room[num - 1].doctor == nullptr) // Check if favourite room is available.
	{
		room[num - 1].doctor = doc;
		cout << "Doctor " << name << " checked in to room " << num << "." << endl;
	}
	else
	{
		cout << "Sorry, room " << num << " is currently occupied." << endl;
	}
}

void doctorOut(Room* room)
{
	string name;
	string spec;
	int num;

	cout << endl << "Doctor check-out initialized." << endl;
	cout << "Enter name: ";
	cin >> name;
	cout << "Enter specialty code: ";
	cin >> spec;
	cout << "Enter room number: ";
	cin >> num;

	if (room[num - 1].doctor != nullptr && room[num - 1].doctor->name == name && room[num - 1].doctor->spec == spec)
	{
		room[num - 1].doctor = nullptr;
		cout << "Doctor " << name << " checked out from room " << num << "." << endl;
	}
	else
	{
		cout << "Sorry, invalid input. Try again." << endl;
	}
}

void patientIn(Room* room)
{
	string name;
	int age;
	string spec;

	cout << endl << "Patient check-in initialized." << endl;
	cout << "Enter name: ";
	cin >> name;
	cout << "Enter age: ";
	cin >> age;
	if (age <= 15) // Any patient under age 16 is assigned to see a pediatrician.
	{
		spec = "PED";
	}
	else
	{
		cout << "Enter specialty code: "; // Request specialty code if older than 16.
		cin >> spec;
	}

	for (int i = 0; i < 20; i++)
	{
		if (room[i].doctor != nullptr && room[i].doctor->spec == spec) // Check if doctor is available.
		{
			if (room[i].patient == nullptr) // Check for a patient queue.
			{
				room[i].patient = new Patient(name, spec, i, age);
				cout << "Patient " << name << " checked in to room " << i + 1 << "." << endl;
				return;
			}
			else // If there is a patient queue, iterate and append.
			{
				Patient* p = room[i].patient;
				while (room[i].patient->next != nullptr)
				{
					p = p->next;
				}
				p->next = new Patient(name, spec, i, age);
				cout << "Patient " << name << " checked in to room " << i + 1 << "." << endl;
				return;
			}
		}
	}
	cout << "Sorry, there are no " << spec << " doctors currently available." << endl;
}

void patientOut(Room* room)
{
	string name;
	int age;
	int num;

	cout << endl << "Patient check-out initialized." << endl;
	cout << "Enter name: ";
	cin >> name;
	cout << "Enter age: ";
	cin >> age;
	cout << "Enter room number: ";
	cin >> num;

	if (room[num - 1].patient != nullptr && room[num - 1].patient->name == name && room[num - 1].patient->age == age)
	{
		Patient* p = room[num - 1].patient;
		room[num - 1].patient = room[num - 1].patient->next;
		delete p;
		cout << "Patient " << name << " checked out from room " << num << "." << endl;
	}
	else
	{
		cout << "Sorry, invalid input. Try again." << endl;
	}
}