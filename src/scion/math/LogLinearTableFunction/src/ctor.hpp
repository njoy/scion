LogLinearTableFunction( const LogLinearTableFunction& ) = default;
LogLinearTableFunction( LogLinearTableFunction&& ) = default;

LogLinearTableFunction& operator=( const LogLinearTableFunction& ) = default;
LogLinearTableFunction& operator=( LogLinearTableFunction&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param x   the x values of the tabulated data
 *  @param f   the f(y) functions of the tabulated data
 */
LogLinearTableFunction( XContainer x, FContainer f ) :
  Parent( std::move( x ), std::move( f ) ) {}
