//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_ngtz.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <cmath>

int main()
{
  auto lmin = eve::valmin(eve::as<EVE_VALUE>());
  auto lmax = eve::valmax(eve::as<EVE_VALUE>());

  auto const std__is_ngtz = [](EVE_VALUE x) -> eve::logical<EVE_VALUE>  { return !(x > 0); };

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE> (EVE_NAME(std__is_ngtz) , xp, std__is_ngtz, arg0);
  run<EVE_VALUE> (EVE_NAME(is_ngtz) , xp, eve::is_ngtz, arg0);
  run<EVE_TYPE>  (EVE_NAME(is_ngtz) , xp, eve::is_ngtz, arg0);
}