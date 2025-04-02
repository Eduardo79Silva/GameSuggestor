#include <FormBuilder.h>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

FormBuilder::FormBuilder()
    : m_desiredPlayTime(0), m_desiredPlayTimeOffset(5), m_desiredPrice(0) {}

FormBuilder::~FormBuilder() {}

int FormBuilder::getDesiredPlayTime() { return m_desiredPlayTime; }

int FormBuilder::getDesiredPrice() { return m_desiredPrice; }

std::vector<std::string> FormBuilder::getDesiredGenres() {
  return m_desiredGenres;
}

std::vector<std::string> FormBuilder::getDesiredCategories() {
  return m_desiredCategories;
}

void FormBuilder::setDesiredPlayTime(int desiredPlayTime) {
  m_desiredPlayTime = desiredPlayTime;
}

void FormBuilder::setDesiredGenres(std::vector<std::string> desiredGenres) {
  m_desiredGenres = desiredGenres;
}

void FormBuilder::setDesiredCategories(
    std::vector<std::string> desiredCategories) {
  m_desiredCategories = desiredCategories;
}

template <typename T> T FormBuilder::askQuestion(std::string question) {
  T answer;
  while (true) {
    std::cout << question << std::endl;
    std::cin >> answer;

    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Invalid input. Please try again." << std::endl;
    } else {
      break;
    }
  }

  return answer;
}

void FormBuilder::runForm() {
  std::cout << "Welcome to the Game Recommendation Form!" << std::endl;
  std::cout << "Please answer the following questions:" << std::endl;

  m_desiredPrice = askQuestion<int>("How much are you willing to pay?");
  m_desiredPlayTime =
      askQuestion<int>("What is your desired playtime (in hours)?");

  std::string genresInput = askQuestion<std::string>(
      "What are your desired genres? (comma-separated)");
  std::string categoriesInput = askQuestion<std::string>(
      "What are your desired categories? (comma-separated)");

  // Split the input strings into vectors
  size_t pos = 0;
  while ((pos = genresInput.find(',')) != std::string::npos) {
    m_desiredGenres.push_back(genresInput.substr(0, pos));
    genresInput.erase(0, pos + 1);
  }
  m_desiredGenres.push_back(genresInput);

  pos = 0;
  while ((pos = categoriesInput.find(',')) != std::string::npos) {
    m_desiredCategories.push_back(categoriesInput.substr(0, pos));
    categoriesInput.erase(0, pos + 1);
  }
  m_desiredCategories.push_back(categoriesInput);
}

void FormBuilder::printForm() {
  std::cout << "Desired Price: " << m_desiredPrice << std::endl;
  std::cout << "Desired Playtime: " << m_desiredPlayTime << " hours"
            << std::endl;
  std::cout << "Desired Playtime Offset: " << m_desiredPlayTimeOffset
            << " hours" << std::endl;

  std::cout << "Desired Genres: ";
  for (const auto &genre : m_desiredGenres) {
    std::cout << genre << " ";
  }
  std::cout << std::endl;

  std::cout << "Desired Categories: ";
  for (const auto &category : m_desiredCategories) {
    std::cout << category << " ";
  }
  std::cout << std::endl;
}
