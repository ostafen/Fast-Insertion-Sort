#pragma once

#include <cmath>
#include <string>
#include <iostream>

using namespace std;

template <typename T>
void swap(T *a, T *b);

template <typename T>
class SortAlgorithm
{
  public:
    virtual void sort(T *A, int n) = 0;
    virtual string name() = 0;
};

template <typename T>
class InsertionSort : public SortAlgorithm<T>
{
  public:
    void sort(T *A, int n)
    {
        for (int i = 1; i < n; i++)
        {
            int j = i - 1;
            T value = A[i];
            while (j >= 0 && A[j] > value)
            {
                A[j + 1] = A[j];
                j--;
            }
            A[j + 1] = value;
        }
    }

    string name()
    {
        return "Insertion Sort";
    }
};

template <typename T>
class MergeSort : public SortAlgorithm<T>
{
    void merge(T arr[], int l, int m, int r, T *L)
    {
        int i, j, k;
        int n1 = m - l + 1;
        int n2 = r - m;

        //T L[n1];
        T *R = arr + m + 1; //T R[n2];

        for (i = 0; i < n1; i++)
            L[i] = arr[l + i];

        /*for (j = 0; j < n2; j++)
            R[j] = arr[m + 1 + j];*/

        i = 0;
        j = 0;
        k = l;
        while (i < n1 && j < n2)
        {
            if (L[i] <= R[j])
            {
                arr[k] = L[i];
                i++;
            }
            else
            {
                arr[k] = R[j];
                j++;
            }
            k++;
        }

        while (i < n1)
            arr[k++] = L[i++];

        while (j < n2)
            arr[k++] = R[j++];
    }

    void _sort(T *A, int l, int r, T *X)
    {
        if (l < r)
        {
            int m = l + (r - l) / 2;
            _sort(A, l, m, X);
            _sort(A, m + 1, r, X);
            merge(A, l, m, r, X);
        }
    }

  public:
    virtual void sort(T *A, int n)
    {
        T X[n];
        _sort(A, 0, n - 1, X);
    }

    virtual string name()
    {
        return "MergeSort";
    }
};

template <typename T>
class BlockInsertionSort : public SortAlgorithm<T>
{
  private:
    int k;
    InsertionSort<T> is;

  public:
    virtual void sort(T *A, int n)
    {
        int k = sqrt(n);
        if (n < k)
        {
            is.sort(A, n);
            return;
        }

        is.sort(A, k);
        for (int i = k; i < n; i += k)
        {
            if (n - i < k)
                k = n - i;

            T b[k];
            for (int h = 0; h < k; h++)
                b[h] = A[i + h];

            is.sort(b, k);
            int j = i - 1;
            int s = k - 1;
            while (s >= 0)
            {
                while (j >= 0 && A[j] > b[s])
                {
                    A[j + s + 1] = A[j];
                    j--;
                }
                A[j + s + 1] = b[s];
                s--;
            }
        }
    }

    string name()
    {
        return "BlockInsertionSort";
    }
};

template <typename T>
class HeapSort : public SortAlgorithm<T>
{
  private:
    void heapify(T arr[], int n, int i)
    {
        int largest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;

        if (l < n && arr[l] > arr[largest])
            largest = l;

        if (r < n && arr[r] > arr[largest])
            largest = r;

        if (largest != i)
        {
            swap(&arr[i], &arr[largest]);

            heapify(arr, n, largest);
        }
    }

  public:
    virtual void sort(T *A, int n)
    {
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(A, n, i);

        for (int i = n - 1; i >= 0; i--)
        {
            swap(&A[0], &A[i]);
            heapify(A, i, 0);
        }
    }

    string name()
    {
        return "HeapSort";
    }
};

template <typename T>
class InplaceInsertionBlock : public SortAlgorithm<T>
{
  private:
    void inplace_insertion_block(T *A, int e, int k)
    {
        int l, r;
        r = e;
        l = e - 2 * k;

        int i = e - k;
        while (i >= 0 && l >= 0 && r > (e - k))
        {
            if (A[l] > A[r])
            {
                swap(&A[i], &A[l]);
                l--;
            }
            else
            {
                swap(&A[i], &A[r]);
                r--;
            }
            i--;
        }

        while (l >= 0)
        {
            swap(&A[i], &A[l]);
            i--;
            l--;
        }

        while (r > e - k)
        {
            swap(&A[i], &A[r]);
            i--;
            r--;
        }
    }

    void insertion(T *A, int i)
    {
        int j = i - 1;
        int value = A[i];
        while (j >= 0 && A[j] > value)
        {
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = value;
    }

    void insertion_sort(T *A, int n)
    {
        for (int i = 1; i < n; i++)
            insertion(A, i);
    }

  public:
    virtual void sort(T *A, int n)
    {
        int k = sqrt(n);
        if (n < k)
        {
            insertion_sort(A, n);
            return;
        }

        int i;
        for (i = k + 1; i < n - k; i += k)
        {
            insertion_sort(A + i, k);
            inplace_insertion_block(A, i + k - 1, k);
        }
        i -= k;
        while (k > 1)
        {
            k = (n - i) / 2;
            i += k;
            insertion_sort(A + i, k);
            inplace_insertion_block(A, i + k - 1, k);
        }

        for (; i < n; i++)
            insertion(A, i);
    }

    string name()
    {
        return "InPlaceInsertionBlock";
    }
};

template <typename T>
class FastInsertionSort : public SortAlgorithm<T>
{
  private:
    int k;
    InsertionSort<T> is;
    float log_base;

    void _sort(T *A, int n, int l, T *b)
    {
        float exp = (float)(l - 1) / l;
        int k = pow(n, exp);
        if (n <= k || k <= 5 || l <= 1)
        {
            is.sort(A, n);
            return;
        }

        _sort(A, k, l - 1, b);
        for (int i = k; i < n; i += k)
        {
            if (n - i < k)
                k = n - i;

            _sort(A + i, k, l - 1, b);

            for (int h = 0; h < k; h++)
                b[h] = A[i + h];

            int j = i - 1;
            int s = k - 1;
            while (s >= 0)
            {
                while (j >= 0 && A[j] > b[s])
                {
                    A[j + s + 1] = A[j];
                    j--;
                }
                A[j + s + 1] = b[s];
                s--;
            }
        }
    }

    float log(float b, float x)
    {
        return log2(x) / log2(b);
    }

  public:
    FastInsertionSort(float c = 5) : log_base(c) {}

    virtual void sort(T *A, int n)
    {
        int i = log(log_base, n);
        float exp = (float)(i - 1) / i;
        int k_0 = pow(n, exp);
        if (k_0 <= 0)
            return;

        T b[k_0];
        _sort(A, n, i, b);
    }

    string name()
    {
        return "FastIS(c=" + to_string((int)(log_base))+")";
    }
};


template <typename T>
class QuickSort : public SortAlgorithm<T>
{
  private:
    InsertionSort<T> is;
    void _sort(T arr[], int low, int high)
    {
        if(low < high) {
            int pi = partition(arr, low, high);
            _sort(arr, low, pi - 1);
            _sort(arr, pi + 1, high);
        }
    }

  public:
    int partition(T arr[], int low, int high)
    {
        T pivot = arr[high];
        int i = (low - 1);

        for (int j = low; j <= high - 1; j++)
        {
            if (arr[j] <= pivot)
            {
                i++;
                swap(&arr[i], &arr[j]);
            }
        }
        swap(&arr[i + 1], &arr[high]);
        return i + 1;
    }

    virtual void sort(T *A, int n)
    {
        _sort(A, 0, n - 1);
    }

    string name()
    {
        return "QuickSort";
    }
};

template <typename T>
class QuickInsertionSort : public SortAlgorithm<T>
{
  private:
    InsertionSort<T> is;
    void _sort(T arr[], int low, int high)
    {
        int size = (high - low) + 1;
        if (size <= 10)
        {
            is.sort(arr + low, size);
            return;
        }
        int pi = partition(arr, low, high);
        _sort(arr, low, pi - 1);
        _sort(arr, pi + 1, high);
    }

  public:
    int partition(T arr[], int low, int high)
    {
        T pivot = arr[high];
        int i = (low - 1);

        for (int j = low; j <= high - 1; j++)
        {
            if (arr[j] <= pivot)
            {
                i++;
                swap(&arr[i], &arr[j]);
            }
        }
        swap(&arr[i + 1], &arr[high]);
        return i + 1;
    }

    virtual void sort(T *A, int n)
    {
        _sort(A, 0, n - 1);
    }

    string name()
    {
        return "QuickInsertionSort";
    }
};

template <typename T>
class BlockInsertionSort1 : public SortAlgorithm<T>
{
  private:
    int k;
    BlockInsertionSort<T> is;

  public:
    virtual void sort(T *A, int n)
    {
        int k = pow(n, 0.666);
        if (n < k)
        {
            is.sort(A, n);
            return;
        }

        is.sort(A, k);
        for (int i = k; i < n; i += k)
        {
            if (n - i < k)
                k = n - i;

            T b[k];
            for (int h = 0; h < k; h++)
                b[h] = A[i + h];

            is.sort(b, k);
            int j = i - 1;
            int s = k - 1;
            while (s >= 0)
            {
                while (j >= 0 && A[j] > b[s])
                {
                    A[j + s + 1] = A[j];
                    j--;
                }
                A[j + s + 1] = b[s];
                s--;
            }
        }
    }

    string name()
    {
        return "BlockInsertionSort1";
    }
};

template <typename T>
class BlockInsertionSort2 : public SortAlgorithm<T>
{
  private:
    int k;
    BlockInsertionSort1<T> is;

  public:
    virtual void sort(T *A, int n)
    {
        int k = pow(n, 0.75);
        if (n < k)
        {
            is.sort(A, n);
            return;
        }

        is.sort(A, k);
        for (int i = k; i < n; i += k)
        {
            if (n - i < k)
                k = n - i;

            T b[k];
            for (int h = 0; h < k; h++)
                b[h] = A[i + h];

            is.sort(b, k);
            int j = i - 1;
            int s = k - 1;
            while (s >= 0)
            {
                while (j >= 0 && A[j] > b[s])
                {
                    A[j + s + 1] = A[j];
                    j--;
                }
                A[j + s + 1] = b[s];
                s--;
            }
        }
    }

    string name()
    {
        return "BlockInsertionSort2";
    }
};

template <typename T>
class FinalBlockInsertionSort : public SortAlgorithm<T>
{
  private:
    int k;
    InsertionSort<T> is;

  public:
    virtual void sort(T *A, int n)
    {
        if (n <= 1)
            return;

        int i = log2(n) + 1;

        int k = pow(n, ((float)(i + 1) / i));
        if (n <= k)
        {
            is.sort(A, n);
            return;
        }

        sort(A, k);
        T b[k];

        for (int i = k; i < n; i += k)
        {
            if (n - i < k)
                k = n - i;

            for (int h = 0; h < k; h++)
                b[h] = A[i + h];

            sort(b, k);
            int j = i - 1;
            int s = k - 1;
            while (s >= 0)
            {
                while (j >= 0 && A[j] > b[s])
                {
                    A[j + s + 1] = A[j];
                    j--;
                }
                A[j + s + 1] = b[s];
                s--;
            }
        }
    }

    string name()
    {
        return "FinalBlockInsertionSort";
    }
};

template <typename T>
class BlockInsertionSort3 : public SortAlgorithm<T>
{
  private:
    int k;
    BlockInsertionSort2<T> is;

  public:
    virtual void sort(T *A, int n)
    {
        int k = pow(n, 0.8);
        if (n < k)
        {
            is.sort(A, n);
            return;
        }

        is.sort(A, k);
        for (int i = k; i < n; i += k)
        {
            if (n - i < k)
                k = n - i;

            T b[k];
            for (int h = 0; h < k; h++)
                b[h] = A[i + h];

            is.sort(b, k);
            int j = i - 1;
            int s = k - 1;
            while (s >= 0)
            {
                while (j >= 0 && A[j] > b[s])
                {
                    A[j + s + 1] = A[j];
                    j--;
                }
                A[j + s + 1] = b[s];
                s--;
            }
        }
    }

    string name()
    {
        return "BlockInsertionSort3";
    }
};


template <typename T>
class ChainedBlockInsertionSort : public SortAlgorithm<T>
{
  private:
    float exp;
    SortAlgorithm<T>* algo;
    int level;
    
  public:
    ChainedBlockInsertionSort() {
        this->algo = new InsertionSort<T>;
        this->exp = 0.5;
        this->level = 1;
    }
    
    ChainedBlockInsertionSort(float exp, SortAlgorithm<T>* algo) {
        this->exp = exp;
        this->algo = algo;
    }

    ~ChainedBlockInsertionSort() {
        delete algo;
    }

    void setLevel(int level) {
        this->level = level;
    }

    virtual void sort(T *A, int n)
    {
        int k = pow(n, exp);
        if (n < k)
        {
            algo->sort(A, n);
            return;
        }

        algo->sort(A, k);
        for (int i = k; i < n; i += k)
        {
            if (n - i < k)
                k = n - i;

            T b[k];
            for (int h = 0; h < k; h++)
                b[h] = A[i + h];

            algo->sort(b, k);
            int j = i - 1;
            int s = k - 1;
            while (s >= 0)
            {
                while (j >= 0 && A[j] > b[s])
                {
                    A[j + s + 1] = A[j];
                    j--;
                }
                A[j + s + 1] = b[s];
                s--;
            }
        }
    }

    string name()
    {
        return "FastIS-"+ to_string(level);
    }
};

template <typename T>
class QuickBlockInsertionSort : public SortAlgorithm<T>
{
  private:
    int minSize;
    BlockInsertionSort<T> is;

    void _sort(T arr[], int low, int high)
    {
        int size = (high - low) + 1;
        if (size <= minSize)
        {
            is.sort(arr + low, size);
            return;
        }
        int pi = partition(arr, low, high);
        _sort(arr, low, pi - 1);
        _sort(arr, pi + 1, high);
    }

  public:
    QuickBlockInsertionSort(int minSize=512) {
        this->minSize = minSize;
    }

    int partition(T arr[], int low, int high)
    {
        T pivot = arr[high];
        int i = (low - 1);

        for (int j = low; j <= high - 1; j++)
        {
            if (arr[j] <= pivot)
            {
                i++;
                swap(&arr[i], &arr[j]);
            }
        }
        swap(&arr[i + 1], &arr[high]);
        return i + 1;
    }

    virtual void sort(T *A, int n)
    {
        _sort(A, 0, n - 1);
    }

    string name()
    {
        return "QuickBlockInsertionSort";
    }
};
