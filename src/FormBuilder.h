#pragma once

#include <string>
#include <vector>
class FormBuilder {

public:
  FormBuilder();
  ~FormBuilder();

  template <typename T> T askQuestion(std::string question);

  int getDesiredPlayTime();
  int getDesiredPlayTimeOffset();
  int getDesiredPrice();
  std::vector<std::string> getDesiredGenres();
  std::vector<std::string> getDesiredCategories();

  void setDesiredPlayTime(int desiredPlayTime);
  void setDesiredPlayTimeOffset(int desiredPlayTimeOffset);
  void setDesiredPrice(int desiredPrice);
  void setDesiredGenres(std::vector<std::string> desiredGenres);
  void setDesiredCategories(std::vector<std::string> desiredCategories);

  void runForm();
  void printForm();

private:
  int m_desiredPlayTime;
  int m_desiredPlayTimeOffset;
  int m_desiredPrice;
  std::vector<std::string> m_desiredGenres;
  std::vector<std::string> m_desiredCategories;
};
