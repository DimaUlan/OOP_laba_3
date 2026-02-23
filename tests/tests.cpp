#include <gtest/gtest.h>
#include <sstream>
#include <memory>
#include "Array.h"
#include "Pentagon.h"
#include "Rhombus.h"
#include "Trapezoid.h"

TEST(BasicTest, PointOperations) {
    Point p1(1, 2), p2(1, 2), p3(1, 3);
    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
    
    std::stringstream ss;
    ss << p1;
    EXPECT_EQ(ss.str(), "(1, 2)");
}

class FigureTest : public ::testing::Test {
protected:
    // Пятиугольник
    std::array<Point, 5> pentagonPoints = {
        Point(0,0), Point(2,0), Point(3,2), Point(1,3), Point(-1,1)
    };
    
    // Ромб
    std::array<Point, 4> rhombusPoints = {
        Point(0,1), Point(2,2), Point(4,1), Point(2,0)
    };
    
    // Трапеция
    std::array<Point, 4> trapezoidPoints = {
        Point(0,0), Point(4,0), Point(3,2), Point(1,2)
    };
};

TEST_F(FigureTest, Pentagon) {
    Pentagon p(pentagonPoints);
    Point center = p.getCenter();
    EXPECT_NEAR(center.x, 1.0, 1e-6);
    EXPECT_NEAR(center.y, 1.2, 1e-6);
    EXPECT_GT(p.getArea(), 0);
    
    Pentagon p2(p); // копирование
    EXPECT_TRUE(p == p2);
}

TEST_F(FigureTest, Rhombus) {
    Rhombus r(rhombusPoints);
    Point center = r.getCenter();
    EXPECT_NEAR(center.x, 2.0, 1e-6);
    EXPECT_NEAR(center.y, 1.0, 1e-6);
    EXPECT_NEAR(r.getArea(), 4.0, 1e-6);
}

TEST_F(FigureTest, Trapezoid) {
    Trapezoid t(trapezoidPoints);
    Point center = t.getCenter();
    EXPECT_NEAR(center.x, 2.0, 1e-6);
    EXPECT_NEAR(center.y, 1.0, 1e-6);
    EXPECT_NEAR(t.getArea(), 6.0, 1e-6);
}

TEST_F(FigureTest, Polymorphism) {
    std::unique_ptr<Figure> f1 = std::make_unique<Pentagon>(pentagonPoints);
    std::unique_ptr<Figure> f2 = std::make_unique<Rhombus>(rhombusPoints);
    
    EXPECT_NE(dynamic_cast<Pentagon*>(f1.get()), nullptr);
    EXPECT_NE(dynamic_cast<Rhombus*>(f2.get()), nullptr);
    EXPECT_FALSE(*f1 == *f2);
}

TEST(ArrayTest, AllOperations) {
    Array arr;
    EXPECT_EQ(arr.size(), 0);
    
    // Добавление
    arr.add(new Pentagon(Point(0,0), Point(2,0), Point(3,2), Point(1,3), Point(-1,1)));
    arr.add(new Rhombus(Point(0,1), Point(2,2), Point(4,1), Point(2,0)));
    arr.add(new Trapezoid(Point(0,0), Point(4,0), Point(3,2), Point(1,2)));
    EXPECT_EQ(arr.size(), 3);
    
    // Доступ
    EXPECT_NE(arr[0], nullptr);
    EXPECT_THROW(arr[10], std::out_of_range);
    
    // Площадь
    EXPECT_GT(arr.totalArea(), 0);
    
    // Удаление
    arr.remove(1);
    EXPECT_EQ(arr.size(), 2);
    EXPECT_THROW(arr.remove(10), std::out_of_range);
    
    // Перемещение
    Array arr2(std::move(arr));
    EXPECT_EQ(arr.size(), 0);
    EXPECT_EQ(arr2.size(), 2);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}