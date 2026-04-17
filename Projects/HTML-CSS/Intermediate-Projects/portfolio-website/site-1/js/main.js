/*
 * Professional Portfolio JavaScript - Level 4: Advanced Web Interactivity
 * 
 * Welcome to advanced JavaScript! This is where interactivity meets professionalism.
 * Learn modern JavaScript techniques and best practices.
 * 
 * Key concepts you'll learn:
 * - DOM manipulation and event handling
 * - Modern ES6+ JavaScript features
 * - Performance optimization techniques
 * - Accessibility considerations
 * - Error handling and debugging
 * - Modular JavaScript architecture
 * - Human-like code with detailed comments!
 */

// Modern JavaScript with strict mode and ES6+ features
'use strict';

// Portfolio Application - Main controller class
class PortfolioApp {
    constructor() {
        console.log('Portfolio App initializing...');
        
        // Application state
        this.state = {
            isMenuOpen: false,
            currentSection: 'home',
            scrollPosition: 0,
            isScrolling: false,
            animationsEnabled: true,
            theme: 'light'
        };
        
        // DOM element references
        this.elements = {
            body: document.body,
            header: document.querySelector('.header'),
            navToggle: document.querySelector('.nav-toggle'),
            navMenu: document.querySelector('.nav-menu'),
            navLinks: document.querySelectorAll('.nav-link'),
            backToTop: document.getElementById('backToTop'),
            sections: document.querySelectorAll('section'),
            skillBars: document.querySelectorAll('.skill-bar'),
            projectCards: document.querySelectorAll('.project-card'),
            filterButtons: document.querySelectorAll('.filter-btn'),
            timeline: document.querySelector('.timeline'),
            stats: document.querySelectorAll('.stat-number'),
            contactForm: document.getElementById('contactForm')
        };
        
        // Initialize application
        this.init();
    }
    
    // Initialize all app features
    init() {
        console.log('Initializing portfolio features...');
        
        // Wait for DOM to be fully loaded
        if (document.readyState === 'loading') {
            document.addEventListener('DOMContentLoaded', () => this.setupFeatures());
        } else {
            this.setupFeatures();
        }
    }
    
    // Setup all application features
    setupFeatures() {
        console.log('Setting up portfolio features...');
        
        // Setup navigation
        this.setupNavigation();
        
        // Setup scroll effects
        this.setupScrollEffects();
        
        // Setup animations
        this.setupAnimations();
        
        // Setup project filtering
        this.setupProjectFiltering();
        
        // Setup skill animations
        this.setupSkillAnimations();
        
        // Setup statistics counter
        this.setupStatsCounter();
        
        // Setup contact form
        this.setupContactForm();
        
        // Setup keyboard navigation
        this.setupKeyboardNavigation();
        
        // Setup performance monitoring
        this.setupPerformanceMonitoring();
        
        // Setup accessibility features
        this.setupAccessibility();
        
        console.log('Portfolio features initialized successfully!');
    }
    
    // Navigation functionality
    setupNavigation() {
        console.log('Setting up navigation...');
        
        // Mobile menu toggle
        if (this.elements.navToggle) {
            this.elements.navToggle.addEventListener('click', (e) => {
                e.preventDefault();
                this.toggleMobileMenu();
            });
        }
        
        // Navigation links
        this.elements.navLinks.forEach(link => {
            link.addEventListener('click', (e) => {
                const href = link.getAttribute('href');
                
                // Handle smooth scrolling to sections
                if (href.startsWith('#')) {
                    e.preventDefault();
                    this.scrollToSection(href.substring(1));
                }
                
                // Close mobile menu
                if (this.state.isMenuOpen) {
                    this.closeMobileMenu();
                }
            });
        });
        
        // Close mobile menu on escape key
        document.addEventListener('keydown', (e) => {
            if (e.key === 'Escape' && this.state.isMenuOpen) {
                this.closeMobileMenu();
            }
        });
        
        // Close mobile menu on outside click
        document.addEventListener('click', (e) => {
            if (this.state.isMenuOpen && 
                !this.elements.navToggle.contains(e.target) && 
                !this.elements.navMenu.contains(e.target)) {
                this.closeMobileMenu();
            }
        });
    }
    
    // Toggle mobile menu
    toggleMobileMenu() {
        console.log('Toggling mobile menu...');
        
        this.state.isMenuOpen = !this.state.isMenuOpen;
        
        if (this.state.isMenuOpen) {
            this.openMobileMenu();
        } else {
            this.closeMobileMenu();
        }
    }
    
    // Open mobile menu
    openMobileMenu() {
        this.elements.navToggle.classList.add('active');
        this.elements.navMenu.classList.add('active');
        this.elements.navToggle.setAttribute('aria-expanded', 'true');
        this.elements.body.style.overflow = 'hidden'; // Prevent background scroll
        
        // Focus first menu item
        const firstLink = this.elements.navMenu.querySelector('.nav-link');
        if (firstLink) {
            firstLink.focus();
        }
    }
    
    // Close mobile menu
    closeMobileMenu() {
        this.elements.navToggle.classList.remove('active');
        this.elements.navMenu.classList.remove('active');
        this.elements.navToggle.setAttribute('aria-expanded', 'false');
        this.elements.body.style.overflow = ''; // Restore background scroll
    }
    
    // Smooth scroll to section
    scrollToSection(sectionId) {
        console.log(`Scrolling to section: ${sectionId}`);
        
        const section = document.getElementById(sectionId);
        if (section) {
            const headerHeight = this.elements.header.offsetHeight;
            const targetPosition = section.offsetTop - headerHeight;
            
            // Smooth scroll with easing
            this.smoothScrollTo(targetPosition, 800);
            
            // Update current section
            this.state.currentSection = sectionId;
            
            // Update URL hash
            history.pushState(null, null, `#${sectionId}`);
        }
    }
    
    // Smooth scroll implementation
    smoothScrollTo(targetPosition, duration) {
        const startPosition = window.pageYOffset;
        const distance = targetPosition - startPosition;
        let startTime = null;
        
        const animation = (currentTime) => {
            if (startTime === null) startTime = currentTime;
            const timeElapsed = currentTime - startTime;
            const progress = Math.min(timeElapsed / duration, 1);
            
            // Easing function (ease-in-out)
            const ease = progress < 0.5 
                ? 2 * progress * progress 
                : -1 + (4 - 2 * progress) * progress;
            
            window.scrollTo(0, startPosition + distance * ease);
            
            if (timeElapsed < duration) {
                requestAnimationFrame(animation);
            } else {
                this.state.isScrolling = false;
            }
        };
        
        this.state.isScrolling = true;
        requestAnimationFrame(animation);
    }
    
    // Scroll effects and header behavior
    setupScrollEffects() {
        console.log('Setting up scroll effects...');
        
        let lastScrollY = window.pageYOffset;
        let ticking = false;
        
        const updateScrollEffects = () => {
            const currentScrollY = window.pageYOffset;
            
            // Header hide/show on scroll
            if (currentScrollY > lastScrollY && currentScrollY > 100) {
                // Scrolling down
                this.elements.header.style.transform = 'translateY(-100%)';
            } else {
                // Scrolling up
                this.elements.header.style.transform = 'translateY(0)';
            }
            
            // Header background opacity
            if (currentScrollY > 50) {
                this.elements.header.style.background = 'rgba(255, 255, 255, 0.98)';
                this.elements.header.style.boxShadow = '0 2px 10px rgba(0, 0, 0, 0.1)';
            } else {
                this.elements.header.style.background = 'rgba(255, 255, 255, 0.95)';
                this.elements.header.style.boxShadow = 'none';
            }
            
            // Back to top button visibility
            if (this.elements.backToTop) {
                if (currentScrollY > 500) {
                    this.elements.backToTop.classList.add('visible');
                } else {
                    this.elements.backToTop.classList.remove('visible');
                }
            }
            
            // Update active navigation link
            this.updateActiveNavLink();
            
            lastScrollY = currentScrollY;
            ticking = false;
        };
        
        const onScroll = () => {
            if (!ticking) {
                requestAnimationFrame(updateScrollEffects);
                ticking = true;
            }
        };
        
        // Throttled scroll event
        window.addEventListener('scroll', onScroll, { passive: true });
        
        // Back to top button
        if (this.elements.backToTop) {
            this.elements.backToTop.addEventListener('click', () => {
                this.smoothScrollTo(0, 600);
            });
        }
    }
    
    // Update active navigation link based on scroll position
    updateActiveNavLink() {
        const scrollPosition = window.pageYOffset + this.elements.header.offsetHeight + 100;
        
        this.elements.navLinks.forEach(link => {
            const href = link.getAttribute('href');
            if (href.startsWith('#')) {
                const section = document.getElementById(href.substring(1));
                if (section) {
                    const sectionTop = section.offsetTop;
                    const sectionBottom = sectionTop + section.offsetHeight;
                    
                    if (scrollPosition >= sectionTop && scrollPosition < sectionBottom) {
                        // Remove active class from all links
                        this.elements.navLinks.forEach(l => l.classList.remove('active'));
                        // Add active class to current link
                        link.classList.add('active');
                    }
                }
            }
        });
    }
    
    // Animation setup and intersection observer
    setupAnimations() {
        console.log('Setting up animations...');
        
        // Check for reduced motion preference
        const prefersReducedMotion = window.matchMedia('(prefers-reduced-motion: reduce)').matches;
        
        if (prefersReducedMotion) {
            console.log('Reduced motion detected, disabling animations');
            this.state.animationsEnabled = false;
            return;
        }
        
        // Intersection Observer for scroll animations
        const observerOptions = {
            root: null,
            rootMargin: '0px',
            threshold: 0.1
        };
        
        const animationObserver = new IntersectionObserver((entries) => {
            entries.forEach(entry => {
                if (entry.isIntersecting) {
                    this.animateElement(entry.target);
                    animationObserver.unobserve(entry.target);
                }
            });
        }, observerOptions);
        
        // Observe elements for animation
        const animatedElements = document.querySelectorAll('.fade-in, .slide-in-left, .slide-in-right, .scale-in');
        animatedElements.forEach(element => {
            animationObserver.observe(element);
        });
        
        // Staggered animations for skill items
        const skillItems = document.querySelectorAll('.skill-item');
        skillItems.forEach((item, index) => {
            item.style.animationDelay = `${index * 0.1}s`;
            animationObserver.observe(item);
        });
        
        // Staggered animations for project cards
        this.elements.projectCards.forEach((card, index) => {
            card.style.animationDelay = `${index * 0.15}s`;
            animationObserver.observe(card);
        });
    }
    
    // Animate individual element
    animateElement(element) {
        if (!this.state.animationsEnabled) return;
        
        // Add animation class based on element type or data attribute
        const animationType = element.dataset.animation || 'fade-in';
        element.classList.add('animate-on-scroll', 'is-animated');
        
        // Remove animation class after completion
        element.addEventListener('animationend', () => {
            element.classList.remove('animate-on-scroll');
        }, { once: true });
    }
    
    // Project filtering functionality
    setupProjectFiltering() {
        console.log('Setting up project filtering...');
        
        this.elements.filterButtons.forEach(button => {
            button.addEventListener('click', (e) => {
                e.preventDefault();
                
                const filter = button.dataset.filter;
                this.filterProjects(filter);
                
                // Update active button
                this.elements.filterButtons.forEach(btn => btn.classList.remove('active'));
                button.classList.add('active');
            });
        });
    }
    
    // Filter projects by category
    filterProjects(category) {
        console.log(`Filtering projects: ${category}`);
        
        this.elements.projectCards.forEach(card => {
            const cardCategory = card.dataset.category;
            
            if (category === 'all' || cardCategory === category) {
                // Show card with animation
                card.style.display = 'block';
                setTimeout(() => {
                    card.style.opacity = '1';
                    card.style.transform = 'translateY(0)';
                }, 50);
            } else {
                // Hide card with animation
                card.style.opacity = '0';
                card.style.transform = 'translateY(20px)';
                setTimeout(() => {
                    card.style.display = 'none';
                }, 300);
            }
        });
    }
    
    // Skill bar animations
    setupSkillAnimations() {
        console.log('Setting up skill animations...');
        
        const skillObserver = new IntersectionObserver((entries) => {
            entries.forEach(entry => {
                if (entry.isIntersecting) {
                    const skillBar = entry.target;
                    const level = skillBar.dataset.level;
                    this.animateSkillBar(skillBar, level);
                    skillObserver.unobserve(skillBar);
                }
            });
        }, { threshold: 0.5 });
        
        this.elements.skillBars.forEach(bar => {
            skillObserver.observe(bar);
        });
    }
    
    // Animate individual skill bar
    animateSkillBar(skillBar, targetLevel) {
        if (!this.state.animationsEnabled) {
            skillBar.style.width = `${targetLevel}%`;
            return;
        }
        
        let currentLevel = 0;
        const increment = targetLevel / 50; // 50 steps for smooth animation
        const duration = 1500; // 1.5 seconds
        const stepTime = duration / 50;
        
        const animate = () => {
            currentLevel += increment;
            
            if (currentLevel < targetLevel) {
                skillBar.style.width = `${currentLevel}%`;
                setTimeout(animate, stepTime);
            } else {
                skillBar.style.width = `${targetLevel}%`;
                
                // Update percentage text
                const percentageText = skillBar.parentElement.querySelector('.skill-percentage');
                if (percentageText) {
                    percentageText.textContent = `${targetLevel}%`;
                }
            }
        };
        
        animate();
    }
    
    // Statistics counter animation
    setupStatsCounter() {
        console.log('Setting up statistics counter...');
        
        const statsObserver = new IntersectionObserver((entries) => {
            entries.forEach(entry => {
                if (entry.isIntersecting) {
                    const stat = entry.target;
                    const target = parseInt(stat.dataset.target);
                    this.animateCounter(stat, target);
                    statsObserver.unobserve(stat);
                }
            });
        }, { threshold: 0.5 });
        
        this.elements.stats.forEach(stat => {
            statsObserver.observe(stat);
        });
    }
    
    // Animate counter from 0 to target
    animateCounter(element, target) {
        if (!this.state.animationsEnabled) {
            element.textContent = target;
            return;
        }
        
        let current = 0;
        const increment = target / 50; // 50 steps
        const duration = 2000; // 2 seconds
        const stepTime = duration / 50;
        
        const animate = () => {
            current += increment;
            
            if (current < target) {
                element.textContent = Math.floor(current);
                setTimeout(animate, stepTime);
            } else {
                element.textContent = target;
            }
        };
        
        animate();
    }
    
    // Contact form handling
    setupContactForm() {
        console.log('Setting up contact form...');
        
        if (!this.elements.contactForm) return;
        
        this.elements.contactForm.addEventListener('submit', (e) => {
            e.preventDefault();
            this.handleContactFormSubmit();
        });
        
        // Real-time validation
        const inputs = this.elements.contactForm.querySelectorAll('input, textarea');
        inputs.forEach(input => {
            input.addEventListener('blur', () => this.validateField(input));
            input.addEventListener('input', () => this.clearFieldError(input));
        });
    }
    
    // Handle contact form submission
    async handleContactFormSubmit() {
        console.log('Handling contact form submission...');
        
        const form = this.elements.contactForm;
        const submitButton = form.querySelector('button[type="submit"]');
        const buttonText = submitButton.querySelector('.btn-text');
        const buttonSpinner = submitButton.querySelector('.btn-spinner');
        
        // Validate form
        if (!this.validateForm()) {
            console.log('Form validation failed');
            return;
        }
        
        // Show loading state
        buttonText.textContent = 'Sending...';
        buttonSpinner.style.display = 'inline-block';
        submitButton.disabled = true;
        
        // Get form data
        const formData = new FormData(form);
        const data = Object.fromEntries(formData.entries());
        
        try {
            // Simulate API call (replace with actual API endpoint)
            await this.simulateApiCall(data);
            
            // Show success message
            this.showFormMessage('success', 'Message sent successfully! I\'ll get back to you soon.');
            
            // Reset form
            form.reset();
            
        } catch (error) {
            console.error('Form submission error:', error);
            this.showFormMessage('error', 'Failed to send message. Please try again later.');
        } finally {
            // Reset button state
            buttonText.textContent = 'Send Message';
            buttonSpinner.style.display = 'none';
            submitButton.disabled = false;
        }
    }
    
    // Simulate API call (replace with actual implementation)
    simulateApiCall(data) {
        return new Promise((resolve, reject) => {
            setTimeout(() => {
                // Simulate success (90% success rate)
                if (Math.random() > 0.1) {
                    resolve({ success: true });
                } else {
                    reject(new Error('Network error'));
                }
            }, 2000);
        });
    }
    
    // Validate entire form
    validateForm() {
        const inputs = this.elements.contactForm.querySelectorAll('input[required], textarea[required]');
        let isValid = true;
        
        inputs.forEach(input => {
            if (!this.validateField(input)) {
                isValid = false;
            }
        });
        
        return isValid;
    }
    
    // Validate individual field
    validateField(field) {
        const value = field.value.trim();
        const fieldGroup = field.closest('.form-group');
        const errorMessage = fieldGroup.querySelector('.form-error');
        
        let isValid = true;
        let message = '';
        
        // Required field validation
        if (field.hasAttribute('required') && !value) {
            isValid = false;
            message = 'This field is required';
        }
        
        // Email validation
        if (field.type === 'email' && value) {
            const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
            if (!emailRegex.test(value)) {
                isValid = false;
                message = 'Please enter a valid email address';
            }
        }
        
        // Subject validation (minimum length)
        if (field.id === 'subject' && value && value.length < 3) {
            isValid = false;
            message = 'Subject must be at least 3 characters long';
        }
        
        // Message validation (minimum length)
        if (field.id === 'message' && value && value.length < 10) {
            isValid = false;
            message = 'Message must be at least 10 characters long';
        }
        
        // Update UI
        if (isValid) {
            fieldGroup.classList.remove('error');
            if (errorMessage) errorMessage.style.display = 'none';
        } else {
            fieldGroup.classList.add('error');
            if (errorMessage) {
                errorMessage.textContent = message;
                errorMessage.style.display = 'block';
            }
        }
        
        return isValid;
    }
    
    // Clear field error
    clearFieldError(field) {
        const fieldGroup = field.closest('.form-group');
        fieldGroup.classList.remove('error');
        const errorMessage = fieldGroup.querySelector('.form-error');
        if (errorMessage) {
            errorMessage.style.display = 'none';
        }
    }
    
    // Show form message
    showFormMessage(type, message) {
        // Remove existing messages
        const existingMessage = this.elements.contactForm.querySelector('.form-message');
        if (existingMessage) {
            existingMessage.remove();
        }
        
        // Create message element
        const messageElement = document.createElement('div');
        messageElement.className = `form-message ${type}`;
        messageElement.textContent = message;
        messageElement.style.cssText = `
            padding: 1rem;
            margin-top: 1rem;
            border-radius: 0.5rem;
            font-weight: 500;
            ${type === 'success' 
                ? 'background: #10b981; color: white;' 
                : 'background: #ef4444; color: white;'
            }
        `;
        
        // Insert after form
        this.elements.contactForm.appendChild(messageElement);
        
        // Auto-remove after 5 seconds
        setTimeout(() => {
            messageElement.style.opacity = '0';
            setTimeout(() => messageElement.remove(), 300);
        }, 5000);
    }
    
    // Keyboard navigation
    setupKeyboardNavigation() {
        console.log('Setting up keyboard navigation...');
        
        document.addEventListener('keydown', (e) => {
            // Skip if user is typing in form field
            if (e.target.tagName === 'INPUT' || e.target.tagName === 'TEXTAREA') {
                return;
            }
            
            switch (e.key) {
                case '1':
                    this.scrollToSection('home');
                    break;
                case '2':
                    this.scrollToSection('about');
                    break;
                case '3':
                    this.scrollToSection('projects');
                    break;
                case '4':
                    this.scrollToSection('contact');
                    break;
                case 'h':
                case 'H':
                    this.showKeyboardHelp();
                    break;
                case '?':
                    this.showKeyboardHelp();
                    break;
                case 'Escape':
                    if (this.state.isMenuOpen) {
                        this.closeMobileMenu();
                    }
                    break;
            }
        });
    }
    
    // Show keyboard help
    showKeyboardHelp() {
        const helpText = `
Keyboard Shortcuts:
1 - Home
2 - About
3 - Projects
4 - Contact
H/? - Show this help
ESC - Close menu
        `;
        
        alert(helpText.trim());
    }
    
    // Performance monitoring
    setupPerformanceMonitoring() {
        console.log('Setting up performance monitoring...');
        
        // Monitor page load performance
        window.addEventListener('load', () => {
            const loadTime = performance.timing.loadEventEnd - performance.timing.navigationStart;
            console.log(`Page load time: ${loadTime}ms`);
            
            // Log performance metrics
            if ('performance' in window && 'memory' in performance) {
                console.log('Memory usage:', {
                    used: Math.round(performance.memory.usedJSHeapSize / 1048576) + 'MB',
                    total: Math.round(performance.memory.totalJSHeapSize / 1048576) + 'MB',
                    limit: Math.round(performance.memory.jsHeapSizeLimit / 1048576) + 'MB'
                });
            }
        });
        
        // Monitor long tasks
        if ('PerformanceObserver' in window) {
            const observer = new PerformanceObserver((list) => {
                list.getEntries().forEach((entry) => {
                    if (entry.duration > 50) {
                        console.warn(`Long task detected: ${entry.duration}ms`);
                    }
                });
            });
            
            try {
                observer.observe({ entryTypes: ['longtask'] });
            } catch (e) {
                console.log('Long task monitoring not supported');
            }
        }
    }
    
    // Accessibility features
    setupAccessibility() {
        console.log('Setting up accessibility features...');
        
        // Focus management
        this.setupFocusManagement();
        
        // ARIA live regions
        this.setupAriaLiveRegions();
        
        // Skip link functionality
        this.setupSkipLinks();
        
        // Color contrast checking (development only)
        this.checkColorContrast();
    }
    
    // Focus management
    setupFocusManagement() {
        // Add focus indicators
        const style = document.createElement('style');
        style.textContent = `
            :focus {
                outline: 2px solid var(--primary-color);
                outline-offset: 2px;
            }
            
            .focus-trap {
                outline: 2px solid var(--primary-color);
                outline-offset: 2px;
            }
        `;
        document.head.appendChild(style);
        
        // Trap focus in mobile menu
        this.elements.navToggle.addEventListener('click', () => {
            if (this.state.isMenuOpen) {
                this.trapFocus(this.elements.navMenu);
            }
        });
    }
    
    // Trap focus within element
    trapFocus(element) {
        const focusableElements = element.querySelectorAll(
            'a[href], button, textarea, input[type="text"], input[type="email"], input[type="tel"], select, [tabindex]:not([tabindex="-1"])'
        );
        
        const firstElement = focusableElements[0];
        const lastElement = focusableElements[focusableElements.length - 1];
        
        element.addEventListener('keydown', (e) => {
            if (e.key === 'Tab') {
                if (e.shiftKey) {
                    if (document.activeElement === firstElement) {
                        lastElement.focus();
                        e.preventDefault();
                    }
                } else {
                    if (document.activeElement === lastElement) {
                        firstElement.focus();
                        e.preventDefault();
                    }
                }
            }
        });
    }
    
    // Setup ARIA live regions
    setupAriaLiveRegions() {
        // Create live region for announcements
        const liveRegion = document.createElement('div');
        liveRegion.setAttribute('aria-live', 'polite');
        liveRegion.setAttribute('aria-atomic', 'true');
        liveRegion.className = 'sr-only';
        liveRegion.style.cssText = `
            position: absolute;
            width: 1px;
            height: 1px;
            padding: 0;
            margin: -1px;
            overflow: hidden;
            clip: rect(0, 0, 0, 0);
            white-space: nowrap;
            border: 0;
        `;
        document.body.appendChild(liveRegion);
        
        // Announce important changes
        this.announce = (message) => {
            liveRegion.textContent = message;
            setTimeout(() => {
                liveRegion.textContent = '';
            }, 1000);
        };
    }
    
    // Setup skip links
    setupSkipLinks() {
        const skipLink = document.querySelector('.skip-link');
        if (skipLink) {
            skipLink.addEventListener('click', (e) => {
                e.preventDefault();
                const target = document.querySelector(skipLink.getAttribute('href'));
                if (target) {
                    target.focus();
                    target.scrollIntoView();
                }
            });
        }
    }
    
    // Check color contrast (development only)
    checkColorContrast() {
        // This would be implemented with a color contrast library
        // For now, just log that it's being checked
        console.log('Color contrast checking would be implemented here');
    }
}

// Initialize portfolio app when DOM is ready
const portfolioApp = new PortfolioApp();

// Export for potential module usage
if (typeof module !== 'undefined' && module.exports) {
    module.exports = PortfolioApp;
}

// Console welcome message
console.log('%c Portfolio App Loaded Successfully! ', 'background: #667eea; color: white; font-size: 16px; padding: 10px; border-radius: 5px;');
console.log('%c Built with modern JavaScript and best practices ', 'background: #28a745; color: white; font-size: 14px; padding: 8px; border-radius: 5px;');
