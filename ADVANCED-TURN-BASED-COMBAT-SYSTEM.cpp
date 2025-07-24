/*
-------------------------------------------------------------
    SIMPLE TURN-BASED COMBAT SYSTEM V3 (FULL VERSION)
    Author: Dawid Chrobak
    Language: C++
    Description:
        Fully-featured console-based combat system built
        with structured logic and randomized gameplay.

        Features:
        - Turn-based player vs enemy mechanics
        - Dynamic difficulty and class selection
        - Combat actions with cooldowns and buffs:
            > Attack (with critical hit chance)
            > Damage Buff (15% boost, CD 5 rounds)
            > Defense Buff (damage reduction, CD 5)
            > Dodge (avoids damage, CD 5)
            > Heal (restores HP, CD 3)
            > Pearcing attack (ignores armor, CD 6)
        - Enemy AI decision-making (randomized behavior)
        - Cooldown & buff system (round-tracking)
        - Random value generation with balanced scaling
        - Output logs showing real-time combat feedback

-------------------------------------------------------------
    C++ TECHNIQUES USED:

    - Loops (`while`, `switch`, `do-while`)
    - `rand()` + `srand()` + `static_cast` for randomness
    - Conditional logic (`if`, `else if`)
    - Use of `float` for precision in HP and damage values
    - Modularity via switch-case for action handling
    - Safety checks (HP/Armor not dropping below 0)

-------------------------------------------------------------

    FILE STRUCTURE:

    - Main battle loop inside `while (playerHP > 0 && enemyHP > 0)`
    - Action menus displayed each round
    - Player chooses action (1–7)
    - Enemy responds with randomized action (1–8)
    - Cooldowns decrease each round

-------------------------------------------------------------
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;


int main() {

    srand(static_cast<unsigned int>(time(0))); // Seed RNG

    // --- Difficulty Selection ---
    string difficultyConfirm;
    int difficultyLevel;

    float enemyHP = 0.0, enemyArmor = 0.0;
    int enemyAttack = 0, enemyCritChance = 50;

    do {
        cout << "Choose difficulty (1-3)\n" << endl;
        cout << "1. Easy\n";
        cout << "2. Medium\n";
        cout << "3. Hard\n";

        cin >> difficultyLevel;

        switch (difficultyLevel)
        {
        case 1:
            cout << "You choose Easy\n";

            enemyHP = 100.0; // Enemy Healt Points
            enemyAttack = rand() % 6 + 5; // 5 - 10 DMG
            enemyArmor = 80.0; // Enemy Armor Points

            cout << "Enemy stats:\n\n";
            cout << "-------------------------\n";
            cout << "Enemy HP [ " << enemyHP << " ]\n";
            cout << "Enemy Armor [ " << enemyArmor << " ]\n";
            cout << "Enemy attack [ 5-10 DMG ]\n";
            cout << "-------------------------\n";
            break;

        case 2:
            cout << "You choose Medium\n";

            enemyHP = 150.0; // Enemy Health Points
            enemyAttack = rand() % 6 + 8; // 8 - 13
            enemyArmor = 100.0; // Enemy Armor Points

            cout << "Enemy stats:\n\n";
            cout << "-------------------------\n";
            cout << "Enemy HP [ " << enemyHP << " ]\n";
            cout << "Enemy Armor [ " << enemyArmor << " ]\n";
            cout << "Enemy attack [ 8-13 DMG ]\n";
            cout << "-------------------------\n";
            break;

        case 3:
            cout << "You choose Hard\n";

            enemyHP = 200.0; // Enemy Health Points
            enemyAttack = rand() % 6 + 11; // 11 - 16 DMG
            enemyArmor = 150.0; // Enemy Armor Points

            cout << "Enemy stats:\n\n";
            cout << "-------------------------\n";
            cout << "Enemy HP [ " << enemyHP << " ]\n";
            cout << "Enemy Armor [ " << enemyArmor << " ]\n";
            cout << "Enemy attack [ 11-16 DMG ]\n";
            cout << "-------------------------\n";
            break;

        default: cout << "Invalid option.\n";  break;
        }
        cout << "Confrim? (y/n)\n";
        cin >> difficultyConfirm;

    } while (difficultyConfirm != "y");

    string classConfirm;
    float playerHP = 0.0, playerArmor = 0.0;
    int playerAttack = 0;
    int playerClass, playerCritChance = 0;

    // --- Player Class Selection. Initialize player class statisticks --- 
    do {
        cout << "Choose class (1-3)\n\n";
        cout << "1. Warrior\n";
        cout << "2. Assasin\n";
        cout << "3. Defender\n";
        cin >> playerClass;

        switch (playerClass)
        {

        case 1:
            cout << "You choose Warrior\n\n";
            playerHP = 150.0; // Player Health Points
            playerAttack = rand() % 13 + 8; // 8 - 13 DMG
            playerArmor = 125.0; // Player Armor Points
            playerCritChance = 25; // Player Crit Chance

            cout << "Class stats:\n\n";
            cout << "-----------------------------------------------\n";
            cout << "Player HP [ " << playerHP << " ]\n";
            cout << "Player Armor [ " << playerArmor << " ]\n";
            cout << "Player Attack [ 8 - 13 DMG ] [ CRIT CHANCE 25% ]\n";
            cout << "-----------------------------------------------\n";
            break;

        case 2:
            cout << "You choose Assasin\n\n";
            playerHP = 125.0; // Player Health Points
            playerArmor = 100.0; // Player Armor Points
            playerAttack = rand() % 13 + 10; // 13 - 23 DMG
            playerCritChance = 60; // Player Crit Chance

            cout << "Class stats:\n\n";
            cout << "-----------------------------------------------\n";
            cout << "Player HP [ " << playerHP << " ]\n";
            cout << "Player Armor [ " << playerArmor << " ]\n";
            cout << "Player Attack [ 13 - 23 DMG ] [ CRIT CHANCE 60% ]\n";
            cout << "-----------------------------------------------\n";
            break;

        case 3:
            cout << "You choose Defender\n\n";

            playerHP = 200.0; // Player Health Points
            playerArmor = 150.0; // Player Armor Points
            playerAttack = rand() % 3 + 5; // 3 - 8 DMG
            playerCritChance = 15; // Player Crit Chance

            cout << "Class stats:\n\n";
            cout << "-----------------------------------------------\n";
            cout << "Player HP [ " << playerHP << " ]\n";
            cout << "Player Armor [ " << playerArmor << " ]\n";
            cout << "Player Attack [ 3 - 8 DMG ] [ CRIT CHANCE 15% ]\n";
            cout << "-----------------------------------------------\n";
            break;

        default: cout << "Invalid Option\n"; break;
        }
        cout << "Confirm? (y/n)\n"; 
        cin >> classConfirm;
    } while (classConfirm != "y");

    // Initalize Round Loop Initialization 
    int round = 1; 
    int playerAction;
    int finalAttack = 0;

    // Initialize Cooldowns And Buff Tracking
    int attackBuffCooldown = 0, defenseBuffCooldown = 0, healPotionCooldown = 0, dashCooldown = 0, pearcingCooldown = 0; 
    int attackBuffUsedRound = -1, defenseBuffUsedRound = -1;

    // Initialize Enemy Cooldowns And Buff Tracking
    int enemyAttackBuffCooldown = 0, enemyDefenseBuffCooldown = 0, enemyDashCooldown = 0, enemyHealPotionCooldown = 0; 
    int enemyAttackBuffUsedRound = -1, enemyDefenseBuffUsedRound = -1; 

    int critChance = rand() % 100 + 1; 

    while (playerHP > 0.0 && enemyHP > 0.0)
    {
        // Initalize player choices
        cout << "--- ROUND #" << round << " ---" << endl;
        cout << "\nChoose Action (1-6)\n\n";
        cout << "1. Attack                        4. Dash [ CD 5 ]\n";
        cout << "2. Attack buff [ 15% CD 5 ]      5. Defense buff [ 15% CD 5 ]\n";
        cout << "3. Pearcing Attack  [ CD 3 ]     6. Skip round\n";
        cout << "7. Heal potion [ +20 HP CD 3] \n\n";
        cin >> playerAction;

        // Initalize player actions -- Main player combat loop
        switch (playerAction)
        {
            // Initalize player attack options, with buffs crit etc.
        case 1:
            if (enemyArmor > 0) {
                if (critChance < playerCritChance && round == attackBuffUsedRound + 1) {
                    finalAttack = playerAttack * 1.65;
                    enemyArmor -= finalAttack;
                    cout << "Critical hit with buff! [ " << finalAttack << " ] DMG" << endl;
                }
                else if (round == attackBuffUsedRound + 1) {
                    finalAttack = playerAttack * 1.15;
                    enemyArmor -= finalAttack;
                    cout << "Attack with buff! [ " << finalAttack << " ] DMG" << endl;
                }
                else if (critChance < playerCritChance && round == defenseBuffUsedRound + 1) {
                    finalAttack = playerAttack * 1.5;
                    enemyArmor -= finalAttack;
                    cout << "Critical hit with defense buff! [ " << finalAttack << " ] DMG " << endl;
                    playerArmor -= enemyAttack / 1.15;
                }
                else if (round == defenseBuffUsedRound + 1) {
                    enemyArmor -= playerAttack;
                    cout << "Player deals [ " << playerAttack << " ] and reducted dmg" << endl;
                }
                else if (critChance < playerCritChance) {
                    finalAttack = playerAttack * 1.5;
                    enemyArmor -= finalAttack;
                    cout << "Critical hit! [ " << finalAttack << " ] DMG" << endl;
                }
                else {
                    enemyArmor -= playerAttack;
                    cout << "Player deals: [ " << playerAttack << " ] DMG" << endl;
                }
            }

            else if (enemyArmor <= 0) {
                if (critChance < playerCritChance && round == attackBuffUsedRound + 1) {
                    finalAttack = playerAttack * 1.65;
                    enemyHP -= finalAttack;
                    cout << "Critical hit with buff! [ " << finalAttack << " ] DMG" << endl;
                }
                else if (round == attackBuffUsedRound + 1) {
                    finalAttack = playerAttack * 1.15;
                    enemyHP -= finalAttack;
                    cout << "Attack with buff! [ " << finalAttack << " ] DMG" << endl;
                }
                else if (critChance < playerCritChance && round == defenseBuffUsedRound + 1) {
                    finalAttack = playerAttack * 1.5;
                    enemyHP -= finalAttack;
                    cout << "Critical hit with defense buff! [ " << finalAttack << " ] DMG " << endl;
                    playerHP -= enemyAttack / 0.15;
                }

                else if (round == defenseBuffUsedRound + 1) {
                    
                    enemyHP -= playerAttack;
                    cout << " Hit while defense buff active! [ " << playerAttack << " ] DMG " << endl;
                    playerHP -= enemyAttack / 0.15;
                }
                
                else if (critChance < playerCritChance) {
                    finalAttack = playerAttack * 1.5;
                    enemyHP -= finalAttack;
                    cout << "Critical hit! [ " << finalAttack << " ] DMG" << endl;
                }
                else {
                    enemyHP -= playerAttack;
                    cout << "Player deals: [ " << playerAttack << " ] DMG" << endl;
                }
            }
            break;

        case 2: if (attackBuffCooldown > 0) {
            
            cout << "Attack buff on cooldown: [ " << attackBuffCooldown << " ]" << endl;
        }
              else {
            cout << "Attack buff used\n";
            attackBuffUsedRound = round;
            attackBuffCooldown = 5;
        }
            break;
        case 3:
            if (pearcingCooldown > 0) {
                cout << "Pearcing attack on cooldown [ " << pearcingCooldown << " ]" << endl;

            }

            else if (pearcingCooldown == 0 && enemyArmor >= 0 && round == attackBuffUsedRound + 1) {
                enemyHP -= playerAttack * 1.15;
                cout << "Pearcing attack with buff! [ " << playerAttack << " ] DMG" << endl;
                pearcingCooldown = 6;

                }
            else if (pearcingCooldown == 0 && enemyArmor >= 0) {
                cout << "Pearcing attack!! [ " << playerAttack << " ] DMG" << endl;
                enemyHP -= playerAttack;
                pearcingCooldown = 6;
            }
            else  {
                finalAttack = playerAttack * 1.10;
                enemyHP -= finalAttack;
                pearcingCooldown = 6;
                cout << "No armor left, percing attak deals extra damage. [ " << playerAttack << " ] DMG" << endl;
            }
            


            break;

        case 4:
            if (dashCooldown > 0) {
                cout << "Dash on cooldown [ " << dashCooldown << " ]" << endl;
            }
            else if (playerArmor > 0) {
                cout << "You avoided attack" << endl;
                playerArmor -= enemyAttack * 0;
                dashCooldown = 5;
            }
            else if (playerArmor <= 0){
                cout << "You avoided attack" << endl;
                playerHP -= enemyAttack * 0;
                dashCooldown = 5;
            }
            break;

        case 5:
            if (defenseBuffCooldown > 0) {
                cout << "Defense buff on cooldown [ " << defenseBuffCooldown << " ]" << endl;
            }
            else {
                cout << "Defense buff used\n";
                defenseBuffUsedRound = round;
                defenseBuffCooldown = 5;
            }
            break;

        case 6:
            cout << "Round skipped\n";
            break;

        case 7:
            if (healPotionCooldown > 0) {
                cout << "Heal potion on cooldown [ " << healPotionCooldown << " ] " << endl;
            }
            else {
                cout << "Heal + 20 HP" << endl;
                playerHP += 20;
                healPotionCooldown = 3;
            }
            break;

        default: cout << "Invalid option\n"; break;
        }

        // Example: Reduce cooldowns each round for player
        if (attackBuffCooldown > 0) { attackBuffCooldown--; }
        if (defenseBuffCooldown > 0) { defenseBuffCooldown--; }
        if (healPotionCooldown > 0) { healPotionCooldown--; }
        if (dashCooldown > 0) { dashCooldown--; }
        if (pearcingCooldown > 0) { pearcingCooldown--; }

        // Refreshing Difficulty Level DMG
        switch (difficultyLevel) {
        case 1: enemyAttack = rand() % 6 + 5; break;     
        case 2: enemyAttack = rand() % 6 + 8; break;     
        case 3: enemyAttack = rand() % 6 + 11; break;   
        }

        
        int enemyAction;
        enemyAction = rand() % 8 + 1; // Initialize Enemy Random Choices
        int enemyCrit = rand() % 100 + 1; // Initalize Enemy Crit Chance

        int enemyFinalAttack = 0;

        // Main Enemy Combat Loop
        switch (enemyAction)
        {
        case 1:
            if (playerArmor > 0) {

                if (round == enemyAttackBuffUsedRound + 1 && enemyCrit <= enemyCritChance) {
                    enemyFinalAttack = enemyAttack * 1.65;
                    playerArmor -= enemyFinalAttack;
                    enemyAttackBuffCooldown = 3;
                    cout << "Enemy Ctitical strike with buff [ " << enemyFinalAttack << " ] DMG" << endl;

                }

                else if (round == enemyAttackBuffUsedRound + 1) {
                    enemyFinalAttack = enemyAttack * 1.15;
                    playerArmor -= enemyFinalAttack;
                    enemyAttackBuffCooldown = 3;
                    cout << "Enemy strike with attack buff! [ " << enemyFinalAttack << " ] DMG" << endl;

                }

                else if (enemyCrit < enemyCritChance) {
                    enemyFinalAttack = enemyAttack * 1.5;
                    playerArmor -= enemyFinalAttack;
                    cout << "Enemy Critical strike! [ " << enemyFinalAttack << " ] DMG" << endl;

                }

                else {
                    playerArmor -= enemyAttack;
                    cout << "Enemy normal attack! [ " << enemyAttack << " ] DMG" << endl;

                }
            }

            else if (playerArmor <= 0) {

                if (round == enemyAttackBuffUsedRound + 1 && enemyCrit <= enemyCritChance) {
                    enemyFinalAttack = enemyAttack * 1.65;
                    playerHP -= enemyFinalAttack;
                    enemyAttackBuffCooldown = 3;
                    cout << "Enemy Ctitical strike with buff [ " << enemyFinalAttack << " ] DMG" << endl;

                }

                else if (round == enemyAttackBuffUsedRound + 1) {
                    enemyFinalAttack = enemyAttack * 1.15;
                    playerHP -= enemyFinalAttack;
                    enemyAttackBuffCooldown = 3;
                    cout << "Enemy strike with attack buff! [ " << enemyFinalAttack << " ] DMG" << endl;

                }

                else if (enemyCrit < enemyCritChance) {
                    enemyFinalAttack = enemyAttack * 1.5;
                    playerHP -= enemyFinalAttack;
                    cout << "Enemy Critical strike! [ " << enemyFinalAttack << " ] DMG" << endl;

                }

                else {
                    playerHP -= enemyAttack;
                    cout << "Enemy normal attack! [ " << enemyAttack << " ] DMG" << endl;

                }
            }
            if (round == enemyDefenseBuffUsedRound + 1) {
                enemyHP -= playerAttack * 0.15;
                cout << "Player dmg reducted by enemy!" << endl;
                enemyDefenseBuffCooldown = 3;
            }
            break;
        case 2:
            if (enemyAttackBuffCooldown > 0) {
                cout << "Enemy attack buff on cooldown [ " << enemyAttackBuffCooldown << " ]" << endl;
            }
            else {
                cout << "Enemy used attack buff" << endl;
                enemyAttackBuffUsedRound = round;
                enemyAttackBuffCooldown = 3;
            }
            break;

        case 3:
            if (enemyAttackBuffCooldown > 0) {
                cout << "Enemy defense buff on cooldown [ " << enemyDefenseBuffCooldown << " ]" << endl;
            }
            else {
                cout << "Enemy used defense buff" << endl;
                enemyDefenseBuffUsedRound = round;
                enemyDefenseBuffCooldown = 3;
            }
            
            break;
        case 4:
            if (enemyHealPotionCooldown > 0) {
                cout << "Enemy heal potion on cooldown [ " << enemyHealPotionCooldown << " ] " << endl;
            }
            else {
                cout << "Enemy use heal!" << endl;
                enemyHP += 20;
                enemyHealPotionCooldown = 3;
            }
            break;
        case 5: 
            if (enemyDashCooldown > 0) {
                cout << "Enemy dash on cooldown [ " << enemyDashCooldown << " ]" << endl;
            }
            else {
                enemyHP -= playerAttack * 0;
                cout << "Enemy avoided attack!\n";
                enemyDashCooldown = 3;
            }
            
            break;
        case 6: 
            if (playerArmor > 0) {

            if (round == enemyAttackBuffUsedRound + 1 && enemyCrit <= enemyCritChance) {
                enemyFinalAttack = enemyAttack * 1.65;
                playerArmor -= enemyFinalAttack;
                enemyAttackBuffCooldown = 3;
                cout << "Enemy Ctitical strike with buff [ " << enemyFinalAttack << " ] DMG" << endl;

            }

            else if (round == enemyAttackBuffUsedRound + 1) {
                enemyFinalAttack = enemyAttack * 1.15;
                playerArmor -= enemyFinalAttack;
                enemyAttackBuffCooldown = 3;
                cout << "Enemy strike with attack buff! [ " << enemyFinalAttack << " ] DMG" << endl;

            }

            else if (enemyCrit < enemyCritChance) {
                enemyFinalAttack = enemyAttack * 1.5;
                playerArmor -= enemyFinalAttack;
                cout << "Enemy Critical strike! [ " << enemyFinalAttack << " ] DMG" << endl;

            }

            else {
                playerArmor -= enemyAttack;
                cout << "Enemy normal attack! [ " << enemyAttack << " ] DMG" << endl;

            }
        }

              else if (playerArmor <= 0) {

            if (round == enemyAttackBuffUsedRound + 1 && enemyCrit <= enemyCritChance) {
                enemyFinalAttack = enemyAttack * 1.65;
                playerHP -= enemyFinalAttack;
                enemyAttackBuffCooldown = 3;
                cout << "Enemy Ctitical strike with buff [ " << enemyFinalAttack << " ] DMG" << endl;

            }

            else if (round == enemyAttackBuffUsedRound + 1) {
                enemyFinalAttack = enemyAttack * 1.15;
                playerHP -= enemyFinalAttack;
                enemyAttackBuffCooldown = 3;
                cout << "Enemy strike with attack buff! [ " << enemyFinalAttack << " ] DMG" << endl;

            }

            else if (enemyCrit < enemyCritChance) {
                enemyFinalAttack = enemyAttack * 1.5;
                playerHP -= enemyFinalAttack;
                cout << "Enemy Critical strike! [ " << enemyFinalAttack << " ] DMG" << endl;

            }

            else {
                playerHP -= enemyAttack;
                cout << "Enemy normal attack! [ " << enemyAttack << " ] DMG" << endl;

            }
        }
              if (round == enemyDefenseBuffUsedRound + 1) {
                  enemyHP -= playerAttack * 0.15;
                  cout << "Player dmg reducted by enemy!" << endl;
                  enemyDefenseBuffCooldown = 3;
              }
              break;

        case 7: 
            if (playerArmor > 0) {

            if (round == enemyAttackBuffUsedRound + 1 && enemyCrit <= enemyCritChance) {
                enemyFinalAttack = enemyAttack * 1.65;
                playerArmor -= enemyFinalAttack;
                enemyAttackBuffCooldown = 3;
                cout << "Enemy Ctitical strike with buff [ " << enemyFinalAttack << " ] DMG" << endl;

            }

            else if (round == enemyAttackBuffUsedRound + 1) {
                enemyFinalAttack = enemyAttack * 1.15;
                playerArmor -= enemyFinalAttack;
                enemyAttackBuffCooldown = 3;
                cout << "Enemy strike with attack buff! [ " << enemyFinalAttack << " ] DMG" << endl;

            }

            else if (enemyCrit < enemyCritChance) {
                enemyFinalAttack = enemyAttack * 1.5;
                playerArmor -= enemyFinalAttack;
                cout << "Enemy Critical strike! [ " << enemyFinalAttack << " ] DMG" << endl;

            }

            else {
                playerArmor -= enemyAttack;
                cout << "Enemy normal attack! [ " << enemyAttack << " ] DMG" << endl;

            }
        }

              else if (playerArmor <= 0) {

            if (round == enemyAttackBuffUsedRound + 1 && enemyCrit <= enemyCritChance) {
                enemyFinalAttack = enemyAttack * 1.65;
                playerHP -= enemyFinalAttack;
                enemyAttackBuffCooldown = 3;
                cout << "Enemy Ctitical strike with buff [ " << enemyFinalAttack << " ] DMG" << endl;

            }

            else if (round == enemyAttackBuffUsedRound + 1) {
                enemyFinalAttack = enemyAttack * 1.15;
                playerHP -= enemyFinalAttack;
                enemyAttackBuffCooldown = 3;
                cout << "Enemy strike with attack buff! [ " << enemyFinalAttack << " ] DMG" << endl;

            }

            else if (enemyCrit < enemyCritChance) {
                enemyFinalAttack = enemyAttack * 1.5;
                playerHP -= enemyFinalAttack;
                cout << "Enemy Critical strike! [ " << enemyFinalAttack << " ] DMG" << endl;

            }

            else {
                playerHP -= enemyAttack;
                cout << "Enemy normal attack! [ " << enemyAttack << " ] DMG" << endl;

            }
        }
              if (round == enemyDefenseBuffUsedRound + 1) {
                  enemyHP -= playerAttack * 0.15;
                  cout << "Player dmg reducted by enemy!" << endl;
                  enemyDefenseBuffCooldown = 3;
              }
              break;

        case 8: if (playerArmor > 0) {

            if (round == enemyAttackBuffUsedRound + 1 && enemyCrit <= enemyCritChance) {
                enemyFinalAttack = enemyAttack * 1.65;
                playerArmor -= enemyFinalAttack;
                enemyAttackBuffCooldown = 3;
                cout << "Enemy Ctitical strike with buff [ " << enemyFinalAttack << " ] DMG" << endl;

            }

            else if (round == enemyAttackBuffUsedRound + 1) {
                enemyFinalAttack = enemyAttack * 1.15;
                playerArmor -= enemyFinalAttack;
                enemyAttackBuffCooldown = 3;
                cout << "Enemy strike with attack buff! [ " << enemyFinalAttack << " ] DMG" << endl;

            }

            else if (enemyCrit < enemyCritChance) {
                enemyFinalAttack = enemyAttack * 1.5;
                playerArmor -= enemyFinalAttack;
                cout << "Enemy Critical strike! [ " << enemyFinalAttack << " ] DMG" << endl;

            }

            else {
                playerArmor -= enemyAttack;
                cout << "Enemy normal attack! [ " << enemyAttack << " ] DMG" << endl;

            }
        }

              else if (playerArmor <= 0) {

            if (round == enemyAttackBuffUsedRound + 1 && enemyCrit <= enemyCritChance) {
                enemyFinalAttack = enemyAttack * 1.65;
                playerHP -= enemyFinalAttack;
                enemyAttackBuffCooldown = 3;
                cout << "Enemy Ctitical strike with buff [ " << enemyFinalAttack << " ] DMG" << endl;

            }

            else if (round == enemyAttackBuffUsedRound + 1) {
                enemyFinalAttack = enemyAttack * 1.15;
                playerHP -= enemyFinalAttack;
                enemyAttackBuffCooldown = 3;
                cout << "Enemy strike with attack buff! [ " << enemyFinalAttack << " ] DMG" << endl;

            }

            else if (enemyCrit < enemyCritChance) {
                enemyFinalAttack = enemyAttack * 1.5;
                playerHP -= enemyFinalAttack;
                cout << "Enemy Critical strike! [ " << enemyFinalAttack << " ] DMG" << endl;

            }

            else {
                playerHP -= enemyAttack;
                cout << "Enemy normal attack! [ " << enemyAttack << " ] DMG" << endl;

            }
        }
              if (round == enemyDefenseBuffUsedRound + 1) {
                  enemyHP -= playerAttack * 0.15;
                  cout << "Player dmg reducted by enemy!" << endl;
                  enemyDefenseBuffCooldown = 3;
              }
              break;
        }

        // Example: Reduce Cooldowns Each Round For Enemy
        if (enemyAttackBuffCooldown > 0) { enemyAttackBuffCooldown--; }
        if (enemyDashCooldown > 0) { enemyDashCooldown--; }
        if (enemyDefenseBuffCooldown > 0) { enemyDefenseBuffCooldown--; }
        if (enemyHealPotionCooldown > 0) { enemyHealPotionCooldown--; }

        // Initalize Armor Points, Can't Go Belowe 0.0 
        enemyArmor = max(0.0f, enemyArmor);
        playerArmor = max(0.0f, playerArmor);
        cout << "Enemy status: HP [ " << enemyHP << " ] Armor [ " << enemyArmor << " ]\n";
        cout << "Player status: HP [ " << playerHP << " ] Armor [ " << playerArmor << " ]\n";

        round++;

    }

    // Initalize Healt Points, Can't Go Belowe 0.0 
    enemyHP = max(0.0f, enemyHP);
    playerHP = max(0.0f, playerHP);

    // Initalize Game Result
    if (enemyHP <= 0.0) {
        cout << "[[ --- VICTORY --- ]]\n";
    }
    else if (playerHP <= 0.0) {
        cout << "[[ --- DEFEAT --- ]]\n";
    }
    else {
        cout << "[[ --- DRAW --- ]]\n";
    }

 
    return 0;
}