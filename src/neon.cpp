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

#include <iostream>

#include "ioparser.h"
#include "molecule.h"
#include "options.h"
#include "processor.h"
#include "reaction.h"

using namespace std;

void print_help();

int main(int argc, char* argv[])
{
    if(argc == 1 || (argc == 2 && string(argv[1]) == "--help"))
    {
        print_help();
        return 0;
    }
    if(argc < 3)
    {
        cout << "ERROR! Wrong usage." << endl;
        cout << "Type 'neon --help' for further informations." << endl;
        return 0;
    }

    string reaction_id = argv[1];
    vector<string> options_list;
    vector<string> before_del;
    string delimiter;
    string after_del;

    int i;
    for(i = argc-1; i > 1; --i)
    {
        string arg = argv[i];

        if(arg[0] == '-' && arg != "-" && arg != "--")
            options_list.push_back(arg);
        else
            break;
    }

    for(int j = 2; j <= i; ++j)
    {
        string arg = argv[j];

        if(arg == "-" || arg == "--")
            delimiter = arg;
        else
        {
            if(delimiter == "")
                before_del.push_back(arg);
            else
            {
                if(!after_del.empty())
                {
                    cout << "ERROR! Only one [output_filename] is allowed." << endl;
                    cout << "Type 'neon --help' for further informations." << endl;
                }
                after_del = arg;
            }
        }
    }

    try
    {
        Reaction reaction = ReactionLoader::load_reaction_from_file(reaction_id);

        OptionsParser options_parser(&reaction);
        Options options = options_parser.parse_options(options_list);

        IOParser ioparser(&reaction);
        Input input = ioparser.parse_input(before_del);

        Processor processor(&reaction, &input, &options);
        vector<Molecule> reactants = processor.load_reactants();        
    }
    catch(const Error& error)
    {
        cout << error.what() << endl;
    }

    return 0;
}

void print_help()
{
    cout << endl;
    cout << " Neon - An experimental cheminformatics toolkit" << endl;
    cout << endl;
    cout << "SYNOPSIS" << endl;
    cout << endl;
    cout << " neon [--help]" << endl;
    cout << " neon <reaction> <input_files>... [delimiter [output_filename]] [options]..." << endl;
    cout << endl;
    cout << "  reaction:          name of the reaction (see below)" << endl;
    cout << endl;
    cout << "  input_files:       multi-molecule file(s) and/or single-molecule file(s)" << endl;
    cout << endl;
    cout << "  delimiter:         '--' for one multi-molecule output file" << endl;
    cout << "                     '-'  for several single-molecule output files" << endl;
    cout << endl;
    cout << "  output_filename:   name used as a basis for the output file(s)" << endl;
    cout << endl;
    cout << "  options:           list of options (see below)" << endl;
    cout << endl;
    cout << "REACTIONS" << endl;
    cout << endl;
    cout << "  ..." << endl;
    cout << endl;
    cout << "OPTIONS" << endl;
    cout << endl;
    cout << "  ..." << endl;
    cout << endl;
}

