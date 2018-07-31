#ifndef LIST_H
#define LIST_H

#include "listNode.h"

template <typename T> class List {
private:    // 规模，头哨兵，尾哨兵
    int _size;
    ListNodePosi(T) header;
    ListNodePosi(T) trailer;

protected:
    void init();
    int clear();
    void copyNodes(ListNodePosi(T) p, int n); // 复制列表中自位置p起的n项
    void merge(ListNodePosi(T)&, int, List<T>&, ListNodePosi(T), int);
    void mergeSort(ListNodePosi(T)&, int); // 对从p开始的连续n个借点归并排序
    void selectionSort(ListNodePosi(T), int);
    void insertionSort(ListNodePosi(T), int);

public:
    List(){init();}
    List(List<T> const& L);
    List(List<T> const& L, Rank r, int n);
    List(ListNodePosi(T) p, int n);
    ~List();
    // 只读访问接口
    Rank size() const {return _size;}
    bool empty() const {return _size <= 0;}
    T& operator[] (Rank r) const; // 循秩访问，需要遍历
    ListNodePosi(T) first() const{return header->succ;}
    ListNodePosi(T) last() const{return trailer->pred;}
    bool valid(ListNodePosi(T) p) // 判断位置p是否对外合法
    {
        return p && (trailer != p) && (header != p);
    }
    int disordered() const; // 判断列表是否已经排序
    ListNodePosi(T) find(T const& e, int n, ListNodePosi(T) p) const; // 无序区间查找
    ListNodePosi(T) find (T const& e) const // 无序列表查找
    {
        return find(e, _size, trailer);
    }
    ListNodePosi(T) search(T const& e) const // 有序列表查找
    {
        return search(e, _size, trailer);
    }
    ListNodePosi(T) search(T const& e, int n, ListNodePosi(T) p) const;
    ListNodePosi(T) searchMax(ListNodePosi(T) p, int n); // 查找p极其后n-1个后继中选出最大者
    ListNodePosi(T) searchMax(){searchMax(header->succ, _size);}
    // 可写接口
    ListNodePosi(T) insertAsFirst(T const& e);
    ListNodePosi(T) insertAsLast(T const& e);
    ListNodePosi(T) insertA(ListNodePosi(T) p, T const& e);
    ListNodePosi(T) insertB(ListNodePosi(T) p, T const& e);
    T remove(ListNodePosi(T) p);
    void merge(List<T>& L)
    {
        merge(first(), size, L, L.first(), L._size);
    }
    void sort(ListNodePosi(T) p, int n); //列表区间排序
    void sort(){sort(first(), _size);}
    int deduplicate();
    int uniquify();
    void reverse();
    // 遍历
    void traverse(void (*visit) (T&)); //遍历，一次实施visit操作
    template <typename VST> void traverse(VST&); // 操作器
    ListNodePosi(T) selectMax(ListNodePosi(T) p, int n);
};

#endif // LIST_H
