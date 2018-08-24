#include <iostream>
#define SZ 10

struct Element {
    Element() {
        name = new char[SZ];
        name[0] = '\0';
    }
    
    Element(const Element &x) {
        priority = x.priority;
        name = new char[SZ];
        strcpy(name, x.name);
    }
    
//    Element &operator =(const Element &c) {
//        priority = c.priority;
//        strcpy(name, c.name);
//        return *this;
//    }
    
    ~Element() {delete[] name;}
    int priority;
    char *name;
};

static const Element f;

class Tree {
public:
    Tree(): space(0) {}
    Tree &insert(const char *n, int p);
    Element deleteMin();
    void makeNull() {space = 0;}
    void printTree() const;
    int checkEmpty() const {return space == 0;}
private:
    static const int size = 15;
    Element arr[size];
    int space; // первый свободный
    void swap(int i, int j);
    int smallest(int i, int j);
    int searchValue(char *n) const;
};

int Tree::searchValue(char *n) const {
    for(int i = 0; i < space; i++)
        if(!strcmp(arr[i].name, n))
            return 1;
    return 0;
}

void Tree::swap(int i, int j) {
    Element temp;
    temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
    temp.name = NULL;
}

int Tree::smallest(int leftSon, int rightSon) { // возвращает элемент массива, меньший по приоритету
    if (leftSon >= space) // если левый сын больше либо равен space, то сыновей нет
        return -1;
    if (rightSon == space) // если правый сын равен space (при условии выше, что левый меньше space), значит, что его не существует, возвр. левого сына
        return leftSon;
    
    return arr[leftSon].priority < arr[rightSon].priority ? leftSon : rightSon; // если оба существуют, выбираем из них
}

Tree &Tree::insert(const char *n, int p) {
    if(checkEmpty()) { // если пусто, то добавляем корень
        arr[space].priority = p;
        strcpy(arr[space].name, n);
        space++;
        return *this;
    }
    
    arr[space].priority = p; // добавляем новый эл-т
    strcpy(arr[space].name, n);
    int i = space, parent = (i - 1)/2;
    
    while (arr[parent].priority > arr[i].priority) { // начинаем поднимать его наверх при необходимости
        swap(parent, i);
        i = parent;
        parent = (i - 1)/2;
    }
    
    space++;
    return *this;
}

Element Tree::deleteMin() {
    if (checkEmpty())
        return f;
    
    if (space == 1) {
        Element temp = arr[--space];
        return temp;
    }
    
    Element temp = arr[0];
    
    swap(0, --space); // меняем самый правый эл-т с корнем
    
    int i = 0, leftSon = 1, rightSon = 2, s;
    
    s = smallest(leftSon, rightSon);
    
    while (arr[i].priority > arr[s].priority && s != -1) { // начинаем его менять с его минимальными сыновьями, если это необходимо
        swap(i, s);
        i = s;
        leftSon = i*2 + 1;
        rightSon = i*2 + 2;
        
        s = smallest(leftSon, rightSon);
    }
    
    return temp;
}

void Tree::printTree() const {
    for(int i = 0; i < space; i++)
        std::cout << arr[i].priority << "(" << arr[i].name << ") ";
    std::cout << std::endl;
}

int main() {
    Tree x;
    
    x.insert("a", 2);
    x.insert("b", 4);
    x.insert("c", 8);
    x.insert("d", 3);
    x.insert("e", 7);
    x.insert("f", 5);
    x.insert("g", 9);
    x.insert("h", 6);
    
    x.printTree();
    
    x.deleteMin();
    
    x.printTree();
    
    x.deleteMin();
    
    x.printTree();
    
    x.deleteMin();
    
    x.printTree();
    
    x.deleteMin();
    
    x.printTree();
    
    x.deleteMin();
    
    x.printTree();
    
    x.deleteMin();
    
    x.printTree();
    
    x.deleteMin();
    
    x.printTree();
    
    x.deleteMin();
    
    x.printTree();
}
