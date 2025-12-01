// MedicalInformaion.h
#ifndef MEDICALINFORMATION_H
#define MEDICALINFORMATION_H

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

class MedicalInformation {
	private:
		static fstream medicalInfo;
	public:
		void addInformation(const string& dob);
		void modifyInformation(const string& dob, const string& name, const string& newInfo);
		void getInformation(const string& dob, const string& name);
};

#endif
