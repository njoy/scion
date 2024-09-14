LogLogTable( const LogLogTable& ) = default;
LogLogTable( LogLogTable&& ) = default;

LogLogTable& operator=( const LogLogTable& ) = default;
LogLogTable& operator=( LogLogTable&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param x   the x values of the tabulated data
 *  @param y   the y values of the tabulated data
 */
LogLogTable( XContainer x, YContainer y ) :
  Parent( std::move( x ), std::move( y ) ) {}
