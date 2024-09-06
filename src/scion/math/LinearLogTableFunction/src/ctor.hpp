/**
 *  @brief Constructor
 *
 *  @param x   the x values of the tabulated data
 *  @param f   the f(y) functions of the tabulated data
 */
LinearLogTableFunction( XContainer x, FContainer f ) :
  Parent( std::move( x ), std::move( f ) ) {}
