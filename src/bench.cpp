#include "algo.cpp"
#include "gen.cpp"
#include "util.cpp"
#include <vector>
#include <ctime>
#include <iostream>
#include <iomanip>

using namespace std;

template <typename T>
class BenchmarkExecutor
{
private:
    ArrayGenerator<T> *gen;
    int minSize, maxSize;

public:
    BenchmarkExecutor(ArrayGenerator<T> *arrayGen, int minSize, int maxSize)
    {
        this->gen = arrayGen;
        this->minSize = minSize;
        this->maxSize = maxSize;
    }

    BenchmarkExecutor(ArrayGenerator<T> *arrayGen)
    {
        this->gen = arrayGen;
        this->minSize = 2;       //default min size
        this->maxSize = 1 << 20; //default max size
    }

    void run(std::vector<SortAlgorithm<T> *> *algos, int n)
    {
        int maxNameLength = -1;
        for (SortAlgorithm<T> *algo : *algos)
        {
            int length = algo->name().length();
            if (length > maxNameLength)
                maxNameLength = length;
        }

        for (int size = minSize; size <= maxSize; size *= 2)
        {
            double time[30];
            for (int i = 0; i < 30; i++)
                time[i] = 0;

            cout << "Size: " << size << endl
                 << endl;

            for (int z = 0; z < n; z++)
            {
                T *A = gen->random(size);
                T *B = arrayCopy<T>(A, size);

                int c = 0;
                for (SortAlgorithm<T> *algo : *algos)
                {
                    int start = clock();
                    algo->sort(B, size);
                    int elapsedTime = clock() - start;
                    time[c++] += (((double)elapsedTime / (double)n) / CLOCKS_PER_SEC) * 1000;

                    for (int i = 0; i < size; i++)
                    {
                        B[i] = A[i];
                    }
                }

                delete[] A;
                delete[] B;
            }

            int c = 0;
            for (SortAlgorithm<T> *algo : *algos)
            {
                cout << setw(maxNameLength) << left
                     << algo->name() << ": " << setw(10) << right << time[c++] << endl;
            }

            cout << endl;
        }
    }
};
