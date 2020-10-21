#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <math.h>
#include <time.h>

std::string generateValidationProgression(const unsigned long int &maxIndex) {
  std::cout <<  std::left << std::setw(30) << "Generating validation progression " << std::setw(10) << " - [START]" << std::endl;
  std::string progressionString;
  unsigned long int currentIndex = 1;
  clock_t generationStartTime = clock();
  while (progressionString.size() < maxIndex) {
    for (unsigned long int i = 1; i <= currentIndex; ++i) {
      progressionString += std::to_string(i);
      std::cout << "\33[2K\r" << std::left << std::setw(34) << "Generation process" << std::setw(4) << " - ["
                  << std::to_string(int(progressionString.size() / double(maxIndex) * 100)) << "%]" << std::flush;
      }
      ++currentIndex;
    }
    std::cout << "\33[2K\r" << std::left << std::setw(34) << "Generation process" << std::setw(10) << " - [FINISHED]"
                                                                                      << std::left << std::flush;
    std::cout << std::endl;
    std::cout << std::setw(34) << "Time taken (seconds)" << std::setw(3) << " - " <<
            (double)(clock() - generationStartTime)/CLOCKS_PER_SEC << std::left << std::endl;
    return progressionString;
}

uint8_t calculateDigitsCount(unsigned long int number) {
    uint8_t digitsCount = 0;
    while (number != 0) {
        number = number / 10;
        ++digitsCount;
    }
    return digitsCount;
}

int main(int argc, char* argv[]) {
  unsigned long int givenIndex = strtol(argv[1], NULL, 10);
  uint8_t indexDigitsCount = calculateDigitsCount(givenIndex);
  // std::string validationProgression = generateValidationProgression(pow(10, indexDigitsCount));
  unsigned long int localMaxIndex = 0;
  unsigned long int localIndex = 0;
  unsigned long int sumMaxIndex = 0;
  unsigned long int numbersSum = 0;
  long long int deltaIndex = 1;
  uint64_t numbersCount = 0;
  while (deltaIndex > 0) {
      ++numbersCount;
      localMaxIndex = ((2 * (numbersSum + numbersCount) + numbersCount * (9 * pow(10, numbersCount - 1) - 1)) / 2) *
                                                                                          9 * pow(10, numbersCount - 1);
      sumMaxIndex += localMaxIndex;
      numbersSum += 9 * pow(10, numbersCount - 1) * numbersCount;
      deltaIndex = givenIndex - sumMaxIndex;
      std::cout << "Local max index - " << localMaxIndex << std::endl;
      std::cout << "Local index - " << localIndex << std::endl;
      std::cout << "Sum max index - " << sumMaxIndex << std::endl;
      std::cout << "Numbers sum - " << numbersSum << std::endl;
      std::cout << std::endl;
  }

  // unsigned long int localIndex = localMaxIndex + deltaIndex;
  // std::cout << "Local index is - " << localIndex << std::endl;
  // std::cout << "Current max index is - " << localMaxIndex << std::endl;
  // std::cout << "Current numbers count - " << numbersCount << std::endl;
  // std::string localProgresion;
  // unsigned long int currentLocalIndex = 1 * pow(10, numbersCount - 1);
  // while (localProgresion.size() <= localIndex) {
  //     for (unsigned long int i = 1; i <= currentLocalIndex; ++i) {
  //         localProgresion += std::to_string(i);
  //     }
  //     ++currentLocalIndex;
  // }
  // std::cout << localProgresion << std::endl;
  // std::cout << "On index " << givenIndex << " is number " << /*validationProgression[givenIndex - 1] << */". Found number is " << localProgresion[localIndex - 1] << std::endl;
  return 0;
}
