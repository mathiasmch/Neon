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

#include "molecule.h"

using namespace std;
using namespace OpenBabel;

Molecule::Molecule():
    obmol_()
{
}

Molecule::Molecule(OBMol mol):
    obmol_(mol)
{
    obmol_.DeleteHydrogens();
}

Molecule::Molecule(const string& smiles)
{
    OBConversion conv;
    conv.SetInFormat("smi");
    conv.ReadString(&obmol_, smiles);

    obmol_.DeleteHydrogens();
}

void Molecule::add_fragment(Molecule& fragment)
{
    unsigned int n = obmol_.NumAtoms();

    FOR_ATOMS_OF_MOL(atom, fragment.obmol())
        obmol_.AddAtom(*atom);

    FOR_BONDS_OF_MOL(bond, fragment.obmol())
        obmol_.AddBond(bond->GetBeginAtomIdx()+n, bond->GetEndAtomIdx()+n, bond->GetBO());

    obmol_.DeleteHydrogens();
}

vector<Molecule> Molecule::separate_fragments()
{
    vector<Molecule> mols;
    vector<OBMol> obmols = obmol_.Separate();

    for(auto& obmol: obmols)
        mols.push_back(Molecule(obmol));

    return mols;
}

void Molecule::modify_charge(unsigned int atom, int charge)
{
    obmol_.GetAtom(atom)->SetFormalCharge(charge);
    obmol_.DeleteHydrogens();
}

void Molecule::modify_bond(unsigned int begin_atom, unsigned int end_atom, unsigned int bond_order)
{
    if(bond_order == 0){
        if(!obmol_.DeleteBond(obmol_.GetBond(begin_atom, end_atom)))
            throw Error("Unable to break a bond.", INTERNAL);}
    else
    {
        if(!obmol_.DeleteBond(obmol_.GetBond(begin_atom, end_atom)))
            throw Error("Unable to break a bond.", INTERNAL);
        if(!obmol_.AddBond(begin_atom, end_atom, bond_order))
            throw Error("Unable to create a bond.", INTERNAL);
    }

    obmol_.DeleteHydrogens();
}

bool Molecule::match_smarts(const string& smarts)
{
    OBSmartsPattern smarts_pattern;
    smarts_pattern.Init(smarts);
    return smarts_pattern.Match(obmol_);
}

string Molecule::formula()
{
    obmol_.AddHydrogens();
    return obmol_.GetFormula();
}

