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

#ifndef SLCE_STANDARD_LIBRARY_CONCEPTS_EMULATION_LIBRARY_HPP
#define SLCE_STANDARD_LIBRARY_CONCEPTS_EMULATION_LIBRARY_HPP
#include <type_traits>
#ifdef __cpp_lib_ranges
#include <range>
#endif
#ifdef __cpp_variable_templates
#define SLCE_ENABLE_CXX14
#ifdef __cpp_concepts
#define SLCE_ENABLE_CONCEPTS_TS
#endif
#endif
#if __cplusplus > 201703L && !defined(SLCE_ENABLE_CONCEPTS_TS)
#define SLCE_ENABLE_CXX20
#endif

#ifdef SLCE_ENABLE_CONCEPTS_TS
#define SLCE_BOOL bool
#define SLCE_ENABLE_CONCEPTS
#elif defined( SLCE_ENABLE_CXX20 )
#define SLCE_BOOL
#define SLCE_ENABLE_CONCEPTS
#endif

#if defined(SLCE_ENABLE_CXX14) && !defined(SLCE_ENABLE_CONCEPTS)
#define SLCE_HELPER( concept_name, trait_name ) \
  template< typename ...Args > \
  constexpr bool trait_name ## _v = trait_name < Args... >::value;
#elif !defined(SLCE_ENABLE_CXX14) && defined(SLCE_ENABLE_CONCEPTS)
#define SLCE_HELPER( concept_name, trait_name ) \
  template< typename ...Args > \
  concept SLCE_BOOL concept_name = trait_name < Args... >::value;
#elif defined(SLCE_ENABLE_CXX14) && defined(SLCE_ENABLE_CONCEPTS)
#define SLCE_HELPER( concept_name, trait_name ) \
  template< typename ...Args > \
  constexpr bool trait_name ## _v = trait_name < Args... >::value; \
  template< typename ...Args > \
  concept SLCE_BOOL concept_name = trait_name < Args... >::value;
#else
#define SLCE_HELPER( concept_name, trait_name )
#endif


#if defined(SLCE_ENABLE_CXX14)
#define SLCE_BOOLEAN_TRAIT_V( trait_name, ... ) \
  template< typename T, typename Enable = void > \
  struct trait_name : public std::false_type {}; \
  template< typename T > \
  struct trait_name< T, typename std::enable_if< __VA_ARGS__ >::type > : public std::true_type {}; \
  template< typename T > \
  using trait_name ## _t = typename trait_name < T >::type; \
  template< typename T > \
  constexpr bool trait_name ## _v = trait_name < T >::value;
#define SLCE_BOOLEAN_TRAIT_T1( trait_name, ... ) \
  template< typename T, typename Enable = void > \
  struct trait_name : public std::false_type {}; \
  template< typename T > \
  struct trait_name< T, typename slce::detail::voider< __VA_ARGS__ >::type > : public std::true_type {}; \
  template< typename T > \
  using trait_name ## _t = typename trait_name < T >::type; \
  template< typename T > \
  constexpr bool trait_name ## _v = trait_name < T >::value;
#define SLCE_BOOLEAN_TRAIT_T2( trait_name, ... ) \
  template< typename T, typename U, typename Enable = void > \
  struct trait_name : public std::false_type {}; \
  template< typename T, typename U > \
  struct trait_name< T, U, typename slce::detail::voider< __VA_ARGS__ >::type > : public std::true_type {}; \
  template< typename T, typename U > \
  using trait_name ## _t = typename trait_name < T, U >::type; \
  template< typename T, typename U > \
  constexpr bool trait_name ## _v = trait_name < T, U >::value;
#else
#define SLCE_BOOLEAN_TRAIT_V( trait_name, ... ) \
  template< typename T, typename Enable = void > \
  struct trait_name : public std::false_type {}; \
  template< typename T > \
  struct trait_name< T, typename std::enable_if< __VA_ARGS__ >::type > : public std::true_type {}; \
  template< typename T > \
  using trait_name ## _t = typename trait_name < T >::type;
#define SLCE_BOOLEAN_TRAIT_T1( trait_name, ... ) \
  template< typename T, typename Enable = void > \
  struct trait_name : public std::false_type {}; \
  template< typename T > \
  struct trait_name< T, typename slce::detail::voider< __VA_ARGS__ >::type > : public std::true_type {}; \
  template< typename T > \
  using trait_name ## _t = typename trait_name < T >::type;
#define SLCE_BOOLEAN_TRAIT_T2( trait_name, ... ) \
  template< typename T, typename U, typename Enable = void > \
  struct trait_name : public std::false_type {}; \
  template< typename T, typename U > \
  struct trait_name< T, U,  typename slce::detail::voider< __VA_ARGS__ >::type > : public std::true_type {}; \
  template< typename T, typename U > \
  using trait_name ## _t = typename trait_name < T, U >::type;
#endif

namespace std {
  template< typename T, typename U, template< class > class Tq, template< class > class Uq >
  struct basic_common_reference;
}
namespace slce {
  namespace detail {
    template< typename ...Args >
    struct voider {
      using type = void;
    };
    template< typename ...Args >
    struct lifter {};
    template< typename T >
    struct remove_cvref {
      using type = typename std::remove_cv< typename std::remove_reference< T >::type >::type;
    };

    template< typename T >
    using add_no_qual_t = T;
    template< typename T >
    using add_c_qual_t = const T;
    template< typename T >
    using add_v_qual_t = volatile T;
    template< typename T >
    using add_l_qual_t = T&;
    template< typename T >
    using add_r_qual_t = T&&;
    template< typename T >
    using add_cv_qual_t = add_c_qual_t< add_v_qual_t< T > >;
    template< typename T >
    using add_cl_qual_t = add_c_qual_t< add_l_qual_t< T > >;
    template< typename T >
    using add_cr_qual_t = add_c_qual_t< add_r_qual_t< T > >;
    template< typename T >
    using add_vl_qual_t = add_v_qual_t< add_l_qual_t< T > >;
    template< typename T >
    using add_vr_qual_t = add_v_qual_t< add_r_qual_t< T > >;
    template< typename T >
    using add_cvl_qual_t = add_c_qual_t< add_v_qual_t< add_l_qual_t< T > > >;
    template< typename T >
    using add_cvr_qual_t = add_c_qual_t< add_v_qual_t< add_r_qual_t< T > > >;
    SLCE_BOOLEAN_TRAIT_V(
      has_no_qual,
      !std::is_const< T >::value &&
      !std::is_volatile< T >::value &&
      !std::is_lvalue_reference< T >::value &&
      !std::is_rvalue_reference< T >::value
    )
    SLCE_BOOLEAN_TRAIT_V(
      has_c_qual,
      std::is_const< T >::value &&
      !std::is_volatile< T >::value &&
      !std::is_lvalue_reference< T >::value &&
      !std::is_rvalue_reference< T >::value
    )
    SLCE_BOOLEAN_TRAIT_V(
      has_v_qual,
      !std::is_const< T >::value &&
      std::is_volatile< T >::value &&
      !std::is_lvalue_reference< T >::value &&
      !std::is_rvalue_reference< T >::value
    )
    SLCE_BOOLEAN_TRAIT_V(
      has_l_qual,
      !std::is_const< T >::value &&
      !std::is_volatile< T >::value &&
      std::is_lvalue_reference< T >::value &&
      !std::is_rvalue_reference< T >::value
    )
    SLCE_BOOLEAN_TRAIT_V(
      has_r_qual,
      !std::is_const< T >::value &&
      !std::is_volatile< T >::value &&
      !std::is_lvalue_reference< T >::value &&
      std::is_rvalue_reference< T >::value
    )
    SLCE_BOOLEAN_TRAIT_V(
      has_cv_qual,
      std::is_const< T >::value &&
      std::is_volatile< T >::value &&
      !std::is_lvalue_reference< T >::value &&
      !std::is_rvalue_reference< T >::value
    )
    SLCE_BOOLEAN_TRAIT_V(
      has_cl_qual,
      std::is_const< T >::value &&
      !std::is_volatile< T >::value &&
      std::is_lvalue_reference< T >::value &&
      !std::is_rvalue_reference< T >::value
    )
    SLCE_BOOLEAN_TRAIT_V(
      has_cr_qual,
      std::is_const< T >::value &&
      !std::is_volatile< T >::value &&
      !std::is_lvalue_reference< T >::value &&
      std::is_rvalue_reference< T >::value
    )
    SLCE_BOOLEAN_TRAIT_V(
      has_vl_qual,
      !std::is_const< T >::value &&
      std::is_volatile< T >::value &&
      std::is_lvalue_reference< T >::value &&
      !std::is_rvalue_reference< T >::value
    )
    SLCE_BOOLEAN_TRAIT_V(
      has_vr_qual,
      !std::is_const< T >::value &&
      std::is_volatile< T >::value &&
      !std::is_lvalue_reference< T >::value &&
      std::is_rvalue_reference< T >::value
    )
    SLCE_BOOLEAN_TRAIT_V(
      has_cvl_qual,
      std::is_const< T >::value &&
      std::is_volatile< T >::value &&
      std::is_lvalue_reference< T >::value &&
      !std::is_rvalue_reference< T >::value
    )
    SLCE_BOOLEAN_TRAIT_V(
      has_cvr_qual,
      std::is_const< T >::value &&
      std::is_volatile< T >::value &&
      !std::is_lvalue_reference< T >::value &&
      std::is_rvalue_reference< T >::value
    )
    template< typename T, typename U >
    struct copy_cvr {
      using type = U;
    };
    template< typename T, typename U >
    struct copy_cvr< T&, U > {
      using type = U&;
    };
    template< typename T, typename U >
    struct copy_cvr< T&&, U > {
      using type = U&&;
    };
    template< typename T, typename U >
    struct copy_cvr< const T, U > {
      using type = const U;
    };
    template< typename T, typename U >
    struct copy_cvr< const T&, U > {
      using type = const U&;
    };
    template< typename T, typename U >
    struct copy_cvr< const T&&, U > {
      using type = const U&&;
    };
    template< typename T, typename U >
    struct copy_cvr< volatile T, U > {
      using type = volatile U;
    };
    template< typename T, typename U >
    struct copy_cvr< volatile T&, U > {
      using type = volatile U&;
    };
    template< typename T, typename U >
    struct copy_cvr< volatile T&&, U > {
      using type = volatile U&&;
    };
    template< typename T, typename U >
    struct copy_cvr< const volatile T, U > {
      using type = const volatile U;
    };
    template< typename T, typename U >
    struct copy_cvr< const volatile T&, U > {
      using type = const volatile U&;
    };
    template< typename T, typename U >
    struct copy_cvr< const volatile T&&, U > {
      using type = const volatile U&&;
    };
  }


  template< typename T, typename U >
  using is_same = std::is_same< T, U >;
  SLCE_HELPER( Same, is_same )

  template< typename Derived, typename Base, typename Enable = void >
  struct is_derived_from : public std::false_type {};
  template< typename Derived, typename Base >
  struct is_derived_from< Derived, Base, typename std::enable_if<
    !std::is_reference< Derived >::value && !std::is_reference< Base >::value
  >::type > : public std::integral_constant<
    bool, std::is_base_of< Base, Derived >::value && std::is_convertible< const volatile Derived*, const volatile Base* >::value
  > {};
  SLCE_HELPER( DerivedFrom, is_derived_from )

  template< typename T, typename U, typename Enable = void >
  struct is_convertible_to : public std::false_type {};
  template< typename T, typename U >
  struct is_convertible_to< T, U, typename detail::voider<
    decltype( static_cast< U >( std::declval< T >() ) )
  >::type > : public std::is_convertible< T, U > {};
  SLCE_HELPER( ConvertibleTo, is_convertible_to )

  namespace detail {
    template< typename T, typename U, typename Enable = void >
    struct common_lvalue_reference {};
    template< typename T, typename U >
    struct common_lvalue_reference< T, U, typename voider<
      decltype( false ? std::declval< typename remove_cvref< T >::type& >() : std::declval< typename remove_cvref< U >::type& >() )
    >::type > {
      using type = decltype( false ? std::declval< typename copy_cvr< U, T >::type& >() : std::declval< typename copy_cvr< T, U >::type& >() );
    };
    SLCE_BOOLEAN_TRAIT_T2(
      has_common_lvalue_reference,
      typename common_lvalue_reference< T, U >::type
    )
    template< typename T, typename U, typename Enable = void >
    struct common_rvalue_reference {};
    template< typename T, typename U >
    struct common_rvalue_reference< T, U, typename voider< typename common_lvalue_reference< T, U >::type >::type > {
      using type = typename std::remove_reference<
        typename common_lvalue_reference< T, U >::type
      >::type&&;
    };
    SLCE_BOOLEAN_TRAIT_T2(
      has_common_rvalue_reference,
      typename common_rvalue_reference< T, U >::type
    )
    template< typename T, typename U, typename Enable = void >
    struct common_const_reference {};
    template< typename T, typename U >
    struct common_const_reference< T, U, typename voider< typename common_lvalue_reference< T, const typename remove_cvref< U >::type >::type >::type > {
      using type = typename std::remove_reference< typename common_lvalue_reference< T, const typename remove_cvref< U >::type >::type >::type&&;
    };
    SLCE_BOOLEAN_TRAIT_T2(
      has_common_const_reference,
      typename common_const_reference< T, U >::type
    )
    template< typename T, typename U, typename Enable = void >
    struct simple_common_reference_type {};
    template< typename T, typename U >
    struct simple_common_reference_type< T, U, typename std::enable_if<
      std::is_lvalue_reference< T >::value &&
      std::is_lvalue_reference< U >::value &&
      std::is_lvalue_reference< typename common_lvalue_reference< T, U >::type >::value
    >::type > {
      using type = typename common_lvalue_reference< T, U >::type;
    };
    template< typename T, typename U >
    struct simple_common_reference_type< T, U, typename std::enable_if<
      std::is_rvalue_reference< T >::value &&
      std::is_rvalue_reference< U >::value &&
      is_convertible_to< T, typename common_rvalue_reference< T, U >::type >::value &&
      is_convertible_to< U, typename common_rvalue_reference< T, U >::type >::value
    >::type > {
      using type = typename common_rvalue_reference< T, U >::type;
    };
    template< typename T, typename U >
    struct simple_common_reference_type< T, U, typename std::enable_if<
      std::is_lvalue_reference< T >::value &&
      std::is_rvalue_reference< U >::value &&
      is_convertible_to< T, typename common_const_reference< T, U >::type >::value &&
      is_convertible_to< U, typename common_const_reference< T, U >::type >::value
    >::type > {
      using type = typename common_rvalue_reference< T, U >::type;
    };
    template< typename T, typename U >
    struct simple_common_reference_type< U, T, typename std::enable_if<
      std::is_lvalue_reference< T >::value &&
      std::is_rvalue_reference< U >::value &&
      is_convertible_to< T, typename common_const_reference< T, U >::type >::value &&
      is_convertible_to< U, typename common_const_reference< T, U >::type >::value
    >::type > {
      using type = typename common_rvalue_reference< T, U >::type;
    };
    SLCE_BOOLEAN_TRAIT_T2(
      has_simple_common_reference_type,
      typename simple_common_reference_type< T, U >::type
    )


    template< typename T, typename U, typename Enable = void >
    struct basic_common_reference_type {};
#define SLCE_BASIC_COMMON_REFERENCE_TYPE_SPEC_L( tqual, uqual ) \
    template< typename T, typename U > \
    struct basic_common_reference_type< T, U, typename voider< \
      typename std::enable_if< \
        has_ ## tqual ## _qual< T >::value && \
	has_ ## uqual ## _qual< U >::value \
      >::type, \
      typename std::basic_common_reference< \
        typename remove_cvref< T >::type, \
	typename remove_cvref< U >::type, \
        add_ ## tqual ## _qual_t, \
	add_ ## uqual ## _qual_t \
      >::type \
    >::type > { \
      using type = typename std::basic_common_reference< \
        typename remove_cvref< T >::type, \
	typename remove_cvref< U >::type, \
        add_ ## tqual ## _qual_t, \
	add_ ## uqual ## _qual_t \
      >::type; \
    };
#define SLCE_BASIC_COMMON_REFERENCE_TYPE_SPEC( tqual ) \
    SLCE_BASIC_COMMON_REFERENCE_TYPE_SPEC_L( tqual, no ) \
    SLCE_BASIC_COMMON_REFERENCE_TYPE_SPEC_L( tqual, c ) \
    SLCE_BASIC_COMMON_REFERENCE_TYPE_SPEC_L( tqual, v ) \
    SLCE_BASIC_COMMON_REFERENCE_TYPE_SPEC_L( tqual, l ) \
    SLCE_BASIC_COMMON_REFERENCE_TYPE_SPEC_L( tqual, r ) \
    SLCE_BASIC_COMMON_REFERENCE_TYPE_SPEC_L( tqual, cv ) \
    SLCE_BASIC_COMMON_REFERENCE_TYPE_SPEC_L( tqual, cl ) \
    SLCE_BASIC_COMMON_REFERENCE_TYPE_SPEC_L( tqual, cr ) \
    SLCE_BASIC_COMMON_REFERENCE_TYPE_SPEC_L( tqual, vl ) \
    SLCE_BASIC_COMMON_REFERENCE_TYPE_SPEC_L( tqual, vr ) \
    SLCE_BASIC_COMMON_REFERENCE_TYPE_SPEC_L( tqual, cvl ) \
    SLCE_BASIC_COMMON_REFERENCE_TYPE_SPEC_L( tqual, cvr )

    SLCE_BASIC_COMMON_REFERENCE_TYPE_SPEC( no )
    SLCE_BASIC_COMMON_REFERENCE_TYPE_SPEC( c )
    SLCE_BASIC_COMMON_REFERENCE_TYPE_SPEC( v )
    SLCE_BASIC_COMMON_REFERENCE_TYPE_SPEC( l )
    SLCE_BASIC_COMMON_REFERENCE_TYPE_SPEC( r )
    SLCE_BASIC_COMMON_REFERENCE_TYPE_SPEC( cv )
    SLCE_BASIC_COMMON_REFERENCE_TYPE_SPEC( cl )
    SLCE_BASIC_COMMON_REFERENCE_TYPE_SPEC( cr )
    SLCE_BASIC_COMMON_REFERENCE_TYPE_SPEC( vl )
    SLCE_BASIC_COMMON_REFERENCE_TYPE_SPEC( vr )
    SLCE_BASIC_COMMON_REFERENCE_TYPE_SPEC( cvl )
    SLCE_BASIC_COMMON_REFERENCE_TYPE_SPEC( cvr )

    SLCE_BOOLEAN_TRAIT_T2(
      has_basic_common_reference_type,
      typename basic_common_reference_type< T, U >::type
    )

    template< typename T, typename U, typename Enable = void >
    struct decltype_common_reference_type {};
    template< typename T, typename U >
    struct decltype_common_reference_type< T, U, typename voider<
      decltype( false ? std::declval< T >() : std::declval< U >() )
    >::type > {
      using type = decltype( false ? std::declval< T >() : std::declval< U >() );
    };
    SLCE_BOOLEAN_TRAIT_T2(
      has_decltype_common_reference_type,
      typename decltype_common_reference_type< T, U >::type
    )

    SLCE_BOOLEAN_TRAIT_T2(
      has_common_type,
      typename std::common_type< T, U >::type
    )

    template< typename T, typename U, typename Enable = void >
    struct common_reference : public std::false_type {};
    template< typename T, typename U >
    struct common_reference< T, U, typename std::enable_if<
      has_simple_common_reference_type< T, U >::value
    >::type > : public simple_common_reference_type< T, U > {};
    template< typename T, typename U >
    struct common_reference< T, U, typename std::enable_if<
      !has_simple_common_reference_type< T, U >::value &&
      has_basic_common_reference_type< T, U >::value
    >::type > : public basic_common_reference_type< T, U > {};
    template< typename T, typename U >
    struct common_reference< T, U, typename std::enable_if<
      !has_simple_common_reference_type< T, U >::value &&
      !has_basic_common_reference_type< T, U >::value &&
      has_decltype_common_reference_type< T, U >::value
    >::type > : public decltype_common_reference_type< T, U > {};
    template< typename T, typename U >
    struct common_reference< T, U, typename std::enable_if<
      !has_simple_common_reference_type< T, U >::value &&
      !has_basic_common_reference_type< T, U >::value &&
      !has_decltype_common_reference_type< T, U >::value &&
      has_common_type< T, U >::value
    >::type > : public std::common_type< T, U > {};
  }
  template< typename ...Args >
  struct common_reference {};
  template< typename T0 >
  struct common_reference< T0 > { using type = T0; };
  template< typename T0, typename T1 >
  struct common_reference< T0, T1 > : public detail::common_reference< T0, T1 > {};
  template< typename T0, typename T1, typename T2, typename ...Args >
  struct common_reference< T0, T1, T2, Args... > : public common_reference< typename common_reference< T0, T1 >::type, T2, Args... > {};
  template< typename T, typename U, typename Enable = void >
  struct is_common_reference : public std::false_type {};
  template< typename T, typename U >
  struct is_common_reference< T, U, typename detail::voider<
    typename common_reference< T, U >::type, typename common_reference< U, T >::type
  >::type > : public std::integral_constant< bool,
    std::is_same<
      typename common_reference< T, U >::type,
      typename common_reference< U, T >::type
    >::value &&
    std::is_convertible< T, typename common_reference< T, U >::type >::value &&
    std::is_convertible< U, typename common_reference< T, U >::type >::value
  > {};
  SLCE_HELPER( CommonReference, is_common_reference )
  template< typename T, typename U, typename Enable = void >
  struct is_common : public std::false_type {};
  template< typename T, typename U >
  struct is_common< T, U, typename detail::voider<
    decltype( static_cast< typename std::common_type< T, U >::type >( std::declval< T >() ) ),
    decltype( static_cast< typename std::common_type< T, U >::type >( std::declval< U >() ) )
  >::type > : public std::integral_constant< bool,
    std::is_same<
      typename std::common_type< T, U >::type,
      typename std::common_type< U, T >::type
    >::value &&
    is_common_reference<
      typename std::add_lvalue_reference< const T >::type, 
      typename std::add_lvalue_reference< const U >::type
    >::value &&
    is_common_reference<
      typename std::add_lvalue_reference< typename std::common_type< T, U >::type >::type,
      typename common_reference<
        typename std::add_lvalue_reference< const T >::type,
        typename std::add_lvalue_reference< const U >::type
      >::type
    >::value
  > {};

  template< typename T >
  using is_integral = std::is_integral< T >;
  SLCE_HELPER( Integral, is_integral )

  template< typename T, typename Enable = void >
  struct is_signed_integral : public std::false_type {};
  template< typename T >
  struct is_signed_integral< T,
    typename std::enable_if< is_integral< T >::value >::type
  > : public std::is_signed< T > {};
  SLCE_HELPER( SignedIntegral, is_signed_integral )

  template< typename T, typename Enable = void >
  struct is_unsigned_integral : public std::false_type {};
  template< typename T >
  struct is_unsigned_integral< T,
    typename std::enable_if< is_integral< T >::value >::type
  > : public std::is_unsigned< T > {};
  SLCE_HELPER( UnsignedIntegral, is_unsigned_integral )

  template< typename L, typename R, typename Enable = void >
  struct is_assignable : public std::false_type {};
  template< typename L, typename R >
  struct is_assignable< L, R, typename std::enable_if<
    is_same<
      decltype( std::declval< L >() = std::forward< R >( std::declval< R&& >() ) ),
      L
    >::value
  >::type > : public std::integral_constant< bool,
    std::is_lvalue_reference< L >::value &&
    is_common_reference<
      const typename std::remove_reference< L >::type&,
      const typename std::remove_reference< R >::type&
    >::value
  > {};
  SLCE_HELPER( Assignable, is_assignable )

  namespace detail {
    namespace using_std {
      using namespace std;
      template< typename T, typename U, typename Enable = void >
      struct is_std_swappable : public std::false_type {};
      template< typename T, typename U >
      struct is_std_swappable< T, U, typename voider<
        decltype( swap( std::declval< T& >(), std::declval< U& >() ) )
      >::type > : public std::true_type {};
    }
    template< typename T, typename U, typename Enable = void >
    struct is_range_swappable : public std::false_type {};
#ifdef __cpp_lib_ranges
    template< typename T, typename U >
    struct is_range_swappable< T, U, typename voider<
      decltype( std::swap_ranges( std::declval< T& >(), std::declval< U& >() ) )
    >::type > : public std::true_type {};
#endif
    template< typename T, typename U, typename Enable = void >
    struct is_swappable_type : public std::false_type {};
    template< typename T >
    struct is_swappable_type< T, T, typename std::enable_if<
      std::is_move_constructible< T >::value &&
      is_assignable< T&, T >::value
    >::type > : public std::true_type {};
  }

  template< typename T, typename U >
  struct is_swappable_with : public std::integral_constant< bool,
    detail::using_std::is_std_swappable< T, U >::value ||
    detail::is_range_swappable< T, U >::value ||
    detail::is_swappable_type< T, U >::value
  > {};
  SLCE_HELPER( SwappableWith, is_swappable_with )
  template< typename T >
  struct is_swappable : public is_swappable_with< T, T > {};
  SLCE_HELPER( Swappable, is_swappable )

  template< typename T >
  using is_destructible = std::is_nothrow_destructible< T >;
  SLCE_HELPER( Destructible, is_destructible )

  template< typename T, typename ...Args >
  struct is_constructible : public std::integral_constant< bool,
    is_destructible< T >::value &&
    std::is_constructible< T, Args... >::value
  > {};
  SLCE_HELPER( Constructible, is_constructible )

  template< typename T >
  struct is_default_constructible : public is_constructible< T > {};
  SLCE_HELPER( DefaultConstructible, is_default_constructible )

  template< typename T >
  struct is_move_constructible : public std::integral_constant< bool,
    is_constructible< T, T >::value &&
    is_convertible_to< T, T >::value
  > {};
  SLCE_HELPER( MoveConstructible, is_move_constructible )

  template< typename T >
  struct is_copy_constructible : public std::integral_constant< bool,
    is_move_constructible< T >::value &&
    is_constructible< T, T& >::value &&
    is_convertible_to< T&, T >::value &&
    is_constructible< T, const T& >::value &&
    is_convertible_to< const T&, T >::value &&
    is_constructible< T, const T >::value &&
    is_convertible_to< const T, T >::value
  > {};
  SLCE_HELPER( CopyConstructible, is_copy_constructible )

  template< typename T >
  struct is_movable : public std::integral_constant< bool,
    std::is_object< T >::value &&
    is_move_constructible< T >::value &&
    is_assignable< T&, T >::value &&
    is_swappable< T >::value
  > {};
  SLCE_HELPER( Movable, is_movable )

  template< typename T, typename Enable = void >
  struct is_boolean : public std::false_type {};
  template< typename T >
  struct is_boolean< T, typename detail::voider<
    decltype( !std::declval< const T& >() ),
    decltype( std::declval< const T& >() && std::declval< bool >() ),
    decltype( std::declval< const T& >() || std::declval< bool >() ),
    decltype( std::declval< const T& >() && std::declval< const T& >() ),
    decltype( std::declval< bool >() && std::declval< const T& >() ),
    decltype( std::declval< const T& >() || std::declval< const T& >() ),
    decltype( std::declval< bool >() || std::declval< const T& >() ),
    decltype( std::declval< const T& >() == std::declval< const T& >() ),
    decltype( std::declval< const T& >() == std::declval< bool >() ),
    decltype( std::declval< bool >() == std::declval< const T& >() ),
    decltype( std::declval< const T& >() != std::declval< const T& >() ),
    decltype( std::declval< const T& >() != std::declval< bool >() ),
    decltype( std::declval< bool >() != std::declval< const T& >() )
  >::type > : public std::integral_constant< bool,
    is_movable< typename detail::remove_cvref< T >::type >::value &&
    is_convertible_to< const typename std::remove_reference< T >::type&, bool >::value &&
    is_convertible_to< decltype( !std::declval< const T& >() ), bool >::value &&
    is_same< decltype( std::declval< const T& >() && std::declval< bool >() ), bool >::value &&
    is_same< decltype( std::declval< const T& >() || std::declval< bool >() ), bool >::value &&
    is_same< decltype( std::declval< const T& >() && std::declval< const T& >() ), bool >::value &&
    is_same< decltype( std::declval< bool >() && std::declval< const T& >() ), bool >::value &&
    is_same< decltype( std::declval< const T& >() || std::declval< const T& >() ), bool >::value &&
    is_same< decltype( std::declval< bool >() || std::declval< const T& >() ), bool >::value &&
    is_convertible_to< decltype( std::declval< const T& >() == std::declval< const T& >() ), bool >::value &&
    is_convertible_to< decltype( std::declval< const T& >() == std::declval< bool >() ), bool >::value &&
    is_convertible_to< decltype( std::declval< bool >() == std::declval< const T& >() ), bool >::value &&
    is_convertible_to< decltype( std::declval< const T& >() != std::declval< const T& >() ), bool >::value &&
    is_convertible_to< decltype( std::declval< const T& >() != std::declval< bool >() ), bool >::value &&
    is_convertible_to< decltype( std::declval< bool >() != std::declval< const T& >() ), bool >::value
  > {};
  SLCE_HELPER( Boolean, is_boolean )

  template< typename T, typename U, typename Enable = void >
  struct is_weakly_equality_comparable_with : public std::false_type {};
  template< typename T, typename U >
  struct is_weakly_equality_comparable_with< T, U, typename detail::voider<
    decltype( std::declval< const typename std::remove_reference< T >::type& >() == std::declval< const typename std::remove_reference< U >::type& >() ),
    decltype( std::declval< const typename std::remove_reference< T >::type& >() != std::declval< const typename std::remove_reference< U >::type& >() ),
    decltype( std::declval< const typename std::remove_reference< U >::type& >() == std::declval< const typename std::remove_reference< T >::type& >() ),
    decltype( std::declval< const typename std::remove_reference< U >::type& >() != std::declval< const typename std::remove_reference< T >::type& >() )
  >::type > : public std::integral_constant< bool,
    std::is_same< bool, decltype( std::declval< const typename std::remove_reference< T >::type& >() == std::declval< const typename std::remove_reference< U >::type& >() ) >::value &&
    std::is_same< bool, decltype( std::declval< const typename std::remove_reference< T >::type& >() != std::declval< const typename std::remove_reference< U >::type& >() ) >::value &&
    std::is_same< bool, decltype( std::declval< const typename std::remove_reference< U >::type& >() == std::declval< const typename std::remove_reference< T >::type& >() ) >::value &&
    std::is_same< bool, decltype( std::declval< const typename std::remove_reference< U >::type& >() != std::declval< const typename std::remove_reference< T >::type& >() ) >::value
  > {};

  template< typename T >
  struct is_equality_comparable : public is_weakly_equality_comparable_with< T, T > {};
  SLCE_HELPER( EqualityComparable, is_equality_comparable )

  template< typename T, typename U >
  struct is_equality_comparable_with : public std::integral_constant< bool,
    is_equality_comparable< T >::value &&
    is_equality_comparable< U >::value &&
    is_common_reference< const typename std::remove_reference< T >::type&, const typename std::remove_reference< U >::type& >::value &&
    is_equality_comparable<
      typename common_reference< const typename std::remove_reference< T >::type&, const typename std::remove_reference< U >::type& >::type
    >::value &&
    is_weakly_equality_comparable_with< T, U >::value
  > {};
  SLCE_HELPER( EqualityComparableWith, is_equality_comparable_with )

  template< typename T, typename Enable = void >
  struct is_strict_totally_ordered : public std::false_type {};
  template< typename T >
  struct is_strict_totally_ordered< T, typename detail::voider<
    decltype( std::declval< const typename std::remove_reference< T >::type& >() < std::declval< const typename std::remove_reference< T >::type& >() ),
    decltype( std::declval< const typename std::remove_reference< T >::type& >() > std::declval< const typename std::remove_reference< T >::type& >() ),
    decltype( std::declval< const typename std::remove_reference< T >::type& >() <= std::declval< const typename std::remove_reference< T >::type& >() ),
    decltype( std::declval< const typename std::remove_reference< T >::type& >() >= std::declval< const typename std::remove_reference< T >::type& >() )
  >::type > : public std::integral_constant< bool,
    is_equality_comparable< T >::value &&
    std::is_same< bool, decltype( std::declval< const typename std::remove_reference< T >::type& >() < std::declval< const typename std::remove_reference< T >::type& >() ) >::value &&
    std::is_same< bool, decltype( std::declval< const typename std::remove_reference< T >::type& >() > std::declval< const typename std::remove_reference< T >::type& >() ) >::value &&
    std::is_same< bool, decltype( std::declval< const typename std::remove_reference< T >::type& >() <= std::declval< const typename std::remove_reference< T >::type& >() ) >::value &&
    std::is_same< bool, decltype( std::declval< const typename std::remove_reference< T >::type& >() >= std::declval< const typename std::remove_reference< T >::type& >() ) >::value
  > {};
  ///
  SLCE_HELPER( StrictTotallyOrdered, is_strict_totally_ordered )

  template< typename T, typename U, typename Enable = void >
  struct is_strict_totally_ordered_with : public std::false_type {};
  template< typename T, typename U >
  struct is_strict_totally_ordered_with< T, U, typename detail::voider<
    decltype( std::declval< const typename std::remove_reference< T >::type& >() < std::declval< const typename std::remove_reference< U >::type& >() ),
    decltype( std::declval< const typename std::remove_reference< T >::type& >() > std::declval< const typename std::remove_reference< U >::type& >() ),
    decltype( std::declval< const typename std::remove_reference< T >::type& >() <= std::declval< const typename std::remove_reference< U >::type& >() ),
    decltype( std::declval< const typename std::remove_reference< T >::type& >() >= std::declval< const typename std::remove_reference< U >::type& >() ),
    decltype( std::declval< const typename std::remove_reference< U >::type& >() < std::declval< const typename std::remove_reference< T >::type& >() ),
    decltype( std::declval< const typename std::remove_reference< U >::type& >() > std::declval< const typename std::remove_reference< T >::type& >() ),
    decltype( std::declval< const typename std::remove_reference< U >::type& >() <= std::declval< const typename std::remove_reference< T >::type& >() ),
    decltype( std::declval< const typename std::remove_reference< U >::type& >() >= std::declval< const typename std::remove_reference< T >::type& >() )
  >::type > : public std::integral_constant< bool,
    is_strict_totally_ordered< T >::value &&
    is_strict_totally_ordered< U >::value &&
    is_equality_comparable_with< T, U >::value &&
    std::is_same< bool, decltype( std::declval< const typename std::remove_reference< T >::type& >() < std::declval< const typename std::remove_reference< U >::type& >() ) >::value &&
    std::is_same< bool, decltype( std::declval< const typename std::remove_reference< T >::type& >() > std::declval< const typename std::remove_reference< U >::type& >() ) >::value &&
    std::is_same< bool, decltype( std::declval< const typename std::remove_reference< T >::type& >() <= std::declval< const typename std::remove_reference< U >::type& >() ) >::value &&
    std::is_same< bool, decltype( std::declval< const typename std::remove_reference< T >::type& >() >= std::declval< const typename std::remove_reference< U >::type& >() ) >::value &&
    std::is_same< bool, decltype( std::declval< const typename std::remove_reference< U >::type& >() < std::declval< const typename std::remove_reference< T >::type& >() ) >::value &&
    std::is_same< bool, decltype( std::declval< const typename std::remove_reference< U >::type& >() > std::declval< const typename std::remove_reference< T >::type& >() ) >::value &&
    std::is_same< bool, decltype( std::declval< const typename std::remove_reference< U >::type& >() <= std::declval< const typename std::remove_reference< T >::type& >() ) >::value &&
    std::is_same< bool, decltype( std::declval< const typename std::remove_reference< U >::type& >() >= std::declval< const typename std::remove_reference< T >::type& >() ) >::value
  > {};
  ///
  SLCE_HELPER( StrictTotallyOrderedWith, is_strict_totally_ordered_with )

  template< typename T >
  struct is_copyable : public std::integral_constant<
    bool,
    is_copy_constructible< T >::value &&
    is_movable< T >::value &&
    is_assignable< T&, const T& >::value
  > {};
  SLCE_HELPER( Copyable, is_copyable )

  template< typename T >
  struct is_semiregular : public std::integral_constant<
    bool,
    is_copyable< T >::value &&
    is_default_constructible< T >::value
  > {};
  SLCE_HELPER( Semiregular, is_semiregular )

  template< typename T >
  struct is_regular : public std::integral_constant<
    bool,
    is_semiregular< T >::value &&
    is_equality_comparable< T >::value
  > {};
  SLCE_HELPER( Regular, is_regular )

  namespace detail {
    template< typename T, typename Args, typename Enable = void >
    struct is_invocable : public std::false_type {};
#ifdef __cpp_lib_invoke
    template< typename F, template< typename ... > typename L, typename ... Args >
    struct is_invocable< F, L< Args... >, typename voider<
      decltype( std::invoke( std::declval< F&& >(), std::declval< Args&& >()... ) )
    >::type > : public std::true_type {};
#endif
  }

  template< typename T, typename ...Args >
  struct is_invocable : public detail::is_invocable< T, detail::lifter< Args... > > {};
  SLCE_HELPER( Invocable, is_invocable )

  template< typename T, typename ...Args >
  struct is_regular_invocable : public is_invocable< T, Args... > {};
  SLCE_HELPER( RegularInvokable, is_regular_invocable )

  namespace detail {
    template< typename T, typename Args, typename Enable = void >
    struct is_predicate : public std::false_type {};
#ifdef __cpp_lib_invoke
    template< typename F, template< typename ... > typename L, typename ... Args >
    struct is_predicate< F, L< Args... >, typename voider<
      decltype( std::invoke( std::declval< F&& >(), std::declval< Args&& >()... ) )
    >::type > : public std::integral_constant<
      bool,
      ::slce::is_regular_invocable< F, Args... >::value &&
      std::is_same<
        bool,
        typename std::remove_cv< decltype( std::invoke( std::declval< F&& >(), std::declval< Args&& >()... ) ) >::type
      >::value
    > {};
#endif
  }

  template< typename F, typename ...Args >
  struct is_predicate : public detail::is_predicate< F, detail::lifter< Args... > > {};
  SLCE_HELPER( Predicate, is_predicate )

  template< typename R, typename T, typename U >
  struct is_relation : public std::integral_constant<
    bool,
    is_predicate< R, T, T >::value && 
    is_predicate< R, U, U >::value && 
    is_predicate< R, T, U >::value && 
    is_predicate< R, U, T >::value
  > {};
  SLCE_HELPER( Relation, is_relation )

  template< typename R, typename T, typename U >
  struct is_strict_weak_order : public is_relation< R, T, U > {};
  SLCE_HELPER( StrictWeakOrder, is_strict_weak_order )

  namespace detail {
    template< typename T >
    using with_reference = T&;
    template< typename T, typename Enable = void >
    struct can_reference : public std::false_type {};
    template< typename T >
    struct can_reference< T, typename voider<
      with_reference< T >
    >::type > : public std::true_type {};
    template< typename T, typename Enable = void >
    struct is_dereferenceable : public std::false_type {};
    template< typename T >
    struct is_dereferenceable< T, typename voider<
      decltype( *std::declval< T& >() )
    >::type > : public can_reference< decltype( *std::declval< T& >() ) > {};
  }
#ifdef __cpp_lib_ranges
  template< typename T >
  using incrementable_traits = std::incrementable_traits< T >;
  template< typename T >
  using iter_difference_t = std::iter_difference_t< T >;
  template< typename T >
  using readable_traits = std::readable_traits< T >;
  template< typename T >
  using iter_value_t = std::iter_value_t< T >;
  template< typename T >
  using iter_reference_t = std::iter_reference_t< T >;
  template< typename T >
  using iter_rvalue_reference_t = std::iter_rvalue_reference_t< T >;
#else
  namespace detail {
    template< typename T, typename Enable = void >
    struct has_dereference_type : public std::false_type {};
    template< typename T >
    struct has_dereference_type< T, typename voider<
      typename T::difference_type
    >::type > : public std::true_type {};
    template< typename T, typename Enable = void >
    struct subtracted_type_is_integral : public std::false_type {};
    template< typename T >
    struct subtracted_type_is_integral< T, typename voider<
      decltype( std::declval< const T& >() - std::declval< const T& >() )
    >::type > : public std::is_integral< decltype( std::declval< const T& >() - std::declval< const T& >() ) > {};
    template< typename T, typename Enable = void >
    struct cond_value_type {};
    template< typename T >
    struct cond_value_type< T, typename std::enable_if<
      std::is_object< T >::value
    >::type > {
      using value_type = typename std::remove_cv< T >::type;
    };
  }
  template< typename, typename Enable = void >
  struct incrementable_traits {};
  template< typename T >
  struct incrementable_traits< T*, typename std::enable_if<
    std::is_object< T >::value
  >::type > {
    using difference_type = ptrdiff_t;
  };
  template< typename T >
  struct incrementable_traits< const T > : incrementable_traits< T > {};
  template< typename T >
  struct incrementable_traits< T, typename std::enable_if<
    detail::has_dereference_type< T >::value
  >::type > {
    using difference_type = typename T::difference_type;
  };
  template< typename T >
  struct incrementable_traits< T, typename std::enable_if<
    !detail::has_dereference_type< T >::value &&
    detail::subtracted_type_is_integral< T >::value
  >::type > {
    using difference_type = std::make_signed_t< decltype( std::declval< T >() - std::declval< T >() ) >;
  };
  template< typename T, typename Enable = void >
  struct iter_difference {};
  template< typename T >
  struct iter_difference< T, typename detail::voider<
    typename std::iterator_traits< T >::difference_type
  > > {
    using type = typename std::iterator_traits< T >::difference_type;
  };
  template< typename T >
  struct iter_difference< T, typename detail::voider<
    typename incrementable_traits< T >::difference_type
  > > {
    using type = typename incrementable_traits< T >::difference_type;
  };
  template< typename T >
  using iter_difference_t = typename iter_difference< T >::type;
  template< typename T, typename Enable = void >
  struct readable_traits {};
  template< typename T >
  struct readable_traits< T*, void > : public detail::cond_value_type< T > {};
  template< typename T >
  struct readable_traits< T, typename std::enable_if<
    std::is_array< T >::value
  >::type > {
    using value_type = typename std::remove_cv< typename std::remove_extent_t< T >::type >::type;
  };
  template< typename T >
  struct readable_traits< const T, void > : public readable_traits< T > {};
  template< typename T >
  struct readable_traits< T, typename detail::voider<
    typename T::value_type
  >::type > : public detail::cond_value_type< typename T::value_type > {};
  template< typename T >
  struct readable_traits< T, typename detail::voider<
    typename T::element_type
  >::type > : public detail::cond_value_type< typename T::element_type > {};
  template< typename T, typename Enable = void >
  struct iter_value {};
  template< typename T >
  struct iter_value< T, typename detail::voider<
    typename std::iterator_traits< T >::value_type
  >::type > {
    using type = typename std::iterator_traits< T >::value_type;
  };
  template< typename T >
  struct iter_value< T, typename detail::voider<
    typename readable_traits< T >::value_type
  >::type > {
    using type = typename readable_traits< T >::value_type;
  };
  template< typename T >
  using iter_value_t = typename iter_value< T >::type;
  template< typename T, typename Enable = void >
  struct iter_reference {};
  template< typename T >
  struct iter_reference< T, typename std::enable_if<
    detail::is_dereferenceable< T >::value
  >::type > {
    using type = decltype( *std::declval< T& >() );
  };
  template< typename T >
  using iter_reference_t = typename iter_reference< T >::type;
  namespace detail {
    template< typename T >
    auto iter_move_( T iter ) -> decltype( iter_move( std::declval< T >() ) ) {
      return iter_move( iter );
    }
    template< typename T, typename Enable = void >
    struct has_specialized_iter_move : public std::false_type {};
    template< typename T >
    struct has_specialized_iter_move< T, typename detail::voider<
      decltype( iter_move_( std::declval< T >() ) )
    >::type > : public std::true_type {};
    template< typename T, typename Enable = void >
    struct dereferenceable_as_lvalue : public std::false_type {};
    template< typename T >
    struct dereferenceable_as_lvalue< T, typename std::enable_if<
      std::is_lvalue_reference< decltype( *std::declval< T >() ) >::value
    >::type > : public std::true_type {};
    template< typename T, typename Enable = void >
    struct dereferenceable_as_rvalue : public std::false_type {};
    template< typename T >
    struct dereferenceable_as_rvalue< T, typename std::enable_if<
      !std::is_lvalue_reference< decltype( *std::declval< T >() ) >::value
    >::type > : public std::true_type {};
  }
  namespace range {
    template< typename T >
    auto iter_move( T iter ) -> typename std::enable_if<
      detail::has_specialized_iter_move< T >::value,
      decltype( detail::iter_move_( std::declval< T >() ) )
    >::type {
      return detail::iter_move_( iter );
    }
    template< typename T >
    auto iter_move( T iter ) -> typename std::enable_if<
      !detail::has_specialized_iter_move< T >::value &&
      detail::dereferenceable_as_lvalue< T >::value,
      decltype( std::move( *std::declval< T >() ) )
    >::type {
      return std::move( *iter );
    }
    template< typename T >
    auto iter_move( T iter ) -> typename std::enable_if<
      !detail::has_specialized_iter_move< T >::value &&
      detail::dereferenceable_as_rvalue< T >::value,
      decltype( *std::declval< T >() )
    >::type {
      return *iter;
    }
  }
  template< typename T, typename Enable = void >
  struct iter_rvalue_reference {};
  template< typename T >
  struct iter_rvalue_reference< T, typename detail::voider<
    decltype( range::iter_move( std::declval< T& >() ) )
  >::type > {
    using type = decltype( range::iter_move( std::declval< T& >() ) );
  };
  template< typename T >
  using iter_rvalue_reference_t = typename iter_rvalue_reference< T >::type;
#endif
  namespace detail {
    template< typename T, typename Enable = void >
    struct is_cpp17_iterator : public std::false_type {};
    template< typename T >
    struct is_cpp17_iterator< T, typename std::enable_if<
      is_copyable< T >::value &&
      can_reference< decltype( *std::declval< T >() ) >::value &&
      is_same< decltype( ++std::declval< T >() ), T& >::value &&
      can_reference< decltype( *std::declval< T >()++ ) >::value
    >::type > : public std::true_type {};
    template< typename T, typename Enable = void >
    struct is_cpp17_input_iterator : public std::false_type {};
    template< typename T >
    struct is_cpp17_input_iterator< T, typename voider<
      typename std::enable_if<
        is_cpp17_iterator< T >::value &&
        is_equality_comparable< T >::value &&
	is_signed_integral< typename incrementable_traits< T >::difference_type >::value
      >::type,
      typename incrementable_traits< T >::difference_type,
      typename readable_traits< T >::value_type,
      typename common_reference<
        iter_reference_t< T >&&,
        typename readable_traits< T >::value_type&
      >::type,
      decltype( *std::declval< T >()++ ),
      typename common_reference<
        decltype( *std::declval< T >()++ )&&,
        typename readable_traits< T >::value_type&
      >::type
    >::type > : public std::true_type {};
    template< typename T, typename Enable = void >
    struct is_cpp17_forward_iterator : public std::false_type {};
    template< typename T >
    struct is_cpp17_forward_iterator< T, typename std::enable_if<
      is_cpp17_input_iterator< T >::value &&
      is_constructible< T >::value &&
      std::is_lvalue_reference< iter_reference_t< T > >::value &&
      is_same<
        typename remove_cvref< iter_reference_t< T > >::type,
        typename readable_traits< T >::value_type
      >::value &&
      is_convertible_to< decltype( std::declval< T >()++ ), const T& >::value &&
      is_same< decltype( *std::declval< T >()++ ), iter_reference_t< T > >::value
    >::type > : public std::true_type {};
    template< typename T, typename Enable = void >
    struct is_cpp17_bidirectional_iterator : public std::false_type {};
    template< typename T >
    struct is_cpp17_bidirectional_iterator< T, typename std::enable_if<
      is_cpp17_forward_iterator< T >::value &&
      is_same< decltype( --std::declval< T >() ), T& >::value &&
      is_convertible_to< decltype( std::declval< T >()-- ), const T& >::value &&
      is_same< decltype( *std::declval< T >()-- ), iter_reference_t< T > >::value
    >::type > : public std::true_type {};
    template< typename T, typename Enable = void >
    struct is_cpp17_random_access_iterator : public std::false_type {};
    template< typename T >
    struct is_cpp17_random_access_iterator< T, typename std::enable_if<
      is_cpp17_bidirectional_iterator< T >::value &&
      is_strict_totally_ordered< T >::value &&
      is_same< decltype( std::declval< T >() += std::declval< typename incrementable_traits< T >::difference_type >() ), T& >::value &&
      is_same< decltype( std::declval< T >() -= std::declval< typename incrementable_traits< T >::difference_type >() ), T& >::value &&
      is_same< decltype( std::declval< T >() + std::declval< typename incrementable_traits< T >::difference_type >() ), T >::value &&
      is_same< decltype( std::declval< typename incrementable_traits< T >::difference_type >() + std::declval< T >() ), T >::value &&
      is_same< decltype( std::declval< T >() - std::declval< typename incrementable_traits< T >::difference_type >() ), T >::value &&
      is_same< decltype( std::declval< T >() - std::declval< T >() ), typename incrementable_traits< T >::difference_type >::value &&
      is_convertible_to< iter_reference_t< T >, decltype( std::declval< T >()[ std::declval< typename incrementable_traits< T >::difference_type >() ] ) >::value
    >::type > : public std::true_type {};
  }

  template< typename T, typename Enable = void >
  struct is_readable : public std::false_type {};
  template< typename T >
  struct is_readable< T, typename detail::voider<
    iter_value_t< T >,
    iter_reference_t< T >,
    iter_rvalue_reference_t< T >
  >::type > : public std::true_type {};
  SLCE_HELPER( Readable, is_readable )

  template< typename Out, typename T, typename Enable = void >
  struct is_writable : public std::false_type {};
  template< typename Out, typename T >
  struct is_writable< Out, T, typename detail::voider<
    decltype( *std::declval< Out&& >() = std::forward< T >( std::declval< T&& >() ) ),
    decltype( *std::forward< Out >( std::declval< Out&& >() ) = std::forward< T >( std::declval< T&& >() ) ),
    decltype( const_cast< const iter_reference_t< Out >&& >( *std::declval< Out&& >() ) =
      std::forward< T >( std::declval< T&& >() ) ),
    decltype( const_cast< const iter_reference_t< Out >&& >( *std::forward< Out >( std::declval< Out&& >() ) ) =
      std::forward< T >( std::declval< T&& >() ) )
  >::type > : public std::true_type {};
  SLCE_HELPER( Writable, is_writable )
}
#endif

