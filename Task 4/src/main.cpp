#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <sstream>
#include <vector>
using namespace std;

class TextData {
private:
    string fileName;
    string text;
    int numberOfVowels;
    int numberOfConsonants;
    int numberOfLetters;
    int numberOfSentences;
    string longestWord;

    bool isVowel(char ch) {
        ch = tolower(ch);
        return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u';
    }

public:
    TextData(const string& filePath) : fileName(filePath), numberOfVowels(0), numberOfConsonants(0),
                                       numberOfLetters(0), numberOfSentences(0) {
        ifstream file(filePath);
        if (file.is_open()) {
            stringstream buffer;
            buffer << file.rdbuf();
            text = buffer.str();
            file.close();
            processText();
        } else {
            cerr << "Failed to open the file: " << filePath << endl;
        }
    }

    void processText() {
        stringstream stream(text);
        string word;
        while (stream >> word) {
            if (word.length() > longestWord.length()) {
                longestWord = word;
            }
            for (char ch : word) {
                if (isalpha(ch)) {
                    numberOfLetters++;
                    if (isVowel(ch)) {
                        numberOfVowels++;
                    } else {
                        numberOfConsonants++;
                    }
                }
            }
        }
        for (char ch : text) {
            if (ch == '.' || ch == '?' || ch == '!') {
                numberOfSentences++;
            }
        }
    }

    string getFilename() const { return fileName; }
    string getText() const { return text; }
    int getNumberOfVowels() const { return numberOfVowels; }
    int getNumberOfConsonants() const { return numberOfConsonants; }
    int getNumberOfLetters() const { return numberOfLetters; }
    int getNumberOfSentences() const { return numberOfSentences; }
    string getLongestWord() const { return longestWord; }
    
    void printInfo() const {
        cout << "File Name: " << getFilename() << endl;
        cout << "Text Content: " << getText() << endl;
        cout << "Number of Vowels: " << getNumberOfVowels() << endl;
        cout << "Number of Consonants: " << getNumberOfConsonants() << endl;
        cout << "Number of Letters: " << getNumberOfLetters() << endl;
        cout << "Number of Sentences: " << getNumberOfSentences() << endl;
        cout << "Longest Word: " << getLongestWord() << endl;
        cout << "----------------------------------------" << endl;
    }
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Please provide at least one .txt file as a argument." << endl;
        return 1;
    }

    for (int i = 1; i < argc; ++i) {
        TextData textData(argv[i]);
        textData.printInfo();
    }

    return 0;
}
