// MedicalInformation.cpp

#include "MedicalInformation.h"

MedicalInformation::addInformation(const string& info){
	medicalInfo.open("patientsInfo.txt", ios::app); // opens patientsInfo.txt if it exists or creates patientsInfo.txt if it doens't exist for appending information
	
	// Checks if the file is opened, returns an error if it isn't
	if (!medicalInfo){
	    cerr << "Medical Information could not be opened" << endl;
	    return;
	}
	
	// Inputs the information and closes the file
	medicalInfo << info << "\n";
	medicalInfo.close();
	
}

