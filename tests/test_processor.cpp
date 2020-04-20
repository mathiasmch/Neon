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
#include "../src/ioparser.h"
#include "../src/molecule.h"
#include "../src/options.h"
#include "../src/processor.h"
#include "../src/reaction.h"

using namespace std;

class ProcessorTest: public ::testing::Test
{
protected:

    // Processor::load_reactants()
    bool LoadReactantsTest(const string& nr, const vector<string>& in, const vector<string>& formulas) const
    {
        Reaction reaction = ReactionLoader::load_reaction_from_file(nr);
        IOParser ioparser(&reaction);
        Input input = ioparser.parse_input(in);

        Processor processor(&reaction, &input, nullptr);
        vector<Molecule> reactants = processor.load_reactants();

        return match_formulas(reactants, formulas);
    }

    // Processor::sort_reactants()
    bool SortReactantsTest(const string& nr, const string& in, const vector<string>& formulas) const
    {
        Reaction reaction = ReactionLoader::load_reaction_from_file(nr);
        IOParser ioparser(&reaction);
        Input input = ioparser.parse_input({in});

        Processor processor(&reaction, &input, nullptr);
        vector<Molecule> reactants = processor.load_reactants();
        vector<Molecule> sorted_reactants = processor.sort_reactants(reactants);

        return match_formulas(sorted_reactants, formulas);
    }

    // Processor::filter_sideproducts()
    bool FilterSideproductsTest(vector<Molecule> products, const vector<string>& formulas) const
    {
        Reaction reaction = ReactionLoader::load_reaction_from_file("../samples/1r3p.nr");

        Processor processor(&reaction, nullptr, nullptr);
        vector<Molecule> filtered_products = processor.filter_sideproducts(products);

        return match_formulas(filtered_products, formulas);
    }
};

// Processor::load_reactants()
TEST_F(ProcessorTest, LoadReactantsTest)
{
    EXPECT_TRUE(LoadReactantsTest("../samples/1r1p.nr", {"../samples/1molecule.smi"}, {"CH4", "H2O", "CH2O"}));
    EXPECT_TRUE(LoadReactantsTest("../samples/3r1p.nr", {"../samples/3molecules.smi"}, {"CH4", "C2H6", "C3H8", "H2O", "CH2O"}));
    EXPECT_TRUE(LoadReactantsTest("../samples/3r1p.nr", {"../samples/2molecules.smi", "../samples/1molecule.smi"}, {"CH4", "C2H6", "CH4", "H2O", "CH2O"}));
}

// Processor::sort_reactants()
TEST_F(ProcessorTest, SortReactantsTest)
{
    EXPECT_TRUE(SortReactantsTest("../samples/5r1p.nr", "../samples/5molecules.smi", {"C3H9N", "CH2O2", "C4H8", "C2H5N", "C2H6O"}));
    EXPECT_TRUE(SortReactantsTest("../samples/5r1p.nr", "../samples/5molecules_bis.smi", {"C3H9N", "CH2O2", "C4H8", "C2H5N", "C2H6O"}));
}

// Processor::filter_sideproducts()
TEST_F(ProcessorTest, FilterSideproductsTest)
{
    EXPECT_TRUE(FilterSideproductsTest({Molecule("CCC"), Molecule("N#N"), Molecule("CC=O")}, {"C3H8"}));
    EXPECT_TRUE(FilterSideproductsTest({Molecule("CC=O"), Molecule("N#N"), Molecule("CCC")}, {"C3H8"}));
    EXPECT_TRUE(FilterSideproductsTest({Molecule("N#N")}, {}));
}

