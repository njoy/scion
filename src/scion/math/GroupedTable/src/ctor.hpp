/**
 * @brief Constructor
 *
 * @param bounds   the boundary values (size n)
 * @param values   vector of values  (size n-1)
 *
 */
GroupedTable( std::vector< X > bounds, 
              std::vector< Y > values ) :
  x_( std::move( bounds ) ), y_( std::move( values ) ) {

    this->verifyTable();
   }
