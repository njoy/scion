template < typename Y,
           typename I = decltype( std::declval< X >() * std::declval< X >() * std::declval< Y >() ) >
std::vector< I > mean( const InterpolationTable< X, Y >& table ) const {

  auto interpolator = interpolation::LinearLinear();
  auto integrator = integration::LinearLinearMean();

  return this->integrate( interpolator, integrator, table );
}
