#include <iostream>
#include <limits>
#include <memory>
#include "Array.h"
#include "Trapezoid.h"
#include "Rhombus.h"
#include "Pentagon.h"

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

template<typename T>
bool readNumber(T& value) {
    std::cin >> value;
    if (std::cin.fail()) {
        clearInput();
        return false;
    }
    return true;
}

bool readPoint(Point& p) {
    if (!readNumber(p.x) || !readNumber(p.y)) {
        std::cout << "Ошибка ввода координат\n";
        return false;
    }
    return true;
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    
    Array figures;
    std::cout << "Программа для работы с геометрическими фигурами\n";
    
    while (true) {
        std::cout << "\nВыберите действие:\n";
        std::cout << "1 - Добавить трапецию\n";
        std::cout << "2 - Добавить ромб\n";
        std::cout << "3 - Добавить пятиугольник\n";
        std::cout << "4 - Завершить ввод и перейти к операциям\n";
        std::cout << "Ваш выбор: ";
        
        int choice;
        if (!readNumber(choice)) {
            std::cout << "Некорректный ввод. введите число.\n";
            continue;
        }
        
        if (choice == 4) break;
        
        try {
            switch (choice) {
                case 1: {
                    std::cout << "Введите координаты 4 вершин трапеции (x y):\n";
                    Point p1, p2, p3, p4;
                    
                    std::cout << "Вершина 1: ";
                    if (!readPoint(p1)) continue;
                    std::cout << "Вершина 2: ";
                    if (!readPoint(p2)) continue;
                    std::cout << "Вершина 3: ";
                    if (!readPoint(p3)) continue;
                    std::cout << "Вершина 4: ";
                    if (!readPoint(p4)) continue;
                    
                    figures.add(new Trapezoid(p1, p2, p3, p4));
                    std::cout << "Трапеция добавлена.\n";
                    break;
                }
                
                case 2: {
                    std::cout << "Введите координаты 4 вершин ромба (x y):\n";
                    Point p1, p2, p3, p4;
                    
                    std::cout << "Вершина 1: ";
                    if (!readPoint(p1)) continue;
                    std::cout << "Вершина 2: ";
                    if (!readPoint(p2)) continue;
                    std::cout << "Вершина 3: ";
                    if (!readPoint(p3)) continue;
                    std::cout << "Вершина 4: ";
                    if (!readPoint(p4)) continue;
                    
                    figures.add(new Rhombus(p1, p2, p3, p4));
                    std::cout << "Ромб добавлен.\n";
                    break;
                }
                
                case 3: {
                    std::cout << "Введите координаты 5 вершин пятиугольника (x y):\n";
                    Point p1, p2, p3, p4, p5;
                    
                    std::cout << "Вершина 1: ";
                    if (!readPoint(p1)) continue;
                    std::cout << "Вершина 2: ";
                    if (!readPoint(p2)) continue;
                    std::cout << "Вершина 3: ";
                    if (!readPoint(p3)) continue;
                    std::cout << "Вершина 4: ";
                    if (!readPoint(p4)) continue;
                    std::cout << "Вершина 5: ";
                    if (!readPoint(p5)) continue;

                    figures.add(new Pentagon(p1, p2, p3, p4, p5));
                    std::cout << "Пятиугольник добавлен.\n";
                    break;
                }
                
                default:
                    std::cout << "введите число от 1 до 4.\n";
            }
        } catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << "\n";
            clearInput();
        }
    }
    
    if (figures.size() == 0) {
        std::cout << "\nНе было добавлено ни одной фигуры. Программа завершена.\n";
        return 0;
    }
    
    std::cout << "\n================================================\n";
    std::cout << "Добавленные фигуры:\n";
    figures.printAll();
    
    while (true) {
        std::cout << "\n================================================\n";
        std::cout << "Выберите операцию:\n";
        std::cout << "1 - Показать все фигуры\n";
        std::cout << "2 - Вычислить общую площадь\n";
        std::cout << "3 - Удалить фигуру по индексу\n";
        std::cout << "4 - Сравнить две фигуры\n";
        std::cout << "5 - Завершить программу\n";
        std::cout << "Ваш выбор: ";
        
        int choice;
        if (!readNumber(choice)) {
            std::cout << "Некорректный ввод.\n";
            continue;
        }
        
        if (choice == 5) break;
        
        try {
            switch (choice) {
                case 1: {
                    figures.printAll();
                    break;
                }
                
                case 2: {
                    double total = figures.totalArea();
                    std::cout << "Общая площадь всех фигур: " << total << "\n";
                    break;
                }
                
                case 3: {
                    std::cout << "Введите индекс фигуры для удаления (от 0 до " << figures.size() - 1 << "): ";
                    size_t index;
                    if (!readNumber(index)) break;
                    
                    figures.remove(index);
                    std::cout << "Фигура удалена.\n";
                    
                    if (figures.size() > 0) {
                        std::cout << "Осталось фигур: " << figures.size() << "\n";
                    } else {
                        std::cout << "Все фигуры удалены.\n";
                    }
                    break;
                }
                
                case 4: {
                    if (figures.size() < 2) {
                        std::cout << "Недостаточно фигур для сравнения.\n";
                        break;
                    }
                    
                    std::cout << "Введите индексы двух фигур для сравнения (от 0 до " << figures.size() - 1 << "): ";
                    size_t idx1, idx2;
                    if (!readNumber(idx1) || !readNumber(idx2)) break;
                    
                    if (*figures[idx1] == *figures[idx2]) {
                        std::cout << "Фигуры равны\n";
                    } else {
                        std::cout << "Фигуры различны\n";
                    }
                    break;
                }
                
                default:
                    std::cout << "введите число от 1 до 5.\n";
            }
        } catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << "\n";
        }
    }
    
    return 0;
}