//Program by Christina Ochsner
//PS#: 1166214

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

struct node
{
	int data;
	struct node *left=NULL;
	struct node *right=NULL;
	int height;
};

class AVLtree
{
	private:
		node* root;
		ofstream out;
	public:
		AVLtree(string filename)
		{
			root = NULL;
			out.open(filename);
		}
		int height(node *n)
		{
			if (n == NULL)
			{
				return 0;
			}
			return n->height;
		}
		
		int max(int x, int y)
		{
			if (x > y)
			{
				return x;
			}
			return y;
		}
		struct node *rotateRight(node* n)
		{
			node *newroot = n->left;
			node* temp = newroot->right;
			newroot->right = n;

			n->left = temp;

			n->height = max(height(n->left), height(n->right))+1;
			newroot->height = max(height(newroot->left), height(newroot->right))+1;

			return newroot;
		}
		int depth(int key)
		{
			node* current = root;
			int level = 1;

			while (current != NULL && current->data != key)
			{
				if (current->data < key)
				{
					current = current->right;
				}
				else if (current->data > key)
				{
					current = current->left;
				}
				level++;
			}
			if (current == NULL)
			{
				//0 means tree is empty
				return 0;
			}
			else
			{
				return level;
			}
		}
		node *rotateLeft(node *n)
		{
			node *newroot = n->right;
			node *temp = newroot->left;

			newroot->left = n;
			n->right = temp;

			n->height = max(height(n->left), height(n->right))+1;
			newroot->height = max(height(newroot->left), height(newroot->right))+1;

			return newroot;
		}
		int balanceFactor(node *n)
		{
			if (n == NULL)
			{
				return 0;
			}
			return height(n->left) - height(n->right);
		}
		node* inserts(node* n, int key)
		{
			if (n == NULL)
			{
				node* newnode = new node;
				newnode->data = key;
				newnode->height = 1;
				return newnode;
			}
			if (key < n->data)
			{
				n->left = inserts(n->left, key);
			}
			else if (key > n->data)
			{
				n->right = inserts(n->right, key);
			}
			else
			{
				return n;
			}

			n->height = max(height(n->left), height(n->right))+1;

			int balance = balanceFactor(n);

			if (balance > 1 && key < n->left->data)
			{
				return rotateRight(n);
			}
			if (balance < -1 && key > n->right->data)
			{
				return rotateLeft(n);
			}
			if (balance > 1 && key > n->left->data)
			{
				n->left = rotateLeft(n->left);
				return rotateRight(n);
			}
			if (balance < -1 && key < n->right->data)
			{
				n->right = rotateRight(n->right);
				return rotateLeft(n);
			}

			return n;
		}
		void level(int l)
		{
			int h = height(root);
			if (l < 1  || h < l)
			{
				out << "empty" <<endl;
				return;
			}
			traverse(root, l);

			out << endl;
		}
		void traverse(node* n, int l)
		{
			if (n != NULL)
			{
				traverse(n->left, l);
				if (depth(n->data) == l)
				{
					out << n->data << " ";
				}
				traverse(n->right, l);
			}
		}
		void insert(int key)
		{
			root=inserts(root, key);
		}
		void inorder(node* n)
		{
			if (n != NULL)
			{
				inorder(n->left);
				out << n->data << " ";
				inorder(n->right);
			}
		}
		void preorder(node* n)
		{
			if (n != NULL)
			{
				out << n->data << " ";
				preorder(n->left);
				preorder(n->right);
			}
		}
		void postorder(node* n)
		{
			if (n != NULL)
			{
				postorder(n->left);
				postorder(n->right);
				out << n->data << " ";
			}
		}
		void print(string type)
		{
			if (type == "Preorder")
			{
				preorder(root);
			}
			else if (type == "Postorder")
			{
				postorder(root);
			}
			else if (type == "Inorder")
			{
				inorder(root);
			}
			out << endl;
		}
		~AVLtree()
		{
			out.close();
		}
};

int main(int argc, char *argv[])
{
	//Declare and/or initialize variables to be used in program.
	char input[25];
	char commands[25];
	char output[25];
	char type;
	int i=0;
	int y=1;
	int o;
	
	//Parse command line to retrieve and store file names.
	while(argv[y][i]!='\0')
	{
		switch(argv[y][i])
		{
			case '=':
				i++;
				o=0;
				while(argv[y][i]!='\0'&&argv[y][i]!=';'&&argv[y][i]!=' ')
				{
					switch(type)
					{
						case 'v':
						input[o]=argv[y][i];
						if(argv[y][i+1]=='\0'||argv[y][i+1]==';')
						{
							input[o+1]='\0';
						}
						break;
						
						case 'c':
						commands[o]=argv[y][i];
						if(argv[y][i+1]=='\0'||argv[y][i+1]==';')
						{
							commands[o+1]='\0';
						}
						break;
						
						case 'o':
						output[o]=argv[y][i];
						if(argv[y][i+1]=='\0'||argv[y][i+1]==';')
						{
							output[o+1]='\0';
						}
						break;
					}
					o++;
					i++;
				}
				if(argv[y][i]=='\0'&&argc>2&&y<3)
				{
						i=0;
						y++;
				}
			break;
			case 'v':
				type='v';
				i++;
			break;
			case 'c':
				type='c';
				i++;
			break;
			case 'o':
				if(argv[y][i+1]=='u')
				{
					type='o';
				}
				i++;
			break;
			default:
				i++;
			break;
		}
	}
	ifstream in(input);
	ifstream cmd(commands);

	AVLtree t(output);
	
	int node;
	string line;

	while (in >> node)
	{
		t.insert(node);
	}
	
	in.close();
	
	while (getline(cmd, line))
	{
		stringstream ss(line);
		string command;
		while (ss >> command)
		{
			if (command == "Level")
			{
				int l;
				ss >> l;
				t.level(l);
			}
			else if (command == "Inorder")
			{
				t.print(command);
			}
			else if (command == "Preorder")
			{
				t.print(command);
			}
			else if (command == "Postorder")
			{
				t.print(command);
			}
		}		
	}
	cmd.close();
	
	return 0;
}