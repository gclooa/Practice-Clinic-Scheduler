// Guan Ce Looa
// CS 301 Summer 2020
// Assignment 2: Clinic Scheduler

#pragma once
#include <string>
using namespace std;

class Doctor
{
public:
	string name;
	string spec;
	int room;
	Doctor(string n, string s, int r);
};

class Patient
{
public:
	string name;
	string spec;
	int age;
	int room;
	Patient* next; // Patients are nodes that may form a queue.
	Patient(string n, string s, int a, int r);
};

class Room
{
public:
	Doctor* doctor;
	Patient* patient;
	Room();
};

Room::Room() // Room default constructor to initialize pointers.
{
	doctor = nullptr; // Room is occupied if doctor is NOT nullptr.
	patient = nullptr; // Patient pointer forms a queue.
}

Doctor::Doctor(string n, string s, int r) // Doctor constructor to assign object values.
{
	name = n;
	spec = s;
	room = r;
}

Patient::Patient(string n, string s, int r, int a) // Patient constructor to assign object values.
{
	name = n;
	spec = s;
	room = r;
	age = a;
	next = nullptr;
}