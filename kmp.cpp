#include <iostream>
#include <cstring>
using namespace std;
string P,T;
int *pi;
void ComputePrefixFunction()
{
    int m = P.length()-1;
    pi = new int[m+1];
    pi[1] = 0;
    int k = 0;
    for(int q = 2;q<=m;q++)
    {
        while(k>0 && P[k+1]!=P[q])
            k = pi[k];
        if(P[k+1] == P[q])
            k = k+1;
        pi[q] = k;
    }
}
void KMP()
{
    int n = T.length()-1;
    int m = P.length()-1;
    ComputePrefixFunction();
    int q = 0;
    for(int i = 1;i<=n;i++)
    {
        while(q>0 && P[q+1]!=T[i])
        {
            q = pi[q];
        }
        if(P[q+1] == T[i])
        {
            q++;
        }
        if(q==m)
        {
            cout<<"Pattern occurs with a shift "<<i-m<<endl;
            q = pi[q];
        }
    }
}
int main()
{
    cout<<"Enter a string ";
    cin>>T;
    cout<<"Enter a pattern ";
    cin>>P;
    T=" "+T;
    P=" "+P;
    KMP();
    return 0;
}
