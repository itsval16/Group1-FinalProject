// MedicalInformation.cpp

#include "MedicalInformation.h"

// string dob, string name, int age, string gender, string insuranceCompany, int insuranceNum, string diagnosis, vector<string> medication
MedicalInformation::addInformation(){
	medicalInfo.open("patientsInfo.txt", ios::app);
	
}
