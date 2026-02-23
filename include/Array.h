#ifndef ARRAY_H
#define ARRAY_H

#include <memory>
#include <cstddef>

class Figure;

class Array {
public:
    Array();
    ~Array();

    void addFigure(Figure* figure);
    void removeAt(size_t index);
    size_t size() const;

    const Figure* get(size_t index) const;

    std::unique_ptr<Figure>& operator[](size_t index);
    const std::unique_ptr<Figure>& operator[](size_t index) const;
    void set(size_t index, Figure* newFigure);
    void printAll() const;
    double totalArea() const;

private:
    std::unique_ptr<Figure>* data;
    size_t capacity;
    size_t count;

    void resize();
};

#endif