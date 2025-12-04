// Appointment.h
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
    string date;   // MM/DD/YYYY
    string time;   // HH:MM
    string reason; // reason for visit

public:
    Appointment();
    Appointment(string pName, string dName, string date, string time, string reason);

    void createAppointment();     // patient input for creating appointment
    void saveAppointment() const; // save to file so we can have a list of all appointments
    void displayAppointment() const; // prints the information if necessary 

    // Getters to retrieve the variables that were set in the private member function
    string getPatient() const { return patientName; }
    string getDoctor() const { return doctorName; }
};

#endif
