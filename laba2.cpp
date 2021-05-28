#include <iostream>
#include <ctime> // содержит time()
#include <chrono>

using namespace std;

typedef chrono::high_resolution_clock Clock;
typedef chrono::duration<double> sec;
Clock::time_point timeStart;
Clock::time_point timeEnd;

int countElements = 0;

struct Node                             
{
	int data;                            
	Node *Next, *Prev;                
};

class List                             
{
	Node *Head, *Tail;                 //Указатели на адреса начала списка и его конца
public:
	List() :Head(NULL), Tail(NULL) {};    //Инициализируем адреса как пустые
	~List();                           
	void Show();                       //Отображение списка на экран
	void Add(int x);                   //Добавлениу элементов в список
	void AddTail(int n);			   //Добавление в конец списка
	void Insert();					   //Вставка элемента
	void Del();						   //Удаление элемента
	void Del(int x);				   //Удаление элемента
	Node* GetElem();				   // Получить элемент списка
};

List::~List()                           //Деструктор
{
	while (Head)                       
	{
		Tail = Head->Next;             //Резервная копия адреса следующего звена списка
		delete Head;                   
		Head = Tail;                   //Смена адреса начала на адрес следующего элемента
	}
}

void List::Add(int x)
{
	Node *temp = new Node;               
	temp->Next = NULL;                   
	temp->data = x;                       

	if (Head != NULL)                  
	{
		temp->Prev = Tail;               //Указываем адрес на предыдущий элемент в соотв. поле
		Tail->Next = temp;               //Указываем адрес следующего за хвостом элемента
		Tail = temp;                     //Меняем адрес хвоста
	}
	else //Если список пустой
	{
		temp->Prev = NULL;               
		Head = Tail = temp;              //Голова=Хвост=элемент
	}
}

void List::Show()
{
	Node *temp = Head;                   
	while (temp != NULL)             
	{
		cout << temp->data << " ";        //Выводим каждое считанное значение на экран
		temp = temp->Next;             //Смена адреса на адрес следующего элемента
	}
	cout << "\n";
}

List *GenerateLst(List *lst) {

	char option;

	cout << "a)List of random numbers\n" << "b)Enter numbers into an array\n" << "Enter: ";
	cin >> option;

	if (option == 'a') {

		int count = 0;
		cout << "Enter the number of elements: ";
		cin >> count;
		timeStart = Clock::now();
		for (int i = 0; i < count; i++) {
			lst->Add(rand() % 99);
		}
		timeEnd = Clock::now();

		countElements = count;

		cout << endl;
		cout << "Generation time: " << sec(timeEnd - timeStart).count() << " s." << endl;
	}
	else {

		int count = 0;
		int value = 0;
		while (cin >> value)
		{
			char c = static_cast<char>(cin.get());
			count++;
			if (isdigit(c) || c == '-' || c == '+')
			{
				//nope
			}
			else if (c == ' ')
			{
				lst->Add(value);
				continue;
			}
			else
			{
				lst->Add(value);
				break;
			}
		}
		countElements = count;
	}

	return lst;
}
void List::AddTail(int n)
{
	Node * temp = new Node;
	// Следующего нет
	temp->Next = 0;

	temp->data = n;
	temp->Prev = Tail;

	// Если элементы есть?
	if (Tail != 0)
		Tail->Next = temp;

	if (countElements == 0)
		Head = Tail = temp;
	else
		Tail = temp;

	countElements++;
}
void List::Insert()
{
	cout << "\nInsert element.\n";

	int pos;
	cout << "Input position: ";
	cin >> pos;

	// Позиция от 1 до Count?
	if (pos < 1 || pos > countElements + 1)
	{
		cout << "Incorrect position !!!\n";
		return;
	}

	// Если вставка в конец списка
	if (pos == countElements + 1)
	{
		int data;
		cout << "Input new number: ";
		cin >> data;
		timeStart = Clock::now();
		Add(data); // Добавление в конец списка
		timeEnd = Clock::now();
		cout << "\nTime to add an item: " << sec(timeEnd - timeStart).count() << " s." << endl;
		return;
	}
	else if (pos == 1)
	{
		int data;
		cout << "Input new number: ";
		cin >> data;
		timeStart = Clock::now();
		AddTail(data); // Добавление в начало списка
		timeEnd = Clock::now();
		cout << "\nTime to add an item: " << sec(timeEnd - timeStart).count() << " s." << endl;
	}

	int i = 1; // Счетчик
	Node * temp = new Node;
	cout << "Input new number: "; cin >> temp->data;

	timeStart = Clock::now();

	Node *Ins = Head;

	while (i < pos)
	{
		// Доходим до элемента, 
		// перед которым вставляемся
		Ins = Ins->Next;
		i++;
	}

	// Доходим до элемента, 
	// который предшествует
	Node * PrevIns = Ins->Prev;

	// настройка связей
	if (PrevIns != 0 && countElements != 1)
		PrevIns->Next = temp;

	temp->Next = Ins;
	temp->Prev = PrevIns;
	Ins->Prev = temp;

	countElements++;
	timeEnd = Clock::now();
	cout << "\nTime to add an item: " << sec(timeEnd - timeStart).count() << " s." << endl;
}

void List::Del()
{
	int var = -1;

	cout << "\nRemoving an item.\n";

	cout << "\n1) By position\n"
		<< "2) By value\n";
	cout << endl;
	cout << "Enter: "; cin >> var;

	if (var == 1) {
		int pos;
		cout << "Input position: "; cin >> pos;

		timeStart = Clock::now();
		if (pos < 1 || pos > countElements) // Неверная позиция
		{
			cout << "Incorrect position !\n";
			timeEnd = Clock::now();
			return;
		}

		int i = 1; // Счетчик
		Node *Del = Head;
		while (i < pos) // Доходим до элемента, который удаляется
		{
			Del = Del->Next;
			i++;
		}

		Node * PrevDel = Del->Prev; // Доходим до элемента, который предшествует удаляемому
		Node * AfterDel = Del->Next; // Доходим до элемента, который следует за удаляемым

		if (PrevDel != 0 && countElements != 1) // Если удаляем не голову
			PrevDel->Next = AfterDel;

		if (AfterDel != 0 && countElements != 1) // Если удаляем не хвост
			AfterDel->Prev = PrevDel;

		if (pos == 1) // Удаляются крайние?
			Head = AfterDel;
		if (pos == countElements)
			Tail = PrevDel;

		delete Del; // Удаление элемента
		timeEnd = Clock::now();
		cout << "\nTime to remove an item: " << sec(timeEnd - timeStart).count() << " s." << endl;
	}
	else {
		int i = 1; // Счетчик
		int count = 1; // Счетчик
		int value;
		cout << "Input value: "; cin >> value;

		timeStart = Clock::now();
		Node *Del = Head;
		for (int i = 1; i < countElements+1; i++) {

			if (Del->data == value) {
				count = i;
			}
			Del = Del->Next;
		}
		if (count < 0) // Неверное значение
		{
			cout << "Incorrect value!\n";
			timeEnd = Clock::now();
			return;
		}

		Del = Head;
		while (i < count) // Доходим до элемента, который удаляется
		{
			Del = Del->Next;
			i++;
		}

		Node *PrevDel = Del->Prev; // Доходим до элемента, который предшествует удаляемому
		Node *AfterDel = Del->Next; // Доходим до элемента, который следует за удаляемым

		if (PrevDel != 0 && countElements != 1) // Если удаляем не голову
			PrevDel->Next = AfterDel;

		if (AfterDel != 0 && countElements != 1) // Если удаляем не хвост
			AfterDel->Prev = PrevDel;

		if (count == 1) // Удаляются крайние?
			Head = AfterDel;
		if (count == countElements)
			Tail = PrevDel;

		delete Del; // Удаление элемента
		timeEnd = Clock::now();
		cout << "\nTime to remove an item: " << sec(timeEnd - timeStart).count() << " s." << endl;
	}

	countElements--;
}
void List::Del(int pos)
{
	int i = 1;
	Node *Del = Head;

	while (i < pos)
	{
		Del = Del->Next;
		i++;
	}

	Node *PrevDel = Del->Prev;
	Node *AfterDel = Del->Next;

	if (PrevDel != 0 && countElements != 1)
		PrevDel->Next = AfterDel;
	if (AfterDel != 0 && countElements != 1)
		AfterDel->Prev = PrevDel;

	if (pos == 1)
		Head = AfterDel;
	if (pos == countElements)
		Tail = PrevDel;
	delete Del;

	countElements--;
}

Node *List::GetElem()
{
	int var = -1;

	cout << "\n1) By position\n"
		<< "2) By value\n";
	cout << endl;
	cout << "Enter: "; cin >> var;

	if (var == 1) {
		int pos;
		cout << "Input position: "; cin >> pos;
		timeStart = Clock::now();
		Node *temp = Head;

		if (pos < 1 || pos > countElements) // Неверная позиция
		{
			cout << "Incorrect position!\n";
			timeEnd = Clock::now();
			return 0;
		}

		int i = 1;
		while (i < pos && temp != 0) // Ищем нужный нам элемент
		{
			temp = temp->Next;
			i++;
		}

		timeEnd = Clock::now();
		cout << "\nTime to remove an item: " << sec(timeEnd - timeStart).count() << " s." << endl;
		if (temp == 0)
			return 0;
		else
			return temp;
	}
	else {
		int count = -1; // Счетчик
		int value;
		int i = 1;
		cout << "Input value: "; cin >> value;

		timeStart = Clock::now();
		Node *temp = Head;

		for (int i = 1; i < countElements + 1; i++) {

			if (temp->data == value) {
				count = i;
			}
			temp = temp->Next;
		}

		if (count < 0) // Неверное значение
		{
			cout << "Incorrect value!\n";
			timeEnd = Clock::now();
			return 0;
		}

		temp = Head;
		while (i < count) // Доходим до элемента, который удаляется
		{
			temp = temp->Next;
			i++;
		}
		timeEnd = Clock::now();
		cout << "\nTime to remove an item: " << sec(timeEnd - timeStart).count() << " s." << endl;

		if (temp == 0)
			return 0;
		else
			return temp;
	}
}

int *GenerateArr(int *ar) {

	//srand(time(NULL));

	char option;

	cout << "a)Array of random numbers\n" << "b)Enter numbers into an array\n" << "Enter: ";
	cin >> option;

	if (option == 'a') {

		int count = 0;
		cout << "Enter the number of elements: ";
		cin >> count;
		timeStart = Clock::now();
		ar = new int[count];
		for (int i = 0; i < count; i++) {
			ar[i] = rand() % 99; 
		}
		timeEnd = Clock::now();

		countElements = count;

		cout << endl;
		cout << "Generation time: " << sec(timeEnd - timeStart).count() << " s." << endl;
	}
	else {
		int count = 0; 
		while (cin >> ar[count])
		{
			char c = static_cast<char>(cin.get());
			count++;
			if (isdigit(c) || c == '-' || c == '+')
			{

			}
			else if (c == ' ')
			{
				continue;
			}
			else
			{
				break;
			}
		}
		countElements = count;
	}

	for (int i = 0; i <= countElements - 1; i++) {
		cout << ar[i] << " ";
	}

	return ar;
}

int *AddElementByIndex(int *ar) {

	int index = 0;
	int value = 0;

	int *arrNew = new int[countElements + 1];

	cout << "Enter the index: "; cin >> index;

	if (index <= countElements - 1) {
		cout << "Enter value: "; cin >> value;
		timeStart = Clock::now();
		for (int i = 0; i <= index - 1; i++) {
			arrNew[i] = ar[i];
		}
		arrNew[index] = value;
		for (int i = index + 1; i <= countElements+1; i++) {
			arrNew[i] = ar[i-1];
		}


		countElements++;
		timeEnd = Clock::now();

		cout << "\nTime to add an item: " << sec(timeEnd - timeStart).count() << " s." << endl;

		return arrNew;
	}
	else {
		cout << "Element missing!\n";
		return ar;
	}
}

int *DeliteElement(int *ar) {

	int var = -1;
	int index = -1;
	int value = 0;
	int *arrNew = new int[countElements - 1];

	cout << endl;
	cout << "\n1) By index\n"
		<< "2) By value\n";
	cout << endl;
	cout << "Enter: "; cin >> var;
	if (var == 1) {

		cout << "Enter the index: "; cin >> index;

		if (index <= countElements - 1 && index >= 0) {
			timeStart = Clock::now();
			for (int i = 0; i < index; i++) {
				arrNew[i] = ar[i];
			}
			for (int i = index + 1; i <= countElements - 1; i++) {
				arrNew[i - 1] = ar[i];
			}

			countElements--;

			timeEnd = Clock::now();
			cout << "\nTime to remove an item: " << sec(timeEnd - timeStart).count() << " s." << endl;
			return arrNew;
		}
		else {
			cout << "Element missing!\n";
			return ar;
		}
	}
	else {
		cout << "Enter the value: "; cin >> value;

		timeStart = Clock::now();
		for (int i = 0; i < countElements; i++) {
			if (value == ar[i]) {
				index = i;
			}
		}

		if (index >= 0) {
			for (int i = 0; i < index; i++) {
				arrNew[i] = ar[i];
			}
			for (int i = index + 1; i <= countElements - 1; i++) {
				arrNew[i - 1] = ar[i];
			}

			countElements--;

			timeEnd = Clock::now();
			cout << "\nTime to remove an item: " << sec(timeEnd - timeStart).count() << " s." << endl;
			return arrNew;
		}
		else {
			cout << "Item not found!\n";
			return ar;
		}
	}
}

int *DeliteElements(int *ar, int index) {

	int *arrNew = new int[countElements - 1];

	for (int i = 0; i < index; i++) {
		arrNew[i] = ar[i];
	}
	for (int i = index + 1; i <= countElements - 1; i++) {
		arrNew[i - 1] = ar[i];
	}

	countElements--;
	return arrNew;
}

int *DeliteOddArray(int *arrr) {
	timeStart = Clock::now();

	int count = countElements;
	int i = 0;
	for (int j = 0; j < count + 1; j++) {
		if (j % 2 == 0) {
			arrr = DeliteElements(arrr, j - i);
			i++;
		}
	}
	timeEnd = Clock::now();
	cout << "\nTime to remove an odd item: " << sec(timeEnd - timeStart).count() << " s." << endl;
	return arrr;
}

int GetElement(int *ar) {

	int var = -1;
	int *element = new int;
	int index = -1;
	int value = 0;

	cout << "\n1) By index\n"
		<< "2) By value\n";
	cout << endl;
	cout << "Enter: "; cin >> var;

	if (var == 1) {
		cout << "Enter the index: "; cin >> index;
		timeStart = Clock::now();
		if (index <= countElements - 1 && index >= 0) {
			*element = ar[index];
		}
	}
	else {
		cout << "Enter the value: "; cin >> value;
		timeStart = Clock::now();
		for (int i = 0; i < countElements; i++) {
			if (value == ar[i]) {
				index = i;
			}
		}

		if (index >= 0) {
			*element = ar[index];
		}
		else {
			cout << "Item not found!\n";
		}
	}

	timeEnd = Clock::now();
	cout << "\nTime to get an item: " << sec(timeEnd - timeStart).count() << " s." << endl;
	return *element;
}

void PrintArray(int *ar) {
	cout << "Array: ";
	for (int i = 0; i <= countElements - 1; i++) {
		cout << ar[i] << " ";
	}
}

int main()
{
	int varOne = -1;
	do {
		cout << "1) Array\n"
			<< "2) List\n";
		cout << endl;
		cin >> varOne;

		if (varOne == 1) {
			int element = -1;
			int var = -1;
			int *arr = new int[1000];        // выделяем память под массив

			arr = GenerateArr(arr);


			do {
				cout << endl;
				cout << "\n1) Insert item\n"
					<< "2) Remove item\n"
					<< "3) Get the item\n"
					<< "4) Removing odd items\n"
					<< "0) Exit\n";
				cout << endl;

				cin >> var;

				if (var == 1) {
					cout << "Adding an item by index\n";
					arr = AddElementByIndex(arr);
					PrintArray(arr);
				}
				else if (var == 2) {
					cout << "Remove item\n";
					arr = DeliteElement(arr);
					PrintArray(arr);
				}
				else if (var == 3) {
					cout << "Get item\n";
					element = GetElement(arr);
					cout << "Element: " << element;
				}
				else if (var == 4) {
					cout << "Removing odd items\n";
					arr = DeliteOddArray(arr);
					PrintArray(arr);
				}
				else {
					break;
				}

			} while (var != 0);
		}
		else if (varOne == 2) {
			int var = -1;

			List *lst = new List;

			lst = GenerateLst(lst);
			lst->Show();

			do {
				cout << endl;
				cout << "\n1) Insert item\n"
					<< "2) Remove item\n"
					<< "3) Get the item\n"
					<< "4) Removing odd items\n"
					<< "0) Exit\n";
				cout << endl;

				cin >> var;

				if (var == 1) {
					cout << "Adding an item by index\n";
					lst->Insert();
					lst->Show();
				}
				else if (var == 2) {
					cout << "Remove item\n";
					lst->Del();
					lst->Show();
				}
				else if (var == 3) {
					cout << "Get item\n";
					cout << "Element: " << lst->GetElem();
				}
				else if (var == 4) {
					cout << "Removing odd items\n";
					timeStart = Clock::now();
					int count = countElements;
					int i = 0;
					for (int j = 1; j < count+1; j++) {
						if (j % 2 == 1) {
							lst->Del(j-i);
							i++;
						}
					}
					timeEnd = Clock::now();
					cout << "\nTime to remove an odd item: " << sec(timeEnd - timeStart).count() << " s." << endl;
					lst->Show();
				}
				else {
					break;
				}

			} while (var != 0);
		}
	} while (varOne > 0);
}
