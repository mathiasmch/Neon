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

#include "options.h"
#include "reaction.h"

using namespace std;

OptionsParser::OptionsParser():
    reaction_(nullptr)
{
}

OptionsParser::OptionsParser(Reaction* reaction):
    reaction_(reaction)
{
}

Options OptionsParser::parse_options(const vector<string>& opts) const
{
    Options options;

    // default:
    options.ignore_sideproducts = false;
    options.stereochemistry = KEEP;
    options.geometry = NOGEOMETRY;

    bool is_stereochemistry_set = false;
    bool is_geometry_set = false;

    for(const auto& opt: opts)
    {
        if(opt == "--nosideproducts")
        {
            if(reaction_->num_sideproducts() == 0)
                throw Error("Invalid use of --nosideproducts: reaction "+reaction_->id()+" has no sideproducts.");
            options.ignore_sideproducts = true;
        }
        else if(opt == "--nostereo")
        {
            if(is_stereochemistry_set)
                throw Error("Invalid options: --nostereo and --racemic are forbidden together.");
            else
            {
                options.stereochemistry = IGNORE;
                is_stereochemistry_set = true;
            }
        }
        else if(opt == "--racemic")
        {
            if(is_stereochemistry_set)
                throw Error("Invalid options: --nostereo and --racemic are forbidden together.");
            else
            {
                options.stereochemistry = RACEMIC;
                is_stereochemistry_set = true;
            }
        }
        else if(opt == "--nogeometry")
        {
            if(is_geometry_set)
                throw Error("Invalid options: --nogeometry and --optimise are forbidden together.");
            else
            {
                options.geometry = NOGEOMETRY;
                is_geometry_set = true;
            }
        }
        else if(opt == "--optimise")
        {
            if(is_geometry_set)
                throw Error("Invalid options: --nogeometry and --optimise are forbidden together.");
            else
            {
                options.geometry = OPTIMISE;
                is_geometry_set = true;
            }
        }

        else
            throw Error("Invalid option "+opt);
    }

    return options;
}

