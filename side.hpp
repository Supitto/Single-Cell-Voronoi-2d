#ifndef SIDE_HPP
#define SIDE_HPP
#endif

#include <CGAL/Simple_cartesian.h>

typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Line_2 Line_2;
typedef Kernel::Ray_2 Ray_2;
typedef Kernel::Segment_2 Segment_2;
typedef Kernel::Point_2 Point_2;
typedef Kernel::Intersect_2 Intersect_2;
typedef Kernel::Vector_2 Vector_2;

class Side
{
    private:
        Line_2 * l = 0;
        bool isLine = false;
        Ray_2 * r = 0;
        bool isRay = false;
        Segment_2 * s = 0;
    public:
        /* The second argument stands for a code, it indicates if it is a line
        *  , a ray, or a segment. Represented by 0, 1 or 2.
        */
        Side(Point_2,Point_2,int);
        bool Cut(Line_2, Point_2); //The return of this method stands for
                                   //Do I still exist after the cut?
        bool inTheSameHyperplan(Line_2,Point_2,Point_2);
        bool inTheSameHyperplan(Point_2,Point_2);
        Point_2 * Intersection(Line_2);
        std::string ToString();
        std::string ToCSV();
        ~Side();
};