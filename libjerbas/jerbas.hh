// file jerbas.hh - the library header file for C++

/**   Copyright (C)  2015 Basile Starynkevitch <basile@starynkevitch.net>

    This file is part of JERBAS.
  
    JERBAS is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3, or (at your option)
    any later version.
  
    JERBAS is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with GCC; see the file COPYING3.   If not see
    <http://www.gnu.org/licenses/>.
**/
#ifndef JERBAS_INCLUDED
#include <vector>
#include <set>
#include <map>
#include <functional>
#include <cstdint>
#include <cassert>

#include <asmjit/asmjit.h>

namespace jerbas {
  class Obj;
  class Function;
  class Frame;
  class Closure;
  class Variable;

  typedef uint64_t serial_t;

  ////////////////
  class Obj {
    serial_t _serial;
    static serial_t _counter;
    std::vector<std::function<void(Obj*)>> _destructors;
  protected:
    Obj() { _counter++; _serial = _counter; };
    void run_destructors(void);
    virtual ~Obj();
  public:
    void register_destructor(std::function <void(Obj*)>);
    serial_t serial() const { return _serial; };
  };				// end class Obj

  enum Type_en {
    typ_none,
    typ_int,			// 64 bits int
    typ_dbl,			// 64 bits IEEE754 floating point
    typ_ptr,			// 64 bits pointers
  };

  enum Varseq_en {
    vseq_none,
    vseq_frame,
    vseq_closure
  };
  
  class VarSeq : public Obj {
  protected:
    std::vector<Variable*> _vars;
    const Varseq_en _kind;
    Function* _ownerfun;
    VarSeq (Varseq_en k) : Obj(), _vars(), _kind(k), _ownerfun(nullptr) {};
  };				// end VarSeq

  class Frame : public VarSeq {
  public:
    Frame() : VarSeq(vseq_frame) {};
  };				// end Frame

  class Closure : public VarSeq {
  public:
    Closure(): VarSeq(vseq_closure) {};
  };				// end Closure
				  

  class Variable : public Obj {
    Type_en _type;
    VarSeq* _vsowner;
  };				// end class Variable
  
};				// end namespace jerbas


//// useful links:
//// https://lwn.net/Articles/631631/ How programs get run: ELF binaries
//// https://lwn.net/Articles/519085/ getauxval() and the auxiliary vector
#endif /* JERBAS_INCLUDED */
