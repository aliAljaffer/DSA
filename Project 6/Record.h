#pragma once
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;


// Each record holds a student's first and
// last names, their UID (an integer), and
// their year (a string)

class Record
{
private:
	string firstName;
	string lastName;
	int uid;
	string year;

public:

	// The default constructor produces a "test" student
	Record()
	{
		firstName = "Test";
		lastName = "Student";
		uid = 0;
		year = "Freshman";
	}

	// This constructor uses an initialization list
	// See "member initialization" at: http://www.cplusplus.com/doc/tutorial/classes/
	Record(string newFirstName, string newLastName, int newUID, string newYear)
		: firstName(newFirstName), lastName(newLastName), uid(newUID), year(newYear)
	{}

	// Fill a record object with values
	void load(string newFirstName, string newLastName, int newUID, string newYear) {
		firstName = newFirstName;
		lastName = newLastName;
		uid = newUID;
		year = newYear;
	}

	// Get the student's name
	string getName() const {
		string result = lastName + ", " + firstName;
		return result;
	}

	// Get the student's id
	int getUID() const {
		return uid;
	}
	
	// Get the student's year
	string getYear() const {
		return year;
	}
	
	// Change the student's year.  You can create setters for the other
	// member data fields if you feel you need them.
	void setYear(string newYear) {
		year = newYear;
	}

	// Overload the << operator for printing a student
	friend ostream& operator<<(ostream& os, const Record& me) {
		os << me.getName() << " (U" << setw(8) << setfill('0') << me.getUID() << "): " << me.getYear();
		return os;
	}

	// No destructor is needed as Records don't use any dynamically
	// allocated memory
	~Record()
	{
	}
};

