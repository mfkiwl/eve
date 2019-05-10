//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_EQUAL_WITH_EQUAL_NANS_HPP
#define IS_EQUAL_WITH_EQUAL_NANS_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/is_equal_with_equal_nans.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check is_equal_with_equal_nans behavior on homogeneous logical<wide>",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>
            )
{
  using eve::wide;
  using eve::logical;

  logical<wide<Type, T>>  lhs([](auto i, auto)  { return i%2 == 0; }),
                          rhs([](auto i, auto)  { return i%3 == 0; });

  logical<wide<Type, T>>  ref([](auto i, auto)  { return eve::is_equal_with_equal_nans((i%2 == 0),(i%3 == 0)); });

  TTS_EQUAL(ref, eve::is_equal_with_equal_nans(lhs, rhs));
}

TTS_CASE_TPL("Check is_equal_with_equal_nans behavior on logical<wide> and scalar",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>
             )
{
  using eve::wide;
  using eve::logical;

  logical<wide<Type, T>>  lhs([](auto i, auto)  { return i%2 == 0; });
  logical<wide<Type, T>>  ref([](auto i, auto)  { return eve::is_equal_with_equal_nans(i%2 == 0,true); });

  TTS_EQUAL(ref, eve::is_equal_with_equal_nans(lhs, logical<Type>(true)));
  TTS_EQUAL(ref, eve::is_equal_with_equal_nans(logical<Type>(true), lhs));
  TTS_EQUAL(ref, eve::is_equal_with_equal_nans(lhs, true));
  TTS_EQUAL(ref, eve::is_equal_with_equal_nans(true, lhs));
}

#endif
