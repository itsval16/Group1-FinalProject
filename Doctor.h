// Doctor.h
#ifndef DOCTOR_H
#define DOCTOR_H
#include <string>
#include "MedicalInformation.h"

class Doctor : public MedicalInformation {
private :
string name;
string specialty;
int password;

public : 
Doctor ();
Doctor (string name, string specialty, int password); //doctor constructor w real info

void viewPatient(); //doctor reads patient info
void updatePatientRecord(); //doctor updates info

virtual void displayInfo() override;
bool operator==(const Doctor& other) const;
friend ostream& operator<<(ostream& out, const Doctor& d);

string getName() const;
string getSpecialty() const;
}; 


#endif
