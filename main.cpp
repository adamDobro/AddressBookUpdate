#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <conio.h>
#include <vector>
#include <iterator>
#include <algorithm>
#include <sstream>

using namespace std;

struct Person {
    int idPerson, idUser;
    string name = "", surname = "", phone_number = "", email = "", address = "";
};

struct User {
    int idUser;
    string name = "", password = "";
};

string inputLine() {
    string input = "";
    cin.sync();
    getline(cin, input);
    return input;
}

int getInteger() {
    string input = "";
    int number = 0;

    while(true) {
        getline(cin, input);

        stringstream myStream(input);
        if(myStream >> number)
            break;
        cout << "To nie jest liczba. Wpisz ponownie." << endl;
    }
    return number;
}

char inputSign() {
    string input = "";
    char sign = {0};

    while(true) {
        getline(cin, input);

        if(input.length() == 1) {
            sign = input[0];
            break;
        }
        cout << "Wpisz pojedynczy znak!" << endl;
    }
    return sign;
}

string changeFirstLettertoCaptialAndRestToSmall(string text) {
    if (!text.empty()) {
        transform(text.begin(), text.end(), text.begin(), ::tolower);
        text[0] = toupper(text[0]);
    }
    return text;
}

int totalPersonQty() {
    fstream file;
    file.open("Adresaci.txt", ios::in);

    if (file.good() == false) {
        return 0;
    }

    string line;
    int lineQty = 0;
    while(!file.eof()) {
        getline(file, line);
        if (line != "") {
            lineQty++;
        }
    }
    file.close();
    return lineQty;
}

int checkLastPersonId() {
    int personQty = totalPersonQty();
    if (personQty == 0) {
        return 0;
    } else {
        fstream file;
        string line;
        file.open("Adresaci.txt", ios::in);
        for (int i = 0; i < personQty; i++ ) {
            if (i == personQty - 1) {
                getline(file,line,'|');
                file.close();
                return atoi(line.c_str());
            } else {
                getline(file,line);
            }
        }
    }
}

void addPersonToFile(vector<Person> &persons, int personQty) {
    fstream file;
    file.open("Adresaci.txt", ios::out | ios::app);

    file << persons[personQty].idPerson << "|";
    file << persons[personQty].idUser << "|";
    file << persons[personQty].name << "|";
    file << persons[personQty].surname << "|";
    file << persons[personQty].phone_number << "|";
    file << persons[personQty].email << "|";
    file << persons[personQty].address << endl;
    file.close();
}

void addPerson(vector<Person> &persons, int &personQty, int idLoggedUser) {
    string name, surname, phone_number, email, address;

    cout << "Podaj imie: ";
    name = inputLine();
    name = changeFirstLettertoCaptialAndRestToSmall(name);

    cout << "Podaj nazwisko: ";
    surname = inputLine();
    surname = changeFirstLettertoCaptialAndRestToSmall(surname);

    cout << "Podaj nr telefonu: ";
    phone_number = inputLine();

    cout << "Podaj adres e-mail: ";
    email = inputLine();

    cout << "Podaj adres: ";
    address = inputLine();

    persons.push_back(Person());

    int allPersonsQty = totalPersonQty();
    if (allPersonsQty == 0) {
        persons[personQty].idPerson = 1;
    } else {
        persons[personQty].idPerson = checkLastPersonId() + 1;
    }
    persons[personQty].idUser = idLoggedUser;
    persons[personQty].name = name;
    persons[personQty].surname = surname;
    persons[personQty].phone_number = phone_number;
    persons[personQty].email = email;
    persons[personQty].address = address;

    addPersonToFile(persons, personQty);
    personQty++;

    cout << endl << "Kontakt zostal dodany do ksiazki adresowej." << endl;
    Sleep(2000);
}

int readPersonsFromFile(vector<Person> &persons, int idLoggedUser) {
    fstream file;
    file.open("Adresaci.txt", ios::in);
    if (file.good() == false) {
        return 0;
    }
    string data, idPerson, idUser;
    int personQty = 0;

    while (!file.eof()) {
        getline(file,idPerson,'|');
        if (idPerson != "") {
            getline(file,idUser,'|');
            if(atoi(idUser.c_str()) == idLoggedUser) {
                persons.push_back(Person());
                persons[personQty].idPerson = atoi(idPerson.c_str());
                persons[personQty].idUser = atoi(idUser.c_str());
                getline(file,data,'|');
                persons[personQty].name = data;
                getline(file,data,'|');
                persons[personQty].surname = data;
                getline(file,data,'|');
                persons[personQty].phone_number = data;
                getline(file,data,'|');
                persons[personQty].email = data;
                getline(file,data);
                persons[personQty].address = data;
                personQty++;
            } else {
                getline(file,data,'|');
                getline(file,data,'|');
                getline(file,data,'|');
                getline(file,data,'|');
                getline(file,data);
            }
        }
    }
    file.close();
    return personQty;
}

void searchPersonByName(vector <Person> &persons) {

    int personQty;

    if(!persons.empty()) {

        cout << "Podaj imie: ";
        string inputName = inputLine();
        inputName = changeFirstLettertoCaptialAndRestToSmall(inputName);

        for(unsigned int i = 0; i < persons.size(); i++) {
            if (persons[i].name == inputName) {
                cout << "ID:             " << persons[i].idPerson << endl;
                cout << "Imie:           " << persons[i].name << endl;
                cout << "Nazwisko:       " << persons[i].surname << endl;
                cout << "Numer telefonu: " << persons[i].phone_number << endl;
                cout << "Email:          " << persons[i].email << endl;
                cout << "Adres:          " << persons[i].address << endl;
                personQty++;
            }
        }
        if(personQty == 0) {
            cout << endl << "Nie ma adresatow z tym imieniem" << endl;
        } else {
            cout << endl << "Ilosc adresatow z imieniem: >>> " << inputName << " <<<";
            cout << " w ksiazce adresowej wynosi: " << personQty << endl << endl;
        }
        system ("pause");
        system ("cls");
    }
}

void searchPersonBySurname(vector <Person> &persons) {

    int personQty;

    if(!persons.empty()) {
        cout << "Podaj nazwisko: ";
        string inputSurname = inputLine();
        inputSurname = changeFirstLettertoCaptialAndRestToSmall(inputSurname);

        for(unsigned int i = 0; i < persons.size(); i++) {
            if (persons[i].surname == inputSurname) {
                cout << "ID:             " << persons[i].idPerson << endl;
                cout << "Imie:           " << persons[i].name << endl;
                cout << "Nazwisko:       " << persons[i].surname << endl;
                cout << "Numer telefonu: " << persons[i].phone_number << endl;
                cout << "Email:          " << persons[i].email << endl;
                cout << "Adres:          " << persons[i].address << endl;
                personQty++;
            }
        }
        if(personQty == 0) {
            cout << endl << "Nie ma adresatow z tym nazwiskiem" << endl;
        } else {
            cout << endl << "Ilosc adresatow z nazwiskiem: >>> " << inputSurname << " <<<";
            cout << " w ksiazce adresowej wynosi: " << personQty << endl << endl;
        }
    }

    system ("pause");
    system ("cls");
}

void showAllPersons(vector <Person> &persons) {
    for(unsigned int i = 0; i < persons.size(); i++) {
        cout << "ID:             " << persons[i].idPerson << endl;
        cout << "Imie:           " << persons[i].name << endl;
        cout << "Nazwisko:       " << persons[i].surname << endl;
        cout << "Numer telefonu: " << persons[i].phone_number << endl;
        cout << "Email:          " << persons[i].email << endl;
        cout << "Adres:          " << persons[i].address << endl;
    }

    system ("pause");
    system ("cls");
}

void overWriteFileUsers(vector<User> users) {
    fstream file;
    file.open("Uzytkownicy.txt", ios::out);
    for (unsigned int i = 0; i < users.size(); i++) {
        if (i == 0) {
            file << users[i].idUser << "|";
        } else {
            file << endl << users[i].idUser << "|";
        }
        file << users[i].name << "|";
        file << users[i].password;
    }
    file.close();
}

void overWriteFilePersons (vector<Person> persons, vector<Person>::iterator itr, string action) {
    fstream file, fileTemp;
    file.open("Adresaci.txt", ios::in);
    fileTemp.open("Adresaci_temp.txt", ios::out);

    string line, idContact;
    while(!file.eof()) {
        getline(file,idContact,'|');
        getline(file,line);
        if (itr -> idPerson == atoi(idContact.c_str()) && action == "edit") {

            fileTemp << itr -> idPerson << "|";
            fileTemp << itr -> idUser << "|";
            fileTemp << itr -> name << "|";
            fileTemp << itr -> surname << "|";
            fileTemp << itr -> phone_number << "|";
            fileTemp << itr -> email << "|";
            fileTemp << itr -> address << endl;
        }

        else if (itr -> idPerson == atoi(idContact.c_str()) && action == "delete") {
            continue;
        } else if (atoi(idContact.c_str())) {
            fileTemp << idContact + "|" + line << endl;
        }
    }
    file.close();
    fileTemp.close();

    remove("Adresaci.txt");
    rename("Adresaci_temp.txt","Adresaci.txt");
}

void changePassword (vector<User> &users, int userQty, int idLoggedUser) {
    string password;
    cout << "Podaj nowe haslo: ";
    cin >> password;
    for( int i = 0; i < userQty; i++) {
        if (users[i].idUser == idLoggedUser) {
            users[i].password = password;
            overWriteFileUsers(users);
            cout << "Haslo zostalo zmienione." << endl;
            Sleep (1500);
        }
    }
}

void displayPerson(vector<Person> persons, vector<Person>::iterator itr) {
    cout << "ID:             " << itr -> idPerson << endl;
    cout << "Imie:           " << itr -> name << endl;
    cout << "Nazwisko:       " << itr -> surname << endl;
    cout << "Numer telefonu: " << itr -> phone_number << endl;
    cout << "Email:          " << itr -> email << endl;
    cout << "Adres:          " << itr -> address << endl << endl;
}

void deletePerson(vector <Person> &persons, int &personQty) {
    cout << "Podaj numer ID adresata do usuniecia: ";
    int inputID = getInteger();
    bool doesPersonExist = false;

    for (vector<Person>::iterator itr = persons.begin(); itr < persons.end(); itr++) {
        if (itr -> idPerson == inputID) {
            doesPersonExist = true;
            cout << "Kontakt do usuniecia: " << endl;
            displayPerson(persons,itr);
            cout << "Potwierdz wciskajac 't' lub wycofaj sie wciskajac 'n'." << endl;
            if (getch() == 't' || getch() == 'T') {
                overWriteFilePersons (persons, itr, "delete");
                persons.erase(itr);
                personQty--;
                cout << endl << "Kontakt zostal usuniety" << endl;
                Sleep(3000);
            } else if ((getch() == 'n' || getch() == 'N'))
                break;
        }
    }
    if(doesPersonExist == false) {
        cout << endl << "Uzytkownik o takim ID nie istnieje" << endl;
        Sleep(2000);
    }
}

void editPerson(vector <Person> &persons) {

    bool doesPersonExist = false;
    int inputID;
    char option;
    string newData;
    cout << "Podaj ID kontaktu do edycji: ";
    cin >> inputID;

    for (vector<Person>::iterator itr = persons.begin(); itr != persons.end(); itr++) {
        if (itr -> idPerson == inputID) {
            doesPersonExist = true;
            while(true) {
                system("cls");
                cout << "Kontakty do edycji" << endl;
                displayPerson(persons, itr);
                cout << endl << "Wybierz opcje do edycji: " << endl;
                cout << "1. Edytuj imie" << endl;
                cout << "2. Edytuj nazwisko" << endl;
                cout << "3. Edytuj numer telefonu." << endl;
                cout << "4. Edytuj email" << endl;
                cout << "5. Edytuj adres" << endl;
                cout << "6. Powrot do Menu" << endl << endl;
                cout << "Twoj wybor: ";
                option = inputSign();

                switch (option) {
                case '1': {
                    cout << "Podaj nowe imie: ";
                    getline(cin, newData);
                    itr -> name = newData;
                    newData = changeFirstLettertoCaptialAndRestToSmall(newData);
                    overWriteFilePersons(persons, itr, "edit");
                    cout << "Dane zostaly edytowane" << endl;
                    Sleep(1000);
                    continue;
                }

                case '2': {
                    cout << "Wprowadz nowe nazwisko: ";
                    getline(cin, newData);
                    itr -> surname = newData;
                    newData = changeFirstLettertoCaptialAndRestToSmall(newData);
                    overWriteFilePersons(persons, itr, "edit");
                    cout << "Dane zostaly edytowane" << endl;
                    Sleep(1000);
                    continue;
                }

                case '3': {
                    cout << "Wprowadz nowy numer telefonu: ";
                    getline(cin, newData);
                    itr -> phone_number = newData;
                    overWriteFilePersons(persons, itr, "edit");
                    cout << "Dane zostaly edytowane" << endl;
                    Sleep(1000);
                    continue;
                }


                case '4': {
                    cout << "Wprowadz nowy email: ";
                    getline(cin, newData);
                    itr -> email = newData;
                    overWriteFilePersons(persons, itr, "edit");
                    cout << "Dane zostaly edytowane" << endl;
                    Sleep(1000);
                    continue;
                }

                case '5': {
                    cout << "Wprowadz nowy adres: ";
                    getline(cin, newData);
                    itr -> address = newData;
                    overWriteFilePersons(persons, itr, "edit");
                    cout << "Dane zostaly edytowane" << endl;
                    Sleep(1000);
                    continue;
                    break;
                }

                case '6': {
                    break;
                }
                }
                break;
            }
        }
    }
    if(doesPersonExist == false) {
        cout << endl << "Uzytkownik o takim ID nie istnieje" << endl;
        Sleep(2000);
    }
}

int readUsersFromFile(vector<User> &users) {
    fstream file;
    file.open("Uzytkownicy.txt", ios::in);
    if (file.good() == 0) {
        return 0;
    }

    string data;
    int userQty = 0;
    while(!file.eof()) {
        getline(file, data, '|');
        if(data != "") {
            users.push_back(User());
            users[userQty].idUser = atoi(data.c_str());
            getline(file, data,'|');
            users[userQty].name = data;
            getline(file, data);
            users[userQty].password = data;
            userQty++;
        }
    }
    file.close();
    return userQty;
}

void addUserToFile (vector<User> users, int userQty) {
    fstream file;
    file.open("Uzytkownicy.txt", ios::out | ios::app);


    if (userQty == 0) {
        file << users[userQty].idUser << "|";
    } else {
        file << endl << users[userQty].idUser << "|";
    }
    file << users[userQty].name << "|";
    file << users[userQty].password;
    file.close();
}

int registration (vector<User> &users, int userQty) {
    string name, password;
    cout << "Podaj nazwe uzytkownika: ";
    cin >> name;
    vector<User>::iterator itr = users.begin();
    while (itr != users.end()) {
        if (itr -> name == name) {
            cout << "Uzytkownik o takiej nazwie juz istnieje. Wpisz inna nazwe uzytkownika: ";
            cin >> name;
            itr = users.begin();
        } else
            itr++;
    }
    cout << "Podaj haslo: ";
    cin >> password;
    users.push_back(User());
    users[userQty].name = name;
    users[userQty].password = password;
    users[userQty].idUser = userQty+1;
    cout << "Konto zostalo utworzone" << endl;
    Sleep(1000);
    addUserToFile (users, userQty);
    return ++userQty;
}

int loggingIn (vector<User> &users, int userQty) {
    string name, password;
    cout << "Podaj nazwe uzytkownika: ";
    cin >> name;

    vector<User>::iterator itr = users.begin();
    while (itr != users.end()) {
        if (itr -> name == name) {
            for (int j = 0; j < 3; j++) {
                cout << "Podaj haslo (pozostalo " << 3-j << " prob): ";
                cin >> password;
                if (itr -> password == password) {
                    cout << "Zalogowales sie." << endl;
                    Sleep (1000);
                    return itr -> idUser;
                }
            }
            cout << "Podales bledne haslo. Poczekaj 3 sekundy przed kolejna proba." << endl;
            Sleep (3000);
            return 0;
        }
        itr++;
    }
    cout << "Nie ma uzytkownika o takiej nazwie" << endl;
    Sleep (1500);
    return 0;
}

void goToAdrressBook(vector<User> &users, int &userQty, int idLoggedUser) {
    vector <Person> persons;
    char option;

    int personQty = readPersonsFromFile(persons, idLoggedUser);

    while(true) {
        system("cls");
        cout << ">>> KSIAZKA ADRESOWA <<<" << endl;
        cout << "------------------------" << endl;
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkich adresatow" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "------------------------" << endl;
        cout << "7. Zmien haslo" << endl;
        cout << "8. Wyloguj sie" << endl;
        cout << "------------------------" << endl;
        cout << "Twoj wybor: ";
        option = inputSign();

        // próbowa³em tê czêœæ zrobiæ na switchu ale nie dzia³a wtedy opcja wylogowania u¿ytkownika st¹d if i else if

        if (!(option == '1' || option == '8' || option == '7') &&  personQty == 0) {
            cout << "Ksiazka adresowa jest pusta!" << endl << "Dodaj plik \"Adresaci.txt\" lub dodaj nowe kontakty."<<endl;
            Sleep (4000);
        } else if (option == '1') {
            system ("cls");
            addPerson(persons, personQty, idLoggedUser);
        } else if (option == '2') {
            system ("cls");
            searchPersonByName(persons);
        } else if (option == '3') {
            system ("cls");
            searchPersonBySurname(persons);
        } else if (option == '4') {
            system ("cls");
            showAllPersons(persons);
        } else if (option == '5') {
            system ("cls");
            deletePerson(persons, personQty);
        } else if (option == '6') {
            system ("cls");
            editPerson(persons);
        } else if (option == '7') {
            changePassword(users, userQty, idLoggedUser);
        } else if (option == '8') {
            idLoggedUser = 0;
            break;
        }
    }
}

int main() {
    vector <User> users;
    int idLoggedUser = 0;
    int userQty = readUsersFromFile(users);
    char option;

    while(true) {
        system("cls");
        cout << ">>> MENU GLOWNE <<<" << endl;
        cout << "-------------------" << endl;
        cout << "1. Rejestracja" << endl;
        cout << "2. Logowanie" << endl;
        cout << "3. Zakoncz program" << endl;
        cout << "-------------------" << endl;
        cout << "Twoj wybor: ";
        option = inputSign();

        if (option == '1') {
            userQty = registration(users, userQty);
        } else if (option == '2') {
            idLoggedUser = loggingIn(users, userQty);
            if (idLoggedUser != 0) {
                goToAdrressBook(users, userQty,idLoggedUser);
            }
        } else if (option == '3') {
            cout << ">> Program zakonczyl prace <<" << endl;
            exit(0);
        }
    }
    return 0;
}
