#pragma once
#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>
#include <map>
#include <vector>
#include <string>

class MyString {
private:
    std::vector<char> str; //  вектор символов
    void toLowerCase(std::vector<char> &s) const;//// Преобразует вектор символов в нижний регистр
    bool isAlphaNumeric(char c) const;// Проверяет, является ли символ буквенно-цифровым или дефисом

public:
    MyString(); // базовый
    MyString(const char* s); //сишный
    MyString(const MyString& other); // копированный
    MyString& operator=(const MyString& other); // оператор
    ~MyString() = default;// деструктор
    MyString()

    int findSubstring(const char* substr);// Находит позицию подстроки
    std::map<std::string, int> getWordDistribution() const; // Возвращает распределения слов
    int countWords() const;// Считает количество слов
    bool loadFromFile(const char* filename); // Загружает данные строки из файла
    bool saveWordDistributionToFile(const char* filename) const; // Сохраняет распределение слов в файл
    void printWordDistribution() const; // Печатает распределение слов
    std::string getString() const; // Возвращает строку 
    std::vector<std::pair<std::string, int>> getWordDistributionVector() const; // Возвращает распределение слов в виде вектора пар
    void printSortedByAlphabet() const; // Печатает слова, отсортированные по алфавиту
    void printSortedByTextOrder() const; // Печатает слова в порядке их появления в тексте
    void printSortedByFrequency(bool descending = true) const; // Печатает слова, отсортированные по частоте
};

#endif 