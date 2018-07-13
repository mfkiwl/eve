//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_PLUS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_PLUS_HPP_INCLUDED

#include <eve/arch.hpp>
#include <eve/module/core/function/simd/common/plus.hpp>

#if defined(EVE_HW_X86)
#if EVE_HW_X86 >= EVE_SSE2_VERSION
#include <eve/module/core/function/simd/x86/sse2/plus.hpp>
#endif

#if EVE_HW_X86 >= EVE_AVX_VERSION
#include <eve/module/core/function/simd/x86/avx/plus.hpp>
#endif

#if EVE_HW_X86 >= EVE_AVX2_VERSION
#include <eve/module/core/function/simd/x86/avx2/plus.hpp>
#endif
#endif

#if defined(EVE_HW_POWERPC)
#if EVE_HW_POWERPC >= EVE_VMX_VERSION
#include <eve/module/core/function/simd/ppc/vmx/plus.hpp>
#endif
#endif

#endif