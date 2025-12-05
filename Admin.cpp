#include "Admin.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Constructor initializes admin name and ID
Admin::Admin(string name, int id) {
    adminName = name;
    adminID = id;
}

// Adds a doctor to the system file
void Admin::addDoctor(const string& doctorInfo) {
    cout << "Adding doctor to system..." << endl;

    // Uses MedicalInformation's add function
    medInfo.addInformation(doctorInfo);

    cout << "Doctor added successfully.\n";
}

// Removes a doctor by rewriting the file without their name
void Admin::removeDoctor(const string& doctorName) {
    fstream file("doctorsInfo.txt", ios::in);  // Use a separate doctors file
    
    if (!file) {
        cerr << "File could not be opened.\n";
        return;
    }

    vector<string> lines;
    string line;

    // Read file and store only lines that do NOT contain the doctor name
    while (getline(file, line)) {
        if (line.find(doctorName) == string::npos) { 
            lines.push_back(line);
        }
    }

    file.close();

    // Rewrite the file
    file.open("doctorsInfo.txt", ios::out);

    if (!file) {
        cerr << "File could not be opened for writing.\n";
        return;
    }

    for (size_t i = 0; i < lines.size(); i++) {
        file << lines[i] << endl;
    }

    file.close();

    cout << "Doctor removed successfully.\n";
}

// Updates patient information using MedicalInformation's modify function
void Admin::updatePatient(const string& dob, const string& name, const string& newInfo) {
    cout << "Updating patient info...\n";
    medInfo.modifyInformation(dob, name, newInfo);
}

// Views patient information using MedicalInformation's get function
void Admin::viewPatients(const string& dob, const string& name) {
    cout << "Fetching patient info...\n";
    medInfo.getInformation(dob, name);
}

// Displays admin details
void Admin::displayInfo() const {
    cout << "\n--- ADMIN INFO ---\n";
    cout << "Admin Name: " << adminName << endl;
    cout << "Admin ID: " << adminID << endl;
}
