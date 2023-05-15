static void verifyCoefficients( const std::vector< Y >& coefficients ) {

  if ( 0 == coefficients.size() ) {

    Log::error( "No coefficients defined for a Legendre series expansion" );
    throw std::exception();
  }
}
