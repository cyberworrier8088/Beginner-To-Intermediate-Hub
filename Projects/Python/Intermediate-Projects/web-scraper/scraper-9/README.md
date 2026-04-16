# 🕸️ Web Scraper - Method 9: HTML Extraction

Welcome to the Intermediate Web Scraping module! This project combines our network knowledge (`requests`) with intense data manipulation using the legendary `BeautifulSoup` library.

### 🧠 The Core Concept: The DOM (Document Object Model)
When you type `https://google.com`, the Google server sends your browser a massive String of "HTML" Text. Your browser reads that text and turns it into the visual website you see. 
This HTML text is heavily structured into "Tags" like `<body>`, `<div>`, `<span>`, and `<p>`. Web Scraping is the art of downloading this raw HTML text via Python, and searching through it for specific tags to steal the data inside them.

### 🛠️ Technical Deep Dive
1.  **Browser Spoofing (Headers)**: Code like `requests.get(url)` is extremely fast—too fast to be a human. Many modern websites have security protocols to block Python scripts from accessing their site. By adding `headers={'User-Agent': 'Mozilla/...'}`, our Python script literally lies to the server, pretending to be a normal human using the Google Chrome browser!
2.  **`BeautifulSoup(html, "html.parser")`**: Trying to find the 56th paragraph in a million-letter string of raw HTML using normal Python code is impossible. When we pass the HTML to BeautifulSoup, it "Parses" it. It turns that chaotic text string into a beautifully organized tree of objects that we can search through matrix-style.
3.  **`soup.find_all("tag", class_="...")`**: Websites use CSS "Classes" to style different parts of the website (e.g., making all quotes blue). Because all the quotes on our target website use the exact same class `class="text"`, we can use `find_all` to instantly extract every single quote on the entire webpage in a fraction of a second!
4.  **`.text` Extraction**: When BeautifulSoup finds a tag, it looks like this: `<span class="text">Hello World</span>`. That's ugly! By typing `.text` at the end, it strips away the HTML armor and leaves only the pure human string: `"Hello World"`.

### 🏃 How to Run
```bash
python scraper.py
```
Watch how Python can visit a website, read the entire page, format the data, and print it to your terminal in under 1 second!
