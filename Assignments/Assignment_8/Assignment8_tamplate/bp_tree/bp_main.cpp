#include "bptree.cpp"

//give command line argument to load a tree from log
//to create a fresh tree, do not give any command line argument
int main(int argc, char* argv[])
{
	BPTree bpt;//B+ tree object that carries out all the operations
	string command;
	int x;
	bool close = false;
	string logBuffer;//used to save into log
	ifstream fin;
	ofstream fout;
	//create tree from log file from command line input
	if(argc > 1)
	{
		fin.open(argv[1]);//open file
		if(!fin.is_open())
		{
			cout<<"File not found\n";
			return 0;
		}
		int i = 1;
		getline(fin, logBuffer, '\0');//copy log from file to logBuffer for saving purpose
		fin.close();
		fin.open(argv[1]);//reopening file
		getline(fin,command);
		stringstream max(command);//first line of log contains the max degree
		max>>MAX;
		while(getline(fin,command))//iterating over every line ie command
		{
			if(!command.substr(0,6).compare("insert"))
			{
				stringstream argument(command.substr(7));
				argument>>x;
				bpt.insert(x);
			}
			else if(!command.substr(0,6).compare("delete"))
			{
				stringstream argument(command.substr(7));
				argument>>x;
				bpt.remove(x);
			}
			else
			{
				cout<<"Unknown command: "<<command<<" at line #"<<i<<"\n";
				return 0;
			}
			i++;
		}
		cout<<"Tree loaded successfully from: \""<<argv[1]<<"\"\n";
		fin.close();
	}
	else//create fresh tree
	{
		cout<<"Enter the max degree\n";
		cin>>command;
		stringstream max(command);
		max>>MAX;
		logBuffer.append(command);
		logBuffer.append("\n");
		cin.clear();
		cin.ignore(1);
	}
	//command line menu
	cout<<"Commands:\nsearch <value> to search\n";
	cout<<"insert <value> to insert\n";
	cout<<"delete <value> to delete\n";
	cout<<"display to display\n";
	cout<<"save to save log\n";
	cout<<"exit to exit\n";
	do
	{
		cout<<"Enter command: ";
		getline(cin,command);
		if(!command.substr(0,6).compare("search"))
		{
			stringstream argument(command.substr(7));
			argument>>x;
			bpt.search(x);
		}
		else if(!command.substr(0,6).compare("insert"))
		{
			stringstream argument(command.substr(7));
			argument>>x;
			bpt.insert(x);
			logBuffer.append(command);
			logBuffer.append("\n");
		}
		else if(!command.substr(0,6).compare("delete"))
		{
			stringstream argument(command.substr(7));
			argument>>x;
			bpt.remove(x);
			logBuffer.append(command);
			logBuffer.append("\n");
		}
		else if(!command.compare("display"))
		{
			bpt.display(bpt.getRoot());
		}
		else if(!command.compare("save"))
		{
			cout<<"Enter file name: ";
			string filename;
			cin>>filename;
			fout.open(filename);
			fout<<logBuffer;
			fout.close();
			cout<<"Saved successfully into file: \""<<filename<<"\"\n";
			cin.clear();
			cin.ignore(1);
		}
		else if(!command.compare("exit"))
		{
			close = true;
		}
		else
		{
			cout<<"Invalid command\n";
		}
	}while(!close);
	return 0;
}
