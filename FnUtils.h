//
//  FnUtils.h
//  Fp
//
//  Created by Roberto Capuano on 17/06/24.
//

#ifndef FnUtils_h
#define FnUtils_h

#include <functional>
#include <vector>
#include <set>

namespace fp {

template< typename T, template <typename... Args> class Container >
set<T> fn_set( const Container<T> &cnt )
{
    return set<T>( begin(cnt), end(cnt) );
}

template< typename T, template <typename... Args> class Container >
vector<T> fn_vector( const Container<T> &cnt )
{
    return vector<T>( begin(cnt), end(cnt) );
}

template< typename T, typename S, template <typename... Args> class Container >
Container<T> fn_map( Container<S> cnt, function<typename Container<T>::value_type (const typename Container<S>::value_type &)> op  ) 
{
    Container<T> result;
    
    transform( begin(cnt), end(cnt), back_inserter(result), op );
    
    return result;
}

template< typename _Cnt >
_Cnt fn_filter( const _Cnt &in, function<bool(const typename _Cnt::value_type &)> pred )
{
    _Cnt out;
    
    copy_if( begin(in), end(in), back_inserter(out), pred );
    
    return out;
}

template< typename _Cnt >
_Cnt fn_sort( const _Cnt &in, function<bool(const typename _Cnt::value_type &a,const typename _Cnt::value_type &)> pred )
{
    _Cnt out(in);
    
    sort( begin(out), end(out), pred );
    
    return out;
}

}

#endif /* FnUtils_h */
