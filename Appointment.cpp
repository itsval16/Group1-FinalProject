#include "Appointment.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <vector>
#include <iomanip>
using namespace std;

// Default constructor
Appointment::Appointment() {
    patientName = "";
    doctorName = "";
    date = "";
    time = "";
    reason = "";
}

// Parameterized constructor
Appointment::Appointment(string p, string d, string da, string ti, string r) {
    patientName = p;
    doctorName = d;
    date = da;
    time = ti;
    reason = r;
}

// Validation: Patient and Doctor names (letters and spaces only)
bool Appointment::isValidName(const string& name) const {
    if (name.empty()) return false;
    
    for (char c : name) {
        if (!isalpha(c) && c != ' ' && c != '.') {
            return false;
        }
    }
    return true;
}

// Validation: Date format MM/DD/YYYY with numbers only
bool Appointment::isValidDate(const string& date) const {
    if (date.length() != 10) return false;
    if (date[2] != '/' || date[5] != '/') return false;
    
    // Check each part for digits only
    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) continue; // Skip slashes
        if (!isdigit(date[i])) return false;
    }
    
    // Extract parts
    string monthStr = date.substr(0, 2);
    string dayStr = date.substr(3, 2);
    string yearStr = date.substr(6, 4);
    
    // Convert to numbers
    int month = stoi(monthStr);
    int day = stoi(dayStr);
    int year = stoi(yearStr);
    
    // Validate ranges
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;
    if (year < 1900 || year > 2100) return false;
    
    // Additional validation for months with 30 days
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
        return false;
    }
    
    // February validation (simplified - doesn't check leap years)
    if (month == 2 && day > 28) {
        return false;
    }
    
    return true;
}

// Validation: Time format HH:MM AM/PM with numbers only
bool Appointment::isValidTime(const string& time) const {
    // Check length (minimum 7 for "1:00 AM", maximum 8 for "12:00 PM")
    if (time.length() < 7 || time.length() > 8) return false;
    
    // Check for AM/PM suffix
    string timeLower = time;
    transform(timeLower.begin(), timeLower.end(), timeLower.begin(), ::tolower);
    
    bool hasAM = (timeLower.find("am") != string::npos);
    bool hasPM = (timeLower.find("pm") != string::npos);
    
    if (!hasAM && !hasPM) return false;
    
    // Extract time part (before AM/PM)
    size_t spacePos = time.find(' ');
    if (spacePos == string::npos) return false;
    
    string timePart = time.substr(0, spacePos);
    
    // Check for colon
    size_t colonPos = timePart.find(':');
    if (colonPos == string::npos) return false;
    
    // Extract hour and minute
    string hourStr = timePart.substr(0, colonPos);
    string minuteStr = timePart.substr(colonPos + 1);
    
    // Check if hour and minute are digits
    for (char c : hourStr) if (!isdigit(c)) return false;
    for (char c : minuteStr) if (!isdigit(c)) return false;
    
    // Convert to numbers
    int hour = stoi(hourStr);
    int minute = stoi(minuteStr);
    
    // Validate ranges
    if (hour < 1 || hour > 12) return false;
    if (minute < 0 || minute > 59) return false;
    
    // Check minute has 2 digits
    if (minuteStr.length() != 2) return false;
    
    return true;
}

// Validation: Reason (allows letters, numbers, spaces, and basic punctuation)
bool Appointment::isValidReason(const string& reason) const {
    if (reason.empty()) return false;
    
    for (char c : reason) {
        if (!isalnum(c) && c != ' ' && c != '.' && c != ',' && c != '!' && c != '?' && c != '-') {
            return false;
        }
    }
    return true;
}

// NEW FUNCTION: Check if appointment slot is already booked
bool Appointment::isSlotAvailable(const string& doctorName, const string& date, const string& time) const {
vector<Appointment> allAppointments = loadAllAppointments();
    
    for (const Appointment& apt : allAppointments) {
        if (apt.doctorName == doctorName && apt.date == date && apt.time == time) {
            return false; // Slot is already booked
        }
    }
    
    return true; // Slot is available
}

// Static validation functions (can be called without object)
bool Appointment::validateName(const string& name) {
    if (name.empty()) return false;
    
    for (char c : name) {
        if (!isalpha(c) && c != ' ' && c != '.') {
            return false;
        }
    }
    return true;
}

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

// Static time validation for AM/PM format
bool Appointment::validateTime(const string& time) {
    // Check length
    if (time.length() < 7 || time.length() > 8) return false;
    
    // Check for AM/PM
    string timeLower = time;
    transform(timeLower.begin(), timeLower.end(), timeLower.begin(), ::tolower);
    
    bool hasAM = (timeLower.find("am") != string::npos);
    bool hasPM = (timeLower.find("pm") != string::npos);
    
    if (!hasAM && !hasPM) return false;
    
    // Extract time part
    size_t spacePos = time.find(' ');
    if (spacePos == string::npos) return false;
    
    string timePart = time.substr(0, spacePos);
    
    // Check for colon
    size_t colonPos = timePart.find(':');
    if (colonPos == string::npos) return false;
    
    // Extract hour and minute
    string hourStr = timePart.substr(0, colonPos);
    string minuteStr = timePart.substr(colonPos + 1);
    
    // Check if digits
    for (char c : hourStr) if (!isdigit(c)) return false;
    for (char c : minuteStr) if (!isdigit(c)) return false;
    
    // Convert to numbers
    int hour = stoi(hourStr);
    int minute = stoi(minuteStr);
    
    // Validate ranges
    if (hour < 1 || hour > 12) return false;
    if (minute < 0 || minute > 59) return false;
    if (minuteStr.length() != 2) return false;
    
    return true;
}

// NEW: Static function to check slot availability
bool Appointment::checkSlotAvailability(const string& doctorName, const string& date, const string& time) {
    // Create a temporary const Appointment object to call the const member function
    const Appointment tempAppt;
    return tempAppt.isSlotAvailable(doctorName, date, time);
}

// Helper function to format time consistently
string formatTime(const string& time) {
    string timeLower = time;
    transform(timeLower.begin(), timeLower.end(), timeLower.begin(), ::tolower);
    
    // Extract parts
    size_t spacePos = time.find(' ');
    if (spacePos == string::npos) return time;
    
    string timePart = time.substr(0, spacePos);
    string ampm = time.substr(spacePos + 1);
    
    // Convert ampm to uppercase
    transform(ampm.begin(), ampm.end(), ampm.begin(), ::toupper);
    
    return timePart + " " + ampm;
}

// Create an appointment with validation
void Appointment::createAppointment() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    cout << "\n=== CREATE NEW APPOINTMENT ===\n";
    
    // Patient Name (letters and spaces only)
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
    
    // Doctor Name (letters and spaces only)
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
    
    // Date (MM/DD/YYYY format with numbers only)
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
    
    // Time (HH:MM AM/PM format with numbers only)
    bool validTime = false;
    bool slotAvailable = false;
    string currentTime;
    
    while (!validTime || !slotAvailable) {
        if (!validTime) {
            cout << "Enter Appointment Time (HH:MM AM/PM): ";
            getline(cin, currentTime);
            
            if (isValidTime(currentTime)) {
                // Format time consistently
                currentTime = formatTime(currentTime);
                time = currentTime;
                validTime = true;
                
                // Now check if slot is available
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
    
    // Reason (allows letters, numbers, spaces, and basic punctuation)
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

// Save appointment to file with CSV format
void Appointment::saveAppointment() const {
    try {
        // Validate all fields before saving
        if (!isValidName(patientName) || 
            !isValidName(doctorName) || 
            !isValidDate(date) || 
            !isValidTime(time) || 
            !isValidReason(reason)) {
            throw runtime_error("Cannot save appointment: Invalid data detected.");
        }
        
        // Double-check slot availability before saving
        if (!isSlotAvailable(doctorName, date, time)) {
            throw runtime_error("Cannot save appointment: Time slot is no longer available.");
        }
        
        ofstream file("appointments.txt", ios::app);
        
        if (!file)
            throw runtime_error("Could not open appointments.txt for writing.");
        
        // Use pipe-separated format for better parsing
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

// Display appointment information
void Appointment::displayAppointment() const {
    cout << "\n=== APPOINTMENT DETAILS ===\n";
    cout << "Patient: " << patientName << endl;
    cout << "Doctor : Dr. " << doctorName << endl;
    cout << "Date   : " << date << endl;
    cout << "Time   : " << time << endl;
    cout << "Reason : " << reason << endl;
    cout << "===========================\n";
}

// Load all appointments from file
vector<Appointment> Appointment::loadAllAppointments() {
    vector<Appointment> appointments;
    
    try {
        ifstream file("appointments.txt");
        
        if (!file) {
            return appointments; // Return empty if file doesn't exist
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

// NEW: Display available time slots for a doctor on a specific date
void Appointment::displayAvailableSlots(const string& doctorName, const string& date) {
    vector<Appointment> allAppointments = loadAllAppointments();
    vector<string> bookedTimes;
    
    // Get all booked times for this doctor on this date
    for (const Appointment& apt : allAppointments) {
        if (apt.doctorName == doctorName && apt.date == date) {
            bookedTimes.push_back(apt.time);
        }
    }
    
    // Define available time slots (standard office hours)
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

// Display all appointments
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

// Search appointments by patient name
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

// Search appointments by doctor name
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

// NEW: Check for scheduling conflicts
bool Appointment::hasSchedulingConflict(const Appointment& newAppointment) {
    vector<Appointment> allAppointments = loadAllAppointments();
    
    for (const Appointment& existing : allAppointments) {
        // Check if same doctor has appointment at same date and time
        if (existing.doctorName == newAppointment.doctorName &&
            existing.date == newAppointment.date &&
            existing.time == newAppointment.time) {
            return true; // Conflict found
        }
        
        // Optional: Also check if same patient has overlapping appointments
        if (existing.patientName == newAppointment.patientName &&
            existing.date == newAppointment.date &&
            existing.time == newAppointment.time) {
            return true; // Patient double-booking conflict
        }
    }
    
    return false; // No conflicts
}

// Operator overload implementations
bool Appointment::operator>(const Appointment& other) const {
    // Compare dates first
    if (date != other.date) {
        return date > other.date;
    }
    
    // If same date, compare times
    // Convert times to comparable format (simplified - for real system, parse properly)
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
