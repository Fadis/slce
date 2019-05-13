/*
 * Copyright (c) 2019 Naomasa Matsubayashi
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>
#include <slce/slce.hpp>
struct base {};
struct inherited : public base {};
struct other {};
struct non_copyable {
  non_copyable( const non_copyable& ) = delete;
  non_copyable &operator=( const non_copyable& ) = delete;
};
struct copyable {
  copyable( const copyable& ) = default;
  copyable &operator=( const copyable& ) = default;
};
struct movable {
  movable( const movable& ) = delete;
  movable( movable&& ) = default;
  movable &operator=( const movable& ) = delete;
  movable &operator=( movable&& ) = default;
};
struct partially_castable_t1 {};
struct partially_castable_t2 {
  partially_castable_t2( const partially_castable_t1& ) {}
  partially_castable_t2( partially_castable_t1&& ) {}
  partially_castable_t2 &operator=( const partially_castable_t1& ) { return *this; };
  partially_castable_t2 &operator=( partially_castable_t1&& ) { return *this; };
  operator partially_castable_t1() const { return partially_castable_t1(); }
};
using fully_castable_t1 = inherited;
using fully_castable_t2 = base;
using default_constructible = base;
struct constructible_with_int {
  constructible_with_int( int ) {}
};
using destructible = base;
class non_destructible {
  ~non_destructible() {}
};
struct bool_like {
  bool_like( bool ) {}
  bool_like( bool_like&& ) {}
  bool_like &operator=( bool_like&& ) { return *this; }
  bool operator!() const {
    return false;
  }
  operator bool() const {
    return true;
  }
};
bool operator&&( const bool_like&, bool ) { return true; }
bool operator||( const bool_like&, bool ) { return true; }
bool operator&&( bool, const bool_like& ) { return true; }
bool operator||( bool, const bool_like& ) { return true; }
bool operator&&( const bool_like&, const bool_like& ) { return true; }
bool operator||( const bool_like&, const bool_like& ) { return true; }
bool operator==( const bool_like&, bool ) { return true; }
bool operator!=( const bool_like&, bool ) { return true; }
bool operator==( bool, const bool_like& ) { return true; }
bool operator!=( bool, const bool_like& ) { return true; }
bool operator==( const bool_like&, const bool_like& ) { return true; }
bool operator!=( const bool_like&, const bool_like& ) { return true; }
bool operator&&( const volatile bool_like&, bool ) { return true; }
bool operator||( const volatile bool_like&, bool ) { return true; }
bool operator&&( bool, const volatile bool_like& ) { return true; }
bool operator||( bool, const volatile bool_like& ) { return true; }
bool operator&&( const volatile bool_like&, const volatile bool_like& ) { return true; }
bool operator||( const volatile bool_like&, const volatile bool_like& ) { return true; }
bool operator&&( const bool_like&, const volatile bool_like& ) { return true; }
bool operator||( const bool_like&, const volatile bool_like& ) { return true; }
bool operator&&( const volatile bool_like&, const bool_like& ) { return true; }
bool operator||( const volatile bool_like&, const bool_like& ) { return true; }
bool operator==( const volatile bool_like&, bool ) { return true; }
bool operator!=( const volatile bool_like&, bool ) { return true; }
bool operator==( bool, const volatile bool_like& ) { return true; }
bool operator!=( bool, const volatile bool_like& ) { return true; }
bool operator==( const volatile bool_like&, const volatile bool_like& ) { return true; }
bool operator!=( const volatile bool_like&, const volatile bool_like& ) { return true; }
bool operator==( const bool_like&, const volatile bool_like& ) { return true; }
bool operator!=( const bool_like&, const volatile bool_like& ) { return true; }
bool operator==( const volatile bool_like&, const bool_like& ) { return true; }
bool operator!=( const volatile bool_like&, const bool_like& ) { return true; }
using incomparable = base;
struct comparable {};
struct comparable_inconvertible {};
struct comparable_convertible : public comparable {};
struct partially_comparable {};
bool operator&&( const comparable&, const comparable& ) { return true; }
bool operator&&( const comparable_inconvertible&, const comparable_inconvertible& ) { return true; }
bool operator&&( const comparable&, const comparable_inconvertible& ) { return true; }
bool operator&&( const comparable_inconvertible&, const comparable& ) { return true; }
bool operator&&( const comparable&, const partially_comparable& ) { return true; }
bool operator&&( const partially_comparable&, const comparable& ) { return true; }
bool operator||( const comparable&, const comparable& ) { return true; }
bool operator||( const comparable_inconvertible&, const comparable_inconvertible& ) { return true; }
bool operator||( const comparable&, const comparable_inconvertible& ) { return true; }
bool operator||( const comparable_inconvertible&, const comparable& ) { return true; }
bool operator||( const comparable&, const partially_comparable& ) { return true; }
bool operator||( const partially_comparable&, const comparable& ) { return true; }
bool operator==( const comparable&, const comparable& ) { return true; }
bool operator==( const comparable_inconvertible&, const comparable_inconvertible& ) { return true; }
bool operator==( const comparable&, const comparable_inconvertible& ) { return true; }
bool operator==( const comparable_inconvertible&, const comparable& ) { return true; }
bool operator==( const comparable&, const partially_comparable& ) { return true; }
bool operator==( const partially_comparable&, const comparable& ) { return true; }
bool operator!=( const comparable&, const comparable& ) { return true; }
bool operator!=( const comparable_inconvertible&, const comparable_inconvertible& ) { return true; }
bool operator!=( const comparable&, const comparable_inconvertible& ) { return true; }
bool operator!=( const comparable_inconvertible&, const comparable& ) { return true; }
bool operator!=( const comparable&, const partially_comparable& ) { return true; }
bool operator!=( const partially_comparable&, const comparable& ) { return true; }
bool operator<( const comparable&, const comparable& ) { return true; }
bool operator<( const comparable_inconvertible&, const comparable_inconvertible& ) { return true; }
bool operator<( const comparable&, const comparable_inconvertible& ) { return true; }
bool operator<( const comparable_inconvertible&, const comparable& ) { return true; }
bool operator<( const comparable&, const partially_comparable& ) { return true; }
bool operator<( const partially_comparable&, const comparable& ) { return true; }
bool operator>( const comparable&, const comparable& ) { return true; }
bool operator>( const comparable_inconvertible&, const comparable_inconvertible& ) { return true; }
bool operator>( const comparable&, const comparable_inconvertible& ) { return true; }
bool operator>( const comparable_inconvertible&, const comparable& ) { return true; }
bool operator>( const comparable&, const partially_comparable& ) { return true; }
bool operator>( const partially_comparable&, const comparable& ) { return true; }
bool operator<=( const comparable&, const comparable& ) { return true; }
bool operator<=( const comparable_inconvertible&, const comparable_inconvertible& ) { return true; }
bool operator<=( const comparable&, const comparable_inconvertible& ) { return true; }
bool operator<=( const comparable_inconvertible&, const comparable& ) { return true; }
bool operator<=( const comparable&, const partially_comparable& ) { return true; }
bool operator<=( const partially_comparable&, const comparable& ) { return true; }
bool operator>=( const comparable&, const comparable& ) { return true; }
bool operator>=( const comparable_inconvertible&, const comparable_inconvertible& ) { return true; }
bool operator>=( const comparable&, const comparable_inconvertible& ) { return true; }
bool operator>=( const comparable_inconvertible&, const comparable& ) { return true; }
bool operator>=( const comparable&, const partially_comparable& ) { return true; }
bool operator>=( const partially_comparable&, const comparable& ) { return true; }
bool operator&&( const volatile comparable&, const volatile comparable& ) { return true; }
bool operator&&( const volatile comparable_inconvertible&, const volatile comparable_inconvertible& ) { return true; }
bool operator&&( const volatile comparable&, const volatile comparable_inconvertible& ) { return true; }
bool operator&&( const volatile comparable_inconvertible&, const volatile comparable& ) { return true; }
bool operator&&( const volatile comparable&, const volatile partially_comparable& ) { return true; }
bool operator&&( const volatile partially_comparable&, const volatile comparable& ) { return true; }
bool operator||( const volatile comparable&, const volatile comparable& ) { return true; }
bool operator||( const volatile comparable_inconvertible&, const volatile comparable_inconvertible& ) { return true; }
bool operator||( const volatile comparable&, const volatile comparable_inconvertible& ) { return true; }
bool operator||( const volatile comparable_inconvertible&, const volatile comparable& ) { return true; }
bool operator||( const volatile comparable&, const volatile partially_comparable& ) { return true; }
bool operator||( const volatile partially_comparable&, const volatile comparable& ) { return true; }
bool operator==( const volatile comparable&, const volatile comparable& ) { return true; }
bool operator==( const volatile comparable_inconvertible&, const volatile comparable_inconvertible& ) { return true; }
bool operator==( const volatile comparable&, const volatile comparable_inconvertible& ) { return true; }
bool operator==( const volatile comparable_inconvertible&, const volatile comparable& ) { return true; }
bool operator==( const volatile comparable&, const volatile partially_comparable& ) { return true; }
bool operator==( const volatile partially_comparable&, const volatile comparable& ) { return true; }
bool operator!=( const volatile comparable&, const volatile comparable& ) { return true; }
bool operator!=( const volatile comparable_inconvertible&, const volatile comparable_inconvertible& ) { return true; }
bool operator!=( const volatile comparable&, const volatile comparable_inconvertible& ) { return true; }
bool operator!=( const volatile comparable_inconvertible&, const volatile comparable& ) { return true; }
bool operator!=( const volatile comparable&, const volatile partially_comparable& ) { return true; }
bool operator!=( const volatile partially_comparable&, const volatile comparable& ) { return true; }
bool operator<( const volatile comparable&, const volatile comparable& ) { return true; }
bool operator<( const volatile comparable_inconvertible&, const volatile comparable_inconvertible& ) { return true; }
bool operator<( const volatile comparable&, const volatile comparable_inconvertible& ) { return true; }
bool operator<( const volatile comparable_inconvertible&, const volatile comparable& ) { return true; }
bool operator<( const volatile comparable&, const volatile partially_comparable& ) { return true; }
bool operator<( const volatile partially_comparable&, const volatile comparable& ) { return true; }
bool operator>( const volatile comparable&, const volatile comparable& ) { return true; }
bool operator>( const volatile comparable_inconvertible&, const volatile comparable_inconvertible& ) { return true; }
bool operator>( const volatile comparable&, const volatile comparable_inconvertible& ) { return true; }
bool operator>( const volatile comparable_inconvertible&, const volatile comparable& ) { return true; }
bool operator>( const volatile comparable&, const volatile partially_comparable& ) { return true; }
bool operator>( const volatile partially_comparable&, const volatile comparable& ) { return true; }
bool operator<=( const volatile comparable&, const volatile comparable& ) { return true; }
bool operator<=( const volatile comparable_inconvertible&, const volatile comparable_inconvertible& ) { return true; }
bool operator<=( const volatile comparable&, const volatile comparable_inconvertible& ) { return true; }
bool operator<=( const volatile comparable_inconvertible&, const volatile comparable& ) { return true; }
bool operator<=( const volatile comparable&, const volatile partially_comparable& ) { return true; }
bool operator<=( const volatile partially_comparable&, const volatile comparable& ) { return true; }
bool operator>=( const volatile comparable&, const volatile comparable& ) { return true; }
bool operator>=( const volatile comparable_inconvertible&, const volatile comparable_inconvertible& ) { return true; }
bool operator>=( const volatile comparable&, const volatile comparable_inconvertible& ) { return true; }
bool operator>=( const volatile comparable_inconvertible&, const volatile comparable& ) { return true; }
bool operator>=( const volatile comparable&, const volatile partially_comparable& ) { return true; }
bool operator>=( const volatile partially_comparable&, const volatile comparable& ) { return true; }
struct callable {
  int operator()( int a, int b ) { return a + b; };
};
struct predicate {
  bool operator()( const base&, const other& ) { return true; };
};
struct relation {
  bool operator()( const base&, const base& ) { return true; };
  bool operator()( const other&, const other& ) { return true; };
  bool operator()( const base&, const other& ) { return true; };
  bool operator()( const other&, const base& ) { return true; };
};
struct implicit_input_iterator {
  using value_type = int;
  int &operator*() const {
    static int value = 0;
    return value;
  }
  implicit_input_iterator &operator++() {
    return *this;
  }
  implicit_input_iterator operator++(int) {
    return *this;
  }
};
bool operator==( const implicit_input_iterator&, const implicit_input_iterator& ) { return true; }
bool operator!=( const implicit_input_iterator&, const implicit_input_iterator& ) { return false; }
int operator-( const implicit_input_iterator&, const implicit_input_iterator& ) { return 0; }
struct explicit_input_iterator {
  using value_type = int;
  using difference_type = int;
  using pointer = int*;
  using reference = int&;
  int &operator*() const {
    static int value = 0;
    return value;
  }
  explicit_input_iterator &operator++() {
    return *this;
  }
  explicit_input_iterator operator++(int) {
    return *this;
  }
};
bool operator==( const explicit_input_iterator&, const explicit_input_iterator& ) { return true; }
bool operator!=( const explicit_input_iterator&, const explicit_input_iterator& ) { return false; }
int operator-( const explicit_input_iterator&, const explicit_input_iterator& ) { return 0; }
struct implicit_forward_iterator {
  using value_type = int;
  int &operator*() const {
    static int value = 0;
    return value;
  }
  implicit_forward_iterator &operator++() {
    return *this;
  }
  implicit_forward_iterator operator++(int) {
    return *this;
  }
};
bool operator==( const implicit_forward_iterator&, const implicit_forward_iterator& ) { return true; }
bool operator!=( const implicit_forward_iterator&, const implicit_forward_iterator& ) { return false; }
int operator-( const implicit_forward_iterator&, const implicit_forward_iterator& ) { return 0; }
struct explicit_forward_iterator {
  using value_type = int;
  using difference_type = int;
  using pointer = int*;
  using reference = int&;
  int &operator*() const {
    static int value = 0;
    return value;
  }
  explicit_forward_iterator &operator++() {
    return *this;
  }
  explicit_forward_iterator operator++(int) {
    return *this;
  }
};
bool operator==( const explicit_forward_iterator&, const explicit_forward_iterator& ) { return true; }
bool operator!=( const explicit_forward_iterator&, const explicit_forward_iterator& ) { return false; }
int operator-( const explicit_forward_iterator&, const explicit_forward_iterator& ) { return 0; }
struct implicit_bidirectional_iterator {
  using value_type = int;
  int &operator*() const {
    static int value = 0;
    return value;
  }
  implicit_bidirectional_iterator &operator++() {
    return *this;
  }
  implicit_bidirectional_iterator operator++(int) {
    return *this;
  }
  implicit_bidirectional_iterator &operator--() {
    return *this;
  }
  implicit_bidirectional_iterator operator--(int) {
    return *this;
  }
};
bool operator==( const implicit_bidirectional_iterator&, const implicit_bidirectional_iterator& ) { return true; }
bool operator!=( const implicit_bidirectional_iterator&, const implicit_bidirectional_iterator& ) { return false; }
int operator-( const implicit_bidirectional_iterator&, const implicit_bidirectional_iterator& ) { return 0; }
struct explicit_bidirectional_iterator {
  using value_type = int;
  using difference_type = int;
  using pointer = int*;
  using reference = int&;
  int &operator*() const {
    static int value = 0;
    return value;
  }
  explicit_bidirectional_iterator &operator++() {
    return *this;
  }
  explicit_bidirectional_iterator operator++(int) {
    return *this;
  }
  explicit_bidirectional_iterator &operator--() {
    return *this;
  }
  explicit_bidirectional_iterator operator--(int) {
    return *this;
  }
};
bool operator==( const explicit_bidirectional_iterator&, const explicit_bidirectional_iterator& ) { return true; }
bool operator!=( const explicit_bidirectional_iterator&, const explicit_bidirectional_iterator& ) { return false; }
int operator-( const explicit_bidirectional_iterator&, const explicit_bidirectional_iterator& ) { return 0; }
struct implicit_random_access_iterator {
  using value_type = int;
  int &operator*() const {
    static int value = 0;
    return value;
  }
  int &operator[](int) const {
    static int value = 0;
    return value;
  }
  implicit_random_access_iterator &operator++() {
    return *this;
  }
  implicit_random_access_iterator operator++(int) {
    return *this;
  }
  implicit_random_access_iterator &operator+=(int) {
    return *this;
  }
  implicit_random_access_iterator &operator--() {
    return *this;
  }
  implicit_random_access_iterator operator--(int) {
    return *this;
  }
  implicit_random_access_iterator &operator-=(int) {
    return *this;
  }
};
bool operator==( const implicit_random_access_iterator&, const implicit_random_access_iterator& ) { return true; }
bool operator!=( const implicit_random_access_iterator&, const implicit_random_access_iterator& ) { return false; }
bool operator<( const implicit_random_access_iterator&, const implicit_random_access_iterator& ) { return false; }
bool operator>( const implicit_random_access_iterator&, const implicit_random_access_iterator& ) { return false; }
bool operator<=( const implicit_random_access_iterator&, const implicit_random_access_iterator& ) { return true; }
bool operator>=( const implicit_random_access_iterator&, const implicit_random_access_iterator& ) { return true; }
int operator-( const implicit_random_access_iterator&, const implicit_random_access_iterator& ) { return 0; }
implicit_random_access_iterator operator+( int, const implicit_random_access_iterator &a ) { return a; }
implicit_random_access_iterator operator+( const implicit_random_access_iterator &a, int ) { return a; }
implicit_random_access_iterator operator-( int, const implicit_random_access_iterator &a ) { return a; }
implicit_random_access_iterator operator-( const implicit_random_access_iterator &a, int ) { return a; }
struct explicit_random_access_iterator {
  using value_type = int;
  using difference_type = int;
  using pointer = int*;
  using reference = int&;
  int &operator*() const {
    static int value = 0;
    return value;
  }
  int &operator[](int) const {
    static int value = 0;
    return value;
  }
  explicit_random_access_iterator &operator++() {
    return *this;
  }
  explicit_random_access_iterator operator++(int) {
    return *this;
  }
  explicit_random_access_iterator &operator+=(int) {
    return *this;
  }
  explicit_random_access_iterator &operator--() {
    return *this;
  }
  explicit_random_access_iterator operator--(int) {
    return *this;
  }
  explicit_random_access_iterator &operator-=(int) {
    return *this;
  }
};
bool operator==( const explicit_random_access_iterator&, const explicit_random_access_iterator& ) { return true; }
bool operator!=( const explicit_random_access_iterator&, const explicit_random_access_iterator& ) { return false; }
bool operator<( const explicit_random_access_iterator&, const explicit_random_access_iterator& ) { return false; }
bool operator>( const explicit_random_access_iterator&, const explicit_random_access_iterator& ) { return false; }
bool operator<=( const explicit_random_access_iterator&, const explicit_random_access_iterator& ) { return true; }
bool operator>=( const explicit_random_access_iterator&, const explicit_random_access_iterator& ) { return true; }
int operator-( const explicit_random_access_iterator&, const explicit_random_access_iterator& ) { return 0; }
explicit_random_access_iterator operator+( int, const explicit_random_access_iterator &a ) { return a; }
explicit_random_access_iterator operator+( const explicit_random_access_iterator &a, int ) { return a; }
explicit_random_access_iterator operator-( int, const explicit_random_access_iterator &a ) { return a; }
explicit_random_access_iterator operator-( const explicit_random_access_iterator &a, int ) { return a; }
template< typename T >
struct sentinel {};
template< typename T >
bool operator==( const sentinel< T >&, const sentinel< T >& ) { return true; }
template< typename T >
bool operator==( const sentinel< T >&, const T& ) { return true; }
template< typename T >
bool operator==( const T&, const sentinel< T >& ) { return true; }
template< typename T >
bool operator!=( const sentinel< T >&, const sentinel< T >& ) { return false; }
template< typename T >
bool operator!=( const sentinel< T >&, const T& ) { return false; }
template< typename T >
bool operator!=( const T&, const sentinel< T >& ) { return false; }
template< typename T >
struct sized_sentinel {};
template< typename T >
bool operator==( const sized_sentinel< T >&, const sized_sentinel< T >& ) { return true; }
template< typename T >
bool operator==( const sized_sentinel< T >&, const T& ) { return true; }
template< typename T >
bool operator==( const T&, const sized_sentinel< T >& ) { return true; }
template< typename T >
bool operator!=( const sized_sentinel< T >&, const sized_sentinel< T >& ) { return false; }
template< typename T >
bool operator!=( const sized_sentinel< T >&, const T& ) { return false; }
template< typename T >
bool operator!=( const T&, const sized_sentinel< T >& ) { return false; }
template< typename T >
auto operator-( const T &i, const sized_sentinel< T >& ) { return i - i; }
template< typename T >
auto operator-( const sized_sentinel< T >&, const T &i ) { return i - i; }

BOOST_AUTO_TEST_CASE(Same) {
  BOOST_CHECK_EQUAL( ( slce::is_same< base, base >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_same< base, inherited >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_same< base, other >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_same< base, const base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_same< base, volatile base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_same< base, base& >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_same< base, base* >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_same< base, int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_same< base, const int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_same< base, volatile int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_same< base, int& >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_same< base, int* >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_same< inherited, base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_same< other, base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_same< const base, base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_same< volatile base, base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_same< base&, base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_same< base*, base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_same< int, base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_same< const int, base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_same< volatile int, base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_same< int&, base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_same< int*, base >::value ), false );
}

BOOST_AUTO_TEST_CASE(DerivedFrom) {
  BOOST_CHECK_EQUAL( ( slce::is_derived_from< base, base >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_derived_from< base, inherited >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_derived_from< base, other >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_derived_from< base, const base >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_derived_from< base, volatile base >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_derived_from< base, base& >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_derived_from< base, base* >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_derived_from< base, int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_derived_from< base, const int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_derived_from< base, volatile int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_derived_from< base, int& >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_derived_from< base, int* >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_derived_from< inherited, base >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_derived_from< other, base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_derived_from< const base, base >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_derived_from< volatile base, base >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_derived_from< base&, base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_derived_from< base*, base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_derived_from< int, base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_derived_from< const int, base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_derived_from< volatile int, base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_derived_from< int&, base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_derived_from< int*, base >::value ), false );
}

BOOST_AUTO_TEST_CASE(ConvertibleTo) {
  BOOST_CHECK_EQUAL( ( slce::is_convertible_to< base, base >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_convertible_to< base, inherited >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_convertible_to< base, other >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_convertible_to< base, const base >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_convertible_to< base, volatile base >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_convertible_to< base, base& >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_convertible_to< base, base* >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_convertible_to< base, int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_convertible_to< base, const int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_convertible_to< base, volatile int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_convertible_to< base, int& >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_convertible_to< base, int* >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_convertible_to< inherited, base >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_convertible_to< other, base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_convertible_to< const base, base >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_convertible_to< volatile base, base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_convertible_to< base&, base >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_convertible_to< base*, base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_convertible_to< int, base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_convertible_to< const int, base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_convertible_to< volatile int, base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_convertible_to< int&, base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_convertible_to< int*, base >::value ), false );
}

BOOST_AUTO_TEST_CASE(CommonReference) {
  BOOST_CHECK_EQUAL( ( slce::is_common_reference< base, base >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_common_reference< base, inherited >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_common_reference< base, other >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_common_reference< base, const base >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_common_reference< base, volatile base >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_common_reference< base, base& >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_common_reference< base, base* >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_common_reference< base, int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_common_reference< base, const int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_common_reference< base, volatile int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_common_reference< base, int& >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_common_reference< base, int* >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_common_reference< inherited, base >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_common_reference< other, base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_common_reference< const base, base >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_common_reference< volatile base, base >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_common_reference< base&, base >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_common_reference< base*, base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_common_reference< int, base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_common_reference< const int, base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_common_reference< volatile int, base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_common_reference< int&, base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_common_reference< int*, base >::value ), false );
}

BOOST_AUTO_TEST_CASE(Common) {
  BOOST_CHECK_EQUAL( ( slce::is_common< base, base >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_common< base, inherited >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_common< base, other >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_common< base, const base >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_common< base, volatile base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_common< base, base& >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_common< base, base* >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_common< base, int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_common< base, const int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_common< base, volatile int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_common< base, int& >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_common< base, int* >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_common< inherited, base >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_common< other, base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_common< const base, base >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_common< volatile base, base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_common< base&, base >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_common< base*, base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_common< int, base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_common< const int, base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_common< volatile int, base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_common< int&, base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_common< int*, base >::value ), false );
}

BOOST_AUTO_TEST_CASE(Integral) {
  BOOST_CHECK_EQUAL( ( slce::is_integral< base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_integral< inherited >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_integral< other >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_integral< const base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_integral< volatile base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_integral< base& >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_integral< base* >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_integral< int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_integral< const int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_integral< volatile int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_integral< int& >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_integral< int* >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_integral< unsigned int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_integral< const unsigned int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_integral< volatile unsigned int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_integral< unsigned int& >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_integral< unsigned int* >::value ), false );
}

BOOST_AUTO_TEST_CASE(SignedIntegral) {
  BOOST_CHECK_EQUAL( ( slce::is_signed_integral< base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_signed_integral< inherited >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_signed_integral< other >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_signed_integral< const base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_signed_integral< volatile base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_signed_integral< base& >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_signed_integral< base* >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_signed_integral< int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_signed_integral< const int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_signed_integral< volatile int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_signed_integral< int& >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_signed_integral< int* >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_signed_integral< unsigned int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_signed_integral< const unsigned int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_signed_integral< volatile unsigned int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_signed_integral< unsigned int& >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_signed_integral< unsigned int* >::value ), false );
}

BOOST_AUTO_TEST_CASE(UnsignedIntegral) {
  BOOST_CHECK_EQUAL( ( slce::is_unsigned_integral< base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_unsigned_integral< inherited >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_unsigned_integral< other >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_unsigned_integral< const base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_unsigned_integral< volatile base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_unsigned_integral< base& >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_unsigned_integral< base* >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_unsigned_integral< int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_unsigned_integral< const int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_unsigned_integral< volatile int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_unsigned_integral< int& >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_unsigned_integral< int* >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_unsigned_integral< unsigned int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_unsigned_integral< const unsigned int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_unsigned_integral< volatile unsigned int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_unsigned_integral< unsigned int& >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_unsigned_integral< unsigned int* >::value ), false );
}

BOOST_AUTO_TEST_CASE(Assignable) {
  BOOST_CHECK_EQUAL( ( slce::is_assignable< base, base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_assignable< base, const base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_assignable< base, volatile base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_assignable< base, base& >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_assignable< base, base* >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_assignable< base, int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_assignable< base, const int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_assignable< base, volatile int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_assignable< base, int& >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_assignable< base, int* >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_assignable< const base, base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_assignable< volatile base, base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_assignable< base&, base >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_assignable< base*, base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_assignable< int, base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_assignable< const int, base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_assignable< volatile int, base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_assignable< int&, base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_assignable< int*, base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_assignable< non_copyable&, non_copyable >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_assignable< copyable&, copyable >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_assignable< movable&, movable >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_assignable< partially_castable_t2&, partially_castable_t1 >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_assignable< fully_castable_t2&, fully_castable_t1 >::value ), true );
}

BOOST_AUTO_TEST_CASE(Swappable) {
  BOOST_CHECK_EQUAL( ( slce::is_swappable< base >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_swappable< const base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_swappable< volatile base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_swappable< base& >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_swappable< base* >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_swappable< int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_swappable< const int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_swappable< volatile int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_swappable< int& >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_swappable< int* >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_swappable< non_copyable >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_swappable< copyable >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_swappable< movable >::value ), true );
}

BOOST_AUTO_TEST_CASE(SwappableWith) {
  BOOST_CHECK_EQUAL( ( slce::is_swappable_with< base, base >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_swappable_with< base, const base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_swappable_with< base, volatile base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_swappable_with< base, base& >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_swappable_with< base, base* >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_swappable_with< base, int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_swappable_with< base, const int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_swappable_with< base, volatile int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_swappable_with< base, int& >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_swappable_with< base, int* >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_swappable_with< const base, base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_swappable_with< volatile base, base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_swappable_with< base&, base >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_swappable_with< base*, base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_swappable_with< int, base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_swappable_with< const int, base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_swappable_with< volatile int, base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_swappable_with< int&, base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_swappable_with< int*, base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_swappable_with< non_copyable, non_copyable >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_swappable_with< copyable, copyable >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_swappable_with< movable, movable >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_swappable_with< partially_castable_t2, partially_castable_t1 >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_swappable_with< fully_castable_t2, fully_castable_t1 >::value ), false );
}

BOOST_AUTO_TEST_CASE(Destructible) {
  BOOST_CHECK_EQUAL( ( slce::is_destructible< destructible >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_destructible< const destructible >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_destructible< volatile destructible >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_destructible< destructible& >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_destructible< destructible* >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_destructible< int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_destructible< const int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_destructible< volatile int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_destructible< int& >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_destructible< int* >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_destructible< non_destructible >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_destructible< const non_destructible >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_destructible< volatile non_destructible >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_destructible< non_destructible& >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_destructible< non_destructible* >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_destructible< constructible_with_int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_destructible< const constructible_with_int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_destructible< volatile constructible_with_int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_destructible< constructible_with_int& >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_destructible< constructible_with_int* >::value ), true );
}

BOOST_AUTO_TEST_CASE(Constructible) {
  BOOST_CHECK_EQUAL( ( slce::is_constructible< default_constructible >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_constructible< const default_constructible >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_constructible< volatile default_constructible >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_constructible< default_constructible& >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_constructible< default_constructible* >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_constructible< default_constructible, int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_constructible< const default_constructible, int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_constructible< volatile default_constructible, int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_constructible< default_constructible&, int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_constructible< default_constructible*, int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_constructible< int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_constructible< const int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_constructible< volatile int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_constructible< int& >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_constructible< int* >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_constructible< int, int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_constructible< const int, int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_constructible< volatile int, int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_constructible< int&, int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_constructible< int*, int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_constructible< constructible_with_int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_constructible< const constructible_with_int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_constructible< volatile constructible_with_int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_constructible< constructible_with_int& >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_constructible< constructible_with_int* >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_constructible< constructible_with_int, int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_constructible< const constructible_with_int, int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_constructible< volatile constructible_with_int, int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_constructible< constructible_with_int&, int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_constructible< constructible_with_int*, int >::value ), false );
}

BOOST_AUTO_TEST_CASE(DefaultConstructible) {
  BOOST_CHECK_EQUAL( ( slce::is_default_constructible< default_constructible >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_default_constructible< const default_constructible >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_default_constructible< volatile default_constructible >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_default_constructible< default_constructible& >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_default_constructible< default_constructible* >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_default_constructible< int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_default_constructible< const int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_default_constructible< volatile int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_default_constructible< int& >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_default_constructible< int* >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_default_constructible< constructible_with_int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_default_constructible< const constructible_with_int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_default_constructible< volatile constructible_with_int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_default_constructible< constructible_with_int& >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_default_constructible< constructible_with_int* >::value ), true );
}

BOOST_AUTO_TEST_CASE(CopyConstructible) {
  BOOST_CHECK_EQUAL( ( slce::is_copy_constructible< copyable >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_copy_constructible< const copyable >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_copy_constructible< volatile copyable >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_copy_constructible< copyable& >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_copy_constructible< copyable* >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_copy_constructible< int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_copy_constructible< const int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_copy_constructible< volatile int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_copy_constructible< int& >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_copy_constructible< int* >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_copy_constructible< non_copyable >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_copy_constructible< const non_copyable >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_copy_constructible< volatile non_copyable >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_copy_constructible< non_copyable& >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_copy_constructible< non_copyable* >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_copy_constructible< movable >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_copy_constructible< const movable >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_copy_constructible< volatile movable >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_copy_constructible< movable& >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_copy_constructible< movable* >::value ), true );
}

BOOST_AUTO_TEST_CASE(MoveConstructible) {
  BOOST_CHECK_EQUAL( ( slce::is_move_constructible< copyable >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_move_constructible< const copyable >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_move_constructible< volatile copyable >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_move_constructible< copyable& >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_move_constructible< copyable* >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_move_constructible< int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_move_constructible< const int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_move_constructible< volatile int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_move_constructible< int& >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_move_constructible< int* >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_move_constructible< non_copyable >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_move_constructible< const non_copyable >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_move_constructible< volatile non_copyable >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_move_constructible< non_copyable& >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_move_constructible< non_copyable* >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_move_constructible< movable >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_move_constructible< const movable >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_move_constructible< volatile movable >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_move_constructible< movable& >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_move_constructible< movable* >::value ), true );
}

BOOST_AUTO_TEST_CASE(Boolean) {
  BOOST_CHECK_EQUAL( ( slce::is_boolean< base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_boolean< const base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_boolean< volatile base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_boolean< base& >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_boolean< base* >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_boolean< int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_boolean< const int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_boolean< volatile int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_boolean< int& >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_boolean< int* >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_boolean< bool >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_boolean< const bool >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_boolean< volatile bool >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_boolean< bool& >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_boolean< bool* >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_boolean< bool_like >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_boolean< const bool_like >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_boolean< volatile bool_like >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_boolean< bool_like& >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_boolean< bool_like* >::value ), false );
}

BOOST_AUTO_TEST_CASE(EqualityComparable) {
  BOOST_CHECK_EQUAL( ( slce::is_equality_comparable< comparable >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_equality_comparable< const comparable >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_equality_comparable< volatile comparable >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_equality_comparable< comparable& >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_equality_comparable< comparable* >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_equality_comparable< comparable_inconvertible >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_equality_comparable< const comparable_inconvertible >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_equality_comparable< volatile comparable_inconvertible >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_equality_comparable< comparable_inconvertible& >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_equality_comparable< comparable_inconvertible* >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_equality_comparable< partially_comparable >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_equality_comparable< const partially_comparable >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_equality_comparable< volatile partially_comparable >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_equality_comparable< partially_comparable& >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_equality_comparable< partially_comparable* >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_equality_comparable< int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_equality_comparable< const int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_equality_comparable< volatile int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_equality_comparable< int& >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_equality_comparable< int* >::value ), true );
}

BOOST_AUTO_TEST_CASE(EqualityComparableWith) {
  BOOST_CHECK_EQUAL( ( slce::is_equality_comparable_with< comparable, comparable >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_equality_comparable_with< comparable, const comparable >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_equality_comparable_with< comparable, volatile comparable >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_equality_comparable_with< comparable, comparable& >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_equality_comparable_with< comparable, comparable* >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_equality_comparable_with< const comparable, comparable >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_equality_comparable_with< volatile comparable, comparable >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_equality_comparable_with< comparable&, comparable >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_equality_comparable_with< comparable*, comparable >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_equality_comparable_with< comparable, comparable_inconvertible >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_equality_comparable_with< comparable_inconvertible, comparable >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_equality_comparable_with< comparable, comparable_convertible >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_equality_comparable_with< comparable_convertible, comparable >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_equality_comparable_with< incomparable, incomparable >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_equality_comparable_with< comparable, incomparable >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_equality_comparable_with< incomparable, comparable >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_equality_comparable_with< int, int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_equality_comparable_with< int, const int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_equality_comparable_with< int, volatile int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_equality_comparable_with< int, int& >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_equality_comparable_with< int, int* >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_equality_comparable_with< const int, int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_equality_comparable_with< volatile int, int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_equality_comparable_with< int&, int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_equality_comparable_with< int*, int >::value ), false );
}

BOOST_AUTO_TEST_CASE(StrictTotallyOrdered) {
  BOOST_CHECK_EQUAL( ( slce::is_strict_totally_ordered< comparable >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_strict_totally_ordered< const comparable >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_strict_totally_ordered< volatile comparable >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_strict_totally_ordered< comparable& >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_strict_totally_ordered< comparable* >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_strict_totally_ordered< comparable_inconvertible >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_strict_totally_ordered< const comparable_inconvertible >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_strict_totally_ordered< volatile comparable_inconvertible >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_strict_totally_ordered< comparable_inconvertible& >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_strict_totally_ordered< comparable_inconvertible* >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_strict_totally_ordered< partially_comparable >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_strict_totally_ordered< const partially_comparable >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_strict_totally_ordered< volatile partially_comparable >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_strict_totally_ordered< partially_comparable& >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_strict_totally_ordered< partially_comparable* >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_strict_totally_ordered< int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_strict_totally_ordered< const int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_strict_totally_ordered< volatile int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_strict_totally_ordered< int& >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_strict_totally_ordered< int* >::value ), true );
}

BOOST_AUTO_TEST_CASE(StrictTotallyOrderedWith) {
  BOOST_CHECK_EQUAL( ( slce::is_strict_totally_ordered_with< comparable, comparable >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_strict_totally_ordered_with< comparable, const comparable >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_strict_totally_ordered_with< comparable, volatile comparable >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_strict_totally_ordered_with< comparable, comparable& >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_strict_totally_ordered_with< comparable, comparable* >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_strict_totally_ordered_with< const comparable, comparable >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_strict_totally_ordered_with< volatile comparable, comparable >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_strict_totally_ordered_with< comparable&, comparable >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_strict_totally_ordered_with< comparable*, comparable >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_strict_totally_ordered_with< comparable, comparable_inconvertible >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_strict_totally_ordered_with< comparable_inconvertible, comparable >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_strict_totally_ordered_with< comparable, comparable_convertible >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_strict_totally_ordered_with< comparable_convertible, comparable >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_strict_totally_ordered_with< incomparable, incomparable >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_strict_totally_ordered_with< comparable, incomparable >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_strict_totally_ordered_with< incomparable, comparable >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_strict_totally_ordered_with< int, int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_strict_totally_ordered_with< int, const int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_strict_totally_ordered_with< int, volatile int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_strict_totally_ordered_with< int, int& >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_strict_totally_ordered_with< int, int* >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_strict_totally_ordered_with< const int, int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_strict_totally_ordered_with< volatile int, int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_strict_totally_ordered_with< int&, int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_strict_totally_ordered_with< int*, int >::value ), false );
}

BOOST_AUTO_TEST_CASE(Movable) {
  BOOST_CHECK_EQUAL( ( slce::is_movable< base >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_movable< const base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_movable< volatile base >::value ), false ); //
  BOOST_CHECK_EQUAL( ( slce::is_movable< base& >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_movable< base* >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_movable< copyable >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_movable< const copyable >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_movable< volatile copyable >::value ), false ); //
  BOOST_CHECK_EQUAL( ( slce::is_movable< copyable& >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_movable< copyable* >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_movable< movable >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_movable< const movable >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_movable< volatile movable >::value ), false ); //
  BOOST_CHECK_EQUAL( ( slce::is_movable< movable& >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_movable< movable* >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_movable< non_copyable >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_movable< const non_copyable >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_movable< volatile non_copyable >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_movable< non_copyable& >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_movable< non_copyable* >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_movable< int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_movable< const int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_movable< volatile int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_movable< int& >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_movable< int* >::value ), true );
}

BOOST_AUTO_TEST_CASE(Copyable) {
  BOOST_CHECK_EQUAL( ( slce::is_copyable< base >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_copyable< const base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_copyable< volatile base >::value ), false ); //
  BOOST_CHECK_EQUAL( ( slce::is_copyable< base& >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_copyable< base* >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_copyable< copyable >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_copyable< const copyable >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_copyable< volatile copyable >::value ), false ); //
  BOOST_CHECK_EQUAL( ( slce::is_copyable< copyable& >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_copyable< copyable* >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_copyable< movable >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_copyable< const movable >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_copyable< volatile movable >::value ), false ); //
  BOOST_CHECK_EQUAL( ( slce::is_copyable< movable& >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_copyable< movable* >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_copyable< non_copyable >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_copyable< const non_copyable >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_copyable< volatile non_copyable >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_copyable< non_copyable& >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_copyable< non_copyable* >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_copyable< int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_copyable< const int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_copyable< volatile int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_copyable< int& >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_copyable< int* >::value ), true );
}

BOOST_AUTO_TEST_CASE(Semiregular) {
  BOOST_CHECK_EQUAL( ( slce::is_semiregular< base >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_semiregular< const base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_semiregular< volatile base >::value ), false ); //
  BOOST_CHECK_EQUAL( ( slce::is_semiregular< base& >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_semiregular< base* >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_semiregular< copyable >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_semiregular< const copyable >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_semiregular< volatile copyable >::value ), false ); //
  BOOST_CHECK_EQUAL( ( slce::is_semiregular< copyable& >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_semiregular< copyable* >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_semiregular< movable >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_semiregular< const movable >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_semiregular< volatile movable >::value ), false ); //
  BOOST_CHECK_EQUAL( ( slce::is_semiregular< movable& >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_semiregular< movable* >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_semiregular< non_copyable >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_semiregular< const non_copyable >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_semiregular< volatile non_copyable >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_semiregular< non_copyable& >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_semiregular< non_copyable* >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_semiregular< int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_semiregular< const int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_semiregular< volatile int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_semiregular< int& >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_semiregular< int* >::value ), true );
}

BOOST_AUTO_TEST_CASE(Regular) {
  BOOST_CHECK_EQUAL( ( slce::is_regular< base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_regular< const base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_regular< volatile base >::value ), false ); //
  BOOST_CHECK_EQUAL( ( slce::is_regular< base& >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_regular< base* >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_regular< copyable >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_regular< const copyable >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_regular< volatile copyable >::value ), false ); //
  BOOST_CHECK_EQUAL( ( slce::is_regular< copyable& >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_regular< copyable* >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_regular< movable >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_regular< const movable >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_regular< volatile movable >::value ), false ); //
  BOOST_CHECK_EQUAL( ( slce::is_regular< movable& >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_regular< movable* >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_regular< non_copyable >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_regular< const non_copyable >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_regular< volatile non_copyable >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_regular< non_copyable& >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_regular< non_copyable* >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_regular< int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_regular< const int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_regular< volatile int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_regular< int& >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_regular< int* >::value ), true );
}

BOOST_AUTO_TEST_CASE(Invocable) {
#ifdef __cpp_lib_invoke
  BOOST_CHECK_EQUAL( ( slce::is_invocable< void(*)() >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_invocable< void(*)(), int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_invocable< void(*)( int ) >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_invocable< void(*)( int ), int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_invocable< callable, int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_invocable< callable, int, int >::value ), true );
#else
  BOOST_CHECK_EQUAL( ( slce::is_invocable< void(*)() >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_invocable< void(*)(), int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_invocable< void(*)( int ) >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_invocable< void(*)( int ), int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_invocable< callable, int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_invocable< callable, int, int >::value ), false );
#endif
}

BOOST_AUTO_TEST_CASE(RegularInvocable) {
#ifdef __cpp_lib_invoke
  BOOST_CHECK_EQUAL( ( slce::is_regular_invocable< void(*)() >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_regular_invocable< void(*)(), int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_regular_invocable< void(*)( int ) >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_regular_invocable< void(*)( int ), int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_regular_invocable< callable, int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_regular_invocable< callable, int, int >::value ), true );
#else
  BOOST_CHECK_EQUAL( ( slce::is_regular_invocable< void(*)() >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_regular_invocable< void(*)(), int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_regular_invocable< void(*)( int ) >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_regular_invocable< void(*)( int ), int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_regular_invocable< callable, int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_regular_invocable< callable, int, int >::value ), false );
#endif
}

BOOST_AUTO_TEST_CASE(Predicate) {
#ifdef __cpp_lib_invoke
  BOOST_CHECK_EQUAL( ( slce::is_predicate< void(*)() >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_predicate< void(*)(), int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_predicate< void(*)( int ) >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_predicate< void(*)( int ), int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_predicate< bool(*)( int ) >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_predicate< bool(*)( int ), int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_predicate< callable, int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_predicate< callable, int, int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_predicate< predicate, base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_predicate< predicate, base, other >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_predicate< relation, base, other >::value ), true );
#else
  BOOST_CHECK_EQUAL( ( slce::is_predicate< void(*)() >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_predicate< void(*)(), int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_predicate< void(*)( int ) >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_predicate< void(*)( int ), int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_predicate< bool(*)( int ) >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_predicate< bool(*)( int ), int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_predicate< callable, int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_predicate< callable, int, int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_predicate< predicate, base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_predicate< predicate, base, other >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_predicate< relation, base, other >::value ), false );
#endif
}

BOOST_AUTO_TEST_CASE(Relation) {
#ifdef __cpp_lib_invoke
  BOOST_CHECK_EQUAL( ( slce::is_relation< callable, base, other >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_relation< predicate, base, other >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_relation< relation, base, other >::value ), true );
#else
  BOOST_CHECK_EQUAL( ( slce::is_relation< callable, base, other >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_relation< predicate, base, other >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_relation< relation, base, other >::value ), false );
#endif
}

BOOST_AUTO_TEST_CASE(StrictWeakOrder) {
#ifdef __cpp_lib_invoke
  BOOST_CHECK_EQUAL( ( slce::is_strict_weak_order< callable, base, other >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_strict_weak_order< predicate, base, other >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_strict_weak_order< relation, base, other >::value ), true );
#else
  BOOST_CHECK_EQUAL( ( slce::is_strict_weak_order< callable, base, other >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_strict_weak_order< predicate, base, other >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_strict_weak_order< relation, base, other >::value ), false );
#endif
}

BOOST_AUTO_TEST_CASE(Cpp17Iterator) {
  BOOST_CHECK_EQUAL( ( slce::detail::is_cpp17_iterator< base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::detail::is_cpp17_iterator< explicit_forward_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::detail::is_cpp17_iterator< implicit_forward_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::detail::is_cpp17_iterator< explicit_bidirectional_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::detail::is_cpp17_iterator< implicit_bidirectional_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::detail::is_cpp17_iterator< explicit_random_access_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::detail::is_cpp17_iterator< implicit_random_access_iterator >::value ), true );
}

BOOST_AUTO_TEST_CASE(Cpp17InputIterator) {
  BOOST_CHECK_EQUAL( ( slce::detail::is_cpp17_input_iterator< base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::detail::is_cpp17_input_iterator< explicit_forward_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::detail::is_cpp17_input_iterator< implicit_forward_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::detail::is_cpp17_input_iterator< explicit_bidirectional_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::detail::is_cpp17_input_iterator< implicit_bidirectional_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::detail::is_cpp17_input_iterator< explicit_random_access_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::detail::is_cpp17_input_iterator< implicit_random_access_iterator >::value ), true );
}

BOOST_AUTO_TEST_CASE(Cpp17ForwardIterator) {
  BOOST_CHECK_EQUAL( ( slce::detail::is_cpp17_forward_iterator< base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::detail::is_cpp17_forward_iterator< explicit_forward_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::detail::is_cpp17_forward_iterator< implicit_forward_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::detail::is_cpp17_forward_iterator< explicit_bidirectional_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::detail::is_cpp17_forward_iterator< implicit_bidirectional_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::detail::is_cpp17_forward_iterator< explicit_random_access_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::detail::is_cpp17_forward_iterator< implicit_random_access_iterator >::value ), true );
}

BOOST_AUTO_TEST_CASE(Cpp17BidirectionalIterator) {
  BOOST_CHECK_EQUAL( ( slce::detail::is_cpp17_bidirectional_iterator< base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::detail::is_cpp17_bidirectional_iterator< explicit_forward_iterator >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::detail::is_cpp17_bidirectional_iterator< implicit_forward_iterator >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::detail::is_cpp17_bidirectional_iterator< explicit_bidirectional_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::detail::is_cpp17_bidirectional_iterator< implicit_bidirectional_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::detail::is_cpp17_bidirectional_iterator< explicit_random_access_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::detail::is_cpp17_bidirectional_iterator< implicit_random_access_iterator >::value ), true );
}

BOOST_AUTO_TEST_CASE(Cpp17RandomAccessIterator) {
  BOOST_CHECK_EQUAL( ( slce::detail::is_cpp17_random_access_iterator< base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::detail::is_cpp17_random_access_iterator< explicit_forward_iterator >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::detail::is_cpp17_random_access_iterator< implicit_forward_iterator >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::detail::is_cpp17_random_access_iterator< explicit_bidirectional_iterator >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::detail::is_cpp17_random_access_iterator< implicit_bidirectional_iterator >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::detail::is_cpp17_random_access_iterator< explicit_random_access_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::detail::is_cpp17_random_access_iterator< implicit_random_access_iterator >::value ), true );
}

BOOST_AUTO_TEST_CASE(Readable) {
  BOOST_CHECK_EQUAL( ( slce::is_readable< base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_readable< explicit_forward_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_readable< implicit_forward_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_readable< explicit_bidirectional_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_readable< implicit_bidirectional_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_readable< explicit_random_access_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_readable< implicit_random_access_iterator >::value ), true );
}

BOOST_AUTO_TEST_CASE(Writable) {
  BOOST_CHECK_EQUAL( ( slce::is_writable< base, int >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_writable< explicit_forward_iterator, int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_writable< implicit_forward_iterator, int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_writable< explicit_bidirectional_iterator, int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_writable< implicit_bidirectional_iterator, int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_writable< explicit_random_access_iterator, int >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_writable< implicit_random_access_iterator, int >::value ), true );
}

BOOST_AUTO_TEST_CASE(WeaklyIncrementable) {
  BOOST_CHECK_EQUAL( ( slce::is_weakly_incrementable< base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_weakly_incrementable< explicit_forward_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_weakly_incrementable< implicit_forward_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_weakly_incrementable< explicit_bidirectional_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_weakly_incrementable< implicit_bidirectional_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_weakly_incrementable< explicit_random_access_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_weakly_incrementable< implicit_random_access_iterator >::value ), true );
}

BOOST_AUTO_TEST_CASE(Incrementable) {
  BOOST_CHECK_EQUAL( ( slce::is_incrementable< base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_incrementable< explicit_forward_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_incrementable< implicit_forward_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_incrementable< explicit_bidirectional_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_incrementable< implicit_bidirectional_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_incrementable< explicit_random_access_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_incrementable< implicit_random_access_iterator >::value ), true );
}

BOOST_AUTO_TEST_CASE(Iterator) {
  BOOST_CHECK_EQUAL( ( slce::is_iterator< base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_iterator< explicit_forward_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_iterator< implicit_forward_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_iterator< explicit_bidirectional_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_iterator< implicit_bidirectional_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_iterator< explicit_random_access_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_iterator< implicit_random_access_iterator >::value ), true );
}

BOOST_AUTO_TEST_CASE(Sentinel) {
  BOOST_CHECK_EQUAL( ( slce::is_sentinel< base, base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_sentinel< explicit_forward_iterator, explicit_forward_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_sentinel< implicit_forward_iterator, implicit_forward_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_sentinel< explicit_bidirectional_iterator, explicit_bidirectional_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_sentinel< implicit_bidirectional_iterator, implicit_bidirectional_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_sentinel< explicit_random_access_iterator, explicit_random_access_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_sentinel< implicit_random_access_iterator, implicit_random_access_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_sentinel< sentinel< explicit_forward_iterator >, explicit_forward_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_sentinel< sentinel< implicit_forward_iterator >, implicit_forward_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_sentinel< sentinel< explicit_bidirectional_iterator >, explicit_bidirectional_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_sentinel< sentinel< implicit_bidirectional_iterator >, implicit_bidirectional_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_sentinel< sentinel< explicit_random_access_iterator >, explicit_random_access_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_sentinel< sentinel< implicit_random_access_iterator >, implicit_random_access_iterator >::value ), true );
}

BOOST_AUTO_TEST_CASE(SizedSentinel) {
  BOOST_CHECK_EQUAL( ( slce::is_sized_sentinel< base, base >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_sized_sentinel< explicit_forward_iterator, explicit_forward_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_sized_sentinel< implicit_forward_iterator, implicit_forward_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_sized_sentinel< explicit_bidirectional_iterator, explicit_bidirectional_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_sized_sentinel< implicit_bidirectional_iterator, implicit_bidirectional_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_sized_sentinel< explicit_random_access_iterator, explicit_random_access_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_sized_sentinel< implicit_random_access_iterator, implicit_random_access_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_sized_sentinel< sentinel< explicit_forward_iterator >, explicit_forward_iterator >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_sized_sentinel< sentinel< implicit_forward_iterator >, implicit_forward_iterator >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_sized_sentinel< sentinel< explicit_bidirectional_iterator >, explicit_bidirectional_iterator >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_sized_sentinel< sentinel< implicit_bidirectional_iterator >, implicit_bidirectional_iterator >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_sized_sentinel< sentinel< explicit_random_access_iterator >, explicit_random_access_iterator >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_sized_sentinel< sentinel< implicit_random_access_iterator >, implicit_random_access_iterator >::value ), false );
  BOOST_CHECK_EQUAL( ( slce::is_sized_sentinel< sized_sentinel< explicit_forward_iterator >, explicit_forward_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_sized_sentinel< sized_sentinel< implicit_forward_iterator >, implicit_forward_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_sized_sentinel< sized_sentinel< explicit_bidirectional_iterator >, explicit_bidirectional_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_sized_sentinel< sized_sentinel< implicit_bidirectional_iterator >, implicit_bidirectional_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_sized_sentinel< sized_sentinel< explicit_random_access_iterator >, explicit_random_access_iterator >::value ), true );
  BOOST_CHECK_EQUAL( ( slce::is_sized_sentinel< sized_sentinel< implicit_random_access_iterator >, implicit_random_access_iterator >::value ), true );
}

