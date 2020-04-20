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

#ifndef NEON_PROCESSOR_H
#define NEON_PROCESSOR_H

#ifdef TESTS
class ProcessorTest;
#endif

struct Input;
class Molecule;
struct Options;
class Reaction;

class Processor
{
public:
    Processor();
    Processor(Reaction*, Input*, Options*);
    std::vector<Molecule> load_reactants() const;

private:
    std::vector<Molecule> sort_reactants(std::vector<Molecule>&) const;
    std::vector<Molecule> filter_sideproducts(std::vector<Molecule>&) const;

    Reaction* reaction_;
    Input* input_;
    Options* options_;

#ifdef TESTS
    friend ProcessorTest;
#endif
};

#endif

