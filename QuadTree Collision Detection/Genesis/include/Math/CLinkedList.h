#pragma once

namespace Genesis
{
	namespace math
	{
		//A Doubly linked list. Holds the chain of nodes together
		template <typename T>
		class CLinkedList
		{
			private:
				//Nodes are used to hold the data given and hold pointers to the next node in the list
				template <typename T>
				class CLinkedNode
				{
					private:
						T m_Data;

						CLinkedList<T>* mp_Parent;	//Previous Node
						CLinkedNode<T>* mp_Next;	//Next node in list (The child node)

													//Prevent copy constructor and Assignment operator use
						CLinkedNode<T>(const CLinkedNode&);
						CLinkedNode<T>& operator=(const CLinkedNode&);

					public:
						CLinkedNode(T data)
						{
							m_Data = data;
							mp_Parent = nullptr;
							mp_Next = nullptr;
						}
						~CLinkedNode() {}

						//ACCESSORS
						//--------------------------

						T GetData()
						{
							mp_Next = nullptr;
							return m_Data;
						}
						CLinkedNode<T>* GetParent() { return mp_Parent; }
						CLinkedNode<T>* GetNext() { return mp_Next; }

						//--------------------------


						//MUTATORS
						//----------------------------

						void SetData(T data) { m_Data = data; }
						void SetParent(CLinkedNode<T>* parent) { mp_Parent = parent; }
						void SetNext(CLinkedNode<T>* next) { mp_Next = next; }

						//----------------------------
				};

				CLinkedNode* mp_Head;	//Head Node of the list

				//Prevent copy constructor and Assignment operator use
				CLinkedList<T>(const CLinkedList&);
				CLinkedList<T>& operator=(const CLinkedList&);
			public:
				//CONSTRUCTOR / DESTRUCTOR
				//---------------------------

				CLinkedList()
				{
					mp_Head = nullptr;
				}
				~CLinkedList()
				{
					//Delete all nodes in chain
					Empty();
				}

				//---------------------------

				//Creates a new node at the end of the list chain and inserts the data
				void Insert(T data)
				{
					if (!mp_Head)
					{
						mp_Head = new CLinkedNode<T>(data);
						return;
					}

					//Move down the chain until we get to the end
					CLinkedNode<T>* tmp = mp_Head;
					CLinkedNode<T>* prevTmp = mp_Head;
					while (tmp->GetNext())
					{
						prevTmp = tmp;
						tmp = tmp->GetNext();
					}

					CLinkedNode<T>* newNode = new CLinkedNode<T>(data);
					newNode->SetParent(prevTmp);
					tmp->SetNext(newNode);
				}

				//Remove the end node in the list
				void RemoveLast()
				{
					if (!mp_Head) return;	//List is already empty
					if (!mp_Head->GetNext())
					{
						//Head is only element in list
						delete(mp_Head);
						mp_Head = nullptr;
						return;
					}

					CLinkedNode<T>* tmp = mp_Head;
					CLinkedNode<T>* prevTmp = mp_Head;
					while (tmp->GetNext())
					{
						prevTmp = tmp;
						tmp = tmp->GetNext();
					}
					
					//Remove element
					prevTmp->SetNext(nullptr);
					delete(tmp);
				}


				//Get all data in the Linked list, as one list
				std::vector<T> GetAll()
				{

				}


				//Empty's the linked list, de-allocating all memory used for the nodes
				void Empty()
				{
					if (!mp_Head) return;	//No needs in list

					//Keep removing the last element in list, until list is empty
					while (!mp_Head)
					{
						RemoveLast();
					}
				}
		};
	}
}