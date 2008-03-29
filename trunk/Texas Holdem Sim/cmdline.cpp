#include <string>
#include <cstring>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include "anyoption.h"

// USE: Parse the command line and the default configuration file
//      OR the optionally specified configuration file, BUT NOT BOTH.
//      Options are read from a config file with ':' separated
//      parameters, one per line.
//
// RETURNS: Output file string name.
//
// NOTE: The parser is not smart enough to use the default values for
//       those that are not specified by the user. That is: ALL options
//       must be specified in a user defined configuration file.
//
// See "anyoption.h" and/or "anyOptionDemo" for more information.
string ParseCmdLine( int argc, char* argv[]) //, AnyOption& anyOpt, vector<string>& vKeys )
{
    initKeys();
    const string defaultOutputFile = "holdem.log";
    const string defaultInputFile  = "holdem.ini";
    string inputFile = "";
    string outputFile = "";

    /* 2. SET PREFERENCES  */
    //opt.noPOSIX(); /* do not check for POSIX style character options */
    //opt.setVerbose(); /* print warnings about unknown options */
    //opt.autoUsagePrint(true); /* print usage for bad options */

    /* 3. SET THE USAGE/HELP   */
    anyOpt.addUsage( "" );
    anyOpt.addUsage( "Usage: " );
    anyOpt.addUsage( "" );
    anyOpt.addUsage( " -h  --help  		 Prints this help " );
    anyOpt.addUsage( " -o  --output FILE 	 Output file " );
    anyOpt.addUsage( " -i  --input  FILE       Input configuration file " );


    /* 4. SET THE OPTION STRINGS/CHARACTERS */

    // Only check on command line for the following options, not the config file.
    anyOpt.setCommandFlag( "help", 'h' );
    anyOpt.setOption( "output", 'o' );
    anyOpt.setOption( "input",  'i' );


    /* 5. PROCESS THE COMMANDLINE AND RESOURCE FILE */

    /* EDIT the vector in main for more input file parameters */
    // Only check the config file for the following and not the commandline.
    // key value pairs separated by ':'. One per line
    // ex: name : Bob Smith
    for(vector<string>::iterator it = vKeys.begin(); it < vKeys.end(); it++)
    {
        anyOpt.setFileOption((*it).c_str());
    }


    // Parse the command line, now that we know what we are looking for
    anyOpt.processCommandArgs( argc, argv );


    // Display help
    if( anyOpt.getFlag( "help" ) || anyOpt.getFlag( 'h' ) )
    {
        anyOpt.printUsage();
        exit(0);
    }


    // Get input config file
    if( anyOpt.getValue('i') != NULL )
    {
        // Set user defined config filename
        anyOpt.processFile(anyOpt.getValue('i'));
        cout << "\nUsing input config file:   " << anyOpt.getValue('i');
    }
    else if( anyOpt.getValue( "input" ) != NULL )
    {
        // Set user defined config filename
        anyOpt.processFile(anyOpt.getValue("input"));
        cout << "\nUsing input config file:   " << anyOpt.getValue("input");
    }
    else
    {
        // Set default config filename
        anyOpt.processFile(defaultInputFile.c_str());
        cout << "\nUsing default config file: " << defaultInputFile;
    }



    // Get output config file
    if( anyOpt.getValue('o') != NULL )
    {
        // Set user defined config filename
        anyOpt.processFile(anyOpt.getValue('o'));
        cout << "\nUsing output file: " << anyOpt.getValue('o');
        outputFile = anyOpt.getValue('o');
    }
    else if( anyOpt.getValue( "output" ) != NULL )
    {
        // Set user defined config filename
        anyOpt.processFile(anyOpt.getValue("output"));
        cout << "\nUsing output file: " << anyOpt.getValue("output");
        outputFile = anyOpt.getValue("output");
    }
    else
    {
        // Set default config filename
        anyOpt.processFile(defaultOutputFile.c_str());
        outputFile = defaultOutputFile;
        cout << "\nUsing default output file: " << defaultOutputFile << "\n\n\n";
    }

    return outputFile;
} // ParseCmdLine


map<string,string> InitLog(ostream& fout)
{

    vector<string>::iterator vit;
    map<string,string>::iterator mit;


    /* 6. GET THE VALUES */
    // I have no idea where the off by 1 error comes from
    // An extra value is pushed to the end of vKey and this makes it work
    for(vit = vKeys.begin(); vit < (vKeys.end() - 1); vit++)
    {
        char* tmpVal = anyOpt.getValue((*vit).c_str());
        string value(tmpVal);
        string key(*vit);

        mPairs.insert( pair<string,string>(key,value));
    }

    return 

    /*
    for(mit = mPairs.begin(); mit != mPairs.end(); mit++)
    {
        fout << mit->first << " : " << mit->second << "\n";
    }
    */

}


void initKeys()
{
    // And I can't initialize a vector with elements already in it because, why?
    vKeys.push_back("Arbitrary Option in file");

    vKeys.push_back("DUMMY");
}

#endif