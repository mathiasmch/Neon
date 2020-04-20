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

#include <gtest/gtest.h>

#include "utility.h"
#include "../src/molecule.h"

using namespace std;
using namespace OpenBabel;

class MoleculeTest: public ::testing::Test
{
protected:

    // Molecule::Molecule() and Molecule::formula()
    string ConstructAndGetFormulaTest(const string& smiles) const
    {
        Molecule mol(smiles);
        return mol.formula();
    }

    // Molecule::add_fragment() and Molecule::separate_fragments()
    bool AddFragmentAndSeparateFragmentsTest(const vector<string>& in, const vector<string>& formulas) const
    {
        Molecule mol;

        for(size_t i = 0; i < in.size(); ++i)
        {
            Molecule fragment(in.at(i));
            mol.add_fragment(fragment);
        }

        vector<Molecule> fragments = mol.separate_fragments();
        return match_formulas(fragments, formulas);
    }

    // Molecule::modify_charge()
    bool ModifyChargeTest(const string& in, unsigned int atom, int charge, unsigned int num_atoms, int tot_charge, const string& formula) const
    {
        Molecule mol(in);
        mol.modify_charge(atom, charge);

        if(mol.obmol()->NumAtoms() != num_atoms || mol.obmol()->GetTotalCharge() != tot_charge || mol.formula() != formula)
            return true;
        return false;
    }

    // Molecule::modify_bond()
    bool ModifyBondTest(const string& in, const vector<string>& formulas, unsigned int ba, unsigned int ea, unsigned int bo) const
    {
        Molecule mol(in);
        mol.modify_bond(ba, ea, bo);

        vector<Molecule> fragments = mol.separate_fragments();
        return match_formulas(fragments, formulas);
    }

    // Molecule::match_smarts()
    bool MatchSmartsTest(const string& in, const string& smarts) const
    {
        Molecule mol(in);
        return mol.match_smarts(smarts);
    }

    // Molecule::num_atoms()
    bool NumAtomsTest(const string& in, unsigned int num_atoms) const
    {
        Molecule mol(in);

        if(mol.num_atoms_noH() == num_atoms)
            return true;
        return false;
    }
};

// Molecule::Molecule() and Molecule::formula()
TEST_F(MoleculeTest, ConstructAndGetFormulaTest)
{
    EXPECT_EQ("CH4", ConstructAndGetFormulaTest("C"));
    EXPECT_EQ("C2H6O", ConstructAndGetFormulaTest("CCO"));
    EXPECT_EQ("C6H6", ConstructAndGetFormulaTest("c1ccccc1"));
}

// Molecule::add_fragment() and Molecule::separate_fragments()
TEST_F(MoleculeTest, AddFragmentAndSeparateFragmentsTest)
{
    EXPECT_TRUE(AddFragmentAndSeparateFragmentsTest({"CCO"}, {"C2H6O"}));
    EXPECT_TRUE(AddFragmentAndSeparateFragmentsTest({"C", "CC", "CCC"}, {"CH4", "C2H6", "C3H8"}));
    EXPECT_FALSE(AddFragmentAndSeparateFragmentsTest({"CCO"}, {"CH4", "C2H6", "C3H8"}));
    EXPECT_FALSE(AddFragmentAndSeparateFragmentsTest({"C", "CC", "CCC"}, {"C2H6O"}));
}

// Molecule::modify_charge()
TEST_F(MoleculeTest, ModifyChargeTest)
{
    EXPECT_TRUE(ModifyChargeTest("O", 1, 1, 4, 1, "H3O+"));
    EXPECT_TRUE(ModifyChargeTest("O", 1, -1, 2, 1, "HO-"));
    EXPECT_TRUE(ModifyChargeTest("CO", 2, -1, 5, -1, "CH3O-"));
}

// Molecule::modify_bond()
TEST_F(MoleculeTest, ModifyBondTest)
{
    EXPECT_TRUE(ModifyBondTest("CC", {"CH4","CH4"}, 1, 2, 0));
    EXPECT_TRUE(ModifyBondTest("CC", {"C2H4"}, 1, 2, 2));
}

// Molecule::match_smarts()
TEST_F(MoleculeTest, MatchSmartsTest)
{
    EXPECT_TRUE(MatchSmartsTest("CCC=O", "[CX3H1](=O)[#6]"));
    EXPECT_FALSE(MatchSmartsTest("CCCC", "[CX3H1](=O)[#6]"));
    EXPECT_TRUE(MatchSmartsTest("CCC#N", "[NX1]#[CX2]"));
    EXPECT_FALSE(MatchSmartsTest("CCCC", "[NX1]#[CX2]"));
}

// Molecule::num_atoms()
TEST_F(MoleculeTest, NumAtomsTest)
{
    EXPECT_TRUE(NumAtomsTest("C", 1));
    EXPECT_TRUE(NumAtomsTest("CC(=O)OC1=CC=CC=C1C(=O)O", 13));
}

