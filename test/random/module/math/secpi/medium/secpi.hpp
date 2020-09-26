//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/detail/function/tmp/boost_math_cospi.hpp>
#include <eve/function/secpi.hpp>
#include <eve/function/abs.hpp>
#include <tts/tests/range.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/maxflint.hpp>
#include <eve/function/is_flint.hpp>
#include <eve/function/is_even.hpp>
#include <eve/function/rec.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on secpi", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto my_stdsecpi =  tts::vectorize<T> ( [](auto x)
    {
      auto z = eve::abs(x);
      if (eve::is_even(z)) return   v_t(1);
      if (z-v_t(0.5) == eve::trunc(z)) return eve::nan(eve::as<v_t>());
      return  v_t(eve::rec(boost::math::cos_pi(double(x))));
    });

  eve::rng_producer<T> p(v_t(-100000.0), v_t(100000.0));
  TTS_RANGE_CHECK(p, my_stdsecpi, eve::medium(eve::secpi));
}