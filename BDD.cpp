// BDD.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <cstdio> #printf
#include <iomanip> #setprecision

using namespace std;

vector<double> h_num;

double f(double x)
{
    #include <math.h>
    double y = exp(x);
    return y;
}

double normal_round(double value, int prec) 
{
    float multiplier = pow(10.0f, (float)prec);
    return round(value * multiplier) / multiplier;
}

void split(string str)
{
    string st_num = "";
    for (auto i : str)
    {
        if (i == ',')
        {
            double do_num = stod(st_num);
            h_num.push_back(do_num);
            st_num = "";
        }
        else
        {
            st_num = st_num + i;
        }
    }
    double do_num = stod(st_num);
    h_num.push_back(do_num);
}

int main()
{
    int prec;
    double xi, fxi;
    string h;
    vector<double> fpxi_list;

    cout << "Enter number of decimal places: ";
    cin >> prec;

    cout << "Enter value for xi: ";
    cin >> xi;

    cout << "Enter values for step size(seperated by comma) : ";
    cin >> h;

    split(h);

    cout << "\nBackward Finite Divided Difference" << endl;
    printf("%-10s%-10s%-10s%-10s%-10s\n", "h", "f(xi)", "xi-1", "f(xi-1)", "f'(xi)");

    fxi = normal_round(f(xi), prec);

    for (auto hi : h_num)
    {
        printf("%-10g", hi);
        printf("%-10g", fxi);

        double xi_1 = normal_round(xi - hi, prec);
        printf("%-10g", xi_1);

        double fxi_1 = normal_round(f(xi_1), prec);
        printf("%-10g", fxi_1);

        double fpxi = normal_round((fxi - fxi_1) / hi, prec);
        printf("%-10g", fpxi);
        fpxi_list.push_back(fpxi);

        cout << endl;
    }


    cout << "\nRichardson's  Extrapolation" << endl;
    printf("%-15s", "h");

    for (auto hn : h_num)
    {
        printf("%-15f", hn);
    }
    cout << endl;

    int n = 0;
    string h_str;
    vector<double> fpxi_list_new;
    for (auto hi : h_num)
    {
        h_str = "D(n=" + to_string(n + 1) + ")";
        printf("%-15s", h_str.c_str());

        if (n == 0)
        {
            for (auto fpx : fpxi_list)
            {
                printf("%-15g", fpx);
            }
        }
        else
        {
            for (int i = 0; i < fpxi_list.size() - 1; i++)
            {
                double d = normal_round(fpxi_list[i + 1] + ((fpxi_list[i + 1] - fpxi_list[i]) / (pow(2, n + 1) - 1)), prec);

                printf("%-15g", d);
                fpxi_list_new.push_back(d);
            }

            fpxi_list.clear();
            copy(fpxi_list_new.begin(), fpxi_list_new.end(), back_inserter(fpxi_list));

            fpxi_list_new.clear();
        }
        n = n + 1;
        cout << endl;
    }
    
        system("pause");
    return 0;
}
