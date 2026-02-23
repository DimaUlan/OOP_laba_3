#include <iostream>
#include <limits>
#include "Figure.h"
#include "Trapezoid.h"
#include "Rhombus.h"
#include "Pentagon.h"
#include "Array.h"

bool readPoint(Point& p) {
    if (!(std::cin >> p.x >> p.y)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
    return true;
}

double totalArea(const Array& array) {
    double sum = 0.0;
    for (size_t i = 0; i < array.size(); ++i) {
        sum += array.get(i)->area();
    }
    return sum;
}

void removeFigureAt(Array& array, size_t index) {
    if (index >= array.size()) {
        std::cout << "Некорректный индекс." << std::endl;
        return;
    }
    array.removeAt(index);
}

void compareFiguresByNumber(const Array& array, size_t num1, size_t num2) {
    if (num1 >= array.size() || num2 >= array.size()) {
        std::cout << "Некорректные номера фигур.\n";
        return;
    }
    double area1 = static_cast<double>(*array.get(num1));
    double area2 = static_cast<double>(*array.get(num2));
    if (area1 == area2)
        std::cout << "Площади фигур " << num1 + 1 << " и " << num2 + 1 << " равны.\n";
    else if (area1 > area2)
        std::cout << "Площадь фигуры " << num1 + 1 << " больше, чем у фигуры " << num2 + 1 << ".\n";
    else
        std::cout << "Площадь фигуры " << num2 + 1 << " больше, чем у фигуры " << num1 + 1 << ".\n";
}


void moveFigure(Array& array, size_t from, size_t to) {
    if (from >= array.size() || to >= array.size()) {
        std::cout << "Некорректные номера фигур.\n";
        return;
    }
    array[to] = std::move(array[from]);
    std::cout << "Фигура перемещена с " << from + 1 << " на " << to + 1 << ".\n";
}

void copyFigure(Array& array, size_t from, size_t to) {
    if (from >= array.size() || to >= array.size()) {
        std::cout << "Некорректные номера фигур.\n";
        return;
    }
    array[to].reset(array[from]->clone());
    std::cout << "Фигура скопирована с " << from + 1 << " на " << to + 1 << ".\n";
}


int main() {
    std::locale::global(std::locale("ru_RU.UTF-8"));

    Array figures;

    while (true) {
        std::cout << "Выберите фигуру:\n 1 - трапеция,\n 2 - ромб,\n 3 - пятиугольник,\n 4 - закончить ввод фигур\n";
        int choice;
        std::cin >> choice;

        if (choice == 4) break;

        switch (choice) {
            case 1: {
                Point p1, p2, p3, p4;
                std::cout << "Введите 4 вершины трапеции (x y):\n";
                while (!readPoint(p1) || !readPoint(p2) || !readPoint(p3) || !readPoint(p4)) {
                    std::cout << "Некорректный ввод. Попробуйте снова:\n";
                }
                figures.addFigure(new Trapezoid(p1, p2, p3, p4));
                break;
            }
            case 2: {
                Point p1, p2, p3, p4;
                std::cout << "Введите 4 вершины ромба (x y):\n";
                while (!readPoint(p1) || !readPoint(p2) || !readPoint(p3) || !readPoint(p4)) {
                    std::cout << "Некорректный ввод. Попробуйте снова:\n";
                }
                figures.addFigure(new Rhombus(p1, p2, p3, p4));
                break;
            }
            case 3: {
                Point p1, p2, p3, p4, p5;
                std::cout << "Введите 5 вершин пятиугольника (x y):\n";

                std::cout << "Вершина 1: ";
                while (!readPoint(p1)) {
                    std::cout << "Некорректный ввод. Попробуйте снова для вершины 1:\n";
                }

                std::cout << "Вершина 2: ";
                while (!readPoint(p2)) {
                    std::cout << "Некорректный ввод. Попробуйте снова для вершины 2:\n";
                }

                std::cout << "Вершина 3: ";
                while (!readPoint(p3)) {
                    std::cout << "Некорректный ввод. Попробуйте снова для вершины 3:\n";
                }

                std::cout << "Вершина 4: ";
                while (!readPoint(p4)) {
                    std::cout << "Некорректный ввод. Попробуйте снова для вершины 4:\n";
                }

                std::cout << "Вершина 5: ";
                while (!readPoint(p5)) {
                    std::cout << "Некорректный ввод. Попробуйте снова для вершины 5:\n";
                }

                figures.addFigure(new Pentagon(p1, p2, p3, p4, p5));
                break;
            }
            default:
                std::cout << "Некорректный выбор. Попробуйте снова.\n";
                break;
        }
    }

    for (size_t i = 0; i < figures.size(); ++i) {
        std::cout << "Фигура " << i + 1 << ":\n";
        figures.get(i)->print(std::cout);
        auto center = figures.get(i)->getCenter();
        std::cout << "Центр: (" << center.x << ", " << center.y << ")\n";
        std::cout << "Площадь: " << static_cast<double>(*figures.get(i)) << "\n\n";
    }

    while (true) {
        std::cout << "Выберите:\n 1 - Общая площадь всех фигур\n 2 - Удаление фигуры по индексу\n 3 - сравнение площадей (==)\n 4 - перемещение\n 5 - присваивание\n 6 - завершить\n";
        int choice = 0;
        std::cin >> choice;

        if (choice == 6) break;

        switch (choice) {
            case 1: {
                std::cout << "Общая площадь всех фигур: " << totalArea(figures) << "\n";
                break;
            }
             case 2: {
                size_t indexToRemove;
                std::cout << "Введите индекс фигуры для удаления (0 - " << figures.size() - 1 << "): ";
                std::cin >> indexToRemove;
                removeFigureAt(figures, indexToRemove);

                if (figures.size() > 0) {
                    std::cout << "\nОставшиеся фигуры:\n";
                    for (size_t i = 0; i < figures.size(); ++i) {
                        std::cout << "Фигура " << i + 1 << ":\n";
                        figures.get(i)->print(std::cout);
                        auto center = figures.get(i)->getCenter();
                        std::cout << "Центр: (" << center.x << ", " << center.y << ")\n";
                        std::cout << "Площадь: " << static_cast<double>(*figures.get(i)) << "\n\n";
                    }
                } else {
                    std::cout << "\nВсе фигуры удалены.\n";
                }
                break;
            }
            case 3: {
                size_t num1, num2;
                std::cout << "Введите номера фигур для сравнения (начиная с 0): ";
                std::cin >> num1 >> num2;
                compareFiguresByNumber(figures, num1, num2);
                break;
            }
            case 4: {
                size_t from, to;
                std::cout << "Введите исходный индекс и целевой индекс (начиная с 0): ";
                std::cin >> from >> to;
                moveFigure(figures, from, to);
                break;
            }
            case 5: {
                size_t from, to;
                std::cout << "Введите исходный индекс и целевой индекс (начиная с 0): ";
                std::cin >> from >> to;
                copyFigure(figures, from, to);
                break;
            }
            default:
                std::cout << "Некорректный выбор. Попробуйте снова.\n";
                break;
        }
    }

    return 0;
}
