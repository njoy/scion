
template< typename Iter, typename Functor, typename Convergence, typename Midpoint >
void operator()( Iter first, Iter last, Functor&& functor,
                 Convergence&& convergence, Midpoint&& midpoint ) {

  X xLeft = *first;
  Y yLeft = functor( xLeft );
  ++first;

  X xRight = xLeft;
  Y yRight = yLeft;

  while ( first != last ) {

    xRight = *first;
    yRight = functor( xRight );
    ++first;

    this->panel( xLeft, xRight, yLeft, yRight,
                 std::forward< Functor >( functor ),
                 std::forward< Convergence >( convergence ),
                 std::forward< Midpoint >( midpoint ) );

    xLeft = xRight;
    yLeft = yRight;
  }

  if ( this->x_.get().size() ) {

    this->x_.get().push_back( xRight );
    this->y_.get().push_back( yRight );
  }
}
