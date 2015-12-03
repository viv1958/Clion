#include <iostream>
#include <algorithm>
#include <array>
#include <set>
#include <functional>
using namespace std;
void TestConstExpt();


auto make_fibo()
{
    return [](int n) {
        std::function<int(int)> recurse;
        recurse = [&](int n){
            return (n<=2)? 1 : recurse(n-1) + recurse(n-2);
        };
        return recurse(n);
    };
}
void test()
{
    std::function<int(int)> fib = [&fib](int n)
    {
       return (n <= 2)? 1 : fib(n-1) + fib(n-2);
    };
    cout << fib(9) << endl;
}
int main() {
    cout << "Hello, World!" << endl;
// ---- ����� �� ��������� � �++11 �������� ����������� �� ��������� �������� ����� ------------------------------------
    auto Identity = [](auto x) {
        return x;
    };
    cout << Identity(3) << " " << Identity("fff") << " " << Identity(2.7) << endl;

    auto add = [](auto x, auto y) -> decltype(x + y) {
        return x + y;
    };
    cout << add(3, 5.4) << endl;
// ---- ������� identityf, ������� ��������� �������� � ���������� ��������� ����������� ������, -----------------------
// ---- ��� ������ �������� ����� ��������� �������� ��������:
    auto identyf = [](auto x) {
        class Inner {
            int x;
        public:
            Inner(int i) : x(i) { }
            int operator() () {return x;}
        };
        return Inner(x);
    };
    cout << identyf(6)() << endl;
// ---- ������ ���������� identityf, ������������ �� ������, � �������  ------------------------------------------------
    int y = 3;
    auto identyf2 = [=](auto x) {
        return [=]() { return x*y; };
    };
    cout << identyf2(5)() << endl; // 5
// ---- �������, ������� ���������� �������-���������, ������������ ����� �� ��������� ��������� -----------------------
    auto fromto = [](auto beg, auto end) {
        return [=]() mutable->decltype(beg) {
            if (beg < end) {
                //cout << " --> " << beg << " " << end << endl;
                return beg++;
            }
        };
    };
    auto range = fromto(4,23);
    // --- ������� � ������ ������� -------
    cout << range(); cout << " " << range(); cout << " " << range(); cout << " " << range() << endl;
    // --- ������� � �������� ������� -----
    cout << range() << " " << range() << " " << range() << " " << range() << endl;
// ---- �������, ����������� ����� �� ������ � ������������ �� ---------------------------------------------------------
    auto addf = [](auto x) {
        return [=](auto y) {
            return x + y;
        };
    };
    cout << addf(4)(7) << endl;
// ----- �������, �������� ������� ��������� ������ ������� ------------------------------------------------------------
    auto swapx =[](auto binary) {
        return [=](auto x, auto y){
            return binary(y,x);
        };
    };
    auto sub = [](auto x, auto y) -> decltype(x - y) {
        return x - y;
    };
    cout << swapx(sub)(1, 1000) << endl;
// ---- �������, ����������� �������� ������� � ������������ ������� �������, ������� �������� �������� � --------------
//      �������� 2 ����
    auto twice = [](auto binary) {
        return [=](auto x) {
            return binary(x,x);
        };
    };
    cout << twice(add)(333) << endl;
// ---- �������, ����������� �������� ������� � ������������ �������, ����������� ��� ��������� �� ������� -------------
    auto applyf = [](auto binary) {
        return [=] (auto x) {
            return [=](auto y) {
                return binary(x,y);
            };
        };
    };
    cout << applyf(add)(1)(100) << endl;
// ---- ������� ������������, ���������� �������� ������� � �������� � ������������ �������, ����������� ---------------
//      ������ ��������. ������������ � �������������� �������, ���������� ��������� ����������,
//      � ������� �������, ����������� �� ������ ���������.
    auto curryf = [](auto binary, auto x) {
        return [=](auto y) {
            return binary(x,y);
        };
    };
    auto sub10 = curryf(sub, 10);
    cout << sub10(45) << endl;
// ----  ��������� ���������� ������� ----------------------------------------------------------------------------------
    auto addFour = [](auto a, auto b, auto c, auto d) {
        return a+ b + c + d;
    };
    auto partial = [](auto fun, auto x, auto y) {
        return [=](auto m, auto n) {
           return fun(x,y,m,n);
        };
    };
    cout << partial(addFour,1000,2000)(9,5) << endl;
// ---- 3 �������� ������� ������������ 1 ------------------------------------------------------------------------------
    auto int1 = curryf(add,1);
    auto int2 = addf(1);
    auto int3 = applyf(add)(1);
    cout << int1(0) << " " << int2(3) << " " << int3(7) << endl;
// ---- ���������� 2 ������� -------------------------------------------------------------------------------------------
    auto compose = [](auto f, auto g) {
        return [=](auto x) {
            return f(g(x));
        };
    };
    cout << compose(int1, curryf(sub,1000))(300) << endl;
// ---- ������������� ���������� � ������ ------------------------------------------------------------------------------
    std::set<int, std::function<bool(int, int)>>   numbers( [](int i, int j) { return i < j; } );
    numbers.insert({1,2,3,4});
    cout << "size = " << numbers.size() << endl;
// ---- ����������� ������-������� -------------------------------------------------------------------------------------
    auto fibo = make_fibo();
    auto make_fibo_loc = []()
    {
        return [](int n) {
            std::function<int(int)> recurse;
            recurse = [&](int n){
                return (n<=2)? 1 : recurse(n-1) + recurse(n-2);
            };
            return recurse(n);
        };
    };

    cout << "fibo " << fibo(1) << "  " << fibo(2) << " " << fibo(3) << " " << fibo(4) << " ";
    cout << fibo(5) << "  " << make_fibo()(6) << " " << fibo(7) << " " << make_fibo_loc()(8) <<endl;
    test();
// -------------
    TestConstExpt();
// =====================================================================================================================
    int x = 0;
    cin >> x;
    return 0;
}
// ---- ����������������� �������� -------------------------------------------------------------------------------------
constexpr long double operator"" _deg ( long double deg )
{
    return deg*3.141592/180;
}
struct mytype
{
    mytype ( unsigned long long m):m(m){}
    unsigned long long m;
};
mytype operator"" _mytype ( unsigned long long n )
{
    return mytype(n);
}


void tprintf(const char* format) // base function
{
    std::cout << format;
}
// ==== ������� � ���������� ����������� ���������� ====================================================================
// ---- ������ ������� -------------------------------------------------------------------------------------------------
template<typename T, typename... Targs>
void tprintf(const char* format, T value, Targs... Fargs) // recursive variadic function
{
    for ( ; *format != '\0'; format++ ) {
        if ( *format == '%' ) {
            std::cout << value;
            tprintf(format+1, Fargs...); // recursive call
            return;
        }
        std::cout << *format;
    }
    if (*format == '\0') {
        std::cout << value;
        tprintf(format+1, Fargs...); // recursive call
        return;
    }
}
// ---- ������� ������� � ���������� ����������� ����������: ���������� �������� ---------------------------------------
template<typename...Args> struct FunctorImpl;
// ������������� ��� ��������� �� ������� �������
template<typename R, typename...Args>
struct FunctorImpl<R(Args...)>
{
    typedef R (*FunType)(Args...);
    FunType m_fn;
    FunctorImpl(FunType fun) : m_fn(fun) {}
    R operator() (Args...args) { return m_fn(args...); }
};
// ����� ������ ���������
template <typename FunType>
struct Functor : FunctorImpl<FunType>
{
    Functor() : FunctorImpl<FunType>(nullptr) {}
    Functor(FunType fun) : FunctorImpl<FunType>(fun) {}
};
// ������������� ��� ��������� �� �������-����� ������
template <typename T,typename R, typename...Args>
struct FunctorImpl<R (T::*)(Args...)>
{
    typedef R (T::*FT)(Args...);
    typedef T HostType;

    FunctorImpl(FT fn = nullptr, T* obj = nullptr) : m_fn(fn),m_obj(obj) {}
    // 2 �������� ������ 1) ����� ������� ������������ ��� ��������� 2) ����� ������ ���������� ������ ����������
    R operator() (Args...args)        { return (m_obj->*m_fn)(args...); }
    R operator() (T* obj,Args...args) { return (obj->*m_fn)  (args...); }

    FT m_fn;
    T* m_obj;
};
template <typename FunType>
struct Closure : public FunctorImpl<FunType>
{
    typedef typename FunctorImpl<FunType>::HostType HostType;
    Closure(HostType* obj, FunType fun) : FunctorImpl<FunType>(fun, obj) {};
};
class TstClosure {
public: TstClosure(int base = 0) : m_base(base) {}
    int foo(int a) {return a + m_base; }
private:int m_base;
};
long long add(int x,int y) {
    long long z = x;
    z+=y;
    return z;
}

void something( char arr[10] )
{
    // this loop is broken
    int x = sizeof(arr);
    int y = sizeof(arr[0]);
    int z = sizeof(arr)/sizeof(arr[0]);

    for( size_t index = 0; index < sizeof(arr)/sizeof(arr[0]); index++ ) {
        //WHATEVER
    }
}
void TestConstExpt()
{
    char arr[100] = {};
    int k = sizeof(arr);
    something(arr);
    // ==== ���������������� �������� =================
    double x = 90.0_deg;
    mytype y = 123_mytype;
    // ==== ������� � ���������� ������ ���������� ====
    tprintf("% world% % -\n","Hello",'!',123, 1,3,5);
    // ==== ������� ===================================
    Functor<long long(int,int)> func1(add);
    TstClosure t1(10), t2;
    Functor<int (TstClosure::*)(int)> b_foo(&TstClosure::foo);
    Closure<int (TstClosure::*)(int)> a_foo(&t2,&TstClosure::foo);
    cout << a_foo(100) << "  " << b_foo(&t1,1000) << endl;

}