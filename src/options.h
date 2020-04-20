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

#ifndef NEON_OPTIONS_H
#define NEON_OPTIONS_H

#include <vector>

#include "error.h"

class Reaction;

enum Stereochemistry { KEEP, IGNORE, RACEMIC };
enum Geometry { NOGEOMETRY, OPTIMISE };

struct Options
{
    bool ignore_sideproducts;
    Stereochemistry stereochemistry;
    Geometry geometry;
};

class OptionsParser
{
public:
    OptionsParser();
    OptionsParser(Reaction*);
    Options parse_options(const std::vector<std::string>&) const;

private:
    Reaction* reaction_;
};

#endif

