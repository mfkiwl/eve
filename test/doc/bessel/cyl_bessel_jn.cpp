// revision 1
#include <eve/module/bessel.hpp>
#include <iostream>

eve::wide<double> wdf([](auto i, auto c)->double{ return 2*(i-c/2);});
eve::wide<std::uint64_t> wu([](auto i, auto )->std::uint64_t{ return 2*i;});
eve::wide wd{0.5, 1.5, 0.1, 1.0, 19.0, 25.0, 21.5, 10000.0};
eve::wide m{0.5, -1.0, 1.5, -2.0, 2.5, -2.6, 3.2, -12.0};

int main()
{
   std::cout << "<- wdf = " << wdf << "\n";
   std::cout << "<- wu = " << wu << "\n";
   std::cout << "<- m  = " << m << "\n";
   std::cout << "<- wd  = " << wd << "\n";

   std::cout << "-> cyl_bessel_jn(wu, wdf)                = " << eve::cyl_bessel_jn(wu, wdf) << "\n";
   std::cout << "-> cyl_bessel_jn[ignore_last(2)](wu, wdf)= " << eve::cyl_bessel_jn[eve::ignore_last(2)](wu, wdf) << "\n";
   std::cout << "-> cyl_bessel_jn[wu != 2u](wu, wdf)      = " << eve::cyl_bessel_jn[wu != 2u](wu, wdf) << "\n";
   std::cout << "-> cyl_bessel_jn(m, wd)                  = " << eve::cyl_bessel_jn(m, wd) << "\n";
}
