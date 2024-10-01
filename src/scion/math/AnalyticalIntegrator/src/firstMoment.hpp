template < typename Y,
           typename I = decltype( std::declval< X >() * std::declval< X >() * std::declval< Y >() ) >
std::vector< I > firstMoment( const InterpolationTable< X, Y >& table ) const {

  auto interpolator = interpolation::LinearLinear();
  auto integrator = integration::FirstMomentLinearLinear();

  return this->integrate( interpolator, integrator, table );
}
