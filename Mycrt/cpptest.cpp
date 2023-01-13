//
// Created by 12096 on 2023/1/13.
//
#include "vector.hpp"
#include "iostream.hpp"

using namespace std;
int main() {
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << endl;
    }
}
