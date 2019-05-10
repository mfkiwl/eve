//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_NAN_HPP
#define IS_NAN_HPP

#include <eve/function/scalar/is_nan.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/as_logical.hpp>
#include <type_traits>

TTS_CASE("Check is_nan return type")
{
  TTS_EXPR_IS(eve::is_nan(Type(0)),  eve::as_logical_t<Type>);
}

TTS_CASE("Check eve::is_nan behavior")
{
  TTS_EQUAL(eve::is_nan(Type{0}), eve::False<Type>());
  TTS_EQUAL(eve::is_nan(Type{2}), eve::False<Type>());
  if constexpr(std::is_floating_point_v<Type>)
  {
    TTS_EQUAL(eve::is_nan(eve::Nan<Type>()), eve::True<Type>());
    TTS_EQUAL(eve::is_nan(eve::Inf<Type>()), eve::False<Type>());
    TTS_EQUAL(eve::is_nan(eve::Minf<Type>()), eve::False<Type>());
  }
}

#endif
