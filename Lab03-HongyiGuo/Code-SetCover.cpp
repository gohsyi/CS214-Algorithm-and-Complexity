#include <iostream>

using namespace std;

void quickSort(int s[], int l, int r)
{
    if (l < r)
    {
        int i = l, j = r, x = s[l];
        while (i < j)
        {
            while(i < j && s[j]>= x)
                j--;
            if(i < j)
                s[i++] = s[j];
            while(i < j && s[i]< x)
                i++;
            if(i < j)
                s[j--] = s[i];
        }
        s[i] = x;
        quickSort(s, l, i - 1);
        quickSort(s, i + 1, r);
    }
}

int Greedy(int x[], int k, int n)
{
    /*
    Please write your Greedy function here.
    If you want to use sorting, please use the quickSort function above.
    */
    quickSort(x, 0, n-1);
    int result = 1, prev = x[0];
    for (int i = 0; i < n; i++) {
    	if (x[i] - prev > k) {
    		result++;
    		prev = x[i];
    	}
    }
    return result;
}

int main()
{
    //x is the point set P with n=7 nodes in total, and the length of intervals is k=3.
    int x[7]={1,2,3,4,5,6,-2};
    int k=3;
    int n=sizeof(x) / sizeof(x[0]);
    int num_interval=Greedy(x,k,n);
    cout << num_interval << endl;
    return 0;
}
