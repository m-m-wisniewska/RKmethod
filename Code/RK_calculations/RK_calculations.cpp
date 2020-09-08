#include<iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <sstream>
#include <iomanip>
#include "RK_calculations.hpp"

void Count(RungeKutta equ)
{
    long long int n;
    std::vector<long double> resolutions;
    std::cout << "Insert number of iterations: ";
    std::cin >> n; //liczba iteracji
    while(std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        std::cout << "Insert number again\n";
        std::cin >> n;
    }
    std::fstream file("calculations.txt", std::ios::out);
    if(file.good())
    {
        std::stringstream s_stream;//uzywamy stringstream, aby ustawic precyzje wyswietlania
        file << "t\tx(0)\t\ty(0)\t\tz(0)\t\tw(0)\n";
        for(int i = 0; i < n; ++i)
        {
            resolutions = equ.make_step(); //obliczenia
            s_stream << std::fixed << std::setprecision(2) << resolutions[0] << "\t"<< std::setprecision(6) <<  resolutions [1] << "\t"<< std::setprecision(6) << resolutions [2] << "\t"<< std::setprecision(6) << resolutions [3] << "\t"<< std::setprecision(6) << resolutions[4] << "\n";
            file << s_stream.str();
            file.flush();
            s_stream.str( std::string() );
        }
        file.close();
    }
    else
        std::cout << "Can't load file\n";
}

void Talk()
{

    std::cout << "Runge-Kutta method - fourth order - calculations" << std::endl;
    std::cout << "Choose the equation 1-6" << std::endl;
    std::cout << "1. Harmonic oscillator:\n\nx'(t) = y\ny'(t) = -kx\n\nwith k = 1.\n";
    std::cout << "2. Lorenz Attractor:\n\nx'(t) = a(y(t) - x(t))\ny'(t) = bx(t) - y(t) - x(t)z(t)\nz'(t) = x(t)y(t) - cz(t)\n\nwith a = 10, b = 28, c = 8/3.\n";
    std::cout << "3. Double pendulum:\n\nx'(t) = (cz(t) - bcos(y(t)-X(t))w(t))/(ac - b^2cos^2(y2-y1))\ny'(t) = (aw(t) - bcos(y(t)-X(t))z(t))/(ac - b^2cos^2(y2-y1))\nz'(t) = -bsin(y(t) - x(t))x'(t)y'(t) - psin(x(t))\nw'(t) = -bsin(y(t) - x(t))x'(t)y'(t) - qsin(y(t))\n\nwith a=(1/3(m1) + (m2))(l1)^2, b = 1/2(m2)(l1)(l2), c = 1/3(m2)(l2)^2\np = (1/2(m1)+(m2))g(l1), q = (m2)(l2)1/2g,\n m1 = 2, m2 = 0.5, l1 = 1, l2 = 0.6, g = 9.81\n";
    std::cout << "4. Chua's equation:\n\nx'(t) = a(y(t) - x(t) - ( bx(t) + ( (c - b)/2 |x(t) + 1| - |x(t) - 1|)\ny'(t) = x(t) - y(t) + z(t)\nz'(t) = dy(t)\n\nwith a = 15, b = -5/7, c = -8/7, d = -25.58.\n";
    std::cout << "5. Three-body Problem:\n\nx'(t) = z(t)\ny'(t) = w(t)\nz'(t) = x(t) + 2y(t) - l(r1)^(-3)(x(t)+ m) - m(r2)^(-3)(x(t) - l)\nw'(t) = y(t) - 2z(t) - ly(t)(r1)^(-3) - my(t)r2^(-3)\n\nwith r1 = ( (x(t) + m)^2 + y(t)^2 )^(1/2),\nr2 = ( (x(t) - l)^2 + y(t)^2 )^(1/2), m = 1/82.45 , l = 1 - m.\n";
    std::cout << "6. Labour market model:\n\nx'(t) = g(x(t)^D - x(t))\ny'(t) = d(x(t)^S - y(t))\n z'(t) = l(x(t) - y(t))\n\nwith x(t)^D = (z(t)/(aD))^(1/(a-1)), x(t)^S = 1/(1+z(t)^(b/(b-1))) and D=1,\n a=0.15, b=-10, d=4, l=4.\n";

    int opt;
    long double y1 = 0;
    long double y2 = 0;
    long double y3 = 0;
    long double y4 = 0;
    double h = 0;

    std::cin >> opt; //wybor ukladu
    while(std::cin.fail() || (opt<1 || opt>6))
    {
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        std::cout << "Digit must be from 1 to 6\n";
        std::cin >> opt;
    }
    std::cout << "Insert method step\n";
    std::cin >> h; //wprowadzenie kroku metody
    while(std::cin.fail() || (opt<1 || opt>6))
    {
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        std::cout << "Insert step again\n";
        std::cin >> h;
    }
    std::cout << "Insert beginning conditions:\n";
    std::cout << "x(0) = ";
    std::cin >> y1; //warunek pierwszy
    while(std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        std::cout << "Insert condition again\n";
        std::cin >> y1;
    }
    std::cout << "y(0) = ";
    std::cin >> y2; //warunek drugi
    while(std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        std::cout << "Insert condition again\n";
        std::cin >> y2;
    }
    if(opt!=1)
    {
        std::cout << "z(0) = ";
        std::cin >> y3; //warunek trzeci
        while(std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
            std::cout << "Insert condition again\n";
            std::cin >> y3;
        }
        if(opt == 3 || opt == 5)
        {
            std::cout << "w(0) = ";
            std::cin >> y4; //warunek czwarty
            while(std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(INT_MAX, '\n');
                std::cout << "Insert condition again\n";
                std::cin >> y4;
            }
        }
    }
    RungeKutta equ(h,opt,0,y1,y2,y3,y4); //tworzymy obiekt, na ktorym beda wykonywane obliczenia
    Count(equ);//wywolujemy funkcje, ktora oblicza wartosci i zapisuje je do pliku

}

int main()
{
    Talk();
    return 0;
}
