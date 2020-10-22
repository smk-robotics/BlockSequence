#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Generate validation progression to check found number.
std::string generateValidationProgression(const unsigned long int &maxIndex) {
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
uint8_t calculateDigitsCount(const unsigned long int &inputNumber) {
    auto number = inputNumber;
    uint8_t digitsCount = 0;
    while (number != 0) {
        number = number / 10;
        ++digitsCount;
    }
    return digitsCount;
}

int main(int argc, char* argv[]) {
  unsigned long int givenIndex = strtol(argv[1], NULL, 10);
  std::cout << std::setw(34) << std::left << "Given index in progression" << " - [" << givenIndex << "]" << std::endl;
  uint8_t indexDigitsCount = calculateDigitsCount(givenIndex);
  std::string validationProgression = generateValidationProgression(pow(10, indexDigitsCount));
  std::cout << "\33[2K\r" << std::left << std::setw(34) << "Find subprogression number " << " - [START]"  << std::flush;
  unsigned long int numbersSum = 0;
  long long int relicIndex = 0;
  uint8_t digitsCount = 0;
  unsigned long int localProgresionSize = 0;
  unsigned long int sumProgressionSize = 0;
  while (givenIndex > sumProgressionSize) {
      ++digitsCount;
      // Calculate relic between given and current max index:
      relicIndex = givenIndex - sumProgressionSize;
      // Calculate local progression size:
      localProgresionSize = ((2 * (numbersSum + digitsCount) + digitsCount *
                                            (9 * pow(10, digitsCount - 1) - 1)) / 2) * 9 * pow(10, digitsCount - 1);
      // Calculate current max index (inculdes all local progressions):
      sumProgressionSize += localProgresionSize;
      // Calculate sum of all numbers:
      numbersSum += 9 * pow(10, digitsCount - 1) * digitsCount;
  }
  std::cout << "\33[2K\r" << std::setw(34) << std::left << "Find subprogression " << " - [FINISHED]" << std::flush;
  std::cout << std::endl;
  std::cout << std::setw(34) << std::left << "Subprogression number digits" << " - [" << int(digitsCount) << "]"
            << std::endl;
  localProgresionSize = 0;
  unsigned long int localProgressionIndex = 0;
  unsigned long int previouSubProgressionSize = 0;
  while (localProgresionSize < relicIndex) {
    ++localProgressionIndex;
    previouSubProgressionSize = localProgresionSize;
    localProgresionSize += 9 * pow(10, digitsCount - 2) * (digitsCount - 1) + digitsCount * localProgressionIndex;
    // std::cout << std::setw(34) << std::left << "LOCAL PROGRESSION SIZE " << " - [" << int(localProgresionSize) << "]"
    //           << std::endl;
  }
  //relicIndex -= previouSubProgressionSize;
  std::cout << std::setw(34) << std::left << "Subprogression index " << " - ["
            << int(previouSubProgressionSize + relicIndex) << "]" << std::left << std::endl;
  std::cout << std::setw(34) << std::left << "Local progression index " << " - [" << int(relicIndex) << "]"
            << std::left << std::endl;
  localProgresionSize = 0;
  unsigned long int number = 0;
  unsigned long int lastLocalProgressionNumber = 0;
  for (uint8_t digit = 1; digit <= digitsCount; ++digit) {
    localProgresionSize += 9 * pow(10, digit - 1) * digit;
    if (relicIndex > localProgresionSize) {
      relicIndex -= localProgresionSize;
      lastLocalProgressionNumber += 9 * pow(10, digit - 1);
    } else {
      // std::cout << "Last local progression number - " << lastLocalProgressionNumber << std::endl;
      // std::cout << "Local progresion size - " << localProgresionSize << std::endl;
      number = lastLocalProgressionNumber + std::ceil(double(relicIndex) / digit);
      std::cout << std::setw(34) << "Found number" << " - [" << number << "]" << std::left << std::endl;
      // std::cout << "Local progression size index - " << relicIndex << std::endl;
      unsigned long int numeralIndex = relicIndex - floor(relicIndex / digitsCount) * digitsCount;
      std::cout << std::setw(34) << "Find numeral index " << " - [" << numeralIndex << "]" << std::left << std::endl;
      std::string numeral = std::to_string(number);
      std::cout << std::setw(34) << "Find numeral" << " - [" << numeral[numeralIndex] << "]" << std::left << std::endl;
      break;
    }
  }
  std::cout << std::setw(34) << "Validation numeral" << " - [" << validationProgression[givenIndex - 1]
            << "]" << std::left << std::endl;
  // std::cout <<  validationProgression[givenIndex - 3] << validationProgression[givenIndex - 2] << validationProgression[givenIndex - 1]
  //           << validationProgression[givenIndex] << validationProgression[givenIndex + 1] << validationProgression[givenIndex + 2] << std::endl;
  return 0;
}
