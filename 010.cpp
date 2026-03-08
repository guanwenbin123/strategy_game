#include<iostream>
#include<windows.h>
#include<iomanip>
#include<stdlib.h>
#include<conio.h>

using namespace std;

class Kingdom {
private:
    struct Resource {
        int gold = 400;       
        int soldiers = 10;    
        int food = 100;       
        int stability = 70;  
        string name;         
    };
    
    Resource player;
    
    void showStatus() {
        system("cls");
        cout << "===============================================" << endl;
        cout << "  Kingdom of " << player.name << endl;
        cout << "===============================================" << endl;
        cout << "  Gold: " << player.gold << " coins" << endl;
        cout << "  Soldiers: " << player.soldiers << " men" << endl;
        cout << "  Food: " << player.food << " units" << endl;
        cout << "  Stability: " << player.stability << "%\n";
        cout << "==============================================="<<endl;
    }
    
	void waitForKey(bool skipable = true) {
	    if (skipable) {
	        cout << "\nPress any key (0 to skip)...";
	        int key = _getch();
	        if (key == 48) {  
	            cout << " [Skipped]" << endl;
	            return;
	        }
	    } else {
	        cout << "\nPress any key to continue...";
	        _getch();
	    }
	}
	
	void displayText(const string& text, int delay = 50, bool skipable = true) {
    	for (size_t i = 0; i < text.length(); i++) {
        	if (skipable && _kbhit()) {   
            	int key = _getch();
            	if (key == 48) {  
                	cout << text.substr(i);
                	cout << " [Skipped]";
                	while (_kbhit()) _getch();
	            	break;
	            	}
        		}
        		cout << text[i];
        		Sleep(delay);
       			if (text[i] == '\n') {
	        	    cout.flush();
    	    	}
    		}
    	cout << endl;
	}
    void randomEvent() {
        int event = rand() % 4;
        
        switch(event) {
            case 0: {   
                displayText("\nThis year brings a bountiful harvest!", 30, true);
                player.food += 50;
                player.stability += 5;
                cout << "  +50 Food, +5 Stability" << endl;
                break;
            }
            case 1: {  
                displayText("\nA friendly merchant caravan passes through your lands.", 30, true);
                player.gold += 100;
                cout << "  +100 Gold" << endl;
                break;
            }
            case 2: {   
                displayText("\nBandits raid one of your villages!", 30, true);
                if (player.soldiers > 5) {
                    displayText("Your soldiers drive off the bandits.", 30, true);
                    player.soldiers -= 2;
                    player.gold += 50;  // Loot
                    cout << "  -2 Soldiers, +50 Gold" << endl;
                } else {
                    displayText("Insufficient soldiers, the village is pillaged...", 30, true);
                    player.gold -= 80;
                    player.stability -= 10;
                    cout << "  -80 Gold, -10 Stability" << endl;
                }
                break;
            }
            case 3: {   
                displayText("\nPlague breaks out in your domain...", 30, true);
                player.food -= 30;
                player.stability -= 15;
                cout << "  -30 Food, -15 Stability" << endl;
                break;
            }
        }
    }
    
    void yearStart(int year) {
        system("cls");
        cout << "===============================================\n";
        cout << "          Year " << 1400 + year << " A.D.\n";
        cout << "===============================================\n";
        
        player.gold += 100;
        player.food += 20;
        
        cout << "Annual income: +100 Gold, +20 Food\n\n";
        waitForKey(false);
    }
    
    void makeDecision() {
        int choice;
        bool valid = false;
        
        while (!valid) {
            showStatus();
            displayText("\nWhat will you decide?", 30, true);
            cout << "1. Recruit Soldiers (100 Gold, gain 5 Soldiers)\n";
            cout << "2. Buy Food (50 Gold, gain 30 Food)\n";
            cout << "3. Levy Taxes (150 Gold, -15 Stability)\n";
            cout << "4. Hold Festival (80 Gold, +20 Stability)\n";
            cout << "5. End Turn\n";
            cout << "Choose (1-5): ";
            
            cin >> choice;
            
            switch(choice) {
                case 1:
                    if (player.gold >= 100) {
                        player.gold -= 100;
                        player.soldiers += 5;
                        displayText("\n5 new soldiers recruited.", 30, true);
                        valid = true;
                    } else {
                        displayText("\nNot enough Gold!", 30, true);
                        waitForKey(false);
                    }
                    break;
                case 2:
                    if (player.gold >= 50) {
                        player.gold -= 50;
                        player.food += 30;
                        displayText("\nPurchased 30 units of food.", 30, true);
                        valid = true;
                    } else {
                        displayText("\nNot enough Gold!", 30, true);
                        waitForKey(false);
                    }
                    break;
                case 3:
                    player.gold += 150;
                    player.stability -= 15;
                    if (player.stability < 0) player.stability = 0;
                    displayText("\nYou impose heavy taxes on the people...", 30, true);
                    valid = true;
                    break;
                case 4:
                    if (player.gold >= 80) {
                        player.gold -= 80;
                        player.stability += 20;
                        if (player.stability > 100) player.stability = 100;
                        displayText("\nThe festival brings joy to the people!", 30, true);
                        valid = true;
                    } else {
                        displayText("\nNot enough Gold!", 30, true);
                        waitForKey(false);
                    }
                    break;
                case 5:
                    displayText("\nYou decide to maintain the status quo.", 30, true);
                    valid = true;
                    break;
                default:
                    displayText("\nInvalid choice!", 30, true);
                    waitForKey(false);
            }
        }
        waitForKey(false);
    }
    
    bool checkGameOver() {
        if (player.stability <= 0) {
            displayText("\nThe people rise in rebellion against your rule!", 30, false);
            displayText("Your reign has ended...", 30, false);
            return true;
        }
        if (player.gold < 0) {
            displayText("\nThe kingdom is bankrupt! Creditors seize your castle.", 30, false);
            return true;
        }
        if (player.food <= 0) {
            displayText("\nFamine sweeps the land, people starve...", 30, false);
            return true;
        }
        if (player.soldiers <= 0) {
            displayText("\nWith no soldiers to defend, neighboring kingdoms invade and conquer your lands.", 30, false);
            return true;
        }
        return false;
    }
    
public:
    void startGame() {
        srand(time(0));   
        
        displayText("The 15th century dawns on a fractured continent.", 50, true);
        waitForKey();
        system("cls");
        
        displayText("In the west, the long war between England and France continues to bleed both kingdoms, its end uncertain.", 50, true);
        waitForKey();
        system("cls");
        
        displayText("The Holy Roman Empire is a mosaic of feuding princes, its emperor weak and his authority ignored.", 50, true);
        waitForKey();
        system("cls");
        
        displayText("In the east, the shadow of a new power grows longer: the Ottoman Turks, having swallowed the Balkans, now fix their gaze on the crumbling walls of Constantinople, the last remnant of Rome.", 50, true);
        waitForKey();
        system("cls");
        
        displayText("Heresy burns in Bohemia, and rival popes have only recently ceased tearing Christendom in two.", 50, true);
        waitForKey();
        system("cls");
        
        displayText("This is an age of collapsing orders, of shifting loyalties, and of steel being tested.", 50, true);
        waitForKey();
        system("cls");
        
        displayText("The old medieval world is dying, and the shape of the new one is for you to decide...", 50, false);
        waitForKey(false);
        
        system("cls");
        cout << "===============================================\n";
        cout << "            Choose Your Kingdom\n";
        cout << "===============================================\n";
        cout << "1. Kingdom of France" << endl;
        cout << "2. Kingdom of England" << endl;
        cout << "3. Holy Roman Empire" << endl;
        cout << "4. Byzantine Empire" << endl;
        cout << "===============================================\n";
        cout << "Choose (1-4): ";
        
        int kingdomChoice;
        cin >> kingdomChoice;
        
        switch(kingdomChoice) {
            case 1:
                player.name = "France";
                player.soldiers = 15;
                player.gold = 500;
                break;
            case 2:
                player.name = "England";
                player.soldiers = 12;
                player.gold = 600;
                break;
            case 3:
                player.name = "Holy Roman";
                player.stability = 60;   
                player.gold = 450;
                break;
            case 4:
                player.name = "Byzantine";
                player.soldiers = 8;
                player.food = 80;
                player.stability = 50;   
                break;
            default:
                player.name = "France";
        }
        
        displayText("\nYou have chosen the " + player.name + " Kingdom.", 30, true);
        displayText("May God bless your reign!", 30, false);
        waitForKey(false);
        
        for (int year = 0; year < 10; year++) {
            yearStart(year);
            makeDecision();
            
            randomEvent();
            
            if (checkGameOver()) {
                break;
            }
            
            if (year == 9) {
                displayText("\n\nAfter ten years of rule, you have successfully consolidated your kingdom!", 30, false);
                displayText("Your name shall be remembered in history!", 30, false);
                waitForKey(false);
            }
        }
        
        system("cls");
        cout << "===============================================\n";
        cout << "               Game Over\n";
        cout << "===============================================\n";
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