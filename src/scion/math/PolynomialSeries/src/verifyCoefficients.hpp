static void verifyCoefficients( const std::vector< Y >& coefficients ) {

  if ( 0 == coefficients.size() ) {

    Log::error( "No coefficients defined for a polynomial series expansion" );
    throw std::exception();
  }
}
