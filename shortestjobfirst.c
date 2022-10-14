#include <stdio.h>

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void arrangeArrival(int n, int matrix[][6]) 
{
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (matrix[j][1] < matrix[i][1]) {
                for (int k = 0; k < 5; k++) {
                    swap(&matrix[i][k], &matrix[j][k]);
                }
            }
        }
    }
}

void completionTime(int n, int matrix[][6])
{
    matrix[0][3] = matrix[0][1] + matrix[0][2];  //completion time CT of first process
    matrix[0][4] = matrix[0][3] - matrix[0][1];  //Turn Around Time TAT = CT - AR
    matrix[0][5] = matrix[0][4] - matrix[0][2];  //Waiting Time = TAT - BT
    int currCompletionTime, minBurstTimeIndex;
    for (int i = 1; i < n; i++) 
    {
        currCompletionTime = matrix[i-1][3];
        int minBurstTime = matrix[i][2];
        int minArrivalTime = matrix[i][1];
        minBurstTimeIndex = i;
        for (int j = i+1; j < n; j++)
        {   
            if (currCompletionTime >= matrix[j][1] && minBurstTime > matrix[j][2])
            {
                minBurstTime = matrix[j][2];
                minBurstTimeIndex = j;
            } else if (currCompletionTime >= matrix[j][1] && minBurstTime == matrix[j][2])
            {
                continue;
            }
           
        }
        matrix[minBurstTimeIndex][3] = currCompletionTime + matrix[minBurstTimeIndex][2];
        matrix[minBurstTimeIndex][4] = matrix[minBurstTimeIndex][3] - matrix[minBurstTimeIndex][1];
        matrix[minBurstTimeIndex][5] = matrix[minBurstTimeIndex][4] - matrix[minBurstTimeIndex][2];
        for (int k = 0; k < 6; k++)
        {
            swap(&matrix[minBurstTimeIndex][k], &matrix[i][k]);
        }
    }   
}

int main()
{
    int n, total_wt = 0, total_tat = 0, total_com = 0;
    float avg_wt, avg_tat, avg_com;
    int matrix[100][6]; //6 categories of a process: 
                        //Process ID, Arrival Time, Burst Time, Completion Time, Turn Around Time, Waiting Time

    printf("Enter Number of Process: ");
    scanf("%d", &n);
    printf("Enter Arrival Time\n");

    for (int i = 0; i < n; i++)
    {
        printf("Process %d:", i+1);
        scanf("%d", &matrix[i][1]);
        matrix[i][0] = i+1;
    }

    printf("\nEnter Burst Time\n");

    for (int i = 0; i < n; i++)
    {
        printf("Process %d:", i+1);
        scanf("%d", &matrix[i][2]);
        matrix[i][0] = i+1;
    }

    arrangeArrival(n, matrix); //increasing order based on arrival time
    completionTime(n, matrix); //calculate Completion time, Turn around time and Average time

    for (int i = 0; i < n; i++) {
        total_tat += matrix[i][4];
        total_wt += matrix[i][5];
        total_com += matrix[i][3];

    }
    avg_tat = (float) total_tat / n;
    avg_wt = (float) total_wt / n;
    avg_com = (float) total_com / n;


    printf("\n-----TABLE RESULT-----\n");
    printf("Process ID\tArrival Time\tBurst Time\tCompletion Time\tTurn Around Time\tWaiting Time\n");
    for (int i =0; i < n; i++)
    {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n",matrix[i][0],matrix[i][1],matrix[i][2],matrix[i][3],matrix[i][4],matrix[i][5]);
    }

    printf("Average Waiting Time = %f", avg_wt);
    printf("\nAverage Turn Around Time = %f", avg_tat);
    for (int i = 0; i < n; i++) {
        printf("\nCompletion Time of process %d = %d", i+1, matrix[i][3]);
    }
    printf("\nAverage Completion Time = %f", avg_com);

}