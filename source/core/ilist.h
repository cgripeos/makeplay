//*****************************************************************************
// Copyright 2016 - 2016 Chris J Gripeos. All rights reserved.
// License: http://www.opensource.org/licenses/BSD-2-Clause
// 
// Author: Chris J Gripeos    
//
//*****************************************************************************


#ifndef MAKEPLAY_INC_ILIST_H
#define MAKEPLAY_INC_ILIST_H
//-----------------------------------------------------------------------------

#ifndef MAKEPLAY_INC_PROTO_H
# include "proto.h"
#endif // MAKEPLAY_INC_PROTO_H

#ifndef MAKEPLAY_INC_NONCOPYABLE_H
#include "noncopyable.h"
#endif // MAKEPLAY_INC_NONCOPYABLE_H


#include <stddef.h>     /* offsetof */

namespace makeplay { namespace core {


//-----------------------------------------------------------------------------
// IListNode
//-----------------------------------------------------------------------------
class IListNode
{
    template<class TOwner, int NODE_OFFSET> friend class IList;

public:
     IListNode() { m_prev = m_next = this; }
    ~IListNode() { unlink(); }

    bool is_linked() const;
    void unlink();

private:
    void insert_me_before(IListNode& _other);
    void insert_me_after(IListNode& _other);

    IListNode*const prev() const;
    IListNode*const next() const;
    IListNode*& prev();
    IListNode*& next();

private:
    IListNode* m_prev;
    IListNode* m_next;
};


//-----------------------------------------------------------------------------
// IList
//-----------------------------------------------------------------------------
template <class TOwner, int NODE_OFFSET>
class IList : public NonCopyable
{
private:
    typedef TOwner     Owner;

    class _iterator
    {
        //typedef TOwner Owner;
        typedef IList<Owner, NODE_OFFSET> OwnerList;
        friend class OwnerList;
        friend class OwnerList::_const_iterator;

    private:
        _iterator(OwnerList& _list, IListNode& _node);

    public:
        _iterator();
        _iterator(_iterator const& _other);

        _iterator& operator++();
        _iterator& operator--();

        Owner&       operator*();
        Owner const& operator*() const;

        bool operator==(_iterator const _other) const;
        bool operator!=(_iterator const _other) const;

    private:
        OwnerList* m_list;
        IListNode* m_node;
    };

    class _const_iterator
    {
        //typedef TOwner Owner;
        typedef IList<Owner, NODE_OFFSET> OwnerList;
        friend class OwnerList;
        friend class OwnerList::_iterator;

    private:
       _const_iterator(OwnerList const& _list, IListNode const& _node);

    public:
        _const_iterator();
        _const_iterator(_iterator const& _other);
        _const_iterator(_const_iterator const& _other);

        _const_iterator& operator=(_iterator const _other);

        _const_iterator& operator++();
        _const_iterator& operator--();

        Owner&       operator*();
        Owner const& operator*() const;

        bool operator==(_const_iterator _other) const;
        bool operator!=(_const_iterator _other) const;

    private:
        OwnerList const* m_list;
        IListNode const* m_node;
    };

public:
    typedef _iterator       iterator;
    typedef _const_iterator const_iterator;

public:
     IList();
    ~IList();

    bool   empty() const;
    size_t size() const;

    Owner& front() const;
    Owner& back() const;

    iterator begin();
    iterator end();

    const_iterator begin() const;
    const_iterator end() const;
    
    void clear();
    void remove(TOwner& _owner);
    void erase(iterator& _iter);
    void push_front(TOwner& _item);
    void pop_front();
    void push_back(TOwner& _item);
    void pop_back();

    // entire other list into me at pos
    void splice(iterator _pos, IList& _other);
    // single other element into me at pos
    void splice(iterator _pos, IList& _other, iterator _other_i);
    // other element range into me at pos 	
    void splice(iterator _pos, IList& _other, iterator _other_first, iterator _other_last);

    template <class Compare> 
    iterator drop_sort(iterator _pos, TOwner& _owner, Compare compare);

    template<class Compare>
    void merge(IList& _other, Compare compare);

    template <class Compare> 
    void sort (Compare comp);

private:
    static IListNode*  to_node(Owner const* _owner);
    static Owner*      to_owner(IListNode const* _node);

    template <class Compare> 
    void _sort(Compare comp, size_t _list_size);

private:
    IListNode m_list;

};





}} // namespace makeplay::core


#include "ilist.inl"

// convinience macro to declare an intrusive linked list
#define ILIST(type, node_name)   makeplay::core::IList<type, offsetof(type, node_name)>



//-----------------------------------------------------------------------------
#endif // MAKEPLAY_INC_ILIST_H
