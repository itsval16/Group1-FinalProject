#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include <string>
#include "MedicalInformation.h"

using namespace std;

class Admin {
    private:
        string adminName;
        int adminID;

        MedicalInformation medInfo;  
        // Admin uses the same file system as patients & doctors

    public:
        Admin(string name = "Admin", int id = 0000);

        void addDoctor(const string& doctorInfo);
        void removeDoctor(const string& doctorName);
        void updatePatient(const string& dob, const string& name, const string& newInfo);
        void viewPatients(const string& dob, const string& name);
        void displayInfo() const;
};

#endif
