#include <iostream>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <fstream>
#include <vector>
#include <algorithm>

class NumberGuessingGame {
public:
    NumberGuessingGame() {
        std::srand(std::time(0)); // Seed the random number generator
        bestScore = INT_MAX;
        loadBestScores();
    }

    void play() {
        char playAgain;
        do {
            setupGame();
            int playerGuess = 0;
            numberOfTries = 0;

            std::cout << "I have selected a number between " << lowerBound << " and " << upperBound << ". Try to guess it!" << std::endl;

            while (playerGuess != numberToGuess) {
                std::cout << "Enter your guess: ";
                std::cin >> playerGuess;
                numberOfTries++;

                if (playerGuess > numberToGuess) {
                    std::cout << "Too high! Try again." << std::endl;
                } else if (playerGuess < numberToGuess) {
                    std::cout << "Too low! Try again." << std::endl;
                } else {
                    std::cout << "Congratulations! You guessed the number in " << numberOfTries << " tries." << std::endl;
                    if (numberOfTries < bestScore) {
                        bestScore = numberOfTries;
                        std::cout << "New best score!" << std::endl;
                        saveBestScore();
                    }
                }
            }

            std::cout << "Do you want to play again? (y/n): ";
            std::cin >> playAgain;
        } while (playAgain == 'y' || playAgain == 'Y');
    }

private:
    int lowerBound;
    int upperBound;
    int numberToGuess;
    int numberOfTries;
    int bestScore;
    std::vector<int> bestScores;

    void setupGame() {
        selectDifficulty();
        numberToGuess = std::rand() % (upperBound - lowerBound + 1) + lowerBound;
    }

    void selectDifficulty() {
        int difficulty;
        std::cout << "Select difficulty level:" << std::endl;
        std::cout << "1. Easy (1-10)" << std::endl;
        std::cout << "2. Medium (1-100)" << std::endl;
        std::cout << "3. Hard (1-1000)" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> difficulty;

        switch (difficulty) {
            case 1:
                lowerBound = 1;
                upperBound = 10;
                break;
            case 2:
                lowerBound = 1;
                upperBound = 100;
                break;
            case 3:
                lowerBound = 1;
                upperBound = 1000;
                break;
            default:
                std::cerr << "Invalid choice. Defaulting to Easy level." << std::endl;
                lowerBound = 1;
                upperBound = 10;
                break;
        }
    }

    void saveBestScore() {
        bestScores.push_back(bestScore);
        std::sort(bestScores.begin(), bestScores.end());
        if (bestScores.size() > 5) {
            bestScores.pop_back(); // Keep only top 5 scores
        }

        std::ofstream outFile("best_scores.txt");
        if (outFile.is_open()) {
            for (int score : bestScores) {
                outFile << score << std::endl;
            }
            outFile.close();
        } else {
            std::cerr << "Error: Could not save best scores." << std::endl;
        }
    }

    void loadBestScores() {
        std::ifstream inFile("best_scores.txt");
        if (inFile.is_open()) {
            int score;
            while (inFile >> score) {
                bestScores.push_back(score);
            }
            inFile.close();
        } else {
            std::cerr << "Error: Could not load best scores." << std::endl;
        }
    }

    void displayBestScores() {
        std::cout << "Best Scores:" << std::endl;
        for (int score : bestScores) {
            std::cout << score << std::endl;
        }
    }
};

int main() {
    NumberGuessingGame game;
    game.play();
    return 0;
}