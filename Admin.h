#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include <string>
#include "MedicalInformation.h"

using namespace std;

// The Admin class controls high-level system actions.
// Admin can: add/remove doctors, update patient info, and view patient info.
class Admin {
    private:
        string adminName;   // Name of the admin using the system
        int adminID;        // Admin's ID (can act like a login code)

        MedicalInformation medInfo;  // Lets admin use medical file functions

    public:
        // Constructor to set admin name and ID
        Admin(string name = "Admin", int id = 0000);

        // Adds a doctor to the system file
        void addDoctor(const string& doctorInfo);

        // Removes a doctor by deleting their line from the file
        void removeDoctor(const string& doctorName);

        // Updates a patient's information using their DOB + Name
        void updatePatient(const string& dob, const string& name, const string& newInfo);

        // Views a patient by searching for their DOB + Name
        void viewPatients(const string& dob, const string& name);

        // Displays the admin's information
        void displayInfo() const;
};

#endif
