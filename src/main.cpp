#include <FormBuilder.h>
#include <GameMatch.h>
#include <GamesManager.h>
#include <HttpClient.h>
#include <SteamWebAPI.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <ostream>

int main() {

  json config = loadSteamCredentials();

  // Access configuration parameters
  std::string apiKey = config.value("steamApiKey", "");
  std::string steamId = config.value("steamId", "");

  std::string url =
      "https://api.steampowered.com/IPlayerService/GetOwnedGames/v0001/"
      "?key=" +
      apiKey + "&steamid=" + steamId +
      "&format=json&include_appinfo=true&include_"
      "played_free_games=true";

  std::cout << "URL: " << url << std::endl;

  HttpClient client = HttpClient();

  json ownedGames = client.callAPI(url);

  if (ownedGames.empty()) {
    std::cout << "No games found. Please check you API key" << std::endl;
    removeCredentials();

    return 1;
  }

  GamesManager gamesManager(ownedGames);
  try {
    // In your test or main function:
    // make a call to loadGamesGenresAndCategories run in the background
    gamesManager.loadGamesGenresAndCategories();
    gamesManager.loadGamesDuration();
    gamesManager.printGames();

    std::cout << "Games loaded successfully." << std::endl;

  } catch (const std::exception &e) {
    // Catch standard exceptions
    std::cerr << "Standard exception: " << e.what() << std::endl;
  } catch (...) {
    // Catch any other exceptions
    std::cerr << "Unknown error occurred" << std::endl;
  }

  FormBuilder formBuilder;
  formBuilder.runForm();
  formBuilder.printForm();

  GameMatch gameMatch;
  gameMatch.runGameMatch(formBuilder, gamesManager);
  gameMatch.printGameMatch();

  return 0;
}
