#pragma once

#include <unordered_map>

//Class to obtain the config of the game. 
//Before using it, loadConfigs() needs to be executed once. 
//Follows the Singleton pattern.
class Config {
	private:
		//We save the configuration and the default configuration
		static std::unordered_map<std::string, std::string> configs;
		static std::unordered_map<std::string, std::string> defaultConfigs;

	public:
		//Function to load the config
		static void loadConfigs();

		//Functions to get a certain value from the current config and the default config
		static std::string getConfig(std::string configID);
		static std::string getDefaultConfig(std::string configID);

		//Function to set a configuration
		static void setConfig(std::string configID, std::string value);

		//Function to save the config
		static void saveConfig();
};