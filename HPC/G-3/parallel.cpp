#include <iostream>
#include <vector>
#include <omp.h>
#include <climits>

using namespace std;

void min_reduction(vector<int>& arr) {
  int min_value = INT_MAX;
  #pragma omp parallel for reduction(min: min_value)
  for (int i = 0; i < arr.size(); i++) {
    if (arr[i] < min_value) {
      min_value = arr[i];
    }
  }
  cout << "Minimum value: " << min_value << endl;
}

void max_reduction(vector<int>& arr) {
  int max_value = INT_MIN;
  #pragma omp parallel for reduction(max: max_value)
  for (int i = 0; i < arr.size(); i++) {
    if (arr[i] > max_value) {
      max_value = arr[i];
    }
  }
  cout << "Maximum value: " << max_value << endl;
}

void sum_reduction(vector<int>& arr) {
  int sum = 0;
   #pragma omp parallel for reduction(+: sum)
   for (int i = 0; i < arr.size(); i++) {
    sum += arr[i];
  }
  cout << "Sum: " << sum << endl;
}

void average_reduction(vector<int>& arr) {
  int sum = 0;
  #pragma omp parallel for reduction(+: sum)
  for (int i = 0; i < arr.size(); i++) {
    sum += arr[i];
  }
  cout << "Average: " << (double)sum / arr.size() << endl;
}

int main() {
  vector<int> arr;

  int size;
  cout << "Enter the number of elements: ";
  cin >> size;

  cout << "Enter the elements: ";
  for (int i = 0; i < size; i++) {
    int element;
    cin >> element;
    arr.push_back(element);
  }

  min_reduction(arr);
  max_reduction(arr);
  sum_reduction(arr);
  average_reduction(arr);

  return 0;
}

/*
Command to run: 
g++ parallel.cpp -lgomp -o test
./test

Input: 
Enter the number of elements: 9
Enter the elements: 5 2 9 1 7 6 8 3 4
Output: 
Minimum value: 1
Maximum value: 9
Sum: 45
Average: 5
*/