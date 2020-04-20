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

#include "../src/options.h"
#include "../src/reaction.h"

using namespace std;

class OptionsParserTest: public ::testing::Test
{
protected:

    // OptionsParser::parse_options()
    bool ParseOptionsTest(const string& nr, const vector<string>& options, Stereochemistry stereo, Geometry geo, bool sp) const
    {
        Reaction reaction = ReactionLoader::load_reaction_from_file(nr);
        OptionsParser options_parser(&reaction);
        Options opt = options_parser.parse_options(options);

        if(opt.stereochemistry != stereo || opt.geometry != geo || opt.ignore_sideproducts != sp)
            return false;
        return true;
    }
};

// OptionsParser::parse_options()
TEST_F(OptionsParserTest, ParseOptionsTest)
{
    EXPECT_TRUE(ParseOptionsTest("../samples/1r1p.nr", {}, KEEP, NOGEOMETRY, false));
    EXPECT_TRUE(ParseOptionsTest("../samples/1r1p.nr", {"--nostereo"}, IGNORE, NOGEOMETRY, false));
    EXPECT_TRUE(ParseOptionsTest("../samples/1r3p.nr", {"--racemic", "--nosideproducts"}, RACEMIC, NOGEOMETRY, true));
    EXPECT_TRUE(ParseOptionsTest("../samples/1r1p.nr", {"--optimise"}, KEEP, OPTIMISE, false));
    EXPECT_TRUE(ParseOptionsTest("../samples/1r1p.nr", {"--nogeometry"}, KEEP, NOGEOMETRY, false));
    EXPECT_TRUE(ParseOptionsTest("../samples/1r1p.nr", {"--nostereo", "--nogeometry"}, IGNORE, NOGEOMETRY, false));
    EXPECT_TRUE(ParseOptionsTest("../samples/1r3p.nr", {"--nostereo", "--optimise", "--nosideproducts"}, IGNORE, OPTIMISE, true));

    EXPECT_THROW(ParseOptionsTest("../samples/1r1p.nr", {"--blablabla"}, KEEP, NOGEOMETRY, false), Error);
    EXPECT_THROW(ParseOptionsTest("../samples/1r1p.nr", {"--nostereo", "--blablabla"}, KEEP, NOGEOMETRY, false), Error);
    EXPECT_THROW(ParseOptionsTest("../samples/1r1p.nr", {"--nostereo", "--racemic"}, KEEP, NOGEOMETRY, false), Error);
    EXPECT_THROW(ParseOptionsTest("../samples/1r1p.nr", {"--nogeometry", "--optimise"}, KEEP, NOGEOMETRY, false), Error);
    EXPECT_THROW(ParseOptionsTest("../samples/1r1p.nr", {"--nostereo", "--nogeometry", "--optimise"}, KEEP, NOGEOMETRY, false), Error);
    EXPECT_THROW(ParseOptionsTest("../samples/1r1p.nr", {"--nosideproducts"}, IGNORE, NOGEOMETRY, false), Error);
}

