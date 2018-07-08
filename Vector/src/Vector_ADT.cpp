#include <iostream>
#include <assert.h>
#include "data_structure.h"

int64_t fibI (int n)
{
    int64_t f = 0, g = 1;
    while (0 < n--)
    {
        g += f;
        f = g - f;
    }
    return f;
}

//  Vector
template <typename T>
void Vector<T>::copyFrom(T const *A, Rank lo, Rank hi)
{
    _elem = new T[_capacity = 2 *(hi - lo)];
    _size = 0;
    while(lo < hi)
        _elem[_size++] = A[lo++];
}

template <typename T>Vector<T>& Vector<T>::operator =(Vector<T> const& V)
{
    if(_elem)
        delete[] _elem;
    copyFrom(V._elem, 0, V.size());
    return *this;
}

template <typename T> void Vector<T>::expand()  // 空间不足时扩容
{
    if(_size < _capacity) return;
    if(_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;
    T* oldElem = _elem;
    _elem = new T[_capacity <<= 1];
    for(int i = 0; i < _size; i++)
        _elem[i] = oldElem[i];      //复制原向量内容，且已经重载赋值操作符=
    delete [] oldElem;
}

template <typename T> void Vector<T>::shrink()  //装填因子过小时压缩所占空间
{
    if(_capacity < (DEFAULT_CAPACITY<<1)) return;
    if(_size << 2 > _capacity) return;
    T *oldElem = _elem;
    _elem = new T[_capacity >>= 1];
    for(int i = 0; i < _size; i++)
        _elem[i] = oldElem[i];
    delete [] oldElem;
}

template <typename T> T& Vector<T>::operator [](Rank r) const
{
    return _elem[r];
}

template <typename T> void permute (Vector<T> &V)
{
    for (int i = V.size(); i > 0; i--)
    {
        SWAP(V[i - 1], V[rand() % i]);
    }
}

template <typename T> void Vector<T>::unsort( Rank lo, Rank hi)
{
    T *V = _elem + lo;
    for (Rank i = hi - lo; i > 0; i--)
        (V[i - 1], V[rand() % i]);
}

//  无序向量顺序查找: 成功时返回对应的秩(存在多个时返回秩最大的一个)，失败则返回lo - 1
template <typename T> Rank Vector<T>::find(T const& e, Rank lo, Rank hi) const
{
    assert((0 <= lo) && (hi <= _size) && (lo <= hi));
    while ((lo < hi--) && (e != _elem[hi]));
    return hi;
}

//  将e作为秩为r的元素插入
template <typename T> Rank Vector<T>::insert(Rank r, T const& e)
{
    assert(r <= _size - 1);
    expand();
    for(int i = _size; i > r; i--)
    {
        _elem[i] = _elem[i - 1];
    }
    _elem[r] = e;
    _size++;
    return r;
}

template <typename T> int Vector<T>::remove(Rank lo, Rank hi)
{
    assert(0 <= lo && hi <= _size && lo <= hi);

    if(lo == hi) return 0;
    while(hi < _size)
    {
        _elem[lo++] = _elem[hi++]; //   [hi, lo)依次迁移hi-lo个单元
    }
    _size = lo;
    shrink();
    return hi - lo;     //被删除元素个数
}

template <typename T> T Vector<T>::remove(Rank r)
{
    assert(0 <= r && r <= _size );
    T e= _elem[r];
    remove(r, r + 1);   //等效于删除[r, r+1)
    return e;
}

//  删除无序向量中重复元素（高效版）
template <typename T> int Vector<T>::deduplicate()
{
    int oldSize = _size;
    Rank i = 1;
    while(i < _size)
    {
        //  从前缀元素中找相同者，找到就删除当前元素
        (find(_elem[i], 0, i) < 0) ? i++ : remove(i);
    }
    return oldSize - _size; //  被删除元素个数
}

template <typename T> void Vector<T>::traverse(void (*visit) (T&))  //函数指针机制
{
    for(int i = 0; i < _size; i++)
    {
        visit(_elem[i]);
    }
}

template <typename T> template <typename VST> void Vector<T>::traverse(VST& visit)    //函数对象机制
{
    for(int i = 0; i < _size; i++)
    {
        visit(_elem[i]);
    }
}

template <typename T> struct Increase
{
    virtual void operator() ( T& e ) // 函数对象：递增一个T类对象
    {
        e++;    // 假设T可以直接递增或已重载++
    }
};

template <typename T> void increase(Vector<T> & V)
{
    V.traverse(Increase<T>());
}

//  只有有序向量才有下列方法
template <typename T> int Vector<T>::disordered() const
{
    int n = 0;
    for(int i = 1; i < _size; i++)
    {
        if(_elem[i -1] > _elem[i])
            n++;
    }
    return n;   // 当且仅当n=0时向量有序
}
#if 0
template <typename T> int Vector<T>::uniquify_low_speed()
{
    int old_size = _size;
    int i = 1;

    while(i < _size)
        _elem[i - 1] == _elem[i] ? remove(i) : i++;
    return old_size - _size;
}
#endif
template <typename T> int Vector<T>::uniquify()
{
    Rank i = 0, j = 0;
    while(++j < _size)
        if(_elem[i] != _elem[j])
            _elem[++i] = _elem[j];
    _size = ++i;
    shrink();
    return j - i;
}

template <typename T> Rank Vector<T>::search(T const& e, Rank lo, Rank hi) const
{
    return binSearch_C(_elem, e, lo, hi); //fibSearch(_elem, e, lo, hi)
}

template <typename T> static Rank binSearch_A(T *A, T const& e, Rank lo, Rank hi)
{
    while(lo < hi)
    {
        Rank mi = (lo + hi) >> 1;
        if(e < A[mi]) hi = mi;
        else if(A[mi] < e) lo = mi + 1;
        else return mi;
    }
}

template <typename T> static Rank binSearch_B(T *A, T const& e, Rank lo, Rank hi)
{
    while( 1 < hi - lo)
    {
        Rank mi = (lo + hi) >> 1;
        (e < A[mi] ) ? hi = mi: lo = mi;
    }
    return (e == A[lo] ? lo : -1);
}

template <typename T> static Rank binSearch_C(T *A, T const& e ,Rank lo, Rank hi)
{
    while(lo < hi)
    {
        Rank mi = (hi + lo) >> 1;
        (e < A[mi]) ? hi = mi : lo = mi + 1;
    }
    return --lo;
}

template <typename T> void Vector<T>::sort(Rank lo, Rank hi)
{
    switch ( rand() % 5) {
    case 1:
        bubbleSort(lo, hi);
        break;
    case 2:
        selectionSort(lo, hi);
        break;
    case 3:
        mergeSort(lo, hi);
        break;
    case 4 :
        heapSort(lo, hi);
        break;
    default:
        quickSort(lo, hi);
        break;
    }
}

template <typename T> bool Vector<T>::bubble(Rank lo, Rank hi)
{
    bool sorted = true;
    while(++lo < hi)
        if(_elem[lo - 1] > _elem[lo])
        {
            sorted = false;
            SWAP(_elem[lo - 1], _elem[lo]);
        }
    return sorted;
}

template <typename T> void Vector<T>::bubbleSort(Rank lo, Rank hi)
{
    while(!bubble(lo, hi--));
}

template <typename T> void Vector<T>::mergeSort(Rank lo, Rank hi)
{
    if(hi - lo < 2) return;
    int mi = (lo + hi) >> 1;
    mergeSort(lo, mi);
    mergeSort(mi, hi);
    if(_elem[mi - 1] > _elem[mi])
        merge(lo, mi, hi);
}

template <typename T> void Vector<T>::merge(Rank lo, Rank mi, Rank hi) //各自有序的子向量[lo, mi)和[mi, hi)
{
    T *A = _elem + lo;
    int lb = mi - lo;
    T *B = new T[lb];
    for(Rank i = 0; i < lb; B[i] = A[i++]);
    int lc = hi - mi;
    T *C = _elem + mi;
    for(Rank i = 0, j = 0, k = 0;(j < lb) || (k < lc);)
    {
        if((j < lb) && (!(k < lc) || (B[j] <= C[k])))
            A[i++] = B[j++];
        if((k < lc) && (!(j < lb) || (C[k] < B[j])))
            A[i++] = C[k++];
    }
    delete [] B;
}

template <typename T> void Vector<T>::merge_D(Rank lo, Rank mi, Rank hi) //各自有序的子向量[lo, mi)和[mi, hi)
{
    Rank i, j, k;

    T *A = _elem + lo;
    int lb = mi - lo;
    T *B = new T[lb];
    for(Rank i = 0; i < lb; i++)
        B[i] = A[i];
    int lc = hi - mi;
    T *C = _elem + mi;
// lb， lc均未填完
    for(Rank i = 0, j = 0, k = 0; (j < lb) && (k < lc);)
    {
        if((j < lb) && (!(k < lc) || (B[j] <= C[k])))
            A[i++] = B[j++];
        if((k < lc) && (!(j < lb) || (C[k] < B[j])))
            A[i++] = C[k++];
    }
// 填完了一个数组后，直接拷贝另一个
    if(j == lb)
    {
        while(k < lc)
        {
            A[i++] = C[k++];
        }
    }
    else // k == lc
    {
        while(j < lb)
        {
            A[i++] = B[j++];
        }
    }
    delete [] B;
}

void Bitmap::set(int i)
{
    Map |= (0x01 << i);
}

void Bitmap::clear(int i)
{
    Map &= ~(0x01 << i);
}

bool Bitmap::check(int i)
{
    return (Map & (0x01 << i));
}




