/**
 *  @brief Constructor
 *
 *  @param x   the x values of the tabulated data
 *  @param y   the y values of the tabulated data
 */
Table( XContainer x, YContainer y ) :
  interpolator_(), x_( std::move( x ) ), y_( std::move( y ) ) {

  verifyTable( this->x(), this->y() );
}
