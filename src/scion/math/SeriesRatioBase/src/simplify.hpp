void simplify() {

  // set the denominator to 1 for a zero order denominator
  if ( this->denominator().order() == 0 &&
       this->denominator().coefficients().front() != Y( 1. ) ) {

    this->numerator_ /= this->denominator_.coefficients()[0];
    this->denominator_ = Y( 1. );
  }
}
