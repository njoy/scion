/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
Unioniser() = default;

/**
 *  @brief Constructor
 *
 *  @param grids   references to the grids to be unionised
 */
Unioniser( std::vector< std::pair< XIter, XIter > > grids ) :
  grids_( std::move( grids ) ) {

  this->sort();
}

/**
 *  @brief Constructor
 *
 *  @param first    the first grid (assumed to be sorted)
 *  @param second   the second grid (assumed to be sorted)
 */
Unioniser( const XContainer& first, const XContainer& second ) :
  Unioniser( { std::make_pair( first.begin(), first.end() ),
               std::make_pair( second.begin(), second.end() ) } ) {}
