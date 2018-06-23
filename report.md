
# Table of Contents

1.  [1D Advection Equation](#org4c2cfb2)
    1.  [Description](#orgb4c8ac5)
    2.  [Discretization](#orgca7d1ad)
        1.  [Forward Difference](#orgefa0089)
        2.  [Backward Difference](#orgb7c1e6d)
        3.  [Central Difference](#orgcab4e4b)
    3.  [Implementation](#org3723bb4)
        1.  [Forward Difference](#orga5d87bf)
        2.  [Backward Difference](#orgded1c63)
        3.  [Central Difference](#orgf9650f4)
    4.  [Graphs](#org57e65d6)
        1.  [Forward Difference](#org90b64c3)
        2.  [Backward Difference](#orge73fba6)
        3.  [Central Difference](#org6b1f7b4)


<a id="org4c2cfb2"></a>

# 1D Advection Equation


<a id="orgb4c8ac5"></a>

## Description

Consider the 1D advection equation,
\[u_t + a u_x = 0\]
defined on the domain \([a,b]\)

With periodic boundary conditions, that is,
\[u(x+1,t) = u(x,t)\]


<a id="orgca7d1ad"></a>

## Discretization

Partition the domain into \(N\) points, such that
\[x_i = i \Delta x\]
where, \(\Delta x\) is the partition size defined as,
\[\Delta x = \frac{b - a}{N-1}\]
The time is partitioned so that,
\[t_n = n \Delta t\]
Where \(\Delta t\) is the time interval

Let \(U_i^n\) be the approximation to the function \(u\), that is,
\[U_i^n \approx u(x_i,t_n)\]

By the finite difference method the time derivative is approximated using a forward difference scheme.
\[\frac{\partial}{\partial t} u(x_i,t) \bigg|_{t=t_n} \Rightarrow \frac{U_i^{n+1} - U_i^n}{\Delta t}\]
The space derivative can be approximated in three different schemes:


<a id="orgefa0089"></a>

### Forward Difference

1.  Description

    \[\frac{\partial}{\partial x} u(x,t_n) \bigg|_{x=x_i} \Rightarrow \frac{U_{i+1}^{n+1} - U_i^n}{\Delta x}\]
    Thus we get,
    \[\frac{U_i^{n+1} - U_i^n}{\Delta t} + a \frac{U_{i+1}^{n+1} - U_i^n}{\Delta x} = 0\]
    Define,
    \[\sigma = \frac{a \Delta t}{\Delta x}\]
    Rearranging we get,
    \[U_i^{n+1} = \left( 1 + \sigma \right) U_i^n - \sigma U_{i+1}^n\]
    where,
    \[i=0,1,\ldots,N-2 \qquad n = 0,1,2,\ldots\]
    With the periodic boundary condition we define,
    \[U_{N-1}^{n+1} = \left( 1 + \sigma \right) U_{N-1}^n - \sigma U_{1}^n\]

2.  Stability

    Using Fourier Analysis we get, the solution
    \[U_i^n = \beta^n e^{i l x_i}\]
    Substituting in the scheme we get,
    \[\beta^{n+1} e^{i l x_i} = \left( 1 + \sigma \right) \beta^n e^{i l x_i} - \sigma \beta^n e^{i l x_{i+1}}\]
    Thus,
    \[\beta = 1 + \sigma - \sigma e^{i l \Delta x}\]
    Clearly, \(\lvert \beta \rvert > 1\). Hence, the forward difference scheme is unconditionally unstable.


<a id="orgb7c1e6d"></a>

### Backward Difference

1.  Description

    \[\frac{\partial}{\partial x} u(x,t_n) \bigg|_{x=x_i} \Rightarrow \frac{U_i^{n+1} - U_{i-1}^n}{\Delta x}\]
    Thus we get,
    \[\frac{U_i^{n+1} - U_i^n}{\Delta t} + a \frac{U_i^{n+1} - U_{i-1}^n}{\Delta x} = 0\]
    Define,
    \[\sigma = \frac{a \Delta t}{\Delta x}\]
    Rearranging we get,
    \[U_i^{n+1} = \left( 1 - \sigma \right) U_i^n + \sigma U_{i-1}^n\]
    where,
    \[i=1,2,\ldots,N-1 \qquad n = 0,1,2,\ldots\]
    With the periodic boundary condition we define,
    \[U_{0}^{n+1} = \left( 1 - \sigma \right) U_{0}^n + \sigma U_{N-2}^n\]

2.  Stability

    Using Fourier Analysis we get, the solution
    \[U_i^n = \beta^n e^{i l x_i}\]
    Substituting in the scheme we get,
    \[\beta^{n+1} e^{i l x_i} = \left( 1 - \sigma \right) \beta^n e^{i l x_i} + \sigma \beta^n e^{i l x_{i-1}}\]
    Thus,
    \[\beta = 1 - \sigma + \sigma e^{- i l \Delta x}\]
    \[\beta = 1 - \sigma + \sigma cos(l \Delta x) - i \sigma sin(l \Delta x)\]
    \[\lvert \beta \rvert = 1 + 2 \sigma \left( \sigma -1 \right) \left( 1 - cos(l \Delta x) \right)\]
    \(\lvert \beta \rvert < 1\) only when \(\sigma < 1\). Hence the bacward difference scheme is stable only when \(\sigma < 1\).


<a id="orgcab4e4b"></a>

### Central Difference

1.  Description

    \[\frac{\partial}{\partial x} u(x,t_n) \bigg|_{x=x_i} \Rightarrow \frac{U_{i+1}^{n+1} - U_{i-1}^n}{\Delta x}\]
    Thus we get,
    \[\frac{U_i^{n+1} - U_i^n}{\Delta t} + a \frac{U_{i+1}^{n+1} - U_{i-1}^n}{\Delta x} = 0\]
    Define,
    \[\sigma = \frac{a \Delta t}{\Delta x}\]
    Rearranging we get,
    \[U_i^{n+1} = U_i^n - \frac{\sigma}{2} U_{i+1}^n + \frac{\sigma}{2} U_{i-1}^n\]
    where,
    \[i=1,2,\ldots,N-2 \qquad n = 0,1,2,\ldots\]
    With the periodic boundary condition we define,
    \[U_0^{n+1} = U_0^n - \frac{\sigma}{2} U_{1}^n + \frac{\sigma}{2} U_{N-2}^n\]
    \[U_{N-1}^{n+1} = U_{N-1}^n - \frac{\sigma}{2} U_{1}^n + \frac{\sigma}{2} U_{N-2}^n\]

2.  Stability

    Using Fourier Analysis we get, the solution
    \[U_i^n = \beta^n e^{i l x_i}\]
    Substituting in the scheme we get,
    \[\beta^{n+1} e^{i l x_i} = \beta^n e^{i l x_i} - \frac{\sigma}{2} \beta^n e^{i l x_{i+1}} + \frac{\sigma}{2} \beta^{n} e^{i l x_{i-1}}\]
    Thus,
    \[\beta = 1 - \sigma/2 e^{i l \Delta x} + \sigma/2 e^{- i l \Delta x}\]
    \[\lvert \beta \rvert = 1 + \sigma^{2} \sin^{2} (l \Delta x)\]
    Clearly, \(\lvert \beta \rvert > 1\). Hence, the central difference scheme is unconditionally unstable.
    
    But \(\beta\) is close to one if \(\sigma < 1\), meaning the solution slowly grows in amplitude for \(\sigma < 1\)


<a id="org3723bb4"></a>

## Implementation

    #include <iostream>
    #include <vector>


<a id="orga5d87bf"></a>

### Forward Difference

    // This method returns the current state of the solution after n time steps
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


<a id="orgded1c63"></a>

### Backward Difference

    // This method returns the current state of the solution after n time steps
    vector<double> nsol(const int n, const double sigma, const vector<double> &u)
    {
        int size = u.size();
        vector<double> u_prev(size,0.0);
        u_prev = u;
        vector<double> u_next(size,0.0);
        for(unsigned int k=0;k<n;k++)
        {
            u_next[0] = (1-sigma)*u_prev[0] + sigma*u_prev[size-2];
            for(unsigned int i=1;i<size;i++)
            {
                u_next[i] = (1-sigma)*u_prev[i] + sigma*u_prev[i-1];
            }
            u_prev = u_next;
        }
        return u_next;
    }


<a id="orgf9650f4"></a>

### Central Difference

    // This method returns the current state of the solution after n time steps
    vector<double> nsol(const int n, const double sigma, const vector<double> &u)
    {
        int size = u.size();
        vector<double> u_prev(size,0.0);
        u_prev = u;
        vector<double> u_next(size,0.0);
        for(unsigned int k=0;k<n;k++)
        {
            u_next[size-1] = u_prev[size-1] - (sigma/2)*u_prev[1] + (sigma/2)*u_prev[size-2];
            u_next[0] = u_prev[0] - (sigma/2)*u_prev[1] + (sigma/2)*u_prev[size-2];
            for(unsigned int i=1;i<size-1;i++)
            {
                u_next[i] = u_prev[i] - (sigma/2)*u_prev[i+1] + (sigma/2)*u_prev[i-1];
            }
            u_prev = u_next;
        }
        return u_next;
    }


<a id="org57e65d6"></a>

## Graphs


<a id="org90b64c3"></a>

### Forward Difference


<a id="orge73fba6"></a>

### Backward Difference


<a id="org6b1f7b4"></a>

### Central Difference

