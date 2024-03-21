
#include <iostream>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <string>
#include <omp.h>
using namespace std;

class employee
{
public:
	int id;
	string name;
	int salary;
	string department;
};
class Node
{
public:
	employee data;
	Node* next, * prev;
};
void insert(Node** head, employee data)
{
	Node* temp = new Node();
	temp->data = data;
	temp->next = temp->prev = NULL;
	if (!(*head))
		(*head) = temp;
	else
	{
		temp->next = *head;
		(*head)->prev = temp;
		(*head) = temp;
	}
}

void print(Node* head, int thread, string str)
{
	ofstream data("local result.txt", std::ios::out | std::ios::app);
	Node* temp = head;
	//cout<<"STUDENT\tID\tNAME\tSALARY\tDEPARTMENT"<<endl;

	while (head)
	{

		data << "Hi this is thread : " << thread << " " << str << head->data.id << "\t" << head->data.name << "\t" << head->data.salary << "\t" << head->data.department << endl;
		temp = head;
		head = head->next;
	}
}void file(Node* head)
{
	ofstream data("sorted data.txt", std::ios::out | std::ios::trunc);
	Node* temp = head;
	//cout<<"STUDENT\tID\tNAME\tSALARY\tDEPARTMENT"<<endl;

	while (head)
	{
		data << head->data.id << "\t" << head->data.name << "\t" << head->data.salary << "\t" << head->data.department << endl;
		temp = head;
		head = head->next;
	}
	cout << "completed";
}
void deleteNode(Node** head_ref, Node* del)
{
	/* base case */
	if (*head_ref == NULL || del == NULL)
		return;

	/* If node to be deleted is head node */
	if (*head_ref == del)
		*head_ref = del->next;

	/* Change next only if node to be
	deleted is NOT the last node */
	if (del->next != NULL)
		del->next->prev = del->prev;

	/* Change prev only if node to be
	deleted is NOT the first node */
	if (del->prev != NULL)
		del->prev->next = del->next;

	/* Finally, free the memory occupied by del*/
//	free(del);
	return;
}
void append(Node** head_ref, employee new_data)
{
	/* 1. allocate node */
	Node* new_node = new Node();

	Node* last = *head_ref; /* used in step 5*/

	/* 2. put in the data */
	new_node->data = new_data;

	/* 3. This new node is going to be the last node, so
		make next of it as NULL*/
	new_node->next = NULL;

	/* 4. If the Linked List is empty, then make the new
		node as head */
	if (*head_ref == NULL)
	{
		new_node->prev = NULL;
		*head_ref = new_node;
		return;
	}

	/* 5. Else traverse till the last node */
	while (last->next != NULL)
		last = last->next;

	/* 6. Change the next of last node */
	last->next = new_node;

	/* 7. Make last node as previous of new node */
	new_node->prev = last;

	return;
}
void swap(int* A, int* B)
{
	int temp = *A;
	*A = *B;
	*B = temp;
}

// Split a doubly linked list (DLL) into 2 DLLs of
// half sizes
Node* split(Node* head)
{
	Node* fast = head, * slow = head;
	while (fast->next && fast->next->next)
	{
		fast = fast->next->next;
		slow = slow->next;
	}
	Node* temp = slow->next;
	slow->next = NULL;
	return temp;
}

Node* merge(Node* first, Node* second, int choice)
{
	// If first linked list is empty
	if (!first)
		return second;

	// If second linked list is empty
	else if (!second)
		return first;

	// Pick the smaller value
	else
	{
		if (choice == 1) {
			for (int i = 0; i < size(first->data.name); i++) {
				if (first->data.name[i] == second->data.name[i])
					continue;

				else if (first->data.name[i] < second->data.name[i]) {
					first->next = merge(first->next, second, choice);
					first->next->prev = first;
					first->prev = NULL;
					return first;
				}
				else
				{
					second->next = merge(first, second->next, choice);
					second->next->prev = second;
					second->prev = NULL;
					return second;
				}
			}
		}
		else if (choice == 3) {
			if (first->data.salary < second->data.salary)
			{
				first->next = merge(first->next, second, choice);
				first->next->prev = first;
				first->prev = NULL;
				return first;
			}
			else
			{
				second->next = merge(first, second->next, choice);
				second->next->prev = second;
				second->prev = NULL;
				return second;
			}
		}
		else if (choice == 2) {
			if (first->data.id < second->data.id)
			{
				first->next = merge(first->next, second, choice);
				first->next->prev = first;
				first->prev = NULL;
				return first;
			}
			else
			{
				second->next = merge(first, second->next, choice);
				second->next->prev = second;
				second->prev = NULL;
				return second;
			}
		}
		else if (choice == 4) {


			if (first->data.department <= second->data.department) {
				first->next = merge(first->next, second, choice);
				first->next->prev = first;
				first->prev = NULL;
				return first;
			}
			else
			{
				second->next = merge(first, second->next, choice);
				second->next->prev = second;
				second->prev = NULL;
				return second;
			}

		}
	}

}
Node* mergeSort(Node* head, int choice)
{
	if (!head || !head->next)
		return head;
	Node* second = split(head);

	// Recur for left and right halves
	head = mergeSort(head, choice);
	second = mergeSort(second, choice);

	// Merge the two sorted halves
	return merge(head, second, choice);
}
int main()
{
	vector <employee> emp;
	employee e;
	ifstream infile("employee.txt");
	if (!infile.fail())
	{
		while (infile >> e.id)
		{

			infile >> e.name;
			infile >> e.salary;
			infile >> e.department;
			emp.push_back(e);
		}
	}

	/*for (int i = 0; i < emp.size(); i++)
	{
		cout << emp[i].id << " " << emp[i].name << " " << emp[i].salary << " " << emp[i].department << endl;
	}*/
	//cout << "\n\n\n" << emp.size();
	Node* head = NULL;
	Node* head2 = NULL;
	int ListSize;
	ListSize = emp.size();
	double p_time = omp_get_wtime();
		for (int i = 0; i < ListSize; i++)
			insert(&head, emp[i]);
	///*cout << "time for parallel is: " << omp_get_wtime() - p_time << endl;
	//double s_time = omp_get_wtime();
	//for (int i = 0; i < ListSize; i++)
	//	insert(&head2, emp[i]);
	//cout << "time for serial is: " << omp_get_wtime() - s_time << endl;*/
	//print(head2);
	//print(head);
	int choice;
	cout << "\n1. by name\n2. by id\n3. by salary\n4. by department\n";
	cin >> choice;
	int divider = 2;
	int threadsize = 1;
	double wtime = omp_get_wtime();
	float sum=0;
	while (threadsize > 0)
	{
		Node* temp1 = NULL;
		//Node* headd = NULL;
		string str = "";
		int threadnum = 0;

#pragma omp parallel reduction(+:sum) num_threads(threadsize) shared(head,choice) private(temp1,threadnum,str)
		{

			Node* temp1 = NULL;
			double wtime;
#pragma omp for schedule(static)
			for (int i = 0; i < ListSize; i++)
			{
#pragma omp critical
				{
					int threadnum = omp_get_thread_num();
					insert(&temp1, head->data);
					if (threadsize == ListSize / divider)
						cout << "thread id: " << threadnum << " inserted record with id: " << head->data.id << endl;
					deleteNode(&head, head);
				}
			}

			if (divider == 2)
			{



#pragma omp critical
				{
					str = " and I have data : ";
					print(temp1, omp_get_thread_num(), str); cout << endl;
				}
			}
			wtime = omp_get_wtime();

			temp1 = mergeSort(temp1, choice);
			wtime = omp_get_wtime() - wtime;
			sum +=wtime;
			if (divider == 2)
			{


#pragma omp critical
				{
					str = " and I sorted data : ";
					print(temp1, omp_get_thread_num(), str);
				}
			}


			double start = omp_get_wtime();
#pragma omp for schedule(static)
			for (int i = 0; i < ListSize; i++)
			{
#pragma omp critical
				{
					append(&head, temp1->data);
					deleteNode(&temp1, temp1);
					//cout << endl; print(head); cout << endl;  //Remove Bar to observe cycles :)
				}
			}


		}

		//cout << endl; print(head); cout << endl; //Remove Bar to observe intermediate result after each loop :)

		if (threadsize == 1)
			break;

		divider *= 2;
		threadsize = (ListSize / divider) + 1;
	}
	cout << sum << endl;
	file(head);
}
