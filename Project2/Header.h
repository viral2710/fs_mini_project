#include<iostream>
#include<string>
#include<fstream>
#include <vector> 
using namespace std;

 
vector<string> splitStrings(string str, char dl)
{
	string word = "";
	int num = 0;
	str = str + dl; 
	int l = str.size(); 
	vector<string> substr_list;
	for (int i = 0; i < l; i++) { 
		if (str[i] != dl)
			word = word + str[i];

		else {
			if ((int)word.size() != 0)
				substr_list.push_back(word);
			word = "";
		}
	}
	return substr_list;
}
class student
{
public:
	string usn;
	string name;
	string sem;
	string dept;
	string Buf;
	char buf[100];
};
istream& operator >> (istream& in, student& s)
{
	cout << "Enter usn:-";
	in >> s.usn;
	cout << "Enter name:-";
	in >> s.name;
	cout << "Enter sem.:-";
	in >> s.sem;
	cout << "Enter dept.:-";
	in >> s.dept;
	return in;
}
ostream& operator << (ostream& out, student& s)
{
	out << s.usn << "\t" << s.name << "\t" << s.sem << "\t" << s.dept << "\t";
	return out;
}
class node
{
public:
	student value[4];
	node* child[4];
	node* next, * per;
	node* parent;
	int size;
	node();
};
class btree
{
public:
	node* head;
	int flag, flage,ds;
	string st[1000];
	void insert(student key);
	void search(student key);
	btree update(student key, student key2);
	void tree_view(node* n);
	btree del(student key);
	void write();
	void read();
	void display();
	btree();
private:
	node* split(node* n);
	node* tchilds(node* n);
	node* findlevel(student key, node* n);
};
node::node() {
	size = 4;
	for (int i = 0; i < size; i++) {
		value[i].usn = "";
		value[i].name = "";
		value[i].sem = "";
		value[i].dept = "";
		child[i] = NULL;
	}
	size = 0;
	next = NULL;
	per = NULL;
	parent = NULL;
}
btree::btree() {
	head = NULL;
	flag = 0;
	flage = 0;
	ds = 0;
}
void btree::insert(student key) {
	if (head == NULL) {
		head = new node;
		head->value[head->size] = key;
		head->size++;
		return;
	}
	node* n = findlevel(key, head);
	int i;

	for (i = 0; i < n->size; i++) {
		if (key.usn == n->value[i].usn) {
			if (key.sem < n->value[i].sem)
				break;
			else if (key.sem > n->value[i].sem)
				continue;
			else {
				cout << "already exits" << endl;
				return;
			}

		}
		if (key.usn < n->value[i].usn) {
			break;
		}
	}
	if (i == n->size) {
		n->value[i] = key;
		n->size++;
	}
	else {
		student temp;
		for (; i < n->size; i++) {
			temp = n->value[i];
			n->value[i] = key;
			key = temp;
		}
		n->value[i] = key;
		n->size++;
	}
	if (n->size > 3) {
		node* x = split(n);
	}
	return;
}
node* btree::findlevel(student key, node* n) {
	node* ptr = n;
	int i;
	for (i = 0; i < ptr->size; i++) {
		if (key.usn < ptr->value[i].usn) {
			if (ptr->child[i] != NULL) {
				return(findlevel(key, ptr->child[i]));
			}
			else {
				return ptr;
			}
		}
	}
	if (i == ptr->size && key.usn > ptr->value[i].usn) {
		if (ptr->child[i] != NULL) {
			return(findlevel(key, ptr->child[i]));
		}
		else
		{
			return ptr;
		}
	}
	return ptr;
}
btree btree::del(student key) {
	node* n = head;
	int x = 0;
	btree b;
	student a[1000];
	while (n->child[0] != NULL) {
		n = n->child[0];
	}
	while (n != NULL) {

		for (int i = 0; i < n->size; i++) {
			if ((key.usn.compare(n->value[i].usn)) && (key.sem.compare(n->value[i].sem))) {
					a[x++] = n->value[i];
			}	
			else {
				flage = 1;
			}
		}
		n = n->next;
	}
	if (flage == 0) {
		cout << "element not found\n";
		b.head = head;
		return b;
	}
	for (int i = 0; i <= x; i++) {
		b.insert(a[i]);
		b.flage = 1;
	}
	return b;
}
btree btree::update(student key, student key2) {
	node* n = head;
	int x = 0;
	btree b;
	student a[1000];
	while (n->child[0] != NULL) {
		n = n->child[0];

	}
	while (n != NULL) {

		for (int i = 0; i < n->size; i++) {
			if ((key.usn.compare(n->value[i].usn)) && (key.sem.compare(n->value[i].sem)))
				a[x++] = n->value[i];
			else {
				a[x++] = key2;
				flage = 1;
			}
		}
		n = n->next;
	}
	if (flage == 0) {
		cout << "element not found\n";
		b.head = head;
		return b;
	}
	for (int i = 0; i <= x; i++) {
		b.insert(a[i]);
		b.flage = 1;
	}
	n = b.head;
	while (n->child[0] != NULL) {
		n = n->child[0];
	}
	for (int i = 0; i < n->size; i++)
		cout << n->value[i];
	return b;
}
node* btree::split(node* n) {
	int m = (n->size / 2);
	int x = 0;
	node* ptr;
	if (n->parent == NULL) {
		head = new node;
		ptr = head;
		ptr->value[x] = n->value[m];
		ptr->size++;
	}
	else {
		ptr = n->parent;
		for (x = 0; x < ptr->size; x++) {
			if (n->value[m].usn < ptr->value[x].usn) {
				break;
			}
		}
		student temp = n->value[m];
		student temp2;
		node* ad1, * ad2;
		ad1 = ptr->child[x];
		int y = x;
		for (; x < ptr->size; x++) {
			temp2 = ptr->value[x];
			ptr->value[x] = temp;
			temp = temp2;

			ad2 = ptr->child[x + 1];
			ptr->child[x + 1] = ad1;
			ad1 = ad2;
		}
		ptr->value[x] = temp;
		ptr->child[x + 1] = ad1;
		x = y;
		ptr->size++;
	}
	node* c1 = new node;
	node* c2 = new node;
	ptr->child[x] = c1;
	ptr->child[x + 1] = c2;
	c1->next = c2;
	c2->per = c1;
	if (x != 0) {
		if (ptr->child[x - 1] != NULL) {
			ptr->child[x - 1]->next = c1;
			c1->per = ptr->child[x - 1];
		}
	}

	if (ptr->child[x + 2] != NULL) {
		c2->next = ptr->child[x + 2];
		ptr->child[x + 2]->per = c2;
	}
	if (n->child[0] == NULL) {
		for (int i = 0; i < m; i++) {
			c1->value[i] = n->value[i];
			c1->size++;
		}
		for (int i = m, x = 0; i < n->size; i++, x++) {
			c2->value[x] = n->value[i];
			c2->size++;
		}
		if (n->next != NULL) {
			c2->next = n->next;
		}
		if (n->per != NULL)
			n->per->next = c1;
	}
	else {
		c1->child[0] = n->child[0];
		c1->child[0]->parent = c1;
		for (int i = 0; i < m; i++) {
			c1->value[i] = n->value[i];
			c1->child[i + 1] = n->child[i + 1];
			c1->child[i + 1]->parent = c1;
			c1->size++;
		}
		c2->child[0] = n->child[m + 1];
		c2->child[0]->parent = c2;
		for (int i = m + 1, x = 0; i < n->size; i++, x++) {
			c2->value[x] = n->value[i];
			c2->child[x + 1] = n->child[i + 1];
			c2->child[x + 1]->parent = c2;
			c2->size++;
		}

	}


	c1->parent = ptr;
	c2->parent = ptr;
	if (ptr->size > 3) {
		ptr = split(ptr);
	}

	return c2;
}
void btree::display() {
	node* n = head;
	st[ds++]= "USN\t|\tNAME\t|\tSEM.\t|\tDEPT\t|\n";
	while (n->child[0] != NULL) {
		n = n->child[0];

	}
	while (n != NULL) {
		
		for (int i = 0; i < n->size; i++) {
			if (n->value[i].usn == "")
				continue;
			st[ds++] = n->value[i].usn + "\t|\t" + n->value[i].name + "\t|\t" + n->value[i].sem + "\t|\t" + n->value[i].dept + "\t|\n";
		}
		n = n->next;
	}
	return;
}
void btree::search(student key) {
	node* ptr = head;
	ds = 0;
	st[ds++] = "USN\t|\tNAME\t|\tSEM.\t|\tDEPT\t|\n";
	int x = 0;
	while (ptr != NULL) {

		if (ptr->child[0] == NULL) {
			for (int i = 0; i < ptr->size; i++) {
				if (key.usn.compare(ptr->value[i].usn)==0) {
					flag = 1;
					st[ds++] = ptr->value[i].usn + "\t|\t" + ptr->value[i].name + "\t|\t" + ptr->value[i].sem + "\t|\t" + ptr->value[i].dept + "\t|\n";
					return;
				}
			}
			break;
		}
		else
		{
			int i;
			for (i = 0; i < ptr->size; i++) {
				if (key.usn < ptr->value[i].usn) {
					break;
				}
			}
			ptr = ptr->child[i];
			cout << x++ << "\t";
			cout << "->";
		}


	}

	st[0] = "usn not found";
	return;
}
void btree::tree_view(node* n) {
	cout << "|";
	for (int i = 0; i < n->size; i++) {
		cout << n->value[i];
	}
	cout << "|" << endl;
	while (n != NULL) {}


}
void btree::write() {
	node* n = head;
	ds = 0;
	for (int i = 0; i < 1000; i++)
	{
		st[i] = "";
	}
	while (n->child[0] != NULL) {
		n = n->child[0];

	}
	while (n != NULL) {

		for (int i = 0; i < n->size; i++) {
			if (n->value[i].usn == "")
				continue;
			st[ds++] = n->value[i].usn + "|" + n->value[i].name + "|" + n->value[i].sem + "|" + n->value[i].dept + "|";
		}
		n = n->next;
	}
	return;
}
void btree::read() {
	char dl = '|';
	student s;
	for (int i = 0; i < ds; i++) {
		vector<string> res = splitStrings(st[i], dl);
		s.usn = res[0];
		s.name = res[1];
		s.sem = res[2];
		s.dept = res[3];
		insert(s);
	}
}