//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

namespace eve
{
  EVE_MAKE_CALLABLE(reverse_, reverse);
}

#include <eve/detail/function/simd/common/reverse.hpp>

#if defined(EVE_HW_X86)
#  include <eve/detail/function/simd/x86/reverse.hpp>
#endif
