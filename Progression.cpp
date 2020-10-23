#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Generate validation progression to check found number.
std::string generateValidationProgression(const unsigned long int &maxIndex) noexcept {
  std::cout << std::setw(30) << std::left << "Generating validation progression " << " - [START]" << std::endl;
  std::string progressionString;
  unsigned long int currentIndex = 1;
  clock_t generationStartTime = clock();
  while (progressionString.size() < maxIndex) {
    for (unsigned long int i = 1; i <= currentIndex; ++i) {
      progressionString += std::to_string(i);
      std::cout << "\33[2K\r" << std::setw(34) << std::left << "Generation process" << " - ["
                << std::to_string(int(progressionString.size() / double(maxIndex) * 100)) << "%]" << std::flush;
      }
      ++currentIndex;
    }
    std::cout << "\33[2K\r" << std::setw(34) << std::left << "Generation process" << " - [FINISHED]" << std::flush;
    std::cout << std::endl;
    std::cout << std::setw(34) << std::left << "Time taken (seconds)" << " - ["
              << (double)(clock() - generationStartTime)/CLOCKS_PER_SEC << "]" << std::endl;
    return progressionString;
}

// Calculate digits count in given number.
uint8_t calculateDigitsCount(const unsigned long int &inputNumber) noexcept {
    auto number = inputNumber;
    uint8_t digitsCount = 0;
    while (number != 0) {
        number = number / 10;
        ++digitsCount;
    }
    return digitsCount;
}

// Find numeral in given number.
uint8_t getNumeralFromNumber(const unsigned long int &originNumber, const uint8_t &index) noexcept {
    auto number = originNumber;
    uint8_t numeral = 0;
    for (auto i = 0; i <= index; ++i) {
      numeral = number % 10;
      number = number / 10;
    }
    return numeral;
}

// Remove full subprogression indices from given index and calculate max digits count.
uint8_t removeSubProgressions(unsigned long int *index) noexcept {
  std::cout << "\33[2K\r" << std::left << std::setw(34) << "Subprogressions removing" << " - [START]"  << std::flush;
  uint8_t digits = 0;
  unsigned long int numbersSum = 0;
  unsigned long int localProgresionSize = 0;
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
  std::cout << "\33[2K\r" << std::setw(34) << std::left << "Subprogressions removing" << " - [FINISHED]" << std::flush;
  std::cout << std::endl;
  std::cout << std::setw(34) << std::left << "Subprogression max digits" << " - [" << int(digits) << "]" << std::endl;
  std::cout << std::setw(34) << std::left << "Subprogression numeral index" << " - [" << int(*index) << "]"
            << std::endl;
  return digits;
}

// Remove local progression indices from given index.
void removeLocalProgressions(unsigned long int *index, const uint8_t &digitsCount) noexcept {
  std::cout << "\33[2K\r" << std::left << std::setw(34) << "Local progressions removing " << " - [START]" << std::flush;
  unsigned long int removedLocalProgresionSize = 0;
  for (auto digit = 1; digit < digitsCount; ++digit) {
    removedLocalProgresionSize += 9 * pow(10, digit - 1) * (digit);
  }
  unsigned long int localProgressionIndex = 1;
  unsigned long int localProgresionSize = 0;
  while (*index > localProgresionSize) {
    *index -= localProgresionSize;
    localProgresionSize = removedLocalProgresionSize + digitsCount * localProgressionIndex;
    ++localProgressionIndex;
  }
  std::cout << "\33[2K\r" << std::left << std::setw(34) << "Remove local subprogressions" << " - [FINISHED]"
            << std::flush;
  std::cout << std::endl;
  std::cout << std::setw(34) << std::left << "Local progression number" << " - [" << localProgressionIndex << "]"
            << std::endl;
  std::cout << std::setw(34) << std::left << "Local progression numeral index" << " - [" << int(*index) << "]"
            << std::endl;
}

unsigned long int findNumeral(unsigned long int *index) {
  std::cout << "\33[2K\r" << std::left << std::setw(34) << "Find numeral in local progression" << " - [START]"
            << std::flush;
  unsigned long int number = 0;
  unsigned long int localProgresionSize = 0;
  while (*index > localProgresionSize) {
      ++number;
      localProgresionSize += calculateDigitsCount(number);
  }
  std::cout << "\33[2K\r" << std::left << std::setw(34) << "Find numeral in local progression" << " - [FINISHED]"
            << std::flush;
  std::cout << std::endl;
  std::cout << std::setw(34) << std::left << "Find number" << " - [" << number << "]" << std::endl;
  uint8_t numeralIndex = localProgresionSize - *index;
  std::cout << std::setw(34) << std::left << "Find numeral index" << " - [" << int(numeralIndex) << "]" << std::endl;
  return getNumeralFromNumber(number, numeralIndex);
}

int main(int argc, char* argv[]) {
  unsigned long int givenIndex = strtol(argv[1], NULL, 10);
  unsigned long int validationIndex = givenIndex;
  std::cout << std::setw(34) << std::left << "Given numeral index" << " - [" << givenIndex << "]" << std::endl;
  uint8_t indexDigitsCount = calculateDigitsCount(givenIndex);
  std::string validationProgression = generateValidationProgression(pow(10, indexDigitsCount));
  uint8_t digitsCount = removeSubProgressions(&givenIndex);
  removeLocalProgressions(&givenIndex, digitsCount);
  uint8_t numeral = findNumeral(&givenIndex);
  std::cout << std::setw(34) << std::left << "Numeral in given index" << " - [" << int(numeral) << "] " << std::endl;
  std::cout << std::setw(34) << std::left << "Numeral in validation progression" << " - ["
            << validationProgression[validationIndex - 1] << "]" << std::left << std::endl;
  if (numeral == (validationProgression[validationIndex - 1] - '0')) {
    std::cout << std::setw(34) << std::left << "VALIDATION PASS" << " - [" << "TRUE" << "]" << std::left << std::endl;
  } else {
    std::cout << std::setw(34) << std::left << "VALIDATION PASS" << " - [" << "FALSE" << "]" << std::left << std::endl;
  }
  return 0;
}
