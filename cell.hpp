
#ifndef CELL_HPP 
#define CELL_HPP
#endif

#include "poligon.hpp"
#include <CGAL/Simple_cartesian.h>

typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Point_2 Point_2;
typedef Kernel::Line_2 Line_2;
typedef Kernel::Vector_2 Vector_2;

class Cell
{
    public:
        Point_2 * Center;
        Poligon * Sides;
        void Cut(Point_2);
        Cell(Point_2);
        bool IsInside(Point_2);
        std::string ToString();
        std::string ToCSV();
};