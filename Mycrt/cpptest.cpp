//
// Created by 12096 on 2023/1/13.
//
#include "vector.hpp"
#include "string.hpp"
#include "iostream.hpp"
#include "list.hpp"

using namespace std;
int main() {
    vector<string> v;
    v.push_back("ddd");
    v.push_back("www");
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << endl;
    }
    list<string> l;
    l.push_back("ddd");
    l.push_back("www");
    for (auto it = l.begin(); it != l.end(); ++it) {
        cout << it->c_str() << endl;
    }
}
