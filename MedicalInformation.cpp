// MedicalInformation.cpp

#include "MedicalInformation.h"
#include <vector>
#include <sstream>
#include <stdexcept>

// Adds new medical information
void MedicalInformation::addInformation(const string& info) {
    try {
        medicalInfo.open("patientsInfo.txt", ios::app);

        if (!medicalInfo)
            throw runtime_error("Medical Information file could not be opened.");

        medicalInfo << info << endl;
        medicalInfo.close();
    }
    catch (exception& e) {
        cerr << "Error adding information: " << e.what() << endl;
    }
}

// Retrieves medical information
void MedicalInformation::getInformation(const string& dob, const string& name) {
    try {
        medicalInfo.open("patientsInfo.txt", ios::in);

        if (!medicalInfo)
            throw runtime_error("Medical Information file could not be opened.");

        string line;
        bool found = false;

        while (getline(medicalInfo, line)) {
            stringstream ss(line);   // REQUIRED stringstream usage

            if (line.find(dob) != string::npos && line.find(name) != string::npos) {
                cout << "\nMedical Record Found:\n";
                cout << line << endl;
                found = true;
                break;
            }
        }

        if (!found)
            cout << "\nInformation not found." << endl;

        medicalInfo.close();
    }
    catch (exception& e) {
        cerr << "Error retrieving information: " << e.what() << endl;
    }
}

// Modifies existing medical record
void MedicalInformation::modifyInformation(const string& dob, const string& name, const string& newInfo) {
    try {
        medicalInfo.open("patientsInfo.txt", ios::in);

        if (!medicalInfo)
            throw runtime_error("Medical Information file could not be opened.");

        vector<string> lines;
        string line;
        bool modified = false;

        while (getline(medicalInfo, line)) {
            if (line.find(dob) != string::npos && line.find(name) != string::npos) {
                lines.push_back(newInfo);
                modified = true;
            }
            else {
                lines.push_back(line);
            }
        }

        medicalInfo.close();

        if (!modified)
            throw runtime_error("Record to modify was not found.");

        medicalInfo.open("patientsInfo.txt", ios::out);

        if (!medicalInfo)
            throw runtime_error("File could not be opened for rewriting.");

        for (const string& i : lines) {
            medicalInfo << i << endl;
        }

        medicalInfo.close();
        cout << "\nMedical record successfully updated." << endl;
    }
    catch (exception& e) {
        cerr << "Error modifying information: " << e.what() << endl;
    }
}
