
#include "Array.h"
#include "Figure.h"

Array::Array()
    : data(new std::unique_ptr<Figure>[4]), capacity(4), count(0) {}

Array::~Array() {
    for (size_t i = 0; i < count; ++i) {
        data[i].reset();
    }
    delete[] data;
}

void Array::resize() {
    size_t newCapacity = (capacity == 0) ? 4 : capacity * 2;
    auto newData = new std::unique_ptr<Figure>[newCapacity];

    for (size_t i = 0; i < count; ++i) {
        newData[i] = std::move(data[i]);
    }

    delete[] data;
    data = newData;
    capacity = newCapacity;
}

void Array::addFigure(Figure* figure) {
    if (count >= capacity) {
        resize();
    }
    data[count] = std::unique_ptr<Figure>(figure);
    ++count;
}

void Array::removeAt(size_t index) {
    if (index >= count) return;

    for (size_t i = index; i < count - 1; ++i) {
        data[i] = std::move(data[i + 1]);
    }
    --count;
}

size_t Array::size() const {
    return count;
}

const Figure* Array::get(size_t index) const {
    if (index >= count) {
        return nullptr;
    }
    return data[index].get();
}


std::unique_ptr<Figure>& Array::operator[](size_t index) {
    if (index >= count) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

const std::unique_ptr<Figure>& Array::operator[](size_t index) const {
    if (index >= count) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

void Array::set(size_t index, Figure* newFigure) {
    if (index >= count) throw std::out_of_range("Index out of range");
    data[index].reset(newFigure);
}

void Array::printAll() const {
    for (size_t i = 0; i < count; ++i) {
        std::cout << "Figure " << i << ": ";
        data[i]->print(std::cout);
    }
}

double Array::totalArea() const {
    double sum = 0.0;
    for (size_t i = 0; i < count; ++i) {
        sum += data[i]->area();
    }
    return sum;
}