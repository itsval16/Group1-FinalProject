#include <iostream>
#include <string>
#include "MedicalInformation.h"

using namespace std;

int main() {
    MedicalInformation medInfo;
    string input;

    cout << "Welcome to the Medical Information System!" << endl;

    while (true) {
        cout << "\nEnter patient information (or type 'exit' to quit): ";
        getline(cin, input);

        if (input == "exit") {
            cout << "\nExiting program. Goodbye!" << endl;
            break;
        }

        medInfo.addInformation(input);
        cout << "Information saved successfully!" << endl;
    }

    return 0;
}
