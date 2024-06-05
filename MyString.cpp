
#include "MyString.h"
#include <fstream>
#include <cctype>
#include <algorithm>

MyString::MyString() {}

MyString::MyString(const char* s) {
    while (*s != '\0') {
        str.push_back(*s++);
    }
}

MyString::MyString(const MyString& other) : str(other.str) {}

MyString& MyString::operator=(const MyString& other) {
    if (this != &other) {
        str = other.str;
    }
    return *this;
}

void MyString::toLowerCase(std::vector<char> &s) const {
    for (char &c : s) {
        c = std::tolower(c);
    }
}

bool MyString::isAlphaNumeric(char c) const {
    return std::isalnum(static_cast<unsigned char>(c)) || c == '-';
}

int MyString::findSubstring(const char* substr) {
    size_t substrLen = 0;
    while (substr[substrLen] != '\0') {
        substrLen++;
    }
    if (substrLen == 0 || substrLen > str.size()) {
        return -1;
    }

    for (size_t i = 0; i <= str.size() - substrLen; i++) {
        size_t j = 0;
        while (j < substrLen && str[i + j] == substr[j]) {
            j++;
        }
        if (j == substrLen) {
            return i;
        }
    }
    return -1;
}

std::map<std::string, int> MyString::getWordDistribution() const {
    std::map<std::string, int> wordCount;
    std::vector<char> word;

    for (size_t i = 0; i <= str.size(); i++) {
        char c = (i < str.size()) ? str[i] : '\0';
        if (isAlphaNumeric(c)) {
            word.push_back(std::tolower(c));
        } else if (!word.empty()) {
            word.push_back('\0');
            wordCount[std::string(word.data())]++;
            word.clear();
        }
    }
    return wordCount;
}

std::vector<std::pair<std::string, int>> MyString::getWordDistributionVector() const {
    std::map<std::string, int> wordCount = getWordDistribution();
    std::vector<std::pair<std::string, int>> wordVector(wordCount.begin(), wordCount.end());
    return wordVector;
}

int MyString::countWords() const {
    std::map<std::string, int> wordCount = getWordDistribution();
    int totalWords = 0;
    for (const auto& pair : wordCount) {
        totalWords += pair.second;
    }
    return totalWords;
}

bool MyString::loadFromFile(const char* filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        return false;
    }
    file.seekg(0, std::ios::end);
    size_t length = file.tellg();
    file.seekg(0, std::ios::beg);
    str.resize(length);
    file.read(&str[0], length);
    file.close();
    return true;
}

bool MyString::saveWordDistributionToFile(const char* filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    std::map<std::string, int> wordCount = getWordDistribution();
    for (const auto& pair : wordCount) {
        file << pair.first << " - " << pair.second << std::endl;
    }
    file.close();
    return true;
}

void MyString::printWordDistribution() const {
    std::map<std::string, int> wordCount = getWordDistribution();
    for (const auto& pair : wordCount) {
        std::cout << pair.first << " - " << pair.second << std::endl;
    }
}

std::string MyString::getString() const {
    return std::string(str.begin(), str.end());
}

void MyString::printSortedByAlphabet() const {
    std::vector<std::pair<std::string, int>> wordVector = getWordDistributionVector();
    std::sort(wordVector.begin(), wordVector.end());
    for (const auto& pair : wordVector) {
        std::cout << pair.first << " - " << pair.second << std::endl;
    }
}

void MyString::printSortedByTextOrder() const {
    std::map<std::string, int> wordCount;
    std::vector<char> word;
    std::vector<std::string> wordsInOrder;

    for (size_t i = 0; i <= str.size(); i++) {
        char c = (i < str.size()) ? str[i] : '\0';
        if (isAlphaNumeric(c)) {
            word.push_back(std::tolower(c));
        } else if (!word.empty()) {
            word.push_back('\0');
            std::string wordStr(word.data());
            if (wordCount[wordStr] == 0) {
                wordsInOrder.push_back(wordStr);
            }
            wordCount[wordStr]++;
            word.clear();
        }
    }
    for (const auto& word : wordsInOrder) {
        std::cout << word << " - " << wordCount[word] << std::endl;
    }
}

void MyString::printSortedByFrequency(bool descending) const {
    std::vector<std::pair<std::string, int>> wordVector = getWordDistributionVector();
    if (descending) {
        std::sort(wordVector.begin(), wordVector.end(), [](const auto& a, const auto& b) {
            return b.second < a.second;
        });
    } else {
        std::sort(wordVector.begin(), wordVector.end(), [](const auto& a, const auto& b) {
            return a.second < b.second;
        });
    }
    for (const auto& pair : wordVector) {
        std::cout << pair.first << " - " << pair.second << std::endl;
    }
}

int main() {
    MyString s1;
    MyString s2;
    std::string fStr;

    std::cout << "Чтобы ввести строку нажмите 1 \n";
    std::cout << "Чтобы найти подстроку в строке нажмите 2 \n";
    std::cout << "Чтобы распределить строку по количеству уникальных слов нажмите 3 \n";
    std::cout << "Чтобы подсчитать количество слов в строке нажмите 4 \n";
    std::cout << "Чтобы вывести распределение слов в строке нажмите 5 \n";
    // std::cout << "Чтобы соединить строки нажмите 6 \n";
    
    int n;
    do {
        std::cin >> n;
        switch (n) {
        case 1:
        {
            std::cout << "Введите название файла: ";
            std::cin >> fStr;
            if (!s1.loadFromFile(fStr.c_str())) {
                std::cout << "Ошибка загрузки файла." << std::endl;
            }
        }
        break;
        case 2:
        {
            std::cout << "Введите искомую подстроку: \n";
            std::string substr; 
            std::cin >> substr;
            int index = s1.findSubstring(substr.c_str());
            std::cout << "Индекс: " << index << '\n';
        }
        break;
        case 3:
        {
            int order;
            std::cout << "Порядок слов в отображаемом результате может быть: \n"
                      << "1. Алфавитный\n"
                      << "2. По порядку слов в тексте\n"
                      << "3. По количеству вхождений: от большего к меньшему\n"
                      << "4. По количеству вхождений: от меньшего к большему\n"
                      << "Выберите желаемый порядок: ";
            std::cin >> order;
            switch (order) {
                case 1:
                    s1.printSortedByAlphabet();
                    break;
                case 2:
                    s1.printSortedByTextOrder();
                    break;
                case 3:
                    s1.printSortedByFrequency(true);
                    break;
                case 4:
                    s1.printSortedByFrequency(false);
                    break;
                default:
                    std::cout << "Неправильный выбор. Попробуйте еще раз.\n";
                    break;
            }
        }
        break;
        case 4:
        {
            std::cout << "Количество слов: " << s1.countWords() << '\n';
        }
        break;
        case 5:
        {
            int c1;
            std::cout << "Если хотите выгрузить распределение в txt-файл нажмите 1 \n"
                << "Если хотите выгрузить распределение в csv-файл нажмите 2 \n";
            std::cin >> c1;
            std::cout << "Введите название файла выгрузки: \n";
            std::string outputFilename; 
            std::cin >> outputFilename;
            if (c1 == 1) {
                if (!s1.saveWordDistributionToFile(outputFilename.c_str())) {
                    std::cout << "Ошибка сохранения в файл." << std::endl;
                }
            } else if (c1 == 2) {
                if (!s1.saveWordDistributionToFile(outputFilename.c_str())) {
                    std::cout << "Ошибка сохранения в файл." << std::endl;
                }
            } else {
                std::cout << "Неправильный выбор." << std::endl;
            }
        }
        break;
        // case 6:
        // {
        //     std::cout << "Введите название второго файла: ";
        //     std::string fStr1;
        //     std::cin >> fStr1;
        //     if (!s2.loadFromFile(fStr1.c_str())) {
        //         std::cout << "Ошибка загрузки файла." << std::endl;
        //     } else {
        //         std::string concatenatedStr = s1.getString() + s2.getString();
        //         std::cout << concatenatedStr << '\n';
        //     }1
        // }
        break;
        default:
            continue;
        }
    } while (n != 0);
    std::cout << "Программа завершена успешно. \n";

    return 0;
}

