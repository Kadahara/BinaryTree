#include<iostream>
#include<ctime>
using namespace std;
using std::cout;
using std::endl;
using std::cin;

#define tab "\t"
#define delimiter "\n------------------------------------------------\n"

class Tree
{
protected:
	class Element
	{

		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr)
			:Data(Data), pLeft(pLeft), pRight(pRight)
		{
#ifdef DEBUG
			cout << "EConstructor:\t" << this << endl;
#endif // DEBUG

		}
		~Element()
		{
#ifdef DEBUG
			cout << "EDestructor" << this << endl;
#endif // DEBUG
		}
		bool is_leaf()const
		{
			return pLeft == pRight;
		}
		friend class Tree;
		friend class UniqueTree;
	}*Root;
public:
	Element* getRoot()
	{
		return Root;
	}
	Tree() :Root(nullptr)
	{
#ifdef DEBUG
		cout << "TConstructor:\t" << this << endl;
#endif // DEBUG

	}
	Tree(const std::initializer_list<int>& il) :Tree()
	{
		for (int i : il)insert(i, Root);
	}
	~Tree()
	{
		clear(Root);
#ifdef DEBUG
		cout << "TDestuctor:\t" << this << endl;
#endif // DEBUG

	}
	void insert(int Data)
	{
		insert(Data, Root);
	}
	int minValue()const
	{
		return minValue(Root);
	}
	int maxValue()const
	{
		return maxValue(Root);
	}
	int count()const
	{
		return count(Root);
	}
	int Sum()const
	{
		return Sum(Root);
	}
	double Avg()const
	{
		return (double)Sum(Root) / count(Root);
	}
	int depth()const
	{
		return depth(Root);
	}
	void clear()
	{
		clear(Root);
		Root = nullptr;
	}
	void erase(int Data)
	{
		erase(Data, Root);
	}
	void print()const
	{
		print(Root);
		cout << endl;
	}
private:
	//					Adding elements:
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr) Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else
		{
			if (Root->pRight == nullptr) Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
	int minValue(Element* Root)const
	{
		if (Root == nullptr)return 0;
		/*if (Root->pLeft == nullptr)return Root->Data;
		else return minValue(Root->pLeft);*/
		return Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
	}
	//				Metods
	int maxValue(Element* Root)const
	{
		if (Root == nullptr) return 0;
		/*if (Root->pRight == nullptr)return Root->Data;
		else return maxValue(Root->pRight);*/
		return Root->pRight == nullptr ? Root->Data : maxValue(Root->pRight);
	}
	int count(Element* Root)const
	{
		if (Root == nullptr)return 0;
		/*return count(Root->pLeft) + count(Root->pRight) + 1;*/
		return !Root ? 0 : count(Root->pLeft) + count(Root->pRight) + 1;
	}
	int Sum(Element* Root)const
	{
		/*if (Root == nullptr)return 0;
		else return Sum(Root->pLeft) + Sum(Root->pRight) + Root->Data;*/
		return Root == nullptr ? 0 : Sum(Root->pLeft) + Sum(Root->pRight) + Root->Data;
	}
	double Avg(Element* Root)const
	{
		return (double)Sum(Root) / count(Root);
	}
	int depth(Element* Root)const
	{
		if (Root == nullptr)return 0;
		int l_depth = depth(Root->pLeft) + 1;
		int r_depth = depth(Root->pRight) + 1;
		return l_depth > r_depth ? l_depth : r_depth;
		/*else return
			depth(Root->pLeft) > depth(Root->pRight) ?
			depth(Root->pLeft) + 1 :
			depth(Root->pRight) + 1;*/
			//if (depth(Root->pLeft) > depth(Root->pRight))return depth(Root->pLeft) + 1;
			//else return depth(Root->pRight) + 1;
	}
	void clear(Element* Root)
	{
		if (Root == nullptr)return;
		clear(Root->pLeft);
		clear(Root->pRight);
		delete Root;
	}
	void erase(int Data, Element* Root)
	{
		if (Root == nullptr)return;
		erase(Data, Root->pLeft);
		erase(Data, Root->pRight);
		if (Data == Root->Data)
		{
			if (Root->is_leaf())
			{
				delete Root;
				Root = nullptr;
			}
			else
				if (count(Root->pLeft) > count(Root->pRight))
				{
					Root->Data = maxValue(Root->pLeft);
					erase(maxValue(Root->pLeft), Root->pLeft);
				}
				else
				{
					Root->Data = minValue(Root->pRight);
					erase(minValue(Root->pRight), Root->pRight);
				}
		}
	}
	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << "\t";
		print(Root->pRight);
	}
};

class UniqueTree :public Tree
{

	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else if (Data > Root->Data)
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
public:
	void insert(int Data)
	{
		insert(Data, Root);
	}
};
template<typename T>
void measure(const char description[], const Tree& tree, T (Tree::*member_function)()const)
{
	cout << description;
	clock_t t_start = clock();
	cout <<  (tree.*member_function)() ;
	clock_t t_end = clock();
	cout << " ��������� �� " << double(t_end - t_start) / CLOCKS_PER_SEC << " ������ \n";
}
//#define BASE_CHECK
//#define DEPTH_CHECK
#define PREFORMANS_CHECK_1


void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	cout << "������� ������ ������: "; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	tree.print();
	cout << endl;
	// minValue
	cout << "����������� �������� � ������: " << tree.minValue() << endl;
	cout << "������������ �������� � ������: " << tree.maxValue() << endl;
	cout << "���-�� ��������� � ������: " << tree.count() << endl;
	cout << "������� ������: " << tree.depth() << endl;
	cout << "------------------------------------------------" << endl;
	UniqueTree u_tree;
	for (int i = 0; i < n; i++)
	{
		u_tree.insert(rand() % 100);
	}
	u_tree.print();
	cout << endl;
	// minValue
	cout << "����������� �������� � ������: " << u_tree.minValue() << endl;
	cout << "������������ �������� � ������: " << u_tree.maxValue() << endl;
	cout << "���-�� ��������� � ������: " << u_tree.count() << endl;
	cout << "������� ������: " << u_tree.depth() << endl;
#endif // BASE_CHECK

#ifdef DEPTH_CHECK
	Tree tree = { 50, 25, 75, 16, 17, 80, 64 };
	//tree.~Tree();
	tree.print();
	cout << "������� ������: " << tree.depth() << endl;
#endif // DEPTH_CHECK

#ifdef PREFORMANS_CHECK_1
	clock_t t_start, t_end;
	int n;
	cout << "������� ������ ������: "; cin >> n;
	Tree tree;
	t_start = clock(); // ������� clock ���������� ��� �� ������ ���������� CPU
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	t_end = clock();
	cout << "������ ��������� �� " << double(t_end - t_start) / CLOCKS_PER_SEC << " ���";
	//tree.print();
	cout << endl;
	// minValue


	/*t_start = clock();
	cout << "����������� �������� � ������: " << tree.minValue() << "\t";
	t_end = clock();
	cout << double(t_end - t_start) / CLOCKS_PER_SEC << " ���" << endl;*/

	measure("����������� �������� � ������:\t", tree, &Tree::minValue);
	measure("������������ �������� � ������:\t", tree, &Tree::maxValue);
	measure("����� ��������� � ������:\t", tree, &Tree::Sum);
	measure("���-�� ��������� � ������:\t", tree, &Tree::count);
	measure("��. ���� ��������� � ������:\t", tree, &Tree::Avg);
	measure("������� ������:\t\t\t", tree, &Tree::depth);

	/*t_start = clock();
	cout << "������������ �������� � ������: " << tree.maxValue() << tab;
	t_end = clock();
	cout << double(t_end - t_start) / CLOCKS_PER_SEC << " ���" << endl;

	t_start = clock();
	cout << "���-�� ��������� � ������: " << tree.count() << tab;
	t_end = clock();
	cout << double(t_end - t_start) / CLOCKS_PER_SEC << " ���" << endl;

	t_start = clock();
	cout << "����� ���������: " << tree.Sum() << tab;
	t_end = clock();
	cout << double(t_end - t_start) / CLOCKS_PER_SEC << " ���" << endl;

	t_start = clock();
	cout << "��.���� ���� ���������: " << tree.Avg() << tab;
	t_end = clock();
	cout << double(t_end - t_start) / CLOCKS_PER_SEC << " ���" << endl;

	t_start = clock();
	cout << "������� ������: " << tree.depth() << tab;
	t_end = clock();
	cout << double(t_end - t_start) / CLOCKS_PER_SEC << " ���" << endl;*/
#endif // PREFORMANS_CHECK

}
