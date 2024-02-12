#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>

using namespace std;

class Contact {
public:
    string name;
    string phoneNumber;
    string relationship;

    Contact(const string& n, const string& phone, const string& rel)
        : name(n), phoneNumber(phone), relationship(rel) {}
};

class DataBase {
private:
    const string filename = "contacts.txt";

public:
    vector<Contact> contacts;

    void loadContacts() {
        ifstream inFile(filename);
        assert(inFile.is_open() && "Unable to open the file for reading.");

        string currentName, phoneNumber, relationship;

        while (inFile >> currentName >> phoneNumber >> relationship) {
            contacts.push_back(Contact(currentName, phoneNumber, relationship));
        }

        inFile.close();
    }

    void saveContacts() {
        ofstream outFile(filename);
        assert(outFile.is_open() && "Unable to open the file for writing.");

        for (const auto& contact : contacts) {
            outFile << contact.name << " " << contact.phoneNumber << " " << contact.relationship << endl;
        }

        outFile.close();
    }

    void AddContact(const Contact& contact) {
        contacts.push_back(contact);
        saveContacts();
        cout << "Contact added successfully." << endl;
    }

    void DeleteByName(const string& name) {
        auto it = find_if(contacts.begin(), contacts.end(),
            [name](const Contact& contact) { return contact.name == name; });

        if (it != contacts.end()) {
            contacts.erase(it);
            saveContacts();
            cout << "Contact deleted successfully." << endl;
        }
        else {
            cout << "Contact not found." << endl;
        }
    }

    void DeleteByPhoneNumber(const string& phoneNumber) {
        auto it = find_if(contacts.begin(), contacts.end(),
            [phoneNumber](const Contact& contact) { return contact.phoneNumber == phoneNumber; });

        if (it != contacts.end()) {
            contacts.erase(it);
            saveContacts();
            cout << "Contact deleted successfully." << endl;
        }
        else {
            cout << "Contact not found." << endl;
        }
    }

    void SearchByName(const string& name) {
        auto it = find_if(contacts.begin(), contacts.end(),
            [name](const Contact& contact) { return contact.name == name; });

        if (it != contacts.end()) {
            cout << "Contact found: " << it->name << " " << it->phoneNumber << " " << it->relationship << endl;
        }
        else {
            cout << "Contact not found." << endl;
        }
    }

    void SearchByPhoneNumber(const string& phoneNumber) {
        auto it = find_if(contacts.begin(), contacts.end(),
            [phoneNumber](const Contact& contact) { return contact.phoneNumber == phoneNumber; });

        if (it != contacts.end()) {
            cout << "Contact found: " << it->name << " " << it->phoneNumber << " " << it->relationship << endl;
        }
        else {
            cout << "Contact not found." << endl;
        }
    }

    void sortByName() {
        for (size_t i = 0; i < contacts.size() - 1; ++i) {
            for (size_t j = i + 1; j < contacts.size(); ++j) {
                if (contacts[j].name < contacts[i].name) {
                    swap(contacts[i], contacts[j]);
                }
            }
        }
    }

    void editName(const string& oldName, const string& newName) {
        auto it = find_if(contacts.begin(), contacts.end(),
            [oldName](const Contact& contact) { return contact.name == oldName; });

        if (it != contacts.end()) {
            it->name = newName;
            saveContacts();
            cout << "Name edited successfully." << endl;
        }
        else {
            cout << "Contact not found." << endl;
        }
    }

    void editPhoneNumber(const string& name, const string& newPhoneNumber) {
        auto it = find_if(contacts.begin(), contacts.end(),
            [name](const Contact& contact) { return contact.name == name; });

        if (it != contacts.end()) {
            it->phoneNumber = newPhoneNumber;
            saveContacts();
            cout << "Phone number edited successfully." << endl;
        }
        else {
            cout << "Contact not found." << endl;
        }
    }

    void displaySortedNames() {
        cout << "Sorted Names:\n";
        for (const auto& contact : contacts) {
            cout << contact.name << endl;
        }
    }

private:
};

void displayMenu() {
    cout << "1. Add Contact\n";
    cout << "2. Delete Contact by Name\n";
    cout << "3. Search Contact by Name\n";
    cout << "4. Sort Contacts by Name and Display\n";
    cout << "5. Edit Contact Name\n";
    cout << "6. Search Contact by Phone Number\n";
    cout << "7. Delete Contact by Phone Number\n";
    cout << "8. Edit Contact Phone Number\n";
    cout << "9. Exit\n";
}

int main() {
    DataBase myContacts;
    myContacts.loadContacts();

    int choice;
    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string name, phone, relationship;
            cout << "Enter contact name: ";
            cin >> name;
            cout << "Enter contact phone number: ";
            cin >> phone;
            cout << "Enter relationship: ";
            cin >> relationship;
            myContacts.AddContact(Contact(name, phone, relationship));
            break;
        }
        case 2: {
            string name;
            cout << "Enter the name of the contact to delete: ";
            cin >> name;
            myContacts.DeleteByName(name);
            break;
        }
        case 3: {
            string name;
            cout << "Enter the name of the contact to search: ";
            cin >> name;
            myContacts.SearchByName(name);
            break;
        }
        case 4:
            myContacts.sortByName();
            myContacts.displaySortedNames();
            break;
        case 5: {
            string oldName, newName;
            cout << "Enter the name of the contact to edit: ";
            cin >> oldName;
            cout << "Enter the new name: ";
            cin >> newName;
            myContacts.editName(oldName, newName);
            break;
        }
        case 6: {
            string phoneNumber;
            cout << "Enter the phone number of the contact to search: ";
            cin >> phoneNumber;
            myContacts.SearchByPhoneNumber(phoneNumber);
            break;
        }
        case 7: {
            string phoneNumber;
            cout << "Enter the phone number of the contact to delete: ";
            cin >> phoneNumber;
            myContacts.DeleteByPhoneNumber(phoneNumber);
            break;
        }
        case 8: {
            string name, newPhoneNumber;
            cout << "Enter the name of the contact to edit phone number: ";
            cin >> name;
            cout << "Enter the new phone number: ";
            cin >> newPhoneNumber;
            myContacts.editPhoneNumber(name, newPhoneNumber);
            break;
        }
        case 9:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 10);

    return 0;
}
