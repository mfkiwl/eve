//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/named_shuffles/named_shuffle_utils.hpp>
#include <eve/module/core/regular/shuffle_v2.hpp>

namespace eve
{

//================================================================================================
//! @addtogroup core_named_shuffles
//! @{
//!    @var slide_left
//!    @brief a named shuffles for sliding two simd values together and selecting
//!    one register. Common names for this would also include "shift", "extract".
//!    Second value can be ommitted for an implicit zero.
//!
//!    **Defined in Header**
//!
//!    @code
//!    #include <eve/module/core.hpp>
//!    @endcode
//!
//!    As any named shuffle, allows to pass a group size, to treat multiple elements as one.
//!    Group size has to be 0 < G <= T::size()
//!    Shift * GroupSize <= T::size()
//!    Shift >= 0
//!
//!    @code
//!    template <simd_value T, std::ptrdiff_t S>
//!    T slide_left(T x, eve::index<S>);  // (1)
//!
//!    template <simd_value T, std::ptrdiff_t G, std::ptrdiff_t S>
//!    T slide_left(T x, eve::fixed<G>, eve::index<S>);  // (2)
//!
//!    template <simd_value T, std::ptrdiff_t S>
//!    T slide_left(T x, T y, eve::index<S>);  // (3)
//!
//!    template <simd_value T, std::ptrdiff_t G, std::ptrdiff_t S>
//!    T slide_left(T x, T y, eve::fixed<G>, eve::index<S>);  // (4)
//!    @endcode
//!
//! **Parameters**
//!
//! * x, y - simd_values to shuffle
//! * G - (optional) - number of elements to treat as one.
//! * S - shift by how many elements to shift
//!
//!  (2), (4) - call (1) (3) respectively, with S = G * S
//!  (1) - equivalent to calling `eve::slide_left(x, eve::zero(eve::as(x)));`
//!  (3) - slide_left [abcd], [efgh], index<1> ==> [bcde]
//!
//! **Return value**
//! shuffled register
//!
//! @groupheader{Example}
//!
//!  @godbolt{doc/core/named_shuffles/slide_left.cpp}
//! @}
//================================================================================================

struct slide_left_impl_t
{
  // One agr
  template<simd_value T, std::ptrdiff_t G, std::ptrdiff_t S>
  static constexpr auto pattern(eve::as<T>, eve::fixed<G>, eve::index_t<S>)
  {
    static_assert(G > 0 && 0 <= S && S <= T::size() / G);
    return eve::fix_pattern<T::size() / G>([](int i, int n) { return (i + S) < n ? i + S : na_; });
  }

  template<simd_value T, std::ptrdiff_t G, std::ptrdiff_t S_>
  static constexpr auto level(eve::as<T>, eve::fixed<G> g, eve::index_t<S_> s)
  {
    constexpr std::ptrdiff_t S = G * S_;
    if constexpr( S == 0 ) return 0;
    else if constexpr ( S == T::size() ) return 1;
    else if constexpr ( current_api >= neon ) return 3;
    else if constexpr( eve::has_aggregated_abi_v<T> )
    {
      using half_t = decltype(T {}.slice(lower_));
      // When combining halves, always taking just max. Even if that might not report
      // the mask required for one of the halves.
      if constexpr (S > T::size() / 2) {
        return level(eve::as<half_t> {}, eve::lane<1>, eve::index<S - T::size() / 2>);
      } else {
        auto halves_together = level(eve::as<half_t> {}, eve::as<half_t> {}, g, s);
        auto just_second = level(eve::as<half_t>{}, g, s);
        return std::max(halves_together, just_second);
      }
    }
    else { return 2; }
  }

  // Two args

  template<simd_value T, std::ptrdiff_t G, std::ptrdiff_t S_>
  static constexpr auto level(eve::as<T>, eve::as<T>, eve::fixed<G>, eve::index_t<S_>)
  {
    constexpr std::ptrdiff_t S = S_ * G;
    constexpr bool is_shift_by_8 = (S * sizeof(element_type_t<T>) % 8) == 0;
    if constexpr( S == 0 || S == T::size() ) return 0;
    if constexpr ( current_api >= neon ) return 2;

    if (current_api >= sse4_2) return 2;
    // sse2
    return is_shift_by_8 ? 2 : 6;
  }
};

struct slide_left_t : detail::named_shuffle_1<slide_left_impl_t>
{};

inline constexpr auto slide_left2 = slide_left_t {};

}