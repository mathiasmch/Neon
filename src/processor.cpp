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
#include "molecule.h"
#include "processor.h"
#include "reaction.h"

using namespace std;

Processor::Processor():
    reaction_(nullptr),
    input_(nullptr),
    options_(nullptr)
{
}

Processor::Processor(Reaction* reaction, Input* input, Options* options):
    reaction_(reaction),
    input_(input),
    options_(options)
{
}

vector<Molecule> Processor::load_reactants() const
{
    vector<Molecule> reactants;

    for(const auto& path: input_->paths)
    {
        vector<Molecule> mols = FileHandler::load_molecules_from_file(path);
        reactants.insert(reactants.end(), mols.begin(), mols.end());
    }

    for(const auto& reagent: reaction_->reagents())
        reactants.push_back(Molecule(reagent));

    return reactants;
}

vector<Molecule> Processor::sort_reactants(vector<Molecule>& reactants) const
{
    vector<string> smartss = reaction_->reactants();
    if(smartss.size() + reaction_->num_sideproducts() != reactants.size())
        throw Error("Unmatched number of reactants/reagents.", INTERNAL);

    vector<Molecule> sorted_reactants;
    vector<bool> reactant_assigned(reactants.size(), false);

    for(const auto& smarts: smartss)
    {
        bool smarts_found = false;

        for(size_t i = 0; i < reactants.size(); ++i)
        {
            if(!reactant_assigned.at(i))
            {
                if(reactants.at(i).match_smarts(smarts))
                {
                    sorted_reactants.push_back(reactants.at(i));

                    reactant_assigned.at(i) = true;
                    smarts_found = true;
                    break;
                }
            }
        }

        if(!smarts_found)
            throw Error("No reactant/reagent found that matches SMARTS "+smarts);
    }

    if(sorted_reactants.size() != reactants.size())
        throw Error("Fail to sort reactants/reagents.", INTERNAL);
    if(!any_of(reactant_assigned.begin(), reactant_assigned.end(), [](bool r){return r;}))
        throw Error("Reactant/reagent with unknown role.", INTERNAL);

    return sorted_reactants;
}

vector<Molecule> Processor::filter_sideproducts(vector<Molecule>& products) const
{
    vector<Molecule> filtered_products;
    vector<string> sideproducts = reaction_->sideproducts();

    for(auto& product: products)
        if(!any_of(sideproducts.begin(), sideproducts.end(), [&product](string smarts){return product.match_smarts(smarts);}))
            filtered_products.push_back(product);

    return filtered_products;
}

