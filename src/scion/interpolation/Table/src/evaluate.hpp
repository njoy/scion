/**
 *  @brief Evaluate the function for a value of x
 *
 *  @param x   the value to be evaluated
 */
Y evaluate( const X& x ) const {

  auto xIter = std::next( this->x().begin() );
  if ( x != *this->x().begin() ) {

    xIter = std::lower_bound( this->x().begin(), this->x().end(), x );
  }

  if ( this->x().end() == xIter ) {

    return Y( 0. );
  }
  else if ( this->x().begin() == xIter ) {

    return Y( 0. );
  }
  else {

    auto yIter = this->y().begin();
    std::advance( yIter, std::distance( this->x().begin(), xIter ) );

    return this->interpolator()( x, *std::prev( xIter ), *xIter,
                                    *std::prev( yIter ), *yIter );
  }
}
