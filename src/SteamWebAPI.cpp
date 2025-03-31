#include <SteamWebAPI.h>
#include <fstream>
#include <iostream>
#include <ostream>

json loadSteamCredentials() {

  // Open the creds file
  std::ifstream configFile("creds.json");
  if (!configFile) {
    configFile.close();
    configFile.clear();
    configFile.open("../creds.json");
    if (!configFile) {
      std::cerr << "Error: Could not open creds file!" << std::endl;
      std::string key = askForAPIKey();
      std::string id = askForSteamID();
      return saveSteamCredentialsLocally(key, id);
    }
  }

  // Parse the JSON creds file
  json creds;
  try {
    configFile >> creds;
  } catch (const json::parse_error &e) {
    std::cerr << "Error parsing creds file: " << e.what() << std::endl;
    std::string key = askForAPIKey();
    std::string id = askForSteamID();
    return saveSteamCredentialsLocally(key, id);
  }

  return creds;
}

json saveSteamCredentialsLocally(std::string steamApiKey, std::string steamId) {
  std::ofstream creds("creds.json");
  if (creds.is_open()) {
    json configDefault =
        json::object({{"steamApiKey", steamApiKey}, {"steamId", steamId}});

    creds << configDefault;

    return configDefault;
  }
  return json();
}

std::string askForAPIKey() {
  std::string key;

  std::cout << "Please insert the API Key that you can find here: "
               "https://steamcommunity.com/dev/apikey"
            << std::endl;
  std::cout << "When you are asked for a domain simply insert: localhost."
            << std::endl;

  std::cout << "API Key: ";

  std::cin >> key;

  return key;
}

std::string askForSteamID() {
  std::string id;

  std::cout << "Please insert you Steam ID that can be found in the link of "
               "your profile or under 'Account Details'"
            << std::endl;

  std::cout << "SteamID: ";
  std::cin >> id;

  return id;
}

void removeCredentials() {
  std::cout << "Removing credentials" << std::endl;
  std::remove("creds.json");
  std::remove("../creds.json");
}
