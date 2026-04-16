/*
 * Text Adventure Game - Level 2: Interactive Storytelling in C++
 * 
 * Welcome to game development in C++! This is where programming meets creativity.
 * Learn object-oriented programming through building a complete adventure game.
 * 
 * Key concepts you'll learn:
 * - Class inheritance and polymorphism
 * - Game state management
 * - Object composition and relationships
 * - Command parsing and execution
 * - File I/O for game data
 * - Random events and game mechanics
 * - Human-like code with personality!
 */

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <random>
#include <algorithm>
#include <memory>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

// Random number generator
random_device rd;
mt19937 gen(rd());

// Forward declarations
class Player;
class Room;
class Item;
class Enemy;

// Base class for all game objects
class GameObject {
protected:
    string name;
    string description;
    
public:
    GameObject(const string& name, const string& desc) : name(name), description(desc) {}
    virtual ~GameObject() = default;
    
    string getName() const { return name; }
    string getDescription() const { return description; }
    
    virtual void examine() const {
        cout << name << ": " << description << endl;
    }
    
    virtual string serialize() const = 0;
    virtual void deserialize(const string& data) = 0;
};

// Item class - things players can collect and use
class Item : public GameObject {
private:
    int value;
    string type;  // weapon, armor, potion, key, treasure
    bool usable;
    
public:
    Item(const string& name, const string& desc, const string& itemType, int val = 0, bool canUse = false)
        : GameObject(name, desc), value(val), type(itemType), usable(canUse) {}
    
    int getValue() const { return value; }
    string getType() const { return type; }
    bool isUsable() const { return usable; }
    
    void use(Player& player);
    
    void examine() const override {
        cout << "=== " << name << " ===" << endl;
        cout << description << endl;
        cout << "Type: " << type;
        if (value > 0) cout << " | Value: " << value;
        if (usable) cout << " | Usable: Yes";
        cout << endl;
    }
    
    string serialize() const override {
        return name + "|" + description + "|" + type + "|" + to_string(value) + "|" + to_string(usable);
    }
    
    void deserialize(const string& data) override {
        stringstream ss(data);
        string token;
        vector<string> parts;
        while (getline(ss, token, '|')) {
            parts.push_back(token);
        }
        if (parts.size() >= 5) {
            name = parts[0];
            description = parts[1];
            type = parts[2];
            value = stoi(parts[3]);
            usable = (parts[4] == "1");
        }
    }
};

// Enemy class - challenges for players to overcome
class Enemy : public GameObject {
private:
    int health;
    int maxHealth;
    int attack;
    int defense;
    int goldReward;
    int expReward;
    bool alive;
    
public:
    Enemy(const string& name, const string& desc, int hp, int atk, int def, int gold, int exp)
        : GameObject(name, desc), health(hp), maxHealth(hp), attack(atk), defense(def), 
          goldReward(gold), expReward(exp), alive(true) {}
    
    int getHealth() const { return health; }
    int getMaxHealth() const { return maxHealth; }
    int getAttack() const { return attack; }
    int getDefense() const { return defense; }
    int getGoldReward() const { return goldReward; }
    int getExpReward() const { return expReward; }
    bool isAlive() const { return alive; }
    
    void takeDamage(int damage) {
        int actualDamage = max(1, damage - defense);
        health -= actualDamage;
        cout << name << " takes " << actualDamage << " damage! Health: " << health << "/" << maxHealth << endl;
        
        if (health <= 0) {
            health = 0;
            alive = false;
            cout << name << " has been defeated!" << endl;
        }
    }
    
    void heal(int amount) {
        health = min(maxHealth, health + amount);
        cout << name << " heals for " << amount << "! Health: " << health << "/" << maxHealth << endl;
    }
    
    int attackPlayer() const {
        // Add some randomness to attacks
        uniform_int_distribution<> dis(attack - 2, attack + 2);
        return dis(gen);
    }
    
    void examine() const override {
        cout << "=== " << name << " ===" << endl;
        cout << description << endl;
        if (alive) {
            cout << "Health: " << health << "/" << maxHealth << endl;
            cout << "Attack: " << attack << " | Defense: " << defense << endl;
            cout << "Rewards: " << goldReward << " gold, " << expReward << " EXP" << endl;
        } else {
            cout << "Status: Defeated" << endl;
        }
    }
    
    string serialize() const override {
        return name + "|" + description + "|" + to_string(health) + "|" + to_string(maxHealth) + "|" +
               to_string(attack) + "|" + to_string(defense) + "|" + to_string(goldReward) + "|" +
               to_string(expReward) + "|" + to_string(alive);
    }
    
    void deserialize(const string& data) override {
        stringstream ss(data);
        string token;
        vector<string> parts;
        while (getline(ss, token, '|')) {
            parts.push_back(token);
        }
        if (parts.size() >= 9) {
            name = parts[0];
            description = parts[1];
            health = stoi(parts[2]);
            maxHealth = stoi(parts[3]);
            attack = stoi(parts[4]);
            defense = stoi(parts[5]);
            goldReward = stoi(parts[6]);
            expReward = stoi(parts[7]);
            alive = (parts[8] == "1");
        }
    }
};

// Room class - locations in the game world
class Room : public GameObject {
private:
    map<string, shared_ptr<Room>> exits;
    vector<shared_ptr<Item>> items;
    vector<shared_ptr<Enemy>> enemies;
    bool visited;
    
public:
    Room(const string& name, const string& desc) : GameObject(name, desc), visited(false) {}
    
    void addExit(const string& direction, shared_ptr<Room> room) {
        exits[direction] = room;
        // Add reciprocal exit
        string opposite;
        if (direction == "north") opposite = "south";
        else if (direction == "south") opposite = "north";
        else if (direction == "east") opposite = "west";
        else if (direction == "west") opposite = "east";
        else opposite = direction;
        
        room->exits[opposite] = shared_from_this();
    }
    
    void addItem(shared_ptr<Item> item) {
        items.push_back(item);
    }
    
    void addEnemy(shared_ptr<Enemy> enemy) {
        enemies.push_back(enemy);
    }
    
    shared_ptr<Room> getExit(const string& direction) {
        if (exits.find(direction) != exits.end()) {
            return exits[direction];
        }
        return nullptr;
    }
    
    vector<string> getExitDirections() const {
        vector<string> directions;
        for (const auto& exit : exits) {
            directions.push_back(exit.first);
        }
        return directions;
    }
    
    shared_ptr<Item> getItem(const string& itemName) {
        for (auto it = items.begin(); it != items.end(); ++it) {
            if ((*it)->getName() == itemName) {
                shared_ptr<Item> item = *it;
                items.erase(it);
                return item;
            }
        }
        return nullptr;
    }
    
    vector<shared_ptr<Enemy>>& getEnemies() { return enemies; }
    
    void markVisited() { visited = true; }
    bool isVisited() const { return visited; }
    
    void describe() const {
        cout << "\n=== " << name << " ===" << endl;
        cout << description << endl;
        
        if (!visited) {
            cout << "\nYou see for the first time:" << endl;
        }
        
        // Show exits
        if (!exits.empty()) {
            cout << "\nExits: ";
            for (const auto& exit : exits) {
                cout << exit.first << " ";
            }
            cout << endl;
        }
        
        // Show items
        if (!items.empty()) {
            cout << "\nItems here:" << endl;
            for (const auto& item : items) {
                cout << "- " << item->getName() << endl;
            }
        }
        
        // Show enemies
        vector<shared_ptr<Enemy>> aliveEnemies;
        for (const auto& enemy : enemies) {
            if (enemy->isAlive()) {
                aliveEnemies.push_back(enemy);
            }
        }
        
        if (!aliveEnemies.empty()) {
            cout << "\nDANGER! Enemies here:" << endl;
            for (const auto& enemy : aliveEnemies) {
                cout << "- " << enemy->getName() << endl;
            }
        }
        
        cout << endl;
    }
    
    string serialize() const override {
        string data = name + "|" + description + "|" + to_string(visited) + "|";
        // Add items, enemies, exits data here in a real implementation
        return data;
    }
    
    void deserialize(const string& data) override {
        stringstream ss(data);
        string token;
        vector<string> parts;
        while (getline(ss, token, '|')) {
            parts.push_back(token);
        }
        if (parts.size() >= 3) {
            name = parts[0];
            description = parts[1];
            visited = (parts[2] == "1");
        }
    }
};

// Player class - the hero of our story
class Player {
private:
    string name;
    int health;
    int maxHealth;
    int attack;
    int defense;
    int level;
    int experience;
    int gold;
    vector<shared_ptr<Item>> inventory;
    shared_ptr<Room> currentRoom;
    
public:
    Player(const string& playerName) : name(playerName), health(100), maxHealth(100), 
                                      attack(15), defense(5), level(1), experience(0), gold(50) {}
    
    // Getters
    string getName() const { return name; }
    int getHealth() const { return health; }
    int getMaxHealth() const { return maxHealth; }
    int getAttack() const { return attack; }
    int getDefense() const { return defense; }
    int getLevel() const { return level; }
    int getExperience() const { return experience; }
    int getGold() const { return gold; }
    shared_ptr<Room> getCurrentRoom() const { return currentRoom; }
    
    // Setters
    void setCurrentRoom(shared_ptr<Room> room) { currentRoom = room; }
    
    // Combat methods
    void takeDamage(int damage) {
        int actualDamage = max(1, damage - defense);
        health -= actualDamage;
        cout << name << " takes " << actualDamage << " damage! Health: " << health << "/" << maxHealth << endl;
        
        if (health <= 0) {
            health = 0;
            cout << name << " has been defeated!" << endl;
        }
    }
    
    void heal(int amount) {
        health = min(maxHealth, health + amount);
        cout << name << " heals for " << amount << "! Health: " << health << "/" << maxHealth << endl;
    }
    
    int attackEnemy() const {
        uniform_int_distribution<> dis(attack - 3, attack + 3);
        return dis(gen);
    }
    
    // Experience and leveling
    void gainExperience(int exp) {
        experience += exp;
        cout << name << " gains " << exp << " experience!" << endl;
        
        // Check for level up
        int expNeeded = level * 100;
        if (experience >= expNeeded) {
            levelUp();
        }
    }
    
    void levelUp() {
        level++;
        maxHealth += 20;
        health = maxHealth;
        attack += 5;
        defense += 2;
        
        cout << "\n" << string(50, '!') << endl;
        cout << "LEVEL UP! " << name << " is now level " << level << "!" << endl;
        cout << "Health: " << health << "/" << maxHealth << endl;
        cout << "Attack: " << attack << " | Defense: " << defense << endl;
        cout << string(50, '!') << endl;
    }
    
    // Inventory management
    void addItem(shared_ptr<Item> item) {
        inventory.push_back(item);
        cout << name << " picks up " << item->getName() << endl;
    }
    
    bool hasItem(const string& itemName) const {
        for (const auto& item : inventory) {
            if (item->getName() == itemName) {
                return true;
            }
        }
        return false;
    }
    
    shared_ptr<Item> getItem(const string& itemName) {
        for (auto it = inventory.begin(); it != inventory.end(); ++it) {
            if ((*it)->getName() == itemName) {
                shared_ptr<Item> item = *it;
                inventory.erase(it);
                return item;
            }
        }
        return nullptr;
    }
    
    void showInventory() const {
        cout << "\n=== " << name << "'s Inventory ===" << endl;
        if (inventory.empty()) {
            cout << "Your inventory is empty." << endl;
        } else {
            for (const auto& item : inventory) {
                cout << "- " << item->getName();
                if (item->getValue() > 0) {
                    cout << " (Value: " << item->getValue() << ")";
                }
                cout << endl;
            }
        }
        cout << "Gold: " << gold << endl;
        cout << "========================" << endl;
    }
    
    // Gold management
    void addGold(int amount) {
        gold += amount;
        cout << name << " gains " << amount << " gold! Total: " << gold << endl;
    }
    
    bool spendGold(int amount) {
        if (gold >= amount) {
            gold -= amount;
            cout << name << " spends " << amount << " gold. Remaining: " << gold << endl;
            return true;
        }
        cout << "Not enough gold! Need " << amount << ", have " << gold << endl;
        return false;
    }
    
    // Status display
    void showStatus() const {
        cout << "\n=== " << name << "'s Status ===" << endl;
        cout << "Level: " << level << " | EXP: " << experience << "/" << (level * 100) << endl;
        cout << "Health: " << health << "/" << maxHealth << endl;
        cout << "Attack: " << attack << " | Defense: " << defense << endl;
        cout << "Gold: " << gold << " | Items: " << inventory.size() << endl;
        cout << "=====================" << endl;
    }
};

// Game class - manages the entire game
class Game {
private:
    shared_ptr<Player> player;
    map<string, shared_ptr<Room>> rooms;
    bool running;
    int moves;
    
public:
    Game() : running(false), moves(0) {}
    
    void initialize() {
        cout << "Welcome to the C++ Text Adventure!" << endl;
        cout << "A journey of mystery, treasure, and danger awaits!" << endl;
        
        string playerName;
        cout << "\nEnter your hero's name: ";
        getline(cin, playerName);
        
        player = make_shared<Player>(playerName);
        createWorld();
        running = true;
        
        cout << "\nWelcome, " << player->getName() << "! Your adventure begins..." << endl;
        cout << "Type 'help' for commands, or start exploring!" << endl;
    }
    
    void createWorld() {
        // Create rooms
        auto entrance = make_shared<Room>("Entrance", 
            "You stand at the entrance of a mysterious dungeon. Stone walls covered in ancient runes surround you.");
        auto hallway = make_shared<Room>("Hallway", 
            "A long hallway stretches before you. The air is thick with the scent of old stone and mystery.");
        auto treasureRoom = make_shared<Room>("Treasure Room", 
            "Gold coins and jewels sparkle in the torchlight. This must be the legendary treasure room!");
        auto dragonLair = make_shared<Room>("Dragon's Lair", 
            "A massive cavern with a sleeping dragon. Piles of gold surround the beast. This is incredibly dangerous!");
        auto garden = make_shared<Room>("Garden", 
            "A beautiful underground garden with glowing mushrooms and exotic plants. The air is fresh here.");
        auto library = make_shared<Room>("Library", 
            "Ancient books line the walls. Some contain powerful knowledge, others hold dark secrets.");
        auto armory = make_shared<Room>("Armory", 
            "Weapons and armor of all kinds hang on the walls. A blacksmith's forge still glows in the corner.");
        auto crypt = make_shared<Room>("Crypt", 
            "An ancient burial chamber. Stone sarcophagi line the walls, and strange whispers echo in the darkness.");
        
        // Connect rooms
        entrance->addExit("north", hallway);
        hallway->addExit("east", treasureRoom);
        hallway->addExit("west", garden);
        hallway->addExit("north", library);
        hallway->addExit("south", entrance);
        treasureRoom->addExit("north", dragonLair);
        dragonLair->addExit("south", treasureRoom);
        garden->addExit("north", armory);
        armory->addExit("south", garden);
        library->addExit("west", crypt);
        crypt->addExit("east", library);
        
        // Add items
        entrance->addItem(make_shared<Item>("Torch", "A wooden torch that provides light.", "tool", 5));
        entrance->addItem(make_shared<Item>("Map", "A fragment of a dungeon map.", "document", 10));
        
        hallway->addItem(make_shared<Item>("Ancient Key", "A rusty key that might open something important.", "key", 20));
        
        treasureRoom->addItem(make_shared<Item>("Gold Coins", "A pouch of shiny gold coins.", "treasure", 100));
        treasureRoom->addItem(make_shared<Item>("Diamond", "A perfectly cut diamond that sparkles brilliantly.", "treasure", 500));
        
        garden->addItem(make_shared<Item>("Healing Potion", "A glowing red liquid that restores health.", "potion", 30, true));
        garden->addItem(make_shared<Item>("Magic Mushroom", "A strange mushroom with magical properties.", "food", 15, true));
        
        library->addItem(make_shared<Item>("Spellbook", "An ancient book filled with powerful spells.", "document", 100));
        library->addItem(make_shared<Item>("Scroll of Wisdom", "A scroll containing ancient knowledge.", "document", 50));
        
        armory->addItem(make_shared<Item>("Iron Sword", "A well-crafted iron sword.", "weapon", 50));
        armory->addItem(make_shared<Item>("Leather Armor", "Sturdy leather armor that provides protection.", "armor", 40));
        
        crypt->addItem(make_shared<Item>("Ancient Artifact", "A mysterious artifact that pulses with energy.", "treasure", 1000));
        
        // Add enemies
        hallway->addEnemy(make_shared<Enemy>("Goblin", "A nasty green creature with rusty armor.", 30, 8, 2, 20, 25));
        treasureRoom->addEnemy(make_shared<Enemy>("Treasure Guardian", "A stone automaton that protects the treasure.", 50, 12, 5, 40, 50));
        garden->addEnemy(make_shared<Enemy>("Giant Spider", "A huge spider with venomous fangs.", 25, 10, 3, 15, 20));
        library->addEnemy(make_shared<Enemy>("Ghost", "A translucent spirit that guards the ancient knowledge.", 35, 15, 4, 30, 40));
        armory->addEnemy(make_shared<Enemy>("Armor Golem", "A living suit of armor that attacks intruders.", 60, 18, 8, 60, 80));
        crypt->addEnemy(make_shared<Enemy>("Lich", "An undead sorcerer of immense power.", 80, 25, 10, 100, 150));
        dragonLair->addEnemy(make_shared<Enemy>("Ancient Dragon", "A massive dragon with scales like rubies and fire in its breath.", 200, 35, 15, 500, 500));
        
        // Store rooms
        rooms["entrance"] = entrance;
        rooms["hallway"] = hallway;
        rooms["treasure"] = treasureRoom;
        rooms["dragon"] = dragonLair;
        rooms["garden"] = garden;
        rooms["library"] = library;
        rooms["armory"] = armory;
        rooms["crypt"] = crypt;
        
        // Set starting position
        player->setCurrentRoom(entrance);
    }
    
    void run() {
        while (running) {
            // Show current room
            auto currentRoom = player->getCurrentRoom();
            currentRoom->describe();
            currentRoom->markVisited();
            
            // Check for combat
            handleCombat();
            
            if (!running) break;
            
            // Get player command
            cout << "\nWhat would you like to do? ";
            string command;
            getline(cin, command);
            
            // Process command
            processCommand(command);
            moves++;
        }
    }
    
    void handleCombat() {
        auto currentRoom = player->getCurrentRoom();
        vector<shared_ptr<Enemy>>& enemies = currentRoom->getEnemies();
        
        // Find alive enemies
        vector<shared_ptr<Enemy>> aliveEnemies;
        for (const auto& enemy : enemies) {
            if (enemy->isAlive()) {
                aliveEnemies.push_back(enemy);
            }
        }
        
        if (aliveEnemies.empty()) return;
        
        cout << "\n" << string(40, '!') << endl;
        cout << "COMBAT BEGINS!" << endl;
        cout << string(40, '!') << endl;
        
        // Combat loop
        while (!aliveEnemies.empty() && player->getHealth() > 0) {
            // Show combat status
            cout << "\nYour Health: " << player->getHealth() << "/" << player->getMaxHealth() << endl;
            cout << "Enemies: " << aliveEnemies.size() << endl;
            
            for (size_t i = 0; i < aliveEnemies.size(); i++) {
                cout << (i + 1) << ". " << aliveEnemies[i]->getName() 
                     << " (HP: " << aliveEnemies[i]->getHealth() << "/" << aliveEnemies[i]->getMaxHealth() << ")" << endl;
            }
            
            cout << "\nCombat actions:" << endl;
            cout << "1. Attack enemy" << endl;
            cout << "2. Use item" << endl;
            cout << "3. Try to flee" << endl;
            cout << "4. Show status" << endl;
            cout << "Choice: ";
            
            string choice;
            getline(cin, choice);
            
            if (choice == "1") {
                // Attack
                cout << "Attack which enemy? (1-" << aliveEnemies.size() << "): ";
                string enemyChoice;
                getline(cin, enemyChoice);
                
                try {
                    int enemyIndex = stoi(enemyChoice) - 1;
                    if (enemyIndex >= 0 && enemyIndex < aliveEnemies.size()) {
                        auto enemy = aliveEnemies[enemyIndex];
                        
                        // Player attacks
                        int damage = player->attackEnemy();
                        enemy->takeDamage(damage);
                        
                        if (!enemy->isAlive()) {
                            // Enemy defeated
                            player->gainExperience(enemy->getExpReward());
                            player->addGold(enemy->getGoldReward());
                            
                            // Remove from alive enemies
                            aliveEnemies.erase(aliveEnemies.begin() + enemyIndex);
                            
                            cout << "Victory! You defeated " << enemy->getName() << "!" << endl;
                        } else {
                            // Enemy counter-attacks
                            int enemyDamage = enemy->attackPlayer();
                            player->takeDamage(enemyDamage);
                        }
                    } else {
                        cout << "Invalid enemy selection!" << endl;
                    }
                } catch (...) {
                    cout << "Invalid input!" << endl;
                }
                
            } else if (choice == "2") {
                // Use item
                player->showInventory();
                cout << "Use which item? (or 'back'): ";
                string itemChoice;
                getline(cin, itemChoice);
                
                if (itemChoice != "back") {
                    auto item = player->getItem(itemChoice);
                    if (item && item->isUsable()) {
                        if (item->getType() == "potion") {
                            player->heal(30);
                            cout << "You drink the potion and feel better!" << endl;
                        } else if (item->getType() == "food") {
                            player->heal(15);
                            cout << "You eat the " << item->getName() << " and feel nourished!" << endl;
                        }
                    } else if (item) {
                        cout << "You can't use " << item->getName() << " in combat!" << endl;
                        player->addItem(item); // Put it back
                    } else {
                        cout << "You don't have that item!" << endl;
                    }
                }
                
            } else if (choice == "3") {
                // Flee
                uniform_int_distribution<> dis(1, 3);
                int fleeRoll = dis(gen);
                
                if (fleeRoll == 1) {
                    cout << "You successfully flee from combat!" << endl;
                    return;
                } else {
                    cout << "You can't escape!" << endl;
                    // All enemies attack
                    for (const auto& enemy : aliveEnemies) {
                        int damage = enemy->attackPlayer();
                        player->takeDamage(damage);
                    }
                }
                
            } else if (choice == "4") {
                player->showStatus();
            } else {
                cout << "Invalid choice!" << endl;
            }
            
            if (player->getHealth() <= 0) {
                cout << "\nYou have been defeated! Game Over." << endl;
                running = false;
                return;
            }
        }
        
        if (aliveEnemies.empty()) {
            cout << "\nAll enemies defeated! The room is safe now." << endl;
        }
    }
    
    void processCommand(const string& command) {
        if (command.empty()) return;
        
        // Parse command
        istringstream iss(command);
        vector<string> parts;
        string part;
        while (iss >> part) {
            parts.push_back(part);
        }
        
        string action = parts[0];
        
        if (action == "help") {
            showHelp();
        } else if (action == "look") {
            player->getCurrentRoom()->describe();
        } else if (action == "go" || action == "move") {
            if (parts.size() < 2) {
                cout << "Go where? (north, south, east, west)" << endl;
                return;
            }
            move(parts[1]);
        } else if (action == "take" || action == "get") {
            if (parts.size() < 2) {
                cout << "Take what?" << endl;
                return;
            }
            takeItem(parts[1]);
        } else if (action == "use") {
            if (parts.size() < 2) {
                cout << "Use what?" << endl;
                return;
            }
            useItem(parts[1]);
        } else if (action == "inventory" || action == "inv") {
            player->showInventory();
        } else if (action == "status") {
            player->showStatus();
        } else if (action == "examine") {
            if (parts.size() < 2) {
                cout << "Examine what?" << endl;
                return;
            }
            examine(parts[1]);
        } else if (action == "quit" || action == "exit") {
            cout << "Thanks for playing!" << endl;
            running = false;
        } else {
            // Try to move directly
            if (command == "north" || command == "south" || command == "east" || command == "west") {
                move(command);
            } else {
                cout << "Unknown command. Type 'help' for assistance." << endl;
            }
        }
    }
    
    void move(const string& direction) {
        auto currentRoom = player->getCurrentRoom();
        auto nextRoom = currentRoom->getExit(direction);
        
        if (nextRoom) {
            player->setCurrentRoom(nextRoom);
            cout << "You move " << direction << "..." << endl;
        } else {
            cout << "You can't go " << direction << " from here." << endl;
        }
    }
    
    void takeItem(const string& itemName) {
        auto currentRoom = player->getCurrentRoom();
        auto item = currentRoom->getItem(itemName);
        
        if (item) {
            player->addItem(item);
            cout << "You take the " << item->getName() << "." << endl;
        } else {
            cout << "There's no " << itemName << " here." << endl;
        }
    }
    
    void useItem(const string& itemName) {
        auto item = player->getItem(itemName);
        
        if (item) {
            if (item->isUsable()) {
                if (item->getType() == "potion") {
                    player->heal(30);
                    cout << "You drink the potion and restore 30 health!" << endl;
                } else if (item->getType() == "food") {
                    player->heal(15);
                    cout << "You eat the " << item->getName() << " and restore 15 health!" << endl;
                } else {
                    cout << "You use the " << item->getName() << "." << endl;
                }
            } else {
                cout << "You can't use " << item->getName() << " right now." << endl;
                player->addItem(item); // Put it back
            }
        } else {
            cout << "You don't have a " << itemName << "." << endl;
        }
    }
    
    void examine(const string& target) {
        auto currentRoom = player->getCurrentRoom();
        
        // Check items in room
        auto item = currentRoom->getItem(target);
        if (item) {
            item->examine();
            currentRoom->addItem(item); // Put it back
            return;
        }
        
        // Check enemies in room
        for (const auto& enemy : currentRoom->getEnemies()) {
            if (enemy->getName() == target) {
                enemy->examine();
                return;
            }
        }
        
        // Check player inventory
        if (player->hasItem(target)) {
            auto invItem = player->getItem(target);
            invItem->examine();
            player->addItem(invItem); // Put it back
            return;
        }
        
        cout << "There's no " << target << " here to examine." << endl;
    }
    
    void showHelp() const {
        cout << "\n=== TEXT ADVENTURE HELP ===" << endl;
        cout << "MOVEMENT:" << endl;
        cout << "  go <direction>  - Move north/south/east/west" << endl;
        cout << "  <direction>     - Quick move (just type 'north')" << endl;
        cout << "\nITEMS:" << endl;
        cout << "  take <item>     - Pick up an item" << endl;
        cout << "  use <item>      - Use an item" << endl;
        cout << "  inventory/inv   - Show your items" << endl;
        cout << "\nINFORMATION:" << endl;
        cout << "  look            - Look around current room" << endl;
        cout << "  examine <thing> - Examine an item, enemy, or object" << endl;
        cout << "  status          - Show your character status" << endl;
        cout << "\nOTHER:" << endl;
        cout << "  help            - Show this help" << endl;
        cout << "  quit/exit       - Exit the game" << endl;
        cout << "\nTIPS:" << endl;
        cout << "- Explore rooms to find treasure and items" << endl;
        cout << "- Combat is dangerous but rewarding" << endl;
        cout << "- Some items can be used to heal in combat" << endl;
        cout << "- Level up by gaining experience" << endl;
        cout << "- Find the ancient artifact to win!" << endl;
        cout << "=========================" << endl;
    }
    
    void showGameOver() const {
        cout << "\n" + string(60, '=') << endl;
        cout << "           GAME OVER" << endl;
        cout << string(60, '=') << endl;
        cout << "Hero: " << player->getName() << endl;
        cout << "Final Level: " << player->getLevel() << endl;
        cout << "Moves Made: " << moves << endl;
        cout << "Gold Collected: " << player->getGold() << endl;
        cout << "Experience Gained: " << player->getExperience() << endl;
        cout << "Items Collected: " << player->showInventory() << endl;
        
        // Calculate score
        int score = (player->getLevel() * 1000) + 
                   (player->getGold() / 10) + 
                   (player->getExperience() / 5) +
                   (moves * 2);
        
        cout << "\nFINAL SCORE: " << score << endl;
        
        if (score > 5000) {
            cout << "LEGENDARY HERO! Your story will be told for generations!" << endl;
        } else if (score > 2000) {
            cout << "GREAT ADVENTURER! You've made your mark on the dungeon!" << endl;
        } else if (score > 1000) {
            cout << "BRAVE EXPLORER! You've faced the dangers and survived!" << endl;
        } else {
            cout << "NOVICE ADVENTURER! Every hero starts somewhere!" << endl;
        }
        
        cout << string(60, '=') << endl;
    }
};

int main() {
    cout << "========================================" << endl;
    cout << "    C++ TEXT ADVENTURE GAME - LEVEL 2" << endl;
    cout << "========================================" << endl;
    cout << "Learn object-oriented programming through adventure!" << endl;
    cout << "This game demonstrates advanced C++ concepts:" << endl;
    cout << "- Class inheritance and polymorphism" << endl;
    cout << "- Smart pointers and memory management" << endl;
    cout << "- STL containers and algorithms" << endl;
    cout << "- Game state management" << endl;
    cout << "- Command parsing and execution" << endl;
    cout << "- Human-like code with personality!" << endl;
    cout << "========================================" << endl;
    
    Game game;
    game.initialize();
    game.run();
    game.showGameOver();
    
    cout << "\nYou've learned:" << endl;
    cout << "- Object-oriented programming principles" << endl;
    cout << "- Class design and relationships" << endl;
    cout << "- Memory management with smart pointers" << endl;
    cout << "- Game development patterns" << endl;
    cout << "- Command parsing and state management" << endl;
    cout << "- Random events and game mechanics" << endl;
    cout << "- Human-readable, maintainable code!" << endl;
    
    return 0;
}
