//*****************************************************************************
// Copyright 2016 - 2016 Chris J Gripeos. All rights reserved.
// License: http://www.opensource.org/licenses/BSD-2-Clause
// 
// Author: Chris J Gripeos    
//
//*****************************************************************************


namespace makeplay { namespace core {


// define shorthand template stuff so we don't type so much
#define TEMPLATE_ILIST  template<class TOwner, int NODE_OFFSET>
#define TILIST          IList<TOwner, NODE_OFFSET>

//------------------------------------------------------------------------------//
// IListNode
//------------------------------------------------------------------------------//

inline bool IListNode::is_linked() const
{
    if (m_next == this || prev() == this)
    {
        MP_ASSERT(m_prev == m_next);
        return false;
    }
    return true;
}

inline void IListNode::unlink()
{
    m_prev->m_next = m_next;
    m_next->m_prev = m_prev;
    m_next = m_prev = this;
}

inline void IListNode::insert_me_before(IListNode& _other)
{
    unlink();
    this->m_next = &_other;
    this->m_prev = _other.m_prev;
    _other.m_prev->m_next = this;
    _other.m_prev = this;
}

inline void IListNode::insert_me_after(IListNode& _other)
{
    unlink();
    this->m_next = _other.m_next;
    this->m_prev = &_other;
    _other.m_next->m_prev = this;
    _other.m_next = this;
}

inline IListNode*const IListNode::prev() const 
{ 
    return m_prev; 
}

inline IListNode*const IListNode::next() const 
{
    return m_next; 
}

inline IListNode*& IListNode::prev()
{
    return m_prev;
}

inline IListNode*& IListNode::next()
{
    return m_next;
}



//------------------------------------------------------------------------------//
// IList::_iterator
//------------------------------------------------------------------------------//


TEMPLATE_ILIST
TILIST::_iterator::_iterator()
    : m_node(NULL)
    , m_list(NULL)
{
}

TEMPLATE_ILIST
TILIST::_iterator::_iterator(OwnerList& _list, IListNode& _node)
    : m_list(&_list)
    , m_node(&_node)
{
}

TEMPLATE_ILIST
TILIST::_iterator::_iterator(_iterator const& _other)
    : m_node(_other.m_node)
    , m_list(_other.m_list)
{
}


TEMPLATE_ILIST
typename TILIST::_iterator& TILIST::_iterator::operator++()
{
    if (*this != m_list->end())
        m_node = m_node->next();
    return *this;
}

TEMPLATE_ILIST
typename TILIST::_iterator& TILIST::_iterator::operator--()
{
    if (*this != m_list->begin())
        m_node = m_node->prev();
    return *this;
}

TEMPLATE_ILIST
TOwner& TILIST::_iterator::operator*()
{
    MP_ASSERT(*this != m_list->end());
    return *TILIST::to_owner(m_node);
}

TEMPLATE_ILIST
TOwner const& TILIST::_iterator::operator*() const
{
    MP_ASSERT(m_node != m_list->end());
    return IList<TOwner, IListNode, NODE_OFFSET>::to_owner(m_node);
}

TEMPLATE_ILIST
bool TILIST::_iterator::operator==(_iterator const _other) const
{
    return m_node == _other.m_node;
}

TEMPLATE_ILIST
bool TILIST::_iterator::operator!=(_iterator const _other) const
{
    return m_node != _other.m_node;
}


//------------------------------------------------------------------------------//
// IList::_iterator
//------------------------------------------------------------------------------//


TEMPLATE_ILIST
TILIST::_const_iterator::_const_iterator()
    : m_node(NULL)
    , m_list(NULL)
{
}

TEMPLATE_ILIST
TILIST::_const_iterator::_const_iterator(OwnerList const& _list, IListNode const& _node)
    : m_list(&_list)
    , m_node(&_node)
{
}

TEMPLATE_ILIST
TILIST::_const_iterator::_const_iterator(_iterator const& _other)
    : m_node(_other.m_node)
    , m_list(_other.m_list)
{
}

TEMPLATE_ILIST
TILIST::_const_iterator::_const_iterator(_const_iterator const& _other)
    : m_node(_other.m_node)
    , m_list(_other.m_list)
{
}

TEMPLATE_ILIST
typename TILIST::_const_iterator& TILIST::_const_iterator::operator= (_iterator const _other)
{
    m_node = _other.m_node;
    m_list = _other.m_list;

    return *this;
}


TEMPLATE_ILIST
typename TILIST::_const_iterator& TILIST::_const_iterator::operator++()
{
    if (*this != m_list->end())
        m_node = m_node->next();
    return *this;
}

TEMPLATE_ILIST
typename TILIST::_const_iterator& TILIST::_const_iterator::operator--()
{
    if (*this != m_list->begin())
        m_node = m_node->prev();
    return *this;
}

TEMPLATE_ILIST
TOwner& TILIST::_const_iterator::operator*()
{
    MP_ASSERT(*this != m_list->end());
    return *TILIST::to_owner(m_node);
}

TEMPLATE_ILIST
TOwner const& TILIST::_const_iterator::operator*() const
{
    MP_ASSERT(m_node != m_list->end());
    return IList<TOwner, IListNode, NODE_OFFSET>::to_owner(m_node);
}

TEMPLATE_ILIST
bool TILIST::_const_iterator::operator==(_const_iterator const _other) const
{
    return m_node == _other.m_node;
}

TEMPLATE_ILIST
bool TILIST::_const_iterator::operator!=(_const_iterator const _other) const
{
    return m_node != _other.m_node;
}



//------------------------------------------------------------------------------//
// IList
//------------------------------------------------------------------------------//


TEMPLATE_ILIST
TILIST::IList()
{
}

TEMPLATE_ILIST
TILIST::~IList()
{
    clear();
}


TEMPLATE_ILIST
IListNode*  TILIST::to_node(TOwner const* _owner) 
{
    return (IListNode*)((char*)(_owner) + NODE_OFFSET);
}

TEMPLATE_ILIST
TOwner* TILIST::to_owner(IListNode const* _node) 
{
    return (TOwner*)((char*)(_node) - NODE_OFFSET);
}


TEMPLATE_ILIST
bool TILIST::empty() const
{
    return !m_list.is_linked();
}

TEMPLATE_ILIST
size_t TILIST::size() const
{
    size_t count = 0;
    const_iterator i = begin();
    while(i != end())
    {
        ++count;
        ++i;
    }
    return count;
}

TEMPLATE_ILIST
TOwner& TILIST::front() const
{
    MP_ASSERT(!empty());
    return *to_owner(m_list.next());
}

TEMPLATE_ILIST
TOwner& TILIST::back() const
{
    MP_ASSERT(!empty());
    return *to_owner(m_list.prev());
}


TEMPLATE_ILIST
typename TILIST::iterator TILIST::begin()
{
    return iterator(*this, *m_list.next());
}

TEMPLATE_ILIST
typename TILIST::iterator TILIST::end()
{
    return iterator(*this, m_list);
}

TEMPLATE_ILIST
typename TILIST::const_iterator TILIST::begin() const
{
    return const_iterator(*this, *m_list.next());
}

TEMPLATE_ILIST
typename TILIST::const_iterator TILIST::end() const
{
    return const_iterator(*this, m_list);
}


TEMPLATE_ILIST
void TILIST::clear()
{
    while (!empty())
    {
        m_list.next()->unlink();
    }
}

TEMPLATE_ILIST
void TILIST::remove(TOwner& _owner)
{
    // no way to check list ownership
    IListNode* node = to_node(&_owner);
    node->unlink();
}

TEMPLATE_ILIST
void TILIST::erase(iterator& _iter)
{
    MP_ASSERT(_iter.m_list == &m_list);
    _iter.m_node.unlink();
}

TEMPLATE_ILIST
void TILIST::push_front(TOwner& _item)
{
    IListNode* node = to_node(&_item);
    node->insert_me_after(m_list);
}

TEMPLATE_ILIST
void TILIST::pop_front()
{
    if(!empty())
    {
        to_node(&front())->unlink();
    }
}

TEMPLATE_ILIST
void TILIST::push_back(TOwner& _item)
{
    IListNode* node = to_node(&_item);
    node->insert_me_before(m_list);
}

TEMPLATE_ILIST
void TILIST::pop_back()
{
    if(!empty())
    {
        to_node(&back())->unlink();
    }
}


// entire other list into me at pos
TEMPLATE_ILIST
void TILIST::splice(iterator _pos, TILIST& _other)
{
    if (_other.empty())
        return;

    splice(_pos, _other, _other.begin(), _other.end());
}

// single other element into me at pos
TEMPLATE_ILIST
void TILIST::splice(iterator _pos, TILIST& _other, iterator _other_i)
{
    if (_other_i == _other.end())
        return;

    MP_ASSERT(!_other.empty());

    _other_i.m_node->insert_me_after(_pos.m_node);
}

// other element range into me at pos 	
TEMPLATE_ILIST
void TILIST::splice(iterator _pos, TILIST& _other, iterator _other_first, iterator _other_last)
{
    if (_other.empty())
        return;

    if (_other_first == _other.end())
        return;

    if (_other_last == _other.end())
        --_other_last;

    IListNode* pos = _pos.m_node;
    IListNode* tail = pos->next();

    IListNode* other_head = _other_first.m_node;
    IListNode* other_tail = _other_last.m_node;

    other_head->prev()->next() = other_tail->next();
    other_tail->next()->prev() = other_head->prev();
    
    pos->next() = other_head;    
    other_head->prev() = pos;    

    tail->prev() = other_tail;
    other_tail->next() = tail;
}


TEMPLATE_ILIST template<class Compare>
typename TILIST::iterator TILIST::drop_sort(iterator _pos, TOwner& _owner, Compare compare)
{
    while (_pos != end() && compare(*to_owner(_pos.m_node), _owner))
    {
        ++_pos;
    }

    IListNode* node = to_node(&_owner);
    node->insert_me_before(*_pos.m_node);
    return iterator(*this, *node->next());
}

TEMPLATE_ILIST template<class Compare>
void TILIST::merge(IList& _other, Compare compare)
{
    iterator pos = begin();
    while(!_other.empty())
    {
        pos = drop_sort(pos, *_other.begin(), compare);
    }
}


TEMPLATE_ILIST template<class Compare>
void TILIST::sort(Compare compare)
{
    if (empty())
        return; //  empty, nothing to sort
    if (m_list.next()->next() == &m_list)
        return; // just one node, nothing to sort

    _sort(compare, size());
}


TEMPLATE_ILIST template<class Compare>
void TILIST::_sort(Compare compare, size_t _list_size)
{
    if (_list_size < 2)
        return;

    if (_list_size == 2)
    {
        TOwner* n = &front();
        pop_front();
        drop_sort(begin(), *n, compare);
        return;
    }

    const size_t pivot = _list_size/2;
    const size_t rsize = _list_size - pivot;

    TILIST rlist;
    {
        iterator itr = begin();
        size_t count = pivot+1;
        while (--count) 
        { 
            ++itr; 
        }
        rlist.splice(rlist.begin(), *this, itr, end());
    }

    this->_sort(compare, pivot);
    rlist._sort(compare, rsize);

    merge(rlist, compare);
}




// undefine shorthand template stuff
#undef TILIST
#undef TEMPLATE_ILIST


}} // namespace makeplay::core

