private:

/**
 *  @brief Private intermediate constructor
 */
HistogramTable( Table&& table ) :
  Parent( IntervalDomain( table.x().front(), table.x().back() ) ),
  table_( std::move( table ) ) {

  verifyTable( this->table_.x(), this->table_.y() );    
}


public:

/**
 *  @brief Constructor
 *
 *  @param x   the x values of the tabulated data
 *  @param y   the y values of the tabulated data
 */
HistogramTable( XContainer x, YContainer y ) :
  HistogramTable( Table( std::move( x ), std::move( y ) ) ) {}
