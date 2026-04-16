"""
Web Scraper - Level 9: HTML Parsing and Data Extraction
Learn web scraping with requests and BeautifulSoup4
Real-world data collection from websites
"""

import requests
from bs4 import BeautifulSoup
import csv
import time
import json
from urllib.parse import urljoin, urlparse
import re

class WebScraper:
    """Professional web scraper with error handling and data extraction"""
    
    def __init__(self):
        self.session = requests.Session()
        self.session.headers.update({
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36'
        })
        self.scraped_data = []
        
    def fetch_page(self, url, timeout=10):
        """Fetch a web page with error handling"""
        print(f"Fetching: {url}")
        
        try:
            response = self.session.get(url, timeout=timeout)
            response.raise_for_status()  # Raise exception for bad status codes
            
            print(f"Success: Status {response.status_code}, Size: {len(response.content)} bytes")
            return response
            
        except requests.exceptions.RequestException as e:
            print(f"Error fetching {url}: {e}")
            return None
    
    def parse_html(self, html_content):
        """Parse HTML content with BeautifulSoup"""
        return BeautifulSoup(html_content, 'html.parser')
    
    def extract_text_safe(self, element):
        """Safely extract text from an element"""
        if element:
            return element.get_text(strip=True)
        return ""
    
    def scrape_demo_site(self, url):
        """Scrape a demo site with structured data"""
        print(f"\n=== SCRAPING DEMO SITE ===")
        print(f"URL: {url}")
        
        # Fetch the page
        response = self.fetch_page(url)
        if not response:
            return []
        
        # Parse HTML
        soup = self.parse_html(response.content)
        
        # Extract page title
        title = self.extract_text_safe(soup.find('title'))
        print(f"Page Title: {title}")
        
        # Extract headings
        headings = []
        for i in range(1, 7):  # h1 to h6
            for heading in soup.find_all(f'h{i}'):
                headings.append({
                    'level': i,
                    'text': self.extract_text_safe(heading),
                    'id': heading.get('id', ''),
                    'class': heading.get('class', [])
                })
        
        print(f"Found {len(headings)} headings")
        
        # Extract links
        links = []
        for link in soup.find_all('a', href=True):
            href = link['href']
            text = self.extract_text_safe(link)
            
            # Convert relative URLs to absolute
            if href.startswith('/'):
                base_url = f"{urlparse(url).scheme}://{urlparse(url).netloc}"
                href = urljoin(base_url, href)
            
            links.append({
                'url': href,
                'text': text,
                'title': link.get('title', '')
            })
        
        print(f"Found {len(links)} links")
        
        # Extract images
        images = []
        for img in soup.find_all('img', src=True):
            src = img['src']
            alt = img.get('alt', '')
            
            # Convert relative URLs to absolute
            if src.startswith('/'):
                base_url = f"{urlparse(url).scheme}://{urlparse(url).netloc}"
                src = urljoin(base_url, src)
            
            images.append({
                'src': src,
                'alt': alt,
                'width': img.get('width', ''),
                'height': img.get('height', '')
            })
        
        print(f"Found {len(images)} images")
        
        # Extract paragraphs
        paragraphs = []
        for p in soup.find_all('p'):
            text = self.extract_text_safe(p)
            if len(text) > 20:  # Only meaningful paragraphs
                paragraphs.append(text)
        
        print(f"Found {len(paragraphs)} meaningful paragraphs")
        
        # Extract meta information
        meta_info = {}
        for meta in soup.find_all('meta'):
            name = meta.get('name') or meta.get('property', '')
            content = meta.get('content', '')
            if name and content:
                meta_info[name] = content
        
        # Compile results
        scraped_data = {
            'url': url,
            'title': title,
            'headings': headings,
            'links': links,
            'images': images,
            'paragraphs': paragraphs,
            'meta_info': meta_info,
            'scraped_at': time.strftime('%Y-%m-%d %H:%M:%S')
        }
        
        self.scraped_data.append(scraped_data)
        return scraped_data
    
    def scrape_multiple_pages(self, urls, delay=1):
        """Scrape multiple pages with rate limiting"""
        print(f"\n=== SCRAPING MULTIPLE PAGES ===")
        print(f"URLs: {len(urls)}, Delay: {delay}s between requests")
        
        all_data = []
        
        for i, url in enumerate(urls, 1):
            print(f"\n--- Page {i}/{len(urls)} ---")
            
            data = self.scrape_demo_site(url)
            if data:
                all_data.append(data)
            
            # Rate limiting - be respectful to servers
            if i < len(urls):  # Don't delay after last request
                print(f"Waiting {delay}s before next request...")
                time.sleep(delay)
        
        print(f"\nCompleted scraping {len(all_data)} pages successfully")
        return all_data
    
    def save_to_json(self, filename, data=None):
        """Save scraped data to JSON file"""
        if data is None:
            data = self.scraped_data
        
        try:
            with open(filename, 'w', encoding='utf-8') as f:
                json.dump(data, f, indent=2, ensure_ascii=False)
            print(f"Data saved to {filename}")
        except Exception as e:
            print(f"Error saving to JSON: {e}")
    
    def save_to_csv(self, filename, data=None):
        """Save scraped data to CSV file"""
        if data is None:
            data = self.scraped_data
        
        try:
            with open(filename, 'w', newline='', encoding='utf-8') as f:
                if not data:
                    print("No data to save")
                    return
                
                # Create CSV writer
                writer = csv.writer(f)
                
                # Write header
                writer.writerow(['URL', 'Title', 'Headings Count', 'Links Count', 'Images Count', 'Paragraphs Count'])
                
                # Write data
                for item in data:
                    writer.writerow([
                        item['url'],
                        item['title'],
                        len(item['headings']),
                        len(item['links']),
                        len(item['images']),
                        len(item['paragraphs'])
                    ])
            
            print(f"Data saved to {filename}")
        except Exception as e:
            print(f"Error saving to CSV: {e}")
    
    def generate_report(self, data=None):
        """Generate a text report of scraped data"""
        if data is None:
            data = self.scraped_data
        
        if not data:
            print("No data to report")
            return
        
        report = []
        report.append("WEB SCRAPING REPORT")
        report.append("=" * 50)
        report.append(f"Pages scraped: {len(data)}")
        report.append(f"Generated at: {time.strftime('%Y-%m-%d %H:%M:%S')}")
        report.append("")
        
        total_headings = sum(len(item['headings']) for item in data)
        total_links = sum(len(item['links']) for item in data)
        total_images = sum(len(item['images']) for item in data)
        total_paragraphs = sum(len(item['paragraphs']) for item in data)
        
        report.append("SUMMARY STATISTICS:")
        report.append(f"Total headings: {total_headings}")
        report.append(f"Total links: {total_links}")
        report.append(f"Total images: {total_images}")
        report.append(f"Total paragraphs: {total_paragraphs}")
        report.append("")
        
        for i, item in enumerate(data, 1):
            report.append(f"PAGE {i}: {item['url']}")
            report.append(f"Title: {item['title']}")
            report.append(f"Headings: {len(item['headings'])}")
            report.append(f"Links: {len(item['links'])}")
            report.append(f"Images: {len(item['images'])}")
            report.append(f"Paragraphs: {len(item['paragraphs'])}")
            
            if item['paragraphs']:
                report.append("Sample paragraph:")
                report.append(f"  {item['paragraphs'][0][:100]}...")
            
            report.append("")
        
        report_text = '\n'.join(report)
        print(report_text)
        
        # Save report to file
        with open('scraping_report.txt', 'w', encoding='utf-8') as f:
            f.write(report_text)
        
        return report_text

def demo_scraping():
    """Demonstrate web scraping capabilities"""
    print("=== WEB SCRAPER DEMONSTRATION ===")
    print("Learning web scraping with requests and BeautifulSoup4!")
    print()
    
    # Create scraper instance
    scraper = WebScraper()
    
    # Demo URLs (these are safe, educational sites)
    demo_urls = [
        "https://httpbin.org/html",  # HTML testing site
        "https://example.com",       # Simple example site
    ]
    
    print("This demo will scrape educational websites to teach you:")
    print("- HTTP requests with error handling")
    print("- HTML parsing with BeautifulSoup")
    print("- Data extraction techniques")
    print("- Rate limiting and respectful scraping")
    print("- Data export to JSON/CSV")
    print()
    
    # Scrape demo sites
    scraped_data = scraper.scrape_multiple_pages(demo_urls, delay=1)
    
    if scraped_data:
        # Generate report
        scraper.generate_report(scraped_data)
        
        # Save data
        scraper.save_to_json('scraped_data.json')
        scraper.save_to_csv('scraped_data.csv')
        
        print("\n=== SCRAPING COMPLETE ===")
        print("Files created:")
        print("- scraped_data.json (full data)")
        print("- scraped_data.csv (summary)")
        print("- scraping_report.txt (analysis)")
        
        print("\nKey concepts learned:")
        print("- HTTP requests and error handling")
        print("- HTML parsing with BeautifulSoup")
        print("- Data extraction and cleaning")
        print("- Rate limiting for ethical scraping")
        print("- Data export in multiple formats")
        
    else:
        print("No data was scraped. Check your internet connection.")

def main():
    """Main function for web scraper demo"""
    print("=== WEB SCRAPER - LEVEL 9 ===")
    print("Learn professional web scraping techniques!")
    print()
    print("Prerequisites:")
    print("pip install requests beautifulsoup4")
    print()
    print("Legal/Ethical Note:")
    print("Always respect robots.txt")
    print("Don't overload servers")
    print("Check terms of service")
    print("Only scrape public data")
    print()
    
    choice = input("Run demo scraping? (y/n): ").lower()
    
    if choice == 'y':
        demo_scraping()
    else:
        print("Demo cancelled. Run with 'y' to see web scraping in action!")

if __name__ == "__main__":
    main()
