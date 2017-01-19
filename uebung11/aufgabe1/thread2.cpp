#include <iostream>
#include <vector>
#include <thread>
#include <functional>
#include <atomic>
using namespace std;


atomic<int> sum(0);

void pow2(int x)
{
    sum += x * x; //kein deadlock, da nur eine Variable - für deadlock werden 2 verschiedene 
}                 //"benötigt" , das ist hier aber nicht gegeben. es gibt keine möglichkeit,
                  //dass ein thread eine variable blockt, ein anderer eine andere und beide
int main()        //auf die jeweils andere warten.
{
    
    auto ref = std::ref(sum);
    vector<thread> threads;
    for (int i = 1; i <= 20; i++)
    {
        threads.push_back(thread(&pow2,i));
    }

    vector<thread>::iterator it;
    for (it = threads.begin(); it != threads.end(); it++)
    {
       (*it).join();
    }

    cout << "Sum auf squares up to 20 is = " << sum << endl;
    return 0;
}
