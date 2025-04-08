#ifndef INC_3_LAB_TRIANGLE_H
#define INC_3_LAB_TRIANGLE_H

#include "../interfaces/figure.hpp"

namespace figures {
    class Triangle final : public Figure {
    private:
        Point _point1;
        Point _point2;
        Point _point3;

        double _edge1_2;
        double _edge1_3;
        double _edge2_3;
    public:
        Triangle() = default;
        Triangle(const Point &, const Point &, const Point &);
        Triangle(const double);
        Triangle(const Triangle &) noexcept;
        Triangle(Triangle &&) noexcept;

        virtual ~Triangle() = default;
        virtual figures::Point calculate_geometric_center() const noexcept override;
        virtual double calculate_perimeter() const noexcept override;
        virtual double calculate_area() const noexcept override;
        const double get_side(std::string) const noexcept;
        void calculate_edges() noexcept;
        virtual operator double() const override;

        Triangle &operator=(const Triangle &)noexcept;
        Triangle &operator=(Triangle &&) noexcept;
        bool operator==(const Triangle &) const;
        bool operator!=(const Triangle &) const;

        friend std::istream &operator>>(std::istream &, Triangle &);
        friend std::ostream &operator<<(std::ostream &, const Triangle &);
    private:
        bool check_triangle(const Point&, const Point&, const Point&) const noexcept;
    };
}

#endif //INC_3_LAB_TRIANGLE_H
