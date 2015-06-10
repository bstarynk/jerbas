// file object.cc - the basic object implementation

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

#include "jerbas.hh"

using namespace jerbas;

serial_t Obj::_counter;

void Obj::run_destructors(void) {
  assert (_serial>0);
  auto vecdest = _destructors;
  _destructors.clear();
  for (auto fd : vecdest)
    fd(this);
}

Obj::~Obj() {
  run_destructors();
  _serial = 0;
} // end Obj::~Obj

void
Obj::register_destructor(std::function <void(Obj*)>fd) {
  _destructors.push_back(fd);
} // end Obj::register_destructor
