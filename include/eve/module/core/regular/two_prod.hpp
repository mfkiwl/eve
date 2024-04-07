//======================================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/core/regular/zip.hpp>

namespace eve
{
template<typename Options>
struct two_prod_t : elementwise_callable<two_prod_t, Options>
{
  template<eve::floating_value T, eve::floating_value U>
  constexpr EVE_FORCEINLINE
  zipped<common_value_t<T,U>,common_value_t<T,U>> operator()(T a, U b) const
  {
    return EVE_DISPATCH_CALL(a,b);
  }

  EVE_CALLABLE_OBJECT(two_prod_t, two_prod_);
};

//================================================================================================
//! @addtogroup core_accuracy
//! @{
//!   @var two_prod
//!   @brief Computes the [elementwise](@ref glossary_elementwise)
//!   pair of  product and error,
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::floating_value T, eve::floating_value U  >
//!      auto two_prod(T x, U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y` :  [argument](@ref eve::value).
//!
//!   **Return value**
//!
//!     Computes [elementwise](@ref glossary_elementwise) a pair of values `[a,e]` such that:
//!
//!     * `a` is `x*y`
//!     * `e` is a value such that `a`\f$\oplus\f$`e` is equal to `x`\f$\otimes\f$`y`
//!
//!    where \f$\oplus\f$ (resp. \f$\otimes\f$) adds (resp. multiplies) its two parameters with
//!    infinite precision.
//!
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/two_prod.cpp}
//!
//! @}
//================================================================================================

inline constexpr auto two_prod = functor<two_prod_t>;

namespace detail
{
  template<typename T, typename U, callable_options O>
  constexpr EVE_FORCEINLINE auto two_prod_(EVE_REQUIRES(cpu_), O const&, T a, U b)
  {
    auto r0 = a * b;
    return eve::zip(r0, numeric(fms)(a, b, r0));
  }
}}
