#include "Patient.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <limits>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <vector>

using namespace std;

Patient::Patient() {
    age = 0;
    insuranceNum = 0;
    hasParentInfo = false;
}

//function to check if insurance info already exists
bool Patient::isInsuranceInfoUnique(const string& company, int number) {
    try {
        ifstream file("patientsInfo.txt");
        
        if (!file) {
            return true;
        }
        
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            vector<string> fields;
            string field;
            
            while (getline(ss, field, ',')) {
                fields.push_back(field);
            }
            
            
            if (fields.size() >= 6) {
                string existingCompany = fields[4]; //insurance company at index 4
                int existingNumber = 0;
                
                try {
                    existingNumber = stoi(fields[5]); //insurance number at index 5
                } catch (...) {
                    continue; 
                }
                
                if (existingCompany == company && existingNumber == number) {
                    file.close();
                    return false; 
                }
            }
        }
        
        file.close();
        return true; 
        
    } catch (exception& e) {
        cerr << "Error checking insurance uniqueness: " << e.what() << endl;
        return false; 
    }
}

void Patient::registerPatient() {
    try {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        bool validName = false;
        while (!validName) {
            cout << "\nEnter full name: ";
            getline(cin, name);
            
            validName = true;
            for (char c : name) {
                if (!isalpha(c) && c != ' ' && c != '.') {
                    validName = false;
                    cout << "Invalid name. Only letters, spaces, and dots are allowed.\n";
                    break;
                }
            }
            
            if (name.empty() || name.find_first_not_of(' ') == string::npos) {
                validName = false;
                cout << "Name cannot be empty.\n";
            }
        }

        bool validDOB = false;
        while (!validDOB) {
            cout << "Enter DOB (MM/DD/YYYY): ";
            getline(cin, dob);
            
            validDOB = true;
            
            if (dob.length() != 10 || dob[2] != '/' || dob[5] != '/') {
                validDOB = false;
                cout << "Invalid date format. Use MM/DD/YYYY with slashes (/).\n";
                continue;
            }
            
            string month = dob.substr(0, 2);
            string day = dob.substr(3, 2);
            string year = dob.substr(6, 4);
            
            for (char c : month + day + year) {
                if (!isdigit(c)) {
                    validDOB = false;
                    cout << "Date must contain only numbers and slashes.\n";
                    break;
                }
            }
            
            if (validDOB) {
                int m = stoi(month);
                if (m < 1 || m > 12) {
                    validDOB = false;
                    cout << "Month must be between 01 and 12.\n";
                }
                
                int d = stoi(day);
                if (d < 1 || d > 31) {
                    validDOB = false;
                    cout << "Day must be between 01 and 31.\n";
                }
                
                int y = stoi(year);
                if (y < 1900 || y > 2024) {
                    validDOB = false;
                    cout << "Year must be between 1900 and 2024.\n";
                }
            }
        }

        bool validGender = false;
        while (!validGender) {
            cout << "Enter gender (M/Male/F/Female): ";
            string genderInput;
            getline(cin, genderInput);
            
            string genderLower = genderInput;
            transform(genderLower.begin(), genderLower.end(), genderLower.begin(), ::tolower);
            
            if (genderLower == "m" || genderLower == "male" || 
                genderLower == "f" || genderLower == "female") {
                
                gender = toupper(genderLower[0]);
                validGender = true;
            } else {
                cout << "Invalid gender. Enter M, Male, F, or Female.\n";
            }
        }

        bool validAge = false;
        while (!validAge) {
            cout << "Enter age (1-100): ";
            string ageInput;
            getline(cin, ageInput);
            
            bool isNumeric = true;
            for (char c : ageInput) {
                if (!isdigit(c)) {
                    isNumeric = false;
                    break;
                }
            }
            
            if (!isNumeric) {
                cout << "Age must be a number.\n";
                continue;
            }
            
            try {
                age = stoi(ageInput);
                if (age >= 1 && age <= 100) {
                    validAge = true;
                } else {
                    cout << "Age must be between 1 and 100.\n";
                }
            } catch (...) {
                cout << "Invalid age entered.\n";
            }
        }

        if (age < 18) {
            cout << "\n--- Parent/Guardian Information (Required for patients under 18) ---\n";
            
            bool validParentName = false;
            while (!validParentName) {
                cout << "Enter parent/guardian full name: ";
                getline(cin, parentName);
                
                validParentName = true;
                for (char c : parentName) {
                    if (!isalpha(c) && c != ' ' && c != '.') {
                        validParentName = false;
                        cout << "Invalid name. Only letters, spaces, and dots are allowed.\n";
                        break;
                    }
                }
                
                if (parentName.empty() || parentName.find_first_not_of(' ') == string::npos) {
                    validParentName = false;
                    cout << "Parent/guardian name cannot be empty.\n";
                }
            }
            
            bool validRelationship = false;
            while (!validRelationship) {
                cout << "Enter relationship to patient (Mother/Father/Guardian/Other): ";
                getline(cin, parentRelationship);
                
                validRelationship = true;
                for (char c : parentRelationship) {
                    if (!isalpha(c) && c != ' ') {
                        validRelationship = false;
                        cout << "Invalid relationship. Only letters and spaces allowed.\n";
                        break;
                    }
                }
                
                if (parentRelationship.empty() || parentRelationship.find_first_not_of(' ') == string::npos) {
                    validRelationship = false;
                    cout << "Relationship cannot be empty.\n";
                }
            }
            
            bool validParentPhone = false;
            while (!validParentPhone) {
                cout << "Enter parent/guardian phone number (10 digits): ";
                string phoneInput;
                getline(cin, phoneInput);
                
                string cleanPhone = "";
                for (char c : phoneInput) {
                    if (isdigit(c)) {
                        cleanPhone += c;
                    }
                }
                
                if (cleanPhone.length() == 10) {
                    try {
                        parentPhone = stoll(cleanPhone);
                        validParentPhone = true;
                    } catch (...) {
                        cout << "Invalid phone number format.\n";
                    }
                } else {
                    cout << "Phone number must be 10 digits.\n";
                }
            }
            
            hasParentInfo = true;
            cout << "Parent/guardian information recorded.\n";
        } else {
            parentName = "";
            parentRelationship = "";
            parentPhone = 0;
            hasParentInfo = false;
        }

        bool validInsuranceCompany = false;
        while (!validInsuranceCompany) {
            cout << "Enter insurance company: ";
            getline(cin, insuranceCompany);
            
            validInsuranceCompany = true;
            for (char c : insuranceCompany) {
                if (!isalpha(c) && c != ' ' && c != '.') {
                    validInsuranceCompany = false;
                    cout << "Invalid company name. Only letters, spaces, and dots are allowed.\n";
                    break;
                }
            }
            
            // Check empty
            if (insuranceCompany.empty() || insuranceCompany.find_first_not_of(' ') == string::npos) {
                validInsuranceCompany = false;
                cout << "Insurance company cannot be empty.\n";
            }
        }

        bool validInsuranceNum = false;
        bool insuranceUnique = false;
        while (!validInsuranceNum || !insuranceUnique) {
            if (!validInsuranceNum) {
                cout << "Enter insurance number (1-9999): ";
                string insNumInput;
                getline(cin, insNumInput);
                
                bool isNumeric = true;
                for (char c : insNumInput) {
                    if (!isdigit(c)) {
                        isNumeric = false;
                        break;
                    }
                }
                
                if (!isNumeric) {
                    cout << "Insurance number must contain only digits.\n";
                    continue;
                }
                
                try {
                    insuranceNum = stoi(insNumInput);
                    if (insuranceNum >= 1 && insuranceNum <= 9999) {
                        validInsuranceNum = true;
                    } else {
                        cout << "Insurance number must be between 1 and 9999.\n";
                        continue;
                    }
                } catch (...) {
                    cout << "Invalid insurance number.\n";
                    continue;
                }
            }
            
            if (validInsuranceNum) {
                insuranceUnique = isInsuranceInfoUnique(insuranceCompany, insuranceNum);
                if (!insuranceUnique) {
                    cout << "Error: This insurance company and number combination is already registered with another patient.\n";
                    cout << "Please enter a different insurance company or number.\n";
                    
                    validInsuranceNum = false;
                    insuranceUnique = false;
                    
                    char choice;
                    cout << "Would you like to: \n";
                    cout << "1. Enter a different insurance company\n";
                    cout << "2. Enter a different insurance number\n";
                    cout << "3. Re-enter both\n";
                    cout << "Enter choice (1-3): ";
                    
                    string choiceInput;
                    getline(cin, choiceInput);
                    
                    if (choiceInput == "1") {
                        validInsuranceNum = true; 
                        validInsuranceCompany = false; 
                    } else if (choiceInput == "2") {
                        validInsuranceNum = false; 
                    } else if (choiceInput == "3") {
                        validInsuranceCompany = false;
                        validInsuranceNum = false;
                    } else {
                        validInsuranceCompany = false;
                        validInsuranceNum = false;
                    }
                }
            }
        }

        cout << "Enter diagnosis: ";
        getline(cin, diagnosis);

        medication.clear();
        string med;
        char choice;

        do {
            cout << "Enter medication name: ";
            getline(cin, med);
            
            bool validMed = true;
            for (char c : med) {
                if (!isalnum(c) && c != ' ' && c != '.' && c != '-' && c != '/' && c != '(' && c != ')') {
                    validMed = false;
                    cout << "Invalid medication name. Use letters, numbers, spaces, and common punctuation.\n";
                    break;
                }
            }
            
            if (validMed && !med.empty()) {
                medication.push_back(med);
                
                cout << "Add another medication? (y/n): ";
                cin >> choice;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else if (!validMed) {
                choice = 'y'; // Continue loop
            } else {
                cout << "Medication name cannot be empty.\n";
                choice = 'y'; // Continue loop
            }

        } while (choice == 'y' || choice == 'Y');

        stringstream ss;
        ss << name << "," << dob << "," << gender << "," << age << ","
           << insuranceCompany << "," << insuranceNum << "," << diagnosis;
        
        if (age < 18 && hasParentInfo) {
            ss << "," << parentName << "," << parentRelationship << "," << parentPhone;
        }
        
        for (size_t i = 0; i < medication.size(); i++) {
            ss << "," << medication[i];
        }

        addInformation(ss.str());

        cout << "\nPatient registered successfully.\n";
    }
    catch (exception& e) {
        cerr << "Registration error: " << e.what() << endl;
    }
}

// Displays patient information
void Patient::displayInfo() const {
    cout << "\n----- Patient Information -----\n";
    cout << "Name: " << name << endl;
    cout << "DOB: " << dob << endl;
    cout << "Gender: " << gender << endl;
    cout << "Age: " << age << endl;
    
    if (age < 18 && hasParentInfo) {
        cout << "\n--- Parent/Guardian Information ---\n";
        cout << "Parent/Guardian Name: " << parentName << endl;
        cout << "Relationship: " << parentRelationship << endl;
        cout << "Phone Number: " << parentPhone << endl;
    }
    
    cout << "\nInsurance Company: " << insuranceCompany << endl;
    cout << "Insurance Number: " << insuranceNum << endl;
    cout << "Diagnosis: " << diagnosis << endl;

    cout << "Medication: ";
    for (size_t i = 0; i < medication.size(); i++) {
        cout << medication[i];
        if (i < medication.size() - 1)
            cout << ", ";
    }

    cout << "\n--------------------------------\n";
}

void Patient::getInformation(const string& dob, const string& name) {
	if (this->name == name && this->dob == dob){
		displayInfo();
	} else {
		cout << "INCORRECT INFORMATION. You sure that you?" << endl;
	}
}

void Patient::requestAppointment() {
    cout << "\nAppointment request feature coming soon...\n";
}

// Getter 
string Patient::getName() const {
    return name;
}

string Patient::getDOB() const {
    return dob;
}

string Patient::getDiagnosis() const {
    return diagnosis;
}

bool Patient::hasParentInformation() const {
    return hasParentInfo;
}

string Patient::getParentName() const {
    return parentName;
}

string Patient::getParentRelationship() const {
    return parentRelationship;
}

long long Patient::getParentPhone() const {
    return parentPhone;
}
