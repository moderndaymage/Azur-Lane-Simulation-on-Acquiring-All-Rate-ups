#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static int TrialRunPulls[100001];
int pullSimulator(void), findMedian(void), quickSort(int low, int high), partition(int low, int high), swap(int* a, int* b), oddsPerPull(void);

int main(void)
{
	srand(time(0));
	pullSimulator();
	findMedian();
	oddsPerPull();
	return 0;
}

int pullSimulator(void)
{
	int pullCounter = 0, singlePullRNG = 0, hermioneGet = 0, howeGet = 0, perseusGet = 0, icarusGet = 0, eagleGet = 0, valiantGet = 0;
	for (int count = 0; count < 100001; count++)
	{
		do
		{
			//	Simulate a single pull, RNG Range is from 1-100
			pullCounter++;
			singlePullRNG = (rand() % 100 + 1);
			if (singlePullRNG <= 7)	// checks if you pull SSR
			{
				singlePullRNG = (rand() % 100 + 1);
				if (singlePullRNG <= 7)
					hermioneGet = 1;
				else if (singlePullRNG >= 8 && singlePullRNG <= 36)
					howeGet = 1;
				else if (singlePullRNG >= 37 && singlePullRNG <= 65)
					perseusGet = 1;
			}
			else if (singlePullRNG >= 8 && singlePullRNG <= 20)	//	checks if you pull an elite
			{
				singlePullRNG = (rand() % 100 + 1);
				if (singlePullRNG <= 4)
					icarusGet = 1;
				else if (singlePullRNG >= 5 && singlePullRNG <= 25)
					eagleGet = 1;
				else if (singlePullRNG >= 26 && singlePullRNG <= 46)
					valiantGet = 1;
			}
		} while (hermioneGet == 0 || howeGet == 0 || perseusGet == 0 || icarusGet == 0 || eagleGet == 0 || valiantGet == 0);
		TrialRunPulls[count] = pullCounter;
		printf("Trial #%d, number of pulls to get all rate-ups = %d\n", count + 1, pullCounter);
		//	reset these variables for the next trial run
		pullCounter = 0, hermioneGet = 0, howeGet = 0, perseusGet = 0, icarusGet = 0, eagleGet = 0, valiantGet = 0;
	}
	return 0;
}

int findMedian(void)
{
	//	do quicksort
	int n = sizeof(TrialRunPulls) / sizeof(TrialRunPulls[0]);
	quickSort(0, n - 1);
	printf("\nMedian: %d\n", TrialRunPulls[50000]);
	return 0;
}

int oddsPerPull(void)
{
	float oddsOnNthPull = 0;
	printf("\nOdds of pulling all rate-ups on N pulls is:\n");
	for (int pullMultiples = 10; pullMultiples < 1001; pullMultiples = pullMultiples + 10)
	{
		float oddsMatch = 0;
		for (int count = 0; count < 100001; count++)
		{
			if (TrialRunPulls[count] <= pullMultiples)
				oddsMatch++;
		}
		oddsOnNthPull = ((oddsMatch / 100001) * 100);
		printf("On %d pulls: ~%.2f%%\n", pullMultiples, oddsOnNthPull);
	}
	return 0;
}

int quickSort(int low, int high)	//	The main function that implements QuickSort, low is starting index, high is ending index
{
	if (low < high)
	{
		int pi = partition(low, high); //	pi is partitioning index, arr[p] is now at right place
		quickSort(low, pi - 1);	// Separately sort elements before partition and after partition 
		quickSort(pi + 1, high);
	}
	return 0;
}

/*	This function takes last element as pivot, places the pivot element at its correct position in sorted array,
	and places all smaller (smaller than pivot) to left of pivot and all greater elements to right of pivot	*/
int partition(int low, int high)
{
	int pivot = TrialRunPulls[high];    // pivot 
	int i = (low - 1);  // Index of smaller element 
	for (int j = low; j <= high - 1; j++)
	{
		if (TrialRunPulls[j] < pivot)	// If current element is smaller than the pivot 
		{
			i++;    // increment index of smaller element 
			swap(&TrialRunPulls[i], &TrialRunPulls[j]);
		}
	}
	swap(&TrialRunPulls[i + 1], &TrialRunPulls[high]);
	return (i + 1);
}

int swap(int* a, int* b)	// A utility function to swap two elements 
{
	int t = *a;
	*a = *b;
	*b = t;
	return 0;
}