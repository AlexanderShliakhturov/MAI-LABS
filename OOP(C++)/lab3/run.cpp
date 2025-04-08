#include <iostream>

#include "include/containers/vector.hpp"
#include "src/containers/vector.cpp"
#include "include/containers/FiguresVector.hpp"

#include "include/figures/Rectangle.hpp"
#include "include/figures/Square.hpp"
#include "include/figures/Triangle.hpp"

using namespace figures;

int main() {
    FiguresVector figures_vector;

    Rectangle* rect = new Rectangle;
    std::cout << "Input rectangle coordinates" << std::endl;
    std::cin >> *rect;
    std::cout << *rect << std::endl;
    figures_vector.push_back(static_cast<Figure*>(rect));

    Rectangle* rectangle_ptr = new Rectangle(5, 3);
    Square* square_ptr = new Square(10);
    Triangle* triangle_ptr = new Triangle(10);

    figures_vector.push_back(static_cast<Figure*>(rectangle_ptr));
    figures_vector.push_back(static_cast<Figure*>(square_ptr));
    figures_vector.push_back(static_cast<Figure*>(triangle_ptr));

    figures_vector.print_geometric_center();
    figures_vector.print_area();
    figures_vector.print_perimeter();

    std::cout << std::endl << "Total area" << std::endl;
    std::cout << figures_vector.calculate_total_area() << std::endl;

    Rectangle* rectangle_ptr1 = new Rectangle(5, 5);
    Rectangle* rectangle_ptr2 = new Rectangle(4, 1);
    Square* square_ptr1 = new Square(4);
    Square* square_ptr2 = new Square(8);
    Triangle* triangle_ptr1 = new Triangle(2);
    Triangle* triangle_ptr2 = new Triangle(4);

    for (auto figure: {rectangle_ptr1, rectangle_ptr2})
        figures_vector.push_back(static_cast<Figure*>(figure));

    for (auto figure: {square_ptr1, square_ptr2})
        figures_vector.push_back(static_cast<Figure*>(figure));

    for (auto figure: {triangle_ptr1, triangle_ptr2})
        figures_vector.push_back(static_cast<Figure*>(figure));

    figures_vector.print_geometric_center();
    figures_vector.print_area();
    figures_vector.print_perimeter();

    std::cout << std::endl << "Total area" << std::endl;
    std::cout << figures_vector.calculate_total_area() << std::endl;

    figures_vector.erase(0);
    figures_vector.erase(2);

    figures_vector.print_geometric_center();
    figures_vector.print_area();
    figures_vector.print_perimeter();

    std::cout << std::endl << "Total area" << std::endl;
    std::cout << figures_vector.calculate_total_area() << std::endl;

    figures_vector.pop_back();
    figures_vector.pop_back();

    figures_vector.print_geometric_center();
    figures_vector.print_area();
    figures_vector.print_perimeter();

    std::cout << std::endl << "Total area" << std::endl;
    std::cout << figures_vector.calculate_total_area() << std::endl;

    return 0;
}