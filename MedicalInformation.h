// MedicalInformaion.h
#ifndef MEDICALINFORMATION_H
#define MEDICALINFORMATION_H

#include <iostream>
#include <fstream>

using namespace std;

class MedicalInformation {
	private:
		static fstream medicalInfo;
	public:
		void addInformation(const string& info);
		void modifyInformation(const string& dob);
		void getInformation();
};

#endif



