#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include <string>
#include <fstream>
#include "MedicalInformation.h"

using namespace std;

// The Admin class controls high-level system actions.
class Admin {
private:
    string adminName;   // Admin's name
    int adminID;        // Admin's ID (like a login)

    MedicalInformation medInfo;  // Allows admin to access patient file

public:
    // Constructor
    Admin(string name = "Admin", int id = 0);

    // Add a doctor (writes to the file)
    void addDoctor(const string& doctorInfo);

    // Remove a doctor (removes matching lines)
    void removeDoctor(const string& doctorName);

    // Update patient information
    void updatePatient(const string& dob, const string& name, const string& newInfo);

    // View a patient's information
    void viewPatients(const string& dob, const string& name);

    // Display admin info
    void displayInfo() const;
};

#endif
