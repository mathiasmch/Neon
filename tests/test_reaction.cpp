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

#include "../src/reaction.h"

using namespace std;

class ReactionLoaderTest: public ::testing::Test
{
protected:

    Reaction oneronep_;
    Reaction onertwop_;
    Reaction onerthreep_;
    Reaction threeronep_;

    virtual void SetUp()
    {
        oneronep_ = ReactionLoader::load_reaction_from_file("../samples/1r1p.nr");
        onertwop_ = ReactionLoader::load_reaction_from_file("../samples/1r2p.nr");
        onerthreep_ = ReactionLoader::load_reaction_from_file("../samples/1r3p.nr");
        threeronep_ = ReactionLoader::load_reaction_from_file("../samples/3r1p.nr");
    }
};

// ReactionLoader::load_reaction_from_file()
TEST_F(ReactionLoaderTest, LoadReactionFromFileTest)
{
    EXPECT_EQ("1r1p", oneronep_.id());
    EXPECT_EQ("One reactant -> one product", oneronep_.title());
    EXPECT_EQ(1, oneronep_.num_reactants());
    EXPECT_EQ(1, oneronep_.num_products());
    EXPECT_EQ("O", oneronep_.reagents().at(0));
    EXPECT_EQ("C=O", oneronep_.reagents().at(1));
    EXPECT_EQ("[CX3H1](=O)[#6]", oneronep_.reactants().at(0));

    EXPECT_EQ("1r2p", onertwop_.id());
    EXPECT_EQ("One reactant -> two products", onertwop_.title());
    EXPECT_EQ(1, onertwop_.num_reactants());
    EXPECT_EQ(2, onertwop_.num_products());
    EXPECT_EQ("[CX3H1](=O)[#6]", onertwop_.reactants().at(0));

    EXPECT_EQ("1r3p", onerthreep_.id());
    EXPECT_EQ(2, onerthreep_.num_sideproducts());
    EXPECT_EQ("N#N", onerthreep_.sideproducts().at(0));
    EXPECT_EQ("[CX3H1](=O)[#6]", onerthreep_.sideproducts().at(1));
    EXPECT_EQ("[CX3H1](=O)[#6]", onerthreep_.reactants().at(0));

    EXPECT_EQ(3, threeronep_.num_reactants());
    EXPECT_EQ("[CX3H1](=O)[#6]", threeronep_.reactants().at(0));
    EXPECT_EQ("[NX1]#[CX2]", threeronep_.reactants().at(1));
    EXPECT_EQ("[OD2]([#6])[#6]", threeronep_.reactants().at(2));
}

