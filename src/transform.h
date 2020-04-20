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

#ifndef NEON_TRANSFORM_H
#define NEON_TRANSFORM_H

#include <vector>

struct Charge
{
    unsigned int atom;
    int charge;
};

struct Bond
{
    unsigned int begin_atom;
    unsigned int end_atom;
    unsigned int bond_order;
};

struct ReactionCharge
{
    unsigned int mol;
    unsigned int atom;
    int charge;
};

struct ReactionBond
{
    unsigned int begin_mol;
    unsigned int begin_atom;
    unsigned int end_mol;
    unsigned int end_atom;
    unsigned int bond_order;
};

typedef std::vector<Charge> ChargeTransform;
typedef std::vector<Bond> BondTransform;
typedef std::vector<ReactionCharge> ReactionChargeTransform;
typedef std::vector<ReactionBond> ReactionBondTransform;

class Transform
{
public:
    static ChargeTransform convert_charges(const ReactionChargeTransform&, const std::vector<unsigned int>&);
    static BondTransform convert_bonds(const ReactionBondTransform&, const std::vector<unsigned int>&);
};

#endif

