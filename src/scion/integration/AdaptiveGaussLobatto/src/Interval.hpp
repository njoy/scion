/**
 *  @class
 *  @brief A class containing the data for an interval upon which adaptive
 *         quadrature is applied
 */
class Interval {

  /* type aliases */
  using I = decltype( std::declval< X >() * std::declval< Y >() );

  /* fields */

  // x and y values
  std::array< X, 7 > x_;
  std::array< Y, 7 > y_;

  // integral estimates
  I gauss_lobatto_;
  I kronrod_7_;
  std::optional< I > kronrod_13_;

  /* points and weights */
  static constexpr const std::array< std::array< X, 4 >, 7 > tuples = {

    std::array< X, 4 >{  0.000000000000000e+0, 0.000000000000000e+0, 4.571428571428571e-1, 2.426110719014077e-1 }, // x = 0          , w_l = 0  , w_k = 16/35
    std::array< X, 4 >{  2.363831996621499e-1, 0.000000000000000e+0, 0.000000000000000e+0, 2.249264653333395e-1 }, // x =            , w_l = 0  , w_k = 0
    std::array< X, 4 >{  4.472135954999579e-1, 8.333333333333334e-1, 4.251700680272109e-1, 1.997734052268585e-1 }, // x = 1/sqrt(5)  , w_l = 5/6, w_k = 125/294
    std::array< X, 4 >{  6.418533423457813e-1, 0.000000000000000e+0, 0.000000000000000e+0, 1.888215739601825e-1 }, // x =            , w_l = 0  , w_k = 0
    std::array< X, 4 >{  8.164965809277260e-1, 0.000000000000000e+0, 2.938775510204082e-1, 1.550719873365854e-1 }, // x = 1/sqrt(2/3), w_l = 0  , w_k = 72/245
    std::array< X, 4 >{  9.428824156954797e-1, 0.000000000000000e+0, 0.000000000000000e+0, 9.427384021885005e-2 }, // x =            , w_l = 0  , w_k = 0
    std::array< X, 4 >{  1.000000000000000e+0, 1.666666666666667e-1, 5.238095238095238e-2, 1.582719197348018e-2 }  // x = 1          , w_l = 1/6, w_k = 11/210
  };

public:

  /* methods */

  /**
   *  @brief Constructor
   *
   *  The constructor initialises the x values used in subdividing the
   *  interval and the associated function values, as well as calculate
   *  the Gauss-Lobatto and Kronrod estimates of the integrals.
   */
  template < typename Functor >
  Interval( Functor&& functor,
            const X& a, const X& b, const Y& fa, const Y& fb,
            bool calculate_kronrod13 = false ) {

    auto half =  ( b - a ) / X( 2 );
    const auto transform = [&] ( auto&& x ) {

      return ( x + X( 1 ) ) * half + a;
    };

    // initialise the x values
    this->x()[0] = a;
    this->x()[1] = transform( -tuples[4][0] );
    this->x()[2] = transform( -tuples[2][0] );
    this->x()[3] = transform(  tuples[0][0] );
    this->x()[4] = transform(  tuples[2][0] );
    this->x()[5] = transform(  tuples[4][0] );
    this->x()[6] = b;

    // initialise the function values
    this->y()[0] = fa;
    this->y()[1] = functor( this->x()[1] );
    this->y()[2] = functor( this->x()[2] );
    this->y()[3] = functor( this->x()[3] );
    this->y()[4] = functor( this->x()[4] );
    this->y()[5] = functor( this->x()[5] );
    this->y()[6] = fb;

    // calculate the integrals
    this->gaussLobattoIntegral() =
        half * ( tuples[2][1] * ( this->y()[2] + this->y()[4] )
               + tuples[6][1] * ( this->y()[0] + this->y()[6] ) );
    this->kronrod7Integral() =
        half * ( tuples[0][2] * this->y()[3]
               + tuples[2][2] * ( this->y()[2] + this->y()[4] )
               + tuples[4][2] * ( this->y()[1] + this->y()[5] )
               + tuples[6][2] * ( this->y()[0] + this->y()[6] ) );

    // calculate the optional integral
    if ( calculate_kronrod13 ) {

      this->kronrod13Integral() =
          half * ( tuples[0][3] * this->y()[3]
                 + tuples[1][3] * ( functor( transform( -tuples[1][0] ) ) + functor( transform( tuples[1][0] ) ) )
                 + tuples[2][3] * ( this->y()[2] + this->y()[4] )
                 + tuples[3][3] * ( functor( transform( -tuples[3][0] ) ) + functor( transform( tuples[3][0] ) ) )
                 + tuples[4][3] * ( this->y()[1] + this->y()[5] )
                 + tuples[5][3] * ( functor( transform( -tuples[5][0] ) ) + functor( transform( tuples[5][0] ) ) )
                 + tuples[6][3] * ( this->y()[0] + this->y()[6] ) );
    }
  }

  /**
   *  @brief Return the x values
   */
  const std::array< X, 7 >& x() const {

    return this->x_;
  }

  /**
   *  @brief Return the x values
   */
  std::array< X, 7 >& x() {

    return this->x_;
  }

  /**
   *  @brief Return the y values
   */
  const std::array< Y, 7 >& y() const {

    return this->y_;
  }

  /**
   *  @brief Return the x values
   */
  std::array< Y, 7 >& y() {

    return this->y_;
  }

  /**
   *  @brief Return the Gauss-Lobatto estimate of the integral
   */
  const I& gaussLobattoIntegral() const {

    return this->gauss_lobatto_;
  };

  /**
   *  @brief Return the Gauss-Lobatto estimate of the integral
   */
  I& gaussLobattoIntegral() {

    return this->gauss_lobatto_;
  };

  /**
   *  @brief Return the 7-point Kronrod estimate of the integral
   */
  const I& kronrod7Integral() const {

    return this->kronrod_7_;
  };

  /**
   *  @brief Return the 7-point Kronrod estimate of the integral
   */
  I& kronrod7Integral() {

    return this->kronrod_7_;
  };

  /**
   *  @brief Return the 13-point Kronrod estimate of the integral (if defined)
   */
  const std::optional< I >& kronrod13Integral() const {

    return this->kronrod_13_;
  };

  /**
   *  @brief Return the 13-point Kronrod estimate of the integral (if defined)
   */
  std::optional< I >& kronrod13Integral() {

    return this->kronrod_13_;
  };

  /**
   *  @brief Calculate an absolute tolerance
   *
   *  @param[in] tolerance   the relative tolerance
   */
  I absoluteTolerance( double tolerance ) const {

    I error1 = this->gaussLobattoIntegral() - this->kronrod13Integral().value();
    I error2 = this->kronrod7Integral() - this->kronrod13Integral().value();
    double ratio = error2 != 0. ? error1 / error2 : 1.;
    if ( ratio > 0 && ratio < 1 ) {

      tolerance /= ratio;
    }
    return tolerance * ( this->kronrod13Integral().value() == 0.
                         ? this->x()[6] - this->x()[0]
                         : std::abs( this->kronrod13Integral().value() ) );
  };

  /**
   *  @brief Calculate the difference in integral estimates
   */
  I difference() const {

    return std::abs( this->gaussLobattoIntegral() - this->kronrod7Integral() );
  };

  /**
   *  @brief Check whether or not the interval can be subdivided (depends on machine
   *         precision)
   */
  bool cannotSubdivide() const {

    return this->x()[1] <= this->x()[0] || this->x()[6] <= this->x()[5];
  }

  /**
   *  @brief Create subdivided intervals
   */
  template < typename Functor >
  std::vector< Interval > subdivide( Functor&& functor ) const {

    return { Interval( functor, this->x()[0], this->x()[1], this->y()[0], this->y()[1] ),
             Interval( functor, this->x()[1], this->x()[2], this->y()[1], this->y()[2] ),
             Interval( functor, this->x()[2], this->x()[3], this->y()[2], this->y()[3] ),
             Interval( functor, this->x()[3], this->x()[4], this->y()[3], this->y()[4] ),
             Interval( functor, this->x()[4], this->x()[5], this->y()[4], this->y()[5] ),
             Interval( functor, this->x()[5], this->x()[6], this->y()[5], this->y()[6] ), };
  }
};
