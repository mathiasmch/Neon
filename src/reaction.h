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

#ifndef NEON_REACTION_H
#define NEON_REACTION_H

#include <vector>
#include <tinyxml2/tinyxml2.h>

#include "error.h"

class Reaction;

class ReactionLoader
{
public:
    static Reaction load_reaction_from_file(const std::string&);
};

class Reaction
{
public:
    Reaction();
    std::string id() const { return id_; }
    std::string title() const { return title_; }
    unsigned int num_reactants() const { return static_cast<unsigned int>(reactants_.size()); }
    unsigned int num_products() const { return static_cast<unsigned int>(products_.size()); }
    unsigned int num_sideproducts() const { return static_cast<unsigned int>(sideproducts_.size()); }
    std::vector<std::string> reagents() const { return reagents_; };
    std::vector<std::string> reactants() const { return reactants_; };
    std::vector<std::string> products() const { return products_; };
    std::vector<std::string> sideproducts() const { return sideproducts_; };

private:
    std::string id_;
    std::string title_;
    std::vector<std::string> reagents_; // SMILES
    std::vector<std::string> reactants_; // SMARTS
    std::vector<std::string> products_; // SMARTS
    std::vector<std::string> sideproducts_; // SMARTS

    friend Reaction ReactionLoader::load_reaction_from_file(const std::string&);
};

#endif

