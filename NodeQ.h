#ifndef NODEQ_H
#define NODEQ_H

template <class T>
class Node
{
    public:
        T A;
        Node<T> *next;
        Node<T> *prev;

    public:
        static Node<T> *montaNo(T X)
        {
            Node<T> *p;
            p = new Node<T>;
            if(!p) return p;
            p->A = X;
            p->next = 0;
            p->prev = 0;

            return p;
        }

        static T desmontaNo(Node<T> *P)
        {
            T x = P->A;
            delete P;
            return x;
        }
};

#endif // NODEQ_H
