#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <chrono>

using namespace std;

// Определите структуру для хранения информации о частоте слов
struct WordFreq {
    string word;
    int freq;
};

// Определите функцию для преобразования строки в слова
vector<string> tokenize(string str) {
    vector<string> tokens;
    stringstream ss(str);
    string token;
    while (ss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

// Определите функцию для подсчета частоты слов в векторе
unordered_map<string, int> countWords(vector<string> words) {
    unordered_map<string, int> freqMap;
    for (string word : words) {
        freqMap[word]++;
    }
    return freqMap;
}

// Определите функцию для сравнения объектов WordFreq по частоте
bool compareWordFreq(const WordFreq& a, const WordFreq& b) {
    return a.freq > b.freq;
}

// Определите функцию для поиска слов в текстовом файле
vector<WordFreq> searchWords(string filename, string query) {
    // Открытие файла
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open file " << filename << endl;
        return {};
    }

    // Считывание файла в строчку
    stringstream buffer;
    buffer << file.rdbuf();
    string text = buffer.str();

    // Преобразование текста в слова
    vector<string> words = tokenize(text);

    // Подсчёт частоты встречаемости слов
    unordered_map<string, int> freqMap = countWords(words);

    // Сортировка слов по частоте
    vector<WordFreq> wordFreqs;
    for (auto it : freqMap) {
        wordFreqs.push_back({it.first, it.second});
    }
    sort(wordFreqs.begin(), wordFreqs.end(), compareWordFreq);

    // Поиск по словам
    vector<WordFreq> results;
    for (WordFreq wordFreq : wordFreqs) {
        if (wordFreq.word.find(query) != string::npos) {
            results.push_back(wordFreq);
            if (results.size() >= 20) {
                break;
            }
        }
    }

    // Закрыть файл
    file.close();

    return results;
}

int main() {
    // Получаем имя файла и запрос от пользователя
    string filename, query;
    cout << "Enter the filename: ";
    getline(cin, filename);
    cout << "Enter the query: ";
    getline(cin, query);

    // Поиск нужных слов и измерение времи
    auto start = chrono::steady_clock::now();
    vector<WordFreq> results = searchWords(filename, query);
    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    double time_ms = chrono::duration<double, milli>(diff).count();

    // Вывести результат
    cout << "Results:" << endl;
    for (WordFreq wordFreq : results) {
        cout << wordFreq.word << " (" << wordFreq.freq << ")" << endl;
    }
    cout << "Time: " << time_ms << " ms" << endl;

    cout << "Работу выполнил: Ставничий Даниил Сергеевич, ФИТУ РПИб" << endl;

    return 0;
}