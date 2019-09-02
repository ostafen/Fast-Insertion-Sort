#include "bench.cpp"
#include "algo.cpp"
#include "util.cpp"
#include "gen.cpp"

#include <string>
#include <vector>
#include <iostream>
#include <unistd.h>

using namespace std;

template<typename T>
ChainedBlockInsertionSort<T>* chain(int k) {
  ChainedBlockInsertionSort<T>* out = new ChainedBlockInsertionSort<T>;

  for(int i = 1; i<k; i++) {
    float exp = (float)(i+1)/(i+2);
    out = new ChainedBlockInsertionSort<T>(exp, out);
  }
  
  out->setLevel(k);
  return out;
};

void run_int()
{
  cout << "########## Type : int ##########" << endl
       << endl;

  std::vector<SortAlgorithm<int> *> algos;

  for(int i=1; i<=10; i++)
    algos.push_back(chain<int>(i));

  algos.push_back(new InplaceInsertionBlock<int>);
  
  for(int i = 2; i<=10; i++)
    algos.push_back(new FastInsertionSort<int>(i));
  
  
  algos.push_back(new QuickSort<int>);
  algos.push_back(new QuickInsertionSort<int>);
  algos.push_back(new QuickBlockInsertionSort<int>(512));
  algos.push_back(new MergeSort<int>);
  algos.push_back(new HeapSort<int>);
  
  IntArrayGenerator intGen;
  BenchmarkExecutor<int> intExcutor(&intGen, 2,  1<<20);
  intExcutor.run(&algos, 100);
}

void run_string()
{
  cout << "########## Type : string ##########" << endl
       << endl;

  std::vector<SortAlgorithm<string> *> algos;

  algos.push_back(new QuickSort<string>);
  algos.push_back(new MergeSort<string>);
  
  /*algos.push_back(new BlockInsertionSort<string>);
  algos.push_back(new InplaceInsertionBlock<string>);
  algos.push_back(new InPlaceRBIS<string>);
  algos.push_back(new RBIS<string>);
  algos.push_back(new MergeSort<string>);
  algos.push_back(new QuickSort<string>);
  algos.push_back(new HeapSort<string>);
  algos.push_back(new QuickInsertionSort<string>);
  algos.push_back(new BCIS<string>);
  algos.push_back(new CBIS<string>);
*/
  StringArrayGenerator stringGen;
  BenchmarkExecutor<string> stringExecutor(&stringGen, 2, 131072);
  stringExecutor.run(&algos, 1000);
}

void run_double()
{
  cout << "########## Type : double ##########" << endl
       << endl;

  std::vector<SortAlgorithm<double> *> algos;

  algos.push_back(new QuickSort<double>);
  algos.push_back(new MergeSort<double>);
  
  DoubleArrayGenerator doubleGen;
  BenchmarkExecutor<double> doubleExecutor(&doubleGen, 2, 131072);
  doubleExecutor.run(&algos, 1000);
}

int main(int argc, char **argv)
{
  run_int();
  return 0;
}
