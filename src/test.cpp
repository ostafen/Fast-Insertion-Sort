#include "util.cpp"
#include "gen.cpp"
#include "algo.cpp"
#include "bench.cpp"
#include <iostream>

#include <stdio.h>

using namespace std;

bool compare(int *A, int *B, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (A[i] != B[i])
        {
            return false;
        }
    }
    return true;
}

#define TEST_NUM 10

int main()
{
    IntArrayGenerator gen;

    SortAlgorithm<int> *algo[] = {
        new BlockInsertionSort<int>,
        new FastInsertionSort<int>,
        new MergeSort<int>,
        new QuickSort<int>,
        new QuickInsertionSort<int>,
        new ChainedBlockInsertionSort<int>(0.666, new ChainedBlockInsertionSort<int>),
        new ChainedBlockInsertionSort<int>(0.8,
            new ChainedBlockInsertionSort<int>(0.666, new ChainedBlockInsertionSort<int>))
        };

    QuickSort<int> qs;
    MergeSort<int> ms;

    int num_algos = sizeof(algo) / sizeof(SortAlgorithm<int> *);
    for (int i = 0; i < num_algos; i++)
    {
        bool passed = true;
        int size = 512;
        for (int n = 0; n < TEST_NUM; n++)
        {
            SortAlgorithm<int> *oracle = typeid(algo[i]) != typeid(QuickSort<int>) ? (SortAlgorithm<int> *)&qs : (SortAlgorithm<int> *)&ms;

            int *A = gen.random(size);
            int *B = arrayCopy(A, size);
            cout << "e[A\r\e[0K" << algo[i]->name() << ": test "
                 << "[" << n + 1 << "/" << TEST_NUM << "]." << flush;

            oracle->sort(B, size);

            algo[i]->sort(A, size);

            if (!compare(A, B, size))
            {
                passed = false;
                break;
            }
            delete[] A;
            delete[] B;
            size = size * 2;
        }
        cout << "e[A\r\e[0K" << algo[i]->name() << ": " << (passed ? "[OK]." : "[FAILED].") << flush << endl;
    }
    return 0;
}
