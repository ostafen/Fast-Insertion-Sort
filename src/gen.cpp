#pragma once

#include <cstdio>
#include <cstdlib>
#include <chrono>
#include <ctime>
#include <climits>
#include <string>
#include <random>

#include "algo.cpp"

using namespace std;

template <typename T>
class ArrayGenerator
{
public:
    ArrayGenerator()
    {
        srand(time(0));
    }
    virtual T *random(int size) = 0;

    T *sorted(int size)
    {
        T *x = this->random(size);
        QuickSort<T> qs;
        qs.sort(x, size);
        return x;
    }

    T *almostSorted(int size, int iter = -1)
    {
        T *x = this->sorted(size);

        if (iter == -1)
            iter = size / 4;

        for (int i = 0; i < iter; i++)
        {
            T *a = &x[rand() % size];
            T *b = &x[rand() % size];
            swap(a, b);
        }
        return x;
    }
};

class IntArrayGenerator : public ArrayGenerator<int>
{
private:
    int min, max;

    int randomInt()
    {
        return rand() % (max - min + 1) + min;
    }

public:
    IntArrayGenerator()
    {
        this->min = 0;
        this->max = RAND_MAX;
    }

    IntArrayGenerator(int min, int max)
    {
        this->min = min;
        this->max = max;
    }

    virtual int *random(int size)
    {
        int *v = new int[size];
        for (int i = 0; i < size; i++)
        {
            v[i] = randomInt();
        }
        return v;
    }
};

class StringArrayGenerator : public ArrayGenerator<string>
{
private:
    int maxLength;

    string getRandomString(int len)
    {
        string s = "";
        for (int j = 0; j < len; j++)
            s += (char)(rand() % 256);
        return s;
    }

public:
    StringArrayGenerator(int maxLength)
    {
        this->maxLength = maxLength;
    }

    StringArrayGenerator()
    {
        this->maxLength=1000;
    }

    virtual string *random(int size)
    {
        string *A = new string[size];

        for (int i = 0; i < size; i++)
        {
            int len = rand() % maxLength;
            A[i] = getRandomString(len);
        }
        return A;
    }
};

class DoubleArrayGenerator : public ArrayGenerator<double>
{
private:
    int min, max;

    double randomDouble()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        double d = std::generate_canonical<double, 10>(gen);
        return d * (rand() % max);
    }

public:
    DoubleArrayGenerator()
    {
        this->min = 0;
        this->max = RAND_MAX;
    }

    DoubleArrayGenerator(int min, int max)
    {
        this->min = min;
        this->max = max;
    }

    virtual double *random(int size)
    {

        double *v = new double[size];
        for (int i = 0; i < size; i++)
        {
            v[i] = randomDouble();
        }
        return v;
    }
};
