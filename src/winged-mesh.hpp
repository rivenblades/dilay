#ifndef DILAY_WINGED_MESH
#define DILAY_WINGED_MESH

#include <list>
#include "fwd-glm.hpp"

class FaceIntersection;
class Ray;
class Triangle;
class Octree;
class OctreeFaceIterator;
class ConstOctreeFaceIterator;
class OctreeNodeIterator;
class ConstOctreeNodeIterator;
class WingedVertex;
class WingedFace;
class WingedEdge;
class Id;

class WingedMesh {
  public: WingedMesh                  ();
          WingedMesh                  (const WingedMesh&);
    const WingedMesh& operator=       (const WingedMesh&);
         ~WingedMesh                  ();

    void              addIndex        (unsigned int);
    WingedVertex&     addVertex       (const glm::vec3&, unsigned int = 0);
    WingedEdge&       addEdge         (const WingedEdge&);
    WingedFace&       addFace         (const WingedFace&, const Triangle&);

    const std::list <WingedVertex>&   vertices () const;
    const std::list <WingedEdge>&     edges    () const;
    const Octree&                     octree   () const;

    OctreeFaceIterator      octreeFaceIterator ();
    ConstOctreeFaceIterator octreeFaceIterator () const;
    OctreeNodeIterator      octreeNodeIterator ();
    ConstOctreeNodeIterator octreeNodeIterator () const;

    /** Deletes an edge and its _right_ face. Note that other parts of the program
     * depend on this behaviour. */
    WingedFace&     deleteEdge        (WingedEdge&);

    /** Realigns a face in a mesh's octree. The passed face becomes invalid
     * and must not be used: use the returned face instead. */
    WingedFace&     realignInOctree   (WingedFace&);

    unsigned int    numVertices       () const;
    unsigned int    numWingedVertices () const;
    unsigned int    numEdges          () const;
    unsigned int    numFaces          () const;

    glm::vec3       vertex            (unsigned int) const;

    void            rebuildIndices    ();
    void            rebuildNormals    ();
    void            bufferData        ();
    void            render            ();
    void            reset             ();
    void            reset             (const glm::vec3&, float);
    void            toggleRenderMode  ();
    
    void            intersectRay      (const Ray&, FaceIntersection&);
  private:
    class Impl;
    Impl* impl;
};

#endif
