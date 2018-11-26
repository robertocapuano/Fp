//
//  Fp.hpp
//  Fp
//
//  Created by Roberto Capuano on 26/11/2018.
//  Copyright © 2018 Roberto Capuano. All rights reserved.
//

#ifndef Fp_hpp
#define Fp_hpp

#include <functional>

using namespace std;

#define SEQ(X) Seq<decltype(X)>(X)

template< typename T >
class Seq
{
public:
    using OP = void(const typename T::value_type &);
    using PRED = bool(const typename T::value_type &);
    
//    const T seq;
    const T &seq;

//    Seq( const T &seq )
//    : seq( seq )
//    {}

//    Seq( T seq )
//    : seq( seq )
//    {}
//
    
    Seq( const T &&seq )
    : seq( seq )
    {}

    Seq( T &seq )
    : seq( seq )
    {}

    void forEach( function<OP> op ) {
        for_each( begin(seq), end(seq), op );
    };
    
    Seq<T> filter( function<PRED> pred )
    {
        T result;
        
        copy_if( begin(seq), end(seq), back_inserter(result), pred );
        
        return Seq( std::move(result) );
    }
    
};


#endif /* Fp_hpp */
