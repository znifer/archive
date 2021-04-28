#include <iostream>
using namespace std;

unsigned int fact(unsigned int n){
	if (n == 0)
		return 1;
	return n * fact(n - 1);
}
bool NextSet(int *a, int n, int m){
  int k = m;
  for (int i = k - 1; i >= 0; --i)
    if (a[i] < n - k + i + 1)
    {
      ++a[i];
      for (int j = i + 1; j < k; ++j)
        a[j] = a[j - 1] + 1;
      return true;
    }
  return false;
}
void Print(int *a, int n){
  static int num = 1;
  cout.width(3);
  cout << num++ << ": ";
  for (int i = 0; i < n; i++)
    cout << a[i] << " ";
  cout << endl;
}


int main(){
    int n = 3, m = 5, *tmp, writePos = 0;


    int combSize = (fact(m) / (fact(n)*fact(m - n)));
    int **res = new int *[combSize];
    for (int i = 0; i < combSize; i++){
        res[i] = new int[n];
    }
    tmp = new int[n];

    for (int i = 0; i < n; i++)
        tmp[i] = i+1;
    res[writePos] = tmp;
    writePos++;
    if (m >= n){
        while (NextSet(tmp, m, n)){
            //res[writePos] = tmp;
            for (int i = 0; i < n; i++){
                res[writePos][i] = tmp[i];
            }
            Print(res[writePos], n);
            writePos++;
        }
    }
    cout << endl << n << " n " << m <<endl << "check:" << endl;
    for (int i = 0; i < combSize; i++){
        Print(res[i], n);

    }
    return 0;
}
