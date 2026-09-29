/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
InterpolationTable() = default;

/**
 *  @brief Copy constructor
 *
 *  @param[in] table    the table to be copied
 */
InterpolationTable( const InterpolationTable& table ) :
  Parent( IntervalDomain( table.x_.front(), table.x_.back() ) ),
  x_( table.x_ ),
  y_( table.y_ ),
  boundaries_( table.boundaries_ ),
  interpolants_( table.interpolants_ ),
  linearised_( table.linearised_ ),
  curated_( table.curated_ ) {

  this->generateTables();
}

/**
 *  @brief Move constructor
 *
 *  @param[in] table    the table to be moved
 */
InterpolationTable( InterpolationTable&& table ) :
  Parent( IntervalDomain( table.x_.front(), table.x_.back() ) ),
  x_( std::move( table.x_ ) ),
  y_( std::move( table.y_ ) ),
  boundaries_( std::move( table.boundaries_ ) ),
  interpolants_( std::move( table.interpolants_ ) ),
  linearised_( table.linearised_ ),
  curated_( table.curated_ ) {

  this->generateTables();
}

/**
 *  @brief Copy assignment using a continuous energy table
 *
 *  @param[in] table    the continuous energy table to be copied
 */
InterpolationTable& operator=( const InterpolationTable& base ) {

  if ( this != &base ) {

    Parent::operator=( base );
    this->x_ = base.x_;
    this->y_ = base.y_;
    this->boundaries_ = base.boundaries_;
    this->interpolants_ = base.interpolants_;
    this->linearised_ = base.linearised_;
    this->curated_ = base.curated_;
    this->generateTables();
  }
  return *this;
}

/**
 *  @brief Move assignment using a continuous energy table
 *
 *  @param[in] table    the continuous energy table to be moved
 */
InterpolationTable& operator=( InterpolationTable&& base ) {

  if ( this != &base ) {

    Parent::operator=( std::move( base ) );
    this->x_ = std::move( base.x_ );
    this->y_ = std::move( base.y_ );
    this->boundaries_ = std::move( base.boundaries_ );
    this->interpolants_ = std::move( base.interpolants_ );
    this->linearised_ = base.linearised_;
    this->curated_ = base.curated_;
    this->generateTables();
  }
  return *this;
}

private:

/**
 *  @brief Constructor
 *
 *  @param data   the processed tabulated data
 */
InterpolationTable( ProcessedData< X, Y >&& data ) :
  Parent( IntervalDomain( data.x.front(), data.x.back() ) ),
  x_( std::move( data.x ) ),
  y_( std::move( data.y ) ),
  boundaries_( std::move( data.boundaries ) ),
  interpolants_( std::move( data.interpolants ) ),
  linearised_( data.linearised ),
  curated_( data.curated ) {

  this->generateTables();
}

public:

/**
 *  @brief Constructor
 *
 *  @param x              the x values of the tabulated data
 *  @param y              the y values of the tabulated data
 *  @param boundaries     the boundaries of the interpolation regions
 *  @param interpolants   the interpolation types of the interpolation regions
 *  @param curate         flag to indicate whether or not to curate the table (default: false)
 */
InterpolationTable( std::vector< X > x, std::vector< Y > y,
                    std::vector< std::size_t > boundaries,
                    std::vector< interpolation::InterpolationType > interpolants,
                    bool curate = false ) :
  InterpolationTable( processData( std::move( x ), std::move( y ),
                                         std::move( boundaries ),
                                         std::move( interpolants ), curate ) ) {}

/**
 *  @brief Constructor for tabulated data in a single interpolation zone
 *
 *  @param x              the x values of the tabulated data
 *  @param y              the y values of the tabulated data
 *  @param interpolant    the interpolation type of the data (default lin-lin)
 *  @param curate         flag to indicate whether or not to curate the table (default: false)
 */
InterpolationTable( std::vector< X > x, std::vector< Y > y,
                    interpolation::InterpolationType interpolant =
                        interpolation::InterpolationType::LinearLinear,
                    bool curate = false ) :
  InterpolationTable( processData( std::move( x ), std::move( y ), interpolant, curate ) ) {}
