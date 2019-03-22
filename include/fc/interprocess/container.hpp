#pragma once

#include <fc/variant.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/containers/map.hpp>
#include <boost/interprocess/containers/flat_map.hpp>
#include <boost/interprocess/containers/set.hpp>
#include <boost/interprocess/containers/deque.hpp>
#include <fc/crypto/hex.hpp>
#include <fc/exception/exception.hpp>
#include <fc/io/raw_fwd.hpp>

namespace fc {

   namespace bip = boost::interprocess;

    template<typename... T >
    void to_variant( const bip::deque< T... >& t, fc::variant& v, uint32_t max_depth ) {
      FC_ASSERT( max_depth > 0, "Recursion depth exceeded!" );
      --max_depth;
      std::vector<variant> vars(t.size());
      for( size_t i = 0; i < t.size(); ++i ) {
         to_variant( t[i], vars[i], max_depth );
      }
      v = std::move(vars);
    }

    template<typename T, typename... A>
    void from_variant( const fc::variant& v, bip::deque< T, A... >& d, uint32_t max_depth ) {
      FC_ASSERT( max_depth > 0, "Recursion depth exceeded!" );
      --max_depth;
      const variants& vars = v.get_array();
      d.clear();
      d.resize( vars.size() );
      for( uint32_t i = 0; i < vars.size(); ++i ) {
         from_variant( vars[i], d[i], max_depth );
      }
    }

    template<typename K, typename V, typename... T >
    void to_variant( const bip::map< K, V, T... >& var, fc::variant& vo, uint32_t max_depth ) {
      FC_ASSERT( max_depth > 0, "Recursion depth exceeded!" );
      --max_depth;
       std::vector< variant > vars(var.size());
       size_t i = 0;
       for( auto itr = var.begin(); itr != var.end(); ++itr, ++i )
          vars[i] = fc::variant( *itr, max_depth );
       vo = vars;
    }

    template<typename... T >
    void to_variant( const bip::vector< T... >& t, fc::variant& v, uint32_t max_depth ) {
      FC_ASSERT( max_depth > 0, "Recursion depth exceeded!" );
      --max_depth;
      std::vector<variant> vars(t.size());
      for( size_t i = 0; i < t.size(); ++i ) {
         to_variant( t[i], vars[i], max_depth );
      }
      v = std::move(vars);
    }

    template<typename T, typename... A>
    void from_variant( const fc::variant& v, bip::vector< T, A... >& d, uint32_t max_depth ) {
      FC_ASSERT( max_depth > 0, "Recursion depth exceeded!" );
      --max_depth;
      const variants& vars = v.get_array();
      d.clear();
      d.resize( vars.size() );
      for( uint32_t i = 0; i < vars.size(); ++i ) {
         from_variant( vars[i], d[i], max_depth );
      }
    }

    template<typename... T >
    void to_variant( const bip::set< T... >& t, fc::variant& v, uint32_t max_depth ) {
      FC_ASSERT( max_depth > 0, "Recursion depth exceeded!" );
      --max_depth;
      std::vector<variant> vars;
      vars.reserve(t.size());
      for( const auto& item : t ) {
         vars.emplace_back( variant( item, max_depth ) );
      }
      v = std::move(vars);
    }

    template<typename... A>
    void to_variant( const bip::vector<char, A...>& t, fc::variant& v, uint32_t max_depth = 1 )
    {
        if( t.size() )
            v = variant(fc::to_hex(t.data(), t.size()));
        else
            v = "";
    }

    template<typename... A>
    void from_variant( const fc::variant& v, bip::vector<char, A...>& d, uint32_t max_depth = 1 )
    {
         auto str = v.as_string();
         d.resize( str.size() / 2 );
         if( d.size() )
         {
            size_t r = fc::from_hex( str, d.data(), d.size() );
            FC_ASSERT( r == d.size() );
         }
    }
}
