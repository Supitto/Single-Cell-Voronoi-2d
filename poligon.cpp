#include "poligon.hpp"
#include <iostream>


Poligon::Poligon()
{
}

Poligon::~Poligon()
{
    for(int i = Sides.size()-1; i >= 0; i--)
    {
        Sides.pop_back();
    }
}

void Poligon::Cut(Line_2 l, Point_2 p)
{ 
    //std::cout<<"DEBUG : in poligon -> cut"<<std::endl;
    std::vector<Point_2> intersections;
    Point_2 * buf;
    //std::cout<<"DEBUG : Got inside the loop"<<std::endl;
    for(int i = Sides.size()-1; i >= 0; i--)
    {
        //std::cout<<"DEBUG : loop "<<i<<std::endl;
        buf = Sides[i].Intersection(l); //no side effect
        //std::cout<<"woof"<<std::endl;
        if(buf != 0)
        {
            if(!(std::find(intersections.begin(), intersections.end(), *buf) != intersections.end())) 
            {
                //std::cout<<*buf<<std::endl;
                intersections.push_back((Point_2)*buf);
            }
        }
        
    }
    Side * s = 0;
    //std::cout<<"DEBUG : Got out of the loop"<<std::endl;
    switch(intersections.size())
    {
        case 0:
        {
            if(this->IsInside(p,l.point(0)))
            {
                s = new Side(l.point(0)+l.to_vector(),l.point(0)-l.to_vector(),0);
            }
        }
        break;

        case 1: 
        {
            if(this->IsInside(intersections[0]+l.to_vector(),p))
            {
                s = new Side(intersections[0],intersections[0]+l.to_vector(),1);
            }
            else
            {            
                if(this->IsInside(intersections[0]-l.to_vector(),p))
                {
                    s = new Side(intersections[0],intersections[0]-l.to_vector(),1);
                }
            }
        }
        break;
 
        case 2:
        {
            s = new Side(intersections[0],intersections[1],2);
        }
        break;

        default: 
            std::cout<<"non trivial"<<std::endl;
            for(int j = 0; j < intersections.size(); j++)
            {
                std::cout<<intersections[j]<<std::endl;
            }
            throw "non trivial case";
    }
    //std::cout<<"size :"<<Sides.size()<<std::endl;
    for(int i = Sides.size()-1; i>=0; i--)
    {
        //std::cout<<"cut loop "<<i<<std::endl<<Sides[i].ToString();
        if(!Sides[i].Cut(l,p))//Do i still alive (please note the joke)
        {
            
            Sides.erase(Sides.begin()+i);
        }
    }

    if(s!=0)
    {
        Sides.push_back((Side)*s);
    }

    //std::cout<<"DEBUG : out poligon -> cut"<<std::endl;
}

bool Poligon::IsInside(Point_2 p, Point_2 q)
{
    bool inside = true;

    for(int i = 0; i < this->Sides.size() && inside; i ++)
    {
        inside = this->Sides[i].inTheSameHyperplan(p,q);
    }
    return inside;
}

std::string Poligon::ToString()
{
    std::string r = "";
    for(int i = 0; i < Sides.size(); i++)
    {
        r += Sides[i].ToString();
    }
    return r;
}

std::string Poligon::ToCSV()
{
    std::string r = "";
    for(int i = 0; i < Sides.size(); i++)
    {
        r += Sides[i].ToCSV();
    }
    return r;
}