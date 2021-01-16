#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>
#include <cstdlib>
using namespace std;

struct ContactBook {
    short identifier = 0;
    string firstName;
    string lastName;
    string phoneNumber;
    string email;
    string adress;
};

vector<ContactBook> loadAllContacts( vector<ContactBook> &contact ) {

    ContactBook newContact;
    string element;
    char sign = '|';
    short quantityOfContacts = 0;
    short elementNumber = 0;

    fstream file;
    file.open( "ContactBook.txt", ios::in );

    if ( file.good() ) {
        while( getline(file, element, sign) ) {
            switch( elementNumber ) {
            case 0:
                newContact.identifier = atoi( element.c_str() );
                break;
            case 1:
                newContact.firstName = element;
                break;
            case 2:
                newContact.lastName = element;
                break;
            case 3:
                newContact.phoneNumber = element;
                break;
            case 4:
                newContact.email = element;
                break;
            case 5:
                newContact.adress = element;
                break;
            }
            if ( elementNumber >= 5 ) {
                elementNumber = 0;
                contact.push_back( newContact );

                quantityOfContacts++;
            } else {
                elementNumber++;
            }
        }
    }
    file.close();

    return contact;
}

void initMenuBox() {
    system("cls");
    cout << "Ksiazka kontaktow: \n";;
    cout << "1. Wpisz kontakt \n";
    cout << "2. Wyszukaj kontakt po imieniu \n";
    cout << "3. Wyszukaj kontakt po nazwisku \n";
    cout << "4. Wyswietl wszystkie kontakty \n";
    cout << "5. Usun kontakt \n";
    cout << "6. Edytuj kontakt \n";
    cout << "9. Zamknij program" << endl;

}

void menuEdition() {
    system("cls");
    cout << "\n PODMENU EDYCYJNE \n\n";
    cout << "1 - Imie \n";
    cout << "2 - Nazwisko \n";
    cout << "3 - Numer telefonu \n";
    cout << "4 - Email \n";
    cout << "5 - Adres \n";
    cout << "6 - Powrot do menu" << endl;
}


vector<ContactBook> addContact( vector<ContactBook> &contact ) {

    string firstName, lastName, phoneNumber, email, adress;
    short identifier = 0;

    ContactBook newContact;
    fstream file;
    file.open( "ContactBook.txt", ios::out | ios::app );

    short numberOfElementsInContainer = contact.size();
    if ( numberOfElementsInContainer == 0 ) identifier = 0;
    else identifier = contact[numberOfElementsInContainer - 1].identifier;

    cout << "Podaj imie: ";
    cin.sync();
    getline(cin,  newContact.firstName);
    cout << "Podaj nazwisko: ";
    cin.sync();
    getline(cin,  newContact.lastName);
    cout << "Podaj numer telefonu: ";
    cin.sync();
    getline(cin,  newContact.phoneNumber);
    cout << "Podaj email: ";
    cin >>  newContact.email;
    cout << "Podaj adres: ";
    cin.sync();
    getline(cin,  newContact.adress);

    newContact.identifier = identifier + 1;
    contact.push_back( newContact );

    file << newContact.identifier << "|";
    file << newContact.firstName << "|";
    file << newContact.lastName << "|";
    file << newContact.phoneNumber << "|";
    file << newContact.email << "|";
    file << newContact.adress << "|" << endl;

    file.close();

    cout << "Kontakt wpisany! \n";
    Sleep(1000);
    system("pause");

    return contact;
}

void searchFirstName( vector<ContactBook> &contact ) {

    string searchedFirstName;
    cout << "Wyszukaj po imieniu \n";
    cout << "Wpisz imie: " << endl;
    cin >> searchedFirstName;

    for ( auto itr = contact.begin(); itr != contact.end(); itr++ ) {
        if( itr -> firstName == searchedFirstName ) {

            cout << itr -> identifier << '|';
            cout << itr -> firstName << '|';
            cout << itr -> lastName << '|';
            cout << itr -> email << '|';
            cout << itr -> phoneNumber << '|';
            cout << itr -> adress << '|' << endl;
        }
    }
    system("pause");
}

void searchLastName( vector<ContactBook> &contact ) {

    string searchedLastName;
    cout << "Wyszukaj po nazwisku \n";
    cout << "Wpisz nazwisko: " << endl;
    cin >> searchedLastName;

    for ( auto itr = contact.begin(); itr != contact.end(); itr++ ) {
        if( itr -> lastName == searchedLastName ) {

            cout << itr -> identifier << '|';
            cout << itr -> firstName << '|';
            cout << itr -> lastName << '|';
            cout << itr -> email << '|';
            cout << itr -> phoneNumber << '|';
            cout << itr -> adress << '|' << endl;
        }
    }
    system("pause");
}

void displayContacts( vector<ContactBook> &contact ) {

    cout << "\n TWOJE KONTAKTY \n\n";
    for ( auto itr = contact.begin(); itr != contact.end(); itr++ ) {
        cout << itr -> identifier << '|';
        cout << itr -> firstName << '|';
        cout << itr -> lastName << '|';
        cout << itr -> email << '|';
        cout << itr -> phoneNumber << '|';
        cout << itr -> adress << '|' << endl;
    }
    cout << "\n";

    system("pause");
}

void displayContactsBeforeRemove( vector<ContactBook> &contact ) {

    cout << "\n TWOJE KONTAKTY \n\n";

    for ( auto itr = contact.begin(); itr != contact.end(); itr++ ) {
        cout << itr -> identifier << '|';
        cout << itr -> firstName << '|';
        cout << itr -> lastName << '|';
        cout << itr -> email << '|';
        cout << itr -> phoneNumber << '|';
        cout << itr -> adress << '|' << endl;
    }
}

vector<ContactBook> updateTextFile ( vector<ContactBook> &contact ) {

    fstream file;
    file.open( "ContactBook.txt", ios::out | ios::trunc );

    short numberOfElementsInContainer = contact.size();

    for ( int i = 0; i < numberOfElementsInContainer; i++ ) {
        file << contact[i].identifier << '|';
        file << contact[i].firstName << '|';
        file << contact[i].lastName << '|';
        file << contact[i].email << '|';
        file << contact[i].phoneNumber << '|';
        file << contact[i].adress << '|' << endl;
    }
    file.close();
    return contact;
}

vector<ContactBook> removeContact( vector<ContactBook> &contact ) {

    char sign;
    short identifierContact = 0;

    displayContactsBeforeRemove( contact );

    cout << "\n Wpisz identyfikator kontaktu, ktory ma zostac usuniety z ksiazki kontaktow: ";
    cin >> identifierContact;

    short numberOfElementsInContainer = contact.size();

    for (int i = 0; i < numberOfElementsInContainer; i++) {

        if ( contact[i].identifier == identifierContact ) {

            cout << "Czy na pewno usunac: ";
            cout << contact[i].identifier << '|';
            cout << contact[i].firstName << '|';
            cout << contact[i].lastName << '|';
            cout << contact[i].email << '|';
            cout << contact[i].phoneNumber << '|';
            cout << contact[i].adress << '|' << endl;
            cout << "Jesli TAK -  wpisz 't' ";

            cin >> sign;
            if ( sign == 't' ) {

                for (int j = i; j < numberOfElementsInContainer-1; j++) {
                    contact[j].identifier = contact[j+1].identifier;
                    contact[j].firstName = contact[j+1].firstName;
                    contact[j].lastName = contact[j+1].lastName;
                    contact[j].email = contact[j+1].email;
                    contact[j].phoneNumber = contact[j+1].phoneNumber;
                    contact[j].adress = contact[j+1].adress;
                }
                contact.pop_back();
                updateTextFile( contact );
            } else
                return contact;
        }
    }
    system("pause");
    return contact;
}


vector<ContactBook> editContactFirstName( vector<ContactBook> contact, short identifier ) {

    string editedFirstName;
    short numberOfElementsInContainer = contact.size();

    for ( int i = 0; i < numberOfElementsInContainer; i++ ) {
        if ( contact[i].identifier == identifier ) {
            cout << "Wpisz nowe imie: ";
            cin >> editedFirstName;
            contact[i].firstName = editedFirstName;
            updateTextFile(contact);
        }
    }
    cout << "Aktualizacja kontaktu przeprowadzona \n";
    system("pause");

    return contact;
}

vector<ContactBook> editContactLastName( vector<ContactBook> contact, short identifier ) {

    string editedLastName;
    short numberOfElementsInContainer = contact.size();

    for ( int i = 0; i < numberOfElementsInContainer; i++ ) {
        if ( contact[i].identifier == identifier ) {
            cout << "Wpisz nowe nazwisko: ";
            cin >> editedLastName;
            contact[i].lastName = editedLastName;
            updateTextFile( contact );
        }
    }
    cout << "Aktualizacja kontaktu przeprowadzona \n";
    system("pause");

    return contact;
}

vector<ContactBook> editContactPhoneNumber( vector<ContactBook> contact, short identifier ) {

    string editedPhoneNumber;
    short numberOfElementsInContainer = contact.size();

    for ( int i = 0; i < numberOfElementsInContainer; i++ ) {
        if (contact[i].identifier == identifier) {
            cout << "Wpisz nowy numer telefonu: ";
            cin >> editedPhoneNumber;
            contact[i].phoneNumber = editedPhoneNumber;
            updateTextFile( contact );
        }
    }
    cout << "Aktualizacja kontaktu przeprowadzona \n";
    system("pause");

    return contact;
}

vector<ContactBook> editContactEmail( vector<ContactBook> contact, short identifier ) {

    string editedEmail;
    short numberOfElementsInContainer = contact.size();

    for ( int i = 0; i < numberOfElementsInContainer; i++ ) {
        if ( contact[i].identifier == identifier ) {
            cout << "Wpisz nowy email: ";
            cin >> editedEmail;
            contact[i].email = editedEmail;
            updateTextFile( contact );
        }
    }
    cout << "Aktualizacja kontaktu przeprowadzona \n";
    system("pause");

    return contact;
}


vector<ContactBook> editContactAdress( vector<ContactBook> contact, short identifier ) {

    string editedAdress;
    short numberOfElementsInContainer = contact.size();

    for ( int i = 0; i < numberOfElementsInContainer; i++ ) {
        if ( contact[i].identifier == identifier ) {
            cout << "Wpisz nowy adres: ";
            cin >> editedAdress;
            contact[i].adress = editedAdress;
            updateTextFile( contact );
        }
    }
    cout << "Aktualizacja kontaktu przeprowadzona \n";
    system("pause");

    return contact;
}


void showContactEditMenu( vector<ContactBook> &contact ) {

    short identifier = 0;
    char choice;

    menuEdition();

    cout << "Wpisz identyfikator kontaktu do edycji: ";
    cin >> identifier;
    cout << "\n Ktore dane chcesz zmienic (od 1 do 5) lub wcisnij 6-powrot do menu: ";
    cin >> choice;

    switch ( choice ) {
    case '1':
        contact = editContactFirstName( contact, identifier );
        break;
    case '2':
        contact = editContactLastName( contact, identifier );
        break;
    case '3':
        contact = editContactPhoneNumber( contact, identifier );
        break;
    case '4':
        contact = editContactEmail( contact, identifier );
        break;
    case '5':
        contact = editContactAdress( contact, identifier );
        break;
    case '6':
        initMenuBox();
        break;
    default:
        cout << "Nie ma takiej opcji w MENU!\n";
    }

}

int main() {

    vector<ContactBook> contact;
    contact = loadAllContacts( contact );
    char choice;

    do {
        initMenuBox();
        cin.clear();
        cin >> choice;
        switch ( choice ) {
        case '1':
            contact = addContact( contact );
            break;
        case '2':
            searchFirstName( contact );
            break;
        case '3':
            searchLastName( contact );
            break;
        case '4':
            displayContacts( contact );
            break;
        case '5':
            removeContact( contact );
            break;
        case '6':
            showContactEditMenu( contact );
            break;
        case '9':
            exit(0);
            break;
        default:
            cout << "Nie ma takiej opcji w MENU!\n";
        }

    } while( 1 );

return 0;
}












