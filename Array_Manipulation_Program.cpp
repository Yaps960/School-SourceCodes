#include <iostream>
#include <string.h>
#include <cctype>
#include <conio.h>
#include <algorithm>

using namespace std;

void banner(){
    cout << " .d8b.  d8888b. d8888b.  .d8b.  db    db      .d88b.  d8888b. d88888b d8888b.  .d8b.  d888888b d888888b  .d88b.  d8b   db .d8888. \n";
    cout << "d8' `8b 88  `8D 88  `8D d8' `8b `8b  d8'     .8P  Y8. 88  `8D 88'     88  `8D d8' `8b `~~88~~'   `88'   .8P  Y8. 888o  88 88'  YP \n";
    cout << "88ooo88 88oobY' 88oobY' 88ooo88  `8bd8'      88    88 88oodD' 88ooooo 88oobY' 88ooo88    88       88    88    88 88V8o 88 `8bo.   \n";
    cout << "88~~~88 88`8b   88`8b   88~~~88    88        88    88 88~~~   88~~~~~ 88`8b   88~~~88    88       88    88    88 88 V8o88   `Y8b. \n";
    cout << "88   88 88 `88. 88 `88. 88   88    88        `8b  d8' 88      88.     88 `88. 88   88    88      .88.   `8b  d8' 88  V888 db   8D \n";
    cout << "YP   YP 88   YD 88   YD YP   YP    YP         `Y88P'  88      Y88888P 88   YD YP   YP    YP    Y888888P  `Y88P'  VP   V8P `8888Y' \n";
}

void menu(int x){
    for(int i = 0; i <= 13; i++){
        for(int j = 0; j < 5; j++){
            switch(j){
                case 0:
                    if(i%2==1)
                        cout << "(";
                    break;
                case 1:
                    if(x == i)
                        cout << "o";
                    else
                        cout << " ";
                        break;
                case 2:
                    if(i%2==1)
                        cout << ")";
                    break;
                case 4:
                    if(i == 1)
                        cout << "Display Array Contents";
                    else if(i == 3)
                        cout << "Insert Element";
                    else if(i == 5)
                        cout << "Delete Element";
                    else if(i == 7)
                        cout << "Swap Elements";
                    else if(i == 9)
                        cout << "Reverse Array";
                    else if(i == 11)
                        cout << "Find Element";
                    else if(i == 13)
                        cout << "Exit Program";
                    break;
                default:
                    cout << " ";
                    break;
            }
        }
        cout << '\n';
    }
    cout << "\nControls:\nW - up\nS - down\nE - Enter";
}

void displayArray(string *arr, int elements){
    for(int i = 0; i < elements; i++){
        cout << i << " - " << arr[i] << '\n';
    }
}

int insertElement(string *arr, int elements){
    if(elements == 20){
        cout << "Array is full!\n";
        system("pause");
        return elements;
    }
    string newWord;
    int option;
    system("cls");
    banner();
    cout << "Enter a new word: ";
    getline(cin, newWord);
    if(isalnum(newWord[0])){
        cout << "In what index?: ";
        cin >> option;
        if(option > elements || option < 1 || !option){
            cout << "Invalid Input\n";
            cin.clear();
            cin.ignore(256,'\n');
            system("pause");
            insertElement(arr, elements);
        }else{
            for(int i = elements - 1; i >= option; i--){

                arr[i+1] = arr[i];
            }
            arr[option] = newWord;
            cout << "Inserted Successfully!\n";
            system("pause");
            return elements + 1;
        }   
    }
    return elements;
}

int deleteElement(string *arr, int elements){
    int option;
    system("cls");
    banner();
    displayArray(arr, elements);
    cout << "What would you like to delete? ";
    cin >> option;
    if(option > elements || option < 0 || !option){
        cout << "Invalid Input\n";
        cin.clear();
        cin.ignore(256,'\n');
        system("pause");
        deleteElement(arr, elements);
    }else{
        for(int i = option; i <= elements; i++){
            arr[i] = arr[i+1];
        }
        cout << "Deleted Successfully!\n";
        system("pause");
        return elements - 1;
    }
}

void swapElements(string *arr, int elements){
    int option, option2;
    system("cls");
    banner();
    displayArray(arr, elements);
    cout << "\nFirst element to swap: ";
    cin >> option;
    if(option > elements || option < 0 || !option){
        cout << "Invalid Input\n";
        cin.clear();
        cin.ignore(256,'\n');
        system("pause");
        swapElements(arr, elements);
    }
    cout << "Second element to swap: ";
    cin >> option2;
    if(option2 > elements || option2 < 0 || !option){
        cout << "Invalid Input\n";
        cin.clear();
        cin.ignore(256,'\n');
        system("pause");
        swapElements(arr, elements);
    }
    string temp = arr[option];
    arr[option] = arr[option2];
    arr[option2] = temp;
    cout << "Swapped Successfully!\n";
    system("pause");
}

void reverseArray(string *arr, int elements){
    system("cls");
    banner();
    string temp;
    cout << "Before: \n";
    displayArray(arr, elements);
    for(int i = 0, j = elements - 1; i < j; i++, j--){
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
    cout << "\nAfter: \n";
    displayArray(arr, elements);
    system("pause");
}

void findElement(string *arr, int elements){
    string word, temp;
    system("cls");
    banner();
    cout << "What word are you looking for: ";
    getline(cin, word);
    if(isalnum(word[0])){
        for(int i = 0; i < elements; i++){
            transform(word.begin(), word.end(), word.begin(), ::tolower);
            temp = arr[i];
            transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
            if(word == temp){
                cout << arr[i] << " is at index " << i << ".\n";
                system("pause");
                return;
            }
        }
        cout << word << " is not in the array.\n";
        system("pause");
    }
}

int exitProgram(){
    system("cls");
    banner();
    cout << "\nMembers:\nYapan, Von Emil\nNavarro, Louise Rederick\n\nThank you!\n";
    system("pause");
    return 1;
}

int main(){
    int exitflag = 0;
    char choice;
    int x = 1;
    string words[20] = {"root", "sphere", "nervous", "demonstration", "employ", "disappear", "yearn", "respectable", "quiet", "strip"};
    int elements = 10;
    do{
        system("cls");
        banner();
        menu(x);
        choice = _getch();
        switch(choice){
            case 'w':
                if(x == 1)
                    x = 13;
                else
                    x -= 2;
                break;
            case 's':
                if(x == 13)
                    x = 1;
                else
                    x += 2;
                break;
            case 'e':
                if(x == 1){
                    system("cls");
                    banner();
                    displayArray(words, elements);
                    system("pause");
                }else if(x == 3){
                    elements = insertElement(words, elements);
                }else if(x == 5){
                    elements = deleteElement(words, elements);
                }else if(x == 7){
                    swapElements(words, elements);
                }else if(x == 9){
                    reverseArray(words, elements);
                }else if(x == 11){
                    findElement(words, elements);
                }else if(x == 13){
                    exitflag = exitProgram();
                }
                break;
            default:
                break;
        }
    }while(exitflag != 1);
    return 0;
}