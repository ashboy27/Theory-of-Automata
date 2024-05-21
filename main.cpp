#include "Dictionary.h"
#include "Button.h"
#include "TextEditor.h"
#include <fstream>



int main() {

    // Load dictionary words
    ifstream file("Words.txt");

    if (!file.is_open()) {
        cerr << "Unable to open file." << endl;
        return 0;
    }

    vector<string> words;
    string individualWords;

    while(file >> individualWords) { // Read words from file
        words.push_back(individualWords); // Store each word in the vector
    }
    file.close();

    Dictionary myD;

    for (const auto &w : words) {
        myD.add(w);
    }

    TextEditor myEditor(myD);   //Dictionary is passed to text editor class
    myEditor.run();


    return 0;
}