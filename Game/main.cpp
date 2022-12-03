#include <iostream>
#include "gameClass.h"
#include <cstdlib> 
#include <ctime> 

int main()
{
    std::string player_name;
    std::cout << "Enter your name:)\n";
    std::cin >> player_name;
    Player p(player_name);
    std::cout << "Welcome, " << p.getName() << ". You have " << p.getHealth() << " health and are carrying " << p.getGold() << " gold.\n";

    srand(time(0)); // устанавливаем значение системных часов в качестве стартового числа
    int rand_value = rand();

    while (!p.isDead() && !p.hasWon()) {
        play(p);
    }
    
    if (p.hasWon())
        std::cout << "\nYou have " << p.getLevel() << " level and earned for " << p.getGold() << " gold. You win!\n";
    else
        std::cout << "\nYou died at level " << p.getLevel() << " and earned " << p.getGold() << " gold.\n\n";
    return 0;
}