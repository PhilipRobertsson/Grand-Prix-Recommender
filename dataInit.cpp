
#include "dataInit.h"
#include <windows.h>
#include <filesystem>

namespace {
	std::string removeQuotes(const std::string& value) {
		if (value.size() >= 2 && value.front() == '"' && value.back() == '"') {
			return value.substr(1, value.size() - 2);
		}
		return value;
	}

	std::string resolveDataPath(const std::string& filename) {
		wchar_t exePath[MAX_PATH];
		const DWORD length = GetModuleFileNameW(NULL, exePath, MAX_PATH);
		if (length == 0 || length >= MAX_PATH) {
			return filename;
		}
		const std::filesystem::path exeDir = std::filesystem::path(exePath).parent_path();
		return (exeDir / "data" / filename).string();
	}
}

std::vector<DataInit::CircuitData> DataInit::readCircuitCSV() {
	std::vector<CircuitData> circuits;
	const std::string path = resolveDataPath("circuits.csv");
	std::ifstream file(path);

	if (!file.is_open()) {
		wxMessageBox("Failed to open circuit data from file: \n" + path, "Error");
		std::cerr << "Failed to open data file: " << path;
		return circuits;
	}

	std::string line;
	std::getline(file, line); // Skips the header

	while (std::getline(file, line)) {
		std::stringstream ss(line);
		CircuitData circuit;
		std::string id_str;

		if (std::getline(ss, id_str, ',') &&
			std::getline(ss, circuit.ref, ',') &&
			std::getline(ss, circuit.name, ',') &&
			std::getline(ss, circuit.country, ',')) {
			circuit.id = std::stoi(id_str);
			circuit.ref = removeQuotes(circuit.ref);
			circuit.name = removeQuotes(circuit.name);
			circuit.country = removeQuotes(circuit.country);
			circuits.push_back(circuit);
		}

	}
	file.close();
	DataInit::setCircuits(circuits);
	return circuits;
};
std::vector<DataInit::ConstructorData> DataInit::readConstructorCSV() {
	std::vector<ConstructorData> constructors;
	const std::string path = resolveDataPath("constructors.csv");
	std::ifstream file(path);

	if (!file.is_open()) {
		wxMessageBox("Failed to open constructor data from file: \n" + path, "Error");
		std::cerr << "Failed to open data file: " << path;
		return constructors;
	}

	std::string line;
	std::getline(file, line); // Skips the header

	while (std::getline(file, line)) {
		std::stringstream ss(line);
		ConstructorData constructor;
		std::string id_str;

		if (std::getline(ss, id_str, ',') &&
			std::getline(ss, constructor.ref, ',') &&
			std::getline(ss, constructor.name, ',') &&
			std::getline(ss, constructor.country, ',')) {
			constructor.id = std::stoi(id_str);
			constructor.ref = removeQuotes(constructor.ref);
			constructor.name = removeQuotes(constructor.name);
			constructor.country = removeQuotes(constructor.country);
			constructors.push_back(constructor);
		}
	}
	file.close();
	DataInit::setConstructors(constructors);
	return constructors;
}
std::vector<DataInit::DriverData> DataInit::readDriverCSV() {
	std::vector<DataInit::DriverData> drivers;
	const std::string path = resolveDataPath("drivers.csv");
	std::ifstream file(path);

	if (!file.is_open()) {
		wxMessageBox("Failed to open driver data from file: \n" + path, "Error");
		std::cerr << "Failed to open data file: " << path;
		return drivers;
	}
	std::string line;
	std::getline(file, line); // Skips the header

	while (std::getline(file, line)) {
		std::stringstream ss(line);
		DriverData driver;
		std::string id_str,dob_str, skip;

		if (std::getline(ss, id_str, ',') &&
			std::getline(ss, driver.ref, ',') &&
			std::getline(ss, skip, ',') &&
			std::getline(ss, skip, ',') &&
			std::getline(ss, driver.forename, ',') &&
			std::getline(ss, driver.surname, ',') &&
			std::getline(ss, dob_str, ',') &&
			std::getline(ss, driver.country, ',')){
			driver.id = std::stoi(id_str);
			driver.dob.year = std::stoi(removeQuotes(dob_str).substr(0, 4));
			driver.dob.month = std::stoi(removeQuotes(dob_str).substr(5, 7));
			driver.dob.month = std::stoi(removeQuotes(dob_str).substr(8, 10));
			driver.ref = removeQuotes(driver.ref);
			driver.forename = removeQuotes(driver.forename);
			driver.surname = removeQuotes(driver.surname);
			driver.country = removeQuotes(driver.country);
			drivers.push_back(driver);
		}
	}
	file.close();
	DataInit::setDrivers(drivers);
	return drivers;
}

void DataInit::initializeData() {
	readCircuitCSV();
	readConstructorCSV();
	readDriverCSV();
}

void DataInit::setCircuits(std::vector<DataInit::CircuitData>& circuits) {
	this->circuits = circuits;
}
std::vector<DataInit::CircuitData> DataInit::getCircuits() {
	return this->circuits;
}

void DataInit::setConstructors(std::vector<DataInit::ConstructorData>& constructors) {
	this->constructors = constructors;
}
std::vector<DataInit::ConstructorData> DataInit::getConstructors() {
	return this->constructors;
}

void DataInit::setDrivers(std::vector<DataInit::DriverData>& drivers) {
	this->drivers = drivers;
}
std::vector<DataInit::DriverData> DataInit::getDrivers() {
	return this->drivers;
}