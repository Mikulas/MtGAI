#include <iostream>
#include <string>
#include "Database.h"

using namespace std;

int main (int argc, char * const argv[])
{
	cout << "started\n";
	Database db = Database();
	cout << "db init\n";
	//db.get();
	
	//Card cr = db.getRandom();
	//cout << "The random card is: " << cr.name << "\n";
	
	Card a = db.get("Disenchant");
	Card b = db.get("Errand of Duty");
	
	getchar();
	getchar();
    return 0;
}
