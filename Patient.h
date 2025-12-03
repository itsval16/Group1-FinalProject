#ifndef PATIENT_H
#define PATIENT_H

#include <string>
using namespace std;

class Patient {
private:
    string name;
    string dob;
    string sex;
    string insurance;
    string phoneNumber;
    string email;

public:
    void registerPatient();
    void displayInfo() const;
    void savefile();
};

#endif
