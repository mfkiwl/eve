//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/function/reverse.hpp>
#include <eve/wide.hpp>

template <typename T, typename Env, typename Filler>
void test_reverse(Env& runtime, bool verbose, Filler filler)
{
  T input(filler);
  T expected([&](int i, int size) { return input.get(size - i - 1); });

  TTS_EQUAL(eve::reverse(input), expected);
}

TTS_CASE_TPL("Check reverse swizzle for arithmetic type", EVE_TYPE )
{
  test_reverse<T>(runtime, verbose, [](int i, int) { return 1+i; } );
}

TTS_CASE_TPL("Check everse swizzle for logical type", EVE_TYPE )
{
  test_reverse<eve::logical<T>>(runtime, verbose, [](int i, int) { return i%3 == 0; } );
}
