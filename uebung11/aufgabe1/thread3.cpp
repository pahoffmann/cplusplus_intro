#include <iostream>
#include <future>
#include <chrono>
#include <functional>
#include <algorithm>
#include <vector>
using namespace std;


struct adder : public unary_function<int,void>{
public:
    int sum;
    adder():sum(0){};
    void operator()(int x){
        sum+=x;
    }
};

int square(int x) {
    return x * x;
}

std::vector<int> v(20);

int main() {
    for(int i =1; i< 21; i++){
        auto a = async(&square, i);
        v.push_back(a.get());
    }
    
    adder sum = for_each(v.begin(),v.end(),adder());
    cout << "The thread returned " << sum.sum << endl;
    return 0;
} 