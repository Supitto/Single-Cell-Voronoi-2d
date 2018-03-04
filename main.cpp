#include "cell.hpp"
#include <CGAL/Simple_cartesian.h>
#include <iostream>
#include <fstream>
#include <time.h>
 #include <ctime>

typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Point_2 Point_2;
typedef Kernel::Line_2 Line_2;

using namespace std;

void ToFile(string filename, string text)
{
  ofstream f;
  f.open (filename);
  f << text;
  f.close();
}

string PointToCSV(Point_2 p)
{
    return "point,"+std::to_string(p.x())+","+std::to_string(p.y())+"\n";
}

int main()
{
    string temp = "";
    int start_s, stop_s,qtd;
    double time;
    vector<Point_2> v;
    bool good = true;
    Point_2 p;
    for(int j = 0; j <30; j++)
    {
        good=true;
        srand(50135);
        Point_2 center(0,0);
        Cell cell(center);
        qtd = pow(2,j);
        for(int i = 0; i < qtd; i++)
        {
            Point_2 p(((rand()%5000000)/1000)*(((rand()%2)==1)?-1:1),((rand()%5000000)/1000)*(((rand()%2)==1)?-1:1));
            if(!(std::find(v.begin(), v.end(), p) != v.end())&&p!=center) 
            {
                v.push_back(p);
            }
        }
        temp += std::to_string(j)+",";
        start_s=clock();
        while(v.size()>0)
        {
            try
            {
                p = v.back();
                v.pop_back();
                cell.Cut(p);
            }
            catch(char const * c)
            {
                good=false;;
            }
        }
        stop_s=clock();
        time = ((good)?(stop_s-start_s)/double(CLOCKS_PER_SEC)*1000:0);
        cout << "qtd: "<<qtd<<", time: " << time <<" ms" <<endl;
        temp+=std::to_string(time)+"/n";
    }
    temp.pop_back();
    ToFile("out.csv",temp);
    return 0;
}
