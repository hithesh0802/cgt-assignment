#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool graphExists(vector<int> &a, int n)
{
    while (1)
    {
        sort(a.begin(), a.end(), greater<>());
        if (a[0] == 0)
            return true;
        int v = a[0];
        a.erase(a.begin() + 0);

        if (v > a.size())
            return false;

        for (int i = 0; i < v; i++)
        {
            a[i]--;
            if (a[i] < 0)
                return false;
        }
    }
}

int main()
{
    cout<< "Test for a random sequence : "<< endl << "Enter number of vertices: " << endl;
    int x;
    cin>> x;
    vector<int> arr(x);
    for(int i=0;i<x;i++){
        cout<< "Enter element " << i+1 << ": "<<endl ;
        cin >> arr[i];
    }
    graphExists(arr, x) ? cout << "Yes it is a graphical sequence" << endl :  cout << "No it is not graphical sequence" << endl;

    //Sample test cases:
    // vector<int> a = {3, 3, 3, 3};
    // vector<int> b = {3, 2,1,0};
    // int n = a.size();
    // int m= b.size();
    // graphExists(a, n) ? cout << "Yes it is a graphical sequence" << endl :  cout << "No it is not graphical sequence" << endl;
    // graphExists(b, m) ? cout << "Yes it is a graphical sequence" << endl :  cout << "No it is not graphical sequence" << endl;
    
    return 0;
}

