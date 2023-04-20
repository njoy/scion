/**
 *  @brief Constructor
 *
 *  @param x   a reference to the container where the x values are to be stored
 *  @param y   a reference to the container where the y values are to be stored
 */
Lineariser( XContainer& x, YContainer& y ) :
  x_( x ), y_( y ), xbuffer_(), ybuffer_() {}
