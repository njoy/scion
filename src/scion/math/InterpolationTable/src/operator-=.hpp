/**
 *  @brief Inplace InterpolationTable subtraction
 *
 *  @param[in] right    the table
 */
InterpolationTable& operator-=( const InterpolationTable& right ) /* noexcept */ {

  // for tables that have the same x values and interpolation regions
  if ( ( this->x() == right.x() ) &&
       ( this->boundaries() == right.boundaries() ) &&
       ( this->interpolants() == right.interpolants() ) ) {

    std::transform( this->y().begin(), this->y().end(), right.y().begin(),
                    this->y_.begin(), std::minus< Y >() );
    return *this;
  }
  else {

    Log::error( "Cannot perform operation just yet" );
    throw std::exception();
  }
}
