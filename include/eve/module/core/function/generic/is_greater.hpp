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

#include <eve/detail/implementation.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/concept/value.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/function/is_greater.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/skeleton_calls.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // regular case
  template<real_value T, real_value U>
  EVE_FORCEINLINE  auto is_greater_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , U const &b) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(is_greater, a, b);
  }

  template<real_scalar_value T>
  EVE_FORCEINLINE  auto is_greater_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , T const &b) noexcept
  {
    return as_logical_t<T>(a > b);
  }

  template<real_simd_value T>
  EVE_FORCEINLINE auto is_greater_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , T const &b) noexcept
  {
    return apply_over(is_greater, a, b);
  }
}

namespace eve
{
  template<value T, value U>
  EVE_FORCEINLINE auto operator >(T const &v0, U const &v1) noexcept
  -> decltype( eve::is_greater(v0,v1) )
  requires compatible_values<T, U>
  {
    return eve::is_greater(v0, v1);
  }
}

