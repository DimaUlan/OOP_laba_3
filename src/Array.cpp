#include "Array.h"
#include "Figure.h"
#include <algorithm>

Array::Array() : data(new std::unique_ptr<Figure>[2]), capacity(2), count(0) {}

Array::~Array() {
    delete[] data;
}

Array::Array(Array&& other) noexcept 
    : data(nullptr), capacity(0), count(0) {
    swap(other);
}

Array& Array::operator=(Array&& other) noexcept {
    if (this != &other) {
        swap(other);
    }
    return *this;
}

void Array::swap(Array& other) noexcept {
    std::swap(data, other.data);
    std::swap(capacity, other.capacity);
    std::swap(count, other.count);
}

void Array::resize() {
    size_t newCapacity = capacity * 2;
    auto newData = new std::unique_ptr<Figure>[newCapacity];
    
    for (size_t i = 0; i < count; ++i) {
        newData[i] = std::move(data[i]);
    }
    
    delete[] data;
    data = newData;
    capacity = newCapacity;
}

void Array::add(Figure* figure) {
    if (!figure) return;
    
    if (count >= capacity) {
        resize();
    }
    data[count] = std::unique_ptr<Figure>(figure);
    ++count;
}

void Array::remove(size_t index) {
    if (index >= count) {
        throw std::out_of_range("Index out of range");
    }
    
    for (size_t i = index; i < count - 1; ++i) {
        data[i] = std::move(data[i + 1]);
    }
    data[count - 1].reset();
    --count;
}

size_t Array::size() const {
    return count;
}

Figure* Array::operator[](size_t index) {
    if (index >= count) {
        throw std::out_of_range("Index out of range");
    }
    return data[index].get();
}

const Figure* Array::operator[](size_t index) const {
    if (index >= count) {
        throw std::out_of_range("Index out of range");
    }
    return data[index].get();
}

double Array::totalArea() const {
    double sum = 0.0;
    for (size_t i = 0; i < count; ++i) {
        sum += static_cast<double>(*data[i]);
    }
    return sum;
}

void Array::printAll() const {
    for (size_t i = 0; i < count; ++i) {
        std::cout << "Фигура " << i + 1 << ": " << *data[i];
        std::cout << "Центр: " << data[i]->getCenter() << std::endl;
        std::cout << "Площадь: " << data[i]->getArea() << std::endl;
        std::cout << std::endl;
    }
}