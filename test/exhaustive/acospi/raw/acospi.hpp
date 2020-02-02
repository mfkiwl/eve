//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/acospi.hpp>
#include <eve/constant/invpi.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide exhaustive check on acospi")
{
  auto std_acospi = tts::vectorize<Type>( [](auto e) { return eve::Invpi<Value>()*std::acos(e); } );

  eve::exhaustive_producer<Type> p(-1, 1);
  TTS_ULP_RANGE_CHECK(p, std_acospi, eve::raw_(eve::acospi), 1024); 
}
