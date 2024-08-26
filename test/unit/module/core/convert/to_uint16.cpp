//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

#include <type_traits>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check eve::convert return type", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using t_t = eve::wide<std::uint16_t, eve::cardinal_t<T>>;

  TTS_EXPR_IS(eve::convert(T(), eve::as<std::uint16_t>()), t_t);
  TTS_EXPR_IS(eve::convert[eve::saturated](T(), eve::as<std::uint16_t>()), t_t);
};

//==================================================================================================
// Value tests
//==================================================================================================
TTS_CASE_TPL("Check eve::convert arithmetic behavior", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using t_t          = eve::wide<std::uint16_t, eve::cardinal_t<T>>;
  using v_t          = eve::element_type_t<T>;
  constexpr auto tgt = eve::as<std::uint16_t>();

  TTS_EQUAL(eve::convert((T(0)), tgt), static_cast<t_t>(0));
  TTS_EQUAL(eve::convert((T(42.69)), tgt), static_cast<t_t>(v_t(42.69)));

  if constexpr( eve::integral_value<T> )
  {
    // with floating value this test produces undefined behaviour
    TTS_EQUAL(eve::convert(eve::valmin(eve::as<T>()), tgt),
              static_cast<t_t>(eve::valmin(eve::as<v_t>())));
    TTS_EQUAL(eve::convert(eve::valmax(eve::as<T>()), tgt),
              static_cast<t_t>(eve::valmax(eve::as<v_t>())));
  }
};

TTS_CASE_TPL("Check saturated eve::convert arithmetic behavior", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using t_t          = eve::wide<std::uint16_t, eve::cardinal_t<T>>;
  using v_t          = eve::element_type_t<T>;
  constexpr auto tgt = eve::as<std::uint16_t>();

  TTS_EQUAL(eve::convert[eve::saturated]((T(0)), tgt), static_cast<t_t>(0));
  TTS_EQUAL(eve::convert[eve::saturated]((T(42.69)), tgt), static_cast<t_t>(v_t(42.69)));

  if constexpr( eve::integral_value<T> )
  {
    // with floating value this test produces undefined behaviour
    TTS_EQUAL(eve::convert[eve::saturated](eve::valmin(eve::as<T>()), tgt), (t_t(0)));

    if constexpr( sizeof(v_t) <= 2 )
    {
      TTS_EQUAL(eve::convert[eve::saturated](eve::valmax(eve::as<T>()), tgt),
                t_t(eve::valmax(eve::as<v_t>())));
    }
    else
    {
      TTS_EQUAL(eve::convert[eve::saturated](eve::valmax(eve::as<T>()), tgt),
                (eve::valmax(eve::as<t_t>())));
    }
  }
};

TTS_CASE_TPL("Check eve::convert logical behavior", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using t_t          = eve::logical<eve::wide<std::uint16_t, eve::cardinal_t<T>>>;
  constexpr auto tgt = eve::as<eve::logical<std::uint16_t>>();

  TTS_EQUAL(eve::convert(eve::logical<T>(true), tgt), t_t(true));
  TTS_EQUAL(eve::convert(eve::logical<T>(false), tgt), t_t(false));

  eve::logical<T> mixed([](auto i, auto) { return i % 2 == 0; });
  t_t             ref([](auto i, auto) { return i % 2 == 0; });

  TTS_EQUAL(eve::convert(mixed, tgt), ref);
};
