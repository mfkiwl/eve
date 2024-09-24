//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{

template<callable_options O, arithmetic_scalar_value T, typename N>
EVE_FORCEINLINE wide<T, N> sub_(EVE_REQUIRES(neon128_), O const& opts, wide<T, N> a, wide<T, N> b) noexcept
    requires arm_abi<abi_t<T, N>>
{
  if constexpr(O::contains(lower) || O::contains(upper))
  {
    return sub.behavior(cpu_{}, opts, a, b);
  }
  else if constexpr (O::contains(saturated) && integral_value<T>)
  {
      return sub.behavior(cpu_{}, opts, a, b);
  }
  else
  {
    constexpr auto c = categorize<wide<T, N>>();

          if constexpr( c == category::int64x1    ) return vsub_s64 (a, b);
    else  if constexpr( c == category::int64x2    ) return vsubq_s64(a, b);
    else  if constexpr( c == category::uint64x1   ) return vsub_u64 (a, b);
    else  if constexpr( c == category::uint64x2   ) return vsubq_u64(a, b);
    else  if constexpr( c == category::int32x2    ) return vsub_s32 (a, b);
    else  if constexpr( c == category::int32x4    ) return vsubq_s32(a, b);
    else  if constexpr( c == category::uint32x2   ) return vsub_u32 (a, b);
    else  if constexpr( c == category::uint32x4   ) return vsubq_u32(a, b);
    else  if constexpr( c == category::int16x4    ) return vsub_s16 (a, b);
    else  if constexpr( c == category::int16x8    ) return vsubq_s16(a, b);
    else  if constexpr( c == category::uint16x4   ) return vsub_u16 (a, b);
    else  if constexpr( c == category::uint16x8   ) return vsubq_u16(a, b);
    else  if constexpr( c == category::int8x8     ) return vsub_s8  (a, b);
    else  if constexpr( c == category::int8x16    ) return vsubq_s8 (a, b);
    else  if constexpr( c == category::uint8x8    ) return vsub_u8  (a, b);
    else  if constexpr( c == category::uint8x16   ) return vsubq_u8 (a, b);
    else  if constexpr( c == category::float32x2  ) return vsub_f32 (a, b);
    else  if constexpr( c == category::float32x4  ) return vsubq_f32(a, b);
    else if constexpr( current_api >= asimd )
    {
            if constexpr( c == category::float64x1 ) return vsub_f64  (a, b);
      else  if constexpr( c == category::float64x2 ) return vsubq_f64 (a, b);
    }
  }
}

}