#include <iostream>
#include <limits>
#include <utility>
#include <cstdlib>

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

int getLeft(int i)
{
    return 2*i+1;
}
int getRight(int i)
{
    return 2*i+2;
}
int getParent(int i)
{
    return (i-1)/2;
}

void maxHeapify(int* array, int heapSize, int i)
{
    int left = getLeft(i);
    int right = getRight(i);
    int largest;
    if(left<heapSize && array[left]>array[i])
    {
        largest = left;
    }
    else{
        largest = i;
    }
    if(right<heapSize && array[right]>array[largest])
    {
        largest = right;
    }
    if(largest!=i)
    {
        swap(array[i],array[largest]);
        maxHeapify(array,heapSize,largest);
    }
}

void buildHeap(int* array,int length)
{
    int heapSize = length;
    for(int i=(heapSize/2);i>=0;i--)
    {
        maxHeapify(array,heapSize,i);
    }
}

void heapSort(int* array,int length)
{
    int heapSize = length;
    buildHeap(array,length);
    for(int i=length-1;i>0;i--)
    {
        swap(array[0],array[i]);
        heapSize = heapSize - 1;
        maxHeapify(array,heapSize,0);
    }
}

int partition(int* array, int p, int r) //p - first element, r - last element
{
    int x = array[r];
    int i = p-1;
    for(int j=p;j<r;j++)
    {
        if(array[j]<=x)
        {
            i++;
            swap(array[i],array[j]);
        }
    }
    swap(array[i+1],array[r]);
    return i+1;
}

void quickSort(int* array, int p, int r)
{
    if(p<r) {
        int q = partition(array, p, r);
        quickSort(array, p, q-1);
        quickSort(array, q + 1, r);
    }
}

int* countingSort(int* a, int n, int k)
{
    int* c = new int[k]; //additional array for counting each numbers
    int* b = new int[n]; //array a that has been sorted
    for(int i=0;i<k;i++) c[i]=0;
    for(int i=0;i<n;i++) c[a[i]]=c[a[i]]+1;
    for(int i=1;i<k;i++) c[i]=c[i]+c[i-1];
    for(int i=n-1;i>=0;i--){
        b[c[a[i]]-1] = a[i];
        c[a[i]] = c[a[i]]-1;
    }
    return b;
}

int main()
{
    int array[10] = {1,3,5,8,19,1,2,4,15,18};
    //insertSort(array,10);
    //heapSort(array,10);
    quickSort(array,0,9);
    for (int i : array) cout<< i <<" ";
    cout<<endl;
    int array2[10] = {1,20,19,3,2,1,23,4,0,12};
    //mergeSort(array2,0,9);
    //heapSort(array2,10);
    quickSort(array2,0,9);
    for (int i : array2) cout<< i <<" ";
    cout<<endl;
    int* array3 = new int[20];
    for(int i=0;i<20;i++)
    {
        array3[i] = rand()%15;
    }
    for(int i=0;i<20;i++) cout<<array3[i]<<" ";
    array3 = countingSort(array3,20,15);
    cout<<endl;
    for(int i=0;i<20;i++) cout<<array3[i]<<" ";


    return 0;
}
