#include "../../include/figures/Triangle.hpp"

using namespace figures;

Triangle::Triangle(const Point& p1, const Point& p2, const Point& p3) {
    this->_point1 = p1;
    this->_point2 = p2;
    this->_point3 = p3;
    calculate_edges();

    if (!check_triangle(p1, p2, p3))
        throw std::invalid_argument("Given points do not form a triangle");
}

Triangle::Triangle(const Triangle& other) noexcept:
    _point1(other._point1), _point2(other._point2), _point3(other._point3) {
    calculate_edges();
}

Triangle::Triangle(const double side) {
    if (side <= 0) {
        throw std::invalid_argument("triangle side size should be more than zero");
    }

    this->_point1 = Point(0, 0);
    this->_point2 = Point(side / 2, side * sqrt(3) / 2);
    this->_point3 = Point(side, 0);
    calculate_edges();
}

Triangle::Triangle(Triangle&& other) noexcept {
    this->_point1 = std::move(other._point1);
    this->_point2 = std::move(other._point2);
    this->_point3 = std::move(other._point3);
    calculate_edges();
}

Triangle& Triangle::operator=(const Triangle& other) noexcept {
    if (this == &other) return *this;

    this->_point1 = other._point1;
    this->_point2 = other._point2;
    this->_point3 = other._point3;

    return *this;
}

Triangle& Triangle::operator=(Triangle&& other) noexcept {
    this->_point1 = std::move(other._point1);
    this->_point2 = std::move(other._point2);
    this->_point3 = std::move(other._point3);

    return *this;
}

figures::Point Triangle::calculate_geometric_center() const noexcept {
    Point geometric_center ((_point1.get_x_cord() + _point2.get_x_cord() + _point3.get_x_cord()) / 3,
                            (_point1.get_y_cord() + _point2.get_y_cord() + _point3.get_y_cord()) / 3);
    return geometric_center;
}

void Triangle::calculate_edges() noexcept {
    const int dx1_2 = _point1.get_x_cord() - _point2.get_x_cord();
    const int dy1_2 = _point1.get_y_cord() - _point2.get_y_cord();
    _edge1_2 = sqrt(dx1_2 * dx1_2 + dy1_2 * dy1_2);

    const int dx1_3 = _point1.get_x_cord() - _point3.get_x_cord();
    const int dy1_3 = _point1.get_y_cord() - _point3.get_y_cord();
    _edge1_3 = sqrt(dx1_3 * dx1_3 + dy1_3 * dy1_3);

    const int dx2_3 = _point2.get_x_cord() - _point3.get_x_cord();
    const int dy2_3 = _point2.get_y_cord() - _point3.get_y_cord();
    _edge2_3 = sqrt(dx2_3 * dx2_3 + dy2_3 * dy2_3);
}

double Triangle::calculate_perimeter() const noexcept {
    return _edge1_2 + _edge1_3 + _edge2_3;
}

double Triangle::calculate_area() const noexcept {
    const double p = calculate_perimeter() / 2;
    return sqrt(p * (p - _edge1_2) * (p - _edge1_3) * (p - _edge2_3));
}

const double Triangle::get_side(std::string sideName) const noexcept {
    if (sideName == "1_2") return _edge1_2;
    if (sideName == "1_3") return _edge1_3;
    if (sideName == "2_3") return _edge2_3;

    throw std::invalid_argument("no edge named: " + sideName);
}

Triangle::operator double() const {
    return calculate_area();
}

bool Triangle::operator==(const Triangle& other) const {
    return this->_point1 == other._point1 &&
           this->_point2 == other._point2 &&
           this->_point3 == other._point3;
}

bool Triangle::operator!=(const Triangle& other) const {
    return !(*this == other);
}

bool Triangle::check_triangle(const Point& p1, const Point& p2,
                                const Point& p3) const noexcept {
    const bool isValid = (_edge1_2 + _edge1_3 >= _edge2_3)
                    && (_edge1_2 + _edge2_3 >= _edge1_3)
                    && (_edge1_3 + _edge2_3 >= _edge1_2);
    const bool isAllPointOnOneLineX = p1.get_x_cord() == p2.get_x_cord() && p2.get_x_cord() == p3.get_x_cord();
    const bool isAllPointOnOneLineY = p1.get_y_cord() == p2.get_y_cord() && p2.get_y_cord() == p3.get_y_cord();
    return isValid && !isAllPointOnOneLineX && !isAllPointOnOneLineY;
}

namespace figures {
    std::istream& operator>>(std::istream& is, Triangle& triangle) {
        Point p1, p2, p3;
        is >> p1 >> p2 >> p3;
        triangle = Triangle(p1, p2, p3);
        return is;
    }

    std::ostream& operator<<(std::ostream& os, const Triangle& triangle) {
        os << "First point: " << triangle._point1 << std::endl;
        os << "Second point: " << triangle._point2 << std::endl;
        os << "Third point: " << triangle._point3 << std::endl;
        return os;
    }
}; // namespace figures