// Array.h
#ifndef ARRAY_H
#define ARRAY_H

#include <memory>
#include <cstddef>
#include <stdexcept>

class Figure;

class Array {
public:
    Array();
    ~Array();
    
    // Запрещаем копирование (unique_ptr не копируется)
    Array(const Array&) = delete;
    Array& operator=(const Array&) = delete;
    
    // Разрешаем перемещение
    Array(Array&& other) noexcept;
    Array& operator=(Array&& other) noexcept;
    
    void add(Figure* figure);           // Добавление фигуры (принимает владение)
    void remove(size_t index);           // Удаление по индексу
    size_t size() const;                 // Текущий размер
    
    // Доступ к фигурам
    Figure* operator[](size_t index);             // Неконстантный доступ
    const Figure* operator[](size_t index) const; // Константный доступ
    
    // Общие операции над массивом
    double totalArea() const;            // Суммарная площадь
    void printAll() const;                // Вывод всех фигур
    
private:
    std::unique_ptr<Figure>* data;       // Динамический массив умных указателей
    size_t capacity;                      // Вместимость
    size_t count;                         // Количество элементов
    
    void resize();                         // Увеличение вместимости
    void swap(Array& other) noexcept;      // Обмен для move-семантики
};

#endif