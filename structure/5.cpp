#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void firstChoice();
void leftDoor();
void rightDoor();
void endGame();

int main() {
    cout << "Welcome to 'Escape the Dungeon'!" << endl;
    cout << "You find yourself in a dark dungeon with two doors in front of you." << endl;
    firstChoice();
    return 0;
}

void firstChoice() {
    string choice;
    cout << "\nDo you want to go through the left door or the right door?" << endl;
    cout << "Type 'left' or 'right': ";
    cin >> choice;

    if (choice == "left") {
        leftDoor();
    } else if (choice == "right") {
        rightDoor();
    } else {
        cout << "Invalid choice. Please choose 'left' or 'right'." << endl;
        firstChoice();
    }
}

void leftDoor() {
    string choice;
    cout << "\nYou enter a room filled with treasure!" << endl;
    cout << "But there's a dragon guarding it. Do you want to:" << endl;
    cout << "1. Fight the dragon" << endl;
    cout << "2. Sneak past the dragon" << endl;

    cout << "Type '1' or '2': ";
    cin >> choice;

    if (choice == "1") {
        cout << "\nYou bravely fight the dragon but it breathes fire and you perish. Game Over!" << endl;
    } else if (choice == "2") {
        cout << "\nYou successfully sneak past the dragon and escape with some treasure!" << endl;
        endGame();
    } else {
        cout << "Invalid choice. Please choose '1' or '2'." << endl;
        leftDoor();
    }
}

void rightDoor() {
    string choice;
    cout << "\nYou enter a dark hallway and hear a noise." << endl;
    cout << "Do you want to:" << endl;
    cout << "1. Investigate the noise" << endl;
    cout << "2. Run back to the previous room" << endl;

    cout << "Type '1' or '2': ";
    cin >> choice;

    srand(static_cast<unsigned>(time(0))); // Seed for random number generation

    if (choice == "1") {
        cout << "\nYou find a goblin who offers you a way out in exchange for some gold." << endl;
        if (rand() % 2 == 0) { // Randomly decide if the goblin is friendly
            cout << "You give the goblin some gold and he shows you the exit! You are free!" << endl;
        } else {
            cout << "The goblin tricks you and takes all your gold. Game Over!" << endl;
        }
    } else if (choice == "2") {
        cout << "\nYou run back and safely return to the previous room." << endl;
        firstChoice();
    } else {
        cout << "Invalid choice. Please choose '1' or '2'." << endl;
        rightDoor();
    }
}

void endGame() {
    cout << "\nCongratulations! You've escaped the dungeon with treasure!" << endl;
    cout << "Thank you for playing!" << endl;
}