// Patient.h
#ifndef PATIENT_H
#define PATIENT_H

#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
using namespace std;

class Patient {
private:
    string name;
    string dob;
    string sex;	
    string insurance;
    string phoneNumber;
    string email;

public:

     void registerPatient() {

        cout << "Enter your full name: " << endl;
        getline(cin, name);

        cout << "Enter your DOB (MM/DD/YYYY): " << endl;
        cin >> dob;

        while (true) {
        	cout << "Enter your Sex (M/F): " << endl;
        	cin >> sex;

        if (sex == "M" || sex == "F" || sex == "m" || sex == "f") {
            break;  // valid input → exit loop
        }

        cerr << "Invalid input. Please enter M or F.\n";
        cin.clear();
        cin.ignore(10000, '\n');
    }
        cout << "Enter your Insurance provider: " << endl;
        cin >> insurance;

        cout << "Enter your Phone number: " << endl;
        cin >> phoneNumber;

        cout << "Enter your Email: " << endl;
        cin >> email;
    }
    void displayInfo() const {
        const int labelWidth = 12;
        const int valueWidth = 25;

        cout << "\n===== Patient Information =====\n";
        cout << left << setw(labelWidth) << "Name:"      << setw(valueWidth) << name        << endl;
        cout << left << setw(labelWidth) << "DOB:"       << setw(valueWidth) << dob         << endl;
        cout << left << setw(labelWidth) << "Sex:"       << setw(valueWidth) << sex         << endl;
        cout << left << setw(labelWidth) << "Insurance:" << setw(valueWidth) << insurance   << endl;
        cout << left << setw(labelWidth) << "Phone:"     << setw(valueWidth) << phoneNumber << endl;
        cout << left << setw(labelWidth) << "Email:"     << setw(valueWidth) << email       << endl;
        cout << "=================================\n";
    }
    
    void savefile() {
        
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

        outfile.close();
    }
};


#endif
