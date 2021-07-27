#include<iostream>
using namespace std;
int mat[10][6];

void arrangeArrival(int num, int mat[][6])
{
    for(int i=0; i<num; i++)
    {
        for(int j=0; j<num-i-1; j++)
        {
            if(mat[j][1] > mat[j+1][1])
            {
                for(int k=0; k<5; k++)
                {
                    swap(mat[j][k], mat[j+1][k]);
                }
            }
        }
    }
}

void completionTime(int num, int mat[][6])
{
    int temp, val;
    mat[0][3] = mat[0][1] + mat[0][2];  // compilation time = arrival + burst
    mat[0][5] = mat[0][3] - mat[0][1];  //Turn Around Time = Completion Time – Arrival Time
    mat[0][4] = mat[0][5] - mat[0][2];  //Waiting Time = Turn Around Time – Burst Time

    for(int i=1; i<num; i++)
    {
        temp = mat[i-1][3];
        int lowB = mat[i][2];
        for(int j=i; j<num; j++)
        {
            if(temp >= mat[j][1] && lowB >= mat[j][2])
            {
                lowB = mat[j][2];
                val = j;
            }
        }
        mat[val][3] = temp + mat[val][2]; //new compilation = last compilation + new burst time
        mat[val][5] = mat[val][3] - mat[val][1];
        mat[val][4] = mat[val][5] - mat[val][2];
        for(int k=0; k<6; k++)
        {
            swap(mat[val][k], mat[i][k]);
        }
    }
}

void printGanttChart(int num, int mat[][6])
{
    cout<<"   --------------- Gantt Chart ---------------\n\n";

    int x =1;
    int y =4;
    cout<<"\t";
    for(int i=0; i<num; i++)
    {
        x=mat[i][2];
        y=((x+1)*2)+1;

        for(int c=0; c<y; c++)
        {
            cout<<"-";
        }
    }
    cout<<"\n";
    cout<<"\t";
    for(int i=0; i<num; i++)
    {
        cout<<"|";
        for(int j=0; j<mat[i][2]; j++)
            cout<<" ";

        cout<<"P"<<mat[i][0];

        for(int j=0; j<mat[i][2]; j++)
            cout<<" ";

    }
    cout<<"|\n";
    cout<<"\t";
    for(int i=0; i<num; i++)
    {
        x=mat[i][2];

        y=((x+1)*2)+1;

        for(int c=0; c<y; c++)
        {

            cout<<"-";
        }
    }
    cout<<"\n";
    cout<<"\t";
    cout<<"0";
    for(int i=0; i<num; i++)
    {
        for(int j=0; j<mat[i][2]; j++)
            cout<<"  ";
        if (mat[i][2]<=9)
        {
            cout<<"  ";
        }
        else
        {
            cout<<" ";
        }
        cout<<mat[i][3];
    }

    cout<<"\n\n";
    cout<<"   ----------------- End -----------------\n\n";
}
int main()
{
    int num;
    //get processes info
    cout<<"Enter number of Process: ";
    cin>>num;

    cout<<"...Enter the process ID...\n";
    for(int i=0; i<num; i++)
    {
        cout<<"...Process "<<i+1<<"...\n";
        cout<<"Enter Process Id: ";
        cin>>mat[i][0];
        cout<<"Enter Burst Time: ";
        cin>>mat[i][2];
        cout<<"Enter Arrival Time: ";
        cin>>mat[i][1];
    }


    //print processes
    cout<<"Before Arrange...\n";
    cout<<"Process ID\tArrival Time\tBurst Time\n";
    for(int i=0; i<num; i++)
    {
        cout<<mat[i][0]<<"\t\t"<<mat[i][1]<<"\t\t"<<mat[i][2]<<"\n";
    }

    arrangeArrival(num, mat);
    completionTime(num, mat);
    //after arrange
    cout<<"\nFinal Result...\n";
    cout<<"Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n";
    for(int i=0; i<num; i++)
    {
        cout<<mat[i][0]<<"\t\t"<<mat[i][1]<<"\t\t"<<mat[i][2]<<"\t\t"<<mat[i][4]<<"\t\t"<<mat[i][5]<<"\t\t"<<"\n";
    }
    //print gantt chart
    printGanttChart(num, mat);

    //print avg
    float avgWaiting=0.0;
    float avgTurn=0.0;

    for(int i=0; i<num; i++)
    {

        avgWaiting+=mat[i][4];
    }
    cout<<"Avg waiting time= "<<avgWaiting/num<<"\n";

    for(int i=0; i<num; i++)
    {
        avgTurn+=mat[i][5];
    }
    cout<<"Avg Turn around time= "<<avgTurn/num<<"\n";
}
