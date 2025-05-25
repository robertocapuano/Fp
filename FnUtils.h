//
//  FnUtils.h
//  lifeland
//
//  Created by Roberto Capuano on 17/06/24.
//

#ifndef FnUtils_h
#define FnUtils_h

#include <optional>
#include <iterator>
#include <algorithm>
#include <functional>
#include <vector>
#include <set>
#include <numeric>
#include <map>
#include <optional>
#include <memory>

using namespace std;

namespace Fn {

template< typename K, typename V >
set<K> fn_keys_set( const map<K,V> &items )
{
    set<K> keys;
    
    for ( const auto &[key, _] : items) {
        keys.insert(key);
    }
    
    return keys;
}

template< typename T >
inline set<T> fn_set( const std::initializer_list<T> &cnt )
{
    return set<T>( begin(cnt), end(cnt) );
}

template< typename T, template <typename... Args> class Container >
inline set<T> fn_set( const Container<T> &cnt )
{
    return set<T>( begin(cnt), end(cnt) );
}

template< typename T, template <typename... Args> class Container >
inline vector<T> fn_vector( const Container<T> &cnt )
{
    return vector<T>( begin(cnt), end(cnt) );
}

template< typename T >
inline vector<T> fn_vector( size_t capacity )
{
    vector<T> v;
    v.reserve( capacity );
    return v;
}

template< typename T, template <typename... Args> class Container >
inline Container<T> fn_slice( const Container<T> &cnt, int st )
{
    return Container<T>( begin(cnt)+st, end(cnt) );
}

template< typename T, template <typename... Args> class Container >
inline Container<T> fn_slice( const Container<T> &cnt, int st, int en )
{
    return Container<T>( begin(cnt)+st, end(cnt)+en );
}

template< typename T, template <typename... Args> class Container >
Container<T> fn_concat( const Container<T> &cnt_a, const Container<T> &cnt_b )
{
    Container<T> dst;
    dst.reserve( cnt_a.size() + cnt_b.size() );
    
    dst.insert(end(dst),begin(cnt_a), end(cnt_a) );
    dst.insert(end(dst),begin(cnt_b), end(cnt_b) );
    
    return dst;
}

template< typename S, template <typename... Args> class Container >
Container<S> fn_reverse( const Container<S> &cnt )
{
    Container<S> result;
    result.resize( cnt.size() );
    
    for ( int i=0; i<cnt.size(); ++i )
        result[i] = cnt[cnt.size()-i-1];
    
    return result;
}

template< typename S >
inline vector<S> fn_iota( size_t size, S value=S{} )
{
    vector<S> out(size);
    
    iota( begin(out), end(out), value );
    
    return out;
}

inline vector<int> fn_range( size_t size ) { return fn_iota<int>( size ); }

template< typename T, template <typename... Args> class Container >
inline void fn_insert( Container<T> &dst, const Container<T> &src )
{
    dst.insert( end(dst), begin(src), end(src) );
}

template< typename T, template <typename... Args> class Container >
inline void fn_append( Container<T> &dst, const Container<T> &src )
{
    dst.insert( end(dst), begin(src), end(src) );
}

template< typename T, typename S, template <typename... Args> class Container >
Container<T> fn_transform( const Container<S> &cnt, function<typename Container<T>::value_type (const typename Container<S>::value_type &)> op  )
{
    Container<T> result;
    result.reserve( cnt.size() );
    
    transform( cnt.begin(), cnt.end(), back_inserter(result), op );
    
    return result;
}

template< typename T, typename S, template <typename... Args> class Container >
inline T fn_reduce( const Container<S> &cnt, T ini_val, function<T (T,const typename Container<S>::value_type &)> op  )
{
    T result;
    
    accumulate( cnt.begin(), cnt.end(), ini_val, op );
    
    return result;
}

template< typename S, template <typename... Args> class Container >
optional<reference_wrapper<S>> fn_find( const Container<S> &cnt, function<bool(const typename Container<S>::value_type &)> op )
{
    const auto it = find_if( begin(cnt), end(cnt), op );
    return (it==end(cnt)) ? nullopt : optional<reference_wrapper<S>> { *it };
}

template< typename S, template <typename... Args> class Container >
optional<reference_wrapper<S>> fn_count( const Container<S> &cnt, function<bool(const typename Container<S>::value_type &)> op )
{
    int c;
    for ( const auto it=begin(cnt); it!=end(cnt); ++cnt )
        c += op(*it) ? 1 : 0;
    
    return c;
}

template< typename S, template <typename... Args> class Container >
optional<const reference_wrapper<S>> fn_find( Container<S> &cnt, function<bool( typename Container<S>::value_type &)> op )
{
    auto it = find_if( begin(cnt), end(cnt), op );
    return (it==end(cnt)) ? nullopt : optional<const reference_wrapper<S>> { *it };
}

template< typename S, template <typename... Args> class Container >
inline void fn_apply( Container<S> &cnt, function<void( typename Container<S>::value_type &)> op )
{
    for_each( begin(cnt), end(cnt), op );
}

template< typename S, template <typename... Args> class Container >
inline void fn_foreach( Container<S> &cnt, function<void(typename Container<S>::value_type &)> op )
{
    for_each( begin(cnt), end(cnt), op );
}

//template< typename S, template <typename... Args> class Container >
//void fn_foreach( const Container<S> &cnt, function<void(const typename Container<S>::value_type &)> op )
//{
//    for_each( begin(cnt), end(cnt), op );
//}

template< typename _Cnt >
inline _Cnt fn_filter( const _Cnt &in, function<bool(const typename _Cnt::value_type &)> pred )
{
    _Cnt out;
    
    copy_if( begin(in), end(in), back_inserter(out), pred );
    
    return out;
}

template< typename _Cnt >
inline _Cnt fn_sort( const _Cnt &in, function<bool(const typename _Cnt::value_type &a,const typename _Cnt::value_type &)> pred )
{
    _Cnt out(in);
    
    sort( begin(out), end(out), pred );
    
    return out;
}

}

#endif /* FnUtils_h */
