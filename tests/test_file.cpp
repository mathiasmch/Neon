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
#include "../src/error.h"
#include "../src/file.h"
#include "../src/molecule.h"

using namespace std;

class FileHandlerTest: public ::testing::Test
{
protected:

    // FileHandler::load_molecules_from_file()
    bool LoadMoleculesFromFileTest(const string& in, const vector<string>& formulas) const
    {
        vector<Molecule> mols = FileHandler::load_molecules_from_file(in);
        return match_formulas(mols, formulas);
    }
};

// FileHandler::load_molecules_from_file()
TEST_F(FileHandlerTest, LoadMoleculesFromFileTest)
{
    EXPECT_TRUE(LoadMoleculesFromFileTest("../samples/1molecule.smi", {"CH4"}));
    EXPECT_TRUE(LoadMoleculesFromFileTest("../samples/2molecules.smi", {"CH4", "C2H6"}));
    EXPECT_TRUE(LoadMoleculesFromFileTest("../samples/3molecules.smi", {"CH4", "C2H6", "C3H8"}));

    EXPECT_THROW(LoadMoleculesFromFileTest("blablabla", {}), Error);
    EXPECT_THROW(LoadMoleculesFromFileTest("blablabla.smi", {}), Error);
}

// FileHandler::count_molecules_in_file()
TEST_F(FileHandlerTest, CountMoleculesInFileTest)
{
    EXPECT_EQ(1, FileHandler::count_molecules_in_file("../samples/1molecule.smi"));
    EXPECT_EQ(2, FileHandler::count_molecules_in_file("../samples/2molecules.smi"));

    EXPECT_THROW(FileHandler::count_molecules_in_file("blablabla"), Error);
    EXPECT_THROW(FileHandler::count_molecules_in_file("blablabla.smi"), Error);
}

