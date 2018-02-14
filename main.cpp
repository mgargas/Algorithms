#include <iostream>

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
int main()
{
    int array[10] = {1,20,19,2,2,1,23,4,0,12};
    insertSort(array,10);
    for (int i : array) cout<< i <<" ";
    return 0;
}