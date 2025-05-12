#include <iostream>
#include <string>
using namespace std;

struct Node {
    char ch;
    Node* next;
    Node(char c) {
        ch = c;
        next = nullptr;
    }
};

struct StringNode {
    string str;
    StringNode* next;
    StringNode(string s) {
        str = s;
        next = nullptr;
    }
};

// Character stack functions
void push(Node*& head, char ch) {
    Node* newNode = new Node(ch);
    newNode->next = head;
    head = newNode;
}

char pop(Node*& head) {
    if (!head) return '\0';
    Node* temp = head;
    char ch = temp->ch;
    head = head->next;
    delete temp;
    return ch;
}

int count(Node* head) {
    int c = 0;
    while (head != NULL) {
        c++;
        head = head->next;
    }
    return c;
}

string getText(Node* head) {
    string result = "";
    while (head != NULL) {
        result = head->ch + result;
        head = head->next;
    }
    return result;
}

void clear(Node*& head) {
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

// String stack functions
void pushString(StringNode*& head, string s) {
    StringNode* newNode = new StringNode(s);
    newNode->next = head;
    head = newNode;
}

string popString(StringNode*& head) {
    if (!head) return "";
    StringNode* temp = head;
    string val = temp->str;
    head = head->next;
    delete temp;
    return val;
}

int main() {
    Node* textStack = nullptr;
    Node* redoStack = nullptr;
    StringNode* inputStack = nullptr;
    StringNode* removedStrings = nullptr;
    string input;
    int choice;

    cout << "============================================\n";
    cout << "      Welcome to the Undo/Redo System!\n";
    cout << "============================================\n";

    while (true) {
        cout << "\n--------------- MENU ----------------";
        cout << "\n[1] Add Text";
        cout << "\n[2] Undo or Redo Character/String";
        cout << "\n[3] Display Current Status";
        cout << "\n[4] Exit";
        cout << "\n-------------------------------------";
        cout << "\nEnter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                cout << "Enter text to add: ";
                getline(cin, input);
                for (char ch : input) {
                    push(textStack, ch);
                }
                pushString(inputStack, input);
                clear(redoStack);
                cout << "\nText added as: \"" << getText(textStack) << "\"";
                break;
            }

            case 2: {  // Undo or Redo Character/String
                int subChoice;
                cout << "\nWould you like to undo or redo?\n";
                cout << "[1] Undo Character\n[2] Redo Character\n[3] Undo String\n[4] Redo String\nEnter choice: ";
                cin >> subChoice;
                cin.ignore();

                if (subChoice == 1) {
                    if (textStack != NULL) {
                        char undoChar = pop(textStack);
                        push(redoStack, undoChar);
                        cout << "\nRemoved character: '" << undoChar << "'";
                    } else {
                        cout << "\nNothing to undo.";
                    }
                } else if (subChoice == 2) {
                    if (redoStack != NULL) {
                        char redoChar = pop(redoStack);
                        push(textStack, redoChar);
                        cout << "\nRe-applied character: '" << redoChar << "'";
                    } else {
                        cout << "\nNothing to redo.";
                    }
                } else if (subChoice == 3) {
                    string lastStr = popString(inputStack);
                    if (lastStr == "") {
                        cout << "\nNo previous string to undo.";
                    } else {
                        cout << "\nUndoing string: \"" << lastStr << "\"";
                        // Only remove characters that are part of the textStack
                        for (char ch : lastStr) {
                            if (textStack != nullptr) {
                                char c = pop(textStack);
                                push(redoStack, c);
                            }
                        }
                    }
                } else if (subChoice == 4) {
                    string redoStr = popString(removedStrings);
                    if (redoStr == "") {
                        cout << "\nNo removed string to redo.";
                    } else {
                        cout << "\nRe-adding string: \"" << redoStr << "\"";
                        for (char ch : redoStr) {
                            push(textStack, ch);
                        }
                        pushString(inputStack, redoStr);  // Track it again
                        clear(redoStack);
                    }
                } else {
                    cout << "\nInvalid choice.";
                }
                break;
            }

            case 3: {  // Display Current Status
                cout << "\n--------------------------------------------";
                cout << "\nCurrent Text     : " << getText(textStack);
                cout << "\nUndo Available   : " << count(textStack);
                cout << "\nRedo Available   : " << count(redoStack);
                cout << "\n--------------------------------------------";
                break;
            }

            case 4: {  // Exit
                cout << "\nExiting the program...\n";
                clear(textStack);
                clear(redoStack);
                while (inputStack != nullptr) popString(inputStack);
                while (removedStrings != nullptr) popString(removedStrings);
                return 0;
            }

            default:
                cout << "\n[Error] Invalid choice! Please enter 1 to 4.";
        }
    }

    return 0;
}
