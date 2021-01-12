//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/function/simd/x86/flags.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/logical_not.hpp>
#include <eve/function/is_equal.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<real_value T, typename N, x86_abi ABI>
  EVE_FORCEINLINE as_logical_t<wide<T, N, ABI>>
  is_not_equal_(EVE_SUPPORTS(sse2_), wide<T,N,ABI> const &v0, wide<T,N,ABI> const &v1) noexcept
  {
    constexpr auto c = categorize<wide<T, N, ABI>>();
    constexpr auto f = to_integer(cmp_flt::neq_uq);

    if constexpr( !ABI::is_wide_logical )
    {
            if constexpr( c == category::float32x16 ) return mask16{_mm512_cmp_ps_mask   (v0,v1,f)};
      else  if constexpr( c == category::float32x8  ) return mask8 {_mm256_cmp_ps_mask   (v0,v1,f)};
      else  if constexpr( c == category::float32x4  ) return mask8 {_mm_cmp_ps_mask      (v0,v1,f)};
      else  if constexpr( c == category::float64x8  ) return mask8 {_mm512_cmp_pd_mask   (v0,v1,f)};
      else  if constexpr( c == category::float64x4  ) return mask8 {_mm256_cmp_pd_mask   (v0,v1,f)};
      else  if constexpr( c == category::float64x4  ) return mask8 {_mm_cmp_pd_mask      (v0,v1,f)};
      else  if constexpr( c == category::uint64x8   ) return mask8 {_mm512_cmpneq_epu64_mask(v0,v1)};
      else  if constexpr( c == category::uint64x4   ) return mask8 {_mm256_cmpneq_epu64_mask(v0,v1)};
      else  if constexpr( c == category::uint64x2   ) return mask8 {_mm_cmpneq_epu64_mask   (v0,v1)};
      else  if constexpr( c == category::uint32x16  ) return mask16{_mm512_cmpneq_epu32_mask(v0,v1)};
      else  if constexpr( c == category::uint32x8   ) return mask8 {_mm256_cmpneq_epu32_mask(v0,v1)};
      else  if constexpr( c == category::uint32x4   ) return mask8 {_mm_cmpneq_epu32_mask   (v0,v1)};
      else  if constexpr( c == category::uint16x32  ) return mask32{_mm512_cmpneq_epu16_mask(v0,v1)};
      else  if constexpr( c == category::uint16x16  ) return mask16{_mm256_cmpneq_epu16_mask(v0,v1)};
      else  if constexpr( c == category::uint16x8   ) return mask8 {_mm_cmpneq_epu16_mask    (v0,v1)};
      else  if constexpr( c == category::uint8x64   ) return mask64{_mm512_cmpneq_epu8_mask (v0,v1)};
      else  if constexpr( c == category::uint8x32   ) return mask32{_mm256_cmpneq_epu8_mask (v0,v1)};
      else  if constexpr( c == category::uint8x16   ) return mask16{_mm_cmpneq_epu8_mask    (v0,v1)};
      else  if constexpr( c == category::int64x8    ) return mask8 {_mm512_cmpneq_epi64_mask(v0,v1)};
      else  if constexpr( c == category::int64x4    ) return mask8 {_mm256_cmpneq_epi64_mask(v0,v1)};
      else  if constexpr( c == category::int64x2    ) return mask8 {_mm_cmpneq_epi64_mask   (v0,v1)};
      else  if constexpr( c == category::int32x16   ) return mask16{_mm512_cmpneq_epi32_mask(v0,v1)};
      else  if constexpr( c == category::int32x8    ) return mask8 {_mm256_cmpneq_epi32_mask(v0,v1)};
      else  if constexpr( c == category::int32x4    ) return mask8 {_mm_cmpneq_epi32_mask   (v0,v1)};
      else  if constexpr( c == category::int16x32   ) return mask32{_mm512_cmpneq_epi16_mask(v0,v1)};
      else  if constexpr( c == category::int16x16   ) return mask16{_mm256_cmpneq_epi16_mask(v0,v1)};
      else  if constexpr( c == category::int16x8    ) return mask8 {_mm_cmpneq_epi16_mask   (v0,v1)};
      else  if constexpr( c == category::int8x64    ) return mask64{_mm512_cmpneq_epi8_mask (v0,v1)};
      else  if constexpr( c == category::int8x32    ) return mask32{_mm256_cmpneq_epi8_mask (v0,v1)};
      else  if constexpr( c == category::int8x16    ) return mask16{_mm_cmpneq_epi8_mask    (v0,v1)};
    }
    else
    {
            if constexpr( c == category::float32x8  ) return _mm256_cmp_ps(v0,v1,f);
      else  if constexpr( c == category::float64x4  ) return _mm256_cmp_pd(v0,v1,f);
      else  if constexpr( c == category::float32x4  ) return _mm_cmpneq_ps(v0,v1);
      else  if constexpr( c == category::float64x2  ) return _mm_cmpneq_pd(v0,v1);
      else  if constexpr(supports_xop)
      {
              if constexpr( c == category::uint64x2 ) return _mm_comneq_epu64(v0,v1);
        else  if constexpr( c == category::uint32x4 ) return _mm_comneq_epu32(v0,v1);
        else  if constexpr( c == category::uint16x8 ) return _mm_comneq_epu16(v0,v1);
        else  if constexpr( c == category::uint8x16 ) return _mm_comneq_epu8 (v0,v1);
        else  if constexpr( c == category::int64x2  ) return _mm_comneq_epi64(v0,v1);
        else  if constexpr( c == category::int32x4  ) return _mm_comneq_epi32(v0,v1);
        else  if constexpr( c == category::int16x8  ) return _mm_comneq_epi16(v0,v1);
        else  if constexpr( c == category::int8x16  ) return _mm_comneq_epi8 (v0,v1);
      }
      else                                            return logical_not(is_equal(v0,v1));
    }
  }
}