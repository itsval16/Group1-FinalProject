#include "Admin.h"
#include <iostream>
#include <fstream> //read/write (file operations)
#include <vector>

using namespace std;

//admin is aggined with name and ID 
//constructor is implemented in here
Admin::Admin(string name, int id) {
    adminName = name;
    adminID = id;
}

// function to add the docs information
//contains a string 
void Admin::addDoctor(const string& doctorInfo) {
    cout << "Adding doctor to system..." << endl;

    //will be added to the med info function if it can add to file 
    fstream file("doctorsInfo.txt", ios::app);
    if (!file) {
        cerr << "File could not be opened.\n"; //file wont be able to be opened
        return;
    }
    file << doctorInfo; //will write the doc info here!

    cout << "Doctor added successfully.\n";
    
    file.close(); //close file
}

// remove the doc
void Admin::removeDoctor(const string& doctorName) {
    fstream file("doctorsInfo.txt", ios::in);  // Use a separate doctors file
    
    if (!file) {
        cerr << "File could not be opened.\n";
        return;
    }

    vector<string> lines;
    string line;

    // will read the file and store only lines that do NOT contain the doctor name
    while (getline(file, line)) {
        if (line.find(doctorName) == string::npos) { //will find the doc names here and remove name 
            lines.push_back(line); //if not found it will be kept
        }
    }

    file.close(); //input file CLOSED

    // rewrites the file here
    file.open("doctorsInfo.txt", ios::out);

    if (!file) {
        cerr << "File could not be opened for writing.\n";
        return;
    }

    for (size_t i = 0; i < lines.size(); i++) {
        file << lines[i] << endl; //writes all the kept lines back onto the file 
    }

    file.close(); //file CLOSED

    cout << "Doctor removed successfully.\n";
}

// updates patient information using medinfo modify function
void Admin::updatePatient(const string& dob, const string& name, const string& newInfo) {
    cout << "Updating patient info...\n";
    medInfo.modifyInformation(dob, name, newInfo);
}

// views patient information using medinfo get function
void Admin::viewPatients(const string& dob, const string& name) {
    cout << "Fetching patient info...\n";
    medInfo.getInformation(dob, name);
}

// display the admins info
void Admin::displayInfo() const {
    cout << "\n--- ADMIN INFO ---\n";
    cout << "Admin Name: " << adminName << endl;
    cout << "Admin ID: " << adminID << endl;
}
