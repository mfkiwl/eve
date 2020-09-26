#include <eve/function/fnma.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_t = eve::wide<float, eve::fixed<4>>;

int main()
{
  float es  = eve::eps(eve::as<float>());
  float esm1 = es-1.0f;
  float esp1 = es+1.0f;
  float vm  = eve::valmax(eve::as<float>());
  wide_t oi = {2, -3, esp1,  vm};
  wide_t pi = {3, -2, esm1,  2 };
  wide_t qi = {4, -1, -1.0f, vm};

  std::cout << "---- simd" << '\n'
            << " <- oi                                 = " << oi << '\n'
            << " <- pi                                 = " << pi << '\n'
            << " <- qi                                 = " << qi << '\n'
            << " -> pedantic(fnma)(oi, pi, qi)        = " << eve::pedantic(eve::fnma)(oi, pi, qi) << '\n'
            << " -> numeric(fnma)(oi, pi, qi)         = " << eve::numeric(eve::fnma)(oi, pi, qi) << '\n'
            << " -> fnma(oi, pi, qi)                   = " << eve::fnma(oi, pi, qi) << '\n'
            << "\n if the last fnma result ends by '0, -inf}', it means that\n"
            << " the system has no simd fnma family intrinsics\n"
            << " or is not configured to use them.\n\n";

  std::cout << "---- scalar" << std::setprecision(10) << '\n'
            << " <- vm =                                " << vm << '\n'
            << " -> pedantic(fnma)(vm, 2.0f, -vm)     = " << eve::pedantic(eve::fnma)(vm, 2.0f, -vm) << '\n'
            << " -> numeric(fnma)(vm, 2.0f, -vm)      = " << eve::numeric(eve::fnma)(vm, 2.0f, -vm) << '\n'
            << " -> fnma(vm, 2.0f, -vm)                = " << eve::fnma(vm, 2.0f, -vm) << '\n'
            << " <- esm1                               = " << esm1 << '\n'
            << " <- esp1                               = " << esp1 << '\n'
            << " -> pedantic(fnma)(esp1, esm1, -1.0f) = " << eve::pedantic(eve::fnma)(esp1, esm1,-1.0f) << '\n'
            << " -> numeric(fnma)(esp1, esm1, -1.0f)  = " << eve::numeric(eve::fnma)(esp1, esm1, -1.0f) << '\n'
            << " -> fnma(esp1, esm1, -1.0f)            = " << eve::fnma(esp1, esm1, -1.0f) << '\n';
  return 0;
}