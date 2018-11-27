//
//  Fp2.hpp
//  Fp
//
//  Created by Roberto Capuano on 27/11/2018.
//  Copyright © 2018 Roberto Capuano. All rights reserved.
//

#ifndef Fp2_hpp
#define Fp2_hpp

#include <functional>
#include <algorithm>

using namespace std;

template< typename T >
class SeqR
{
public:
    using OP = void( typename T::value_type &);
    using PRED = bool(const typename T::value_type &);
    using MAP = typename T::value_type(typename T::value_type &);
    
    T &seq;
    
    SeqR( T &seq )
    : seq( seq )
    {}
    
    void forEach( function<OP> op ) {
        for_each( begin(seq), end(seq), op );
    };
    
    SeqR<T> &filter( function<SeqR::PRED> pred )
    {
        remove_if( begin(seq), end(seq), [&] (auto x) { return !pred(x); } );
        return *this;
    }
    
    SeqR<T> &map( function<SeqR::MAP> mapper )
    {
        transform( begin(seq), end(seq), begin(seq), mapper );
        
        return *this;
    }
    
    SeqR<T> &sort(  )
    {
        std::sort( begin(seq), end(seq) );
        
         return *this;
    }
    
    SeqR<T> &ort( function<SeqR::MAP> comp )
    {
        std::sort( begin(seq), end(seq), comp );
        
        return *this;
    }
    
    //    size_t find( const typename T::value_type &v ) {
    //        auto it = std::find( cbegin(seq), cend(seq), v );
    //
    //        return it - cbegin(seq);
    //    }
    
    bool exist( const typename T::value_type &&v ) {
        auto it = std::find( cbegin(seq), cend(seq), v );
        
        return it!=cend(seq);
    }
    
    bool exist( function<SeqR::PRED> pred ) {
        auto it = std::find( cbegin(seq), cend(seq), pred );
        
        return it!=cend(seq);
    }
    
    const typename T::value_type find( function<SeqR::PRED> pred  ) {
        auto it = find_if( cbegin(seq), cend(seq), pred );
        
        if (it==cend(seq))
            return typename T::value_type();
        
        return *it;
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
SeqV<T> NEWSEQ( T seqv )
{
    return SeqV<T>( seqv );
}

template <typename T>
SeqR<T> SEQ( T &seqv )
{
    return SeqR<T>( seqv );
}

#endif /* Fp2_hpp */
