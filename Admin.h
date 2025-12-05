#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include <string>
#include <fstream>
#include "MedicalInformation.h"

using namespace std;

// The Admin class controls high-level system actions
class Admin {
private:
    string adminName;           // Admin's name
    int adminID;                // Admin's ID (like a login)
    MedicalInformation medInfo; // Allows admin to access patient files

public:
    // Constructor
    Admin(string name = "Admin", int id = 0);

    // Doctor management
    void addDoctor(const string& doctorInfo);       // Add a doctor to the system file
    void removeDoctor(const string& doctorName);    // Remove doctor info from file

    // Patient management
    void updatePatient(const string& dob, const string& name, const string& newInfo); // Update patient record
    void viewPatients(const string& dob, const string& name);                          // View patient info

    // Display admin info
    void displayInfo() const;
};

#endif