#include <variant>
#include <iostream>
#include <cmath>

// 定义形状的基类和派生类
class Shape {
public:
    virtual ~Shape() {}
    virtual double getArea() const = 0;
};

class Circle : public Shape {
public:
    explicit Circle(double radius) : radius_(radius) {}
    double getArea() const override { return M_PI * radius_ * radius_; }

private:
    double radius_;
};

class Rectangle : public Shape {
public:
    Rectangle(double width, double height) : width_(width), height_(height) {}
    double getArea() const override { return width_ * height_; }

private:
    double width_, height_;
};

class Triangle : public Shape {
public:
    Triangle(double base, double height) : base_(base), height_(height) {}
    double getArea() const override { return 0.5 * base_ * height_; }

private:
    double base_, height_;
};

// 使用 std::variant 来存储不同类型的形状
using ShapeVariant = std::variant<Circle, Rectangle, Triangle>;

// 访问者类，用于计算并输出形状的面积
struct AreaCalculator {
    void operator()(const Circle& c) const {
        std::cout << "Circle area: " << c.getArea() << std::endl;
    }
    
    void operator()(const Rectangle& r) const {
        std::cout << "Rectangle area: " << r.getArea() << std::endl;
    }
    
    void operator()(const Triangle& t) const {
        std::cout << "Triangle area: " << t.getArea() << std::endl;
    }
};

int main() {
    ShapeVariant shapes[] = {
        Circle(5.0),
        Rectangle(4.0, 6.0),
        Triangle(3.0, 7.0)
    };

    for(const auto& shape : shapes) {
        std::visit(AreaCalculator{}, shape);
    }

    return 0;
}