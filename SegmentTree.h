//
// Created by qawbecrdtey on 2018-12-20.
//

#ifndef SEGMENT_TREE_SEGMENTTREE_H
#define SEGMENT_TREE_SEGMENTTREE_H

#include <vector>
#include <ostream>

template <typename inType,typename treeType>
class SegmentTree {
    using ull=unsigned long long;

    std::vector<inType> element;
    std::vector<treeType> tree;
    ull size;
    treeType(*convert)(const inType &);
    treeType(*process_func)(const treeType &,const treeType &);
    treeType treeType_ZERO; // process_func(a, treeType_ZERO) == a for all a

    ull bb(ull n) {
        ull x=1;
        while(x<n)x*=2;
        return x;
    }

    treeType init(ull cur, ull start, ull end) {
        if(start==end) {tree[cur]=convert(element[start]);std::cout<<start<<" : "<<tree[cur]<<std::endl;return tree[cur];}
        return tree[cur]=process_func(init(cur*2, start, (start+end)/2), init(cur*2+1, (start+end)/2+1, end));
    }
    treeType search(ull cur, ull start, ull end, ull left, ull right) {
        if(left>end||right<start) return treeType_ZERO;
        if(left<=start&&right>=end) return tree[cur];
        return process_func(search(cur*2,start,(start+end)/2,left,right),search(cur*2+1,(start+end)/2+1,end,left,right));
    }
    void update(ull cur, ull start, ull end, ull to, treeType change) {
        if(to<start||to>end) return;
        if(start>=end) tree[cur]=change;
        else{
            update(cur*2, start, (start+end)/2, to, change);
            update(cur*2+1, (start+end)/2+1, end, to, change);
            tree[cur]=process_func(tree[cur*2], tree[cur*2+1]);
        }
    }

public:
    SegmentTree(const std::vector<inType> &element, treeType (*convert)(const inType &),
                treeType (*process_func)(const treeType &, const treeType &), treeType treeType_ZERO)
            : size(element.size()),
              convert(convert),
              process_func(process_func),
              treeType_ZERO(treeType_ZERO) {
        this->element.reserve(element.size()+1);
        this->element.emplace_back(treeType_ZERO);
        for(ull i = 0; i < element.size(); i++){
            this->element.emplace_back(element[i]);
        }
        tree.resize(bb(size)*2);
        init(1,1,size);
    }

    bool operator==(const SegmentTree &rhs) const {
        return element == rhs.element &&
               tree == rhs.tree &&
               size == rhs.size &&
               convert == rhs.convert &&
               process_func == rhs.process_func &&
               treeType_ZERO == rhs.treeType_ZERO;
    }
    bool operator!=(const SegmentTree &rhs) const{
        return !(rhs == *this);
    }

    inType operator[](ull n) const {
        return element[n+1];
    }
    void set_element(ull n, const inType &in) {
        element[n+1]=in;
        update(1, 1, size, n+1, convert(in));
    }
    inType get_element(ull n) {
        return element[n+1];
    }

    treeType search(ull left, ull right) {
        return search(1, 1, size, left+1, right+1);
    }
};


#endif //SEGMENT_TREE_SEGMENTTREE_H
