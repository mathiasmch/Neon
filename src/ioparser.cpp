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

#include "ioparser.h"
#include "reaction.h"

using namespace std;

IOParser::IOParser():
    reaction_(nullptr)
{
}

IOParser::IOParser(Reaction* reaction):
    reaction_(reaction)
{
}

Input IOParser::parse_input(const vector<string>& reactants) const
{
    if(reactants.empty())
        throw Error("No <input_files> specified.\nType 'neon --help' for further informations.");

    Input input;
    input.multimol_file = false;

    unsigned int num_input_mol = 0;

    for(const auto& reactant: reactants)
    {
        input.paths.push_back(reactant);

        unsigned int n = FileHandler::count_molecules_in_file(reactant);
        if(n > 1)
            input.multimol_file = true;

        num_input_mol += n;
    }

    if(reaction_->num_reactants() != num_input_mol)
        throw Error("Wrong number of reactants for reaction "+reaction_->id()+".");

    return input;
}

