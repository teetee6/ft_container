#include <iostream>

class Obj {
    public:
    Obj() { std::cout << "부모생성" << std::endl;}
    virtual ~Obj() { std::cout << "부모삭제" << std::endl;}
};

class Child : public Obj {
    public:
    Child() { std::cout << "자식셍성" << std::endl;}
     ~Child() { std::cout << "자식삭제" << std::endl;}
};

int main()
{
    Obj *c = new Child();
    delete(c);
}