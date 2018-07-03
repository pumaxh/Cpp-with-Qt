#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H

int64_t fibI (int n);

// vector ADT
typedef int Rank;
#define DEFAULT_CAPACITY 3

#define SWAP(a, b) \
    do { \
    a = a + b; \
    b = a - b; \
    a = a - b; \
    }while(0)

template <typename T> class Vector {
protected:
    Rank _size;         //秩的规模
    int _capacity;      //容量
    T* _elem;           //数据区
    void copyFrom( T const *A, Rank lo, Rank hi);   //复制数组区间A[lo, hi)
    void expand();      //空间不足时扩容
    void shrink();      //装填因子过小是压缩
    bool bubble(Rank lo, Rank hi);      //扫描交换
    void bubbleSort(Rank lo, Rank hi);  //冒泡排序
    Rank max(Rank lo, Rank mi, Rank hi);//选取最大元素
    void selectionSort(Rank lo, Rank hi);//选择排序
    void merge(Rank lo, Rank mi, Rank hi);//归并算法
    void mergeSort(Rank lo, Rank hi);   //归并排序算法
    Rank partition(Rank lo, Rank hi);   //轴点构造算法
    void quickSort(Rank lo, Rank hi);   //快速排序算法
    void heapSort(Rank lo, Rank hi);    //堆排序

public:
    Vector (int c = DEFAULT_CAPACITY, int s = 0, T v = 0)   //容量为c、规模为s、所有元素初始化为v
    {
        _elem = new T[_capacity = c];

        for(_size = 0; _size < s; _elem[_size++] = v);
    }

    Vector (T const *A, Rank n)
    {
        copyFrom(A, 0, n);
    }

    Vector (T const *A, Rank lo, Rank hi)
    {
        copyFrom(A, lo, hi);
    }

    Vector (Vector<T> const& V)     //向量整体复制
    {
        copyFrom(V._elem, 0, V._size);
    }

    Vector (Vector<T> const& V, Rank lo, Rank hi)
    {
        copyFrom(V._elem, lo, hi);
    }

    ~Vector()
    {
        delete[] _elem;
    }

//    只读访问接口
    Rank size() const
    {
        return _size;
    }

    bool empty() const
    {
        return !_size;
    }

    int disordered()const;

    Rank find(T const &e) const
    {
        return find(e, 0, _size);
    }

    Rank find(T const &e, Rank lo, Rank hi) const;
//    可写接口
    T& operator[] (Rank r) const;   //重载下表操作符，可类似于数组引用元素
    Vector<T> &operator= (Vector<T> const&);    //重载赋值操作符，一边直接克隆向量
    T remove(Rank r);
    int remove(Rank lo, Rank hi);   //删除在[lo, hi)之内的元素
    Rank insert(Rank r, T const& e);
    Rank insert(T const &e)
    {
        return insert(_size, e);
    }

    void sort(Rank lo, Rank hi);
    void sort()
    {
        sort(0, _size);
    }

    void unsort(Rank lo, Rank hi);
    void unsort()
    {
        unsort(0, _size);
    }

    int deduplicate();
    int uniquify();

    //遍历
    void traverse(void (*) (T&));   //遍历（使用函数指针，只读性局部修改）
    template <typename VST> void traverse( VST&);   //遍历（使用函数对象，可全局修改）

    Rank search(T const& e, Rank lo, Rank hi) const;
};

#endif // DATA_STRUCTURE_H
