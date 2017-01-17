#include <iostream>
#include <vector>
#include <thread>
using namespace std;

int square_sum = 0;

void pow2(int x)
{
    square_sum += x * x;
}

int main() 
{
    vector<thread> threads;
    for (int i = 1; i <= 20; i++)
    {
        threads.push_back(thread(&pow2, i));
    }

    vector<thread>::iterator it;
    for (it = threads.begin(); it != threads.end(); it++)
    {
       (*it).join();
    }
    cout << "Sum auf squares up to 20 is = " << square_sum << endl;
    return 0;
}
