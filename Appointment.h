#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Appointment {
private:
    string patientName;
    string doctorName;
    string date;    // MM/DD/YYYY
    string time;    // HH:MM
    string reason;  // Reason for visit

public:
    // Constructors
    Appointment();  // Default
    Appointment(string pName, string dName, string date, string time, string reason);

    // Appointment actions
    void createAppointment();        // Collect appointment info from user
    void saveAppointment() const;    // Save appointment to file
    void displayAppointment() const; // Display appointment info

    // Getters
    string getPatient() const { return patientName; }
    string getDoctor() const { return doctorName; }
    string getDate() const { return date; }
    string getTime() const { return time; }
    string getReason() const { return reason; }
};

#endif