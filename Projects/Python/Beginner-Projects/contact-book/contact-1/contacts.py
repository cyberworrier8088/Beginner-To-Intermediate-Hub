class Contact:
    """Contact class for managing contact information"""
    
    def __init__(self, name, phone, email=""):
        """Initialize contact with name, phone, and optional email"""
        self.name = name
        self.phone = phone
        self.email = email
    
    def __str__(self):
        """String representation of contact"""
        return f"Name: {self.name}, Phone: {self.phone}, Email: {self.email}"
    
    def update_info(self, phone=None, email=None):
        """Update contact information"""
        if phone:
            self.phone = phone
        if email:
            self.email = email

class ContactBook:
    """Contact book class for managing multiple contacts"""
    
    def __init__(self):
        """Initialize empty contact book"""
        self.contacts = []
    
    def add_contact(self, contact):
        """Add a new contact to the contact book"""
        # Check if contact with same name already exists
        for existing_contact in self.contacts:
            if existing_contact.name.lower() == contact.name.lower():
                print(f"Contact with name '{contact.name}' already exists!")
                return False
        
        self.contacts.append(contact)
        print(f"Contact '{contact.name}' added successfully!")
        return True
    
    def find_contact(self, name):
        """Find contact by name"""
        for contact in self.contacts:
            if contact.name.lower() == name.lower():
                return contact
        return None
    
    def update_contact(self, name, phone=None, email=None):
        """Update existing contact information"""
        contact = self.find_contact(name)
        if contact:
            contact.update_info(phone, email)
            print(f"Contact '{name}' updated successfully!")
            return True
        else:
            print(f"Contact '{name}' not found!")
            return False
    
    def delete_contact(self, name):
        """Delete contact from contact book"""
        contact = self.find_contact(name)
        if contact:
            self.contacts.remove(contact)
            print(f"Contact '{name}' deleted successfully!")
            return True
        else:
            print(f"Contact '{name}' not found!")
            return False
    
    def display_all_contacts(self):
        """Display all contacts in the contact book"""
        if not self.contacts:
            print("No contacts in the contact book!")
            return
        
        print("\n" + "="*60)
        print("ALL CONTACTS")
        print("="*60)
        for i, contact in enumerate(self.contacts, 1):
            print(f"{i}. {contact}")
        print("="*60)
    
    def search_contacts(self, search_term):
        """Search contacts by name or phone"""
        results = []
        search_term = search_term.lower()
        
        for contact in self.contacts:
            if (search_term in contact.name.lower() or 
                search_term in contact.phone):
                results.append(contact)
        
        return results

def display_menu():
    """Display contact book menu"""
    print("\n" + "="*40)
    print("CONTACT BOOK MANAGER")
    print("="*40)
    print("1. Add New Contact")
    print("2. View All Contacts")
    print("3. Search Contact")
    print("4. Update Contact")
    print("5. Delete Contact")
    print("6. Exit")
    print("="*40)

def get_non_empty_input(prompt):
    """Get non-empty input from user"""
    while True:
        value = input(prompt).strip()
        if value:
            return value
        print("This field cannot be empty!")

def main():
    """Main contact book application"""
    print("Welcome to Contact Book Manager!")
    print("================================")
    
    contact_book = ContactBook()
    
    while True:
        display_menu()
        choice = input("Enter your choice (1-6): ")
        
        if choice == '1':
            # Add new contact
            print("\n--- Add New Contact ---")
            name = get_non_empty_input("Enter name: ")
            phone = get_non_empty_input("Enter phone number: ")
            email = input("Enter email (optional): ").strip()
            
            contact = Contact(name, phone, email)
            contact_book.add_contact(contact)
        
        elif choice == '2':
            # View all contacts
            contact_book.display_all_contacts()
        
        elif choice == '3':
            # Search contact
            search_term = input("Enter name or phone to search: ").strip()
            results = contact_book.search_contacts(search_term)
            
            if results:
                print(f"\nFound {len(results)} contact(s):")
                for i, contact in enumerate(results, 1):
                    print(f"{i}. {contact}")
            else:
                print("No contacts found!")
        
        elif choice == '4':
            # Update contact
            name = get_non_empty_input("Enter name of contact to update: ")
            phone = input("Enter new phone (leave blank to keep current): ").strip()
            email = input("Enter new email (leave blank to keep current): ").strip()
            
            contact_book.update_contact(name, phone if phone else None, email if email else None)
        
        elif choice == '5':
            # Delete contact
            name = get_non_empty_input("Enter name of contact to delete: ")
            confirm = input(f"Are you sure you want to delete '{name}'? (yes/no): ").lower()
            
            if confirm == 'yes':
                contact_book.delete_contact(name)
            else:
                print("Deletion cancelled.")
        
        elif choice == '6':
            print("\nThank you for using Contact Book Manager!")
            print("Goodbye!")
            break
        
        else:
            print("Invalid choice! Please enter a number between 1 and 6.")
        
        input("\nPress Enter to continue...")

if __name__ == "__main__":
    main()
