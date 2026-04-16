/*
 * RPG Game - Level 3: Complex Game Systems
 * Learn game development, character systems, and combat mechanics
 * Written like a human game developer would write it!
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NAME_LENGTH 50
#define MAX_INVENTORY 20
#define MAX_ENEMIES 10

// Character structure - the heart of our RPG!
typedef struct {
    char name[MAX_NAME_LENGTH];
    int health;
    int max_health;
    int attack;
    int defense;
    int level;
    int experience;
    int gold;
    char inventory[MAX_INVENTORY][MAX_NAME_LENGTH];
    int inventory_count;
} Player;

// Enemy structure - for combat encounters!
typedef struct {
    char name[MAX_NAME_LENGTH];
    int health;
    int max_health;
    int attack;
    int defense;
    int gold_reward;
    int exp_reward;
    char description[200];
} Enemy;

// Item structure - for loot and equipment!
typedef struct {
    char name[MAX_NAME_LENGTH];
    char type[20];  // weapon, armor, potion, misc
    int value;
    int effect;
    char description[100];
} Item;

// Game state - track everything!
typedef struct {
    Player player;
    Enemy current_enemy;
    int in_combat;
    int game_over;
    int enemies_defeated;
    int rooms_explored;
} GameState;

// Initialize player character
void init_player(Player* player, const char* name) {
    strcpy(player->name, name);
    player->health = 100;
    player->max_health = 100;
    player->attack = 15;
    player->defense = 5;
    player->level = 1;
    player->experience = 0;
    player->gold = 50;
    player->inventory_count = 0;
    
    // Starting equipment
    strcpy(player->inventory[0], "Rusty Sword");
    strcpy(player->inventory[1], "Leather Armor");
    strcpy(player->inventory[2], "Health Potion");
    player->inventory_count = 3;
    
    printf("✨ %s the hero begins their journey!\n", name);
    printf("   Health: %d/%d\n", player->health, player->max_health);
    printf("   Attack: %d  Defense: %d\n", player->attack, player->defense);
    printf("   Gold: %d\n", player->gold);
}

// Create enemies with personality!
void create_enemy(Enemy* enemy, int type) {
    switch(type) {
        case 1: // Goblin
            strcpy(enemy->name, "Goblin Warrior");
            strcpy(enemy->description, "A nasty green creature with rusty armor and bloodshot eyes. It drools as it eyes your gold!");
            enemy->health = 30;
            enemy->max_health = 30;
            enemy->attack = 8;
            enemy->defense = 2;
            enemy->gold_reward = 20;
            enemy->exp_reward = 25;
            break;
            
        case 2: // Orc
            strcpy(enemy->name, "Orc Brute");
            strcpy(enemy->description, "A massive green beast with muscles bulging and a crude axe. It smells terrible!");
            enemy->health = 50;
            enemy->max_health = 50;
            enemy->attack = 12;
            enemy->defense = 5;
            enemy->gold_reward = 40;
            enemy->exp_reward = 50;
            break;
            
        case 3: // Dark Knight
            strcpy(enemy->name, "Dark Knight");
            strcpy(enemy->description, "A shadowy figure in black armor. Red eyes glow from within the helmet. Evil radiates from it!");
            enemy->health = 80;
            enemy->max_health = 80;
            enemy->attack = 18;
            enemy->defense = 10;
            enemy->gold_reward = 100;
            enemy->exp_reward = 100;
            break;
            
        case 4: // Dragon (Boss!)
            strcpy(enemy->name, "Ancient Red Dragon");
            strcpy(enemy->description, "A colossal dragon with scales like rubies and fire burning in its throat. The ground trembles as it breathes!");
            enemy->health = 200;
            enemy->max_health = 200;
            enemy->attack = 25;
            enemy->defense = 15;
            enemy->gold_reward = 500;
            enemy->exp_reward = 500;
            break;
            
        default:
            strcpy(enemy->name, "Rat");
            strcpy(enemy->description, "Just a giant rat. Kinda pathetic, really.");
            enemy->health = 10;
            enemy->max_health = 10;
            enemy->attack = 3;
            enemy->defense = 0;
            enemy->gold_reward = 5;
            enemy->exp_reward = 5;
    }
}

// Display player status with style!
void display_player_status(Player* player) {
    printf("\n" + "="*60);
    printf("⚔️  %s - Level %d Adventurer ⚔️", player->name, player->level);
    printf("="*60);
    printf("❤️  Health: %d/%d", player->health, player->max_health);
    printf("⚔️  Attack: %d    🛡️  Defense: %d", player->attack, player->defense);
    printf("⭐  Experience: %d   💰  Gold: %d", player->experience, player->gold);
    printf("🎒  Inventory (%d items):", player->inventory_count);
    
    for (int i = 0; i < player->inventory_count; i++) {
        printf("   • %s", player->inventory[i]);
    }
    printf("="*60);
}

// Display enemy with intimidation!
void display_enemy(Enemy* enemy) {
    printf("\n" + "!"*50);
    printf("👹 %s APPEARS! 👹", enemy->name);
    printf("!"*50);
    printf("%s", enemy->description);
    printf("❤️  Health: %d/%d", enemy->health, enemy->max_health);
    printf("⚔️  Attack: %d    🛡️  Defense: %d", enemy->attack, enemy->defense);
    printf("💰  Reward: %d gold, %d EXP", enemy->gold_reward, enemy->exp_reward);
    printf("!"*50);
}

// Combat system with strategy!
void combat(GameState* game) {
    Enemy* enemy = &game->current_enemy;
    Player* player = &game->player;
    
    printf("\n⚔️  COMBAT BEGINS! ⚔️\n");
    
    while (enemy->health > 0 && player->health > 0) {
        printf("\n" + "-"*40);
        printf("Your Turn: %d HP | Enemy: %d HP", player->health, enemy->health);
        printf("1. 🗡️  Attack");
        printf("2. 🛡️  Defend");
        printf("3. 🧪  Use Item");
        printf("4. 🏃  Flee");
        printf("Choose action: ");
        
        int choice;
        scanf("%d", &choice);
        getchar(); // Clear newline
        
        int player_damage = 0;
        int enemy_damage = 0;
        
        switch(choice) {
            case 1: // Attack
                player_damage = player->attack + (rand() % 10 - 5); // +/- 5 random
                enemy_damage = enemy->attack - player->defense + (rand() % 6 - 3);
                
                printf("You strike with all your might!\n");
                
                // Critical hit chance!
                if (rand() % 20 == 0) {
                    player_damage *= 2;
                    printf("💥 CRITICAL HIT! 💥\n");
                }
                
                enemy->health -= player_damage;
                printf("You deal %d damage!\n", player_damage);
                break;
                
            case 2: // Defend
                printf("You raise your shield defensively!\n");
                enemy_damage = (enemy->attack - player->defense * 2) / 2 + (rand() % 4 - 2);
                
                // Counter attack chance!
                if (rand() % 4 == 0) {
                    player_damage = player->attack / 2;
                    enemy->health -= player_damage;
                    printf("⚡  COUNTER ATTACK! You strike for %d damage!\n", player_damage);
                }
                break;
                
            case 3: // Use Item
                if (player->inventory_count > 0) {
                    printf("Your items:\n");
                    for (int i = 0; i < player->inventory_count; i++) {
                        printf("%d. %s\n", i + 1, player->inventory[i]);
                    }
                    printf("Use which item? ");
                    int item_choice;
                    scanf("%d", &item_choice);
                    getchar();
                    
                    if (item_choice > 0 && item_choice <= player->inventory_count) {
                        char* item = player->inventory[item_choice - 1];
                        
                        if (strstr(item, "Health Potion")) {
                            int heal = 30 + rand() % 20;
                            player->health = (player->health + heal < player->max_health) ? 
                                          player->health + heal : player->max_health;
                            printf("You drink potion and restore %d HP!\n", heal);
                            
                            // Remove used item
                            for (int i = item_choice - 1; i < player->inventory_count - 1; i++) {
                                strcpy(player->inventory[i], player->inventory[i + 1]);
                            }
                            player->inventory_count--;
                        } else {
                            printf("You can't use %s in combat!\n", item);
                        }
                    }
                } else {
                    printf("No items to use!\n");
                }
                continue; // Skip enemy turn
                
            case 4: // Flee
                if (rand() % 3 == 0) { // 33% success rate
                    printf("You successfully escape!\n");
                    game->in_combat = 0;
                    return;
                } else {
                    printf("You try to flee but fail!\n");
                    enemy_damage = enemy->attack;
                }
                break;
                
            default:
                printf("You hesitate and lose your turn!\n");
                enemy_damage = enemy->attack;
        }
        
        // Enemy turn (if not fled)
        if (enemy->health > 0 && game->in_combat) {
            if (enemy_damage > 0) {
                player->health -= enemy_damage;
                printf("%s attacks for %d damage!\n", enemy->name, enemy_damage);
            }
        }
        
        // Check combat end
        if (player->health <= 0) {
            printf("\n💀  You have been defeated by %s! 💀\n", enemy->name);
            game->game_over = 1;
        } else if (enemy->health <= 0) {
            printf("\n🎉  VICTORY! You defeated %s! 🎉\n", enemy->name);
            
            // Rewards!
            player->gold += enemy->gold_reward;
            player->experience += enemy->exp_reward;
            game->enemies_defeated++;
            
            printf("💰  + %d gold", enemy->gold_reward);
            printf("⭐  + %d EXP", enemy->exp_reward);
            printf("🏆  Enemies defeated: %d", game->enemies_defeated);
            
            // Level up check!
            if (player->experience >= player->level * 100) {
                player->level++;
                player->max_health += 20;
                player->health = player->max_health;
                player->attack += 5;
                player->defense += 2;
                
                printf("\n🌟  LEVEL UP! 🌟");
                printf("You are now level %d!", player->level);
                printf("Health: %d/%d, Attack: %d, Defense: %d", 
                       player->health, player->max_health, player->attack, player->defense);
            }
            
            game->in_combat = 0;
        }
    }
}

// Exploration system
void explore(GameState* game) {
    printf("\n🗺️  You venture deeper into the dungeon...\n");
    
    // Random encounter!
    int encounter_type = rand() % 100;
    
    if (encounter_type < 60) { // 60% enemy
        int enemy_type = (rand() % 3) + 1; // Enemies 1-3
        if (game->enemies_defeated > 5) enemy_type = 4; // Dragon after 5 kills!
        
        create_enemy(&game->current_enemy, enemy_type);
        game->in_combat = 1;
        display_enemy(&game->current_enemy);
        
    } else if (encounter_type < 80) { // 20% treasure
        int gold_found = 10 + rand() % 50;
        game->player.gold += gold_found;
        printf("💰  You found a treasure chest with %d gold!", gold_found);
        
        // Random item!
        if (rand() % 3 == 0) {
            char* items[] = {"Magic Sword", "Shield of Light", "Dragon Scale Armor", "Health Potion"};
            int item_index = rand() % 4;
            
            if (game->player.inventory_count < MAX_INVENTORY) {
                strcpy(game->player.inventory[game->player.inventory_count], items[item_index]);
                game->player.inventory_count++;
                printf("🎒  And found a %s!", items[item_index]);
            }
        }
        
    } else if (encounter_type < 95) { // 15% merchant
        printf("\n🧙  You meet a mysterious merchant!\n");
        printf("Merchant: 'I have rare items for sale, brave adventurer!'\n");
        printf("Your gold: %d", game->player.gold);
        printf("1. Buy Health Potion (20 gold)");
        printf("2. Buy Sword Upgrade (50 gold)");
        printf("3. Buy Armor Upgrade (40 gold)");
        printf("4. Leave shop");
        
        int shop_choice;
        printf("Choice: ");
        scanf("%d", &shop_choice);
        getchar();
        
        switch(shop_choice) {
            case 1:
                if (game->player.gold >= 20) {
                    game->player.gold -= 20;
                    if (game->player.inventory_count < MAX_INVENTORY) {
                        strcpy(game->player.inventory[game->player.inventory_count], "Health Potion");
                        game->player.inventory_count++;
                        printf("Purchased Health Potion!");
                    }
                } else {
                    printf("Not enough gold!");
                }
                break;
            case 2:
                if (game->player.gold >= 50) {
                    game->player.gold -= 50;
                    game->player.attack += 5;
                    printf("Sword upgraded! Attack +5");
                } else {
                    printf("Not enough gold!");
                }
                break;
            case 3:
                if (game->player.gold >= 40) {
                    game->player.gold -= 40;
                    game->player.defense += 3;
                    printf("Armor upgraded! Defense +3");
                } else {
                    printf("Not enough gold!");
                }
                break;
        }
        
    } else { // 5% healing fountain
        printf("⛲  You discover a magical healing fountain!\n");
        int heal_amount = 20 + rand() % 30;
        game->player.health = (game->player.health + heal_amount < game->player.max_health) ? 
                            game->player.health + heal_amount : game->player.max_health;
        printf("You drink from the fountain and restore %d HP!", heal_amount);
    }
    
    game->rooms_explored++;
}

// Main game loop
void game_loop(GameState* game) {
    printf("\n🏰  Welcome to the Dungeon of Destiny! 🏰\n");
    printf("A text RPG adventure with combat, leveling, and loot!\n");
    
    char player_name[MAX_NAME_LENGTH];
    printf("Enter your hero's name: ");
    fgets(player_name, MAX_NAME_LENGTH, stdin);
    player_name[strcspn(player_name, "\n")] = '\0';
    
    init_player(&game->player, player_name);
    
    while (!game->game_over) {
        display_player_status(&game->player);
        
        printf("\n🗺  What would you like to do?");
        printf("1. 🗺️  Explore Dungeon");
        printf("2. 📊  View Stats");
        printf("3. 🎒  Manage Inventory");
        printf("4. 🏪  Rest (Heal 20 HP)");
        printf("5. 🚪  Exit Game");
        printf("Choice: ");
        
        int choice;
        scanf("%d", &choice);
        getchar();
        
        switch(choice) {
            case 1:
                if (!game->in_combat) {
                    explore(game);
                } else {
                    printf("You're in combat! Fight or flee!\n");
                }
                break;
                
            case 2:
                printf("\n📊  HERO STATISTICS");
                printf("Enemies Defeated: %d", game->enemies_defeated);
                printf("Rooms Explored: %d", game->rooms_explored);
                printf("Current Level: %d", game->player.level);
                printf("Experience to Next Level: %d", (game->player.level * 100) - game->player.experience);
                break;
                
            case 3:
                printf("\n🎒  INVENTORY MANAGEMENT");
                for (int i = 0; i < game->player.inventory_count; i++) {
                    printf("%d. %s\n", i + 1, game->player.inventory[i]);
                }
                
                if (game->player.inventory_count > 0) {
                    printf("Use item? (1-%d, 0=No): ", game->player.inventory_count);
                    int item_choice;
                    scanf("%d", &item_choice);
                    getchar();
                    
                    if (item_choice > 0 && item_choice <= game->player.inventory_count) {
                        char* item = game->player.inventory[item_choice - 1];
                        
                        if (strstr(item, "Health Potion")) {
                            int heal = 30 + rand() % 20;
                            game->player.health = (game->player.health + heal < game->player.max_health) ? 
                                                  game->player.health + heal : game->player.max_health;
                            printf("You drink %s and restore %d HP!", item, heal);
                            
                            // Remove used item
                            for (int i = item_choice - 1; i < game->player.inventory_count - 1; i++) {
                                strcpy(game->player.inventory[i], game->player.inventory[i + 1]);
                            }
                            game->player.inventory_count--;
                        } else {
                            printf("You can't use %s right now.\n", item);
                        }
                    }
                }
                break;
                
            case 4:
                if (game->player.gold >= 10) {
                    game->player.gold -= 10;
                    int heal_amount = 20 + rand() % 10;
                    game->player.health = (game->player.health + heal_amount < game->player.max_health) ? 
                                        game->player.health + heal_amount : game->player.max_health;
                    printf("You rest at the inn and restore %d HP for 10 gold!", heal_amount);
                } else {
                    printf("You need 10 gold to rest at the inn!\n");
                }
                break;
                
            case 5:
                printf("Thanks for playing %s!\n", game->player.name);
                game->game_over = 1;
                break;
                
            default:
                printf("Invalid choice! Try again.\n");
        }
        
        // Check if in combat
        if (game->in_combat) {
            combat(game);
        }
    }
}

int main() {
    printf("🎮  TEXT RPG - LEVEL 3");
    printf("========================");
    printf("Learn game development, combat systems, and character progression!");
    printf("This is how real RPG games are programmed!\n");
    
    // Seed random number generator
    srand(time(NULL));
    
    // Initialize game state
    GameState game = {0};
    game.in_combat = 0;
    game.game_over = 0;
    game.enemies_defeated = 0;
    game.rooms_explored = 0;
    
    // Start the adventure!
    game_loop(&game);
    
    // Final score
    printf("\n" + "="*60);
    printf("🏆  GAME OVER - FINAL SCORES 🏆");
    printf("="*60);
    printf("Hero: %s", game.player.name);
    printf("Final Level: %d", game.player.level);
    printf("Enemies Defeated: %d", game.enemies_defeated);
    printf("Rooms Explored: %d", game.rooms_explored);
    printf("Gold Collected: %d", game.player.gold);
    printf("Experience Gained: %d", game.player.experience);
    
    // Calculate final score
    int final_score = (game.player.level * 1000) + 
                    (game.enemies_defeated * 100) + 
                    (game.rooms_explored * 50) + 
                    (game.player.gold / 10);
    
    printf("🏆  FINAL SCORE: %d 🏆", final_score);
    
    if (final_score > 5000) {
        printf("🌟  LEGENDARY HERO! The bards will sing of your deeds!");
    } else if (final_score > 2000) {
        printf("⭐  GREAT ADVENTURER! You've made your mark!");
    } else if (final_score > 500) {
        printf("👍  SOLID HERO! Keep training and return stronger!");
    } else {
        printf("💪  NOVICE HERO! Every legend starts somewhere!");
    }
    
    printf("\nYou've learned:");
    printf("- Character systems and stats");
    printf("- Combat mechanics and strategy");
    printf("- Random encounters and events");
    printf("- Item management and inventory");
    printf("- Level progression systems");
    printf("- Game state management");
    printf("- Text-based game design");
    
    return 0;
}
