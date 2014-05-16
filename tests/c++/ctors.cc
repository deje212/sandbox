#include <iostream>
#include <vector>

using namespace std;

class Integer {
public:
  Integer() : x(0) { cout << "Integer()\n"; }
  Integer(int i) : x(i) { cout << "Conv Integer(" << x << ")\n"; }
  Integer(const Integer& i) { x = i.x; cout << "Copy of Integer(" << i.x << ")\n"; }
  ~Integer() { cout << "Destructor\n"; }

  Integer& operator=(int i) { x = i; cout << "operator=()\n"; return *this; }

  int get() { return x; }

private:
  int x;
};

int main()
{
  cout << "\nvector and iterator declaration\n";
  vector<Integer> arrayOfIntegers;
  vector<Integer>::iterator i;

  cout << "push 1\n";
  arrayOfIntegers.push_back(1);
  cout << "push 2\n";
  arrayOfIntegers.push_back(2);
  cout << "push 3\n";
  arrayOfIntegers.push_back(3);

  cout << "\nShow array\n";
  int j = 0;
  for (i = arrayOfIntegers.begin(); i != arrayOfIntegers.end(); i++)
    cout << "v[" << j++ << "] = " << i->get() << '\n';

  cout << "\nclear vector\n";
  arrayOfIntegers.clear();
  
  cout << "\nexit.\n";
  return 0;
}
