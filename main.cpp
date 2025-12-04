// MedicalInformation.h
#ifndef MEDICALINFORMATION_H
#define MEDICALINFORMATION_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class MedicalInformation {
protected:
    fstream medicalInfo;

public:
    void addInformation(const string& info);
    void modifyInformation(const string& dob, const string& name, const string& newInfo);
    void getInformation(const string& dob, const string& name);

    // Virtual destructor for safety with inheritance
    virtual ~MedicalInformation() {}
};

#endif


