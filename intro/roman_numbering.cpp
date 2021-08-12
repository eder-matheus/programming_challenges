// translate arabic numbers to roman numbers
#include <iostream>
#include <map>
#include <vector>
 
int main() {
  std::map<int, char> arabic_to_roman;
  arabic_to_roman[1]    = 'I';
  arabic_to_roman[5]    = 'V';
  arabic_to_roman[10]   = 'X';
  arabic_to_roman[50]   = 'L';
  arabic_to_roman[100]  = 'C';
  arabic_to_roman[500]  = 'D';
  arabic_to_roman[1000] = 'M';
  std::vector<int> numbers{1000, 500, 100, 50, 10, 5, 1};

  int n;
  int multiplier = 1;
  std::cin >> n;

  std::string roman;

  while (n > 0) {
    int digit = n % 10;
    int number = digit * multiplier;
    n /= 10;
    int i = numbers[0];
    int cnt = 1;
    std::string roman_digit;
    while (number > 0) {
      if ((number - i) >= 0) {
        roman_digit.push_back(arabic_to_roman[i]);
        number -= i;
      } else if ((number - i) == (-1*multiplier)) {
        int j = (i != 5 && i != 50 && i != 500) ? numbers[cnt+1] : numbers[cnt];
        roman_digit.push_back(arabic_to_roman[j]);
        roman_digit.push_back(arabic_to_roman[i]);
        number -= i;
      } else {
        i = numbers[cnt];
        cnt++;
      }
    }
    multiplier *= 10;
    roman = roman_digit + roman;
  }

  std::cout << roman << "\n";

  return 0;
}
