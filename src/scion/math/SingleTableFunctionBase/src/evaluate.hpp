/**
 *  @brief Evaluate the function for a value of x and y
 *
 *  @param x   the x value to be evaluated
 *  @param y   the y value to be evaluated
 */
Z evaluate( const X& x, const Y& y ) const {

  auto xIter = std::next( this->x().begin() );
  if ( x != *this->x().begin() ) {

    xIter = std::lower_bound( this->x().begin(), this->x().end(), x );
  }

  if ( this->x().end() == xIter ) {

    return Z( 0. );
  }
  else if ( this->x().begin() == xIter ) {

    return Z( 0. );
  }
  else {

    auto fIter = this->f().begin();
    std::advance( fIter, std::distance( this->x().begin(), xIter ) );

    return this->interpolator()( x, y, *std::prev( xIter ), *xIter,
                                       *std::prev( fIter ), *fIter );
  }
}
