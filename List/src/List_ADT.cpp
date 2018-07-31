#include <assert.h>
#include "data_structure.h"

template <typename T> void List<T>::init()
{
    ListNodePosi(T) header = new ListNode<T>;   // 头哨兵
    ListNodePosi(T) trailer = new ListNode<T>;  // 尾哨兵
    header->succ = trailer;
    header->pred = NULL;
    trailer->pred = header;
    trailer->succ = NULL;
    _size = 0;
}

template <typename T> T& List<T>::operator [](Rank r) const
{
    assert((0 <= r) && (r < size()));
    ListNodePosi(T) p = first();
    while (0 < r--)
        p = p->succ;
    return p->data;
}

template <typename T> ListNodePosi(T) List<T>::find(T const& e, int n, ListNodePosi(T) p) const
{
    assert(0 <= n && n <= _size);
    while(0 < n--)
        if(e == (p->pred)->data) return p->pred;
    return NULL;    // p超出左边界意味着e不在区间内
}

template <typename T> ListNodePosi(T) List<T>::insertAsFirst(T const& e)
{
    _size++;
    return header->insertAsSucc(e);
}

template <typename T> ListNodePosi(T) List<T>::insertAsLast(T const& e)
{
    _size++;
    return trailer->insertAsPred(e);
}

template <typename T> ListNodePosi(T) List<T>::insertA(ListNodePosi(T) p, T const& e)
{
    _size++;
    return p->insertAsSucc(e);
}

template <typename T> ListNodePosi(T) List<T>::insertB(ListNodePosi(T) p, T const& e)
{
    _size++;
    return p->insertAsPred(e);
}

template <typename T> ListNodePosi(T) ListNode<T>::insertAsPred(T const& e)
{
    ListNodePosi(T) x = new ListNode(e, pred, this);    // 创建新节点
    pred->succ = x;     // 设置正向链接
    pred = x;
    return x;
}

template <typename T> ListNodePosi(T) ListNode<T>::insertAsSucc( T const& e )
{
    ListNodePosi(T) x = new ListNode(e, this, succ);
    succ->pred = x;
    succ = x;
    return x;
}

// 复制列表中自p起n项, p合法且至少有n-1个后继节点
template <typename T> void List<T>::copyNodes(ListNodePosi(T)p, int n)
{
    init();
    while(n--)
    {
        insertAsLast(p->data);
        p = p->succ;
    }
}
//复制列表中自位置p起的n项（assert: p为合法位置，且至少有n-1个后继节点）
template <typename T> List<T>::List(ListNodePosi(T) p, int n)
{
    assert(p != NULL && size >= n);
    copyNodes(p, n);
}

template <typename T> List<T>::List (List<T> const& L)
{
    copyNodes(L.first(), L.size());
}

template <typename T> List<T>::List (List<T> const& L, int r, int n)
{
    assert(r + n < L.size());
    copyNodes(L[r], n);
}

template <typename T> T List<T>::remove(ListNodePosi(T) p)
{
    T e = p->data;
    p->pred->succ = p->succ;
    p->succ->pred = p->pred;
    delete p;
    _size--;
    return e;
}

template <typename T> int List<T>::clear()
{
    int oldSize = _size;
    while( 0 < _size)
        remove(header->succ);
    return oldSize;
}

// 析构
template <typename T> List<T>::~List()
{
    clear();
    delete header;
    delete trailer;
}

// 唯一化
template <typename T> int List<T>::deduplicate()
{
    if(_size < 2) return 0;
    int oldSize = _size;
    ListNodePosi(T) p = header;
    Rank r = 0;
    while (trailer != (p = p->succ)) {
        ListNodePosi(T) q = find(p->data, r, p);
        q ? remove(q) : r++;
    }
    return oldSize - _size;
}

template <typename T> template <typename VST>
void List<T>::traverse (VST& visit)
{
    for (ListNodePosi(T) p = header->succ; p != trailer; p= p->succ)
        visit(p->data);
}

template <typename T> int List<T>::uniquify()
{
    if(_size < 2) return 0;
    int oldSize = _size;
    ListNodePosi(T) p = first();
    ListNodePosi(T) q;
    while(trailer != (q = p->succ))
    {
        if(p->data != q->data)
            p = q;
        else
            remove(q);
    }
    return oldSize - _size;
}

template <typename T> ListNodePosi(T) List<T>::search(T const& e, int n, ListNodePosi(T) p) const
{
    while( 0 <= n--)
    {
        if(((p = p->pred)->data) <= e)
            break;
    }
    return p;
}

// 排序器
template <typename T> void List<T>::sort(ListNodePosi(T) p, int n)
{
    switch (rand() % 3)
    {
        case 1: insertionSort(p, n); break;
        case 2: selectionSort(p, n); break;

        default: mergeSort(p, n);break;
    }
}

template <typename T>
void List<T>::insertionSort( ListNodePosi(T) p, int n)
{
    for (int r = 0; r < n; r++)
    {
        insertA(search(p->data, r, p), p->data);
        p = p->succ;
        remove(p->pred);
    }
}

// 对于始于p位置的n个元素排序
template <typename T>
void List<T>::selectionSort(ListNodePosi(T) p, int n)
{
    ListNodePosi(T) head = p->pred;
    ListNodePosi(T) tail = p;
    for (int i = 0; i < n; i++) tail = tail->succ;  // 待排序区间为(head, tail)
    while (1 < n)
    {
        ListNodePosi(T) max = searchMax(head->succ, n);
        insertB(tail, remove(max));
        tail = tail->pred;
        n--;
    }
}

template <typename T> // 从起始于位置p的n个元素中选出最大者
ListNodePosi(T) List<T>::selectMax(ListNodePosi(T) p, int n)
{
    ListNodePosi(T) max = p;
    for (ListNodePosi(T) cur = p; 1 < n; n--)
    {
        if(!lt(( cur = cur->succ)->data, max->data))
            max = cur;
    }
    return max;
}

template <typename T>   // 有序列表的归并：当前列表中自p起的n个元素，与列表L中自q起的m个元素归并
// 注意：在归并排序之类的场合，有可能this == L && rank(p) + n = rank(q)
void List<T>::merge(ListNodePosi(T)& p, int n, List<T>& L, ListNodePosi(T) q, int m)
{
    ListNodePosi(T) pp = p->pred;
    while(0 < m)    // 在q尚未移出区间之前
        if( (0 < m) && (p->data <= q->data))    // 若p仍在区间内且v(p) <= v(q)
        {
            if(q == (p = p->succ))              // p归入合并的列表，并替换为其直接后继
                break;
            n--;
        }
        else                                    // 若p已超出右界v(q) < v(p)
        {
            insertB( p, L.remove((q = q->succ)->pred));
            m--;
        }
    p = pp->succ;   //  归并后区间的新起点
}

template <typename T>
void List<T>::mergeSort(ListNodePosi(T)& p, int n)
{
    if(n < 2) return;
    int m = n >> 1;
    ListNodePosi(T) q = p;
    for(auto i = 0; i < m; i++)
    {
        q = q->succ;
    }
    mergeSort(p, m);
    mergeSort(q, n - m);
    merge(p, m, *this, q, n - m);
}


















