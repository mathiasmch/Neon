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

#include "../src/transform.h"

using namespace std;

class TransformerTest: public ::testing::Test
{
protected:

    // Transformer::convert_charges()
    bool ConvertChargesTest(const ReactionChargeTransform& rct, const vector<unsigned int>& mols_sizes, const ChargeTransform& result)
    {
        ChargeTransform ct = Transform::convert_charges(rct, mols_sizes);

        if(ct.size() != result.size())
            return false;

        for(size_t i = 0; i < ct.size(); ++i)
        {
            if(ct.at(i).atom != result.at(i).atom)
                return false;
            if(ct.at(i).charge != result.at(i).charge)
                return false;
        }

        return true;
    }

    // Transformer::convert_bonds()
    bool ConvertBondsTest(const ReactionBondTransform& rbt, const vector<unsigned int>& mols_sizes, const BondTransform& result) const
    {
        BondTransform bt = Transform::convert_bonds(rbt, mols_sizes);

        if(bt.size() != result.size())
            return false;

        for(size_t i = 0; i < bt.size(); ++i)
        {
            if(bt.at(i).begin_atom != result.at(i).begin_atom)
                return false;
            if(bt.at(i).end_atom != result.at(i).end_atom)
                return false;
            if(bt.at(i).bond_order != result.at(i).bond_order)
                return false;
        }

        return true;
    }
};

// Transformer::convert_charges()
TEST_F(TransformerTest, ConvertChargesTest)
{
    EXPECT_TRUE(ConvertChargesTest({{1,1,-1}},{1},{{1,-1}}));
    EXPECT_TRUE(ConvertChargesTest({{1,2,1},{3,1,-1},{4,2,2},{4,3,0}},{4,2,1,3},{{2,1},{7,-1},{9,2},{10,0}}));
}

// Transformer::convert_bonds()
TEST_F(TransformerTest, ConvertBondsTest)
{
    EXPECT_TRUE(ConvertBondsTest({{1,1,1,2,2},{1,3,1,4,0}},{1},{{1,2,2},{3,4,0}}));
    EXPECT_TRUE(ConvertBondsTest({{1,1,2,1,2},{1,2,1,3,1},{1,3,3,1,1},{2,2,2,4,0},{2,3,3,1,3}},{3,4,1},{{1,4,2},{2,3,1},{3,8,1},{5,7,0},{6,8,3}}));
}

