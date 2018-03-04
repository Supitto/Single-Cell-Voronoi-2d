#ifndef POLIGON_HPP
#define POLIGON_HPP
#endif

#include <CGAL/Simple_cartesian.h>
#include "side.hpp"
#include <vector>

typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Line_2 Line_2;
typedef Kernel::Point_2 Point_2;

class Poligon
{
    public:
        Poligon();
        std::vector<Side> Sides;
        void Cut(Line_2,Point_2);
        bool IsInside(Point_2,Point_2);
        std::string ToString();
        std::string ToCSV();
        ~Poligon();
};