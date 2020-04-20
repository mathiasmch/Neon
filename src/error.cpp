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

#include "error.h"

using namespace std;

Error::Error(const string& msg, ErrorType type):
    type_(type),
    msg_(msg)
{
}

string Error::what() const
{
    if(type_ == USER_INPUT)
        return "ERROR! "+msg_;
    else
        return "Sorry, an internal error has occured... ("+msg_+").";
}

