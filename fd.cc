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
        u_next[size-1] = (1+sigma)*u_prev[size-1] - sigma*u_prev[1];
        for(unsigned int i=0;i<size-1;i++)
        {
            u_next[i] = (1+sigma)*u_prev[i] - sigma*u_prev[i+1];
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

    const int frame = 100;
    string name = "fd/fd";
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
