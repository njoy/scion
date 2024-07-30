private:

/**
 *  @brief Private constructor
 */
SingleTableBase( IntervalDomain< X >&& domain, XContainer&& x, YContainer&& y ) :
  Parent( std::move( domain ) ), interpolator_(), 
  x_( std::move( x ) ), y_( std::move( y ) ) {}

protected:

/**
 *  @brief Constructor
 *
 *  @param x   the x values of the tabulated data
 *  @param y   the y values of the tabulated data
 */
SingleTableBase( XContainer x, YContainer y ) :
  SingleTableBase( verifyTableAndRetrieveDomain( x, y ),
                   std::move( x ), std::move( y ) ) {}

