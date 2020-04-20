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

#include "utility.h"

using namespace std;

bool match_formulas(const vector<Molecule>& molecules, const vector<string>& expected_formulas)
{
    vector<string> formulas(molecules.size(), "");

    transform(molecules.begin(),
                molecules.end(),
                formulas.begin(),
                [](Molecule mol){ return mol.formula(); });

    if(equal(formulas.begin(), formulas.end(), expected_formulas.begin()))
        return true;
    return false;
}

