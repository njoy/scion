/**
 *  @brief Integrate the function over the domain
 */
template < typename I = decltype( std::declval< X >() * std::declval< Y >() ) >
I integrate() const {

  auto xIter = std::next( this->x().begin() );
  auto yIter = std::next( this->y().begin() );
  return integration::integrate( xIter, this->x().end(), yIter,
                                 static_cast< const Derived* >( this )->integrator() );
}
