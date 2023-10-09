static void verifyDomain( const X& lower, const X& upper ) {

  if ( ( upper < lower ) || ( upper == lower ) ) {

    Log::error( "Incoherent domain, expected lower < upper" );
    Log::info( "Lower limit: {}", lower );
    Log::info( "Upper limit: {}", upper );
    throw std::exception();
  }
}
