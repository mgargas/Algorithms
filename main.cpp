#include <iostream>
#include <limits>
#include <utility>
#include <cstdlib>
#include <ctime>

using namespace std;

void printArray(int array[],int length){
    for(int i=0;i<length;i++) cout<<array[i]<<" ";
    cout<<endl;
}

void printArray(float array[],int length){
    for(int i=0;i<length;i++) cout<<array[i]<<" ";
    cout<<endl;
}

void insertSort(int array[],int n) {
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
}


void merge(int array[], int p, int q, int r)
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


void mergeSort(int array[], int p, int r)
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

void maxHeapify(int array[], int heapSize, int i)
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

void buildHeap(int array[],int length)
{
    int heapSize = length;
    for(int i=(heapSize/2);i>=0;i--)
    {
        maxHeapify(array,heapSize,i);
    }
}

void heapSort(int array[],int length)
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

int partition(int array[], int p, int r) //p - first element, r - last element
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

void quickSort(int array[], int p, int r)
{
    if(p<r) {
        int q = partition(array, p, r);
        quickSort(array, p, q-1);
        quickSort(array, q + 1, r);
    }
}

void countingSort(int a[], int n, int k)
{
    int c[k]; //additional array for counting each numbers
    int b[n]; //sorted array
    for(int i=0;i<k;i++) c[i]=0;
    for(int i=0;i<n;i++) c[a[i]]=c[a[i]]+1;
    for(int i=1;i<k;i++) c[i]=c[i]+c[i-1];
    for(int i=n-1;i>=0;i--){
        b[c[a[i]]-1] = a[i];
        c[a[i]] = c[a[i]]-1;
    }
    for(int i=0;i<n;i++) a[i] = b[i];
}

int getMax(int array[], int length)
{
    if(length<1) return 0;
    int max = array[0];
    for(int i=1;i<length;i++){
        if(array[i]>max) max = array[i];
    }
    return max;
}
int countDigits(int number){
    int counter = 0;
    while(number!=0){
        counter++;
        number = number/10;
    }
    return counter;
}

void countingSortAccordingToDigit(int array[], int length, int digit){ //digit=1 means the least significant digit
    int output[length];
    int counter[10] = {0};
    for(int i=0;i<length;i++){
        counter[(array[i]/digit)%10]++;
    }
    for(int i=1;i<10;i++){
        counter[i] = counter[i] + counter[i-1];
    }
    for(int i=length-1;i>=0;i--){
        output[counter[(array[i]/digit)%10]-1] = array[i];
        counter[(array[i]/digit)%10]--;
    }
    for(int i=0;i<length;i++){
        array[i] = output[i];
    }
}

void radixSort(int array[], int length){
    int max = getMax(array,length);
    for(int digit = 1;(max/digit)>0;digit=digit*10){
        countingSortAccordingToDigit(array,length,digit);
    }
}

struct Node{
    float value;
    Node* next;
};
void insertBeginning(Node* &head, float key){
    Node* newNode = new Node;
    newNode->value = key;
    newNode->next = head;
    head = newNode;
}
void printList(Node* head){
    while(head!=NULL){
        cout<<"key = "<<head->value<<" ";
        head = head->next;
    }
}
void insertSorted(Node* &head, Node* newNode){
    if(head==NULL || head->value >= newNode->value){
        newNode->next = head;
        head = newNode;
    }
    else{
        Node* current = head;
        while(current->next!=NULL && current->next->value <= newNode->value){
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

void insertSort(Node* &head){
    Node* output = NULL;
    Node* current = head;
    while(current!=NULL){
        Node* next = current->next;
        insertSorted(output,current);
        current = next;
    }
    head = output;
}

void bucketSort(float array[],int n){
    //make n buckets
    Node* bucketArray[n] = {NULL};
    for(int i=0;i<n;i++){
        //insert into appropriate bucket
        int index = (int)(n*array[i]);
        float key = array[i];
        insertBeginning(bucketArray[index],key);
    }
    for(int i=0;i<n;i++){ //sort each bucket
        insertSort(bucketArray[i]);
    }
    int j=0;
    for(int i=0;i<n;i++){ //combine buckets(put keys into array)
        Node* current = bucketArray[i];
        while(current!=NULL){
            array[j] = current->value;
            j++;
            current = current->next;
        }
    }
}
int random(int min, int max) //range : [min, max)
{
    static bool first = true;
    if ( first )
    {
        srand(time(NULL)); //seeding for the first time only!
        first = false;
    }
    return min + rand() % ((max + 1) - min);
}
int randomizedPartition(int array[],int p,int r){
    int randomIndex = random(p,r);
    swap(array[randomIndex],array[r]);
    return partition(array,p,r);
}

int select(int array[],int p,int r,int i){
    if(p==r) return array[p];
    int q = randomizedPartition(array,p,r);
    int k = q-p+1;
    if(k==i) return array[q];
    else if(k>i) return select(array,p,q-1,i);
    else return select(array,q+1,r,i-k);
}


int main()
{
    int array[10] = {1,3,5,8,19,1,2,4,15,18};
    //insertSort(array,10);
    //heapSort(array,10);
    quickSort(array,0,9);
    printArray(array,10);
    cout<<"This is the 4th smallest number in the array: "<<select(array,0,9,4)<<endl;

    int array2[10] = {1,20,19,3,2,1,23,4,0,12};
    //mergeSort(array2,0,9);
    //heapSort(array2,10);
    quickSort(array2,0,9);
    printArray(array2,10);

    int array3[20];
    for(int i=0;i<20;i++)
    {
        array3[i] = rand()%15;
    }
    printArray(array3,20);
    countingSort(array3,20,15);
    printArray(array3,20);

    int array4[20];
    for(int i=0;i<20;i++)
    {
        array4[i] = rand()%1000;
    }
    printArray(array4,10);
    radixSort(array4,20);
    //countingSortAccordingToDigit(array4,10,1);
    printArray(array4,10);

    float array5[20];
    for(int i=0;i<20;i++){
        array5[i] = ((float) rand()) / (float) RAND_MAX;
    }
    printArray(array5,20);
    bucketSort(array5,20);
    printArray(array5,20);

    return 0;
}
