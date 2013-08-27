
//Matthew Thorne
//04/09/2012
//Shell sort with paralel processing using openMP
//Cosc 320 parallel processing project
//-----------------------------------------------------------------------------------------------------------------------------------
#include <omp.h>
#include <iostream>
#include <time.h>
#include <ctime>
#include <cstdlib>


using namespace std;


int* CreateArray( int*);
void shellSortParallel( int*, int);
void shellSortSequential(int*, int);
//void Printarray( vector<int>);
void InsertSort( int*, int, int, int);


int main()
{	
	int num = 0;
	cout << "Select 1 for sequential shell sort or 2 for parallel shell sort." << endl;
	cin >> num;
	double start, end, instanceTotal, total = 0, ntotal = 0, newtotal = 0;
	int* A;
	int length = 100000;
	int temp[100000];
	
	double endTime = 0, startTime = 0, totalTime = 0;
	switch(num)
	{
	case 1:
				startTime = time(NULL);
				for(int l = 0; l< 100; l++)
				{
					for(int i = 0; i < 100; i++)
					{ 
						A = CreateArray(temp);
						start = omp_get_wtime();// Start performance timer 1 run
						shellSortSequential(A, length);//Run the algorithm
						end = omp_get_wtime();// End performance timer 1 run
						instanceTotal = end - start;// Get performance time 1 run
						total += instanceTotal;// The total time to run this algorithm 100 times.
					}
					ntotal = total/100;// The average time to run this algorithm 100 times.
					newtotal += ntotal;
					newtotal = newtotal/100;
				}
				endTime = time(NULL);
		   break;
	case 2:
			startTime = time(NULL);
				for(int l = 0; l< 100; l++)
				{
					for(int i = 0; i < 100; i++)
					{ 
						A = CreateArray(temp);
						start = omp_get_wtime();// Start performance timer 1 run
						shellSortParallel(A, length);//Run the algorithm
						end = omp_get_wtime();// End performance timer 1 run
						instanceTotal = end - start;// Get performance time 1 run
						total += instanceTotal;// The total time to run this algorithm 100 times.
					}
					ntotal = total/100;// The average time to run this algorithm 100 times.
					newtotal += ntotal;
					newtotal = newtotal/100;
				}
				endTime = time(NULL);
			break;
	default:
			cout <<"invalid number" << endl;
	}
	
	totalTime = endTime - startTime;
	cout << "This is the time it took to run.  " << totalTime << endl;// time in seconds
	cout <<"This is the total time for the algorithm performance  " << total << "." << endl;//total time algorithm took to run 10,000 times
	cout <<"This is the average time for the algorithm performance  " << newtotal << "." << endl;//the average runtime of each shell sort
	int stupid = 0;
	cin >> stupid;
	return 0;

	
}

int* CreateArray(int temp[])
{
	int rnum = 0;
	int arr[100000];
	srand(time(0));
	srand((unsigned) time(NULL));
	for (int i = 0; i < 100000; i++)
	{
		rnum = rand() % 1000000;
		arr[i] = rnum;
		temp[i] = arr[i];
	}
	return temp;
}


void shellSortParallel(int array[], int length)
{
	int h;
	int j = 0;
	int temp = 0;
	int i = 0;
	for(h =length/2; h > 0; h = h/2)
	{
		#pragma omp parallel for shared( array, length, h, i)  default(none)
		for( i = 0; i < h; i++)
		{
			//int ID = omp_get_thread_num();
			InsertSort(array, i, length, h);
		}
	}
}
void InsertSort(int arr[], int i, int length,  int half){
	//cout << ID << "   ";
	int temp = 0;
	int j = 0;

	for (int f = half + i; f < length; f = f + half)
	{
		j = f;
		while(j > i && arr[j-half] > arr[j])
		{
			temp = arr[j];
			arr[j] = arr[j-half];
			arr[j-half] = temp;
			j = j -half;
		}
	}
}

/*void Printarray( vector<int> n)
{ int num = 0;
	for(int r = 0; r < 100000; r++)
	{
		cout << n << " ";
	}
	cout << endl;*/
	
void shellSortSequential(int array[], int length)
{
	int count = 0, j = 0, temp = 0, h = 0;
	
	for(h =length/2; h > 0; h = h/2)
	{	
		for(int i = 0; i < h; i++)
		{
			for (int f = h + i; f < length; f = f + h)
			{
				j = f;
				while(j > i && array[j-h] > array[j])
				{
					temp = array[j];
					array[j] = array[j-h];
					array[j-h] = temp;
					j = j -h;
				}
			}
		}
	}
}