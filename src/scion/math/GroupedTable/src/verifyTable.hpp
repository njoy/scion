void verifyTable( ) {

  // check sizes - there must be at least two boundaries
  if ( ! verification::isAtLeastOfSize( this->bounds(), 2 )  ) {

    Log::error( "Insufficient boundary values defined for grouped data "
            "(at least 2 values are required)" );
    Log::info( "Boundary size: {}", this->bounds().size() );
    throw std::exception();
  }

  // check sizes - bounds must be one longer than values
  if ( this->bounds().size() != this->values().size() + 1 ) {

    Log::error( "Inconsistent boundaries and values defined for grouped data "
            "(number of boundaries must be one greater than number of values)" );
    Log::info( "Boundaries: {}", this->bounds().size() );
    Log::info( "Values: {}", this->values().size() );
    throw std::exception();
  }

  // check that the energy values are all increasing, with
  // no repeated values
  if ( ! verification::isSorted( this->bounds() ) ) {

    Log::error( "The boundary values do not appear to be in ascending order." );
    throw std::exception();
  }

  if ( ! verification::isUnique( this->bounds() ) ) {

    Log::error( "The boundary values do not appear to be in unique." );
    throw std::exception();
  }
}