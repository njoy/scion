LinearLinearTableFunction( const LinearLinearTableFunction& ) = default;
LinearLinearTableFunction( LinearLinearTableFunction&& ) = default;

LinearLinearTableFunction& operator=( const LinearLinearTableFunction& ) = default;
LinearLinearTableFunction& operator=( LinearLinearTableFunction&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param x   the x values of the tabulated data
 *  @param f   the f(y) functions of the tabulated data
 */
LinearLinearTableFunction( XContainer x, FContainer f ) :
  Parent( std::move( x ), std::move( f ) ) {}
