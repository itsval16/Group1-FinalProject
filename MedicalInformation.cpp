// MedicalInformation.cpp

#include "MedicalInformation.h"

MedicalInformation::addInformation(const string& info){
	medicalInfo.open("patientsInfo.txt", ios::app); // opens patientsInfo.txt if it exists or creates patientsInfo.txt if it doens't exist for appending information
	
	// Checks if the file is opened, returns a error if it isn't
	if (!medicalInfo){
	    cerr << "Medical Information could not be opened" << endl;
	    return;
	}
	
	// Inputs the information and closes the file
	medicalInfo << info << "\n";
	medicalInfo.close();
	
}

MedicalInformation::getInformation(const string& dob){
    medicalInfo.open("patientsInfo.txt",ios::in);
    
    // Checks if the file is opened, returns a error if it isn't
	if (!medicalInfo){
	    cerr << "Medical Information could not be opened" << endl;
	    return;
    }
    
    string line;
    bool found = false;
    
    while (getline(medicalInfo,line)){
        if(line.find(dob) != string::npos){ // looks for the line with dob and checks that it exists
            cout << line << endl;
            found = true;
            break;
        }
    }
    
    if (!found){
        cout << "Information not found" << endl;
    }
    
    medicalInfo.close();
}
