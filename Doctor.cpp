// Doctor.cpp

#include "Doctor.h"
#include <iostream> 
using namespace std;

Doctor::Doctor() {
    name = "";
    specialty = "";
    password = 0;
} 

Doctor::Doctor(string n, string s, int p) {
    name = n;
    specialty = s;
    password = p;
}

void Doctor::displayInfo() {
    cout << "Doctor Information";
    cout << "Name: " << name << endl;
    cout << "Specialty: " << specialty << endl;}

void Doctor::viewPatient() {
    string dob;
   cout << "Enter the patient's DOB you want to view: ";
    cin >> dob;

    getInformation(dob);}

void Doctor::updatePatientRecord() {
    string dob;
    string newInfo;

    cout << "Enter patient's DOB you want to update: ";
    cin >> dob;

    cout << "Enter the updated information: ";
    cin.ignore();
    getline(cin, newInfo);

    modifyInformation(dob, newInfo);}

bool Doctor::operator==(const Doctor& other) const {
    return name == other.name && specialty == other.specialty;}

ostream& operator<<(ostream& out, const Doctor& d) {
    out << "Doctor: " << d.name << " (" << d.specialty << ")";
    return out;}

string Doctor::getName() const {
    return name;}

string Doctor::getSpecialty() const {
    return specialty;}
