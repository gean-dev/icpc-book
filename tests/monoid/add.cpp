#include "../../content/monoid/Add.hpp"

int main(){
    int a,b;
    cin >> a >> b;
    cout << AddMonoid<int>::op(a,b);
}