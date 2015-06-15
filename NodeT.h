#ifndef NODET_H
#define NODET_H


template <class myType>
class NodeT
{
    public:
        myType A;
        int FB;
        NodeT<myType>  *Right;
        NodeT<myType>  *Left;

    public:
        static NodeT<myType> *montaNo(myType X)
        {
            NodeT<myType> *p;
            p = new NodeT<myType>;
            if(!p) return p;
            p->A = X;
            p->Right = NULL;
            p->Left = NULL;
            p->FB = 0;

            return p;
        }

        static myType desmontaNo(NodeT<myType> *P)
        {
            myType x = P->A;
            delete P;
            return x;
        }
};

#endif // NODET_H
