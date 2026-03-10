#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <conio.h>

using namespace std;

struct Resource {
    int gold;
    int soldiers;
    int food;
    int stability;
    string name;
};

class City {
public:
    string name;
    string type;
    int population;
    int taxRate;
    int prosperity;
    int loyalty;

    City(string n, string t) : name(n), type(t) {
        population = 1000 + rand() % 2000;
        taxRate = 3;
        prosperity = 60 + rand() % 30;
        loyalty = 70 + rand() % 20;
    }

    void update(Resource& res) {   
        int tax = (population * taxRate) / 100;
        res.gold += tax;

        if (type == "Farm") res.food += population / 200;
        else if (type == "Mine") res.gold += tax / 2;
        else if (type == "Military" && loyalty > 50) res.soldiers += 1;

        prosperity += (taxRate <= 5) ? 2 : -1;
        loyalty -= (taxRate > 7) ? 5 : 1;
        population += prosperity / 20;

        if (prosperity > 100) prosperity = 100;
        if (prosperity < 0) prosperity = 0;
        if (loyalty > 100) loyalty = 100;
        if (loyalty < 0) loyalty = 0;
    }

    void show() const {
        cout << "  [" << name << "] Type:" << type
             << " Pop:" << population
             << " Tax:" << taxRate << "/10"
             << " Prosperity:" << prosperity
             << " Loyalty:" << loyalty << endl;
    }
};

class Kingdom {
private:
    vector<City> cities;  
    Resource player; 

    void clearScreen() { system("cls"); }
    
    void waitKey() {
        cout << "\nPress any key to continue...";
        _getch();
    }
    
    void displayText(const string& text, int delay = 50) {
        for (size_t i = 0; i < text.length(); i++) {
            cout << text[i];
            Sleep(delay);
            if (text[i] == '\n') {
                cout.flush();
            }
        }
        cout << endl;
    }

    void showStatus() {
        clearScreen();
        cout << "===============================================\n";
        cout << "  Kingdom of " << player.name << "\n";
        cout << "===============================================\n";
        cout << "  Gold: " << player.gold << " coins\n";
        cout << "  Soldiers: " << player.soldiers << " men\n";
        cout << "  Food: " << player.food << " units\n";
        cout << "  Stability: " << player.stability << "%\n";
        cout << "===============================================\n";
    }

    void randomEvent() {
        const char* events[] = {
            "A bountiful harvest! +50 Food, +5 Stability",
            "A merchant caravan visits. +100 Gold",
            "Bandits attack! Lose 2 Soldiers, gain 50 Gold (if Soldiers>5), else lose 80 Gold and 10 Stability",
            "Plague strikes... -20 Food, -10 Stability"
        };
        int e = rand() % 4;
        cout << "\nEvent: " << events[e] << endl;

        switch(e) {
            case 0: player.food += 50; player.stability += 5; break;
            case 1: player.gold += 100; break;
            case 2:
                if (player.soldiers > 5) { player.soldiers -= 2; player.gold += 50; }
                else { player.gold -= 80; player.stability -= 10; }
                break;
            case 3: player.food -= 20; player.stability -= 10; break;
        }
    }

    void initCities() {
        cities.clear();
        if (player.name == "France") {
            cities.push_back(City("Paris", "Trade"));
            cities.push_back(City("Orleans", "Farm"));
            cities.push_back(City("Lyon", "Military"));
        } else if (player.name == "England") {
            cities.push_back(City("London", "Trade"));
            cities.push_back(City("York", "Military"));
            cities.push_back(City("Canterbury", "Farm"));
        } else if (player.name == "Holy Roman") {
            cities.push_back(City("Aachen", "Trade"));
            cities.push_back(City("Nuremberg", "Mine"));
            cities.push_back(City("Cologne", "Military"));
        } else {  
            cities.push_back(City("Constantinople", "Trade"));
            cities.push_back(City("Thessalonica", "Farm"));
            cities.push_back(City("Nicea", "Military"));
        }
    }

    void manageCities() {
        int choice;
        do {
            clearScreen();
            cout << "=== Manage Cities ===\n";
            for (size_t i = 0; i < cities.size(); ++i) {
                cout << i+1 << ". "; cities[i].show();
            }
            cout << cities.size()+1 << ". Back\nChoice: ";
            cin >> choice;

            if (choice > 0 && choice <= (int)cities.size()) {
                City& c = cities[choice-1];
                cout << "\n1. Change Tax (Now: " << c.taxRate << ")\n"
                     << "2. Build (100 Gold, +10 Prosperity)\n"
                     << "3. Feast (50 Gold, +15 Loyalty)\nChoice: ";
                int act; cin >> act;
                if (act == 1) { cout << "New rate (1-10): "; cin >> c.taxRate; }
                else if (act == 2 && player.gold >= 100) { player.gold -= 100; c.prosperity += 10; }
                else if (act == 3 && player.gold >= 50) { player.gold -= 50; c.loyalty += 15; }
                else cout << "Not enough gold or invalid choice.\n";
                waitKey();
            }
        } while (choice != (int)cities.size()+1);
    }

    bool makeDecision() {
        int choice;
        showStatus();
        cout << "\n1. Recruit (100G -> 5 Soldiers)\n"
             << "2. Buy Food (50G -> 30 Food)\n"
             << "3. Tax (150G, -15 Stability)\n"
             << "4. Festival (80G, +20 Stability)\n"
             << "5. Manage Cities\n"
             << "6. End Turn\nChoice: ";
        cin >> choice;

        switch(choice) {
            case 1: if (player.gold>=100) { player.gold-=100; player.soldiers+=5; } break;
            case 2: if (player.gold>=50) { player.gold-=50; player.food+=30; } break;
            case 3: player.gold+=150; player.stability-=15; break;
            case 4: if (player.gold>=80) { player.gold-=80; player.stability+=20; } break;
            case 5: manageCities(); return false;  
            case 6: return true;  
        }
        if (player.stability > 100) player.stability = 100;
        if (player.stability < 0) player.stability = 0;
        waitKey();
        return true;
    }

    bool checkGameOver() {
        if (player.stability <= 0) { cout << "\nRebellion! Game Over.\n"; return true; }
        if (player.gold < 0) { cout << "\nBankrupt! Game Over.\n"; return true; }
        if (player.food <= 0) { cout << "\nFamine! Game Over.\n"; return true; }
        if (player.soldiers <= 0) { cout << "\nInvaded! Game Over.\n"; return true; }
        return false;
    }

public:
    void startGame() {
        srand(time(0));
        clearScreen();

        displayText("The 15th century dawns on a fractured continent.", 50);
        waitKey();
        system("cls");
        
        displayText("In the west, the long war between England and France continues to bleed both kingdoms, its end uncertain.", 50);
        waitKey();
        system("cls");
        
        displayText("The Holy Roman Empire is a mosaic of feuding princes, its emperor weak and his authority ignored.", 50);
        waitKey();
        system("cls");
        
        displayText("In the east, the shadow of a new power grows longer: the Ottoman Turks, having swallowed the Balkans, now fix their gaze on the crumbling walls of Constantinople, the last remnant of Rome.", 50);
        waitKey();
        system("cls");
        
        displayText("Heresy burns in Bohemia, and rival popes have only recently ceased tearing Christendom in two.", 50);
        waitKey();
        system("cls");
        
        displayText("This is an age of collapsing orders, of shifting loyalties, and of steel being tested.", 50);
        waitKey();
        system("cls");
        
        displayText("The old medieval world is dying, and the shape of the new one is for you to decide...", 50);
        waitKey();
        
        cout << "1. France\n2. England\n3. Holy Roman Empire\n4. Byzantine Empire\nChoice: ";
        int k; cin >> k;
        const char* names[] = {"France", "England", "Holy Roman", "Byzantine"};
        player.name = names[k-1];
        initCities();

        cout << "\nYou rule the " << player.name << " Kingdom. Begin!\n";
        waitKey();

        for (int year = 0; year < 10; ++year) {
            clearScreen();
            cout << "=== Year " << 1400+year << " ===\n";
            player.gold += 100;
            player.food += 20;
            cout << "Income: +100 Gold, +20 Food\n";

            cout << "\n--- City Reports ---\n";
            for (auto& city : cities) {
                city.update(player);
                city.show();
            }
            waitKey();

            while (!makeDecision()) {}
            randomEvent();
            if (checkGameOver()) break;
        }

        cout << "\n=== Game Ended ===\n";
        showStatus();
        cout << "\nPress any key to exit...";
        _getch();
    }
};

int main() {
    Kingdom game;
    game.startGame();
    return 0;
}


