# 🕸️ Web Scraper - Level 9 (HTML Parsing)
# Welcome to a new Intermediate Python project!
# When you look at a website, you see beautiful colors and text.
# But underneath, your browser sees raw "HTML" code.
# Web scraping is the act of using Python to automatically hunt through that HTML to steal data!

import requests
from bs4 import BeautifulSoup

def fetch_html(url):
    """Uses the 'requests' library to download the raw HTML of a website."""
    print(f"[*] Dispatching 'requests' to download HTML from: {url}")
    try:
        # We pretend to be a real browser using 'headers', otherwise some websites block us!
        headers = {'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64)'}
        response = requests.get(url, headers=headers)
        
        # 200 means OK! The server gave us the file.
        if response.status_code == 200:
            return response.text # This returns thousands of lines of messy HTML code
        else:
            print(f"[!] Server rejected us. Status code: {response.status_code}")
            return None
    except requests.exceptions.RequestException as e:
        print(f"[!] Network Error: {e}")
        return None

def main():
    print("========================================")
    print("      🕸️ BASIC HTML EXTRACTOR        ")
    print("========================================")
    
    # We will scrape a "dummy" sandbox website designed specifically for learning Web Scraping!
    target_url = "http://quotes.toscrape.com/"
    
    raw_html = fetch_html(target_url)
    if not raw_html:
        return

    print("\n[*] HTML Downloaded Successfully.")
    print("[*] Handing messy HTML over to 'BeautifulSoup4' to parse and structure it...\n")
    
    # --- ENTER BEAUTIFUL SOUP ---
    # We feed the raw chaotic string into BeautifulSoup. It magically turns it into a searchable Python object!
    soup = BeautifulSoup(raw_html, "html.parser")
    
    # On this specific website, quotes are located inside <span class="text"> tags!
    # So we tell BeautifulSoup: "Find EVERY single span tag that has the class 'text'."
    quotes = soup.find_all("span", class_="text")
    
    # The authors of the quotes are inside <small class="author"> tags!
    authors = soup.find_all("small", class_="author")
    
    print("--- 📚 SCRAPED QUOTES ---")
    # We use a loop to pair the exact quote with the exact author and print them cleanly!
    # 'zip()' allows us to loop through TWO lists at the exact same time.
    for quote_tag, author_tag in zip(quotes, authors):
        # We add .text to the end of the tag. 
        # This strips away the ugly <span class="text"> HTML part and just leaves the human words!
        clean_quote = quote_tag.text
        clean_author = author_tag.text
        
        print(f"🔹 {clean_quote}")
        print(f"   - {clean_author}\n")

if __name__ == "__main__":
    main()
