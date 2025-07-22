#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

// Class to represent a Player
class Player {
private:
    string name;
    int score;

public:
    Player(string playerName, int initialScore = 0) : name(playerName), score(initialScore) {}

    string getName() const { return name; }
    int getScore() const { return score; }
    void setName(string newName) { name = newName; }
    void addScore(int points) { score += points; }
};

// Class to manage the Dice Game
class DiceGame {
private:
    vector<Player> players;
    unordered_map<string, int> leaderboard; // Hash map for leaderboard

    // Function to roll a die
    int rollDie() {
        return (rand() % 6) + 1; // Returns random number between 1 and 6
    }

    // Function to update leaderboard
    void updateLeaderboard() {
        for (const auto& player : players) {
            leaderboard[player.getName()] = player.getScore();
        }
    }

public:
    DiceGame() {
        srand(time(0)); // Seed random number generator
    }

    // Function to initialize players
    void initializePlayers(int numPlayers) {
        for (int i = 0; i < numPlayers; ++i) {
            string name = "Player" + to_string(i + 1);
            cout << "Enter name for " << name << " (or press Enter to keep default): ";
            string customName;
            getline(cin, customName);
            if (!customName.empty()) {
                name = customName;
            }
            players.emplace_back(name);
        }
    }

    // Function to play one round
    void playRound() {
        cout << "\n--- New Round ---\n";
        for (auto& player : players) {
            int roll = rollDie();
            player.addScore(roll);
            cout << player.getName() << " rolled a " << roll << ". Total score: " << player.getScore() << endl;
        }
        updateLeaderboard();
    }

    // Function to display leaderboard
    void displayLeaderboard() {
        cout << "\n--- Leaderboard ---\n";
        // Create a vector of pairs for sorting
        vector<pair<string, int> > sortedLeaderboard(leaderboard.begin(), leaderboard.end());
        sort(sortedLeaderboard.begin(), sortedLeaderboard.end(),
             [](const pair<string, int>& a, const pair<string, int>& b) { 
                 return a.second > b.second; 
             });

        cout << left << setw(20) << "Player" << "Score\n";
        cout << string(30, '-') << endl;
        for (const auto& entry : sortedLeaderboard) {
            cout << left << setw(20) << entry.first << entry.second << endl;
        }
    }

    // Function to determine and display the winner
    void displayWinner() {
        if (players.empty()) return;

        auto winner = max_element(players.begin(), players.end(),
                                 [](const Player& a, const Player& b) { return a.getScore() < b.getScore(); });
        cout << "\n*** " << winner->getName() << " wins with a score of " << winner->getScore() << "! ***\n";
    }

    // Function to run the game
    void runGame(int numRounds) {
        for (int i = 1; i <= numRounds; ++i) {
            cout << "\nRound " << i << ":\n";
            playRound();
            displayLeaderboard();
        }
        displayWinner();
    }
};

// Main function
int main() {
    cout << "Welcome to the Dice Game Simulator!\n";
    
    int numPlayers;
    do {
        cout << "Enter number of players (2 or more): ";
        cin >> numPlayers;
        cin.ignore(); // Clear newline from input buffer
    } while (numPlayers < 2);

    int numRounds;
    do {
        cout << "Enter number of rounds (1 or more): ";
        cin >> numRounds;
        cin.ignore();
    } while (numRounds < 1);

    DiceGame game;
    game.initializePlayers(numPlayers);
    game.runGame(numRounds);

    return 0;
}