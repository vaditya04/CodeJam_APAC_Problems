/*input
3
0 2
/home/gcj/finals
/home/gcj/quals
2 1
/chicken
/chicken/egg
/chicken
1 3
/a
/a/b
/a/c
/b/b
*/

#include <vector>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>
#include <sstream>
#include <map>
#include <iterator>

using namespace std; 

struct fileDir
{
	string dirName;
	map<string, fileDir*> childDirs;
};

void split(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
}

vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}

int insertDir(vector<string> pathDirs, fileDir *fd)
{
	long long insertCount = 0;
	// cout<<pathDirs[0]<<endl;
	fileDir *currentFd = fd;
	for (long long k = 0; k < pathDirs.size(); ++k)
	{
		if (pathDirs[k].length() <1)
			continue;

		if (currentFd->childDirs.find(pathDirs[k]) == currentFd->childDirs.end())
		{
			insertCount++;
			fileDir *newDir = new fileDir();
			newDir->dirName = pathDirs[k];
			currentFd->childDirs[pathDirs[k]] = newDir;
			currentFd = currentFd->childDirs[pathDirs[k]];
		}
		else
		{
			currentFd = currentFd->childDirs[pathDirs[k]];
		}
	}
	return insertCount;
}

void deleteFileDir(fileDir *fd)
{
	map<string, fileDir*>::const_iterator iterator = fd->childDirs.begin();
	for (; iterator !=	 fd->childDirs.end(); ++iterator)
	{
		deleteFileDir(iterator->second);
	}
	delete fd;
}

int main(int argc, char const *argv[])
{
	freopen("A-large-practice.in","r",stdin);
    freopen("output.out","w",stdout);

	long long testCaseCount;

	cin>>testCaseCount;

	for (long long i = 0; i < testCaseCount; ++i)
	{
		long long originalPaths, newPaths;

		cin>>originalPaths>>newPaths;

		fileDir *fd = new fileDir();
		fd->dirName = "";

		for (long long j = 0; j < originalPaths; ++j)
		{
			string path;
			cin>>path;
			vector<string> pathDirs = split(path, '/');
		

			insertDir(pathDirs, fd);
		}		
		// printDir(fd);
		long long finalCount = 0;

		vector <string> paths;
		for (long long j = 0; j < newPaths; ++j)
		{
			string path;
			cin>>path;
			// cout<<path;
			paths.push_back(path);
		// }

		// sort(paths.begin(), paths.end()/*, lengthComp()*/);

		// for (long long j = 0; j < newPaths; ++j)
		// {
			vector<string> pathDirs = split(paths[j], '/');
			// cout<<paths[j]<<endl;
			// cout<<"3"<<path<<endl;
			finalCount += insertDir(pathDirs, fd);
			// cout<<"4"<<path<<endl;
		}


		// printDir(fd);
		cout<<"Case #"<<i+1<<": "<<finalCount<<endl;
		deleteFileDir(fd);
	}

	return 0;
}