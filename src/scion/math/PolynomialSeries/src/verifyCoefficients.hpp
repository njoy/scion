static void verifyCoefficients( const std::vector< Y >& coefficients ) {

  if ( verification::isEmpty( coefficients ) ) {

    Log::error( "No coefficients defined for a polynomial series expansion" );
    throw std::exception();
  }
}
