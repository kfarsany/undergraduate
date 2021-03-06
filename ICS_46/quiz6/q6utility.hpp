#include <vector>
#include <algorithm>                 // std::random_shuffle
#include <random>


//Tuype declaration for LN<T>
template<class T>
class LN {
  public:
    LN ()
      : value(), next()
    {}

    LN (const LN<T>& l)
      : value(l.value), next(l.next)
    {}

    LN (T value, LN* n = nullptr)
      : value(value), next(n)
    {}

  T   value;
  LN* next;
};


//Print a linked list/array nicely, prefaced by label,
//  optionally printing whether or not it is sorted
template<class T>
void print (std::string label, LN<T>* l, bool report_sorted) {
  bool sorted = true;
  std::cout << label;
  for (LN<T>* c=l; c!=nullptr; c=c->next) {
    std::cout << c->value;
    if (c->next == nullptr)
      std::cout << std::endl;
    else {
      std::cout << ", ";
      if (c->value > c->next->value)
        sorted = false;
    }
  }
  if (report_sorted)
    std::cout << (sorted ? "    Sorted" : "    Not Sorted") << std::endl;
}


template<class T>
void print (std::string label, T a[], int length, bool report_sorted) {
  bool sorted = true;
  std::cout << label;
  for (int i=0; i<length; ++i) {
    std::cout << a[i];
    if (i == length-1)
      std::cout << std::endl;
    else {
      std::cout << ", ";
      if (a[i] > a[i+1])
        sorted = false;
    }
  }
  if (report_sorted)
    std::cout << (sorted ? "    Sorted" : "    Not Sorted") << std::endl;
}


//Build a list from an array (keeping the same order)
template<class T>
LN<T>* build (T a[], int length, int i) {
  if (i >= length)
    return nullptr;
  else
    return new LN<T>(a[i],build(a,length,i+1));
}


//Randomize positions of values in an array
template<class T>
void shuffle(T values[], int length) {
  std::vector<T> v_values;
  for (int i=0; i<length; ++i)
    v_values.push_back(values[i]);
  std::random_shuffle(v_values.begin(),v_values.end());
  for (int i=0; i<length; ++i)
    values[i] = v_values[i];
}


//partition returns an index i, swapping values in the array, such that
//  all values a[low]..a[i-1]  are < a[i]
//  all values a[i+1]..a[high] are >= a[i]
//using pivot_index as the pivot (first swapping it to the end)
template<class T>
int partition(T a[], int low, int high, int pivot_index) {
  int l = low, r = high, pivot = a[pivot_index];
  std::swap(a[pivot_index],a[high]);
  while (l < r) {                    //Are there some values to examine?
    while (l < r && a[l] < pivot)    //Find a left value >= the pivot
      ++l;
    while (l < r && a[r] >= pivot)   //Find a right value < the pivot
      --r;
    if (l < r)                       //If found both, swap them
      std::swap(a[l], a[r]);
  }

  std::swap(a[r], a[high]);          //Put pivot value in correct position
  return r;                          //Return its index
}


//Function returning index for pivot (always high)
template<class T>
int last(T a[], int low, int high) {
  return high;
}


//Function returning index for pivot (the index that contains the medians of the
//  values stored at indexes low, (low+high)/2, high); the code here is similar
//  to the code for an optimal comparison tree for sorting 3 values, but it returns
//  the index of the middle value.
template<class T>
int median_3(T a[], int low, int high) { //Returns the index of the middle value
  int l = a[low];
  int mid = (low + high) / 2;
  int m = a[mid];
  int r = a[high];
  if (l < m) {
    if (m < r)
      return mid;
    else if (l < r)
      return high;
    else
      return low;
  }else{
    if (r < m)
      return mid;
    else if (l < r)
      return low;
    else
      return high;
  }
}

//Function returning index for pivot (the index that contains the medians of the
//  values stored at indexes low, (low+high)/4, 2*(low+high)/4, 3*(low+high)/4, and high);
template<class T>
int median_5(T a[], int low, int high) { //Returns the index of the middle value
  std::vector<T>   x(5);
  std::vector<int> i(5);

  x[0] = a[low]; i[0] = low;

  x[1] = a[(low+high)/4];   i[1] = (low+high)/4;
  x[2] = a[(low+high)/2];   i[2] = (low+high)/2;
  x[3] = a[3*(low+high)/4]; i[3] = 3*(low+high)/4;

  x[4] = a[high]; i[4] = high;

  std::vector<T> y(5);
  for (int j=0; j<5; ++j)
    y[j] = x[j];
  std::sort(x.begin(),x.end());
  for (int j=0; j<5; ++j)
    if (y[j] == x[2])
      return i[j];

  //It chooses one of the values in y, so the for loop always finds a match; to shut up the
  //  the compiler, I put this code in.
  return -1;
}


//Function returning index for pivot (the true median, by sorting: way too much work!)
template<class T>
int median(T a[], int low, int high) { //Returns the index of the median value
  T* copy = new T[high];
  for (int i = low; i<high; ++i)
    copy[i] = a[i];
  std::sort(copy+low,copy+high);
  for (int i=low; i<high; ++i)
    if (a[i] == copy[(low+high)/2])
      return i;

  //It chooses one of the values in a, so the for loop always finds a match; to shut up the
  //  the compiler, I put this code in.
  return -1;
}