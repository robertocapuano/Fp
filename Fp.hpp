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

template< typename T >
class SeqV;

template< typename T >
class SeqR
{
public:
    using OP = void(const typename T::value_type &);
    using PRED = bool(const typename T::value_type &);
    using MAP = typename T::value_type(const typename T::value_type &);
    
    const T &seq;
    
    SeqR( const T &seq )
    : seq( seq )
    {}

    void forEach( function<OP> op ) {
        for_each( cbegin(seq), cend(seq), op );
    };
    
    SeqV<T> filter( function<SeqR::PRED> pred )
    {
        T result;
        
        copy_if( begin(seq), end(seq), back_inserter(result), pred );
        
        return SeqV<T>( std::move(result) );
    }
    
    SeqV<T> map( function<SeqR::MAP> pred )
    {
        T result;
        
        transform( begin(seq), end(seq), back_inserter(result), pred );
        
        return SeqV<T>( std::move(result) );
    }
    
    const T& get() { return seq; }
    
};


template< typename T >
class SeqV : public SeqR<T>
{
public:
    
    T seqv;
    
    SeqV( T _seqv )
    : SeqR<T>(seqv),
        seqv( _seqv )
    {}
    
     T get() { return seqv; }
};


template <typename T>
SeqV<T> SEQ( const T &&seqv )
{
    return SeqV<T>( std::move(seqv) );
}

template <typename T>
SeqR<T> SEQ( const T &seqv )
{
    return SeqR<T>( seqv );
}

#endif /* Fp_hpp */
