#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Generate validation progression to check found number.
std::string generateValidationProgression(const unsigned long long &maxIndex) noexcept {
  std::string progressionString;
  unsigned long long currentIndex = 1;
  while (progressionString.size() < maxIndex) {
    for (auto i = 1; i <= currentIndex; ++i) {
      progressionString += std::to_string(i);
      std::cout << "\33[2K\r" << std::setw(38) << std::left << "Generating validation progression" << " - ["
                << std::to_string(long(progressionString.size() / double(maxIndex) * 100)) << "%]" << std::flush;
      }
      ++currentIndex;
    }
    std::cout << std::endl;
    return progressionString;
}

// Calculate digits count in given number.
uint8_t calculateDigitsCount(const unsigned long long &inputNumber) noexcept {
    auto number = inputNumber;
    uint8_t digitsCount = 0;
    while (number != 0) {
        number = number / 10;
        ++digitsCount;
    }
    return digitsCount;
}

// Find numeral in given number.
uint8_t getNumeralFromNumber(const unsigned long long &originNumber, const uint8_t &index) noexcept {
    auto number = originNumber;
    uint8_t numeral = 0;
    for (auto i = 0; i <= index; ++i) {
      numeral = number % 10;
      number = number / 10;
    }
    return numeral;
}

// Remove full subprogression indices from given index and calculate max digits count.
uint8_t removeSubProgressions(unsigned long long *index) noexcept {
  std::cout << "\33[2K\r" << std::left << std::setw(38) << "Subprogressions removing" << " - [START]"  << std::flush;
  uint8_t digits = 0;
  unsigned long long numbersSum = 0;
  unsigned long long localProgresionSize = 0;
  while (*index > localProgresionSize) {
      ++digits;
      // Calculate relic between given and current max index:
      *index -= localProgresionSize;
      // Calculate local progression size:
      localProgresionSize = ((2 * (numbersSum + digits) + digits * (9 * pow(10, digits - 1) - 1)) / 2) * 9
                                                                                                * pow(10, digits - 1);
      // Calculate sum of all numbers:
      numbersSum += 9 * pow(10, digits - 1) * (digits);
  }
  std::cout << "\33[2K\r" << std::setw(38) << std::left << "Subprogressions removing" << " - [FINISHED]" << std::flush;
  std::cout << std::endl;
  std::cout << std::setw(38) << std::left << "Subprogression max digits" << " - [" << int(digits) << "]" << std::endl;
  std::cout << std::setw(38) << std::left << "Subprogression numeral index" << " - [" << int(*index) << "]"
            << std::endl;
  return digits;
}

// Remove local progression indices from given index.
void removeLocalProgressions(unsigned long long *index, const uint8_t &digitsCount) noexcept {
  std::cout << "\33[2K\r" << std::left << std::setw(38) << "Local progressions removing " << " - [START]" << std::flush;
  unsigned long long removedLocalProgresionSize = 0;
  for (auto digit = 1; digit < digitsCount; ++digit) {
    removedLocalProgresionSize += 9 * pow(10, digit - 1) * (digit);
  }
  unsigned long long localProgressionIndex = 1;
  unsigned long long localProgresionSize = 0;
  while (*index > localProgresionSize) {
    *index -= localProgresionSize;
    localProgresionSize = removedLocalProgresionSize + digitsCount * localProgressionIndex;
    ++localProgressionIndex;
  }
  std::cout << "\33[2K\r" << std::left << std::setw(38) << "Remove local subprogressions" << " - [FINISHED]"
            << std::flush;
  std::cout << std::endl;
  std::cout << std::setw(38) << std::left << "Local progression number" << " - [" << localProgressionIndex << "]"
            << std::endl;
  std::cout << std::setw(38) << std::left << "Local progression numeral index" << " - ["
            << static_cast<long long>(*index) << "]"
            << std::endl;
}

unsigned long long findNumeral(unsigned long long *index) {
  std::cout << "\33[2K\r" << std::left << std::setw(38) << "Find numeral in local progression" << " - [START]"
            << std::flush;
  unsigned long long number = 0;
  unsigned long long localProgresionSize = 0;
  while (*index > localProgresionSize) {
      ++number;
      localProgresionSize += calculateDigitsCount(number);
  }
  std::cout << "\33[2K\r" << std::left << std::setw(38) << "Find numeral in local progression" << " - [FINISHED]"
            << std::flush;
  std::cout << std::endl;
  std::cout << std::setw(38) << std::left << "Find number" << " - [" << number << "]" << std::endl;
  uint8_t numeralIndex = localProgresionSize - *index;
  std::cout << std::setw(38) << std::left << "Numeral index in number" << " - ["
            << static_cast<long long>(numeralIndex) << "]" << std::endl;
  return getNumeralFromNumber(number, numeralIndex);
}

int main(int argc, char* argv[]) {
  if (argc < 1) {
    std::cout << "[ERROR] - Need to pass index in command line argument" << std::endl;
    return 1;
  }
  unsigned long long givenIndex = strtol(argv[1], NULL, 10);
  unsigned long long validationIndex = givenIndex;
  std::string validationProgression;
  bool needValidation = false;
  std::cout << std::setw(38) << std::left << "Given numeral index" << " - [" << givenIndex << "]" << std::endl;
  if (argv[2] != nullptr) {
    if (std::string(argv[2]) == "-v") {
      std::cout << std::setw(38) << std::left << "Need validation" << " - [TRUE]" << std::endl;
      uint8_t indexDigitsCount = calculateDigitsCount(givenIndex);
      validationProgression = generateValidationProgression(pow(10, indexDigitsCount));
      needValidation = true;
    }
  } else {
    std::cout << std::setw(38) << std::left << "Need validation " << " - [FALSE]" << std::endl;
  }
  clock_t algorithmStartTime = clock();
  uint8_t digitsCount = removeSubProgressions(&givenIndex);
  removeLocalProgressions(&givenIndex, digitsCount);
  uint8_t numeral = findNumeral(&givenIndex);
  std::cout << std::setw(38) << std::left << "RESULT. Numeral in given index" << " - [" << static_cast<int>(numeral)
            << "] " << std::endl;
  if (needValidation) {
    std::cout << std::setw(38) << std::left << "Numeral in VALIDATION progression" << " - ["
              << validationProgression[validationIndex - 1] << "]" << std::left << std::endl;
    if (numeral == (validationProgression[validationIndex - 1] - '0')) {
      std::cout << std::setw(38) << std::left << "VALIDATION RESULT" << " - [" << "PASS" << "]" << std::left
                << std::endl;
    } else {
      std::cout << std::setw(38) << std::left << "VALIDATION RESULT" << " - [" << "FAILED" << "]" << std::left
                << std::endl;
    }
  }
  std::cout << std::setw(38) << std::left << "Time taken for search (seconds)" << " - ["
            << static_cast<double>(clock() - algorithmStartTime) / CLOCKS_PER_SEC << "]" << std::endl;
  return 0;
}
