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

#include <algorithm>

#include "../src/ioparser.h"
#include "../src/reaction.h"

using namespace std;

class IOParserTest: public ::testing::Test
{
protected:

    // IOParser::parse_input()
    bool ParseInputTest(const string& reactionpath, const vector<string>& inputpaths, const vector<string>& outputpaths, bool outputmultimol) const
    {
        Reaction reaction = ReactionLoader::load_reaction_from_file(reactionpath);
        IOParser ioparser(&reaction);
        Input input = ioparser.parse_input(inputpaths);

        if(input.multimol_file != outputmultimol)
            return false;

        if(!equal(input.paths.begin(), input.paths.end(), outputpaths.begin()))
            return false;

        return true;
    }

    // IOParser::parse_input()
    void ParseInputInvalidTest(const string& reactionpath, const vector<string>& inputpaths) const
    {
        Reaction reaction = ReactionLoader::load_reaction_from_file(reactionpath);
        IOParser ioparser(&reaction);
        Input input = ioparser.parse_input(inputpaths);
    }
};

// IOParser::parse_input()
TEST_F(IOParserTest, ParseInputTest)
{
    EXPECT_TRUE(ParseInputTest("../samples/1r1p.nr", {"../samples/1molecule.smi"}, {"../samples/1molecule.smi"}, false));
    EXPECT_TRUE(ParseInputTest("../samples/3r1p.nr", {"../samples/3molecules.smi"}, {"../samples/3molecules.smi"}, true));
    EXPECT_TRUE(ParseInputTest("../samples/3r1p.nr", {"../samples/1molecule.smi", "../samples/1molecule.smi", "../samples/1molecule.smi"}, {"../samples/1molecule.smi", "../samples/1molecule.smi", "../samples/1molecule.smi"}, false));
    EXPECT_TRUE(ParseInputTest("../samples/3r1p.nr", {"../samples/2molecules.smi","../samples/1molecule.smi"}, {"../samples/2molecules.smi","../samples/1molecule.smi"}, true));

    EXPECT_THROW(ParseInputInvalidTest("../samples/1r1p.nr", {}), Error);
    EXPECT_THROW(ParseInputInvalidTest("../samples/1r1p.nr", {"../samples/3molecules.smi"}), Error);
    EXPECT_THROW(ParseInputInvalidTest("../samples/1r1p.nr", {"../samples/1molecule.smi", "../samples/1molecule.smi", "../samples/1molecule.smi"}), Error);
}

