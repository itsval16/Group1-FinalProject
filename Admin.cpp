#include "Admin.h"
#include <fstream>
#include <vector>

// Constructor sets up the admin's name and ID
Admin::Admin(string name, int id) {
    adminName = name;
    adminID = id;
}

// Adds a doctor to the file using the MedicalInformation class
void Admin::addDoctor(const string& doctorInfo) {
    cout << "Adding doctor to system..." << endl;

    // Adds the doctor's information to patientsInfo.txt
    medInfo.addInformation(doctorInfo);

    cout << "Doctor added successfully.\n";
}

// Removes a doctor by rewriting the file without that doctor's name
void Admin::removeDoctor(const string& doctorName) {
    fstream file("patientsInfo.txt", ios::in);

    // Check if the file opened correctly
    if (!file) {
        cerr << "Medical Information could not be opened" << endl;
        return;
    }

    vector<string> lines;
    string line;

    // Read every line and keep only lines that DO NOT belong to the doctor
    while (getline(file, line)) {
        if (line.find(doctorName) == string::npos) {
            lines.push_back(line); // keep the line
        }
    }

    file.close();

    // Rewrite the file without the removed doctor
    file.open("patientsInfo.txt", ios::out);

    for (const string& i : lines) {
        file << i << endl;
    }

    file.close();

    cout << "Doctor removed successfully.\n";
}

// Updates a patient's info using their DOB + Name to find the line
void Admin::updatePatient(const string& dob, const string& name, const string& newInfo) {
    cout << "Updating patient info..." << endl;

    // Uses MedicalInformation's modify function
    medInfo.modifyInformation(dob, name, newInfo);
}

// Views a patient's information based on DOB + Name
void Admin::viewPatients(const string& dob, const string& name) {
    cout << "Fetching patient info...\n";

    // Uses MedicalInformation's get function
    medInfo.getInformation(dob, name);
}

// Shows the admin's personal information
void Admin::displayInfo() const {
    cout << "\n--- ADMIN INFO ---\n";
    cout << "Name: " << adminName << endl;
    cout << "ID: " << adminID << endl;
}
