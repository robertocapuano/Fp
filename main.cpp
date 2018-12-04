//
//  main.cpp
//  Fp
//
//  Created by Roberto Capuano on 26/11/2018.
//  Copyright © 2018 Roberto Capuano. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <list>

#include "Fp.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    
    list<int> v = { 5, -3 ,13 };
    
    SEQ(v)
    .sort()
    .forEach( [] (auto x ) {
        cout << x << endl;

    });
    
    cout << &v << endl;
//    cout << (v) << endl;
//    cout << v.data() << endl;
    auto res = SEQ(v)
    .filter( [] (auto x) {
        return x%2;
    }).
    map( [] (auto x ) { return x+x; }).get();//.find( [] (auto x) { return x.size()>1; } );
    
//    cout << res[0] << endl;
    cout << &res<< endl;
//    cout << res<< endl;
//    cout << (void*) res.data() << endl;
    
//    cout << res << endl;
//    SEQ(res).forEach(  [] (auto x ) {
//        cout << x << endl;
//
//    });
    return 0;
}
