
template< typename Iter, typename Functor, typename Convergence, typename Split >
void operator()( Iter first, Iter last, Functor&& functor,
                 Convergence&& convergence, Split&& split ) {

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
                 std::forward< Split >( split ) );

    xLeft = xRight;
    yLeft = yRight;
  }

  if ( this->x_.get().size() ) {

    this->x_.get().push_back( xRight );
    this->y_.get().push_back( yRight );
  }
}
