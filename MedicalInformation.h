// MedicalInformaion.h
#ifndef MEDICALINFORMATION_H
#define MEDICALINFORMATION_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class MedicalInformation {
	protected:
		fstream medicalInfo;
	public:
		void addInformation(const string& info); //adds new medinfo
		void modifyInformation(const string& dob, const string& name, const string& newInfo); //controls mods
		void getInformation(const string& dob, const string& name); //displays medinfo (can be looked up)
};

#endif


