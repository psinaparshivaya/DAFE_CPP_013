#include <iostream>
#include <memory>
#include <utility>
using std::cout;
using std::allocator;
using std::out_of_range;
using std::string;
using std::stringstream;
using std::auto_ptr;
template<typename T, typename A = allocator<T> >
class vector11 
{
private:
    int sz;
    int space;
    T* elem;
    void copy(const vector11& arg);
protected:
    A alloc;
public:   
    vector11() :sz(0), space(0), elem(0) {}
    vector11(int _sz, int _space) : sz(_sz), space(_space)
    {
        elem = alloc.allocate(space);
        std::uninitialized_fill_n(elem, sz, T());
    }
    vector11(int _sz, int _space, T val): sz(_sz), space(_space)
    {
        elem = alloc.allocate(space);
        std::uninitialized_fill_n(elem, sz, val);
    }
    double get(int n) const {return elem[n];}
	void set(int n, double v) {elem[n]=v;}
    vector11(const vector11&); 
    vector11& operator=(const vector11&);
    virtual ~vector11() 
    {
        for (int i = 0; i < sz; i++)
            alloc.destroy(&elem[i]);
        alloc.deallocate(elem, space);
    }
    T& operator[](int n) { return elem[n]; }
    const T& operator[](int n) const { return elem[n]; } 
    T& at(int n);
    const T& at(int n) const; 
    int size() const { return sz; }
    int capacity() const { return space; }
    void reserve(int newalloc);
    void resize(int newsize, T value = T());
    void push_back(T value);
};
template<typename T, typename A>
void vector11<T, A>::copy(const vector11& arg) 
{
    for (int i = 0; i<arg.sz; i++)
        alloc.construct(&elem[i], arg.elem[i]);
}
template<typename T, typename A>
vector11<T, A>::vector11(const vector11& arg)
{
    cout << this << " \t\tvvector::vvector(const vvector& arg)" << std::endl;
    sz = arg.sz;
    elem = alloc.allocate(arg.sz);
    copy(arg);
    reserve(arg.space);
}
template<typename T, typename A>
void vector11<T, A>::operator=(const vector11& arg) 
{
    cout << this << " \t\tvector11::operator=(const vector11& v)" << std::endl;
    if (this == &arg) return *this;
    if (arg.sz <= space) 
    {
        copy(arg);
        sz = arg.sz;
        return *this;
    }
    auto_ptr<T> p(alloc.allocate(arg.space));
    for (int i = 0; i<arg.sz; i++)
        alloc.construct(&p.get()[i], arg.elem[i]);  
    for (int i = 0; i<sz; i++)
        alloc.destroy(&elem[i]);
    alloc.deallocate(elem, space);  
    elem = p.release();
    sz = arg.sz;
    reserve(arg.space);  
    return *this;
}

template<typename T, typename A>
void vector11<T, A>::reserve(int newalloc) 
{
    cout << this << " vector11::reserve(int newalloc), newalloc==" << newalloc << endl;
    if (newalloc <= space) return; 
    auto_ptr<T> pa(alloc.allocate(newalloc));
    for (int i = 0; i < sz; i++)
    {
        alloc.construct(&pa.get()[i], elem[i]);
        alloc.destroy(&elem[i]);
    }
    elem = pa.release();
    space = newalloc;
    cout << this << " vector11<T,A>::reserve, space == " << space << endl;
 
}
template<typename T, typename A>
void vvector<T, A>::resize(int newsize, T value) 
{
    cout << this << " \t\tvector11::resize(int newsize, T value)" << endl;
    reserve(newsize);
    for (int i = sz; i<newsize; i++)
        alloc.construct(&elem[i], value);   
    for (int i = newsize; i<sz; i++)
        alloc.destroy(&elem[i]);  
    sz = newsize;
}
template<typename T, typename A>
void vector11<T, A>::push_back(T value) 
{
    if (!space) reserve(8);
    else if (sz == space) reserve(2 * space);
    alloc.construct(&elem[sz], value);
    ++sz;
}
template<typename T, typename A>
T& vector11<T, A>::at(int n) 
{
 
    if (n<0 || sz <= n) {
        string s = "wrong index: ";
        stringstream ss;
        ss << n;
        s += ss.str();
        throw out_of_range(s);
    }
    return elem[n];
 
}
template<typename T, typename A>
const T& vector11<T, A>::at(int n) const 
{
    if (n<0 || sz <= n) 
    {
        string s = "wrong index: ";
        stringstream ss;
        ss << n;
        s += ss.str();
        throw out_of_range(s);
    }
    return elem[n];
}
