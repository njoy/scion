/**
 *  @brief Constructor
 *
 *  @param x   the x values of the tabulated data
 *  @param f   the f(y) functions of the tabulated data
 */
SingleTableFunctionBase( XContainer x, FContainer f ) :
  interpolator_(), x_( std::move( x ) ), f_( std::move( f ) ) {

  verifyTable( this->x(), this->f() );
}
