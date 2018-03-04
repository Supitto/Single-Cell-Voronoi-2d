#include "side.hpp"
#include <stdexcept>
#include <CGAL/intersections.h>
#include <CGAL/number_utils.h> 
#include <iostream>
#include <boost/optional/optional_io.hpp>

Side::Side(Point_2 a, Point_2 b, int code)
{
    switch(code)
    {
        case 0:
            this->isLine = true;
            this->l = new Line_2(a,b);
            break;
        case 1:
            this->r = new Ray_2(a,b);
            this->isRay = true;
            break;
        case 2:
            this->s = new Segment_2(a,b);
            break;
        default:
            throw std::invalid_argument( "Code must be 0, 1, or 2" );
    }
}

bool Side::Cut(Line_2 l, Point_2 refer)
{
    bool DoIStillExist = true; //Such a vaporwave question, such a sad answer
    Point_2 * p = 0;
    if(this->isLine)
    {
        p = this->Intersection(l);
        if (p != 0) 
        {
            if(this->inTheSameHyperplan(l,*p+(*this->l).to_vector(),refer))
            {
                //std::cout<<"woof"<<std::endl;
                this->r = new Ray_2(*p,*p+(*this->l).to_vector());
            }
            else
            {
                this->r = new Ray_2(*p,*p-(*this->l).to_vector());

            }
            delete this->l;
            this->l = 0;
            this->isLine = false;
            this->isRay = true;
        }
        else //must be parallel
        {
            if(!this->inTheSameHyperplan(l, (*this->l).point(0), refer)) DoIStillExist = false;
        }
    }
    else if(this->isRay)
    {

        p = this->Intersection(l);
        if(p != 0)
        {
            if(this->inTheSameHyperplan(l,(*this->r).source(),refer))
            {
                this->s = new Segment_2((*this->r).source(),*p);
                delete this->r;
                this->r = 0;
                this->isRay = false;
                this->isLine = false;
            }
            else
            {
                this->r = new Ray_2(*p,*p+(*this->r).to_vector());
            }
        }
        else
        {
            if( ! this->inTheSameHyperplan(l, (*this->r).point(0), refer))    DoIStillExist = false;
        }
    }
    else
    {
        p = this->Intersection(l);
        if (p != 0) 
        {
            if(this->inTheSameHyperplan(l,(*this->s).source(),refer))
            {
                this->s = new Segment_2((*this->s).source(),*p);
            }
            else
            {
                this->s = new Segment_2((*this->s).target(),*p);
            }
        }
        else
        {
            if( ! this->inTheSameHyperplan(l, (*this->s).target(), refer))    DoIStillExist = false;
        }
    }
    if(p!=0)
    { 
        //std::cout<<*p<<std::endl; 
        delete p;
    }
    return DoIStillExist;
}

Side::~Side()
{
    this->r = 0;
    delete this->r;
    this->l = 0;
    delete this->l;
    this->s = 0;
    delete this->s;
}

Point_2 * Side::Intersection(Line_2 m )// no side effects
{
    //std::cout<<"DEBUG : in side -> intersection"<<std::endl;
    if(this->isLine)
    {
        //std::cout<<"DEBUG : inside in line code block"<<std::endl;
        CGAL::cpp11::result_of<Intersect_2(Line_2,Line_2)>::type v = intersection(m,*this->l);
        if(v)
        {
            Point_2 * p = boost::get<Point_2>(&*v);
            if (p!=0) 
            {
                //std::cout<<"DEBUG : out side -> intersection. Out with Segment"<<std::endl;
                Point_2 * temp;
                temp = new Point_2(p->x(),p->y());
                return temp;
            }
        }
    } 
    else if (this->isRay)
    {
        //std::cout<<"DEBUG : inside in ray code block"<<std::endl; 
        CGAL::cpp11::result_of<Intersect_2(Line_2,Ray_2)>::type v = intersection(m,*this->r);
        if(v)
        {
            Point_2 * p = boost::get<Point_2>(&*v);
            if (p!=0) 
            {
                //std::cout<<"DEBUG : out side -> intersection. Out with Segment"<<std::endl;
                Point_2 * temp;
                temp = new Point_2(p->x(),p->y());
                return temp;
            }
        }
    }
    else 
    {
        if(this->s == 0) throw "Side is not a segment";
        //std::cout<<"DEBUG : inside in segment code block"<<std::endl;
        CGAL::cpp11::result_of<Intersect_2(Line_2,Segment_2)>::type v = intersection(m,*this->s);
        if(v)
        {
            Point_2 * p = boost::get<Point_2>(&*v);
            if (p!=0) 
            {
                //std::cout<<"DEBUG : out side -> intersection. Out with Segment"<<std::endl;
                Point_2 * temp;
                temp = new Point_2(p->x(),p->y());
                return temp;
            }
        }
    }
    //std::cout<<"DEBUG : out side -> intersection. Out with null"<<std::endl;
    return 0; 
}

bool Side::inTheSameHyperplan(Line_2 l, Point_2 p, Point_2 q)
{
   Point_2 lp = l.point(0);
   Point_2 lq = l.point(1);
   return ((lp.y()-lq.y())*(p.x()-lp.x())+(lq.x()-lp.x())*(p.y()-lp.y()))*
            ((lp.y()-lq.y())*(q.x()-lp.x())+(lq.x()-lp.x())*(q.y()-lp.y())) >0 ;
}
bool Side::inTheSameHyperplan(Point_2 p, Point_2 ref)
{
    Line_2 l;
    if(this->isLine) 
    {
        return this->inTheSameHyperplan(Line_2(*this->l), p, ref);
    }
    else
    { 
        if (this->isRay) 
        {
            return this->inTheSameHyperplan(Line_2(*this->r), p, ref);
        }
        else
        {
            return this->inTheSameHyperplan(Line_2(*this->s), p, ref);
        }
    }
    return false;
}

std::string Side::ToString()
{
    std::string r = "";
    if(this->isLine)
    {
        double x1 = CGAL::to_double((*this->l).point(0).x()), x2 = CGAL::to_double((*this->l).point(1).x()), y1 = CGAL::to_double((*this->l).point(0).y()), y2 = CGAL::to_double((*this->l).point(1).y());
        r = "Line : ("+std::to_string(x1)+", "+std::to_string(y1)+"), ("+std::to_string(x2)+", "+std::to_string(y2)+") \n";
    }
    else if(this->isRay)
    {
        double x1 = CGAL::to_double((*this->r).source().x()), x2 = CGAL::to_double((*this->r).second_point().x()), y1 = CGAL::to_double((*this->r).source().y()), y2 = CGAL::to_double((*this->r).second_point().y());
        r = "Ray : ("+std::to_string(x1)+", "+std::to_string(y1)+"), ("+std::to_string(x2)+", "+std::to_string(y2)+") \n";
    }
    else
    {
        double x1 = CGAL::to_double((*this->s).source().x()), x2 = CGAL::to_double((*this->s).target().x()), y1 = CGAL::to_double((*this->s).start().y()), y2 = CGAL::to_double((*this->s).target().y());
        r = "Segment : ("+std::to_string(x1)+", "+std::to_string(y1)+"), ("+std::to_string(x2)+", "+std::to_string(y2)+") \n";
    }
    return r;
}

std::string Side::ToCSV()
{
    std::string r = "";
    if(this->isLine)
    {
        double x1 = CGAL::to_double((*this->l).point(0).x()), x2 = CGAL::to_double((*this->l).point(1).x()), y1 = CGAL::to_double((*this->l).point(0).y()), y2 = CGAL::to_double((*this->l).point(1).y());
        r = "line,"+std::to_string(x1)+","+std::to_string(y1)+","+std::to_string(x2)+","+std::to_string(y2)+"\n";
    }
    else if(this->isRay)
    {
        double x1 = CGAL::to_double((*this->r).source().x()), x2 = CGAL::to_double((*this->r).second_point().x()), y1 = CGAL::to_double((*this->r).source().y()), y2 = CGAL::to_double((*this->r).second_point().y());
        r = "ray,"+std::to_string(x1)+","+std::to_string(y1)+","+std::to_string(x2)+","+std::to_string(y2)+"\n";
    }
    else
    {
        double x1 = CGAL::to_double((*this->s).source().x()), x2 = CGAL::to_double((*this->s).target().x()), y1 = CGAL::to_double((*this->s).start().y()), y2 = CGAL::to_double((*this->s).target().y());
        r = "segment,"+std::to_string(x1)+","+std::to_string(y1)+","+std::to_string(x2)+","+std::to_string(y2)+"\n";
    }
    return r;
}