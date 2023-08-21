void generateTables() {

  std::vector< TableVariant > tables;

  auto xStart = this->x().begin();
  auto yStart = this->y().begin();
  auto xEnd = xStart;
  auto yEnd = yStart;
  std::size_t nr = this->boundaries().size();
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
      case interpolation::InterpolationType::LinearLog : {

        tables.emplace_back( LinearLogTable< X, Y, XContainer, YContainer >(
            XContainer( xStart, xEnd ),
            YContainer( yStart, yEnd ) ) );
        break;
      }
      case interpolation::InterpolationType::LogLinear : {

        tables.emplace_back( LogLinearTable< X, Y, XContainer, YContainer >(
            XContainer( xStart, xEnd ),
            YContainer( yStart, yEnd ) ) );
        break;
      }
      case interpolation::InterpolationType::LogLog : {

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

    std::swap( xStart, xEnd );
    std::swap( yStart, yEnd );
    if ( *xStart > *std::prev( xStart ) ) {

      --xStart;
      --yStart;
    }
  }

  this->tables_ = tables;
}
