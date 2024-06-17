#include <bits/stdc++.h> 
#include <sys/time.h>
using namespace std; 

int MaxIncreasingSub(int arr[], int ArrayLength, int subArrayLength) 
{ 
	int **dp, ans = -1;
	dp = new int *[ArrayLength]; //this create a matrix
	for(int i=0; i < ArrayLength; i++)
		dp[i] = new int[subArrayLength+1];
	for(int i = 0; i < ArrayLength; i++){
		for(int j = 0; j < subArrayLength; j++){
			dp[i][j] = -1; //this initialize the matrix with -1
		}
	}
	for (int i = 0; i < ArrayLength; i++) { 
		dp[i][1] = arr[i]; //this initialize the first column of the matrix with the array elements
	} 
	
	for (int l = 1; l <= subArrayLength - 1; l++) {
		#pragma omp parallel for default(none) shared(l, dp, arr, ArrayLength) schedule(guided)
		for (int i = 1; i < ArrayLength; i++) { 
			for (int j = 0; j < i; j++) { 
				if (arr[j] < arr[i]) { 
					if (dp[j][l] != -1) { 
						dp[i][l + 1] = max(dp[i][l + 1],dp[j][l] + arr[i]); 
					} 
				}
			} 
		} 
	}
	 //this loop fills the matrix with the maximum sum of the increasing subsequence

	for (int i = 0; i < ArrayLength; i++) { 
		if (ans < dp[i][subArrayLength]) 
			ans = dp[i][subArrayLength]; 
	} 

	return (ans == -1) ? 0 : ans; 
} 

int main() 
{ 
	 struct timeval start, end;

  // Começo da minha medição
   gettimeofday(&start, NULL);
	int ArrayLength, subArrayLength;
	cin >> ArrayLength; //array length
	cin >> subArrayLength; //subsequence length
	int arr[ArrayLength]; 
	for (int i=0; i<ArrayLength; i++)
		cin >> arr[i]; //array elements
	int ans = MaxIncreasingSub(arr, ArrayLength, subArrayLength); 
	gettimeofday(&end, NULL);
	int duration;
  	duration = (end.tv_sec*1000 + end.tv_usec/1000) - (start.tv_sec*1000 + start.tv_usec/1000);
  	cout << "Sum = " << ans << " \n"; 
	printf("Tempo = %d ms\n", duration);
	return 0;
} 
