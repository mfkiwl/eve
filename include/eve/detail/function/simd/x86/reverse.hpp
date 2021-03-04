//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>

namespace eve::detail
{
  template<real_scalar_value T, typename N, x86_abi ABI>
  EVE_FORCEINLINE wide<T,N,ABI> reverse_( EVE_SUPPORTS(sse2_), wide<T,N,ABI> const& v) noexcept
  {
    // TODO: implement here
    return reverse_(EVE_RETARGET(cpu_), v);
  }
}
