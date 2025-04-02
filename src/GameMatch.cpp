#include <GameData.h>
#include <GameMatch.h>
#include <GamesManager.h>
#include <iostream>
#include <string>
#include <vector>

GameMatch::GameMatch() {}
GameMatch::~GameMatch() {}

void GameMatch::setGameMatch(std::vector<std::string> gameMatch) {
  m_gameMatch = gameMatch;
}

void GameMatch::printGameMatch() {
  std::cout << "Game Match:" << std::endl;
  for (const auto &game : m_gameMatch) {
    std::cout << game << std::endl;
  }
}

void GameMatch::runGameMatch(FormBuilder &formBuilder,
                             GamesManager &gamesManager) {
  std::cout << "Running game match..." << std::endl;

  // Example of how to use the formBuilder to get user input
  int desiredPlayTime = formBuilder.getDesiredPlayTime();
  int desiredPrice = formBuilder.getDesiredPrice();
  std::vector<std::string> desiredGenres = formBuilder.getDesiredGenres();
  std::vector<std::string> desiredCategories =
      formBuilder.getDesiredCategories();

  std::vector<GameData> gamesWithGenre = {};
  std::vector<GameData> gamesWithCategory = {};
  std::vector<GameData> gamesWithPlayTime = {};
  std::vector<GameData> gamesWithPrice = {};

  std::vector<GameData> games = gamesManager.getGames();

  for (const auto genre : desiredGenres) {
    auto partialGamesWithGenre = gamesManager.getGamesWithGenre(genre);
    gamesWithGenre.insert(gamesWithGenre.end(), partialGamesWithGenre.begin(),
                          partialGamesWithGenre.end());
  }

  for (const auto category : desiredCategories) {
    auto partialGamesWithCategory = gamesManager.getGamesWithCategory(category);
    gamesWithCategory.insert(gamesWithCategory.end(),
                             partialGamesWithCategory.begin(),
                             partialGamesWithCategory.end());
  }

  for (auto game : games) {
    const auto gamePrice = game.getPrice();
    const auto gamePlayTime = game.getPlaytime();
    if (gamePrice <= desiredPrice) {
      gamesWithPrice.push_back(game);
    }
    if (gamePlayTime <= desiredPlayTime) {
      gamesWithPlayTime.push_back(game);
    }
  }

  std::map<std::string, int> gameMatchScore;
  for (auto &game : games) {
    int score = 0;
    if (std::find(gamesWithGenre.begin(), gamesWithGenre.end(), game) !=
        gamesWithGenre.end()) {
      score += 1;
    }
    if (std::find(gamesWithCategory.begin(), gamesWithCategory.end(), game) !=
        gamesWithCategory.end()) {
      score += 1;
    }
    if (std::find(gamesWithPlayTime.begin(), gamesWithPlayTime.end(), game) !=
        gamesWithPlayTime.end()) {
      score += 1;
    }
    if (std::find(gamesWithPrice.begin(), gamesWithPrice.end(), game) !=
        gamesWithPrice.end()) {
      score += 1;
    }
    gameMatchScore[game.getName()] = score;
  }

  std::vector<std::pair<std::string, int>> sortedGameMatch(
      gameMatchScore.begin(), gameMatchScore.end());

  std::sort(sortedGameMatch.begin(), sortedGameMatch.end(),
            [](const auto &a, const auto &b) { return a.second > b.second; });

    sortedGameMatch.resize(5); // Limit to top 10 matches


  // Store the game match in the member variable
  for (const auto &game : sortedGameMatch) {
    m_gameMatch.push_back(game.first);
  }
}
