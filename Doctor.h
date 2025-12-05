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
    int password; 

public:
    //constructors
    Doctor(); 
    Doctor(string name, string specialty, int password);

    //doc action
    void viewPatient();             //read
    void updatePatientRecord();     //update


    virtual void displayInfo() const;  
    
    //operator overload
    bool operator==(const Doctor& other) const;
    friend ostream& operator<<(ostream& out, const Doctor& d);

    //getter
    string getName() const;
    string getSpecialty() const;
    
    static Doctor createDoctorWithValidation();
};

#endif
