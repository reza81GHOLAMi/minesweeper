#include <iostream>
#include <stdlib.h>
#include <time.h>
#define MAP_SIZE 25
#define SIZE 6
using namespace std;
void introduction()
{
    cout << "flag=1 ,,, picking up flag = 2 ,,, Otherwise=0 " << endl;
    cout << "Columns and rows 1 to 5 are included" << endl;
}
void makeMove(int &x, int &y, int &flag,int count_flag)
{
    cout << "Enter your move, (row, column, flag) -> ";
    cin >> x >> y >> flag;
    if (x > 5 || x < 1 || y > 5 || y < 1 || flag < 0 || flag > 2)
    {
        cout << "wrong";
        introduction();
        makeMove(x, y, flag,count_flag);
    }
    if (count_flag==6 && flag==1)
    {
        cout << "wrong"<<endl;
        cout<<"You have used all your flag"<<endl;
        cout << "Enter your move, (row, column, flag) -> ";
        makeMove(x, y, flag,count_flag);
    }
    return;
}
void Merge(int *a, int low, int high, int mid)
{
    int i, j, k, temp[high - low + 1];
    i = low;
    k = 0;
    j = mid + 1;
    while (i <= mid && j <= high)
    {
        if (a[i] < a[j])
        {
            temp[k] = a[i];
            k++;
            i++;
        }
        else
        {
            temp[k] = a[j];
            k++;
            j++;
        }
    }
    while (i <= mid)
    {
        temp[k] = a[i];
        k++;
        i++;
    }
    while (j <= high)
    {
        temp[k] = a[j];
        k++;
        j++;
    }
    for (i = low; i <= high; i++)
    {
        a[i] = temp[i - low];
    }
}
void MergeSort(int *a, int low, int high)
{
    int mid;
    if (low < high)
    {
        mid = (low + high) / 2;
        MergeSort(a, low, mid);
        MergeSort(a, mid + 1, high);
        Merge(a, low, high, mid);
    }
}
void selection_mine(int mine_address[], int i)
{
    int j;
    mine_address[i] = rand() % 25;
    for (j = 0; j < i; j++)
    {
        if (mine_address[j] == mine_address[i])
        {
            selection_mine(mine_address, i);
        }
    }
}
void mine(int mine_address[])
{
    int i;
    for (i = 0; i < SIZE; i++)
    {
        selection_mine(mine_address, i);
    }
}
void initial_map(int map[], int mine_address[])
{
    int i, north, north_east, east, south_east, south, south_west, west, north_west;
    for (i = 0; i < SIZE; i++)
    {
        map[mine_address[i]] = 101;
        north = mine_address[i] - 5;
        if (north >= 0 && north < 25)
        {
            map[north]++;
        }
        north_east = north + 1;
        if (north_east >= 0 && north_east < 25 && mine_address[i]%5!=4)
        {
            map[north_east]++;
        }
        east = mine_address[i] + 1;
        if (east >= 0 && east < 25 && mine_address[i]%5!=4)
        {
            map[east]++;
        }
        south = mine_address[i] + 5;
        if (south >= 0 && south < 25)
        {
            map[south]++;
        }
        south_east = south + 1;
        if (south_east >= 0 && south_east < 25 && mine_address[i]%5!=4)
        {
            map[south_east]++;
        }
        south_west = south - 1;
        if (south_west >= 0 && south_west < 25 && mine_address[i]%5!=0)
        {
            map[south_west]++;
        }
        west = mine_address[i] - 1;
        if (west >= 0 && west < 25 && mine_address[i]%5!=0)
        {
            map[west]++;
        }
        north_west = north - 1;
        if (north_west >= 0 && north_west < 25 && mine_address[i]%5!=0)
        {
            map[north_west]++;
        }
    }
    for (i = 0; i < 5; i++)
    {
        cout << endl
             << "#  #  #  #  #";
    }
    cout << endl << endl;
    return;
}
void lost(int mine_address[], int map[])
{
    int i, j = 0;
    cout << "you dead ha! ha! ha!"<<endl;
    for (i = 0; i < 25; i++)
    {
        if (map[i] == 0)
        {
            cout <<"   ";
        }
        else
        {
            if (i == mine_address[j])
            {
                if (j < 5)
                {
                    j++;
                }
                cout << "*  ";
            }
            else
                cout << map[i] << "  ";
        }
        if (i % 5 == 4)
        {
            cout << endl;
        }
    }
}
void show(int next_map[], int map[], int address)
{
    int north, west, south, east, north_west, north_east, south_west, south_east;
    if (next_map[address] == 0)
    {
        north = address - 5;
        if (north >= 0 && north < 25)
        {
            next_map[north] = map[north];
            show(next_map, map, north);
        }
        north_east = north + 1;
        if (north_east >= 0 && north_east < 25 && address%5!=4)
        {
            next_map[north_east] = map[north_east];
            show(next_map, map, north_east);
        }
        east = address + 1;
        if (east >= 0 && east < 25 && address%5!=4)
        {
            next_map[east] = map[east];
            show(next_map, map, east);
        }
        south = address + 5;
        if (south >= 0 && south < 25)
        {
            next_map[south] = map[south];
            show(next_map, map, south);
        }
        south_east = south + 1;
        if (south_east >= 0 && south_east < 25 && address%5!=4)
        {
            next_map[south_east] = map[south_east];
            show(next_map, map, south_east);
        }
        south_west = south - 1;
        if (south_west >= 0 && south_west < 25 && address%5!=0)
        {
            next_map[south_west] = map[south_west];
            show(next_map, map, south_west);
        }
        west = address - 1;
        if (west >= 0 && west < 25 && address%5!=0)
        {
            next_map[west] = map[west];
            show(next_map, map, west);
        }
        north_west = north - 1;
        if (north_west >= 0 && north_west < 25 && address%5!=0)
        {
            next_map[north_west] = map[north_west];
            show(next_map, map, north_west);
        }
    }
    return;
}
void show_map(int next_map[])
{
    int i;
    for(i=0;i<25;i++)
    {
        if (i%5==0)
        {
            cout<<endl;
        }
        if (next_map[i]==200)
        {
            cout<<"#  ";
            continue;
        }
        if (next_map[i]==300)
        {
            cout<<"F  ";
            continue;
        }
        if (next_map[i]==0)
        {
            cout<<"   ";
            continue;
        }
        cout<<next_map[i]<<"  ";
    }
}
void active(int mine_address[], int map[])
{
    int x, y, flag, i, j = 0, address,count_flag=0;
    int next_map[MAP_SIZE];
    fill(next_map, next_map + MAP_SIZE, 200);
    bool continuance = true;
    while (continuance)
    {
        cout<<endl;
        makeMove(x, y, flag,count_flag);
        address = x * 5 + y - 6;
        if (flag == 0 && next_map[address]!=300)
        {
            next_map[address] = map[address];
            if (next_map[address] > 99)
            {
                lost(mine_address, map);
                return;
            }
            // show(next_map, map, address);
        }
        if (flag==1)
        {
            next_map[address]=300;
            count_flag++;
        }
        if (flag==2)
        {
            if (next_map[address]==300)
            {
                next_map[address]=200;
                count_flag--;
            }
        }
        show_map(next_map);
        for(i==0;i<25;i++)
        {
            if(next_map[i]==200)
            {
                i=0;
                break;
            }
            if (i==24)
            {
                cout<<endl<<"congratulations"<<endl<<"You defused all the bombs"<<endl;
                return;
            }
            
        }
    }
}
int main()
{
    cout<<"bomb=* ,,,, flag=F";
    srand(time(0));
    int mine_address[SIZE];
    mine(mine_address);
    MergeSort(mine_address, 0, SIZE - 1);
    int map[MAP_SIZE] = {0};
    initial_map(map, mine_address);
    introduction();
    active(mine_address, map);
    return 0;
}