/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
InterpolationTableFunction() = default;

/**
 *  @brief Copy constructor
 *
 *  @param[in] table    the table to be copied
 */
InterpolationTableFunction( const InterpolationTableFunction& table ) :
  x_( table.x_ ), f_( table.f_ ),
  boundaries_( table.boundaries_ ),
  interpolants_( table.interpolants_ ) {

  this->generateTables();
}

/**
 *  @brief Move constructor
 *
 *  @param[in] table    the table to be moved
 */
InterpolationTableFunction( InterpolationTableFunction&& table ) :
  x_( std::move( table.x_ ) ), f_( std::move( table.f_ ) ),
  boundaries_( std::move( table.boundaries_ ) ),
  interpolants_( std::move( table.interpolants_ ) ) {

  this->generateTables();
}

/**
 *  @brief Copy assignment using a table
 *
 *  @param[in] table    the table to be copied
 */
InterpolationTableFunction& operator=( const InterpolationTableFunction& base ) {

  if ( this != &base ) {

    Parent::operator=( base );
    this->x_ = base.x_;
    this->f_ = base.f_;
    this->boundaries_ = base.boundaries_;
    this->interpolants_ = base.interpolants_;
    this->generateTables();
  }
  return *this;
}

/**
 *  @brief Move assignment using a table
 *
 *  @param[in] table    the table to be moved
 */
InterpolationTableFunction& operator=( InterpolationTableFunction&& base ) {

  if ( this != &base ) {

    Parent::operator=( base );
    this->x_ = std::move( base.x_ );
    this->f_ = std::move( base.f_ );
    this->boundaries_ = std::move( base.boundaries_ );
    this->interpolants_ = std::move( base.interpolants_ );
    this->generateTables();
  }
  return *this;
}

private:

/**
 *  @brief Private constructor
 */
InterpolationTableFunction(
    std::tuple< std::vector< X >,
                std::vector< F >,
                std::vector< std::size_t >,
                std::vector< interpolation::InterpolationType > >&& data ) :
  x_( std::move( std::get< 0 >( data ) ) ), f_( std::move( std::get< 1 >( data ) ) ),
  boundaries_( std::move( std::get< 2 >( data ) ) ),
  interpolants_( std::move( std::get< 3 >( data ) ) ) {

  this->generateTables();
}

public:

/**
 *  @brief Constructor
 *
 *  @param x              the x values of the tabulated data
 *  @param f              the f(y) functions of the tabulated data
 *  @param boundaries     the boundaries of the interpolation regions
 *  @param interpolants   the interpolation types of the interpolation regions
 */
InterpolationTableFunction( std::vector< X > x, std::vector< F > f,
                            std::vector< std::size_t > boundaries,
                            std::vector< interpolation::InterpolationType > interpolants ) :
  InterpolationTableFunction( processBoundaries( std::move( x ), std::move( f ),
                                                 std::move( boundaries ),
                                                 std::move( interpolants ) ) ) {}

/**
 *  @brief Constructor for tabulated data in a single interpolation zone
 *
 *  @param x              the x values of the tabulated data
 *  @param f              the f(y) functions of the tabulated data
 *  @param interpolant    the interpolation type of the data (default lin-lin)
 */
InterpolationTableFunction( std::vector< X > x, std::vector< F > f,
                            interpolation::InterpolationType interpolant =
                                interpolation::InterpolationType::LinearLinear ) :
  InterpolationTableFunction( processBoundaries( std::move( x ), std::move( f ), interpolant ) ) {}
