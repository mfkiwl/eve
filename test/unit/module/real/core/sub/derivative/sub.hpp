//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/derivative/sub.hpp>
#include <type_traits>

TTS_CASE_TPL("Check derivative(sub) return type", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    using ui_t = eve::detail::as_integer_t<T, unsigned>;
    TTS_EXPR_IS(eve::derivative(eve::sub)(T(), T(), unsigned(), unsigned()), T);
    TTS_EXPR_IS(eve::derivative(eve::sub)(T(), T(), ui_t(), ui_t()), T);
  }
  else
  {
    TTS_PASS("Unsupported type");
  }
}

TTS_CASE_TPL("Check eve::derivative(eve::sub) behavior", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    TTS_EQUAL(eve::derivative(eve::sub)(T{10},T{5}, 0u, 0u), T(5));
    TTS_EQUAL(eve::derivative(eve::sub)(T{10},T{5}, 1u, 0u), T(1));
    TTS_EQUAL(eve::derivative(eve::sub)(T{10},T{5}, 2u, 0u), T(0));
    TTS_EQUAL(eve::derivative(eve::sub)(T{-10},T{5}, 0u, 1u), T(-1));
    TTS_EQUAL(eve::derivative(eve::sub)(T{-10},T{5}, 1u, 1u), T(0));
    TTS_EQUAL(eve::derivative(eve::sub)(T{-10},T{5}, 0u, 2u), T(0));
  }
  else
  {
    TTS_PASS("Unsupported type");
  }
}