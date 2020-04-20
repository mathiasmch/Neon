/******************************************************************************

    Neon - An experimental cheminformatics toolkit

    Copyright (C) 2014 Mathias M.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

******************************************************************************/

#ifndef NEON_MOLECULE_H
#define NEON_MOLECULE_H

#include <vector>

#include "error.h"
#include "openbabel.h"

class Molecule
{
public:
    Molecule();
    Molecule(OpenBabel::OBMol);
    Molecule(const std::string&);

    void add_fragment(Molecule&);
    std::vector<Molecule> separate_fragments();
    void modify_charge(unsigned int, int);
    void modify_bond(unsigned int, unsigned int, unsigned int);
    bool match_smarts(const std::string&);

    std::string formula();
    OpenBabel::OBMol* obmol() { return &obmol_; };
    unsigned int num_atoms_noH() { return obmol_.NumAtoms(); };

private:
    OpenBabel::OBMol obmol_;   
};

#endif

