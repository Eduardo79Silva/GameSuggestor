#pragma once
#include <FormBuilder.h>
#include <GamesManager.h>
#include <string>
#include <vector>

class GameMatch {
public:
  GameMatch();
  ~GameMatch();

  void runGameMatch(FormBuilder &formBuilder, GamesManager &gamesManager);
  void printGameMatch();

  void setGameMatch(std::vector<std::string> gameMatch);

private:
  std::vector<std::string> m_gameMatch;
};
