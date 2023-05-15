/**
 *  @brief Transform x in [a, b] to xprime in [-1, 1]
 *
 *  @param[in] x    the value of x to transform into xprime
 */
X transform( const X& x ) const {

  return ( 2. * x - ( this->upper_ + this->lower_ ) )
         / ( this->upper_ - this->lower_ );
}

/**
 *  @brief Transform xprime in [-1, 1] to x in [a, b]
 *
 *  @param[in] xprime    the value of xprime to transform into x
 */
X invert( const X& xprime ) const {

  return ( xprime + X( 1 ) ) * ( this->upper_ - this->lower_ ) / X( 2 ) + this->lower_;
}
