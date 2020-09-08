#ifndef RK_hpp
#define RK_hpp

const long double mi = pow(82.45, -1);
const long double lambda = 1 - mi;
const double m1 = 2.0;
const double m2 = 0.5;
const double l1 = 1.0;
const double l2 = 0.6;
const long double a = (pow(3.0, -1) * m1 + m2)*l1*l1;
const long double b = 0.5*m2*l1*l2;
const long double c = pow(3.0,-1)*m2*l2*l2;
const long double g = 9.81;
const long double p =(m1*0.5+m2)*g*l1;
const long double q = m2*l2*g*0.5;
const double sk = 0.21;
const double Dr = 1;
const double ar = 0.15;
const double br = -10;
const double dr = 4;
const double lr = 4;
const double gr = 0.8;

class RungeKutta{

    long double h;
    int option;
    long double x0, y0, y0_2, y0_3, y0_4;
public:
    long double scale;
    RungeKutta(): h(0), option(0), x0(0), y0(0), y0_2(0), y0_3(0), y0_4(0){}

    RungeKutta(long double step, int option_ch, long double x, long double y1, long double y2, long double y3, long double y4):
        h(step), option(option_ch), x0(x), y0(y1), y0_2(y2), y0_3(y3), y0_4(y4){};

    void fill_conditions(std::vector<long double> cond) //funkcja wypelniajaca warunki poczatkowe
    {
        y0 = cond[0];
        y0_2 = cond[1];
        y0_3 = cond[2];
        y0_4 = cond[3];
    }

    void fill_parameters( long double step, int option_ch, long double scale_s)//uzupelnianie parametrow
    {
        option = option_ch;
        h = step;
        scale = scale_s;
    }

    long double f1(long double x, long double y1, long double y2, long double y3, long double y4) //pierwsze rownanie w ukladzie
    {
        switch(option)
        {
        case 1:
            return y2;
        case 2:
            return 10*(y2 - y1);
        case 3:
            return (c*y3 - b*cos(y2-y1)*y4)/(a*c - b*b*pow(cos(y2-y1),2));
        case 4:
            return (-(0.839*y1 + 0.5*(-0.419-0.839)*(abs(y1+1)-abs(y1-1))) + y3)*(1/1.02);
        case 5:
            return y3;
        case 6:
            return gr*(pow(y3 * pow(ar * Dr,-1),pow(ar-1,-1)) - y1);
        }
    }

    long double f2(long double x, long double y1, long double y2, long double y3, long double y4) //drugie rownianie w ukladzie
    {
        switch(option)
        {
        case 1:
            return -y1;
        case 2:
            return 28*y1 - y2 - y1*y3;
        case 3:
            return (a*y4 - b*cos(y2-y1)*y3)/(a*c - b*b*pow(cos(y2-y1),2));
        case 4:
            return (-0.0033*y2 + y3)*(1/-0.632);
        case 5:
            return y4;
        case 6:
            return dr*(powl(1 + powl(y3, br*powl(br-1,-1)),-1) - y2);
        }
    }

    long double f3(long double x, long double y1, long double y2, long double y3, long double y4) // trzecie rownanie w ukladzie
    {
        switch(option)
        {
        case 1:
            return 0;
        case 2:
            return y1*y2 - 8.0/3.0*y3;
        case 3:
            return -b*sin(y2-y1)*((c*y3 - b*cos(y2-y1)*y4)/(a*c - b*b*pow(cos(y2-y1),2)))*((a*y4 - b*cos(y2-y1)*y3)/(a*c - b*b*pow(cos(y2-y1),2))) - p*sin(y1);
        case 4:
            return (-y1 - y2 - (-0.33)*y3)*(1/-1.02);
        case 5:
        {
            long double r1, r2;
            r1 = sqrt(pow(y1 + mi, 2) + y2*y2);
            r2 = sqrt(pow(y1 - lambda, 2) + y2*y2);
            return y1 + 2 * y4 - (lambda*(y1 + mi))* pow(r1, -3) - (mi*(y1 - lambda))*pow(r2, -3);
        }
        case 6:
            return lr*(y1-y2);
        }
    }

    long double f4(long double x, long double y1, long double y2, long double y3, long double y4) //czwarte rownanie w ukladzie
    {
        switch (option)
        {
        case 1:
            return 0;
        case 2:
            return 0;
        case 3:
            return -b*sin(y2-y1)*((c*y3 - b*cos(y2-y1)*y4)/(a*c - b*b*pow(cos(y2-y1),2)))*((a*y4 - b*cos(y2-y1)*y3)/(a*c - b*b*pow(cos(y2-y1),2))) - q*sin(y1);
        case 4:
            return 0;
        case 5:
        {
            long double r1, r2;
            r1 = sqrt(pow( y1 + mi, 2 ) + y2*y2);
            r2 = sqrt(pow( y1 - lambda, 2) + y2*y2);
            return y2 - 2*y3 - (lambda*y2)*pow(r1, -3) - (mi*y2)*pow(r2, -3);
        }
        case 6:
            return 0;
        }
    }

    std::vector<long double> make_step() //metoda wykonujaca jeden krok schematu RK
    {
        std::vector<long double> resolution;
        std::vector<long double> k1, k2 ,k3, k4;

        resolution.reserve(5);

        k1.push_back(h*f1(x0, y0, y0_2, y0_3, y0_4));
        k1.push_back(h*f2(x0, y0, y0_2, y0_3, y0_4));
        k1.push_back(h*f3(x0, y0, y0_2, y0_3, y0_4));
        k1.push_back(h*f4(x0, y0, y0_2, y0_3, y0_4));

        k2.push_back(h*f1(x0 + 0.5*h, y0 + 0.5*k1[0],y0_2 + 0.5*k1[1],y0_3 +  0.5*k1[2], y0_4 + 0.5*k1[3]));
        k2.push_back(h*f2(x0 + 0.5*h, y0 + 0.5*k1[0],y0_2 + 0.5*k1[1],y0_3 +  0.5*k1[2], y0_4 + 0.5*k1[3]));
        k2.push_back(h*f3(x0 + 0.5*h, y0 + 0.5*k1[0],y0_2 + 0.5*k1[1],y0_3 +  0.5*k1[2], y0_4 + 0.5*k1[3]));
        k2.push_back(h*f4(x0 + 0.5*h, y0 + 0.5*k1[0],y0_2 + 0.5*k1[1],y0_3 +  0.5*k1[2], y0_4 + 0.5*k1[3]));

        k3.push_back(h*f1(x0 + 0.5*h, y0 + 0.5*k2[0],y0_2 + 0.5*k2[1],y0_3 +  0.5*k2[2], y0_4 + 0.5*k2[3]));
        k3.push_back(h*f2(x0 + 0.5*h, y0 + 0.5*k2[0],y0_2 + 0.5*k2[1],y0_3 +  0.5*k2[2], y0_4 + 0.5*k2[3]));
        k3.push_back(h*f3(x0 + 0.5*h, y0 + 0.5*k2[0],y0_2 + 0.5*k2[1],y0_3 +  0.5*k2[2], y0_4 + 0.5*k2[3]));
        k3.push_back(h*f4(x0 + 0.5*h, y0 + 0.5*k2[0],y0_2 + 0.5*k2[1],y0_3 +  0.5*k2[2], y0_4 + 0.5*k2[3]));

        k4.push_back(h*f1(x0 + h, y0 + k3[0], y0_2 + k3[1], y0_3 + k3[2], y0_4 + k3[3]));
        k4.push_back(h*f2(x0 + h, y0 + k3[0], y0_2 + k3[1], y0_3 + k3[2], y0_4 + k3[3]));
        k4.push_back(h*f3(x0 + h, y0 + k3[0], y0_2 + k3[1], y0_3 + k3[2], y0_4 + k3[3]));
        k4.push_back(h*f4(x0 + h, y0 + k3[0], y0_2 + k3[1], y0_3 + k3[2], y0_4 + k3[3]));

        y0   = y0 + pow(6, -1)*(k1[0] + 2*k2[0] + 2*k3[0] + k4[0]);
        y0_2   = y0_2 + pow(6, -1)*(k1[1] + 2*k2[1] + 2*k3[1] + k4[1]);
        y0_3  = y0_3 + pow(6, -1)*(k1[2] + 2*k2[2] + 2*k3[2] + k4[2]);
        y0_4 = y0_4 + pow(6, -1)*(k1[3] + 2*k2[3] + 2*k3[3] + k4[3]);

        x0+=h;

        for(int i = 0; i < 4; ++i)
        {
            k1.pop_back();
            k2.pop_back();
            k3.pop_back();
            k4.pop_back();
        }

        resolution.push_back(x0);
        resolution.push_back(y0);
        resolution.push_back(y0_2);
        resolution.push_back(y0_3);
        resolution.push_back(y0_4);

        return resolution;
    }

    std::vector<long double> draw(sf::RenderWindow& window, std::vector<long double> res, std::vector<int> plain, double scale, sf::Color color) //metoda rysujaca linie
    {
        sf::VertexArray lines(sf::Lines, 2);

        lines[0].position = sf::Vector2f(640 + scale*res[plain[0]], 400 - scale*res[plain[1]]);
        lines[0].color = color;

        x0 = res[0];
        y0 = res[1];
        y0_2 = res[2];
        y0_3 = res[3];
        y0_4 = res[4];

        for(int i = 0; i < 5; ++i)
            res.pop_back();

        res = make_step();

        lines[1].position = sf::Vector2f(640 + scale*res[plain[0]], 400 - scale*res[plain[1]]);
        lines[1].color = color;

        window.draw(lines);

        return res;
    }

    void draw_exact_oscillator(sf::RenderWindow& window, double scale, sf::Color color, long double y1, long double y2)//metoda liczaca dokladne wartosci dla oscylatora harmonicznego
    {
        sf::VertexArray lines(sf::Lines, 2);
        double t = 0;
        double h = 0.01;
        lines[0].position = sf::Vector2f(640 + scale*(y1*cos(t) + y2*sin(t)), 400 - scale*(-y1*sin(t) + y2*cos(t)));
        for(int i = 0; i < 10000; ++i)
        {
            lines[0].color = color;
            lines[1].position = sf::Vector2f(640 + scale*(y1*cos(t+h) + y2*sin(t+h)), 400 - scale*(-y1*sin(t+h) + y2*cos(t+h)));
            lines[1].color = color;
            window.draw(lines);
            lines[0].position = lines[1].position;
            t+=h;
        }
    }

};
#endif // RK_hpp
