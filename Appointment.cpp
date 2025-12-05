// Appointment.cpp
#include "Appointment.h"
#include <iostream>
#include <fstream>
#include <limits>
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

// Create an appointment by asking the user for all info
void Appointment::createAppointment() {
    // Clear input buffer to avoid skipping getline
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

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

    cout << "\nAppointment created successfully!\n";
}

// Save appointment to file
void Appointment::saveAppointment() const {
    try {
        ofstream file("appointments.txt", ios::app);  // open for appending

        if (!file)
            throw runtime_error("Could not open appointments.txt for writing.");

        file << "PATIENT: " << patientName << "\n";
        file << "DOCTOR: " << doctorName << "\n";
        file << "DATE: " << date << "\n";
        file << "TIME: " << time << "\n";
        file << "REASON: " << reason << "\n";
        file << "---------------------------\n";

        file.close();
    }
    catch (exception& e) {
        cerr << "Error saving appointment: " << e.what() << endl;
    }
}

// Display appointment information
void Appointment::displayAppointment() const {
    cout << "\n--- APPOINTMENT DETAILS ---\n";
    cout << "Patient: " << patientName << endl;
    cout << "Doctor : " << doctorName << endl;
    cout << "Date   : " << date << endl;
    cout << "Time   : " << time << endl;
    cout << "Reason : " << reason << endl;
    cout << "---------------------------\n";
}