/*
 * Number Guessing Game in Rust - Level 2: Game Logic and Error Handling
 * 
 * Welcome to game development in Rust! This is where safety meets fun.
 * Learn Rust's ownership system and error handling through a classic game.
 * 
 * Key concepts you'll learn:
 * - Random number generation with external crates
 * - Input validation and error handling
 * - Pattern matching for game logic
 * - Loop control and user interaction
 * - String manipulation and parsing
 * - Human-like code with personality!
 */

use std::io::{self, Write};
use rand::Rng;

// Game structure to hold game state
struct GuessingGame {
    secret_number: u32,
    attempts: u32,
    max_attempts: u32,
    min_range: u32,
    max_range: u32,
    game_over: bool,
}

impl GuessingGame {
    // Create a new game
    fn new(min_range: u32, max_range: u32, max_attempts: u32) -> Self {
        let mut rng = rand::thread_rng();
        let secret = rng.gen_range(min_range..=max_range);
        
        GuessingGame {
            secret_number: secret,
            attempts: 0,
            max_attempts,
            min_range,
            max_range,
            game_over: false,
        }
    }
    
    // Process a guess
    fn process_guess(&mut self, guess: u32) -> GameResult {
        self.attempts += 1;
        
        println!("Attempt {}: You guessed {}", self.attempts, guess);
        
        if guess == self.secret_number {
            self.game_over = true;
            GameResult::Win
        } else if self.attempts >= self.max_attempts {
            self.game_over = true;
            GameResult::Lose(self.secret_number)
        } else if guess < self.secret_number {
            println!("Too low! Try a higher number.");
            let remaining = self.max_attempts - self.attempts;
            println!("Attempts remaining: {}", remaining);
            GameResult::TooLow
        } else {
            println!("Too high! Try a lower number.");
            let remaining = self.max_attempts - self.attempts;
            println!("Attempts remaining: {}", remaining);
            GameResult::TooHigh
        }
    }
    
    // Check if game is over
    fn is_game_over(&self) -> bool {
        self.game_over
    }
    
    // Get game statistics
    fn get_stats(&self) -> GameStats {
        GameStats {
            secret_number: self.secret_number,
            attempts: self.attempts,
            max_attempts: self.max_attempts,
            range: (self.min_range, self.max_range),
        }
    }
}

// Game result enumeration
#[derive(Debug)]
enum GameResult {
    Win,
    Lose(u32), // Secret number
    TooLow,
    TooHigh,
}

// Game statistics structure
#[derive(Debug)]
struct GameStats {
    secret_number: u32,
    attempts: u32,
    max_attempts: u32,
    range: (u32, u32),
}

// Input validation functions
fn get_valid_number(prompt: &str) -> Result<u32, String> {
    loop {
        print!("{}", prompt);
        io::stdout().flush().unwrap();
        
        let mut input = String::new();
        match io::stdin().read_line(&mut input) {
            Ok(_) => {
                match input.trim().parse::<u32>() {
                    Ok(num) => return Ok(num),
                    Err(_) => {
                        println!("Invalid input! Please enter a valid number.");
                        continue;
                    }
                }
            }
            Err(e) => return Err(format!("Failed to read input: {}", e)),
        }
    }
}

fn get_valid_range() -> Result<(u32, u32), String> {
    println!("Let's set up your game range!");
    
    let min = loop {
        match get_valid_number("Enter minimum number: ") {
            Ok(num) => break num,
            Err(e) => {
                println!("Error: {}", e);
                continue;
            }
        }
    };
    
    let max = loop {
        match get_valid_number("Enter maximum number: ") {
            Ok(num) => {
                if num <= min {
                    println!("Maximum must be greater than minimum ({})", min);
                    continue;
                }
                break num;
            }
            Err(e) => {
                println!("Error: {}", e);
                continue;
            }
        }
    };
    
    Ok((min, max))
}

fn get_valid_attempts() -> Result<u32, String> {
    loop {
        match get_valid_number("Enter maximum attempts (3-20): ") {
            Ok(attempts) => {
                if attempts < 3 || attempts > 20 {
                    println!("Attempts must be between 3 and 20!");
                    continue;
                }
                return Ok(attempts);
            }
            Err(e) => {
                println!("Error: {}", e);
                continue;
            }
        }
    }
}

// Display game introduction
fn display_intro() {
    println!("========================================");
    println!("    NUMBER GUESSING GAME - RUST");
    println!("========================================");
    println!("Welcome to the Rust Number Guessing Game!");
    println("This game demonstrates Rust's safety features:");
    println!("- Pattern matching for game logic");
    println!("- Error handling with Result types");
    println!("- Input validation and sanitization");
    println!("- Memory safety without garbage collection");
    println!("- Human-like code with personality!");
    println!("========================================");
}

// Display game rules
fn display_rules() {
    println!("\n=== GAME RULES ===");
    println!("1. I'll think of a number in your chosen range");
    println!("2. You have limited attempts to guess it");
    println!("3. I'll tell you if your guess is too high or too low");
    println!("4. Guess the number before you run out of attempts!");
    println!("5. Rust ensures no crashes or memory issues!");
    println!("==================");
}

// Play a single game
fn play_game() -> GameResult {
    println!("\n=== NEW GAME ===");
    
    // Get game configuration
    let (min, max) = match get_valid_range() {
        Ok(range) => range,
        Err(e) => {
            println!("Error setting range: {}", e);
            println!("Using default range 1-100");
            (1, 100)
        }
    };
    
    let max_attempts = match get_valid_attempts() {
        Ok(attempts) => attempts,
        Err(e) => {
            println!("Error setting attempts: {}", e);
            println!("Using default attempts 7");
            7
        }
    };
    
    println!("\nI'm thinking of a number between {} and {}!", min, max);
    println!("You have {} attempts to guess it!", max_attempts);
    println!("Good luck!");
    
    // Create and run game
    let mut game = GuessingGame::new(min, max, max_attempts);
    
    while !game.is_game_over() {
        let guess = match get_valid_number(&format!("Enter your guess ({}-{}): ", min, max)) {
            Ok(num) => {
                if num < min || num > max {
                    println!("Please enter a number between {} and {}!", min, max);
                    continue;
                }
                num
            }
            Err(e) => {
                println!("Error: {}", e);
                continue;
            }
        };
        
        let result = game.process_guess(guess);
        
        match result {
            GameResult::Win => {
                println!("\n" + "="*50);
                println!("    CONGRATULATIONS! YOU WON!");
                println!("="*50);
                println!("You guessed the number {} in {} attempts!", 
                        game.secret_number, game.attempts);
                
                // Performance rating
                let efficiency = (game.max_attempts - game.attempts + 1) as f64 / game.max_attempts as f64;
                let rating = match efficiency {
                    x if x >= 0.8 => "Excellent! You're a guessing master!",
                    x if x >= 0.6 => "Great job! Very impressive!",
                    x if x >= 0.4 => "Good work! Keep practicing!",
                    x if x >= 0.2 => "Not bad! Room for improvement!",
                    _ => "Better luck next time! Keep trying!",
                };
                
                println!("Performance: {}", rating);
                println!("="*50);
                
                return GameResult::Win;
            }
            GameResult::Lose(secret) => {
                println!("\n" + "="*50);
                println!("    GAME OVER! YOU LOST!");
                println!("="*50);
                println!("The secret number was: {}", secret);
                println!("You used all {} attempts.", game.attempts);
                println!("Don't give up! Try again!");
                println!("="*50);
                
                return GameResult::Lose(secret);
            }
            GameResult::TooLow | GameResult::TooHigh => {
                // Continue game
                continue;
            }
        }
    }
    
    GameResult::Lose(game.secret_number) // Fallback
}

// Display game statistics
fn display_stats(stats: &[GameStats]) {
    if stats.is_empty() {
        println!("No games played yet!");
        return;
    }
    
    println!("\n=== GAME STATISTICS ===");
    println!("Total games played: {}", stats.len());
    
    let total_attempts: u32 = stats.iter().map(|s| s.attempts).sum();
    let avg_attempts = total_attempts as f64 / stats.len() as f64;
    
    println!("Total attempts: {}", total_attempts);
    println!("Average attempts per game: {:.1}", avg_attempts);
    
    // Range statistics
    let mut min_ranges = Vec::new();
    let mut max_ranges = Vec::new();
    
    for stat in stats {
        min_ranges.push(stat.range.0);
        max_ranges.push(stat.range.1);
    }
    
    if !min_ranges.is_empty() {
        let avg_min = min_ranges.iter().sum::<u32>() as f64 / min_ranges.len() as f64;
        let avg_max = max_ranges.iter().sum::<u32>() as f64 / max_ranges.len() as f64;
        
        println!("Average range: {:.0} - {:.0}", avg_min, avg_max);
    }
    
    println!("==================");
}

// Main game loop
fn main() {
    display_intro();
    display_rules();
    
    let mut game_stats = Vec::new();
    let mut games_played = 0;
    let mut games_won = 0;
    
    loop {
        println!("\n=== MAIN MENU ===");
        println!("1. Play New Game");
        println!("2. View Statistics");
        println!("3. View Game Rules");
        println!("4. About This Game");
        println!("5. Exit");
        
        let choice = loop {
            match get_valid_number("Enter your choice (1-5): ") {
                Ok(num) => {
                    if num >= 1 && num <= 5 {
                        break num;
                    }
                    println!("Please enter a number between 1 and 5!");
                }
                Err(e) => {
                    println!("Error: {}", e);
                }
            }
        };
        
        match choice {
            1 => {
                let result = play_game();
                games_played += 1;
                
                match result {
                    GameResult::Win => {
                        games_won += 1;
                        println!("Games won: {} / {}", games_won, games_played);
                    }
                    GameResult::Lose(_) => {
                        println!("Games won: {} / {}", games_won, games_played);
                    }
                    _ => {}
                }
            }
            
            2 => {
                display_stats(&game_stats);
                
                if games_played > 0 {
                    let win_rate = (games_won as f64 / games_played as f64) * 100.0;
                    println!("Win rate: {:.1}%", win_rate);
                    
                    let rating = match win_rate {
                        x if x >= 80.0 => "Amazing! You're a guessing champion!",
                        x if x >= 60.0 => "Great! You're really good at this!",
                        x if x >= 40.0 => "Good! You're getting better!",
                        x if x >= 20.0 => "Fair! Keep practicing!",
                        _ => "Keep trying! Practice makes perfect!",
                    };
                    
                    println!("Skill rating: {}", rating);
                }
            }
            
            3 => {
                display_rules();
            }
            
            4 => {
                println!("\n=== ABOUT THIS GAME ===");
                println!("This Rust Number Guessing Game demonstrates:");
                println!("- Memory safety without garbage collection");
                println!("- Pattern matching for clean game logic");
                println!("- Error handling with Result types");
                println!("- Input validation and sanitization");
                println!("- Human-readable, maintainable code");
                println!("- Zero-cost abstractions");
                println!("");
                println!("Rust guarantees:");
                println!("- No null pointer exceptions");
                println!("- No data races");
                println!("- Memory safety at compile time");
                println!("- Thread safety by default");
                println!("");
                println!("This makes Rust perfect for:");
                println!("- Systems programming");
                println!("- Game development");
                println!("- Web applications");
                println!("- Embedded systems");
                println!("==================");
            }
            
            5 => {
                println!("\nThanks for playing the Rust Number Guessing Game!");
                println!("You've experienced safe and fun programming!");
                println!("Final stats:");
                println!("Games played: {}", games_played);
                println!("Games won: {}", games_won);
                
                if games_played > 0 {
                    let win_rate = (games_won as f64 / games_played as f64) * 100.0;
                    println!("Win rate: {:.1}%", win_rate);
                }
                
                println!("\nYou've learned:");
                println!("- Rust's ownership system");
                println!("- Pattern matching and error handling");
                println!("- Input validation and sanitization");
                println!("- Game state management");
                println!("- Human-like code with personality!");
                println!("- Safe systems programming!");
                
                break;
            }
            
            _ => {
                println!("Invalid choice!");
            }
        }
        
        // Add a small pause for better UX
        if choice != 5 {
            println!("\nPress Enter to continue...");
            let mut _input = String::new();
            io::stdin().read_line(&mut _input).unwrap();
        }
    }
}
