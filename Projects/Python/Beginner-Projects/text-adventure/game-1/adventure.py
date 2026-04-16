"""
Text Adventure Game - Level 2: Game Logic and Storytelling
Learn game development, state management, and interactive storytelling
This is written like a human developer would write it - with personality!
"""

import random
import time
import sys

class TextAdventure:
    """A text-based adventure game with multiple rooms and puzzles"""
    
    def __init__(self):
        # Game state - this is where we track everything!
        self.current_room = "entrance"
        self.inventory = []
        self.game_over = False
        self.moves = 0
        self.health = 100
        self.score = 0
        
        # Room descriptions - make it feel real!
        self.rooms = {
            "entrance": {
                "description": "You stand at the entrance of a mysterious dungeon. The air is thick with ancient magic. Stone walls covered in glowing runes surround you. There's a wooden door to the north and a dark passage to the east.",
                "exits": {"north": "hallway", "east": "cave"},
                "items": ["torch"],
                "enemies": None,
                "visited": False
            },
            
            "hallway": {
                "description": "A long hallway stretches before you. The torch light flickers, revealing paintings of long-forgotten kings. You hear distant echoes. The hallway continues north, and you can go back south.",
                "exits": {"north": "throne_room", "south": "entrance"},
                "items": ["ancient_key"],
                "enemies": ["ghost"],
                "visited": False
            },
            
            "cave": {
                "description": "A damp cave with dripping water. Strange crystals glow blue on the walls. There's a narrow tunnel leading deeper into the darkness. You can go back west.",
                "exits": {"west": "entrance", "north": "treasure_room"},
                "items": ["crystal", "mysterious_potion"],
                "enemies": ["bat_swarm"],
                "visited": False
            },
            
            "throne_room": {
                "description": "The throne room! A massive stone throne sits on a raised platform. Gold coins are scattered across the floor. This must be the king's chamber! You can go back south.",
                "exits": {"south": "hallway"},
                "items": ["golden_crown", "treasure_chest"],
                "enemies": ["guardian"],
                "visited": False
            },
            
            "treasure_room": {
                "description": "You've found the treasure room! Piles of gold, jewels, and ancient artifacts fill the room. In the center sits a glowing orb of power. This is the ultimate prize! You can go back south.",
                "exits": {"south": "cave"},
                "items": ["orb_of_power", "diamond", "ruby"],
                "enemies": None,
                "visited": False
            }
        }
        
        # Enemy data - make combat interesting!
        self.enemies = {
            "ghost": {
                "health": 30,
                "damage": 10,
                "description": "A translucent ghost floats before you, its eyes burning with ancient hatred.",
                "loot": ["ectoplasm", "ghost_sword"],
                "defeat_message": "The ghost dissolves into mist with a final whisper..."
            },
            
            "bat_swarm": {
                "health": 40,
                "damage": 5,
                "description": "A swarm of bats fills the cave, their high-pitched squeaks echoing off the walls.",
                "loot": ["bat_wing", "guano"],
                "defeat_message": "The bats scatter into the darkness, leaving behind their treasures."
            },
            
            "guardian": {
                "health": 60,
                "damage": 15,
                "description": "A massive stone guardian stands before the throne, its eyes glowing with protective magic.",
                "loot": ["guardian_shield", "magic_scroll"],
                "defeat_message": "The guardian crumbles to dust, its duty finally complete."
            }
        }
        
        # Item effects - make items useful!
        self.item_effects = {
            "torch": {"type": "light", "effect": "Illuminates dark areas"},
            "ancient_key": {"type": "key", "effect": "Opens locked doors"},
            "crystal": {"type": "magic", "effect": "Glows with power"},
            "mysterious_potion": {"type": "heal", "effect": "Restores 50 health"},
            "golden_crown": {"type": "quest", "effect": "Symbol of royalty"},
            "treasure_chest": {"type": "container", "effect": "Contains gold coins"},
            "orb_of_power": {"type": "win", "effect": "Game victory item"},
            "diamond": {"type": "treasure", "effect": "Worth 1000 gold"},
            "ruby": {"type": "treasure", "effect": "Worth 500 gold"},
            "ectoplasm": {"type": "ingredient", "effect": "Magic potion ingredient"},
            "ghost_sword": {"type": "weapon", "effect": "Damage +20"},
            "bat_wing": {"type": "ingredient", "effect": "Potion ingredient"},
            "guano": {"type": "gross", "effect": "Fertilizer?"},
            "guardian_shield": {"type": "armor", "effect": "Defense +10"},
            "magic_scroll": {"type": "spell", "effect": "Learn new spell"}
        }
    
    def clear_screen(self):
        """Clear the terminal for better experience"""
        print('\n' * 50)
    
    def type_text(self, text, delay=0.03):
        """Type text like a human would - with delays!"""
        for char in text:
            print(char, end='', flush=True)
            time.sleep(delay)
        print()
    
    def get_room_description(self):
        """Get current room description with dynamic elements"""
        room = self.rooms[self.current_room]
        
        # Mark room as visited
        if not room["visited"]:
            room["visited"] = True
            self.score += 10  # Bonus for exploring!
        
        # Build description
        description = room["description"]
        
        # Add items in room
        if room["items"]:
            description += f"\n\nYou see: {', '.join(room['items'])}"
        
        # Add enemies in room
        if room["enemies"]:
            enemy_names = [self.enemies[e]["description"] for e in room["enemies"]]
            description += f"\n\n⚔️ DANGER: {', '.join(enemy_names)}"
        
        # Add exits
        exits = list(room["exits"].keys())
        description += f"\n\nExits: {', '.join(exits).upper()}"
        
        return description
    
    def show_status(self):
        """Display player status in a nice format"""
        print("=" * 50)
        print(f"📍 Location: {self.current_room.replace('_', ' ').title()}")
        print(f"❤️  Health: {self.health}/100")
        print(f"🎒 Inventory: {len(self.inventory)} items")
        print(f"⭐ Score: {self.score}")
        print(f"👟 Moves: {self.moves}")
        if self.inventory:
            print(f"📦 Items: {', '.join(self.inventory)}")
        print("=" * 50)
    
    def process_combat(self, enemy_name):
        """Handle combat with enemies"""
        enemy = self.enemies[enemy_name]
        
        self.type_text(f"\n⚔️ COMBAT WITH {enemy_name.upper().replace('_', ' ')}!", 0.05)
        self.type_text(enemy["description"], 0.03)
        print()
        
        player_damage = 15  # Base damage
        
        # Check for weapons
        for item in self.inventory:
            if "sword" in item:
                player_damage += 20
                self.type_text(f"Your {item} glows with power!", 0.03)
        
        # Combat loop
        while enemy["health"] > 0 and self.health > 0:
            print(f"\n❤️ Your Health: {self.health}")
            print(f"👹 {enemy_name.title()} Health: {enemy['health']}")
            print("\nChoose your action:")
            print("1. Attack")
            print("2. Use Item")
            print("3. Run Away")
            
            choice = input("What do you do? ").lower()
            
            if choice == "1" or choice == "attack":
                # Player attack
                damage = random.randint(player_damage - 5, player_damage + 5)
                enemy["health"] -= damage
                self.type_text(f"You strike for {damage} damage!", 0.02)
                
                if enemy["health"] > 0:
                    # Enemy attack
                    enemy_damage = random.randint(enemy["damage"] - 2, enemy["damage"] + 2)
                    self.health -= enemy_damage
                    self.type_text(f"{enemy_name.title()} attacks for {enemy_damage} damage!", 0.02)
            
            elif choice == "2" or choice == "use":
                self.use_item()
            
            elif choice == "3" or choice == "run":
                # 50% chance to escape
                if random.random() > 0.5:
                    self.type_text("You successfully run away!", 0.02)
                    return
                else:
                    self.type_text("You can't escape!", 0.02)
                    enemy_damage = random.randint(enemy["damage"] - 2, enemy["damage"] + 2)
                    self.health -= enemy_damage
                    self.type_text(f"{enemy_name.title()} attacks as you try to flee for {enemy_damage} damage!", 0.02)
            else:
                print("Invalid choice! You hesitate...")
                enemy_damage = random.randint(enemy["damage"] - 2, enemy["damage"] + 2)
                self.health -= enemy_damage
                self.type_text(f"{enemy_name.title()} attacks while you're confused for {enemy_damage} damage!", 0.02)
            
            self.moves += 1
        
        # Combat outcome
        if self.health <= 0:
            self.game_over = True
            self.type_text("\n💀 You have died! The dungeon claims another victim...", 0.05)
            self.type_text(f"Final Score: {self.score}", 0.03)
        
        elif enemy["health"] <= 0:
            self.type_text(f"\n🎉 Victory! {enemy_name.title()} is defeated!", 0.03)
            self.type_text(enemy["defeat_message"], 0.02)
            
            # Add loot to room
            room = self.rooms[self.current_room]
            room["items"].extend(enemy["loot"])
            room["enemies"].remove(enemy_name)
            
            # Score bonus
            self.score += 50
            self.type_text(f"+50 score! Total: {self.score}", 0.02)
    
    def use_item(self):
        """Use an item from inventory"""
        if not self.inventory:
            print("You have no items to use!")
            return
        
        print("\nYour items:")
        for i, item in enumerate(self.inventory, 1):
            effect = self.item_effects.get(item, {}).get("effect", "Unknown effect")
            print(f"{i}. {item} - {effect}")
        
        try:
            choice = int(input("Use which item? ")) - 1
            if 0 <= choice < len(self.inventory):
                item = self.inventory[choice]
                self.apply_item_effect(item)
            else:
                print("Invalid item number!")
        except ValueError:
            print("Invalid input!")
    
    def apply_item_effect(self, item):
        """Apply the effect of an item"""
        effect_data = self.item_effects.get(item, {})
        effect_type = effect_data.get("type", "unknown")
        
        if effect_type == "heal":
            heal_amount = 50
            self.health = min(self.health + heal_amount, 100)
            self.type_text(f"You drink the potion and restore {heal_amount} health!", 0.02)
            self.inventory.remove(item)
            self.type_text(f"Current health: {self.health}/100", 0.02)
        
        elif effect_type == "win":
            self.game_over = True
            self.score += 1000
            self.type_text("\n🏆 VICTORY! You've found the Orb of Power!", 0.05)
            self.type_text("The dungeon's magic surges through you!", 0.03)
            self.type_text("You are now the master of this realm!", 0.03)
            self.type_text(f"Final Score: {self.score}", 0.03)
        
        else:
            self.type_text(f"You use the {item}, but nothing special happens right now.", 0.02)
    
    def take_item(self, item_name):
        """Take an item from the current room"""
        room = self.rooms[self.current_room]
        
        if item_name in room["items"]:
            room["items"].remove(item_name)
            self.inventory.append(item_name)
            self.type_text(f"You take the {item_name}!", 0.02)
            self.score += 5
            self.type_text(f"+5 score! Total: {self.score}", 0.02)
        else:
            self.type_text(f"There's no {item_name} here.", 0.02)
    
    def move_to_room(self, direction):
        """Move to a different room"""
        room = self.rooms[self.current_room]
        
        if direction in room["exits"]:
            self.current_room = room["exits"][direction]
            self.moves += 1
            self.type_text(f"\nYou move {direction}...", 0.02)
            time.sleep(1)
        else:
            self.type_text("You can't go that way!", 0.02)
    
    def process_command(self, command):
        """Process player commands with natural language understanding"""
        command = command.lower().strip()
        
        # Movement commands
        if command in ["north", "n", "go north"]:
            self.move_to_room("north")
        
        elif command in ["south", "s", "go south"]:
            self.move_to_room("south")
        
        elif command in ["east", "e", "go east"]:
            self.move_to_room("east")
        
        elif command in ["west", "w", "go west"]:
            self.move_to_room("west")
        
        # Item commands
        elif command.startswith("take "):
            item_name = command[5:].strip()
            self.take_item(item_name)
        
        elif command.startswith("get "):
            item_name = command[4:].strip()
            self.take_item(item_name)
        
        elif command in ["inventory", "inv", "i"]:
            self.show_inventory()
        
        elif command.startswith("use "):
            item_name = command[4:].strip()
            if item_name in self.inventory:
                self.apply_item_effect(item_name)
            else:
                self.type_text(f"You don't have a {item_name}!", 0.02)
        
        # Game commands
        elif command in ["look", "l", "describe"]:
            self.type_text(self.get_room_description(), 0.01)
        
        elif command in ["help", "h", "?"]:
            self.show_help()
        
        elif command in ["quit", "exit", "q"]:
            self.game_over = True
            self.type_text("Thanks for playing!", 0.02)
        
        else:
            self.type_text("I don't understand that command. Type 'help' for assistance.", 0.02)
    
    def show_inventory(self):
        """Display player inventory"""
        if not self.inventory:
            self.type_text("Your inventory is empty.", 0.02)
        else:
            self.type_text("\n📦 Your Inventory:", 0.02)
            for item in self.inventory:
                effect = self.item_effects.get(item, {}).get("effect", "Unknown effect")
                self.type_text(f"  • {item} - {effect}", 0.01)
    
    def show_help(self):
        """Show game help"""
        self.type_text("\n📖 ADVENTURE HELP:", 0.02)
        self.type_text("Movement: north/south/east/west (or n/s/e/w)", 0.01)
        self.type_text("Items: take <item>, get <item>, use <item>", 0.01)
        self.type_text("Info: look, inventory (or inv), help", 0.01)
        self.type_text("Quit: quit (or exit, q)", 0.01)
        self.type_text("\n💡 Tip: Explore all rooms and find the Orb of Power!", 0.01)
    
    def check_combat(self):
        """Check if there are enemies in the current room"""
        room = self.rooms[self.current_room]
        return room["enemies"] is not None and len(room["enemies"]) > 0
    
    def play(self):
        """Main game loop"""
        self.clear_screen()
        
        # Epic intro!
        self.type_text("🏰 THE DUNGEON OF MYSTERIES 🏰", 0.05)
        self.type_text("=" * 50, 0.03)
        self.type_text("Legend tells of an ancient dungeon filled with treasure...", 0.02)
        self.type_text("Many have entered, but none have returned...", 0.02)
        self.type_text("Will you be the one to claim the Orb of Power?", 0.02)
        self.type_text("=" * 50, 0.03)
        
        input("\nPress Enter to begin your adventure...")
        
        # Main game loop
        while not self.game_over:
            self.clear_screen()
            self.show_status()
            
            # Check for combat first
            if self.check_combat():
                # Handle first enemy in room
                enemy_name = self.rooms[self.current_room]["enemies"][0]
                self.process_combat(enemy_name)
            else:
                # Normal exploration
                self.type_text(self.get_room_description(), 0.01)
                
                print("\n" + "-" * 50)
                command = input("What do you do? ")
                self.process_command(command)
            
            # Check health
            if self.health <= 0:
                self.game_over = True
        
        # Game over message
        if self.health <= 0:
            self.type_text("\n💀 GAME OVER - The dungeon has claimed another soul...", 0.05)
        elif "orb_of_power" in self.inventory:
            self.type_text("\n🏆 EPIC VICTORY - You are the new master of the dungeon!", 0.05)
        
        self.type_text(f"\n📊 Final Stats:", 0.02)
        self.type_text(f"   Score: {self.score}", 0.01)
        self.type_text(f"   Moves: {self.moves}", 0.01)
        self.type_text(f"   Rooms Explored: {sum(1 for room in self.rooms.values() if room['visited'])}", 0.01)
        self.type_text(f"   Items Collected: {len(self.inventory)}", 0.01)

def main():
    """Main function to run the game"""
    print("🎮 TEXT ADVENTURE GAME - LEVEL 2")
    print("=" * 50)
    print("Learn game development, state management, and storytelling!")
    print("This game is written with human-like code - with personality!")
    print("=" * 50)
    
    # Ask if player wants instructions
    want_instructions = input("\nDo you want to see the game story and instructions? (y/n): ").lower()
    
    if want_instructions == 'y':
        print("\n📖 THE STORY:")
        print("You are a brave adventurer seeking the legendary Orb of Power.")
        print("Ancient texts say it lies deep within the Dungeon of Mysteries.")
        print("Many have tried to claim it, but the dungeon's guardians")
        print("and deadly traps have defeated them all.")
        print("Will you succeed where others have failed?")
        print("\n🎯 YOUR GOAL:")
        print("Explore the dungeon, defeat enemies, collect items,")
        print("and find the Orb of Power to win the game!")
        print("\n💡 TIPS:")
        print("- Explore every room to find treasure")
        print("- Combat is dangerous, but rewarding")
        print("- Some items have special effects")
        print("- Manage your health carefully")
        print("\nPress Enter to start...")
        input()
    
    # Create and run game
    game = TextAdventure()
    game.play()
    
    # Ask to play again
    while True:
        play_again = input("\n🔄 Play again? (y/n): ").lower()
        if play_again != 'y':
            break
        game = TextAdventure()
        game.play()
    
    print("\nThanks for playing the Text Adventure!")
    print("You've learned:")
    print("- Game state management")
    print("- Object-oriented programming")
    print("- Command processing")
    print("- Combat systems")
    print("- Storytelling in code")

if __name__ == "__main__":
    main()
