#include "Appointment.h"
#include <iostream>
#include <fstream>
#include <limits> //cin.igonre!
#include <algorithm> //string man.
#include <cctype> //char. class
#include <sstream>
#include <vector>
#include <iomanip>
using namespace std;

// constructor
Appointment::Appointment() { // initializes all the member var.(empty strings)
    patientName = "";
    doctorName = "";
    date = "";
    time = "";
    reason = "";
}

// parameterized constructors
// chars: p-patient name, d-doctor name, da-date, ti-time, r-reason
Appointment::Appointment(string p, string d, string da, string ti, string r) {
    patientName = p;
    doctorName = d;
    date = da;
    time = ti;
    reason = r;
}

// checks if the inputs are (letters and spaces only)
bool Appointment::isValidName(const string& name) const {
    if (name.empty()) return false; //no name, no next step!
    
   
   //checks here the chars.
    for (char c : name) {
        if (!isalpha(c) && c != ' ' && c != '.') {
            return false;
        }
    }
    return true;
}

// checks if the format MM/DD/YYYY is with numbers only (INPUT)
bool Appointment::isValidDate(const string& date) const {
    if (date.length() != 10) return false; //date length is ten dig.
    if (date[2] != '/' || date[5] != '/') return false; //cheks possitions mm/ = 0,1,2
    
    // digits only (//)
    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) continue; // Skip slashes
        if (!isdigit(date[i])) return false;
    }
    
    // substrings for the date format
    string monthStr = date.substr(0, 2);
    string dayStr = date.substr(3, 2);
    string yearStr = date.substr(6, 4);
    
    // converts the strings to numbers
    int month = stoi(monthStr);
    int day = stoi(dayStr);
    int year = stoi(yearStr);
    
    // reviews if it's in between the ranges of the calender 
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false; //take into account to months wiht leap years!!-val
    if (year < 1900 || year > 2100) return false;
    
    //  months with 30 days
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
        return false;
    }
    

    // february (doesn't check leap years)
    if (month == 2 && day > 28) {
        return false;
    }
    
    return true;
}

//  HH:MM AM/PM with numbers only
bool Appointment::isValidTime(const string& time) const {
    // check length (minimum 7 for "1:00 AM", maximum 8 for "12:00 PM")
    if (time.length() < 7 || time.length() > 8) return false;
    
    // review AM/PM
    string timeLower = time;
    transform(timeLower.begin(), timeLower.end(), timeLower.begin(), ::tolower);
    
    bool hasAM = (timeLower.find("am") != string::npos);
    bool hasPM = (timeLower.find("pm") != string::npos);
    
    if (!hasAM && !hasPM) return false; //mist have am and Pm
    
    // take time only
    size_t spacePos = time.find(' ');
    if (spacePos == string::npos) return false;
    
    string timePart = time.substr(0, spacePos);
    
    // sees the :
    size_t colonPos = timePart.find(':');
    if (colonPos == string::npos) return false;
    
    // take the hour and min.
    string hourStr = timePart.substr(0, colonPos);
    string minuteStr = timePart.substr(colonPos + 1);
    
    // reviews if the time are dig. not letters
    for (char c : hourStr) if (!isdigit(c)) return false;
    for (char c : minuteStr) if (!isdigit(c)) return false;
    
    // string to nub.
    int hour = stoi(hourStr);
    int minute = stoi(minuteStr);
    
    // reviews the hour an dtime ranges (hour 12) (minutes 59)
    if (hour < 1 || hour > 12) return false;
    if (minute < 0 || minute > 59) return false;
    
    // minutes must have 2 dig. (01 or 59)
    if (minuteStr.length() != 2) return false;
    
    return true;
}

// allows letters, numbers, spaces
bool Appointment::isValidReason(const string& reason) const {
    if (reason.empty()) return false;
    
    for (char c : reason) {
        if (!isalnum(c) && c != ' ' && c != '.' && c != ',' && c != '!' && c != '?' && c != '-') {
            return false;
        }
    }
    return true;
}

// check if appointment slot is already booked (for the doc.)
bool Appointment::isSlotAvailable(const string& doctorName, const string& date, const string& time) const {
vector<Appointment> allAppointments = loadAllAppointments();
    
    for (const Appointment& apt : allAppointments) {
        if (apt.doctorName == doctorName && apt.date == date && apt.time == time) {
            return false; //slot is already booked!!!
        }
    }
    
    return true; //slot is available
}

//chedks the name 
bool Appointment::validateName(const string& name) {
    if (name.empty()) return false;
    
    for (char c : name) {
        if (!isalpha(c) && c != ' ' && c != '.') {
            return false;
        }
    }
    return true;
}
 
 //reviews the date as well 
 //not vaild 
bool Appointment::validateDate(const string& date) {
    if (date.length() != 10) return false;
    if (date[2] != '/' || date[5] != '/') return false;
    
    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) continue;
        if (!isdigit(date[i])) return false;
    }
    
    string monthStr = date.substr(0, 2);
    string dayStr = date.substr(3, 2);
    string yearStr = date.substr(6, 4);
    
    int month = stoi(monthStr);
    int day = stoi(dayStr);
    int year = stoi(yearStr);
    
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;
    if (year < 1900 || year > 2100) return false;
    
    return true;
}

bool Appointment::validateTime(const string& time) {
    if (time.length() < 7 || time.length() > 8) return false;
    
    string timeLower = time;
    transform(timeLower.begin(), timeLower.end(), timeLower.begin(), ::tolower);
    
    bool hasAM = (timeLower.find("am") != string::npos);
    bool hasPM = (timeLower.find("pm") != string::npos);
    
    if (!hasAM && !hasPM) return false;
    
    size_t spacePos = time.find(' ');
    if (spacePos == string::npos) return false;
    
    string timePart = time.substr(0, spacePos);
    
    size_t colonPos = timePart.find(':');
    if (colonPos == string::npos) return false;
    
    //extract
    string hourStr = timePart.substr(0, colonPos);
    string minuteStr = timePart.substr(colonPos + 1);
    
    for (char c : hourStr) if (!isdigit(c)) return false;
    for (char c : minuteStr) if (!isdigit(c)) return false;
    
    int hour = stoi(hourStr);
    int minute = stoi(minuteStr);
    
    if (hour < 1 || hour > 12) return false;
    if (minute < 0 || minute > 59) return false;
    if (minuteStr.length() != 2) return false;
    
    return true;
}


//USE OF CHATGPT: Create a way to review the slot of Apopintments Available 
bool Appointment::checkSlotAvailability(const string& doctorName, const string& date, const string& time) {
    const Appointment tempAppt;
    return tempAppt.isSlotAvailable(doctorName, date, time);
}

string formatTime(const string& time) {
    string timeLower = time;
    transform(timeLower.begin(), timeLower.end(), timeLower.begin(), ::tolower);
    
    size_t spacePos = time.find(' ');
    if (spacePos == string::npos) return time;
    
    string timePart = time.substr(0, spacePos);
    string ampm = time.substr(spacePos + 1);
    
    transform(ampm.begin(), ampm.end(), ampm.begin(), ::toupper);
    
    return timePart + " " + ampm;
}
//USE OF CHATGPT: figure a method to allow certian inputs to be accepted
void Appointment::createAppointment() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    cout << "\n=== CREATE NEW APPOINTMENT ===\n";
    
    //patient Name (letters and spaces only)
    bool validPatientName = false;
    while (!validPatientName) {
        cout << "Enter Patient Name (letters and spaces only): ";
        getline(cin, patientName);
        
        if (isValidName(patientName)) {
            validPatientName = true;
        } else {
            cout << "Invalid name. Use only letters and spaces.\n";
        }
    }
    
    //doctor Name (letters and spaces only)
    bool validDoctorName = false;
    string currentDoctor;
    while (!validDoctorName) {
        cout << "Enter Doctor Name (letters and spaces only): ";
        getline(cin, currentDoctor);
        
        if (isValidName(currentDoctor)) {
            doctorName = currentDoctor;
            validDoctorName = true;
        } else {
            cout << "Invalid doctor name. Use only letters and spaces.\n";
        }
    }
    
    bool validDate = false;
    string currentDate;
    while (!validDate) {
        cout << "Enter Appointment Date (MM/DD/YYYY): ";
        getline(cin, currentDate);
        
        if (isValidDate(currentDate)) {
            date = currentDate;
            validDate = true;
        } else {
            cout << "Invalid date. Use MM/DD/YYYY format with numbers only.\n";
            cout << "Example: 12/25/2024\n";
        }
    }
    
    bool validTime = false;
    bool slotAvailable = false;
    string currentTime;
    
    while (!validTime || !slotAvailable) {
        if (!validTime) {
            cout << "Enter Appointment Time (HH:MM AM/PM): ";
            getline(cin, currentTime);
            
            if (isValidTime(currentTime)) {
                currentTime = formatTime(currentTime);
                time = currentTime;
                validTime = true;
                
                slotAvailable = isSlotAvailable(doctorName, date, time);
                
                if (!slotAvailable) {
                    cout << "Error: This time slot is already booked for Dr. " << doctorName << " on " << date << ".\n";
                    cout << "Please choose a different time.\n";
                    validTime = false; // Reset to get new time
                }
            } else {
                cout << "Invalid time. Use HH:MM AM/PM format with numbers only.\n";
                cout << "Examples: 9:00 AM, 2:30 PM, 11:15 AM\n";
            }
        }
    }
    
    bool validReason = false;
    while (!validReason) {
        cout << "Reason for Visit: ";
        getline(cin, reason);
        
        if (isValidReason(reason)) {
            validReason = true;
        } else {
            cout << "Invalid reason. Use letters, numbers, spaces, and basic punctuation only.\n";
        }
    }
    
    cout << "\nAppointment created successfully!\n";
    cout << "Dr. " << doctorName << " on " << date << " at " << time << " is confirmed.\n";
}

void Appointment::saveAppointment() const {
    try {
        if (!isValidName(patientName) || 
            !isValidName(doctorName) || 
            !isValidDate(date) || 
            !isValidTime(time) || 
            !isValidReason(reason)) {
            throw runtime_error("Cannot save appointment: Invalid data detected.");
        }
        
        if (!isSlotAvailable(doctorName, date, time)) {
            throw runtime_error("Cannot save appointment: Time slot is no longer available.");
        }
        
        ofstream file("appointments.txt", ios::app);
        
        if (!file)
            throw runtime_error("Could not open appointments.txt for writing.");
        
        file << patientName << "|"
             << doctorName << "|"
             << date << "|"
             << time << "|"
             << reason << endl;
        
        file.close();
        cout << "Appointment saved to file successfully!\n";
    }
    catch (exception& e) {
        cerr << "Error saving appointment: " << e.what() << endl;
    }
}

void Appointment::displayAppointment() const {
    cout << "\n=== APPOINTMENT DETAILS ===\n";
    cout << "Patient: " << patientName << endl;
    cout << "Doctor : Dr. " << doctorName << endl;
    cout << "Date   : " << date << endl;
    cout << "Time   : " << time << endl;
    cout << "Reason : " << reason << endl;
    cout << "===========================\n";
}

vector<Appointment> Appointment::loadAllAppointments() {
    vector<Appointment> appointments;
    
    try {
        ifstream file("appointments.txt");
        
        if (!file) {
            return appointments; //return empty if file doesn't exist
        }
        
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            vector<string> fields;
            string field;
            
            while (getline(ss, field, '|')) {
                fields.push_back(field);
            }
            
            if (fields.size() >= 5) {
                Appointment apt(fields[0], fields[1], fields[2], fields[3], fields[4]);
                appointments.push_back(apt);
            }
        }
        
        file.close();
        
    } catch (exception& e) {
        cerr << "Error loading appointments: " << e.what() << endl;
    }
    
    return appointments;
}

void Appointment::displayAvailableSlots(const string& doctorName, const string& date) {
    vector<Appointment> allAppointments = loadAllAppointments();
    vector<string> bookedTimes;
    
    for (const Appointment& apt : allAppointments) {
        if (apt.doctorName == doctorName && apt.date == date) {
            bookedTimes.push_back(apt.time);
        }
    }
    
    vector<string> allSlots = {
        "9:00 AM", "9:30 AM", "10:00 AM", "10:30 AM", 
        "11:00 AM", "11:30 AM", "12:00 PM", "12:30 PM",
        "1:00 PM", "1:30 PM", "2:00 PM", "2:30 PM",
        "3:00 PM", "3:30 PM", "4:00 PM", "4:30 PM"
    };
    
    cout << "\n=== AVAILABLE SLOTS FOR Dr. " << doctorName << " ON " << date << " ===\n";
    
    if (bookedTimes.empty()) {
        cout << "All slots are available!\n";
    }
    
    bool foundAvailable = false;
    for (const string& slot : allSlots) {
        bool isBooked = false;
        for (const string& booked : bookedTimes) {
            if (slot == booked) {
                isBooked = true;
                break;
            }
        }
        
        if (!isBooked) {
            cout << "• " << slot << " (Available)\n";
            foundAvailable = true;
        } else {
            cout << "• " << slot << " (BOOKED)\n";
        }
    }
    
    if (!foundAvailable) {
        cout << "No available slots for this date.\n";
    }
    
    cout << "================================================\n";
}

void Appointment::displayAllAppointments() {
    vector<Appointment> appointments = loadAllAppointments();
    
    if (appointments.empty()) {
        cout << "\nNo appointments scheduled.\n";
        return;
    }
    
    cout << "\n=== ALL SCHEDULED APPOINTMENTS ===\n";
    for (size_t i = 0; i < appointments.size(); i++) {
        cout << "\nAppointment #" << (i + 1) << ":\n";
        appointments[i].displayAppointment();
    }
    cout << "==================================\n";
}

vector<Appointment> Appointment::searchByPatient(const string& patientName) {
    vector<Appointment> allAppointments = loadAllAppointments();
    vector<Appointment> results;
    
    for (const Appointment& apt : allAppointments) {
        if (apt.patientName == patientName) {
            results.push_back(apt);
        }
    }
    
    return results;
}

vector<Appointment> Appointment::searchByDoctor(const string& doctorName) {
    vector<Appointment> allAppointments = loadAllAppointments();
    vector<Appointment> results;
    
    for (const Appointment& apt : allAppointments) {
        if (apt.doctorName == doctorName) {
            results.push_back(apt);
        }
    }
    
    return results;
}

bool Appointment::hasSchedulingConflict(const Appointment& newAppointment) {
    vector<Appointment> allAppointments = loadAllAppointments();
    
    for (const Appointment& existing : allAppointments) {
        if (existing.doctorName == newAppointment.doctorName &&
            existing.date == newAppointment.date &&
            existing.time == newAppointment.time) {
            return true; 
        }
        
        if (existing.patientName == newAppointment.patientName &&
            existing.date == newAppointment.date &&
            existing.time == newAppointment.time) {
            return true;
        }
    }
    
    return false; 
}

bool Appointment::operator>(const Appointment& other) const {
    
    if (date != other.date) {
        return date > other.date;
    }
    
    
    return time > other.time;
}

bool Appointment::operator==(const Appointment& other) const {
    return patientName == other.patientName &&
           doctorName == other.doctorName &&
           date == other.date &&
           time == other.time;
}

ostream& operator<<(ostream& out, const Appointment& app) {
    out << "Appointment: " << app.patientName << " with Dr. " << app.doctorName 
        << " on " << app.date << " at " << app.time;
    return out;
    
    
}
