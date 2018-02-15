#include <iostream>
#include <limits>

using namespace std;
int* insertSort(int* array,int n) {
    for(int i=1;i<n;i++)
    {
        // choose the key
        int key = array[i];
        // insert the key into sorted sequence
        int j = i-1;
        while(j>=0 && array[j]>key)
        {
            array[j+1] = array[j];
            j = j-1;
        }
        array[j+1] = key;
    }
    return array;
}


void merge(int* array, int p, int q, int r)
{
    int n1 = q-p+1;
    int n2 = r-q;
    int* left = new int[n1+1]; //p..q..inf
    int* right = new int[n2+1]; //q+1..r..inf
    for(int i=0;i<n1;i++)
    {
        left[i] = array[p+i];
    }
    for(int j=0;j<n2;j++)
    {
        right[j] = array[q+j+1];
    }
    left[n1] = numeric_limits<int>::max(); //guards
    right[n2] = numeric_limits<int>::max();

    int i = 0;
    int j = 0;
    for(int k=p;k<=r;k++)
    {
        if(left[i]<=right[j])
        {
            array[k] = left[i];
            i++;
        }
        else{
            array[k] = right[j];
            j++;
        }
    }
}


void mergeSort(int* array, int p, int r)
{
    if(p<r)
    {
        int q = (p+r)/2;
        mergeSort(array,p,q);
        mergeSort(array,q+1,r);
        merge(array,p,q,r);
    }
}

int main()
{
    int array[10] = {1,3,5,8,19,1,2,4,15,18};
    insertSort(array,10);
    for (int i : array) cout<< i <<" ";
    cout<<endl;
    int array2[10] = {1,20,19,3,2,1,23,4,0,12};
    mergeSort(array2,0,9);
    for (int i : array2) cout<< i <<" ";

    return 0;
}