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

#include "transform.h"

using namespace std;

ChargeTransform Transform::convert_charges(const ReactionChargeTransform& rcts, const vector<unsigned int>& mols_sizes)
{
    ChargeTransform ct;

    for(const auto& rct: rcts)
    {
        Charge c;
        c.atom = rct.atom;
        c.charge = rct.charge;

        if(rct.mol != 1)
            for(size_t j = 0; j < rct.mol-1; ++j)
                c.atom += mols_sizes.at(j);

        ct.push_back(c);
    }

    return ct;
}

BondTransform Transform::convert_bonds(const ReactionBondTransform& rbts, const vector<unsigned int>& mols_sizes)
{
    BondTransform bt;

    for(const auto& rbt: rbts)
    {
        Bond b;
        b.begin_atom = rbt.begin_atom;
        b.end_atom = rbt.end_atom;
        b.bond_order = rbt.bond_order;

        if(rbt.begin_mol != 1)
            for(size_t j = 0; j < rbt.begin_mol-1; ++j)
                b.begin_atom += mols_sizes.at(j);

        if(rbt.end_mol != 1)
            for(size_t j = 0; j < rbt.end_mol-1; ++j)
                b.end_atom += mols_sizes.at(j);

        bt.push_back(b);
    }

    return bt;
}

