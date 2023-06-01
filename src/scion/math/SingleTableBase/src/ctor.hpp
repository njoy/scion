private:

/**
 *  @brief Private intermediate constructor
 */
SingleTableBase( Table&& table ) :
  Parent( IntervalDomain( table.x().front(), table.x().back() ) ),
  table_( std::move( table ) ) {

  verifyTable( this->table_.x(), this->table_.y() );
}

protected:

/**
 *  @brief Constructor
 *
 *  @param x   the x values of the tabulated data
 *  @param y   the y values of the tabulated data
 */
SingleTableBase( XContainer x, YContainer y ) :
  SingleTableBase( Table( std::move( x ), std::move( y ) ) ) {}
