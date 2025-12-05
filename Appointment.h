#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Appointment {
private:
    string patientName;
    string doctorName;
    string date;    // MM/DD/YYYY
    string time;    // HH:MM AM/PM
    string reason;  // reason for visit
    
    //functions
    bool isValidName(const string& name) const;
    bool isValidDate(const string& date) const;
    bool isValidTime(const string& time) const;
    bool isValidReason(const string& reason) const;
    
    //const
    bool isSlotAvailable(const string& doctorName, const string& date, const string& time) const;

public:
    //constructor
    Appointment(); 
    Appointment(string pName, string dName, string date, string time, string reason);

    
    void createAppointment(); //collect appointment info from user
    void saveAppointment() const; // Save appointment to file
    void displayAppointment() const; 
    
    
    static bool validateName(const string& name);
    static bool validateDate(const string& date);
    static bool validateTime(const string& time);
    
    
    static vector<Appointment> loadAllAppointments();
    static void displayAllAppointments();
    static vector<Appointment> searchByPatient(const string& patientName);
    static vector<Appointment> searchByDoctor(const string& doctorName);
    
 
    static bool checkSlotAvailability(const string& doctorName, const string& date, const string& time);
    static void displayAvailableSlots(const string& doctorName, const string& date);
    static bool hasSchedulingConflict(const Appointment& newAppointment);

   
    string getPatient() const { return patientName; }
    string getDoctor() const { return doctorName; }
    string getDate() const { return date; }
    string getTime() const { return time; }
    string getReason() const { return reason; }
    
    //operator overloaad
    bool operator>(const Appointment& other) const;
    bool operator==(const Appointment& other) const;
    friend ostream& operator<<(ostream& out, const Appointment& app);
};

#endif
