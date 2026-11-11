
#include "dataInit.h"
#include <windows.h>
#include <filesystem>

namespace {
	std::string stripQuotes(const std::string& value) {
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
			std::getline(ss, circuit.circuitRef, ',') &&
			std::getline(ss, circuit.name, ',') &&
			std::getline(ss, circuit.country, ',')) {
			circuit.id = std::stoi(id_str);
			circuit.circuitRef = stripQuotes(circuit.circuitRef);
			circuit.name = stripQuotes(circuit.name);
			circuit.country = stripQuotes(circuit.country);
			circuits.push_back(circuit);
		}

	}
	file.close();
	DataInit::setCircuits(circuits);
	return circuits;
};

void DataInit::setCircuits(std::vector<DataInit::CircuitData>& circuits) {
	this->circuits = circuits;
}
std::vector<DataInit::CircuitData> DataInit::getCircuits() {
	return this->circuits;
}
