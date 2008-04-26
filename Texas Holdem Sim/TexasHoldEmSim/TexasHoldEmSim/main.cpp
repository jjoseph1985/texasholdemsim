// main.cpp

#include <string>
#include <iostream>

#include "card.h"
#include "player.h"
#include "hand.h"
#include "table.h"
#include "anyoption.h"
#include "deck.h"

// Function declarations
string ParseCmdLine( int argc, char* argv[], vector<string>& vKeys, AnyOption& anyOpt);
void MapKeys(map<string,string>& mPairs, vector<string>& vKeys, AnyOption& anyOpt);
void InitKeys(vector<string>& vKeys);



int main( int argc, char ** argv )
{
    vector<string> vKeys;
    map<string,string> mPairs;
	Table table(25,10);
    AnyOption anyOpt;
    string outPutFile = "";
    ofstream fout;
    
    // Starting things off:
    // 1. Parse the command line
    // 2. Init the keys in the config file
    // 3. Map them to their values
    // 4. Open the output file
    /*InitKeys(vKeys);
    outPutFile = ParseCmdLine(argc, argv, vKeys, anyOpt);
    MapKeys(mPairs, vKeys, anyOpt);
    
    fout.open(outPutFile.c_str());
    if(!fout.is_open())
    {
        cout << "IO Error... could not open " << outPutFile;
        exit(0);
    }*/
	
	//NE: Just testing the odds table printout.
	/*
	GameFlow* fl;
	game testGame(fl);
	//wait
	char k;
	cin >> k;
	*/
	table.Init();

    
	// TODO: Write the main application so that the sim starts and plays itself.
    //       Because it is currently gui driven they are using QT related things
    //       to progress through the game if no human players are left (pretty sure).
    //       
    //       Problem: Comp class doesn't work at the moment...
    //
    //       http://www.nd.edu/~cseprog/proj04_331/deepgold/source/
    
    // TODO: Initialize appropriate components based upon the mPairs map.
    
    fout.close();
    
    return 0;   
}



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
string ParseCmdLine( int argc, char* argv[], vector<string>& vKeys, AnyOption& anyOpt) //, AnyOption& anyOpt, vector<string>& vKeys )
{

    const string defaultOutputFile = "simulation.log";
    const string defaultInputFile  = "simulation.ini";
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
        cout << "\nUsing input config file:   " << anyOpt.getValue('i') << "\n";
    }
    else if( anyOpt.getValue( "input" ) != NULL )
    {
        // Set user defined config filename
        anyOpt.processFile(anyOpt.getValue("input"));
        cout << "\nUsing input config file:   " << anyOpt.getValue("input") << "\n";
    }
    else
    {
        // Set default config filename
        anyOpt.processFile(defaultInputFile.c_str());
        cout << "\nUsing default config file: " << defaultInputFile << "\n";
    }



    // Get output config file
    if( anyOpt.getValue('o') != NULL )
    {
        // Set user defined config filename
        anyOpt.processFile(anyOpt.getValue('o'));
        cout << "\nUsing output file: " << anyOpt.getValue('o') << "\n";
        outputFile = anyOpt.getValue('o');
    }
    else if( anyOpt.getValue( "output" ) != NULL )
    {
        // Set user defined config filename
        anyOpt.processFile(anyOpt.getValue("output"));
        cout << "\nUsing output file: " << anyOpt.getValue("output") << "\n";
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


/*
    MapKeys: Takes the specified configuration file keys, and maps them
             To their specified value.
*/
void MapKeys(map<string,string>& mPairs, vector<string>& vKeys, AnyOption& anyOpt)
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

    /*
    for(mit = mPairs.begin(); mit != mPairs.end(); mit++)
    {
        fout << mit->first << " : " << mit->second << "\n";
    }
    */
} // MapKeys()


void InitKeys( vector<string>& vKeys)
{
    // These end up being case insensitive
    vKeys.push_back("Number of players");
    vKeys.push_back("Player difficulty");
    vKeys.push_back("Buy in");
    vKeys.push_back("Big blind");
    vKeys.push_back("Small blind");
    vKeys.push_back("Blind timer");
    vKeys.push_back("Dealer");
    vKeys.push_back("OFF-BY-ONE");
    
} // InitKeys()