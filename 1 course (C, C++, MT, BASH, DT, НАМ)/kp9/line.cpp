#include "line.hpp"

Line::Line(ComplexNumber _key, string _data) { 
    key = _key;
    data = _data;
}

Line::Line() {
    key = ComplexNumber();
    data = "";
}