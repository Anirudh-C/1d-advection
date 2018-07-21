#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>

using namespace std;

/* This method returns the current state of the solution after n steps */
vector<double> nsol(const int n, const double sigma, const vector<double> &u)
{
    int size = u.size();
    vector<double> u_prev(size,0.0); 
    u_prev = u;
    vector<double> u_next(size,0.0);
    for(unsigned int k=0;k<n;k++)
    {
      u_next[size-1] = (1- sigma*sigma)*u_prev[size-1] + (sigma/2)*(sigma - 1)*u_prev[1] + (sigma/2)*(sigma+1)*u_prev[size-2];
      u_next[0] = (1- sigma*sigma)*u_prev[0] + (sigma/2)*(sigma-1)*u_prev[1] + (sigma/2)*(sigma+1)*u_prev[size-2];
      for(unsigned int i=1;i<size-1;i++)
      {
        u_next[i] = (1-sigma*sigma)*u_prev[i] + (sigma/2)*(sigma -1)*u_prev[i+1] + (sigma/2)*(sigma+1)*u_prev[i-1];
      }
      u_prev = u_next;
    }
    return u_next;
}

int main()
{
    int N = 30;
    double h = 1.0/(N-1);
    vector<double> x(N,0.0);
    vector<double> u_prev(N,0.0);
    for(unsigned int i=0;i<N;i++)
    {
        x[i] = i*h;
        u_prev[i] = sin(2*M_PI*x[i]);
    }
    double sigma = 0.25;

    const int frame = 200;
    string name = "lw/lw";
    ofstream outfstr[frame];
    for(int i=0;i<frame;++i)
        outfstr[i].open(name + to_string(i) + ".txt");

    for(int i=0;i<frame;++i)
    {
        for(int j=0;j<N;++j)
        {
            outfstr[i] << x[j] << " " << nsol(i,sigma,u_prev)[j] << endl;
        }
    }
    cout << "Solved";
    return 0;
}
