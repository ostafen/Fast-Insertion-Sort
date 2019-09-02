#pragma once

template <typename T>
T *arrayCopy(T *A, int n)
{
    T *B = new T[n];
    for (int i = 0; i < n; i++)
        B[i] = A[i];
    return B;
}

template <typename T>
void swap(T *a, T *b)
{
    T temp = *a;
    *a = *b;
    *b = temp;
}