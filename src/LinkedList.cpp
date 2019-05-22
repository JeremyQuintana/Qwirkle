
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
}

// Returns size of linked list
int LinkedList::size()
{
    return this->count;
}

// Deletes everything inside linked list
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

// Returns tile at index i
Tile* LinkedList::get(int i)
{
    int listCount = 0;
    Node* temp = head;

    // Tile result; //In case value is invalid returns 0 for both components
    // result.colour = 0;
    // result.shape = 0;
    if (i < count)
    {
        while (listCount < i) //Indexing starts at 0
        {
            temp = temp->next;

            listCount++;
        }

        // result = *(temp->tile);
    }
    return temp->tile; //Dereferences tile pointer
}

// Add tile to front of linked list
void LinkedList::addFront(Tile* data)
{
    Node* temp = new Node(data, nullptr);

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

// Adds tile to back
void LinkedList::addBack(Tile* data)
{
    Node* temp = new Node(data, nullptr);

    if (count == 0){
        head = temp;
        tail = temp;
    } else {
        tail->next = temp;
        tail = temp;
    }

    count++; //Update size counter
}

// Deletes tile at front
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

// Deletes tile at back
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

// Deletes tile in list that matches given tile
void LinkedList::deleteTile(Tile data) //Doesn't check if Tile is in list
{
    Node* temp = head;
    Node* prev = nullptr; //Keeps track of last node
    bool deleted = false;

    while (temp != nullptr && deleted == false)
    {
        if (((temp->tile)->colour == data.colour)
                && ((temp->tile)->shape == data.shape)){
            if (temp == head) head = head->next;
            else prev->next = temp->next;
            deleted = true;
            delete temp;
            count--;
        } else {
            prev = temp;
            temp = temp->next;
        }
    }
}

// Checks if tile is in list
bool LinkedList::inList(Tile data) //Returns true if tile is in list
{
    bool result = false;
    Node* temp = head;

    while (temp != nullptr)
    {
        if ((temp->tile->colour == data.colour)
                && (temp->tile->shape == data.shape))
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
    int tempCounter = count; // How many more elements need to be sent to back
    int listCount = 0; // Just for iterating through list
    int tempIndex; // Temporary index of tile in list

    Node* temp; // Current node being moved
    Node* prev; // Previous node for reference

    std::random_device engine;

    while (tempCounter > 0)
    {
        listCount = 0; // Reset variable
        temp = head;
        prev = head;

        std::uniform_int_distribution<int> uniform_int(0, tempCounter);

        tempIndex = uniform_int(engine); // Get random temp index

        // Finds the generated index in list
        while (listCount < tempIndex-1) //Indexing starts at 0
        {
            prev = temp;
            temp = temp->next;

            listCount++;
        }

        if (temp == tail)
        {
            // No operations need to be done
        }
        else if (temp == head)
        {
            head = temp->next;
            tail->next = temp;
            temp->next = nullptr;

            tail = temp;
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

std::string LinkedList::listToString()
{
    Node* temp = head;

    std::string listStr = (temp->tile)->getValue();

    for (int i = 0; i < (this->count)-1; i++)
    {
        temp = temp->next;
        listStr.append(",");
        listStr.append((temp->tile)->getValue());
    }

    return listStr;
}
