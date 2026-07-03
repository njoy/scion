void verifyTable( ) {

  // check sizes - there must be at least two boundaries
  if ( ! verification::isAtLeastOfSize( this->boundaries(), 2 )  ) {

    Log::error( "Insufficient boundary values defined for grouped data "
            "(at least 2 values are required)" );
    Log::info( "Boundary size: {}", this->boundaries().size() );
    throw std::exception();
  }

  // check sizes - bounds must be one longer than values
  if ( this->boundaries().size() != this->values().size() + 1 ) {

    Log::error( "Inconsistent boundaries and values defined for grouped data "
            "(number of boundaries must be one greater than number of values)" );
    Log::info( "Boundaries: {}", this->boundaries().size() );
    Log::info( "Values: {}", this->values().size() );
    throw std::exception();
  }

  // check that the energy values are all increasing, with
  // no repeated values
  if ( ! verification::isSorted( this->boundaries() ) ) {

    Log::error( "The boundary values do not appear to be in ascending order." );
    throw std::exception();
  }

  if ( ! verification::isUnique( this->boundaries() ) ) {

    Log::error( "The boundary values do not appear to be in unique." );
    throw std::exception();
  }
}