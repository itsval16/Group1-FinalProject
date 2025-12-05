#include <iostream>
#include <limits>
#include "Patient.h"
#include "Doctor.h"
#include "Appointment.h"
#include "Admin.h"

using namespace std;

int main() {
    Patient patient;
    Doctor doctor;
    Appointment appointment;
    Admin admin("SuperAdmin", 1); // default admin

    int choice;

    cout << "=========================================\n";
    cout << "   Welcome to the Medical Information System\n";
    cout << "=========================================\n";

    do {
        cout << "\nMain Menu\n";
        cout << "1. Register New Patient\n";
        cout << "2. Check Newly Registered Information\n";
        cout << "3. Register New Doctor\n";
        cout << "4. Display Doctor Information\n";
        cout << "5. Doctor Actions (View/Update Patient)\n";
        cout << "6. Create Appointment\n";
        cout << "7. Display Appointment\n";
        cout << "8. Admin Actions\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        try {
            if (choice < 1 || choice > 9)
                throw runtime_error("Invalid menu option.");
        }
        catch (exception& e) {
            cout << e.what() << endl;
            continue;
        }

        switch (choice) {
            case 1:
                patient.registerPatient();
                break;

            case 2: {
            	cin.ignore(numeric_limits<streamsize>::max(), '\n');
            	string pname,pdob;
            	cout << "Enter name: ";
                getline(cin, pname);
                cout << endl;

                cout << "Enter dob: ";
                getline(cin, pdob);
                cout << endl;

                patient.getInformation(pdob,pname);
                break;
			}
			
            case 3:
                // Use the static validation function
                doctor = Doctor::createDoctorWithValidation();
                cout << "Doctor registered successfully!\n";
                break;

            case 4:
                doctor.displayInfo();
                break;

            case 5: {
                int docChoice;
                cout << "\nDoctor Actions Menu\n";
                cout << "1. View Patient Information\n";
                cout << "2. Update Patient Record\n";
                cout << "Enter your choice: ";
                cin >> docChoice;

                if (docChoice == 1)
                    doctor.viewPatient();
                else if (docChoice == 2)
                    doctor.updatePatientRecord();
                else
                    cout << "Invalid choice.\n";
                break;
            }

            case 6:
                appointment.createAppointment();
                appointment.saveAppointment();
                break;

            case 7:
                appointment.displayAppointment();
                break;

            // In main.cpp, you could add to case 7 or create a new option:
case 8: { // New option to check available slots
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    string doctorName, date;
    
    cout << "Enter Doctor Name: ";
    getline(cin, doctorName);
    
    if (Appointment::validateName(doctorName)) {
        cout << "Enter Date to Check (MM/DD/YYYY): ";
        getline(cin, date);
        
        if (Appointment::validateDate(date)) {
            Appointment::displayAvailableSlots(doctorName, date);
        } else {
            cout << "Invalid date format.\n";
        }
    } else {
        cout << "Invalid doctor name.\n";
    }
    break;
}

            case 9:
                cout << "\nExiting system. Goodbye!\n";
                break;
        }

    } while (choice != 9);

    return 0;
}
