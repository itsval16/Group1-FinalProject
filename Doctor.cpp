#include "Doctor.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <string>
#include <cctype>
using namespace std;

//constructor
Doctor::Doctor() {
    name = "";
    specialty = "";
    password = 0;
}

//parameterized constructor
Doctor::Doctor(string n, string s, int p) {
    name = n;
    specialty = s;
    password = p;
}


void Doctor::displayInfo() const {
    cout << "\n----- Doctor Information -----\n";
    cout << "Name: " << name << endl;
    cout << "Specialty: " << specialty << endl;
    cout << "-------------------------------\n";
}

//view patient info
void Doctor::viewPatient() {
    string patientName, dob;

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
    cout << "Enter the patient's full name to view: ";
    getline(cin, patientName);

    
    bool validPatientName = true;
    for (char c : patientName) {
        if (!isalpha(c) && c != ' ' && c != '.') {
            cout << "Invalid patient name format. Only letters, spaces, and dots allowed.\n";
            validPatientName = false;
            break;
        }
    }
    
    if (!validPatientName) {
        return;
    }

    cout << "Enter the patient's DOB (MM/DD/YYYY): ";
    getline(cin, dob);

   
    bool validDOB = true;
    if (dob.length() != 10 || dob[2] != '/' || dob[5] != '/') {
        cout << "Invalid date format. Use MM/DD/YYYY with slashes (/).\n";
        validDOB = false;
    } else {
        string month = dob.substr(0, 2);
        string day = dob.substr(3, 2);
        string year = dob.substr(6, 4);
        
        for (char c : month + day + year) {
            if (!isdigit(c)) {
                cout << "Date must contain only numbers and slashes.\n";
                validDOB = false;
                break;
            }
        }
    }
    
    if (validDOB) {
        getInformation(dob, patientName);  
    }
}


void Doctor::updatePatientRecord() {
    string patientName, dob, newInfo;

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    cout << "Enter the patient's full name to update: ";
    getline(cin, patientName);

  
    bool validPatientName = true;
    for (char c : patientName) {
        if (!isalpha(c) && c != ' ' && c != '.') {
            cout << "Invalid patient name format. Only letters, spaces, and dots allowed.\n";
            validPatientName = false;
            break;
        }
    }
    
    if (!validPatientName) {
        return;
    }

    cout << "Enter the patient's DOB (MM/DD/YYYY): ";
    getline(cin, dob);


    bool validDOB = true;
    if (dob.length() != 10 || dob[2] != '/' || dob[5] != '/') {
        cout << "Invalid date format. Use MM/DD/YYYY with slashes (/).\n";
        validDOB = false;
    } else {
        string month = dob.substr(0, 2);
        string day = dob.substr(3, 2);
        string year = dob.substr(6, 4);
        
        for (char c : month + day + year) {
            if (!isdigit(c)) {
                cout << "Date must contain only numbers and slashes.\n";
                validDOB = false;
                break;
            }
        }
    }
    
    if (!validDOB) {
        return;
    }

    cout << "Enter the updated information (CSV format): ";
    getline(cin, newInfo);


    if (newInfo.find(',') == string::npos) {
        cout << "Invalid CSV format. Information should be comma-separated.\n";
        return;
    }

    modifyInformation(dob, patientName, newInfo);  
}

bool Doctor::operator==(const Doctor& other) const {
    return name == other.name && specialty == other.specialty;
}

ostream& operator<<(ostream& out, const Doctor& d) {
    out << "Doctor: " << d.name << " (" << d.specialty << ")";
    return out;
}

//getter
string Doctor::getName() const {
    return name;
}

string Doctor::getSpecialty() const {
    return specialty;
}
Doctor Doctor::createDoctorWithValidation() {
    string name, specialty;
    int password;
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
//letter and space
    bool validName = false;
    while (!validName) {
        cout << "Enter doctor's name: ";
        getline(cin, name);
        
        validName = true;
        for (char c : name) {
            if (!isalpha(c) && c != ' ' && c != '.') {
                validName = false;
                cout << "Invalid name. Only letters, spaces, and dots are allowed.\n";
                break;
            }
        }
        
        if (name.empty() || name.find_first_not_of(' ') == string::npos) {
            validName = false;
            cout << "Name cannot be empty.\n";
        }
    }
    
//letter an dspace
    bool validSpecialty = false;
    while (!validSpecialty) {
        cout << "Enter doctor's specialty: ";
        getline(cin, specialty);
        
        validSpecialty = true;
        for (char c : specialty) {
            if (!isalpha(c) && c != ' ' && c != '.') {
                validSpecialty = false;
                cout << "Invalid specialty. Only letters, spaces, and dots are allowed.\n";
                break;
            }
        }
        
        if (specialty.empty() || specialty.find_first_not_of(' ') == string::npos) {
            validSpecialty = false;
            cout << "Specialty cannot be empty.\n";
        }
    }
    
//password
    bool validPassword = false;
    while (!validPassword) {
        cout << "Enter doctor's password (4-8 digits): ";
        string passwordInput;
        getline(cin, passwordInput);
        
        bool isNumeric = true;
        for (char c : passwordInput) {
            if (!isdigit(c)) {
                isNumeric = false;
                break;
            }
        }
        
        if (!isNumeric) {
            cout << "Password must contain only numbers.\n";
            continue;
        }
        
        try {
            password = stoi(passwordInput);
            if (passwordInput.length() >= 4 && passwordInput.length() <= 8) {
                validPassword = true;
            } else {
                cout << "Password must be 4 to 8 digits long.\n";
            }
        } catch (...) {
            cout << "Invalid password. Enter numeric digits only.\n";
        }
    }
    
    return Doctor(name, specialty, password);
}

