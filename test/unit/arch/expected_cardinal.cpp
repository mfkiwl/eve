//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/wide.hpp>

TTS_CASE("Check for 64 bits ABI expected cardinal")
{
  TTS_EQUAL( (eve::expected_cardinal_v<double, eve::arm_64_>), 1);
  TTS_EQUAL( (eve::expected_cardinal_v<float , eve::arm_64_>), 2);
  TTS_EQUAL( (eve::expected_cardinal_v<short , eve::arm_64_>), 4);
  TTS_EQUAL( (eve::expected_cardinal_v<char  , eve::arm_64_>), 8);
}

TTS_CASE("Check for 128 bits ABI expected cardinal")
{
  TTS_EQUAL( (eve::expected_cardinal_v<double, eve::arm_128_>), 2  );
  TTS_EQUAL( (eve::expected_cardinal_v<float , eve::arm_128_>), 4  );
  TTS_EQUAL( (eve::expected_cardinal_v<short , eve::arm_128_>), 8  );
  TTS_EQUAL( (eve::expected_cardinal_v<char  , eve::arm_128_>), 16 );

  TTS_EQUAL( (eve::expected_cardinal_v<double, eve::ppc_>), 2  );
  TTS_EQUAL( (eve::expected_cardinal_v<float , eve::ppc_>), 4  );
  TTS_EQUAL( (eve::expected_cardinal_v<short , eve::ppc_>), 8  );
  TTS_EQUAL( (eve::expected_cardinal_v<char  , eve::ppc_>), 16 );

  TTS_EQUAL( (eve::expected_cardinal_v<double, eve::x86_128_>), 2  );
  TTS_EQUAL( (eve::expected_cardinal_v<float , eve::x86_128_>), 4  );
  TTS_EQUAL( (eve::expected_cardinal_v<short , eve::x86_128_>), 8  );
  TTS_EQUAL( (eve::expected_cardinal_v<char  , eve::x86_128_>), 16 );

  TTS_EQUAL( (eve::expected_cardinal_v<double, eve::emulated_>), 2  );
  TTS_EQUAL( (eve::expected_cardinal_v<float , eve::emulated_>), 4  );
  TTS_EQUAL( (eve::expected_cardinal_v<short , eve::emulated_>), 8  );
  TTS_EQUAL( (eve::expected_cardinal_v<char  , eve::emulated_>), 16 );
}

TTS_CASE("Check for 256 bits ABI expected cardinal")
{
  TTS_EQUAL( (eve::expected_cardinal_v<double, eve::x86_256_>), 4  );
  TTS_EQUAL( (eve::expected_cardinal_v<float , eve::x86_256_>), 8  );
  TTS_EQUAL( (eve::expected_cardinal_v<short , eve::x86_256_>), 16 );
  TTS_EQUAL( (eve::expected_cardinal_v<char  , eve::x86_256_>), 32 );
}