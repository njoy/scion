HistogramTable( const HistogramTable& ) = default;
HistogramTable( HistogramTable&& ) = default;

HistogramTable& operator=( const HistogramTable& ) = default;
HistogramTable& operator=( HistogramTable&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param x   the x values of the tabulated data
 *  @param y   the y values of the tabulated data
 */
HistogramTable( XContainer x, YContainer y ) :
  Parent( std::move( x ), std::move( y ) ) {}
