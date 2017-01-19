#include <iostream>
#include <vector>
#include <thread>
#include <functional>
using namespace std;

void pow2(int &square_sum, int x)
{
    square_sum += x * x;
}

int main() 
{
    int square_sum = 0;
    auto ref = std::ref(square_sum);
    vector<thread> threads;
    for (int i = 1; i <= 20; i++)
    {
        threads.push_back(thread(&pow2,ref, i));
    }

    vector<thread>::iterator it;
    for (it = threads.begin(); it != threads.end(); it++)
    {
       (*it).join();
    }
    cout << "Sum auf squares up to 20 is = " << square_sum << endl;
    return 0;
}
