
template< typename Functor, typename Convergence, typename Split >
void panel( X xLeft, X xRight, Y yLeft, Y yRight,
        	  Functor&& functor, Convergence&& criterion, Split&& split ) {

  while ( true ) {

    const X point = split( xLeft, xRight, yLeft, yRight );
    const Y trial = 0.5 * ( yLeft + yRight );
    const Y reference = functor( point );

    if ( criterion( trial, reference, xLeft, xRight, yLeft, yRight ) ) {

      this->x_.get().push_back( xLeft );
      this->y_.get().push_back( yLeft );
      if ( ! this->xbuffer_.size() ) {

        break;
      }

      std::swap( xLeft, xRight );
      std::swap( yLeft, yRight );
      xRight = this->xbuffer_.back();
      yRight = this->ybuffer_.back();
      this->xbuffer_.pop_back();
      this->ybuffer_.pop_back();
    }
    else {

      this->xbuffer_.push_back( xRight );
      this->ybuffer_.push_back( yRight );
      xRight = point;
      yRight = reference;
    }
  }
}
