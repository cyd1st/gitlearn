template <class T1,class T2> 
class A { 
    T1 v1; T2 v2;
};

template <class T>
class B:public A<int,double> { 
    T v;
};

template <class T1,class T2, class T3>
class B:public A<T2,T1> { 
    T1 v3; T2 v4;, T3 v5;
};

template <class T>
class C:public B<T,T> { 
    T v5;
};

int main() {
    A<int, double> aa;
    B<int> bb;
    B<int, double, float> bb2;
    C<int> cc;
    return 0;
}