/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
AnalyticalIntegrator() = default;

/**
 *  @brief Constructor
 *
 *  @param boundaries   the integration boundaries
 */
AnalyticalIntegrator( std::vector< X > boundaries ) :
  boundaries_( std::move( boundaries ) ) {

  verifyBoundaries( this->boundaries() );
}

/**
 *  @brief Constructor
 *
 *  @param a   the lower limit of the integration interval
 *  @param b   the upper limit of the integration interval
 */
AnalyticalIntegrator( X a, X b ) :
  AnalyticalIntegrator( std::vector< X >{ std::move( a ), std::move( b ) } ) {}
