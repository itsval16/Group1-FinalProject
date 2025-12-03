#include "Patient.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
using namespace std;

void Patient::registerPatient() { //patient register function
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter your full name: ";
    getline(cin, name);

    cout << "Enter your DOB (MM/DD/YYYY): ";
    getline(cin, dob);

    while (true) {  //loop is used in verifying proper input
        cout << "Enter your Sex (M/F): ";
        getline(cin, sex);

        if (sex == "M" || sex == "F" || sex == "m" || sex == "f")
            break; // clears any incorect inputs

        cerr << "Invalid input. Please enter M or F.\n";
    }

    cout << "Enter your Insurance provider: ";
    getline(cin, insurance);

    cout << "Enter your Phone number: ";
    getline(cin, phoneNumber);

    cout << "Enter your Email: ";
    getline(cin, email);
}

void Patient::displayInfo() const {
    const int labelWidth = 12;
    const int valueWidth = 25;

    cout << "\n----- Patient Information -----\n";
    cout << left << setw(labelWidth) << "Name:"      << setw(valueWidth) << name        << endl;
    cout << left << setw(labelWidth) << "DOB:"       << setw(valueWidth) << dob         << endl;
    cout << left << setw(labelWidth) << "Sex:"       << setw(valueWidth) << sex         << endl;
    cout << left << setw(labelWidth) << "Insurance:" << setw(valueWidth) << insurance   << endl;
    cout << left << setw(labelWidth) << "Phone:"     << setw(valueWidth) << phoneNumber << endl;
    cout << left << setw(labelWidth) << "Email:"     << setw(valueWidth) << email       << endl;
    cout << "---------------------------------\n";
}

void Patient::savefile() {
    ofstream outfile("patient.txt", ios::app);

    if (!outfile) {
        cerr << "Error opening patient.txt for writing.\n";
        return;
    }

    outfile << "Name: "      << name        << "\n";
    outfile << "DOB: "       << dob         << "\n";
    outfile << "Sex: "       << sex         << "\n";
    outfile << "Insurance: " << insurance   << "\n";
    outfile << "Phone: "     << phoneNumber << "\n";
    outfile << "Email: "     << email       << "\n";
    outfile << "-----------------------------\n";
