void generateTables() {

  std::vector< TableVariant > tables;

  auto xStart = this->x().begin();
  auto fStart = this->f().begin();
  std::size_t nr = this->boundaries().size();
  bool linearised = true;
  for ( std::size_t i = 0; i < nr; ++i ) {

    auto xEnd = this->x().begin();
    auto fEnd = this->f().begin();
    std::advance( xEnd, this->boundaries()[i] + 1 );
    std::advance( fEnd, this->boundaries()[i] + 1 );

    switch ( this->interpolants()[i] ) {

      case interpolation::InterpolationType::LinearLinear : {

        tables.emplace_back(
          LinearLinearTableFunction< X, Y, Z, F, XContainer, FContainer >(
            XContainer( xStart, xEnd ),
            FContainer( fStart, fEnd ) ) );
        break;
      }
      case interpolation::InterpolationType::Histogram : {

        linearised = false;
        tables.emplace_back(
          HistogramTableFunction< X, Y, Z, F, XContainer, FContainer >(
            XContainer( xStart, xEnd ),
            FContainer( fStart, fEnd ) ) );
        break;
      }
      case interpolation::InterpolationType::LinearLog : {

        linearised = false;
        tables.emplace_back(
          LinearLogTableFunction< X, Y, Z, F, XContainer, FContainer >(
            XContainer( xStart, xEnd ),
            FContainer( fStart, fEnd ) ) );
        break;
      }
      case interpolation::InterpolationType::LogLinear : {

        linearised = false;
        tables.emplace_back(
          LogLinearTableFunction< X, Y, Z, F, XContainer, FContainer >(
            XContainer( xStart, xEnd ),
            FContainer( fStart, fEnd ) ) );
        break;
      }
      case interpolation::InterpolationType::LogLog : {

        linearised = false;
        tables.emplace_back(
          LogLogTableFunction< X, Y, Z, F, XContainer, FContainer >(
            XContainer( xStart, xEnd ),
            FContainer( fStart, fEnd ) ) );
        break;
      }
      default : {

        Log::error( "Unsupported interpolation type for InterpolationTable" );
        throw std::exception();
      }
    }

    std::swap( xStart, xEnd );
    std::swap( fStart, fEnd );
    if ( *xStart > *std::prev( xStart ) ) {

      --xStart;
      --fStart;
    }
  }

  this->tables_ = tables;
}