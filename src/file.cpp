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

#include "file.h"
#include "molecule.h"

using namespace std;
using namespace OpenBabel;

vector<Molecule> FileHandler::load_molecules_from_file(const string& path)
{
    vector<Molecule> molecules;

    OBMol mol;
    OBConversion conv;

    OBFormat* format = conv.FormatFromExt(path);
    if(!format)
        throw Error("Unable to determine the file format of "+path);
    conv.SetInFormat(format);

    if(!conv.ReadFile(&mol, path))
        throw Error("Unable to read "+path);
    else
    {
        while(1)
        {
            molecules.push_back(Molecule(mol));

            mol.Clear();
            if(!conv.Read(&mol))
                break;
        }
    }

    return molecules;
}

unsigned int FileHandler::count_molecules_in_file(const string& path)
{
    return static_cast<unsigned int>(load_molecules_from_file(path).size());
}

