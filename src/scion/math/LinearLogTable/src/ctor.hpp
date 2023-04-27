private:

/**
 *  @brief Private intermediate constructor
 */
LinearLogTable( Table&& table ) :
  Parent( IntervalDomain( table.x().front(), table.x().back() ) ),
  table_( std::move( table ) ) {}


public:

/**
 *  @brief Constructor
 *
 *  @param x   the x values of the tabulated data
 *  @param y   the y values of the tabulated data
 */
LinearLogTable( std::vector< X > x, std::vector< Y > y ) :
  LinearLogTable( Table( std::move( x ), std::move( y ) ) ) {}
