#include "winged-face.hpp"
#include "winged-edge.hpp"

WingedFace :: WingedFace (LinkedEdge* e, Depth d) : _depth (d) {
  this->_edge = e;
}

void WingedFace :: setEdge (LinkedEdge* e) {
  this->_edge = e;
}

void WingedFace :: addIndices (WingedMesh& mesh) {
  WingedEdge& e1 = this->_edge->data ();
  WingedEdge& e2 = e1.successor (*this)->data ();
  
  e1.firstVertex  (*this)->data ().addIndex (mesh);
  e1.secondVertex (*this)->data ().addIndex (mesh);
  e2.secondVertex (*this)->data ().addIndex (mesh);
}

Triangle WingedFace :: triangle (const WingedMesh& mesh) const {
  WingedEdge& e1 = this->_edge->data ();
  WingedEdge& e2 = e1.successor (*this)->data ();
  
  return Triangle ( e1.firstVertex  (*this)->data ().vertex (mesh)
                  , e1.secondVertex (*this)->data ().vertex (mesh)
                  , e2.secondVertex (*this)->data ().vertex (mesh)
      );
}

LinkedEdge& WingedFace :: longestEdge (const WingedMesh& mesh) {
  LinkedEdge& e1 = *this->_edge->data ().successor (*this,0);
  LinkedEdge& e2 = *this->_edge->data ().successor (*this,1);
  LinkedEdge& e3 = *this->_edge->data ().successor (*this,2);

  float e1Length = e1.data ().lengthSqr (mesh);
  float e2Length = e2.data ().lengthSqr (mesh);
  float e3Length = e3.data ().lengthSqr (mesh);

  if (e1Length >= e2Length && e1Length >= e3Length)
    return e1;
  else if (e2Length >= e3Length)
    return e2;
  else
    return e3;
}

void WingedFace :: increaseDepth () { this->_depth.increase (); }
void WingedFace :: decreaseDepth () { this->_depth.decrease (); }
