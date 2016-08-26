/*input
3
2
10.1.2.3/8
10.2.3.4/17
2
10.2.3.4/9
10.128.2.3/9
10
224.147.224.186/18
58.45.85.53/14
52.56.134.139/26
52.227.82.227/22
83.250.251.44/13
83.250.12.64/16
58.40.52.11/14
52.22.138.56/23
238.223.58.151/27
58.32.52.11/13
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
#include <cmath>
#include <iomanip>
#include <ctime>
#include <climits>
#include <cfloat>
#include <queue>
#include <set>
#include <bitset>

using namespace std;


struct BinTree
{
	BinTree *left;
	BinTree *right;
	bool end;
};


bool insert(BinTree &root, string bitString)
{
	BinTree *temp;
	bool newOne = false;
	// cout<<bitString<<endl;
	if (bitString[0] == '0')
	{
		temp = root.left;
		if (temp == NULL)
		{
			root.left = new BinTree();
			temp = root.left;
			temp->left = NULL;
			temp->right = NULL;
			newOne = true;
		}
	}
	else
	{
		temp = root.right;
		if (temp == NULL)
		{
			root.right = new BinTree();
			temp = root.right;
			temp->left = NULL;
			temp->right = NULL;
			newOne = true;
		}
	}


	for (int i = 1; i < bitString.length(); ++i)
	{
		if (bitString[i] == '0')
		{
			if (temp->left != NULL)
			{
				temp = temp->left;
			}
			else if (temp->left == NULL && temp->right == NULL && !newOne)
			{
				return false;
			}
			else
			{
				temp->left = new BinTree();
				temp = temp->left;
				temp->left = NULL;
				temp->right = NULL;
				newOne = true;
			}
		}
		else
		{
			if (temp->right != NULL)
			{
				temp = temp->right;
			}
			else if (temp->left == NULL && temp->right == NULL && !newOne)
			{
				return false;
			}
			else
			{
				temp->right = new BinTree();
				temp = temp->right;
				temp->left = NULL;
				temp->right = NULL;
				newOne = true;
			}
		}
	}
	temp->left = NULL;
	temp->right = NULL;
	return true;
}

bool checkAllPresent(BinTree *root)
{
	// cout<<"TRUE"<<endl;
	if (root->left == NULL && root->right != NULL)
	{
		return false;
	}
	if (root->left != NULL && root->right == NULL)
	{
		return false;
	}
	if (root->left != NULL && root->right != NULL)
	{
		return (checkAllPresent(root->left)&checkAllPresent(root->right));
	}
	return true;
}

void modifyTree(BinTree *root)
{
	BinTree *temp1 = root->left;
	BinTree *temp2 = root->right;
	if (temp1 != NULL && temp2 != NULL && checkAllPresent(temp1) && checkAllPresent(temp2))
	{
		root->left = NULL;
		root->right = NULL;		
	}
	else
	{
		if (temp1 != NULL)
		{
			modifyTree(temp1);
		}
		if (temp2 != NULL)
		{
			modifyTree(temp2);
		}
	}

}


void traverseTree(string current, int depth, BinTree *root, string number)
{
	// cout<<current<<endl;

	stringstream buffer;

	if (depth%8 == 0 && depth != 0)
	{
		current = current + "00000000";
		buffer<<strtol(current.substr(0, 8).c_str(), NULL, 2);
		current = "";
		if (root->left == NULL && root->right == NULL)
		{
			for (int i = (depth-1)/8; i < 3; ++i)
			{
				buffer<<".0";
			}

			buffer<<"/"<<depth;
			cout<<number+buffer.str()<<endl;
			return;
		}
		else
		{
			buffer<<".";
		}
	}

	if (root->left != NULL)
	{
		traverseTree(current+'0', depth+1, root->left, number+buffer.str());	
	}
	if (root->right != NULL)
	{
		traverseTree(current+'1', depth+1, root->right, number+buffer.str());
	}
	if (root->left == NULL && root->right == NULL)
	{
		current = current + "00000000";
		buffer<<strtol(current.substr(0, 8).c_str(), NULL, 2);

		for (int i = (depth-1)/8; i < 3; ++i)
		{
			buffer<<".0";
		}

		buffer<<"/"<<depth;
		cout<<number+buffer.str()<<endl;
	}
}

string convertToBitString(string subnet)
{
	vector<int> intVals;
	int lastPos = 0;
	for (int i = 0; i < subnet.length(); ++i)
	{
		if (subnet[i] == '.' || subnet[i] == '/')
		{
			// cout<<subnet<<" "<<subnet.substr(lastPos, i-lastPos)<<" "<<atoi(subnet.substr(lastPos, i-lastPos).c_str())<<endl;
			intVals.push_back(atoi(subnet.substr(lastPos, i-lastPos).c_str()));
			lastPos = i+1;
		}
	}

	int length = atoi(subnet.substr(lastPos, subnet.length()-lastPos).c_str());

	bitset<8> bitVals1(intVals[0]);
	bitset<8> bitVals2(intVals[1]);
	bitset<8> bitVals3(intVals[2]);
	bitset<8> bitVals4(intVals[3]);

	string bitString = "";

	for (int i = 0; i < length; ++i)
	{
		if (i/8 == 0)
		{
			bitString += bitVals1[7-i%8]?'1':'0';
		}
		else if (i/8 == 1)
		{
			bitString += bitVals2[7-i%8]?'1':'0';			
		}
		else if (i/8 == 2)
		{
			bitString += bitVals3[7-i%8]?'1':'0';
		}
		else
		{			
			bitString += bitVals4[7-i%8]?'1':'0';
		}
	}
	// cout<<bitString<<endl;
	return bitString;
}

int main(int argc, char const *argv[])
{	
    freopen("C-large-practice.in","r",stdin);
    freopen("output.out","w",stdout);


    int testCaseCount;

    cin>>testCaseCount;

    for (int i = 0; i < testCaseCount; ++i)
    {
    	BinTree root;
    	root.left = NULL;
    	root.right = NULL;
    	root.end = false;

    	int subnetCount;
    	cin>>subnetCount;

    	for (int j = 0; j < subnetCount; ++j)
    	{
    		string subnet;
    		cin>>subnet;
    		insert(root, convertToBitString(subnet));
    	}

        cout<<"Case #"<<i+1<<": "<<endl;
        modifyTree(&root);
        traverseTree("",0, &root,"");
    }
}