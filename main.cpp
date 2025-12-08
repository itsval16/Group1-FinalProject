#include <iostream>
#include <limits>
#include "Patient.h"
#include "Doctor.h"
#include "Appointment.h"
#include "Admin.h"

using namespace std;

int main() { 
//CREATES CLASSES FOR THE MED INFO SYSTEM - VAL
    Patient patient; //OBJ FOR ALL PATIENT INFO
    Doctor doctor; //OBJ FOR ALL DOC INFO
    Appointment appointment;
    Admin admin("SuperAdmin", 1); // default admin

    int choice; 	//Variable to store user's menu choices

//display
    cout << "=========================================\n";
    cout << "   Welcome to the Medical Information System\n";
    cout << "=========================================\n";

    
	//main menu
	//contains a loop
	//loop will break untill usr chooses from menu or exits 
	do {
        cout << "\nMain Menu\n";
        cout << "1. Register New Patient\n";
        cout << "2. Check Newly Registered Information\n";
        cout << "3. Register New Doctor\n";
        cout << "4. Display Doctor Information\n";
        cout << "5. Doctor Actions (View/Update Patient)\n";
        cout << "6. Create Appointment\n";
        cout << "7. Display Appointment\n";
        cout << "8. Check Appointment Availability\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

//checks if the user's choices range from the menu 1-9 options 
        try {
            if (choice < 1 || choice > 9)
                throw runtime_error("Invalid menu option.");
        }
        //displays error messgae if it's not from 1-9
        //will show the menu again to choose again
        catch (exception& e) {
            cout << e.what() << endl;
            continue;
        }

        switch (choice) {
            case 1:
                patient.registerPatient(); //info for the patient's reg.
                break;

            case 2: { //new reg. patients 
            //info will be checked 
            	cin.ignore(numeric_limits<streamsize>::max(), '\n'); //clear input buffers
            	string pname,pdob; //stores
            	cout << "Enter name: ";
                getline(cin, pname);  
                cout << endl;

                cout << "Enter dob: ";
                getline(cin, pdob);
                cout << endl;

                patient.getInformation(pdob,pname); // will store and display the info entered
                break;
			}
			
            case 3:
                // reg new doc.
                doctor = Doctor::createDoctorWithValidation();
                cout << "Doctor registered successfully!\n";
                break;

            case 4:
                doctor.displayInfo(); //call to display doc info
                break;

            case 5: { //doc action menu
                int docChoice;
				 //displays doc menu
                cout << "\nDoctor Actions Menu\n";
                cout << "1. View Patient Information\n";
                cout << "2. Update Patient Record\n";
                cout << "Enter your choice: ";
                cin >> docChoice; //get doc choice

                if (docChoice == 1)
                    doctor.viewPatient();
                else if (docChoice == 2)
                    doctor.updatePatientRecord();
                else
                    cout << "Invalid choice.\n";
                break;
            }

            case 6:
                appointment.createAppointment(); //new app.
                appointment.saveAppointment(); //save app.
                break;

            case 7:
                appointment.displayAppointment(); //shows app. details 
                break;

           
case 8: { //admin option to check any app. that are avaliable 
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clears any inputs buffers
    
    string doctorName, date; //var. to store doc info
	    
    cout << "Enter Doctor Name (Dr.): ";
    getline(cin, doctorName);
    
   //uses static 
    if (Appointment::validateName(doctorName)) {
        cout << "Enter Date to Check (MM/DD/YYYY): "; //will use DOB to validate 
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
