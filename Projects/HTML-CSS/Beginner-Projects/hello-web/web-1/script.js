/*
 * JavaScript for Hello Web - Level 1: Web Interactivity
 * 
 * Welcome to JavaScript! This is where static pages come alive.
 * Learn how to add interactivity and dynamic behavior to your web pages.
 * 
 * Key concepts you'll learn:
 * - DOM manipulation (changing HTML elements)
 * - Event handling (responding to user actions)
 * - CSS manipulation (changing styles dynamically)
 * - Functions and event listeners
 * - Human-like code with detailed comments!
 */

// Wait for the page to fully load before running our code
document.addEventListener('DOMContentLoaded', function() {
    console.log('Hello Web page loaded successfully!');
    
    // Initialize the page with some welcome animations
    initializePage();
    
    // Add hover effects to interactive elements
    addHoverEffects();
    
    // Setup smooth scrolling
    setupSmoothScrolling();
});

// Initialize the page with welcome animations
function initializePage() {
    console.log('Initializing page...');
    
    // Add fade-in animation to sections
    const sections = document.querySelectorAll('section');
    sections.forEach((section, index) => {
        // Stagger the animations for a nice effect
        setTimeout(() => {
            section.classList.add('fade-in');
        }, index * 200); // 200ms delay between each section
    });
    
    // Add animation to concept cards
    const conceptCards = document.querySelectorAll('.concept-card');
    conceptCards.forEach((card, index) => {
        setTimeout(() => {
            card.classList.add('slide-in');
        }, 1000 + (index * 100)); // Start after sections, stagger cards
    });
    
    console.log('Page initialized with animations!');
}

// Add hover effects to interactive elements
function addHoverEffects() {
    console.log('Adding hover effects...');
    
    // Add hover effect to concept cards
    const conceptCards = document.querySelectorAll('.concept-card');
    conceptCards.forEach(card => {
        card.addEventListener('mouseenter', function() {
            // Add a subtle glow effect
            this.style.boxShadow = '0 8px 25px rgba(40, 167, 69, 0.3)';
            this.style.transform = 'translateY(-5px) scale(1.02)';
        });
        
        card.addEventListener('mouseleave', function() {
            // Remove the glow effect
            this.style.boxShadow = '0 3px 10px rgba(0, 0, 0, 0.1)';
            this.style.transform = 'translateY(0) scale(1)';
        });
    });
    
    // Add hover effect to step cards
    const steps = document.querySelectorAll('.step');
    steps.forEach(step => {
        step.addEventListener('mouseenter', function() {
            const stepNumber = this.querySelector('.step-number');
            stepNumber.style.transform = 'scale(1.1) rotate(5deg)';
            stepNumber.style.background = 'linear-gradient(45deg, #ff6b6b 0%, #ee5a24 100%)';
        });
        
        step.addEventListener('mouseleave', function() {
            const stepNumber = this.querySelector('.step-number');
            stepNumber.style.transform = 'scale(1) rotate(0deg)';
            stepNumber.style.background = 'linear-gradient(45deg, #4facfe 0%, #00f2fe 100%)';
        });
    });
    
    console.log('Hover effects added!');
}

// Setup smooth scrolling for navigation
function setupSmoothScrolling() {
    console.log('Setting up smooth scrolling...');
    
    // Add click event to all internal links
    const internalLinks = document.querySelectorAll('a[href^="#"]');
    internalLinks.forEach(link => {
        link.addEventListener('click', function(e) {
            e.preventDefault(); // Prevent default jump behavior
            
            const targetId = this.getAttribute('href');
            const targetElement = document.querySelector(targetId);
            
            if (targetElement) {
                // Smooth scroll to the target element
                targetElement.scrollIntoView({
                    behavior: 'smooth',
                    block: 'start'
                });
            }
        });
    });
    
    console.log('Smooth scrolling setup complete!');
}

// Interactive Demo Functions

// Function to change background color
function changeColor() {
    console.log('Changing background color...');
    
    // Array of beautiful gradient combinations
    const gradients = [
        'linear-gradient(135deg, #667eea 0%, #764ba2 100%)',
        'linear-gradient(135deg, #f093fb 0%, #f5576c 100%)',
        'linear-gradient(135deg, #4facfe 0%, #00f2fe 100%)',
        'linear-gradient(135deg, #43e97b 0%, #38f9d7 100%)',
        'linear-gradient(135deg, #fa709a 0%, #fee140 100%)',
        'linear-gradient(135deg, #30cfd0 0%, #330867 100%)',
        'linear-gradient(135deg, #a8edea 0%, #fed6e3 100%)',
        'linear-gradient(135deg, #ff9a9e 0%, #fecfef 100%)'
    ];
    
    // Pick a random gradient
    const randomGradient = gradients[Math.floor(Math.random() * gradients.length)];
    
    // Apply the gradient to the body with a smooth transition
    document.body.style.transition = 'background 1s ease-in-out';
    document.body.style.background = randomGradient;
    
    // Update the demo output
    updateDemoOutput('Background changed to a beautiful gradient! Try again for another color.');
    
    console.log('Background color changed successfully!');
}

// Function to add text to the demo output
function addText() {
    console.log('Adding text...');
    
    // Array of encouraging messages
    const messages = [
        'You\'re doing great! Keep learning!',
        'Web development is fun, isn\'t it?',
        'Every expert was once a beginner!',
        'Keep practicing and you\'ll master this!',
        'You\'re building amazing skills!',
        'The web is your canvas!',
        'Code, create, and inspire!',
        'Your journey has just begun!'
    ];
    
    // Pick a random message
    const randomMessage = messages[Math.floor(Math.random() * messages.length)];
    
    // Create a new paragraph element
    const newParagraph = document.createElement('p');
    newParagraph.textContent = randomMessage;
    newParagraph.style.marginTop = '10px';
    newParagraph.style.padding = '10px';
    newParagraph.style.background = 'rgba(255, 255, 255, 0.2)';
    newParagraph.style.borderRadius = '5px';
    newParagraph.style.animation = 'fadeIn 0.5s ease-in';
    
    // Add the new paragraph to the demo output
    const demoOutput = document.getElementById('demo-output');
    demoOutput.appendChild(newParagraph);
    
    // Update the main message
    updateDemoOutput('New text added! Each message is randomly chosen to keep things interesting.');
    
    console.log('Text added successfully!');
}

// Function to toggle visibility of elements
function toggleVisibility() {
    console.log('Toggling visibility...');
    
    // Get all concept cards
    const conceptCards = document.querySelectorAll('.concept-card');
    
    // Check if any cards are currently hidden
    let anyHidden = false;
    conceptCards.forEach(card => {
        if (card.style.display === 'none') {
            anyHidden = true;
        }
    });
    
    if (anyHidden) {
        // Show all hidden cards
        conceptCards.forEach(card => {
            card.style.display = 'block';
            card.style.animation = 'fadeIn 0.5s ease-in';
        });
        updateDemoOutput('All concept cards are now visible! Click again to hide them.');
    } else {
        // Hide all cards with animation
        conceptCards.forEach((card, index) => {
            setTimeout(() => {
                card.style.animation = 'fadeOut 0.5s ease-out';
                setTimeout(() => {
                    card.style.display = 'none';
                }, 500);
            }, index * 100); // Stagger the hiding animation
        });
        updateDemoOutput('Concept cards are now hidden! Click again to show them.');
    }
    
    console.log('Visibility toggled successfully!');
}

// Helper function to update the demo output
function updateDemoOutput(message) {
    console.log('Updating demo output:', message);
    
    const demoOutput = document.getElementById('demo-output');
    
    // Create a new message element
    const messageElement = document.createElement('div');
    messageElement.textContent = message;
    messageElement.style.padding = '15px';
    messageElement.style.marginTop = '10px';
    messageElement.style.background = 'rgba(255, 255, 255, 0.2)';
    messageElement.style.borderRadius = '8px';
    messageElement.style.border = '2px solid rgba(255, 255, 255, 0.3)';
    messageElement.style.animation = 'fadeIn 0.5s ease-in';
    
    // Clear previous content and add new message
    demoOutput.innerHTML = '';
    demoOutput.appendChild(messageElement);
    
    console.log('Demo output updated!');
}

// Add fadeOut animation to the stylesheet
const style = document.createElement('style');
style.textContent = `
    @keyframes fadeOut {
        from { opacity: 1; transform: scale(1); }
        to { opacity: 0; transform: scale(0.8); }
    }
`;
document.head.appendChild(style);

// Add keyboard shortcuts for better user experience
document.addEventListener('keydown', function(e) {
    console.log('Key pressed:', e.key);
    
    // Check if user is typing in an input field
    const activeElement = document.activeElement;
    const isTyping = activeElement.tagName === 'INPUT' || activeElement.tagName === 'TEXTAREA';
    
    if (!isTyping) {
        switch(e.key) {
            case '1':
                changeColor();
                break;
            case '2':
                addText();
                break;
            case '3':
                toggleVisibility();
                break;
            case 'h':
            case 'H':
                // Show help
                alert('Keyboard Shortcuts:\n1 - Change Background Color\n2 - Add Text\n3 - Toggle Visibility\nH - Show Help');
                break;
        }
    }
});

// Add a progress tracker to show learning progress
function addProgressTracker() {
    console.log('Adding progress tracker...');
    
    // Create progress tracker container
    const progressContainer = document.createElement('div');
    progressContainer.style.cssText = `
        position: fixed;
        top: 20px;
        right: 20px;
        background: rgba(255, 255, 255, 0.95);
        padding: 15px;
        border-radius: 10px;
        box-shadow: 0 5px 15px rgba(0, 0, 0, 0.2);
        z-index: 1000;
        max-width: 200px;
    `;
    
    // Add progress title
    const progressTitle = document.createElement('h4');
    progressTitle.textContent = 'Your Progress';
    progressTitle.style.cssText = `
        margin: 0 0 10px 0;
        color: #333;
        font-size: 1.1em;
    `;
    
    // Add progress items
    const progressItems = [
        { text: 'HTML Basics', completed: true },
        { text: 'CSS Fundamentals', completed: true },
        { text: 'JavaScript Magic', completed: false },
        { text: 'Interactive Demo', completed: false }
    ];
    
    let progressHTML = '';
    progressItems.forEach(item => {
        const status = item.completed ? 'completed' : 'pending';
        const icon = item.completed ? 'completed' : 'pending';
        progressHTML += `
            <div style="margin: 5px 0; font-size: 0.9em;">
                <span style="color: ${item.completed ? '#28a745' : '#6c757d'};">
                    ${item.completed ? 'completed' : 'pending'} ${item.text}
                </span>
            </div>
        `;
    });
    
    progressContainer.innerHTML = progressHTML;
    document.body.appendChild(progressContainer);
    
    console.log('Progress tracker added!');
}

// Initialize progress tracker when page loads
addProgressTracker();

// Add a "back to top" button for better navigation
function addBackToTopButton() {
    console.log('Adding back to top button...');
    
    // Create the button
    const backToTopButton = document.createElement('button');
    backToTopButton.innerHTML = 'uparrow';
    backToTopButton.textContent = 'uparrow';
    backToTopButton.style.cssText = `
        position: fixed;
        bottom: 20px;
        right: 20px;
        background: linear-gradient(45deg, #007bff, #0056b3);
        color: white;
        border: none;
        width: 50px;
        height: 50px;
        border-radius: 50%;
        cursor: pointer;
        font-size: 20px;
        box-shadow: 0 5px 15px rgba(0, 0, 0, 0.3);
        transition: all 0.3s ease;
        z-index: 1000;
        display: none;
    `;
    
    // Show/hide button based on scroll position
    window.addEventListener('scroll', function() {
        if (window.pageYOffset > 300) {
            backToTopButton.style.display = 'block';
        } else {
            backToTopButton.style.display = 'none';
        }
    });
    
    // Scroll to top when clicked
    backToTopButton.addEventListener('click', function() {
        window.scrollTo({
            top: 0,
            behavior: 'smooth'
        });
    });
    
    // Add hover effect
    backToTopButton.addEventListener('mouseenter', function() {
        this.style.transform = 'scale(1.1)';
        this.style.boxShadow = '0 8px 20px rgba(0, 0, 0, 0.4)';
    });
    
    backToTopButton.addEventListener('mouseleave', function() {
        this.style.transform = 'scale(1)';
        this.style.boxShadow = '0 5px 15px rgba(0, 0, 0, 0.3)';
    });
    
    // Add to page
    document.body.appendChild(backToTopButton);
    
    console.log('Back to top button added!');
}

// Initialize back to top button
addBackToTopButton();

// Console message for developers
console.log('%c Hello Web - Interactive Learning Experience! ', 'background: #007bff; color: white; font-size: 16px; padding: 10px; border-radius: 5px;');
console.log('%c Explore the interactive features and learn web development! ', 'background: #28a745; color: white; font-size: 14px; padding: 8px; border-radius: 5px;');
console.log('%c Keyboard shortcuts: 1 (color), 2 (text), 3 (toggle), H (help) ', 'background: #ffc107; color: #333; font-size: 12px; padding: 6px; border-radius: 5px;');
