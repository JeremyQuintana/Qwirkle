
#include "LinkedList.h"

LinkedList::LinkedList()
{
    head = nullptr;
    tail = nullptr;
    count = 0;
}

LinkedList::~LinkedList()
{
    clear();
    delete head;
    delete tail;
}

int LinkedList::size()
{ 
    return this->count;
}

void LinkedList::clear()
{
    Node* temp = head;

    while (temp != nullptr)
    {
        Node* saved = temp->next;
        delete temp;
        temp = saved;
    }

    head = nullptr;
    tail = nullptr;
    count = 0;
}

Tile LinkedList::get(int i)
{
    int listCount = 0;
    Node* temp = head;

    Tile result; //In case value is invalid returns 0 for both components
    result.colour = 0;
    result.shape = 0;

    if (i <= this->count)
    {
        while (listCount < i) //Indexing starts at 0
        {
            temp = temp->next;

            listCount++;
        }

        result = *(temp->tile);
    }

    return result; //Dereferences tile pointer
}

void LinkedList::addFront(Tile data)
{
    Node* temp = new Node(&data, nullptr);

    if (head == nullptr)
    {
        head = temp;
    }
    else
    {
        temp->next = head;
        head = temp;
    }

    if (head->next == nullptr)
    {
        tail = head;
    }

    count++; //Update size counter
}

void LinkedList::addBack(Tile data)
{
    Node* temp = new Node(&data, nullptr);

    if (tail == nullptr)
    {
        tail = temp;
    }
    else
    {
        temp = tail->next;
        tail = temp;
    }

    if (head == nullptr)
    {
        head = tail;
    }

    count++; //Update size counter
}

void LinkedList::deleteFront()
{
    if (this->count > 0) //Check if list is empty, can improve later
    {
        Node* temp = head->next;
        delete head;

        head = temp;

        count--; //Update size counter
    }
}

void LinkedList::deleteBack()
{
    if (this->count > 0) //Check if list is empty, can improve later
    {
        Node* temp = head;

        delete tail;

        while (temp->next != nullptr) //Find new tail
        {
            temp = temp->next;
        }

        tail = temp;

        count--; //Update size counter
    }
}

void LinkedList::deleteTile(Tile data) //Doesn't check if Tile is in list
{
    Node* temp = head;
    Node* prev = nullptr; //Keeps track of last node

    while (temp != nullptr)
    {
        if ((temp->tile->colour == data.colour) && (temp->tile->shape == data.shape))
        {
            if (temp == head)
            {
                head = temp->next;
                delete temp;
            }
            else
            {
                prev->next = temp->next;
                delete temp;
            }

            return;
        }

        prev = temp;
        temp = temp->next;
    }
}

bool LinkedList::inList(Tile data) //Returns true if tile is in list
{
    bool result = false;
    Node* temp = head;

    while (temp != nullptr)
    {
        if ((temp->tile->colour == data.colour) && (temp->tile->shape == data.shape))
        {
            result = true;
        }

        temp = temp->next;
    }

    return result;
}

//Shuffles contents of list
void LinkedList::shuffle()
{
    int tempCounter = count;
    int listCount = 0; // Just for iterating through list
    int tempIndex;
    
    Node* temp;
    Node* prev;

    std::random_device engine;

    while (tempCounter > 0)
    {   
        listCount = 0; // Reset variable
        temp = head;
        prev = head;

        std::uniform_int_distribution<int> uniform_int(0, tempCounter);

        tempIndex = uniform_int(engine);

        // Finds the generated index
        while (listCount < tempIndex) //Indexing starts at 0
        {
            prev = temp;
            temp = temp->next;

            listCount++;
        }

        if (temp == head)
        {
            head = temp->next;
            tail->next = temp;
            temp->next = nullptr;

            tail = temp;
        }
        else if (temp == tail)
        {
            // No operations need to be done
        }
        else
        {
            tail->next = temp;
            prev->next = temp->next;
            temp->next = nullptr;

            tail = temp;
        }

        tempCounter--;
    }

}

