void generateTables() {

  std::vector< TableVariant > tables;

  auto xStart = this->x().begin();
  auto yStart = this->y().begin();
  std::size_t nr = this->boundaries().size();
  bool linearised = true;
  for ( std::size_t i = 0; i < nr; ++i ) {

    auto xEnd = this->x().begin();
    auto yEnd = this->y().begin();
    std::advance( xEnd, this->boundaries()[i] + 1 );
    std::advance( yEnd, this->boundaries()[i] + 1 );

    switch ( this->interpolants()[i] ) {

      case interpolation::InterpolationType::LinearLinear : {

        tables.emplace_back(
          LinearLinearTable< X, Y, XContainer, YContainer >(
            XContainer( xStart, xEnd ),
            YContainer( yStart, yEnd ) ) );
        break;
      }
      case interpolation::InterpolationType::Histogram : {

        linearised = false;
        tables.emplace_back(
          HistogramTable< X, Y, XContainer, YContainer >(
            XContainer( xStart, xEnd ),
            YContainer( yStart, yEnd ) ) );
        break;
      }
      case interpolation::InterpolationType::LinearLog : {

        linearised = false;
        tables.emplace_back( LinearLogTable< X, Y, XContainer, YContainer >(
            XContainer( xStart, xEnd ),
            YContainer( yStart, yEnd ) ) );
        break;
      }
      case interpolation::InterpolationType::LogLinear : {

        linearised = false;
        tables.emplace_back( LogLinearTable< X, Y, XContainer, YContainer >(
            XContainer( xStart, xEnd ),
            YContainer( yStart, yEnd ) ) );
        break;
      }
      case interpolation::InterpolationType::LogLog : {

        linearised = false;
        tables.emplace_back( LogLogTable< X, Y, XContainer, YContainer >(
            XContainer( xStart, xEnd ),
            YContainer( yStart, yEnd ) ) );
        break;
      }
      default : {

        Log::error( "Unsupported interpolation type for InterpolationTable" );
        throw std::exception();
      }
    }

    // don't do this for the last region: valgrind will yell at you
    if ( xEnd != this->x().end() ) {

      // go back to the shared boundary if there is no jump or advance to the last
      // point in the jump if there is one

      std::swap( xStart, xEnd );
      std::swap( yStart, yEnd );
      if ( *xStart > *std::prev( xStart ) ) {

        --xStart;
        --yStart;
      }
      else {

        auto iter = std::prev( std::upper_bound( xStart, this->x().end(), *xStart ) );
        auto offset = std::distance( xStart, iter );
        std::advance( xStart, offset );
        std::advance( yStart, offset );
      }
    }
  }

  this->linearised_ = linearised;
  this->tables_ = std::move( tables );
}
