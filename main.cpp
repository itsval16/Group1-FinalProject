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
			
            case 3: {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                string name, specialty;
                int password;

                cout << "Enter doctor's name: ";
                getline(cin, name);

                cout << "Enter doctor's specialty: ";
                getline(cin, specialty);

                cout << "Enter doctor's password (numeric): ";
                cin >> password;

                doctor = Doctor(name, specialty, password);
                cout << "Doctor registered successfully!\n";
                break;
            }

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

            case 8: {
                int adminChoice;
                cout << "\nAdmin Actions Menu\n";
                cout << "1. Add Doctor\n";
                cout << "2. Remove Doctor\n";
                cout << "3. View Patient Record\n";
                cout << "4. Update Patient Record\n";
                cout << "5. Display Admin Info\n";
                cout << "Enter your choice: ";
                cin >> adminChoice;

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (adminChoice == 1) {
                    string info;
                    cout << "Enter doctor info (CSV format): ";
                    getline(cin, info);
                    admin.addDoctor(info);
                }
                else if (adminChoice == 2) {
                    string doctorName;
                    cout << "Enter doctor name to remove: ";
                    getline(cin, doctorName);
                    admin.removeDoctor(doctorName);
                }
                else if (adminChoice == 3) {
                    string name, dob;
                    cout << "Enter patient full name: ";
                    getline(cin, name);
                    cout << "Enter patient DOB: ";
                    getline(cin, dob);
                    admin.viewPatients(dob, name);
                }
                else if (adminChoice == 4) {
                    string name, dob, newInfo;
                    cout << "Enter patient full name: ";
                    getline(cin, name);
                    cout << "Enter patient DOB: ";
                    getline(cin, dob);
                    cout << "Enter updated patient info (CSV format): ";
                    getline(cin, newInfo);
                    admin.updatePatient(dob, name, newInfo);
                }
                else if (adminChoice == 5) {
                    admin.displayInfo();
                }
                else {
                    cout << "Invalid choice.\n";
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
