/*
 * Web Scraper in Rust - Level 4: Network Programming and Data Extraction
 * 
 * Welcome to web programming in Rust! This is where safety meets the internet.
 * Learn HTTP requests, HTML parsing, and data extraction with Rust's safety guarantees.
 * 
 * Key concepts you'll learn:
 * - HTTP client programming with reqwest
 * - HTML parsing with scraper crate
 * - Error handling for network operations
 * - Data extraction and manipulation
 * - Async programming with tokio
 * - Safe string processing and validation
 * - Human-like code with detailed explanations!
 */

use std::collections::HashMap;
use scraper::{Html, Selector};
use serde::{Deserialize, Serialize};
use tokio;

// Web scraper structure
struct WebScraper {
    client: reqwest::Client,
    user_agent: String,
    request_count: u32,
    scraped_data: Vec<ScrapedPage>,
}

// Scraped page data structure
#[derive(Debug, Clone, Serialize, Deserialize)]
struct ScrapedPage {
    url: String,
    title: String,
    headings: Vec<Heading>,
    links: Vec<Link>,
    images: Vec<Image>,
    paragraphs: Vec<String>,
    meta_info: HashMap<String, String>,
    scraped_at: String,
}

// Heading structure
#[derive(Debug, Clone, Serialize, Deserialize)]
struct Heading {
    level: u8,
    text: String,
    id: Option<String>,
}

// Link structure
#[derive(Debug, Clone, Serialize, Deserialize)]
struct Link {
    url: String,
    text: String,
    title: Option<String>,
}

// Image structure
#[derive(Debug, Clone, Serialize, Deserialize)]
struct Image {
    src: String,
    alt: String,
    title: Option<String>,
}

impl WebScraper {
    // Create new web scraper
    fn new() -> Self {
        let client = reqwest::Client::builder()
            .user_agent("Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36")
            .timeout(std::time::Duration::from_secs(10))
            .build()
            .expect("Failed to create HTTP client");
        
        WebScraper {
            client,
            user_agent: "Rust Web Scraper 1.0".to_string(),
            request_count: 0,
            scraped_data: Vec::new(),
        }
    }
    
    // Fetch web page
    async fn fetch_page(&mut self, url: &str) -> Result<String, Box<dyn std::error::Error>> {
        println!("Fetching: {}", url);
        
        let response = self.client.get(url).send().await?;
        
        if !response.status().is_success() {
            return Err(format!("HTTP Error: {}", response.status()).into());
        }
        
        let html = response.text().await?;
        self.request_count += 1;
        
        println!("Success: Status {}, Size: {} bytes", response.status(), html.len());
        Ok(html)
    }
    
    // Parse HTML and extract data
    fn parse_html(&self, html: &str, url: &str) -> ScrapedPage {
        let document = Html::parse_document(html);
        
        // Extract title
        let title_selector = Selector::parse("title").unwrap();
        let title = document
            .select(&title_selector)
            .next()
            .map(|el| el.text().collect::<String>())
            .unwrap_or_else(|| "No title found".to_string());
        
        // Extract headings
        let headings = self.extract_headings(&document);
        
        // Extract links
        let links = self.extract_links(&document, url);
        
        // Extract images
        let images = self.extract_images(&document, url);
        
        // Extract paragraphs
        let paragraphs = self.extract_paragraphs(&document);
        
        // Extract meta information
        let meta_info = self.extract_meta_info(&document);
        
        ScrapedPage {
            url: url.to_string(),
            title,
            headings,
            links,
            images,
            paragraphs,
            meta_info,
            scraped_at: chrono::Utc::now().to_rfc3339(),
        }
    }
    
    // Extract headings
    fn extract_headings(&self, document: &Html) -> Vec<Heading> {
        let mut headings = Vec::new();
        
        for level in 1..=6 {
            let selector = Selector::parse(&format!("h{}", level)).unwrap();
            
            for element in document.select(&selector) {
                let text = element.text().collect::<String>();
                let id = element.value().attr("id").map(|s| s.to_string());
                
                headings.push(Heading {
                    level: level as u8,
                    text,
                    id,
                });
            }
        }
        
        headings
    }
    
    // Extract links
    fn extract_links(&self, document: &Html, base_url: &str) -> Vec<Link> {
        let selector = Selector::parse("a[href]").unwrap();
        let mut links = Vec::new();
        
        for element in document.select(&selector) {
            if let Some(href) = element.value().attr("href") {
                let text = element.text().collect::<String>();
                let title = element.value().attr("title").map(|s| s.to_string());
                
                // Convert relative URLs to absolute
                let url = if href.starts_with("http") {
                    href.to_string()
                } else if href.starts_with('/') {
                    let base = match base_url.split('/').next() {
                        Some(scheme_part) => {
                            match scheme_part.split(':').next() {
                                Some(scheme) => format!("{}:{}", scheme, base_url.split(':').nth(1).unwrap_or("")),
                                None => base_url.to_string(),
                            }
                        }
                        None => base_url.to_string(),
                    };
                    format!("{}{}", base, href)
                } else {
                    format!("{}/{}", base_url.trim_end_matches('/'), href)
                };
                
                links.push(Link {
                    url,
                    text,
                    title,
                });
            }
        }
        
        links
    }
    
    // Extract images
    fn extract_images(&self, document: &Html, base_url: &str) -> Vec<Image> {
        let selector = Selector::parse("img[src]").unwrap();
        let mut images = Vec::new();
        
        for element in document.select(&selector) {
            if let Some(src) = element.value().attr("src") {
                let alt = element.value().attr("alt").unwrap_or("").to_string();
                let title = element.value().attr("title").map(|s| s.to_string());
                
                // Convert relative URLs to absolute
                let src = if src.starts_with("http") {
                    src.to_string()
                } else if src.starts_with('/') {
                    let base = base_url.split('/').take(3).collect::<Vec<&str>>().join("/");
                    format!("{}{}", base, src)
                } else {
                    format!("{}/{}", base_url.trim_end_matches('/'), src)
                };
                
                images.push(Image {
                    src,
                    alt,
                    title,
                });
            }
        }
        
        images
    }
    
    // Extract paragraphs
    fn extract_paragraphs(&self, document: &Html) -> Vec<String> {
        let selector = Selector::parse("p").unwrap();
        let mut paragraphs = Vec::new();
        
        for element in document.select(&selector) {
            let text = element.text().collect::<String>();
            if text.len() > 20 { // Only meaningful paragraphs
                paragraphs.push(text);
            }
        }
        
        paragraphs
    }
    
    // Extract meta information
    fn extract_meta_info(&self, document: &Html) -> HashMap<String, String> {
        let mut meta_info = HashMap::new();
        
        // Extract meta tags
        let meta_selector = Selector::parse("meta").unwrap();
        for element in document.select(&meta_selector) {
            if let (Some(name), Some(content)) = (
                element.value().attr("name").or_else(|| element.value().attr("property")),
                element.value().attr("content")
            ) {
                meta_info.insert(name.to_string(), content.to_string());
            }
        }
        
        meta_info
    }
    
    // Scrape a single URL
    async fn scrape_url(&mut self, url: &str) -> Result<ScrapedPage, Box<dyn std::error::Error>> {
        println!("\n=== SCRAPING: {} ===", url);
        
        let html = self.fetch_page(url).await?;
        let scraped_page = self.parse_html(&html, url);
        
        // Display summary
        println!("Page Title: {}", scraped_page.title);
        println!("Headings: {}", scraped_page.headings.len());
        println!("Links: {}", scraped_page.links.len());
        println!("Images: {}", scraped_page.images.len());
        println!("Paragraphs: {}", scraped_page.paragraphs.len());
        println!("Meta tags: {}", scraped_page.meta_info.len());
        
        self.scraped_data.push(scraped_page.clone());
        
        Ok(scraped_page)
    }
    
    // Scrape multiple URLs
    async fn scrape_multiple_urls(&mut self, urls: &[&str]) -> Result<(), Box<dyn std::error::Error>> {
        println!("\n=== MULTI-URL SCRAPING ===");
        println!("Scraping {} URLs...", urls.len());
        
        for (i, url) in urls.iter().enumerate() {
            println!("\n--- URL {}/{} ---", i + 1, urls.len());
            
            match self.scrape_url(url).await {
                Ok(_) => println!("Successfully scraped: {}", url),
                Err(e) => println!("Error scraping {}: {}", url, e),
            }
            
            // Add delay to be respectful
            if i < urls.len() - 1 {
                tokio::time::sleep(tokio::time::Duration::from_millis(1000)).await;
            }
        }
        
        Ok(())
    }
    
    // Display scraped data summary
    fn display_summary(&self) {
        println!("\n" + "=".repeat(60));
        println!("    WEB SCRAPING SUMMARY");
        println!("=".repeat(60));
        println!("Total URLs scraped: {}", self.scraped_data.len());
        println!("Total HTTP requests: {}", self.request_count);
        
        let mut total_headings = 0;
        let mut total_links = 0;
        let mut total_images = 0;
        let mut total_paragraphs = 0;
        
        for page in &self.scraped_data {
            total_headings += page.headings.len();
            total_links += page.links.len();
            total_images += page.images.len();
            total_paragraphs += page.paragraphs.len();
        }
        
        println!("Total headings: {}", total_headings);
        println!("Total links: {}", total_links);
        println!("Total images: {}", total_images);
        println!("Total paragraphs: {}", total_paragraphs);
        
        // Display per-page details
        for (i, page) in self.scraped_data.iter().enumerate() {
            println!("\n--- Page {}: {} ---", i + 1, page.url);
            println!("Title: {}", page.title);
            println!("Headings: {} | Links: {} | Images: {} | Paragraphs: {}", 
                    page.headings.len(), page.links.len(), 
                    page.images.len(), page.paragraphs.len());
            
            // Show sample content
            if !page.headings.is_empty() {
                println!("Sample heading: {}", page.headings[0].text);
            }
            
            if !page.paragraphs.is_empty() {
                let sample = &page.paragraphs[0];
                let truncated = if sample.len() > 100 {
                    format!("{}...", &sample[..100])
                } else {
                    sample.clone()
                };
                println!("Sample paragraph: {}", truncated);
            }
        }
        
        println!("=".repeat(60));
    }
    
    // Save scraped data to JSON
    fn save_to_json(&self, filename: &str) -> Result<(), Box<dyn std::error::Error>> {
        let json = serde_json::to_string_pretty(&self.scraped_data)?;
        std::fs::write(filename, json)?;
        println!("Data saved to: {}", filename);
        Ok(())
    }
    
    // Search scraped data
    fn search_data(&self, query: &str) {
        println!("\n=== SEARCH RESULTS FOR '{}' ===", query);
        
        let mut found_pages = 0;
        
        for (i, page) in self.scraped_data.iter().enumerate() {
            let mut page_matches = false;
            
            // Search in title
            if page.title.to_lowercase().contains(&query.to_lowercase()) {
                println!("Page {}: Title match - {}", i + 1, page.title);
                page_matches = true;
            }
            
            // Search in headings
            for heading in &page.headings {
                if heading.text.to_lowercase().contains(&query.to_lowercase()) {
                    println!("Page {}: Heading match - H{}: {}", i + 1, heading.level, heading.text);
                    page_matches = true;
                }
            }
            
            // Search in paragraphs
            for paragraph in &page.paragraphs {
                if paragraph.to_lowercase().contains(&query.to_lowercase()) {
                    let truncated = if paragraph.len() > 150 {
                        format!("{}...", &paragraph[..150])
                    } else {
                        paragraph.clone()
                    };
                    println!("Page {}: Paragraph match - {}", i + 1, truncated);
                    page_matches = true;
                    break; // Show only first match per page
                }
            }
            
            if page_matches {
                found_pages += 1;
            }
        }
        
        if found_pages == 0 {
            println!("No matches found for '{}'", query);
        } else {
            println!("Found matches in {} pages", found_pages);
        }
    }
}

// Demo URLs for testing
fn get_demo_urls() -> Vec<&'static str> {
    vec![
        "https://httpbin.org/html",  // HTML testing site
        "https://example.com",       // Simple example site
        "https://www.rust-lang.org", // Rust official site
    ]
}

// Interactive menu
async fn interactive_mode() -> Result<(), Box<dyn std::error::Error>> {
    let mut scraper = WebScraper::new();
    
    loop {
        println!("\n=== RUST WEB SCRAPER ===");
        println!("1. Scrape single URL");
        println!("2. Scrape demo URLs");
        println!("3. View scraped data");
        println!("4. Search scraped data");
        println!("5. Save data to JSON");
        println!("6. Exit");
        
        println!("Enter choice (1-6): ");
        let mut input = String::new();
        std::io::stdin().read_line(&mut input)?;
        
        match input.trim() {
            "1" => {
                println!("Enter URL to scrape:");
                let mut url = String::new();
                std::io::stdin().read_line(&mut url)?;
                let url = url.trim();
                
                if !url.is_empty() {
                    match scraper.scrape_url(url).await {
                        Ok(_) => println!("Successfully scraped: {}", url),
                        Err(e) => println!("Error: {}", e),
                    }
                }
            }
            
            "2" => {
                let demo_urls = get_demo_urls();
                scraper.scrape_multiple_urls(&demo_urls).await?;
            }
            
            "3" => {
                scraper.display_summary();
            }
            
            "4" => {
                println!("Enter search query:");
                let mut query = String::new();
                std::io::stdin().read_line(&mut query)?;
                let query = query.trim();
                
                if !query.is_empty() {
                    scraper.search_data(query);
                }
            }
            
            "5" => {
                let filename = "scraped_data.json";
                scraper.save_to_json(filename)?;
            }
            
            "6" => {
                println!("Thanks for using Rust Web Scraper!");
                break;
            }
            
            _ => {
                println!("Invalid choice. Please enter 1-6.");
            }
        }
    }
    
    Ok(())
}

#[tokio::main]
async fn main() -> Result<(), Box<dyn std::error::Error>> {
    println!("========================================");
    println!("    RUST WEB SCRAPER - LEVEL 4");
    println!("========================================");
    println!("Welcome to web scraping in Rust!");
    println!("This program demonstrates:");
    println!("- Safe HTTP client programming");
    println!("- HTML parsing and data extraction");
    println!("- Async programming with tokio");
    println!("- Error handling for network operations");
    println!("- Data serialization with serde");
    println!("- Human-like code with personality!");
    println!("========================================");
    
    println!("Note: This scraper uses demo URLs for safe testing.");
    println!("Always respect robots.txt and website terms of service!");
    
    // Check if we want interactive mode
    println!("\nChoose mode:");
    println!("1. Interactive mode");
    println!("2. Demo mode (scrape demo URLs)");
    
    println!("Enter choice (1-2): ");
    let mut input = String::new();
    std::io::stdin().read_line(&mut input)?;
    
    match input.trim() {
        "1" => {
            interactive_mode().await?;
        }
        "2" => {
            let mut scraper = WebScraper::new();
            let demo_urls = get_demo_urls();
            
            println!("Running demo scrape...");
            scraper.scrape_multiple_urls(&demo_urls).await?;
            scraper.display_summary();
            
            // Save results
            scraper.save_to_json("demo_scraped_data.json")?;
            
            // Demo search
            println!("\nDemo search for 'Rust':");
            scraper.search_data("Rust");
        }
        _ => {
            println!("Invalid choice. Running demo mode...");
            let mut scraper = WebScraper::new();
            let demo_urls = get_demo_urls();
            scraper.scrape_multiple_urls(&demo_urls).await?;
            scraper.display_summary();
        }
    }
    
    println!("\nYou've learned:");
    println!("- HTTP client programming with reqwest");
    println!("- HTML parsing with scraper crate");
    println!("- Async programming with tokio");
    println!("- Error handling for network operations");
    println!("- Data serialization with serde");
    println!("- Safe string processing and validation");
    println!("- Human-readable, maintainable code!");
    
    println!("\nKey takeaways:");
    println!("- Rust ensures memory safety in network operations");
    println!("- Async programming prevents blocking operations");
    println!("- Error handling prevents crashes and data loss");
    println!("- Structured data makes processing reliable");
    println!("- Human-like code makes maintenance easier!");
    
    Ok(())
}
