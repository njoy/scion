/**
 *  @brief Constructor
 *
 *  @param boundaries   the group boundaries (size n)
 *  @param values       the grouped values (size n-1)
 *
 */
GroupedTable( std::vector< X > boundaries,
              std::vector< Y > values ) :
    x_( std::move( boundaries ) ), y_( std::move( values ) ) {

  this->verifyTable();
}
