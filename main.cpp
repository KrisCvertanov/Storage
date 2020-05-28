#include <iostream>
#include "Storage.h"
using namespace std;


int main()
{
    std::cout << "Welcome to my storage! Please enter a command. If you want to check list with all commands, type 'help'." << std::endl;
    Storage storage;
    Vector<Section> tempSections;
    String command;
    char* dir = new(nothrow) char[1]; 
    if(dir == nullptr){
        throw ("No memory for dir!(main.cpp)");
    }
    bool fileOpened = false;
    cout << "> ";
    while (true) {
        cin >> command;
        if (command.getSize() == 0) continue;
        int brOfIntervals = 0, n = command.getSize(), numOfWords = 0;
        for (int i = 0; i < n; i++) {
            if (command[i] == ' ') brOfIntervals++;
        }
        char** wordsOfCommand = new(nothrow) char* [brOfIntervals + 1]; // dumite na komandata
        if (wordsOfCommand == nullptr) {
            delete[] dir;
            throw ("No memory for wordOfCommand!(main.cpp)");
        }
        int sizeOfWord = 0;
        for (int i = 0; i <= n; i++) {  // zadelyame pamet za dumite na comandata
            sizeOfWord++;
            if (command[i] == ' ' || command[i] == '\0') {
                wordsOfCommand[numOfWords] = new(nothrow) char[sizeOfWord];
                if (wordsOfCommand[numOfWords] == nullptr) {
                    delete[] dir;
                    for (int j = 0; j < numOfWords; j++) {
                        delete[] wordsOfCommand[j];
                    }
                    delete[] wordsOfCommand;
                    throw ("No memory for wordsOfCommand!(main.cpp)");
                }
                sizeOfWord = 0;
                numOfWords++;
            }
        }
        numOfWords = 0;
        int j = 0;
        for (int i = 0; i < n; i++) { // inicializirame dumite na komandata
            if (command[i] == ' ') {
                wordsOfCommand[numOfWords][j] = '\0';
                j = 0;
                i++;
                numOfWords++;
            }
            wordsOfCommand[numOfWords][j] = command[i];
            j++;
        }
        wordsOfCommand[numOfWords][j] = '\0';
        numOfWords++;

        // proverka koq e komandata
    
        if (strcmp(wordsOfCommand[0], "close") == 0 && numOfWords == 1) {
            if (fileOpened) storage.close(tempSections);
            else cout << "You haven't opened a file yet!" << endl;
        }
        else if (strcmp(wordsOfCommand[0], "save") == 0 && numOfWords == 1) {
            if (fileOpened) storage.save(dir, tempSections);
            else cout << "You haven't opened a file yet!" << endl;
        }
        else if (strcmp(wordsOfCommand[0], "help") == 0 && numOfWords == 1) storage.help();
        else if (strcmp(wordsOfCommand[0], "exit") == 0 && numOfWords == 1) {
            cout << "Exiting program..." << endl;
            return 0;
        }
        else if (strcmp(wordsOfCommand[0], "print") == 0 && numOfWords == 1) {
            if (fileOpened) storage.print();
            else cout << "You haven't opened a file yet!" << endl;
        }
        else if (strcmp(wordsOfCommand[0], "add") == 0 && numOfWords == 1) {
            if (fileOpened) storage.add(tempSections);
            else cout << "You haven't opened a file yet!" << endl;
        }
        else if (strcmp(wordsOfCommand[0], "remove") == 0 && numOfWords == 1) {
            if (fileOpened) storage.remove(tempSections);
            else cout << "You haven't opened a file yet!" << endl;
        }
        else if (strcmp(wordsOfCommand[0], "clean") == 0 && numOfWords == 1) {
            if (fileOpened) storage.clean(tempSections);
            else cout << "You haven't opened a file yet!" << endl;
        }
        else if (strcmp(wordsOfCommand[0], "open") == 0 && numOfWords == 2) {
            delete[] dir;
            int l = strlen(wordsOfCommand[1]);
            dir = new(nothrow) char[l + 1];
            if (dir == nullptr) {
                for (int j = 0; j < numOfWords; j++) {
                    delete[] wordsOfCommand[j];
                }
                delete[] wordsOfCommand;
                throw ("No memory for dir!(main.cpp)");
            }
            for (int i = 0; i < l; i++) { // vzemame direktoriyata ot 2rata duma na komandata
                dir[i] = wordsOfCommand[1][i];
            }
            dir[l] = '\0';
            fileOpened = true;
            storage.open(dir, tempSections);
        }
        else if (strcmp(wordsOfCommand[0], "saveas") == 0 && numOfWords == 2) {
            if (fileOpened) storage.saveas(wordsOfCommand[1], tempSections);
            else cout << "You haven't opened a file yet!" << endl;
        }
        else if (strcmp(wordsOfCommand[0], "log") == 0 && numOfWords == 3) {
            if (fileOpened) storage.log(wordsOfCommand[1], wordsOfCommand[2]);
            else cout << "You haven't opened a file yet!" << endl;
        }
        else cout << "That command does not exist! Please enter a valid one." << endl;

        for (int i = 0; i < numOfWords; i++) {
            delete[] wordsOfCommand[i];
        }
        delete[] wordsOfCommand;
        command.clear();
        cout << "> ";
    }
    delete[] dir;
    
    return 0;
}
