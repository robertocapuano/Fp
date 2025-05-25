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

#include "FnUtils.h"

using namespace std;
using namespace Fn;

int main(int argc, const char * argv[]) {
    
    auto v = fn_vector<int>(10);
    auto v2 = fn_iota<int>(10,1);
    
    auto v3 = fn_filter( v2, [] (auto x) { return x>5; } );
    
    return 0;
}
