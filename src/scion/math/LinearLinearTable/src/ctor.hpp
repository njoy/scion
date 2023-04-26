private:

/**
 *  @brief Private intermediate constructor
 */
LinearLinearTable( IntervalDomain< X >&& domain,
                   std::vector< X >&& x, std::vector< Y >&& y ) :
  Parent( std::move( domain ) ),
  table_( std::move( x ), std::move( y ) ) {}


public:

/**
 *  @brief Constructor
 *
 *  @param x   the x values of the tabulated data
 *  @param y   the y values of the tabulated data
 */
LinearLinearTable( std::vector< X > x, std::vector< Y > y ) :
  LinearLinearTable( IntervalDomain( x.front(), x.back() ),
                     std::move( x ), std::move( y ) ) {}
