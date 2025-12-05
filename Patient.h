#ifndef PATIENT_H
#define PATIENT_H

#include <string>
#include <vector>
#include "MedicalInformation.h"

using namespace std;

class Patient : public MedicalInformation {   // ? Inheritance
private:
    string name;
    string dob;
    char gender;
    string insuranceCompany;
    string diagnosis;
    int age;
    int insuranceNum;
    vector<string> medication;
    
    // Parent information for patients under 18
    string parentName;
    string parentRelationship;
    long long parentPhone;
    bool hasParentInfo;

public:
    Patient();

    void registerPatient();        // ? adds new patient to file
    void requestAppointment();     // ? later used with Appointment class

    // ? Polymorphism (overrides base behavior)
    void displayInfo() const;
    void getInformation(const string& dob, const string& name) override;

    // ? Getter functions for Doctor/Admin
    string getName() const;
    string getDOB() const;
    string getDiagnosis() const;
    
    // Parent information getters
    bool hasParentInformation() const;
    string getParentName() const;
    string getParentRelationship() const;
    long long getParentPhone() const;
    
private:
    // Helper function to check insurance uniqueness
    bool isInsuranceInfoUnique(const string& company, int number);
};

#endif
