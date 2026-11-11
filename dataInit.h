// GradPrixRecommender.h : Include file for standard system include files,
// or project specific include files.

#pragma once
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include <unordered_map>
#include <iomanip>

class DataInit {
private:
	struct CircuitData {
		int id;
		std::string circuitRef;
		std::string name;
		std::string country;
	};
	std::vector<CircuitData> circuits;
public:
	std::vector<CircuitData> readCircuitCSV();
	void setCircuits(std::vector<CircuitData>&);
	std::vector<CircuitData> getCircuits();
	
};