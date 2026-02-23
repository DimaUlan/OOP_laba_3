#include <gtest/gtest.h>
#include "Array.h"
#include "Trapezoid.h"
#include "Rhombus.h"
#include "Pentagon.h"

std::unique_ptr<Figure> createTrapezoid() {
    return std::make_unique<Trapezoid>(Point{0,0}, Point{4,0}, Point{3,3}, Point{1,3});
}

std::unique_ptr<Figure> createRhombus() {
    return std::make_unique<Rhombus>(Point{0,0}, Point{2,2}, Point{4,0}, Point{2,-2});
}

std::unique_ptr<Figure> createPentagon() {
    return std::make_unique<Pentagon>(Point{0,0}, Point{1,0}, Point{1,1}, Point{0,1}, Point{0.5,0.5});
}

TEST(ArrayTest, AddFigure) {
    Array arr;
    arr.addFigure(createTrapezoid().release());
    EXPECT_EQ(arr.size(), 1);
}

TEST(ArrayTest, Size) {
    Array arr;
    arr.addFigure(createRhombus().release());
    arr.addFigure(createPentagon().release());
    EXPECT_EQ(arr.size(), 2);
}

TEST(ArrayTest, GetFigureArea) {
    Array array;
    array.addFigure(new Rhombus(Point(0, 0), Point(1, 0), Point(1, 1), Point(0, 1)));

    const Figure* fig = array.get(0);
    ASSERT_NE(fig, nullptr);
    EXPECT_DOUBLE_EQ(fig->area(), 1.0);
}

TEST(ArrayTest, TotalArea) {
    Array arr;
    arr.addFigure(createTrapezoid().release()); 
    arr.addFigure(createRhombus().release());
    double total = arr.totalArea();
    EXPECT_GT(total, 0);
}

TEST(ArrayTest, RemoveAt) {
    Array arr;
    arr.addFigure(createPentagon().release());
    size_t sizeBefore = arr.size();
    arr.removeAt(0);
    EXPECT_EQ(arr.size(), sizeBefore - 1);
}

TEST(ArrayTest, PrintAll) {
    Array arr;
    arr.addFigure(createTrapezoid().release());
    EXPECT_NO_THROW(arr.printAll());
}

TEST(PentagonTest, Equality) {
    Point pts[5] = {
        Point{0, 0},
        Point{1, 0},
        Point{1, 1},
        Point{0, 1},
        Point{0.5, 0.5}
    };
    Pentagon p1(pts);
    Pentagon p2(pts);
    EXPECT_TRUE(p1 == p2);
}

TEST(RhombusTest, AreaCalculation) {
    Rhombus r(Point{0,0}, Point{2,2}, Point{4,0}, Point{2,-2});
    double area = r.area();
    EXPECT_NEAR(area, 8.0, 1e-6);
}

TEST(TrapezoidTest, GetCenter) {
    Trapezoid t(Point{0,0}, Point{4,0}, Point{3,3}, Point{1,3});
    Point c = t.getCenter();
    EXPECT_NEAR(c.x, 2.0, 1e-6);
    EXPECT_NEAR(c.y, 1.5, 1e-6);
}

TEST(RhombusTest, InequalityDifferentFigures) {
    Rhombus r(Point{0,0}, Point{2,2}, Point{4,0}, Point{2,-2});
    Trapezoid t(Point{0,0}, Point{4,0}, Point{3,3}, Point{1,3});
    EXPECT_FALSE(r == t);
}

int main(int argc, char **argv) {
    std::locale::global(std::locale("ru_RU.UTF-8"));
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}