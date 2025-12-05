#ifndef DOCTOR_H
#define DOCTOR_H

#include <string>
#include <iostream>
#include "MedicalInformation.h"

using namespace std;

class Doctor : public MedicalInformation {
private:
    string name;
    string specialty;
    int password;  // Could be used for authentication in the future

public:
    // Constructors
    Doctor();  // Default
    Doctor(string name, string specialty, int password); // Parameterized

    // Doctor actions
    void viewPatient();             // Read patient info
    void updatePatientRecord();     // Update patient info

    // Display doctor info
    virtual void displayInfo() const;  // Use const for display functions

    // Operator overloads
    bool operator==(const Doctor& other) const;
    friend ostream& operator<<(ostream& out, const Doctor& d);

    // Getters
    string getName() const;
    string getSpecialty() const;
};

#endif
