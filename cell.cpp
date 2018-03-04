#include "cell.hpp"
#include <CGAL/number_utils.h> 
#include <iostream>

Cell::Cell(Point_2 c)
{
    this->Center = new Point_2(c);
    this->Sides = new Poligon();
}

void Cell::Cut(Point_2 p)
{ 
    Point_2 mid = CGAL::midpoint(*this->Center,p);
    Segment_2 aux = Segment_2(*this->Center,p);
    Vector_2 b = aux.to_vector().perpendicular(CGAL::LEFT_TURN);
    Line_2 l(mid,b);
    (*this->Sides).Cut(l,(*this->Center));
}

bool Cell::IsInside(Point_2 p)
{
    bool inside = true;

    for(int i = 0; i < (this->Sides)->Sides.size() && inside; i ++)
    {
        inside = this->Sides->Sides[i].inTheSameHyperplan(p,*this->Center);
    }
    return inside;
}
std::string Cell::ToString()
{
    double x = CGAL::to_double(this->Center->x());
    double y = CGAL::to_double(this->Center->y()); 
    return "Center : ("+std::to_string(x)+", "+std::to_string(y)+") \n"+this->Sides->ToString();
}

std::string Cell::ToCSV()
{
    double x = CGAL::to_double(this->Center->x());
    double y = CGAL::to_double(this->Center->y());    
    std::string s = "point,"+std::to_string(x)+","+std::to_string(y)+"\n" + this->Sides->ToCSV();;
    s.pop_back();
    return s;
}