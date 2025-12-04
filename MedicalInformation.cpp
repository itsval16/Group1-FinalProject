// MedicalInformation.cpp

#include "MedicalInformation.h"
#include <vector>

void MedicalInformation::addInformation(const string& info){
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

void MedicalInformation::getInformation(const string& dob, const string& name){
    medicalInfo.open("patientsInfo.txt",ios::in); // opens for reading
    
    // Checks if the file is opened, returns a error if it isn't
	if (!medicalInfo){
	    cerr << "Medical Information could not be opened" << endl;
	    return;
    }
    
    string line;
    bool found = false;
    
    while (getline(medicalInfo,line)){
        if(line.find(dob) != string::npos && line.find(name) != string::npos){ // looks for the line with dob and checks that it exists
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

void MedicalInformation::modifyInformation(const string& dob, const string& name, const string& newInfo){
    medicalInfo.open("patientsInfo.txt",ios::in);
    
    // Checks if the file is opened, returns a error if it isn't
	if (!medicalInfo){
	    cerr << "Medical Information could not be opened" << endl;
	    return;
    }
    
    vector<string> lines;
    string line;
    
    // Loops through the file and gets every line, if the line that needs to be replaced shows up, new info is used instead
    while (getline(medicalInfo,line)){
        if(line.find(dob) != string::npos && line.find(name) != string::npos){ // looks for the line with dob and checks that it exists
            lines.push_back(newInfo);
        } else {
            lines.push_back(line);
        }
    }
    
    medicalInfo.close();
    medicalInfo.open("patientsInfo.txt",ios::out);
    
    // adds back in all the information alongside new info
    for (const string& i : lines){
        medicalInfo << i << endl;
    }
    
    medicalInfo.close();
}

