#include<iostream>
#include<algorithm>
using namespace std;
int *A;
int partition(int p, int r)
{
    int x = A[r];
    int i = p-1;
    for(int j = p;j<r;j++)
    {
        if(A[j]<=x)
        {
            i = i+1;
            swap(A[i],A[j]);
        }
    }
    swap(A[i+1],A[r]);
    return i+1;
}
void quicksort(int p, int r)
{
    if(p<r)
    {
        int q = partition(p,r);
        quicksort(p,q-1);
        quicksort(q+1,r);
    }
}
int main()
{
    int n;
    cout<<"Enter the number of elements ";
    cin>>n;
    A = new int[n+1];
    cout<<"Enter the elements of array\n";
    for(int i = 1;i<=n;i++)
        cin>>A[i];
    quicksort(1,n);
    cout<<"The sorted array is ";
    for(int i = 1;i<=n;i++)
        cout<<A[i]<<" ";
    return 0;
}
