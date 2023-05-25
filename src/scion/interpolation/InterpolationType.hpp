#ifndef NJOY_SCION_INTERPOLATION_INTERPOLATIONTYPE
#define NJOY_SCION_INTERPOLATION_INTERPOLATIONTYPE

// system includes

// other includes

namespace njoy {
namespace scion {
namespace interpolation {

  enum class InterpolationType : short {

    Histogram,       // constant or histogram interpolation
    LinearLinear,    // y is linear in x
    LinearLog,       // y is linear in ln(x)
    LogLinear,       // ln(y) is linear in x
    LogLog           // ln(y) is linear in ln(x)
  };

} // interpolation namespace
} // scion namespace
} // njoy namespace

#endif
