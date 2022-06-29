/* Fall 2020
 This program has been created to view the content in a file based upon a specified limit.
 That specified limit is then used to allow a user to navigate through a file progressively
 by entering yes. 
 
 This program will give you various amount of information such as your file size, your browsing position,
 your current page number, how many pages there are, and lastly this program will display the content of each
 successive yes.

 Note: The first result will not return anything as I start from 0. Please enter 'y' to continue
 to match your first result and consecutive results.

 Rickey Lavel Hargrove Jr.
*/


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

 //Function prototypes 
// display contents, allow 24 lines per display
// then pause, show 24 more lines if user enter Y and N for close
	bool openFileIn(fstream &, string);
	void showContents(fstream &);

int main()
{
  //prepare this file to be opened, read, and or written to
  fstream dataFile;  
  //get the users requested file //this requires an absolute file path
  //for testing /Users/InnovativeMagic/Desktop/
  string filename = "";
  //get response
  char response;
  //create an array for the data
  char data[100][2];
  //hold file size
  long numBytes;
  //hold a char
  char ch;
  //hold number of pages
  int pages;
  //page count holder
  int iteration;


  //get file name
  cout << "Please enter the name of the file you are searching for.\n";
  cin >> filename;
  cout << "You are searching for " << filename << endl;
  

  //check if the file exists
  dataFile.open(filename, ios::in);
  //if open fails
  if(dataFile.fail()){
  	// send a failed alert 
  	bool status;
  	cout << "This file does not exist on your system\n Be sure to type in an absolute path such as /path1/path2/Desktop/MyFile.txt";
  	status = false;
  	return status;
  } 
  else{
    //get the file and its contents/ insert file into array
    cout << "We are processing your file for display.\n";
    //place initial data into array.
    dataFile.read(reinterpret_cast<char *>(data), sizeof(data));
    //Get number of bytes in this file
    dataFile.seekg(0L, ios::end);
    numBytes = dataFile.tellg();
    cout << "The file has " << numBytes << " bytes.\n";
    //go to beginning of file
    dataFile.seekg(0L, ios::beg);

    do{
    	//cout << iteration << " you've said yes this many times";
        cout << "Current position " << dataFile.tellg() << endl;
        int pageAt = ((numBytes / 24) + 1) - (((numBytes - dataFile.tellg())/24)+1) ;
        cout << "Current page " <<  iteration << endl;
       //if you have reached the maximum amount of pages, to prevent a loop, close file, and exit.
        if(iteration == 9){
        	cout << "You have read all of the data in this file.\n";
        	dataFile.close();
        	exit(0);
        }else{

       //Get how many pages are in the file
    	pages = (numBytes / 24) + 1;
    	cout << "There are this many pages " << pages << "\n";

    	//read the contents of the file and place it into the array
    	// dynamically define the array to read a dynamic amount of content
        int showContent = 24 * iteration;
        char data[showContent][2];
        dataFile.read(reinterpret_cast<char *>(data), sizeof(data));
        
        // this will display the requested data based upon the current iteration of yes.
        cout << data[iteration] << " " << " \n";

        //continue 
        if(dataFile.tellg() < 0){
         //After reading all of the data the current position will set to -1, you can continue or stop.
         // the end of file is calculuated by the number of pages based upon the requested 24 lines and the total number of 
         // bytes
         cout << "You have read all of the data in this file but here is more unreadable content in this file\n";
         cout << "Do you wish to coninue\n";
         cin >> response;
        }else{ 

      	cout << "Do you want to see more?" << endl;
        cin >> response;
        }
        //log how many times user is saying yes,
        // this can't exceed the page limit
        if(tolower(response) == 'y'){
          iteration++;
        }
    }
    }while(tolower(response) == 'y');

  }

 return 0;
}
