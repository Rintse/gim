#include "entities/george/georgeparts.h"
#include <iostream>


GeorgeA::GeorgeA() {}

GeorgeA::GeorgeA(Level* l, EmptySquare* s) : GeorgeNoGun (l,s) {}

char GeorgeA::token() {
  return 'A';
}

//#############################################################################

GeorgeB::GeorgeB() {}

GeorgeB::GeorgeB(Level* l, EmptySquare* s) : GeorgeNoGun (l,s) {}

char GeorgeB::token() {
  return 'B';
}

//#############################################################################

GeorgeC::GeorgeC() {}

GeorgeC::GeorgeC(Level* l, EmptySquare* s) : GeorgeNoGun (l,s) {}

char GeorgeC::token() {
  return 'C';
}

//#############################################################################

GeorgeD::GeorgeD() {}

GeorgeD::GeorgeD(Level* l, EmptySquare* s) : GeorgeGun (l,s) {}

char GeorgeD::token() {
  return 'D';
}

//#############################################################################

GeorgeE::GeorgeE() {}

GeorgeE::GeorgeE(Level* l, EmptySquare* s) : GeorgeNoGun (l,s) {}

char GeorgeE::token() {
  return 'E';
}

//#############################################################################

GeorgeF::GeorgeF() {}

GeorgeF::GeorgeF(Level* l, EmptySquare* s) : GeorgeGun (l,s) {}

char GeorgeF::token() {
  return 'F';
}
