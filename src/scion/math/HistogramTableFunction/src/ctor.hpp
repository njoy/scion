HistogramTableFunction( const HistogramTableFunction& ) = default;
HistogramTableFunction( HistogramTableFunction&& ) = default;

HistogramTableFunction& operator=( const HistogramTableFunction& ) = default;
HistogramTableFunction& operator=( HistogramTableFunction&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param x   the x values of the tabulated data
 *  @param f   the f(y) functions of the tabulated data
 */
HistogramTableFunction( XContainer x, FContainer f ) :
  Parent( std::move( x ), std::move( f ) ) {}
