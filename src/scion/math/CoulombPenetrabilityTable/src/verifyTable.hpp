void verifyTable( const XContainer& x, Y threshold = 0.0 ) {

  // check the x values are above the threshold

  auto iter = x.begin();
  if ( *iter < threshold ) {

    Log::error( "The x values cannot be less than the threshold value" );
    throw std::exception();
  }
  else {
    std::cout<< " -- threshold vals ok"<< "\n";
  }
}

