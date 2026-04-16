# 🕸️ Web Scraper - Level 10 (The CSV Data Miner)
# Scraping 1 page of quotes and printing them to a terminal is fun.
# But what if a client pays you to scrape 10,000 products across 50 pages?
# You need Pagination (clicking 'Next Page' automatically) and CSV Exporting!
# A CSV file is basically a pure data format that opens perfectly in Microsoft Excel.

import requests
from bs4 import BeautifulSoup
import csv # The built-in Standard Library for handling Excel data!
import time

CSV_FILENAME = "scraped_quotes.csv"

def scrape_quotes_to_csv():
    print("========================================")
    print("      ⛏️ AUTOMATED CSV DATA MINER        ")
    print("========================================")
    
    # We open a CSV file in 'w' (Write) mode.
    # newline='' prevents Windows from adding ugly double-spacing between rows.
    # encoding='utf-8' is CRITICAL because authors might have foreign characters in their names!
    with open(CSV_FILENAME, "w", newline='', encoding='utf-8') as file:
        
        # We create a 'writer' object that acts like an Excel cursor
        writer = csv.writer(file)
        
        # Write our Column Headers (Row 1)
        writer.writerow(["Quote", "Author", "Tags"])
        
        page_number = 1
        total_quotes_found = 0
        
        # We start an infinite loop. We will only break it when we hit the very last page!
        while True:
            # We dynamically inject the page number into the URL
            url = f"http://quotes.toscrape.com/page/{page_number}/"
            print(f"[*] Extracting Data from Page {page_number}...")
            
            headers = {'User-Agent': 'Mozilla/5.0'}
            response = requests.get(url, headers=headers)
            
            # Defensive programming: If the server crashes, save what we have and abort!
            if response.status_code != 200:
                print(f"[!] Server error {response.status_code}. Aborting early.")
                break
                
            soup = BeautifulSoup(response.text, "html.parser")
            
            # The core structure of this site wraps every quote inside a <div class="quote">
            # By finding the containers FIRST, we ensure the Author matches the exact Quote!
            quote_containers = soup.find_all("div", class_="quote")
            
            # If a page has NO containers on it, it means we went past the final page!
            if len(quote_containers) == 0:
                print("\n[!] Reached the end of the website. No more quotes found!")
                break
                
            # Loop through every single container on the current page
            for container in quote_containers:
                # We use .find() instead of .find_all() because there is only ONE quote per container
                text = container.find("span", class_="text").text
                author = container.find("small", class_="author").text
                
                # Tags are trickier! A quote might have 4 tags. We find all of them.
                tag_elements = container.find_all("a", class_="tag")
                # We use a List Comprehension to extract the text from the tag objects
                tags_list = [t.text for t in tag_elements]
                # Then we join them into a single string separated by commas (e.g., "life, love, humor")
                tags_string = ", ".join(tags_list)
                
                # Finally, we write this entire row of data into our Excel CSV file
                writer.writerow([text, author, tags_string])
                total_quotes_found += 1
                
            # Be polite to the server! Don't spam 100 requests per second or you will be banned.
            time.sleep(1)
            
            # Turn the page incrementer for the next loop!
            page_number += 1

    print("========================================")
    print(f"🎉 MINING COMPLETE! Extracted {total_quotes_found} quotes.")
    print(f"💾 Check the folder for the new '{CSV_FILENAME}' file and open it in Excel!")

if __name__ == "__main__":
    scrape_quotes_to_csv()
