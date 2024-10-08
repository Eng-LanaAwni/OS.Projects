//Lana Awni Alotoom 144806
//Eman Mohammad Idreis 152531
#include <iostream>
#include <vector>
#include <pthread.h>
#include <climits>
#include <fstream>

using namespace std;

int abovethresh = 0;
int equalsthresh = 0;
int belowthresh = 0;
int threshold;
int T;
vector<long> arr;
vector<pthread_t>threads;


struct Dthread 
{
    int low;
    int high;
};

void merge(Dthread *d1,int mid) 
{
    long  Lsize = mid - d1->low + 1;
    long Rsize = d1->high - mid;
    long left[Lsize], right[Rsize];
    long  i = 0, j = 0, k = d1->low;
    //copy array from thread into arr[of subarrays]

   
    for(long x=0; x<Lsize;x++){   left[x]=arr[k+x];}
    for(long y=0 ; y<Rsize;y++){  right[y]=arr[y+mid+1];}
    

    while (i < Lsize && j < Rsize)
  {  
        
 
    if (left[i] <= right[j])
        {   
            arr[k] = left[i];
            i++;
        }

    else
        { 
           
           arr[k] = right[j];
            j++;
        }
 
    k++;
   
  }

    while (i < Lsize)
    {   
    
        arr[k] = left[i];
    
        i++;
        k++;
    }
    while (j < Rsize)
    {   
   
        arr[k] = right[j];
   
        j++;
        k++;
    }
    
} // close of merge function

void *mergesort(void* arg) 
{
    Dthread *info = static_cast<Dthread*>(arg);
    int low = info->low;
    int high = info->high;

    if (low >= high) 
    {
         
        if (arr[low] > threshold) 
        {
        
            abovethresh++;
        
        } 
        
        else if (arr[low] < threshold) {
       
            belowthresh++;
        
        } 
        
        else 
        {
        
            equalsthresh++;
        
        }
   
        return NULL;
    }//close of base case

    int mid = low + (high - low) / 2;
    Dthread leftinfo = { low, mid };
    Dthread rightinfo = { mid + 1, high };

    mergesort(&leftinfo);  
    mergesort(&rightinfo);  
    merge(info, mid);  
  
    return NULL;
}// close of mergesort function

void merge_sections(long size, long num_threads) 
{
    int section_siz=1;
    if (size>=T)
    {
        num_threads=T; 
        section_siz=size / num_threads;
    }
    
    else 
        num_threads=size;
    
    for (int i = 0; i <num_threads ; i++) 
    {
        int left = 0;
        int right = (i + 1) * section_siz - 1;
        int mid = i * section_siz - 1;
        Dthread info = { left, right };
       
        merge(&info, mid);
    }
}//close of merge_main function
void *extraworker(void* arg) {
   
    long *id = static_cast<long*>(arg); // Cast back to long*
    cout << "Thread " << *id << " is an extra worker." << endl;
    delete id; // Deallocate memory for thread ID
    pthread_exit(NULL);
    return NULL;
}

int main(int argc, char* argv[]) 
{
    ifstream input("in.txt");
    ofstream output("out.txt");

    if (!input.is_open() || !output.is_open()) 
    {
        cerr << "Error opening file" << endl;
        return 1;
    }

    if (argc != 2) 
    {
        cout << "Invalid number of arguments" << endl;
        return 1;
    }

    long n;
    input >> n >> threshold;
    
    arr.resize(n);
    T = stoi(argv[1]);
    threads.resize(T);
    
    for (long i = 0; i < n; i++){input >> arr[i];}

    
    cout <<"Main: Starting sorting with N="<<n<<", TH="<<threshold<<endl;
    
    if (T <= 0) 
    {
        cout << "Invalid number of threads" << endl;
        return 1;
    }

    if (n < T) 
    {
        for (long i = 0; i < n; i++) 
        {
            Dthread *d1 = new Dthread;
            d1->low = i;
            d1->high = i;
            cout << "Starting thread " << i << ": low =" << d1->low << "  high= " << d1->high << endl;
            pthread_create(&threads[i], NULL, mergesort, d1);
        }
        
        for (long i = 0; i < n; i++) 
        {pthread_join(threads[i], NULL);}
        
        for (long i = n; i < T; i++) {
    long *thread_id = new long(i); // Allocate memory for thread ID
    pthread_create(&threads[i], NULL, extraworker, (void*)thread_id); // Pass thread ID as void*
}

       for (long i = n; i < T; i++) 
        {pthread_join(threads[i], NULL);} 
        
    } 
    else if (n == T) 
    {
        for (long i = 0; i < n; i++) 
        {
            Dthread *d1 = new Dthread;
            d1->low = i;
            d1->high = i;
            cout << "Starting thread " << i << ": low =" << d1->low << "  high= " << d1->high << endl;
            pthread_create(&threads[i], NULL, mergesort, d1);
        }
        for (long i = 0; i < n; i++) {pthread_join(threads[i], NULL);}
       
    }
    else 
    {
        int nperT = n / T;
        if (n%T==0)
        {
            for (long i = 0; i < T; i++) 
           {
              int low=i*nperT;
              int high=low+nperT-1;
            
            Dthread *d1 = new Dthread;
            d1->low = low;
            d1->high = high;
            cout << "Starting thread " << i << ": low =" << d1->low << "  high= " << d1->high << endl;
            pthread_create(&threads[i], NULL, mergesort, d1);
           
           }
            for (long i = 0; i < T; i++) {pthread_join(threads[i], NULL);}
        }
        else
            cout<<"T is indivisble on n "<<endl;
       
    }
    
     merge_sections(n, T);
    
    output << "sorted array:" << endl;
    for (long i = 0; i < n; i++) 
         {output << arr[i] << "  ";}
          output << endl;
    
    cout << "Main: Above Threshold = " << abovethresh << endl;
    cout << "Main: Equals Threshold = " << equalsthresh << endl;
    cout << "Main: Below Threshold = " << belowthresh << endl;


    input.close();
    output.close();
    return 0;
}
