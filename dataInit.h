// GradPrixRecommender.h : Include file for standard system include files,
// or project specific include files.

#pragma once
#include<iostream>

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include <unordered_map>
#include <iomanip>

class DataInit {
private:
	// Used for driver dob for example
	struct Date {
		int year;
		int month;
		int day;
	};

	// Circuit related data
	struct CircuitData {
		int id;
		std::string ref;
		std::string name;
		std::string country;
	};

	std::vector<CircuitData> circuits;
	std::vector<CircuitData> readCircuitCSV();
	void setCircuits(std::vector<CircuitData>&);

	// Constructor related data
	struct ConstructorData {
		int id;
		std::string ref;
		std::string name;
		std::string country;
	};
	std::vector<ConstructorData> constructors;
	std::vector<ConstructorData> readConstructorCSV();
	void setConstructors(std::vector<ConstructorData>&);

	// Driver related data
	struct DriverData {
		int id;
		Date dob;
		std::string ref;
		std::string forename;
		std::string surname;
		std::string country;
	};

	std::vector<DriverData> drivers;
	std::vector<DriverData> readDriverCSV();
	void setDrivers(std::vector<DriverData>&);

public:
	void initializeData();
	std::vector<CircuitData> getCircuits();
	std::vector<ConstructorData> getConstructors();
	std::vector<DriverData> getDrivers();
};