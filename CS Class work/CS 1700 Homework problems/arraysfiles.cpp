// arraysfiles.cpp
// A program to demonstrate using functions to read data
// from files into arrays and to write data in arrays out
// to files. It will also demonstrate passing file names 
// to functions by reference.

#include<fstream.h>
#include<iomanip.h>
#include<stdlib.h>

void inputfromfile(ifstream & infile, double scores[], int & n);
void sort(double scores[], const int n);
void swap(double &a, double &b);
void shuffle(double scores[], const int n);
void outputtofile(ofstream & outfile, const double scores[], const int n);
void outputtoscreen(const double scores[], const int n);

void main(void)
{
        double scores[200];
        int n;
        
        ifstream infile("scores.dat");
        inputfromfile(infile, scores, n);
        infile.close();

        outputtoscreen(scores, n);

        ofstream outfile("scores.out");
        outfile << "The scores in their original order." << endl;
        outputtofile(outfile, scores, n);

        sort(scores, n);
        outfile << "\n\nThe scores in sorted order." << endl;   
        outputtofile(outfile, scores, n);
        
        shuffle(scores, n);
        outfile << "\n\nThe scores after shuffle." << endl;
        outputtofile(outfile, scores,n);
        
        outfile.close();
}

void inputfromfile(ifstream & infile, double scores[], int & n)
{
        for(int i=0; infile >> scores[i]; i++);
        n = i;
}       

void sort(double x[], const int n)
{
        int i, j;
        for(i=0;i<n;i++)
                for(j=i+1;j<n;j++)
                        if(x[j]<x[i])
                                swap(x[j], x[i]);
}


void swap(double &a, double &b)
{
        double temp = a;
        a=b;
        b=temp;
}


void shuffle(double x[], const int n)
{
        int i, r;
        for(i=0;i<n;i++)
        {
                r=rand()%n;
                swap(x[i], x[r]);
        }

}

void outputtofile(ofstream & outfile, const double x[], const int n)
{
        int i;
        outfile << setiosflags(ios::showpoint|ios::fixed) 
                    << setprecision(1);
        for(i=0;i<n;i++)
        {
                outfile << setw(6) << x[i];
                if ((i+1)%10==0)
                        outfile << endl;
        }
        outfile << endl;
}

void outputtoscreen(const double x[], const int n)
{
        int i;
        cout << setiosflags(ios::showpoint|ios::fixed) 
                 << setprecision(1);
        for(i=0;i<n;i++)
        {
                cout << setw(6) << x[i];
                if ((i+1)%10==0)
                        cout << endl;
        }
        cout << endl;
}

