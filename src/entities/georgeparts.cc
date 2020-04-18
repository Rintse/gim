#include "entities/georgeparts.h"


GeorgeA::GeorgeA() {}

GeorgeA::GeorgeA(Level* l, Square* s) : GeorgeNoGun (l,s) {}

char GeorgeA::token() {
  return 'A';
}

//#############################################################################

GeorgeB::GeorgeB() {}

GeorgeB::GeorgeB(Level* l, Square* s) : GeorgeNoGun (l,s) {}

char GeorgeB::token() {
  return 'B';
}

//#############################################################################

GeorgeC::GeorgeC() {}

GeorgeC::GeorgeC(Level* l, Square* s) : GeorgeNoGun (l,s) {}

char GeorgeC::token() {
  return 'C';
}

//#############################################################################

GeorgeD::GeorgeD() {}

GeorgeD::GeorgeD(Level* l, Square* s) : GeorgeGun (l,s) {}

char GeorgeD::token() {
  return 'D';
}

//#############################################################################

GeorgeE::GeorgeE() {}

GeorgeE::GeorgeE(Level* l, Square* s) : GeorgeNoGun (l,s) {}

char GeorgeE::token() {
  return 'E';
}

//#############################################################################

GeorgeF::GeorgeF() {}

GeorgeF::GeorgeF(Level* l, Square* s) : GeorgeGun (l,s) {}

char GeorgeF::token() {
  return 'F';
}
