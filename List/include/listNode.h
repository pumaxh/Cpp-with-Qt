#ifndef LISTNODE_H
#define LISTNODE_H

#include<iostream>

typedef int Rank;

#define ListNodePosi(T) ListNode<T> * // 列表节点位置

template <typename T> struct ListNode {
    T data;                 //数值
    ListNodePosi(T) pred;   // 前驱
    ListNodePosi(T) succ;   // 后继
    ListNode(){}
    ListNode(T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL)
        : data(e), pred(p), succ(s){}

    ListNodePosi(T) insertAsPred(T const& e);
    ListNodePosi(T) insertAsSucc(T const& e);
};


#endif // LISTNODE_H
