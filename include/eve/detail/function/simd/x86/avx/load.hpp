//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_FUNCTION_SIMD_X86_AVX_LOAD_HPP_INCLUDED
#define EVE_DETAIL_FUNCTION_SIMD_X86_AVX_LOAD_HPP_INCLUDED

#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <eve/as.hpp>

#if defined(EVE_COMP_IS_GNUC)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-attributes"
#endif

namespace eve { namespace detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE auto  load(as_<pack<T,N>> const&, eve::avx_ const&, T* p) noexcept
                        requires( typename pack<T,N>::storage_type, Arithmetic<T>)
  {
    if constexpr( std::is_same_v<T, double> ) return _mm256_loadu_pd(p);
    if constexpr( std::is_same_v<T, float>  ) return _mm256_loadu_ps(p);
    if constexpr( std::is_integral_v<T>     ) return _mm256_loadu_si256((__m256i*)p);
  }

  template<typename T, typename N, std::size_t A>
  EVE_FORCEINLINE auto  load( as_<pack<T,N>> const& tgt, eve::avx_ const& mode
                            , aligned_ptr<T,A> p
                            ) noexcept
                        requires( typename pack<T,N>::storage_type, Arithmetic<T>)
  {
    if constexpr( A >= 16)
    {
      if constexpr( std::is_same_v<T, double> ) return _mm256_load_pd(p.get());
      if constexpr( std::is_same_v<T, float>  ) return _mm256_load_ps(p.get());
      if constexpr( std::is_integral_v<T>     ) return _mm256_load_si256((__m256i*)p.get());
    }
    else
    {
      return load(tgt,mode,p.get());
    }
  }
} }

#if defined(EVE_COMP_IS_GNUC)
#pragma GCC diagnostic pop
#endif

#endif
