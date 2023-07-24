/**
 *  @brief Linearise a function
 *
 *  @param[in] first         the iterator to the beginning of the initial grid
 *  @param[in] last          the iterator to the end of the initial grid
 *  @param[in] functor       the function to linearise
 *  @param[in] convergence   the convergence criterion functor
 *  @param[in] split         the panel splitting functor
 */
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

/**
 *  @brief Linearise a function
 *
 *  @param[in] grid          the initial grid
 *  @param[in] functor       the function to linearise
 *  @param[in] convergence   the convergence criterion functor
 *  @param[in] split         the panel splitting functor
 */
template< typename Range, typename Functor, typename Convergence, typename Split >
void operator()( const Range& grid, Functor&& functor,
                 Convergence&& convergence, Split&& split ) {

  ( *this )( grid.begin(), grid.end(),
             std::forward< Functor >( functor ),
             std::forward< Convergence >( convergence ),
             std::forward< Split >( split ) );
}
