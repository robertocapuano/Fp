//
//  main.cpp
//  Fp
//
//  Created by Roberto Capuano on 26/11/2018.
//  Copyright © 2018 Roberto Capuano. All rights reserved.
//

#include <iostream>
#include <vector>

#include "Fp.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    
    vector<int> v = { 5, 3 ,1 };
    
//    SEQ<vector<int>>  sv(v);
//    SEQ(v)
//    .forEach( [] (auto x ) {
//        cout << x << endl;
//
//    });
    
    cout << &v << endl;
    auto res = SEQ(v)
    .filter( [] (auto x) {
        return x%2;
    }).
    map( [] (auto x ) { return x*2; }).sort().get();
    
    SEQ(res).forEach(  [] (auto x ) {
        cout << x << endl;

    });
    return 0;
}
