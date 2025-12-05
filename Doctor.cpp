#include "Doctor.h"
#include <iostream>
#include <limits>   // for numeric_limits
using namespace std;

// Default constructor
Doctor::Doctor() {
    name = "";
    specialty = "";
    password = 0;
}

// Parameterized constructor
Doctor::Doctor(string n, string s, int p) {
    name = n;
    specialty = s;
    password = p;
}

// Display doctor info
void Doctor::displayInfo() const {
    cout << "\n----- Doctor Information -----\n";
    cout << "Name: " << name << endl;
    cout << "Specialty: " << specialty << endl;
    cout << "-------------------------------\n";
}

// View patient info
void Doctor::viewPatient() {
    string patientName, dob;

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
    cout << "Enter the patient's full name to view: ";
    getline(cin, patientName);

    cout << "Enter the patient's DOB (MM/DD/YYYY): ";
    getline(cin, dob);

    getInformation(dob, patientName);  // Pass both name and DOB
}

// Update patient record
void Doctor::updatePatientRecord() {
    string patientName, dob, newInfo;

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
    cout << "Enter the patient's full name to update: ";
    getline(cin, patientName);

    cout << "Enter the patient's DOB (MM/DD/YYYY): ";
    getline(cin, dob);

    cout << "Enter the updated information (CSV format): ";
    getline(cin, newInfo);

    modifyInformation(dob, patientName, newInfo);  // Pass both name and DOB
}

// Equality operator
bool Doctor::operator==(const Doctor& other) const {
    return name == other.name && specialty == other.specialty;
}

// Stream output
ostream& operator<<(ostream& out, const Doctor& d) {
    out << "Doctor: " << d.name << " (" << d.specialty << ")";
    return out;
}

// Getters
string Doctor::getName() const {
    return name;
}

string Doctor::getSpecialty() const {
    return specialty;
}
