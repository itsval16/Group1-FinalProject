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
		void addInformation();
		void modifyInformation();
		void getInformation();
};

#endif

