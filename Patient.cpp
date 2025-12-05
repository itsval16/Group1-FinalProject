#include "Patient.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <limits>

using namespace std;

Patient::Patient() {
    age = 0;
    insuranceNum = 0;
}

// Registers a new patient
void Patient::registerPatient() {
    try {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\nEnter full name: ";
        getline(cin, name);

        cout << "Enter DOB (MM/DD/YYYY): ";
        getline(cin, dob);

        cout << "Enter gender: ";
        cin >> gender;
        if (gender != 'm' || gender != 'M' || gender != 'f' || gender != 'F')
            throw runtime_error("Invalid gender entered.");
            
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter age: ";
        cin >> age;

        if (age < 0 || age > 120)
            throw runtime_error("Invalid age entered.");

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter insurance company: ";
        getline(cin, insuranceCompany);

        cout << "Enter insurance number: ";
        cin >> insuranceNum;

        if (insuranceNum <= 0)
            throw runtime_error("Invalid insurance number.");

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter diagnosis: ";
        getline(cin, diagnosis);

        // Medication entry
        medication.clear();
        string med;
        char choice;

        do {
            cout << "Enter medication name: ";
            getline(cin, med);
            medication.push_back(med);

            cout << "Add another medication? (y/n): ";
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

        } while (choice == 'y' || choice == 'Y');

        // Format as CSV using stringstream
        stringstream ss;
        ss << name << "," << dob << "," << gender << "," << age << ","
           << insuranceCompany << "," << insuranceNum << "," << diagnosis;

        for (size_t i = 0; i < medication.size(); i++) {
            ss << "," << medication[i];
        }

        // ? Save using BASE CLASS file function
        addInformation(ss.str());

        cout << "\nPatient registered successfully.\n";
    }
    catch (exception& e) {
        cerr << "Registration error: " << e.what() << endl;
    }
}

// Displays patient information
void Patient::displayInfo() const {
    cout << "\n----- Patient Information -----\n";
    cout << "Name: " << name << endl;
    cout << "DOB: " << dob << endl;
    cout << "Gender: " << gender << endl;
    cout << "Age: " << age << endl;
    cout << "Insurance Company: " << insuranceCompany << endl;
    cout << "Insurance Number: " << insuranceNum << endl;
    cout << "Diagnosis: " << diagnosis << endl;

    cout << "Medication: ";
    for (size_t i = 0; i < medication.size(); i++) {
        cout << medication[i];
        if (i < medication.size() - 1)
            cout << ", ";
    }

    cout << "\n--------------------------------\n";
}

// Placeholder for appointment system (used later)
void Patient::requestAppointment() {
    cout << "\nAppointment request feature coming soon...\n";
}

// Getter functions
string Patient::getName() const {
    return name;
}

string Patient::getDOB() const {
    return dob;
}

string Patient::getDiagnosis() const {
    return diagnosis;
}
