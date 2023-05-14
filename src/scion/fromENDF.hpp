#ifndef NJOY_SCION_FROMENDF
#define NJOY_SCION_FROMENDF

// system includes

// other includes
#include "utility/overload.hpp"
#include "scion/math/LegendreSeries.hpp"
#include "scion/math/PolynomialSeries.hpp"
#include "scion/math/LinearLinearTable.hpp"
#include "ENDFtk/section.hpp"
#include "ENDFtk/section/1/452.hpp"
#include "ENDFtk/section/6.hpp"

namespace njoy {
namespace scion {

std::variant< math::PolynomialSeries< double >,
              math::LinearLinearTable< double > >
fromENDF( const njoy::ENDFtk::section::Type< 1, 452 >& section ) {

  using Variant = std::variant< math::PolynomialSeries< double >,
                                math::LinearLinearTable< double > >;

  return std::visit(
      utility::overload {
        [] ( const njoy::ENDFtk::section::PolynomialMultiplicity& data ) -> Variant {

          std::vector< double > coefficients( data.coefficients().begin(), data.coefficients().end() );
          return math::PolynomialSeries< double >( 1e-5, 2e+7, std::move( coefficients ) );
        },
        [] ( const njoy::ENDFtk::section::TabulatedMultiplicity& data ) -> Variant {

          std::vector< double > energies( data.energies().begin(), data.energies().end() );
          std::vector< double > multiplicities( data.multiplicities().begin(), data.multiplicities().end() );
          return math::LinearLinearTable< double >(
                        std::move( energies ),
                        std::move( multiplicities ) );
        }
      },
      section.nubar() );
}

std::vector< math::LegendreSeries< double > >
fromENDF( const njoy::ENDFtk::section::Type< 6 >::ContinuumEnergyAngle::LegendreCoefficients& section ) {

  std::vector< math::LegendreSeries< double > > distributions;
  for ( const auto& coefficients : section.coefficients() ) {

    distributions.emplace_back( std::vector< double >{ coefficients.begin(), coefficients.end() } );
  }
  return distributions;
}

} // scion namespace
} // njoy namespace

#endif
