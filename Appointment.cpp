// Appointment.cpp
#include "Appointment.h"
#include <limits>

// Defining a default constructor
Appointment::Appointment() {
    patientName = "";
    doctorName = "";
    date = "";
    time = "";
    reason = "";
}

// Constructor with the parameters
Appointment::Appointment(string p, string d, string da, string ti, string r) {
    patientName = p;
    doctorName = d;
    date = da;
    time = ti;
    reason = r;
}

// Creates an appointment by asking the user for all info
void Appointment::createAppointment() {
    // Clears any leftover newline characters so the getline command works properly
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Collect basic appointment information
    cout << "Enter Patient Name: ";
    getline(cin, patientName);

    cout << "Enter Doctor Name: ";
    getline(cin, doctorName);

    cout << "Enter Appointment Date (MM/DD/YYYY): ";
    getline(cin, date);

    cout << "Enter Appointment Time (HH:MM): ";
    getline(cin, time);

    cout << "Reason for Visit: ";
    getline(cin, reason);
}

// Saves appointment to appointments.txt file
void Appointment::saveAppointment() const {
    ofstream file("appointments.txt", ios::app);  // open for appending

    if (!file) {
        cerr << "Error opening appointments.txt\n";
        return;
    }

    // Write the appointment details into the file
    file << "PATIENT: " << patientName << "\n";
    file << "DOCTOR: " << doctorName << "\n";
    file << "DATE: " << date << "\n";
    file << "TIME: " << time << "\n";
    file << "REASON: " << reason << "\n";
    file << "---------------------------\n";

    file.close(); // close the file after writing
}

// Displays appointment information to the screen when called
void Appointment::displayAppointment() const {
    cout << "\n--- APPOINTMENT DETAILS ---\n";
    cout << "Patient: " << patientName << endl;
    cout << "Doctor : " << doctorName << endl;
    cout << "Date   : " << date << endl;
    cout << "Time   : " << time << endl;
    cout << "Reason : " << reason << endl;
    cout << "---------------------------\n";
}
