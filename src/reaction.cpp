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

#include "reaction.h"

using namespace std;
using namespace tinyxml2;

Reaction::Reaction():
    id_(),
    title_(),
    reagents_(),
    reactants_(),
    products_(),
    sideproducts_()
{
}

Reaction ReactionLoader::load_reaction_from_file(const string& path)
{
    Reaction reaction;

    XMLDocument file;
    if(file.LoadFile(path.c_str()))
        throw Error("Unable to parse reaction file "+path+".");

    XMLElement* root = file.FirstChildElement("reaction");
    if(!root)
        throw Error("No <reaction> found in "+path+".");

    XMLElement* id = root->FirstChildElement("id");
    if(!id)
        throw Error("No <id> found in "+path+".");
    reaction.id_ = id->GetText();

    XMLElement* title = root->FirstChildElement("title");
    if(!title)
        throw Error("No <title> found in "+path+".");
    reaction.title_ = title->GetText();

    XMLElement* reagents = root->FirstChildElement("reagents");
    if(reagents)
    {
        XMLElement* reagent = reagents->FirstChildElement("reagent");
        if(!reagent)
            throw Error("Empty <reagents> in "+path+".");

        while(reagent)
        {
            reaction.reagents_.push_back(reagent->GetText());
            reagent = reagent->NextSiblingElement("reagent");
        }
    }

    XMLElement* reactants = root->FirstChildElement("reactants");
    if(!reactants)
        throw Error("No <reactants> found in "+path+".");
    else
    {
        XMLElement* reactant = reactants->FirstChildElement("reactant");
        if(!reactant)
            throw Error("Empty <reactants> in "+path+".");

        while(reactant)
        {
            reaction.reactants_.push_back(reactant->GetText());
            reactant = reactant->NextSiblingElement("reactant");
        }
    }

    XMLElement* products = root->FirstChildElement("products");
    if(!products)
        throw Error("No <products> found in "+path+".");
    else
    {
        XMLElement* product = products->FirstChildElement("product");
        if(!product)
            throw Error("Empty <products> in "+path+".");

        while(product)
        {
            reaction.products_.push_back(product->GetText());
            product = product->NextSiblingElement("product");
        }
    }

    XMLElement* sideproducts = root->FirstChildElement("sideproducts");
    if(sideproducts)
    {
        XMLElement* sideproduct = sideproducts->FirstChildElement("sideproduct");
        if(!sideproduct)
            throw Error("Empty <sideproducts> in "+path+".");

        while(sideproduct)
        {
            reaction.sideproducts_.push_back(sideproduct->GetText());
            sideproduct = sideproduct->NextSiblingElement("sideproduct");
        }
    }

    return reaction;
}

