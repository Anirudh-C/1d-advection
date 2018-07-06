#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <mpi.h>

using namespace std;

/* This method returns the current state of the solution after n steps */
vector<double> nsol(const int n, const double sigma, const vector<double> &u,int commsize, int commrank) {
  int size = u.size();
  vector<double> u_prev(size,0.0);
  double temp;
  MPI_Status status;
  u_prev = u;
  vector<double> u_next(size,0.0);
  int factor = int(size/commsize);
  int dest, source;
  for(unsigned int k=0;k<n;k++) {
    for(unsigned int i=0;i<factor;i++) {
      // For the first block
      if(commrank == 0) {
        dest = commsize - 1;
        source = commrank + 1;
        MPI_Send(&u_prev[1],1,MPI_DOUBLE,dest,0,MPI_COMM_WORLD);
        if(i == factor - 1) {
          MPI_Recv(&temp,1,MPI_DOUBLE,source,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
          u_next[i + factor*commrank] = (1+sigma)*u_prev[i + factor*commrank] - sigma*temp;
        }
        else
          u_next[i + factor*commrank] = (1+sigma)*u_prev[i + factor*commrank] - sigma*u_prev[i + factor*commrank + 1];
      }

      // For the last block
      else if(commrank == (commsize - 1)) {
        dest = commsize - 2;
        source = 0;
        MPI_Send(&u_prev[factor*commrank],1,MPI_DOUBLE,dest,0,MPI_COMM_WORLD);
        if(i == factor - 1) {
          MPI_Recv(&temp,1,MPI_DOUBLE,source,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
          u_next[i + factor*commrank] = (1+sigma)*u_prev[i + factor*commrank] - sigma*temp;
        }
        else
          u_next[i + factor*commrank] = (1+sigma)*u_prev[i + factor*commrank] - sigma*u_prev[i + factor*commrank + 1];
      }

      // For every other block
      else {
        dest = commrank - 1;
        source = commrank + 1;
        MPI_Send(&u_prev[factor*commrank],1,MPI_DOUBLE,dest,0,MPI_COMM_WORLD);
        if(i == factor - 1) {
          MPI_Recv(&temp,1,MPI_DOUBLE,source,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
          u_next[i + factor*commrank] = (1+sigma)*u_prev[i + factor*commrank] - sigma*temp;
        }
        else
          u_next[i + factor*commrank] = (1+sigma)*u_prev[i + factor*commrank] - sigma*u_prev[i + factor*commrank + 1];
      }
    }
    u_prev = u_next;
  }
  return u_next;
}

int main(int argc, char ** argv) {
  // Initialize data
  int mynode, totalnodes;
  int N = 4;
  double h = 1.0/(N-1);
  vector<double> x(N,0.0);
  vector<double> u_prev(N,0.0);
  for(unsigned int i=0;i<N;i++) {
    x[i] = i*h;
    u_prev[i] = sin(2*M_PI*x[i]);
  }
  vector<double> u_next(N,0.0);
  const int frame = 100;
  string name = "fd/fd";
  ofstream outfstr[frame];
  double sigma = 0.25;
  for(int i=0;i<frame;++i)
    outfstr[i].open(name + to_string(i) + ".txt");

  // Solve the equation parallely
  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD,&totalnodes);
  MPI_Comm_rank(MPI_COMM_WORLD,&mynode);
  for(int i = 0;i<frame;i++) {
    u_next = nsol(i,sigma,u_prev,totalnodes,mynode);
  }
  MPI_Finalize();
  return 0;
}
