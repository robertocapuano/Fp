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
#include <algorithm>

using namespace std;

template < typename Container, typename Op >
void forEach( Container &&list, Op f ) {
    for_each( begin(list), end(list), f );
}

template < typename Container, typename Op >
Container transform( const Container &cnt, Op op ) {
    Container result;
    
    transform( begin(cnt), end(cnt), back_inserter(result), op );
    
    return result;
}

template < typename Container, typename Op, typename T >
T accumulate( const Container &cnt, T &&val, Op op ) {
    Container result;
    
    accumulate( begin(cnt), end(cnt), val, op );
    
    return result;
}

template < typename Container, typename Op >
Container filter( const Container &cnt, Op op ) {
    Container result;
    
    copy_if( begin(cnt), end(cnt), back_inserter(result), op );
    
    return result;
}

template < typename Container, typename Op >
Container &remove( Container &cnt, Op op ) {
    
    remove_if( begin(cnt), end(cnt), op );
    
    return cnt;
}


template<template <typename... Args> class Container, typename T>
class SeqV;

template<template <typename... Args> class Container, typename T>
class SeqR
{
public:
    using OP = void(const  T &);
    using PRED = bool(const  T &);
    
    template <typename S>
    using MAP = S( const T & );
    
    using COMP = bool( const T &, const T & );
    
    const Container<T> &seq;
    
    SeqR( const Container<T> &seq )
    : seq( seq )
    {}
    
    void forEach( function<OP> op ) {
        for_each( cbegin(seq), cend(seq), op );
    };
    
    SeqV<Container,T> filter( function<SeqR::PRED> pred )
    {
        Container<T> result;
        
        copy_if( begin(seq), end(seq), back_inserter(result), pred );
        
        return SeqV<Container,T>( std::move(result) );
    }
    
    template<typename S>
    SeqV< Container, S > map( function< SeqR::MAP<S> > mapper )
    {
        Container<S> result;
        
        transform( begin(seq), end(seq), back_inserter(result), mapper );
        
        return SeqV< Container, S  >( std::move(result) );
    }
    
    SeqV<Container, T> sort(  )
    {
        Container<T> result { seq };
        
        std::sort( begin(result), end(result) );
        
        return SeqV<Container, T>( std::move(result) );
    }
    
    SeqV<Container,T> sort( function<SeqR::COMP> comp )
    {
        Container<T> result(seq);
        
        std::sort( begin(result), end(result),  comp );
        
        return SeqV<Container,T>( std::move(result) );
    }
    
    size_t find( const T &v ) {
        auto it = std::find( cbegin(seq), cend(seq), v );
        
        return it - cbegin(seq);
    }
    
    bool exist( const T &&v ) {
        auto it = std::find( cbegin(seq), cend(seq), v );
        
        return it!=cend(seq);
    }
    
    bool exist( function<SeqR::PRED> pred ) {
        auto it = std::find( cbegin(seq), cend(seq), pred );
        
        return it!=cend(seq);
    }
    
    const T find( function<SeqR::PRED> pred  ) {
        auto it = find_if( cbegin(seq), cend(seq), pred );
        
        if (it==cend(seq))
            return typename T::value_type();
        
        return *it;
    }
    
    const Container<T>& get() { return seq; }
    
    template<template <typename... Args> class ContainerResult>
    ContainerResult<T> to() {
        return ContainerResult<T>( begin(seq), end(seq) );
    }
    
};


template<template <typename... Args> class Container, typename T>
class SeqV : public SeqR< Container, T >
{
public:
    Container<T> seqv;
    
    SeqV( Container<T> _seqv )
    : SeqR<Container,T>(seqv),
    seqv( _seqv )
    {}
    
    Container<T> get() { return seqv; }
};

template<template <typename... Args> class Container, typename T>
SeqV< Container, T > SEQ( Container<T> &&seqv )
{
    return SeqV<  Container, T >( std::move(seqv) );
}

template<template <typename... Args> class Container, typename T>
SeqR< Container, T > SEQ( const Container<T> &seqv )
{
    return SeqR< Container, T >( seqv );
}


#endif /* Fp_hpp */
