template < typename Y,
           typename I = decltype( std::declval< X >() * std::declval< Y >() ) >
std::vector< I > operator()( const InterpolationTable< X, Y >& table ) const {

  auto interpolator = interpolation::LinearLinear();
  auto integrator = integration::LinearLinear();

  return this->integrate( interpolator, integrator, table );
}
