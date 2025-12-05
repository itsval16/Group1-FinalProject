#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include <string>
#include <fstream>
#include "MedicalInformation.h"

using namespace std;

//handles admin.cpp
class Admin {
private:
    string adminName;        
    int adminID;               
    MedicalInformation medInfo; // allows for the admin to access patient files

public:
    // constructor HERE
    Admin(string name = "Admin", int id = 0);

    // doc mang.
    void addDoctor(const string& doctorInfo);       // add doc
    void removeDoctor(const string& doctorName);    // remove doc

    // patient mag.
    void updatePatient(const string& dob, const string& name, const string& newInfo); // update
    void viewPatients(const string& dob, const string& name);                          // view

    
    void displayInfo() const;
};

#endif
