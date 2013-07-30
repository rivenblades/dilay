#ifndef DILAY_ID
#define DILAY_ID

#include <iosfwd>

typedef unsigned int IdPrimitive;

class Id {
  public: Id (const Id& id) : _id (id .get ()) {}
          Id ()             : _id (0)          {}

    friend class IdObject;

    bool operator== (const Id& id) const { return this->_id == id.get (); }
    IdPrimitive get ()             const { return this->_id; }
    bool isInvalid  ()             const { return this->_id == 0; }
    bool isValid    ()             const { return ! this->isInvalid (); }

  private:
    Id (IdPrimitive idp) : _id (idp) {}
    const IdPrimitive _id;
};

std::ostream& operator<<(std::ostream&, const Id&);

class IdObject {
  public:    IdObject (const Id& = IdObject::invalidId ());
    explicit IdObject (const IdObject&);

    const IdObject& operator= (const IdObject&) {
      return *this;
    }
           Id id        () const { return Id (this->_id); }
    static Id invalidId ()       { return Id (); }

  private:
    const  IdPrimitive _id;
    static IdPrimitive nextId ();
};

#endif
