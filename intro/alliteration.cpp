// detect alliterations
#include <iostream>
#include <sstream>
#include <map>

int main() {
  std::string line = "";

  while (std::getline(std::cin, line)) {
    std::istringstream stream(line);
    std::string word;
    char last_letter = std::tolower(line[0]);
    int word_count = 0;
    int alliterations = 0;
    bool same_letter = false;

    while (stream >> word) {
      if (word_count > 0 &&
          std::tolower(word[0]) == last_letter) {
        if (!same_letter) {
          alliterations++;
        }
        same_letter = true;
      } else {
        last_letter = std::tolower(word[0]);
        same_letter = false;
      }
      word_count++;
    }

    std::cout << alliterations << "\n";
  }

  return 0;
}
