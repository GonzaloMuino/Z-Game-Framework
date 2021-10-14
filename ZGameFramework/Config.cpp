#include <iostream>
#include <fstream>
#include <string>

#include "Config.h"
#include "Utils.h"

std::unordered_map<std::string, std::string> Config::configs;
std::unordered_map<std::string, std::string> Config::defaultConfigs;

//Function to load the config
void Config::loadConfigs() {
	//We load the configuration
	std::ifstream file;
	file.open("Resources/Config.ini");

	std::string line;

	while (getline(file, line)) {
		if (line.size() > 2 && line.at(0) != '/' && line.at(1) != '/') {
			std::vector<std::string> splitLine = Utils::splitString(line, "=");

			std::string key = splitLine.at(0);
			std::string value = splitLine.at(1);

			Config::configs.insert({ key.c_str(),value });
		}
	}

	file.close();

	//We load the default configuration
	file.open("Resources/DefaultConfig.ini");
	while (getline(file, line)) {
		if (line.size() > 2 && line.at(0) != '/' && line.at(1) != '/') {
			std::vector<std::string> splitLine = Utils::splitString(line, "=");

			std::string key = splitLine.at(0);
			std::string value = splitLine.at(1);

			Config::defaultConfigs.insert({ key.c_str(),value });
		}
	}
}

//Functions to get a certain value from the current config and the default config
std::string Config::getConfig(std::string config) {
	std::unordered_map<std::string,std::string>::const_iterator iterator = Config::configs.find(config);
	if (iterator == Config::configs.end()) {
		return "";
	}
	else {
		return iterator->second;
	}
}


std::string Config::getDefaultConfig(std::string config) {
	std::unordered_map<std::string, std::string>::const_iterator iterator = Config::defaultConfigs.find(config);

	if (iterator == Config::defaultConfigs.end()) {
		return "";
	}
	else {
		return iterator->second;
	}
}

//Function to set a configuration
void Config::setConfig(std::string config, std::string value) {
	std::unordered_map<std::string, std::string>::const_iterator iterator = Config::configs.find(config);
	if (iterator != Config::configs.end()) {
		Config::configs.erase(iterator);
	}

	Config::configs.insert({config.c_str(),value});
}

//Function to save the config
void Config::saveConfig() {
	std::ofstream configFile;
	configFile.open("Resources/Config.ini");

	for (std::unordered_map<std::string,std::string>::iterator iter = Config::configs.begin(); iter != Config::configs.end(); ++iter){
		std::string key = iter->first;
		std::string value = iter->second;

		configFile << key + "=" + value + "\n";
	}

	configFile.close();
}