// vector standard header
#pragma once
#ifndef _VECTOR_
#define _VECTOR_
#ifndef RC_INVOKED
#include <xmemory>
#include <stdexcept>

#pragma pack(push,_CRT_PACKING)
#pragma warning(push,3)
#pragma push_macro("new")
#undef new

#pragma warning(disable: 4127)
#pragma warning(disable: 4244)

_STD_BEGIN
#define _VECTOR_ORPHAN_RANGE   (_ITERATOR_DEBUG_LEVEL == 2)

// TEMPLATE CLASS _Vector_const_iterator
template<class _Myvec>
class _Vector_const_iterator
    : public _Iterator012<random_access_iterator_tag,
      typename _Myvec::value_type,
      typename _Myvec::difference_type,
      typename _Myvec::const_pointer,
      typename _Myvec::const_reference,
      _Iterator_base>
{
    // iterator for nonmutable vector
public:
    typedef _Vector_const_iterator<_Myvec> _Myiter;
    typedef random_access_iterator_tag iterator_category;

    typedef typename _Myvec::value_type value_type;
    typedef typename _Myvec::difference_type difference_type;
    typedef typename _Myvec::const_pointer pointer;
    typedef typename _Myvec::const_reference reference;
    typedef typename _Myvec::pointer _Tptr;

    _Vector_const_iterator()
        : _Ptr()
    {
        // construct with null pointer
    }

    _Vector_const_iterator(_Tptr _Parg, const _Container_base *_Pvector)
        : _Ptr(_Parg)
    {
        // construct with pointer _Parg
        this->_Adopt(_Pvector);
    }

    typedef pointer _Unchecked_type;

    _Myiter& _Rechecked(_Unchecked_type _Right)
    {
        // reset from unchecked iterator
        this->_Ptr = (_Tptr)_Right;
        return (*this);
    }

    _Unchecked_type _Unchecked() const
    {
        // make an unchecked iterator
        return (_Unchecked_type(this->_Ptr));
    }

    reference operator*() const
    {
        // return designated object
#if _ITERATOR_DEBUG_LEVEL == 2
        if (this->_Getcont() == 0
            || this->_Ptr == 0
            || this->_Ptr < ((_Myvec *)this->_Getcont())->_Myfirst
            || ((_Myvec *)this->_Getcont())->_Mylast <= this->_Ptr) {
            // report error
            _DEBUG_ERROR("vector iterator not dereferencable");
            _SCL_SECURE_OUT_OF_RANGE;
        }

#elif _ITERATOR_DEBUG_LEVEL == 1
        _SCL_SECURE_VALIDATE(this->_Getcont() != 0);
        _SCL_SECURE_VALIDATE_RANGE(
            this->_Ptr != _Tptr()
            && ((_Myvec *)this->_Getcont())->_Myfirst <= this->_Ptr
            && this->_Ptr < ((_Myvec *)this->_Getcont())->_Mylast);
#endif /* _ITERATOR_DEBUG_LEVEL */

        _Analysis_assume_(this->_Ptr != _Tptr());

        return (*this->_Ptr);
    }

    pointer operator->() const
    {
        // return pointer to class object
        return (_STD pointer_traits<pointer>::pointer_to(**this));
    }

    _Myiter& operator++()
    {
        // preincrement
#if _ITERATOR_DEBUG_LEVEL == 2
        if (this->_Getcont() == 0
            || this->_Ptr == 0
            || ((_Myvec *)this->_Getcont())->_Mylast <= this->_Ptr) {
            // report error
            _DEBUG_ERROR("vector iterator not incrementable");
            _SCL_SECURE_OUT_OF_RANGE;
        }

#elif _ITERATOR_DEBUG_LEVEL == 1
        _SCL_SECURE_VALIDATE(this->_Getcont() != 0);
        _SCL_SECURE_VALIDATE_RANGE(
            this->_Ptr != _Tptr()
            && this->_Ptr < ((_Myvec *)this->_Getcont())->_Mylast);
#endif /* _ITERATOR_DEBUG_LEVEL */

        ++this->_Ptr;
        return (*this);
    }

    _Myiter operator++(int)
    {
        // postincrement
        _Myiter _Tmp = *this;
        ++*this;
        return (_Tmp);
    }

    _Myiter& operator--()
    {
        // predecrement
#if _ITERATOR_DEBUG_LEVEL == 2
        if (this->_Getcont() == 0
            || this->_Ptr == 0
            || this->_Ptr <= ((_Myvec *)this->_Getcont())->_Myfirst) {
            // report error
            _DEBUG_ERROR("vector iterator not decrementable");
            _SCL_SECURE_OUT_OF_RANGE;
        }

#elif _ITERATOR_DEBUG_LEVEL == 1
        _SCL_SECURE_VALIDATE(this->_Getcont() != 0);
        _SCL_SECURE_VALIDATE_RANGE(
            this->_Ptr != _Tptr()
            && ((_Myvec *)this->_Getcont())->_Myfirst < this->_Ptr);
#endif /* _ITERATOR_DEBUG_LEVEL */

        --this->_Ptr;
        return (*this);
    }

    _Myiter operator--(int)
    {
        // postdecrement
        _Myiter _Tmp = *this;
        --*this;
        return (_Tmp);
    }

    _Myiter& operator+=(difference_type _Off)
    {
        // increment by integer
#if _ITERATOR_DEBUG_LEVEL == 2
        if (this->_Getcont() == 0
            || this->_Ptr + _Off < ((_Myvec *)this->_Getcont())->_Myfirst
            || ((_Myvec *)this->_Getcont())->_Mylast < this->_Ptr + _Off) {
            // report error
            _DEBUG_ERROR("vector iterator + offset out of range");
            _SCL_SECURE_OUT_OF_RANGE;
        }

#elif _ITERATOR_DEBUG_LEVEL == 1
        _SCL_SECURE_VALIDATE(this->_Getcont() != 0);
        _SCL_SECURE_VALIDATE_RANGE(
            ((_Myvec *)this->_Getcont())->_Myfirst <= this->_Ptr + _Off
            && this->_Ptr + _Off <= ((_Myvec *)this->_Getcont())->_Mylast);
#endif /* _ITERATOR_DEBUG_LEVEL */

        _Ptr += _Off;
        return (*this);
    }

    _Myiter operator+(difference_type _Off) const
    {
        // return this + integer
        _Myiter _Tmp = *this;
        return (_Tmp += _Off);
    }

    _Myiter& operator-=(difference_type _Off)
    {
        // decrement by integer
        return (*this += -_Off);
    }

    _Myiter operator-(difference_type _Off) const
    {
        // return this - integer
        _Myiter _Tmp = *this;
        return (_Tmp -= _Off);
    }

    difference_type operator-(const _Myiter& _Right) const
    {
        // return difference of iterators
        _Compat(_Right);
        return (this->_Ptr - _Right._Ptr);
    }

    reference operator[](difference_type _Off) const
    {
        // subscript
        return (*(*this + _Off));
    }

    bool operator==(const _Myiter& _Right) const
    {
        // test for iterator equality
        _Compat(_Right);
        return (this->_Ptr == _Right._Ptr);
    }

    bool operator!=(const _Myiter& _Right) const
    {
        // test for iterator inequality
        return (!(*this == _Right));
    }

    bool operator<(const _Myiter& _Right) const
    {
        // test if this < _Right
        _Compat(_Right);
        return (this->_Ptr < _Right._Ptr);
    }

    bool operator>(const _Myiter& _Right) const
    {
        // test if this > _Right
        return (_Right < *this);
    }

    bool operator<=(const _Myiter& _Right) const
    {
        // test if this <= _Right
        return (!(_Right < *this));
    }

    bool operator>=(const _Myiter& _Right) const
    {
        // test if this >= _Right
        return (!(*this < _Right));
    }

#if _ITERATOR_DEBUG_LEVEL == 2
    void _Compat(const _Myiter& _Right) const
    {
        // test for compatible iterator pair
        if (this->_Getcont() == 0
            || this->_Getcont() != _Right._Getcont()) {
            // report error
            _DEBUG_ERROR("vector iterators incompatible");
            _SCL_SECURE_INVALID_ARGUMENT;
        }
    }

#elif _ITERATOR_DEBUG_LEVEL == 1
    void _Compat(const _Myiter& _Right) const
    {
        // test for compatible iterator pair
        _SCL_SECURE_VALIDATE(this->_Getcont() != 0);
        _SCL_SECURE_VALIDATE_RANGE(this->_Getcont() == _Right._Getcont());
    }

#else /* _ITERATOR_DEBUG_LEVEL == 0 */
    void _Compat(const _Myiter&) const
    {
        // test for compatible iterator pair
    }
#endif /* _ITERATOR_DEBUG_LEVEL */

    _Tptr _Ptr; // pointer to element in vector
};

template<class _Myvec> inline
typename _Vector_const_iterator<_Myvec>::_Unchecked_type
_Unchecked(_Vector_const_iterator<_Myvec> _Iter)
{
    // convert to unchecked
    return (_Iter._Unchecked());
}

template<class _Myvec> inline
_Vector_const_iterator<_Myvec>&
_Rechecked(_Vector_const_iterator<_Myvec>& _Iter,
           typename _Vector_const_iterator<_Myvec>
           ::_Unchecked_type _Right)
{
    // convert to checked
    return (_Iter._Rechecked(_Right));
}

template<class _Myvec> inline
_Vector_const_iterator<_Myvec> operator+(
    typename _Vector_const_iterator<_Myvec>::difference_type _Off,
    _Vector_const_iterator<_Myvec> _Next)
{
    // add offset to iterator
    return (_Next += _Off);
}

// TEMPLATE CLASS _Vector_iterator
template<class _Myvec>
class _Vector_iterator
    : public _Vector_const_iterator<_Myvec>
{
    // iterator for mutable vector
public:
    typedef _Vector_iterator<_Myvec> _Myiter;
    typedef _Vector_const_iterator<_Myvec> _Mybase;
    typedef random_access_iterator_tag iterator_category;

    typedef typename _Myvec::value_type value_type;
    typedef typename _Myvec::difference_type difference_type;
    typedef typename _Myvec::pointer pointer;
    typedef typename _Myvec::reference reference;

    _Vector_iterator()
    {
        // construct with null vector pointer
    }

    _Vector_iterator(pointer _Parg, const _Container_base *_Pvector)
        : _Mybase(_Parg, _Pvector)
    {
        // construct with pointer _Parg
    }

    typedef pointer _Unchecked_type;

    _Myiter& _Rechecked(_Unchecked_type _Right)
    {
        // reset from unchecked iterator
        this->_Ptr = _Right;
        return (*this);
    }

    _Unchecked_type _Unchecked() const
    {
        // make an unchecked iterator
        return (_Unchecked_type(this->_Ptr));
    }

    reference operator*() const
    {
        // return designated object
        return ((reference)**(_Mybase *)this);
    }

    pointer operator->() const
    {
        // return pointer to class object
        return (_STD pointer_traits<pointer>::pointer_to(**this));
    }

    _Myiter& operator++()
    {
        // preincrement
        ++*(_Mybase *)this;
        return (*this);
    }

    _Myiter operator++(int)
    {
        // postincrement
        _Myiter _Tmp = *this;
        ++*this;
        return (_Tmp);
    }

    _Myiter& operator--()
    {
        // predecrement
        --*(_Mybase *)this;
        return (*this);
    }

    _Myiter operator--(int)
    {
        // postdecrement
        _Myiter _Tmp = *this;
        --*this;
        return (_Tmp);
    }

    _Myiter& operator+=(difference_type _Off)
    {
        // increment by integer
        *(_Mybase *)this += _Off;
        return (*this);
    }

    _Myiter operator+(difference_type _Off) const
    {
        // return this + integer
        _Myiter _Tmp = *this;
        return (_Tmp += _Off);
    }

    _Myiter& operator-=(difference_type _Off)
    {
        // decrement by integer
        return (*this += -_Off);
    }

    _Myiter operator-(difference_type _Off) const
    {
        // return this - integer
        _Myiter _Tmp = *this;
        return (_Tmp -= _Off);
    }

    difference_type operator-(const _Mybase& _Right) const
    {
        // return difference of iterators
        return (*(_Mybase *)this - _Right);
    }

    reference operator[](difference_type _Off) const
    {
        // subscript
        return (*(*this + _Off));
    }
};

template<class _Myvec> inline
typename _Vector_iterator<_Myvec>::_Unchecked_type
_Unchecked(_Vector_iterator<_Myvec> _Iter)
{
    // convert to unchecked
    return (_Iter._Unchecked());
}

template<class _Myvec> inline
_Vector_iterator<_Myvec>&
_Rechecked(_Vector_iterator<_Myvec>& _Iter,
           typename _Vector_iterator<_Myvec>
           ::_Unchecked_type _Right)
{
    // convert to checked
    return (_Iter._Rechecked(_Right));
}

template<class _Myvec> inline
_Vector_iterator<_Myvec> operator+(
    typename _Vector_iterator<_Myvec>::difference_type _Off,
    _Vector_iterator<_Myvec> _Next)
{
    // add offset to iterator
    return (_Next += _Off);
}

// vector TYPE WRAPPERS
template<class _Value_type,
         class _Size_type,
         class _Difference_type,
         class _Pointer,
         class _Const_pointer,
         class _Reference,
         class _Const_reference>
struct _Vec_iter_types {
    // wraps types needed by iterators
    typedef _Value_type value_type;
    typedef _Size_type size_type;
    typedef _Difference_type difference_type;
    typedef _Pointer pointer;
    typedef _Const_pointer const_pointer;
    typedef _Reference reference;
    typedef _Const_reference const_reference;
};

template<class _Ty,
         class _Alloc0>
struct _Vec_base_types {
    // types needed for a container base
    typedef _Alloc0 _Alloc;
    typedef _Vec_base_types<_Ty, _Alloc> _Myt;

    typedef _Wrap_alloc<_Alloc> _Alty0;
    typedef typename _Alty0::template rebind<_Ty>::other _Alty;


    typedef typename _Alty::pointer _Tptr;
    typedef typename _Alty::template rebind<_Tptr>::other _Alpty;

    typedef typename _If<_Is_simple_alloc<_Alty>::value,
            _Simple_types<typename _Alty::value_type>,
            _Vec_iter_types<typename _Alty::value_type,
            typename _Alty::size_type,
            typename _Alty::difference_type,
            typename _Alty::pointer,
            typename _Alty::const_pointer,
            typename _Alty::reference,
            typename _Alty::const_reference> >::type
            _Val_types;
};

// TEMPLATE CLASS _Vector_val
template<class _Val_types>
class _Vector_val
    : public _Container_base
{
    // base class for vector to hold data
public:
    typedef _Vector_val<_Val_types> _Myt;

    typedef typename _Val_types::value_type value_type;
    typedef typename _Val_types::size_type size_type;
    typedef typename _Val_types::difference_type difference_type;
    typedef typename _Val_types::pointer pointer;
    typedef typename _Val_types::const_pointer const_pointer;
    typedef typename _Val_types::reference reference;
    typedef typename _Val_types::const_reference const_reference;

    typedef _Vector_iterator<_Myt> iterator;
    typedef _Vector_const_iterator<_Myt> const_iterator;

    _Vector_val()
    {
        // initialize values
        _Myfirst = pointer();
        _Mylast = pointer();
        _Myend = pointer();
    }

    pointer _Myfirst;   // pointer to beginning of array
    pointer _Mylast;    // pointer to current end of sequence
    pointer _Myend; // pointer to end of array
};

// TEMPLATE CLASS _Vector_alloc
template<bool _Al_has_storage,
         class _Alloc_types>
class _Vector_alloc
    : public _Vector_val<typename _Alloc_types::_Val_types>
{
    // base class for vector to hold allocator with storage
public:
    typename _Alloc_types::_Alty _Alval;    // allocator object

    typedef _Vector_alloc<_Al_has_storage, _Alloc_types> _Myt;
    typedef typename _Alloc_types::_Alloc _Alloc;
    typedef typename _Alloc_types::_Alty _Alty;

#if _ITERATOR_DEBUG_LEVEL == 0
    _Vector_alloc(const _Alloc& _Al = _Alloc())
        : _Alval(_Al)
    {
        // construct allocator from _Al
    }

    void _Change_alloc(const _Alty& _Al)
    {
        // replace old allocator
        this->_Alval = _Al;
    }

    void _Swap_alloc(_Myt& _Right)
    {
        // swap allocators
        _Swap_adl(this->_Alval, _Right._Alval);
    }

#else /* _ITERATOR_DEBUG_LEVEL == 0 */
    _Vector_alloc(const _Alty& _Al = _Alty())
        : _Alval(_Al)
    {
        // construct allocator from _Al
        _Alloc_proxy();
    }

    ~_Vector_alloc() _NOEXCEPT {
        // destroy proxy
        _Free_proxy();
    }

    void _Change_alloc(const _Alty& _Al)
    {
        // replace old allocator
        _Free_proxy();
        this->_Alval = _Al;
        _Alloc_proxy();
    }

    void _Swap_alloc(_Myt& _Right)
    {
        // swap allocators
        _Swap_adl(this->_Alval, _Right._Alval);
        _Swap_adl(this->_Myproxy, _Right._Myproxy);
    }

    void _Alloc_proxy()
    {
        // construct proxy from _Alval
        typename _Alty::template rebind<_Container_proxy>::other
        _Alproxy(this->_Alval);
        this->_Myproxy = _Alproxy.allocate(1);
        _Alproxy.construct(this->_Myproxy, _Container_proxy());
        this->_Myproxy->_Mycont = this;
    }

    void _Free_proxy()
    {
        // destroy proxy
        typename _Alty::template rebind<_Container_proxy>::other
        _Alproxy(this->_Alval);
        this->_Orphan_all();
        _Alproxy.destroy(this->_Myproxy);
        _Alproxy.deallocate(this->_Myproxy, 1);
        this->_Myproxy = 0;
    }
#endif /* _ITERATOR_DEBUG_LEVEL == 0 */

    _Alty& _Getal()
    {
        // get reference to allocator
        return (this->_Alval);
    }

    const _Alty& _Getal() const
    {
        // get reference to allocator
        return (this->_Alval);
    }
};

template<class _Alloc_types>
class _Vector_alloc<false, _Alloc_types>
    : public _Vector_val<typename _Alloc_types::_Val_types>
{
    // base class for vector to hold allocator with no storage
public:
    typedef _Vector_alloc<false, _Alloc_types> _Myt;
    typedef typename _Alloc_types::_Alloc _Alloc;

    typedef typename _Alloc_types::_Alty _Alty;

#if _ITERATOR_DEBUG_LEVEL == 0
    _Vector_alloc(const _Alloc& = _Alloc())
    {
        // construct allocator from _Al
    }

    void _Change_alloc(const _Alty&)
    {
        // replace old allocator
    }

    void _Swap_alloc(_Myt&)
    {
        // swap allocators
    }

#else /* _ITERATOR_DEBUG_LEVEL == 0 */
    _Vector_alloc(const _Alloc& = _Alloc())
    {
        // construct allocator from _Al
        _Alloc_proxy();
    }

    ~_Vector_alloc() _NOEXCEPT {
        // destroy proxy
        _Free_proxy();
    }

    void _Change_alloc(const _Alty&)
    {
        // replace old allocator
    }

    void _Swap_alloc(_Myt& _Right)
    {
        // swap allocators
        _Swap_adl(this->_Myproxy, _Right._Myproxy);
    }

    void _Alloc_proxy()
    {
        // construct proxy from _Alval
        typename _Alty::template rebind<_Container_proxy>::other
        _Alproxy;
        this->_Myproxy = _Alproxy.allocate(1);
        _Alproxy.construct(this->_Myproxy, _Container_proxy());
        this->_Myproxy->_Mycont = this;
    }

    void _Free_proxy()
    {
        // destroy proxy
        typename _Alty::template rebind<_Container_proxy>::other
        _Alproxy;
        this->_Orphan_all();
        _Alproxy.destroy(this->_Myproxy);
        _Alproxy.deallocate(this->_Myproxy, 1);
        this->_Myproxy = 0;
    }
#endif /* _ITERATOR_DEBUG_LEVEL == 0 */

    _Alty _Getal() const
    {
        // get reference to allocator
        return (_Alty());
    }
};

// TEMPLATE CLASS vector
template<class _Ty,
         class _Alloc = allocator<_Ty> >
class vector
    : public _Vector_alloc<!is_empty<_Alloc>::value,
      _Vec_base_types<_Ty, _Alloc> >
{
    // varying size array of values
public:
    typedef vector<_Ty, _Alloc> _Myt;
    typedef _Vector_alloc<!is_empty<_Alloc>::value,
            _Vec_base_types<_Ty, _Alloc> > _Mybase;
    typedef _Alloc allocator_type;

    typedef typename _Mybase::_Alty _Alty;

    typedef typename _Mybase::value_type value_type;
    typedef typename _Mybase::size_type size_type;
    typedef typename _Mybase::difference_type difference_type;
    typedef typename _Mybase::pointer pointer;
    typedef typename _Mybase::const_pointer const_pointer;
    typedef typename _Mybase::reference reference;
    typedef typename _Mybase::const_reference const_reference;

#define _VICONT(it)    it._Getcont()
#define _VIPTR(it) (it)._Ptr

    typedef typename _Mybase::iterator iterator;
    typedef typename _Mybase::const_iterator const_iterator;

    typedef _STD reverse_iterator<iterator> reverse_iterator;
    typedef _STD reverse_iterator<const_iterator> const_reverse_iterator;

    vector()
        : _Mybase()
    {
        // construct empty vector
    }

    explicit vector(const _Alloc& _Al)
        : _Mybase(_Al)
    {
        // construct empty vector, allocator
    }

    explicit vector(size_type _Count)
        : _Mybase()
    {
        // construct from _Count * value_type()
        if (_Buy(_Count)) {
            // nonzero, fill it
            _Alty _Alval(this->_Getal());
            _TRY_BEGIN
            _Uninitialized_default_fill_n(this->_Myfirst, _Count, _Alval);
            this->_Mylast += _Count;
            _CATCH_ALL
            _Tidy();
            _RERAISE;
            _CATCH_END
        }
    }

    vector(size_type _Count, const value_type& _Val)
        : _Mybase()
    {
        // construct from _Count * _Val
        _Construct_n(_Count, _STD addressof(_Val));
    }

    vector(size_type _Count, const value_type& _Val, const _Alloc& _Al)
        : _Mybase(_Al)
    {
        // construct from _Count * _Val, allocator
        _Construct_n(_Count, _STD addressof(_Val));
    }

    vector(const _Myt& _Right)

        : _Mybase(_Right._Getal().select_on_container_copy_construction())


    {
        // construct by copying _Right
        if (_Buy(_Right.size()))
            _TRY_BEGIN
            this->_Mylast = _Ucopy(_Right.begin(), _Right.end(),
                                   this->_Myfirst);
        _CATCH_ALL
        _Tidy();
        _RERAISE;
        _CATCH_END
    }

    vector(const _Myt& _Right, const _Alloc& _Al)
        : _Mybase(_Al)
    {
        // construct by copying _Right, allocator
        if (_Buy(_Right.size()))
            _TRY_BEGIN
            this->_Mylast = _Ucopy(_Right.begin(), _Right.end(),
                                   this->_Myfirst);
        _CATCH_ALL
        _Tidy();
        _RERAISE;
        _CATCH_END
    }

    template<class _Iter,
             class = typename enable_if<_Is_iterator<_Iter>::value,
                                        void>:: type>
    vector(_Iter _First, _Iter _Last)
        : _Mybase()
    {
        // construct from [_First, _Last)
        _Construct(_First, _Last);
    }

    template<class _Iter,
             class = typename enable_if<_Is_iterator<_Iter>::value,
                                        void>:: type>
    vector(_Iter _First, _Iter _Last, const _Alloc& _Al)
        : _Mybase(_Al)
    {
        // construct from [_First, _Last) with allocator
        _Construct(_First, _Last);
    }

    template<class _Iter>
    void _Construct(_Iter _First, _Iter _Last)
    {
        // initialize with [_First, _Last)
        _Construct(_First, _Last, _Iter_cat(_First));
    }

    template<class _Iter>
    void _Construct(_Iter _First, _Iter _Last, input_iterator_tag)
    {
        // initialize with [_First, _Last), input iterators
        _TRY_BEGIN

        for (; _First != _Last; ++_First)
            emplace_back(*_First);

        _CATCH_ALL
        _Tidy();
        _RERAISE;
        _CATCH_END
    }

    template<class _Iter>
    void _Construct(_Iter _First, _Iter _Last, forward_iterator_tag)
    {
        // initialize with [_First, _Last), forward iterators
        if (_Buy(_STD distance(_First, _Last))) {
            // nonzero, fill it
            _TRY_BEGIN
            this->_Mylast = _Ucopy(_First, _Last, this->_Myfirst);
            _CATCH_ALL
            _Tidy();
            _RERAISE;
            _CATCH_END
        }
    }

    void _Construct_n(size_type _Count, const value_type *_Pval)
    {
        // construct from _Count * *_Pval
        if (_Buy(_Count)) {
            // nonzero, fill it
            _TRY_BEGIN
            this->_Mylast = _Ufill(this->_Myfirst, _Count, _Pval);
            _CATCH_ALL
            _Tidy();
            _RERAISE;
            _CATCH_END
        }
    }

    vector(_Myt&& _Right)
        : _Mybase(_Right._Getal())
    {
        // construct by moving _Right
        _Assign_rv(_STD forward<_Myt>(_Right), true_type());
    }

    vector(_Myt&& _Right, const _Alloc& _Al)
        : _Mybase(_Al)
    {
        // construct by moving _Right, allocator
        _Assign_rv(_STD forward<_Myt>(_Right));
    }

    _Myt& operator=(_Myt&& _Right)
    {
        // assign by moving _Right
        if (this != &_Right) {
            // different, assign it
            _Tidy();
            if (_Alty::propagate_on_container_move_assignment::value
                && this->_Getal() != _Right._Getal())
                this->_Change_alloc(_Right._Getal());

            _Assign_rv(_STD forward<_Myt>(_Right));
        }
        return (*this);
    }

    void _Assign_rv(_Myt&& _Right, true_type)
    {
        // move from _Right, stealing its contents
        this->_Swap_all((_Myt&)_Right);
        this->_Myfirst = _Right._Myfirst;
        this->_Mylast = _Right._Mylast;
        this->_Myend = _Right._Myend;

        _Right._Myfirst = pointer();
        _Right._Mylast = pointer();
        _Right._Myend = pointer();
    }

    void _Assign_rv(_Myt&& _Right, false_type)
    {
        // move from _Right, possibly moving its contents
        if (get_allocator() == _Right.get_allocator())
            _Assign_rv(_STD forward<_Myt>(_Right), true_type());
        else
            _Construct(_STD make_move_iterator(_Right.begin()),
                       _STD make_move_iterator(_Right.end()));
    }

    void _Assign_rv(_Myt&& _Right)
    {
        // assign by moving _Right
        _Assign_rv(_STD forward<_Myt>(_Right),
                   typename _Alty::propagate_on_container_move_assignment());
    }


    void push_back(value_type&& _Val)
    {
        // insert by moving into element at end
        if (_Inside(_STD addressof(_Val))) {
            // push back an element
            size_type _Idx = _STD addressof(_Val) - this->_Myfirst;
            if (this->_Mylast == this->_Myend)
                _Reserve(1);
            _Orphan_range(this->_Mylast, this->_Mylast);
            this->_Getal().construct(this->_Mylast,
                                     _STD forward<value_type>(this->_Myfirst[_Idx]));
            ++this->_Mylast;
        } else {
            // push back a non-element
            if (this->_Mylast == this->_Myend)
                _Reserve(1);
            _Orphan_range(this->_Mylast, this->_Mylast);
            this->_Getal().construct(this->_Mylast,
                                     _STD forward<value_type>(_Val));
            ++this->_Mylast;
        }
    }

    iterator insert(const_iterator _Where, _Ty&& _Val)
    {
        // insert by moving _Val at _Where
        return (emplace(_Where, _STD move(_Val)));
    }

    template<class... _Valty>
    void emplace_back(_Valty&&... _Val)
    {
        // insert by moving into element at end
        if (this->_Mylast == this->_Myend)
            _Reserve(1);
        _Orphan_range(this->_Mylast, this->_Mylast);
        this->_Getal().construct(this->_Mylast,
                                 _STD forward<_Valty>(_Val)...);
        ++this->_Mylast;
    }

    template<class... _Valty>
    iterator emplace(const_iterator _Where, _Valty&&... _Val)
    {
        // insert by moving _Val at _Where
        size_type _Off = _VIPTR(_Where) - this->_Myfirst;

#if _ITERATOR_DEBUG_LEVEL == 2
        if (size() < _Off)
            _DEBUG_ERROR("vector emplace iterator outside range");
#endif /* _ITERATOR_DEBUG_LEVEL == 2 */

        emplace_back(_STD forward<_Valty>(_Val)...);
        _STD rotate(begin() + _Off, end() - 1, end());
        return (begin() + _Off);
    }


    vector(_XSTD initializer_list<value_type> _Ilist,
           const _Alloc& _Al = allocator_type())
        : _Mybase(_Al)
    {
        // construct from initializer_list
        insert(begin(), _Ilist.begin(), _Ilist.end());
    }

    _Myt& operator=(_XSTD initializer_list<value_type> _Ilist)
    {
        // assign initializer_list
        assign(_Ilist.begin(), _Ilist.end());
        return (*this);
    }

    void assign(_XSTD initializer_list<value_type> _Ilist)
    {
        // assign initializer_list
        assign(_Ilist.begin(), _Ilist.end());
    }

    iterator insert(const_iterator _Where,
                    _XSTD initializer_list<value_type> _Ilist)
    {
        // insert initializer_list
        return (insert(_Where, _Ilist.begin(), _Ilist.end()));
    }

    ~vector() _NOEXCEPT {
        // destroy the object
        _Tidy();
    }

    _Myt& operator=(const _Myt& _Right)
    {
        // assign _Right
        if (this != &_Right) {
            // different, assign it
            if (this->_Getal() != _Right._Getal()
                && _Alty::propagate_on_container_copy_assignment::value) {
                // change allocator before copying
                _Tidy();
                this->_Change_alloc(_Right._Getal());
            }

            this->_Orphan_all();

            if (_Right.empty())
                clear();    // new sequence empty, erase existing sequence
            else if (_Right.size() <= size()) {
                // enough elements, copy new and destroy old
                pointer _Ptr = _Copy_impl(_Right._Myfirst,
                                          _Right._Mylast, this->_Myfirst);    // copy new
                _Destroy(_Ptr, this->_Mylast);  // destroy old
                this->_Mylast = this->_Myfirst + _Right.size();
            } else if (_Right.size() <= capacity()) {
                // enough room, copy and construct new
                pointer _Ptr = _Right._Myfirst + size();
                _Copy_impl(_Right._Myfirst,
                           _Ptr, this->_Myfirst);
                this->_Mylast = _Ucopy(_Ptr, _Right._Mylast, this->_Mylast);
            } else {
                // not enough room, allocate new array and construct new
                if (this->_Myfirst != pointer()) {
                    // discard old array
                    _Destroy(this->_Myfirst, this->_Mylast);
                    this->_Getal().deallocate(this->_Myfirst,
                                              this->_Myend - this->_Myfirst);
                }
                if (_Buy(_Right.size()))
                    _TRY_BEGIN
                    this->_Mylast = _Ucopy(_Right._Myfirst, _Right._Mylast,
                                           this->_Myfirst);
                _CATCH_ALL
                _Tidy();
                _RERAISE;
                _CATCH_END
            }
        }
        return (*this);
    }

    void reserve(size_type _Count)
    {
        // determine new minimum length of allocated storage
        if (capacity() < _Count) {
            // something to do, check and reallocate
            if (max_size() < _Count)
                _Xlen();
            _Reallocate(_Count);
        }
    }

    size_type capacity() const _NOEXCEPT
    {
        // return current length of allocated storage
        return (this->_Myend - this->_Myfirst);
    }

    size_type _Unused_capacity() const _NOEXCEPT
    {
        // micro-optimization for capacity() - size()
        return (this->_Myend - this->_Mylast);
    }

    size_type _Has_unused_capacity() const _NOEXCEPT
    {
        // micro-optimization for capacity() != size()
        return (this->_Myend != this->_Mylast);
    }

    iterator begin() _NOEXCEPT {
        // return iterator for beginning of mutable sequence
        return (iterator(this->_Myfirst, this));
    }

    const_iterator begin() const _NOEXCEPT
    {
        // return iterator for beginning of nonmutable sequence
        return (const_iterator(this->_Myfirst, this));
    }

    iterator end() _NOEXCEPT {
        // return iterator for end of mutable sequence
        return (iterator(this->_Mylast, this));
    }

    const_iterator end() const _NOEXCEPT
    {
        // return iterator for end of nonmutable sequence
        return (const_iterator(this->_Mylast, this));
    }

    iterator _Make_iter(const_iterator _Where) const
    {
        // make iterator from const_iterator
        return (iterator(_Where._Ptr, this));
    }

    reverse_iterator rbegin() _NOEXCEPT {
        // return iterator for beginning of reversed mutable sequence
        return (reverse_iterator(end()));
    }

    const_reverse_iterator rbegin() const _NOEXCEPT
    {
        // return iterator for beginning of reversed nonmutable sequence
        return (const_reverse_iterator(end()));
    }

    reverse_iterator rend() _NOEXCEPT {
        // return iterator for end of reversed mutable sequence
        return (reverse_iterator(begin()));
    }

    const_reverse_iterator rend() const _NOEXCEPT
    {
        // return iterator for end of reversed nonmutable sequence
        return (const_reverse_iterator(begin()));
    }

    const_iterator cbegin() const _NOEXCEPT
    {
        // return iterator for beginning of nonmutable sequence
        return (((const _Myt *)this)->begin());
    }

    const_iterator cend() const _NOEXCEPT
    {
        // return iterator for end of nonmutable sequence
        return (((const _Myt *)this)->end());
    }

    const_reverse_iterator crbegin() const _NOEXCEPT
    {
        // return iterator for beginning of reversed nonmutable sequence
        return (((const _Myt *)this)->rbegin());
    }

    const_reverse_iterator crend() const _NOEXCEPT
    {
        // return iterator for end of reversed nonmutable sequence
        return (((const _Myt *)this)->rend());
    }

    void shrink_to_fit()
    {
        // reduce capacity
        if (_Has_unused_capacity()) {
            // worth shrinking, do it
            if (empty())
                _Tidy();
            else
                _Reallocate(size());
        }
    }

    void resize(size_type _Newsize)
    {
        // determine new length, padding as needed
        if (_Newsize < size())
            _Pop_back_n(size() - _Newsize);
        else if (size() < _Newsize) {
            // pad as needed
            _Alty _Alval(this->_Getal());
            _Reserve(_Newsize - size());
            _TRY_BEGIN
            _Uninitialized_default_fill_n(this->_Mylast, _Newsize - size(),
                                          _Alval);
            _CATCH_ALL
            _Tidy();
            _RERAISE;
            _CATCH_END
            this->_Mylast += _Newsize - size();
        }
    }

    void resize(size_type _Newsize, const value_type& _Val)
    {
        // determine new length, padding with _Val elements as needed
        if (_Newsize < size())
            _Pop_back_n(size() - _Newsize);
        else if (size() < _Newsize) {
            // pad as needed
            const value_type *_Ptr = _STD addressof(_Val);

            if (_Inside(_Ptr)) {
                // padding is inside vector, recompute _Ptr after reserve
                const difference_type _Idx = _Ptr
                                             - _STD addressof(*this->_Myfirst);
                _Reserve(_Newsize - size());
                _Ptr = _STD addressof(*this->_Myfirst) + _Idx;
            } else
                _Reserve(_Newsize - size());

            _TRY_BEGIN
            _Ufill(this->_Mylast, _Newsize - size(), _Ptr);
            _CATCH_ALL
            _Tidy();
            _RERAISE;
            _CATCH_END
            this->_Mylast += _Newsize - size();
        }
    }

    size_type size() const _NOEXCEPT
    {
        // return length of sequence
        return (this->_Mylast - this->_Myfirst);
    }

    size_type max_size() const _NOEXCEPT
    {
        // return maximum possible length of sequence
        return (this->_Getal().max_size());
    }

    bool empty() const _NOEXCEPT
    {
        // test if sequence is empty
        return (this->_Myfirst == this->_Mylast);
    }

    _Alloc get_allocator() const _NOEXCEPT
    {
        // return allocator object for values
        return (this->_Getal());
    }

    const_reference at(size_type _Pos) const
    {
        // subscript nonmutable sequence with checking
        if (size() <= _Pos)
            _Xran();
        return (*(this->_Myfirst + _Pos));
    }

    reference at(size_type _Pos)
    {
        // subscript mutable sequence with checking
        if (size() <= _Pos)
            _Xran();
        return (*(this->_Myfirst + _Pos));
    }

    const_reference operator[](size_type _Pos) const
    {
        // subscript nonmutable sequence
#if _ITERATOR_DEBUG_LEVEL == 2
        if (size() <= _Pos) {
            // report error
            _DEBUG_ERROR("vector subscript out of range");
            _SCL_SECURE_OUT_OF_RANGE;
        }

#elif _ITERATOR_DEBUG_LEVEL == 1
        _SCL_SECURE_VALIDATE_RANGE(_Pos < size());
#endif /* _ITERATOR_DEBUG_LEVEL */

        return (*(this->_Myfirst + _Pos));
    }

    reference operator[](size_type _Pos)
    {
        // subscript mutable sequence
#if _ITERATOR_DEBUG_LEVEL == 2
        if (size() <= _Pos) {
            // report error
            _DEBUG_ERROR("vector subscript out of range");
            _SCL_SECURE_OUT_OF_RANGE;
        }

#elif _ITERATOR_DEBUG_LEVEL == 1
        _SCL_SECURE_VALIDATE_RANGE(_Pos < size());
#endif /* _ITERATOR_DEBUG_LEVEL */

        return (*(this->_Myfirst + _Pos));
    }

    pointer data() _NOEXCEPT {
        // return address of first element
        return (this->_Myfirst);
    }

    const_pointer data() const _NOEXCEPT
    {
        // return address of first element
        return (this->_Myfirst);
    }

    reference front()
    {
        // return first element of mutable sequence
        return (*begin());
    }

    const_reference front() const
    {
        // return first element of nonmutable sequence
        return (*begin());
    }

    reference back()
    {
        // return last element of mutable sequence
        return (*(end() - 1));
    }

    const_reference back() const
    {
        // return last element of nonmutable sequence
        return (*(end() - 1));
    }

    void push_back(const value_type& _Val)
    {
        // insert element at end
        if (_Inside(_STD addressof(_Val))) {
            // push back an element
            size_type _Idx = _STD addressof(_Val) - this->_Myfirst;
            if (this->_Mylast == this->_Myend)
                _Reserve(1);
            _Orphan_range(this->_Mylast, this->_Mylast);
            this->_Getal().construct(this->_Mylast,
                                     this->_Myfirst[_Idx]);
            ++this->_Mylast;
        } else {
            // push back a non-element
            if (this->_Mylast == this->_Myend)
                _Reserve(1);
            _Orphan_range(this->_Mylast, this->_Mylast);
            this->_Getal().construct(this->_Mylast,
                                     _Val);
            ++this->_Mylast;
        }
    }

#if _ITERATOR_DEBUG_LEVEL == 2
    void pop_back()
    {
        // erase element at end
        if (empty())
            _DEBUG_ERROR("vector empty before pop");
        else {
            // erase last element
            _Orphan_range(this->_Mylast - 1, this->_Mylast);
            this->_Getal().destroy(this->_Mylast - 1);
            --this->_Mylast;
        }
    }

#else /* _ITERATOR_DEBUG_LEVEL == 2 */
    void pop_back()
    {
        // erase element at end
        this->_Getal().destroy(this->_Mylast - 1);
        --this->_Mylast;
    }
#endif /* _ITERATOR_DEBUG_LEVEL == 2 */

    template<class _Iter>
    typename enable_if<_Is_iterator<_Iter>::value,
             void>::type
             assign(_Iter _First, _Iter _Last)
    {
        // assign [_First, _Last)
        clear();
        _Assign(_First, _Last, _Iter_cat(_First));
    }

    template<class _Iter>
    void _Assign(_Iter _First, _Iter _Last, input_iterator_tag)
    {
        // assign [_First, _Last), input iterators
        for (; _First != _Last; ++_First)
            emplace_back(*_First);
    }

    template<class _Iter>
    void _Assign(_Iter _First, _Iter _Last, forward_iterator_tag)
    {
        // assign [_First, _Last), forward iterators
        if (_First == _Last)
            return; // nothing to do

        size_type _Newsize = _STD distance(_First, _Last);

        if (capacity() < _Newsize) {
            // need more room, try to get it
            size_type _Newcapacity = _Grow_to(_Newsize);
            _Tidy();
            _Buy(_Newcapacity);
        }

        this->_Mylast = _Ucopy(_First, _Last, this->_Myfirst);
    }

    void assign(size_type _Count, const value_type& _Val)
    {
        // assign _Count * _Val
        clear();
        insert(begin(), _Count, _Val);
    }

    iterator insert(const_iterator _Where, const _Ty& _Val)
    {
        // insert _Val at _Where
        return (_Insert_n(_Where, (size_type)1, _Val));
    }

    iterator insert(const_iterator _Where, size_type _Count,
                    const _Ty& _Val)
    {
        // insert _Count * _Val at _Where
        return (_Insert_n(_Where, _Count, _Val));
    }

    template<class _Iter>
    typename enable_if<_Is_iterator<_Iter>::value,
             iterator>::type
             insert(const_iterator _Where, _Iter _First, _Iter _Last)
    {
        // insert [_First, _Last) at _Where
        size_type _Off = _VIPTR(_Where) - this->_Myfirst;
        _Insert(_Where, _First, _Last, _Iter_cat(_First));
        return (begin() + _Off);
    }

    template<class _Iter>
    void _Insert(const_iterator _Where, _Iter _First, _Iter _Last,
                 input_iterator_tag)
    {
        // insert [_First, _Last) at _Where, input iterators
        size_type _Off = _VIPTR(_Where) - this->_Myfirst;

#if _ITERATOR_DEBUG_LEVEL == 2
        if (size() < _Off)
            _DEBUG_ERROR("vector insert iterator outside range");
#endif /* _ITERATOR_DEBUG_LEVEL == 2 */

        if (_First != _Last) {
            // worth doing, gather at end and rotate into place
            size_type _Oldsize = size();

            _TRY_BEGIN
            for (; _First != _Last; ++_First)
                push_back(*_First); // append

            _CATCH_ALL
            erase(begin() + _Oldsize, end());
            _RERAISE;
            _CATCH_END

            _STD rotate(begin() + _Off, begin() + _Oldsize, end());
        }
    }

    template<class _Iter>
    void _Insert(const_iterator _Where, _Iter _First, _Iter _Last,
                 forward_iterator_tag)
    {
        // insert [_First, _Last) at _Where, forward iterators
#if _ITERATOR_DEBUG_LEVEL == 2
        if (_VICONT(_Where) != this
            || _VIPTR(_Where) < this->_Myfirst
            || this->_Mylast < _VIPTR(_Where))
            _DEBUG_ERROR("vector insert iterator outside range");
        _DEBUG_RANGE(_First, _Last);
#endif /* _ITERATOR_DEBUG_LEVEL == 2 */

        size_type _Count = 0;
        _Distance(_First, _Last, _Count);

        if (_Count == 0)
            ;
        else if (_Unused_capacity() < _Count) {
            // not enough room, reallocate
            if (max_size() - size() < _Count)
                _Xlen();    // result too long

            size_type _Capacity = _Grow_to(size() + _Count);
            pointer _Newvec = this->_Getal().allocate(_Capacity);
            pointer _Ptr = _Newvec;

            _TRY_BEGIN
            _Ptr = _Umove(this->_Myfirst, _VIPTR(_Where),
                          _Newvec);   // copy prefix
            _Ptr = _Ucopy(_First, _Last, _Ptr); // add new stuff
            _Umove(_VIPTR(_Where), this->_Mylast,
                   _Ptr);  // copy suffix
            _CATCH_ALL
            _Destroy(_Newvec, _Ptr);
            this->_Getal().deallocate(_Newvec, _Capacity);
            _RERAISE;
            _CATCH_END

            _Count += size();
            if (this->_Myfirst != pointer()) {
                // destroy and deallocate old array
                _Destroy(this->_Myfirst, this->_Mylast);
                this->_Getal().deallocate(this->_Myfirst,
                                          this->_Myend - this->_Myfirst);
            }

            this->_Orphan_all();
            this->_Myend = _Newvec + _Capacity;
            this->_Mylast = _Newvec + _Count;
            this->_Myfirst = _Newvec;
        } else {
            // new stuff fits, append and rotate into place
            _Ucopy(_First, _Last, this->_Mylast);
            _STD rotate(_VIPTR(_Where), this->_Mylast,
                        this->_Mylast + _Count);
            this->_Mylast += _Count;
            _Orphan_range(_VIPTR(_Where), this->_Mylast);
        }
    }

#if _ITERATOR_DEBUG_LEVEL == 2
    iterator erase(const_iterator _Where)
    {
        // erase element at where
        if (_VICONT(_Where) != this
            || _VIPTR(_Where) < this->_Myfirst
            || this->_Mylast <= _VIPTR(_Where))
            _DEBUG_ERROR("vector erase iterator outside range");
        _Move(_VIPTR(_Where) + 1, this->_Mylast, _VIPTR(_Where));
        _Destroy(this->_Mylast - 1, this->_Mylast);
        _Orphan_range(_VIPTR(_Where), this->_Mylast);
        --this->_Mylast;
        return (_Make_iter(_Where));
    }

#else /* _ITERATOR_DEBUG_LEVEL == 2 */
    iterator erase(const_iterator _Where)
    {
        // erase element at where
        _Move(_VIPTR(_Where) + 1, this->_Mylast,
              _VIPTR(_Where));
        _Destroy(this->_Mylast - 1, this->_Mylast);
        --this->_Mylast;
        return (_Make_iter(_Where));
    }
#endif /* _ITERATOR_DEBUG_LEVEL == 2 */

    iterator erase(const_iterator _First_arg,
                   const_iterator _Last_arg)
    {
        // erase [_First, _Last)
        if (_First_arg == begin() && _Last_arg == end())
            clear();
        else if (_First_arg != _Last_arg) {
            // clear partial
            iterator _First = _Make_iter(_First_arg);
            iterator _Last = _Make_iter(_Last_arg);

            if (_First != _Last) {
                // worth doing, copy down over hole
#if _ITERATOR_DEBUG_LEVEL == 2
                if (_Last < _First || _VICONT(_First) != this
                    || _VIPTR(_First) < this->_Myfirst
                    || this->_Mylast < _VIPTR(_Last))
                    _DEBUG_ERROR("vector erase iterator outside range");
                pointer _Ptr = _Move(_VIPTR(_Last), this->_Mylast,
                                     _VIPTR(_First));
                _Orphan_range(_VIPTR(_First), this->_Mylast);

#else /* _ITERATOR_DEBUG_LEVEL == 2 */
                pointer _Ptr = _Move(_VIPTR(_Last), this->_Mylast,
                                     _VIPTR(_First));
#endif /* _ITERATOR_DEBUG_LEVEL == 2 */

                _Destroy(_Ptr, this->_Mylast);
                this->_Mylast = _Ptr;
            }
        }
        return (_Make_iter(_First_arg));
    }

    void _Pop_back_n(size_type _Count)
    {
        // erase _Count elements at end
        pointer _Ptr = this->_Mylast - _Count;

#if _ITERATOR_DEBUG_LEVEL == 2
        _Orphan_range(_Ptr, this->_Mylast);
#endif /* _ITERATOR_DEBUG_LEVEL == 2 */

        _Destroy(_Ptr, this->_Mylast);
        this->_Mylast = _Ptr;
    }

    void clear() _NOEXCEPT {
        // erase all
        this->_Orphan_all();
        _Destroy(this->_Myfirst, this->_Mylast);
        this->_Mylast = this->_Myfirst;
    }

    void swap(_Myt& _Right)
    {
        // exchange contents with _Right
        if (this == &_Right)
            ;   // same object, do nothing
        else if (this->_Getal() == _Right._Getal()) {
            // same allocator, swap control information
            this->_Swap_all(_Right);
            _Swap_adl(this->_Myfirst, _Right._Myfirst);
            _Swap_adl(this->_Mylast, _Right._Mylast);
            _Swap_adl(this->_Myend, _Right._Myend);
        }

        else if (_Alty::propagate_on_container_swap::value) {
            // swap allocators and control information
            this->_Swap_alloc(_Right);
            _Swap_adl(this->_Myfirst, _Right._Myfirst);
            _Swap_adl(this->_Mylast, _Right._Mylast);
            _Swap_adl(this->_Myend, _Right._Myend);
        }

        else {
            // containers are incompatible
#if _ITERATOR_DEBUG_LEVEL == 2
            _DEBUG_ERROR("vector containers incompatible for swap");

#else /* ITERATOR_DEBUG_LEVEL == 2 */
            _XSTD terminate();
#endif /* ITERATOR_DEBUG_LEVEL == 2 */
        }
    }

protected:
    bool _Buy(size_type _Capacity)
    {
        // allocate array with _Capacity elements
        this->_Myfirst = pointer();
        this->_Mylast = pointer();
        this->_Myend = pointer();

        if (_Capacity == 0)
            return (false);
        else if (max_size() < _Capacity)
            _Xlen();    // result too long
        else {
            // nonempty array, allocate storage
            this->_Myfirst = this->_Getal().allocate(_Capacity);
            this->_Mylast = this->_Myfirst;
            this->_Myend = this->_Myfirst + _Capacity;
        }
        return (true);
    }

    void _Destroy(pointer _First, pointer _Last)
    {
        // destroy [_First, _Last) using allocator
        _Alty _Alval(this->_Getal());
        _Destroy_range(_First, _Last, _Alval);
    }

    size_type _Grow_to(size_type _Count) const
    {
        // grow by 50% or at least to _Count
        size_type _Capacity = capacity();

        _Capacity = max_size() - _Capacity / 2 < _Capacity
                    ? 0 : _Capacity + _Capacity / 2;    // try to grow by 50%
        if (_Capacity < _Count)
            _Capacity = _Count;
        return (_Capacity);
    }

    bool _Inside(const value_type *_Ptr) const
    {
        // test if _Ptr points inside vector
        return (_Ptr < this->_Mylast && this->_Myfirst <= _Ptr);
    }

    void _Reallocate(size_type _Count)
    {
        // move to array of exactly _Count elements
        pointer _Ptr = this->_Getal().allocate(_Count);

        _TRY_BEGIN
        _Umove(this->_Myfirst, this->_Mylast, _Ptr);
        _CATCH_ALL
        this->_Getal().deallocate(_Ptr, _Count);
        _RERAISE;
        _CATCH_END

        size_type _Size = size();
        if (this->_Myfirst != pointer()) {
            // destroy and deallocate old array
            _Destroy(this->_Myfirst, this->_Mylast);
            this->_Getal().deallocate(this->_Myfirst,
                                      this->_Myend - this->_Myfirst);
        }

        this->_Orphan_all();
        this->_Myend = _Ptr + _Count;
        this->_Mylast = _Ptr + _Size;
        this->_Myfirst = _Ptr;
    }

    void _Reserve(size_type _Count)
    {
        // ensure room for _Count new elements, grow exponentially
        if (_Unused_capacity() < _Count) {
            // need more room, try to get it
            if (max_size() - size() < _Count)
                _Xlen();
            _Reallocate(_Grow_to(size() + _Count));
        }
    }

    void _Tidy()
    {
        // free all storage
        if (this->_Myfirst != pointer()) {
            // something to free, destroy and deallocate it
            this->_Orphan_all();
            _Destroy(this->_Myfirst, this->_Mylast);
            this->_Getal().deallocate(this->_Myfirst,
                                      this->_Myend - this->_Myfirst);
            this->_Myfirst = pointer();
            this->_Mylast = pointer();
            this->_Myend = pointer();
        }
    }

    template<class _Iter>
    pointer _Ucopy(_Iter _First, _Iter _Last, pointer _Ptr)
    {
        // copy initializing [_First, _Last), using allocator
        _Alty _Alval(this->_Getal());
        return (_Uninitialized_copy(_First, _Last,
                                    _Ptr, _Alval));
    }

    template<class _Iter>
    pointer _Umove(_Iter _First, _Iter _Last, pointer _Ptr)
    {
        // move initializing [_First, _Last), using allocator
        _Alty _Alval(this->_Getal());
        return (_Uninitialized_move(_First, _Last,
                                    _Ptr, _Alval));
    }

    iterator _Insert_n(const_iterator _Where,
                       size_type _Count, const value_type& _Val)
    {
        // insert _Count * _Val at _Where
#if _ITERATOR_DEBUG_LEVEL == 2
        if (_VICONT(_Where) != this
            || _VIPTR(_Where) < this->_Myfirst
            || this->_Mylast < _VIPTR(_Where))
            _DEBUG_ERROR("vector insert iterator outside range");
#endif /* _ITERATOR_DEBUG_LEVEL == 2 */

        size_type _Off = _VIPTR(_Where) - this->_Myfirst;
        if (_Count == 0)
            ;
        else if (_Unused_capacity() < _Count) {
            // not enough room, reallocate
            if (max_size() - size() < _Count)
                _Xlen();    // result too long

            size_type _Capacity = _Grow_to(size() + _Count);
            pointer _Newvec = this->_Getal().allocate(_Capacity);
            size_type _Whereoff = _VIPTR(_Where) - this->_Myfirst;
            int _Ncopied = 0;

            _TRY_BEGIN
            _Ufill(_Newvec + _Whereoff, _Count,
                   _STD addressof(_Val));  // add new stuff
            ++_Ncopied;
            _Umove(this->_Myfirst, _VIPTR(_Where),
                   _Newvec);   // copy prefix
            ++_Ncopied;
            _Umove(_VIPTR(_Where), this->_Mylast,
                   _Newvec + (_Whereoff + _Count));    // copy suffix
            _CATCH_ALL
            if (1 < _Ncopied)
                _Destroy(_Newvec, _Newvec + _Whereoff);
            if (0 < _Ncopied)
                _Destroy(_Newvec + _Whereoff, _Newvec + _Whereoff + _Count);
            this->_Getal().deallocate(_Newvec, _Capacity);
            _RERAISE;
            _CATCH_END

            _Count += size();
            if (this->_Myfirst != pointer()) {
                // destroy and deallocate old array
                _Destroy(this->_Myfirst, this->_Mylast);
                this->_Getal().deallocate(this->_Myfirst,
                                          this->_Myend - this->_Myfirst);
            }

            this->_Orphan_all();
            this->_Myend = _Newvec + _Capacity;
            this->_Mylast = _Newvec + _Count;
            this->_Myfirst = _Newvec;
        } else if ((size_type)(this->_Mylast - _VIPTR(_Where))
                   < _Count) {
            // new stuff spills off end
            value_type _Tmp = _Val; // in case _Val is in sequence

            _Umove(_VIPTR(_Where), this->_Mylast,
                   _VIPTR(_Where) + _Count);   // copy suffix

            _TRY_BEGIN
            _Ufill(this->_Mylast,
                   _Count - (this->_Mylast - _VIPTR(_Where)),
                   _STD addressof(_Tmp));  // insert new stuff off end
            _CATCH_ALL
            _Destroy(_VIPTR(_Where) + _Count,
                     this->_Mylast + _Count);
            _RERAISE;
            _CATCH_END

            this->_Mylast += _Count;
            _Orphan_range(_VIPTR(_Where), this->_Mylast);
            _STD fill(_VIPTR(_Where), this->_Mylast - _Count,
                      _Tmp);  // insert up to old end
        } else {
            // new stuff can all be assigned
            value_type _Tmp = _Val; // in case _Val is in sequence

            pointer _Oldend = this->_Mylast;
            this->_Mylast = _Umove(_Oldend - _Count, _Oldend,
                                   this->_Mylast); // copy suffix

            _Orphan_range(_VIPTR(_Where), this->_Mylast);
            _Copy_backward(_VIPTR(_Where), _Oldend - _Count,
                           _Oldend);   // copy hole
            _STD fill(_VIPTR(_Where),
                      _VIPTR(_Where) + _Count, _Tmp); // insert into hole
        }
        return (begin() + _Off);
    }

    pointer _Ufill(pointer _Ptr, size_type _Count, const value_type *_Pval)
    {
        // copy initializing _Count * _Val, using allocator
        _Alty _Alval(this->_Getal());
        _Uninitialized_fill_n(_Ptr, _Count, _Pval, _Alval);
        return (_Ptr + _Count);
    }

    __declspec(noreturn) void _Xlen() const
    {
        // report a length_error
        _Xlength_error("vector<T> too long");
    }

    __declspec(noreturn) void _Xran() const
    {
        // report an out_of_range error
        _Xout_of_range("invalid vector<T> subscript");
    }

#if _VECTOR_ORPHAN_RANGE
    void _Orphan_range(pointer _First, pointer _Last) const
    {
        // orphan iterators within specified (inclusive) range
        _Lockit _Lock(_LOCK_DEBUG);
        const_iterator **_Pnext = (const_iterator **)this->_Getpfirst();
        if (_Pnext != 0)
            while (*_Pnext != 0)
                if ((*_Pnext)->_Ptr < _First || _Last < (*_Pnext)->_Ptr)
                    _Pnext = (const_iterator **)(*_Pnext)->_Getpnext();
                else {
                    // orphan the iterator
                    (*_Pnext)->_Clrcont();
                    *_Pnext = *(const_iterator **)(*_Pnext)->_Getpnext();
                }
    }

#else /* _VECTOR_ORPHAN_RANGE */
    void _Orphan_range(pointer, pointer) const
    {
        // orphan iterators within specified (inclusive) range
    }
#endif /* _VECTOR_ORPHAN_RANGE */
};

// vector TEMPLATE OPERATORS

template<class _Ty,
         class _Alloc> inline
void swap(vector<_Ty, _Alloc>& _Left, vector<_Ty, _Alloc>& _Right)
{
    // swap _Left and _Right vectors
    _Left.swap(_Right);
}

template<class _Ty,
         class _Alloc> inline
bool operator==(const vector<_Ty, _Alloc>& _Left,
                const vector<_Ty, _Alloc>& _Right)
{
    // test for vector equality
    return (_Left.size() == _Right.size()
            && equal(_Left.begin(), _Left.end(), _Right.begin()));
}

template<class _Ty,
         class _Alloc> inline
bool operator!=(const vector<_Ty, _Alloc>& _Left,
                const vector<_Ty, _Alloc>& _Right)
{
    // test for vector inequality
    return (!(_Left == _Right));
}

template<class _Ty,
         class _Alloc> inline
bool operator<(const vector<_Ty, _Alloc>& _Left,
               const vector<_Ty, _Alloc>& _Right)
{
    // test if _Left < _Right for vectors
    return (lexicographical_compare(_Left.begin(), _Left.end(),
                                    _Right.begin(), _Right.end()));
}

template<class _Ty,
         class _Alloc> inline
bool operator>(const vector<_Ty, _Alloc>& _Left,
               const vector<_Ty, _Alloc>& _Right)
{
    // test if _Left > _Right for vectors
    return (_Right < _Left);
}

template<class _Ty,
         class _Alloc> inline
bool operator<=(const vector<_Ty, _Alloc>& _Left,
                const vector<_Ty, _Alloc>& _Right)
{
    // test if _Left <= _Right for vectors
    return (!(_Right < _Left));
}

template<class _Ty,
         class _Alloc> inline
bool operator>=(const vector<_Ty, _Alloc>& _Left,
                const vector<_Ty, _Alloc>& _Right)
{
    // test if _Left >= _Right for vectors
    return (!(_Left < _Right));
}

//
// TEMPLATE CLASS vector<bool, Alloc> AND FRIENDS
//
typedef unsigned int _Vbase;    // word type for vector<bool> representation
const int _VBITS = 8 * sizeof (_Vbase); // at least CHAR_BITS bits per word

// CLASS _Vb_iter_base
template<class _Alloc>
class _Vb_iter_base
    : public _Iterator012<random_access_iterator_tag,
      _Bool,
      typename _Alloc::difference_type,
      bool *,
      bool,
      _Iterator_base>
{
    // store information common to reference and iterators
public:
    typedef typename _Alloc::size_type _Sizet;
    typedef vector<_Bool, _Alloc> _Mycont;

    _Vb_iter_base()
        : _Myptr(0), _Myoff(0)
    {
        // construct with null pointer
    }

    _Vb_iter_base(const _Vbase *_Ptr, _Sizet _Off,
                  const _Container_base *_Mypvbool)
        : _Myptr(_Ptr), _Myoff(_Off)
    {
        // construct with offset and pointer
        this->_Adopt(_Mypvbool);
    }

    void _Advance(_Sizet _Off)
    {
        // advance iterator by _Off
        _Myoff += _Off;
        _Myptr += _Myoff / _VBITS;
        _Myoff %= _VBITS;
    }

    int _Valid(_Sizet _Inc) const
    {
        // test for valid incremented offset
#if _ITERATOR_DEBUG_LEVEL == 2
        _Sizet _Mysize = ((_Mycont *)this->_Getcont())->_Mysize;

        _Inc += _Myoff;
        _Inc += _VBITS * (_Myptr
                          - (((_Mycont *)this->_Getcont())->_Myvec)._Myfirst);
        return (_Inc < _Mysize ? -1 : _Inc == _Mysize ? 0 : +1);

#else /* _ITERATOR_DEBUG_LEVEL == 2 */

        return (-1);
#endif /* _ITERATOR_DEBUG_LEVEL == 2 */
    }

    const _Vbase *_Myptr;
    _Sizet _Myoff;
};

// CLASS _Vb_reference
template<class _Alloc>
class _Vb_reference
    : public _Vb_iter_base<_Alloc>
{
    // reference to a bit within a base word
    typedef _Vb_iter_base<_Alloc> _Mybase;
    typedef _Vb_reference<_Alloc> _Mytype;

    _Vb_reference() _NOEXCEPT {
        // construct with null pointer (private)
    }

public:
    _Vb_reference(const _Mybase& _Right)
        : _Mybase(_Right._Myptr, _Right._Myoff, _Right._Getcont())
    {
        // construct with base
    }

    _Mytype& operator=(const _Mytype& _Right) _NOEXCEPT {
        // assign _Vb_reference _Right to bit
        return (*this = bool(_Right));
    }

    _Mytype& operator=(bool _Val) _NOEXCEPT {
        // assign _Val to bit
        if (_Val)
            *(_Vbase *)_Getptr() |= _Mask();
        else
            *(_Vbase *)_Getptr() &= (~_Mask()); // STET
        return (*this);
    }

    void flip() _NOEXCEPT {
        // toggle the bit
        *(_Vbase *)_Getptr() ^= _Mask();
    }

    operator bool() const _NOEXCEPT
    {
        // test if bit is set
        return ((*_Getptr() & _Mask()) != 0);
    }

    const _Vbase *_Getptr() const
    {
        // get pointer to base word
#if _ITERATOR_DEBUG_LEVEL == 2
        if (this->_Getcont() == 0
            || this->_Myptr == 0
            || 0 <= this->_Valid(0)) {
            // report error
            _DEBUG_ERROR("vector<bool> iterator not dereferencable");
            _SCL_SECURE_OUT_OF_RANGE;
        }

#elif _ITERATOR_DEBUG_LEVEL == 1
        _SCL_SECURE_VALIDATE(this->_Getcont() != 0 && this->_Myptr != 0);
        _SCL_SECURE_VALIDATE_RANGE(this->_Valid(0) < 0);
#endif /* _ITERATOR_DEBUG_LEVEL */

        return (this->_Myptr);
    }

protected:
    _Vbase _Mask() const
    {
        // convert offset to mask
        return ((_Vbase)(1 << this->_Myoff));
    }
};

template<class _Alloc> inline
void swap(_Vb_reference<_Alloc> _Left,
          _Vb_reference<_Alloc> _Right)
{
    // swap _Left and _Right vector<bool> elements
    bool _Val = _Left;  // NOT _STD swap
    _Left = _Right;
    _Right = _Val;
}

// CLASS _Vb_const_iterator
template<class _Alloc>
class _Vb_const_iterator
    : public _Vb_iter_base<_Alloc>
{
    // iterator for nonmutable vector<bool>
public:
    typedef _Vb_iter_base<_Alloc> _Mybase;
    typedef _Vb_const_iterator<_Alloc> _Mytype;

    typedef _Vb_reference<_Alloc> _Reft;
    typedef bool const_reference;

    typedef random_access_iterator_tag iterator_category;
    typedef _Bool value_type;
    typedef typename _Alloc::size_type size_type;
    typedef typename _Alloc::difference_type difference_type;
    typedef const_reference *pointer;
    typedef const_reference reference;

    _Vb_const_iterator()
    {
        // construct with null reference
    }

    _Vb_const_iterator(const _Vbase *_Ptr, const _Container_base *_Mypvbool)
        : _Mybase(_Ptr, 0, _Mypvbool)
    {
        // construct with offset and pointer
    }

    const_reference operator*() const
    {
        // return (reference to) designated object
        return (_Reft(*this));
    }

    _Mytype& operator++()
    {
        // preincrement
        _Inc();
        return (*this);
    }

    _Mytype operator++(int)
    {
        // postincrement
        _Mytype _Tmp = *this;
        ++*this;
        return (_Tmp);
    }

    _Mytype& operator--()
    {
        // predecrement
        _Dec();
        return (*this);
    }

    _Mytype operator--(int)
    {
        // postdecrement
        _Mytype _Tmp = *this;
        --*this;
        return (_Tmp);
    }

    _Mytype& operator+=(difference_type _Off)
    {
        // increment by integer
        if (_Off < 0 && this->_Myoff < 0 - (size_type)_Off) {
            /* add negative increment */
            this->_Myoff += _Off;
            this->_Myptr -= 1 + ((size_type)(-1) - this->_Myoff) / _VBITS;
            this->_Myoff %= _VBITS;
        } else {
            /* add non-negative increment */
            this->_Myoff += _Off;
            this->_Myptr += this->_Myoff / _VBITS;
            this->_Myoff %= _VBITS;
        }
        return (*this);
    }

    _Mytype operator+(difference_type _Off) const
    {
        // return this + integer
        _Mytype _Tmp = *this;
        return (_Tmp += _Off);
    }

    _Mytype& operator-=(difference_type _Off)
    {
        // decrement by integer
        return (*this += -_Off);
    }

    _Mytype operator-(difference_type _Off) const
    {
        // return this - integer
        _Mytype _Tmp = *this;
        return (_Tmp -= _Off);
    }

    difference_type operator-(
        const _Mytype& _Right) const
    {
        // return difference of iterators
        _Compat(_Right);
        return (_VBITS * (this->_Myptr - _Right._Myptr)
                + (difference_type)this->_Myoff
                - (difference_type)_Right._Myoff);
    }

    const_reference operator[](difference_type _Off) const
    {
        // subscript
        return (*(*this + _Off));
    }

    bool operator==(const _Mytype& _Right) const
    {
        // test for iterator equality
        _Compat(_Right);
        return (this->_Myptr == _Right._Myptr
                && this->_Myoff == _Right._Myoff);
    }

    bool operator!=(const _Mytype& _Right) const
    {
        // test for iterator inequality
        return (!(*this == _Right));
    }

    bool operator<(const _Mytype& _Right) const
    {
        // test if this < _Right
        _Compat(_Right);
        return (this->_Myptr < _Right._Myptr
                || (this->_Myptr == _Right._Myptr
                    && this->_Myoff < _Right._Myoff));
    }

    bool operator>(const _Mytype& _Right) const
    {
        // test if this > _Right
        return (_Right < *this);
    }

    bool operator<=(const _Mytype& _Right) const
    {
        // test if this <= _Right
        return (!(_Right < *this));
    }

    bool operator>=(const _Mytype& _Right) const
    {
        // test if this >= _Right
        return (!(*this < _Right));
    }

#if _ITERATOR_DEBUG_LEVEL == 2
    void _Compat(const _Mytype& _Right) const
    {
        // test for compatible iterator pair
        if (this->_Getcont() == 0
            || this->_Getcont() != _Right._Getcont())
            _DEBUG_ERROR("vector<bool> iterators incompatible");
    }

#elif _ITERATOR_DEBUG_LEVEL == 1
    void _Compat(const _Mytype& _Right) const
    {
        // test for compatible iterator pair
        _SCL_SECURE_VALIDATE(this->_Getcont() != 0);
        _SCL_SECURE_VALIDATE_RANGE(this->_Getcont() == _Right._Getcont());
    }

#else /* _ITERATOR_DEBUG_LEVEL == 0 */
    void _Compat(const _Mytype&) const
    {
        // test for compatible iterator pair
    }
#endif /* _ITERATOR_DEBUG_LEVEL */

    void _Dec()
    {
        // decrement bit position
        if (this->_Myoff != 0)
            --this->_Myoff;
        else {
            // move to previous word
#if _ITERATOR_DEBUG_LEVEL == 2
            if (this->_Getcont() == 0 || 0 < this->_Valid((size_type)-1)) {
                // report error
                _DEBUG_ERROR("vector<bool> iterator not decrementable");
                _SCL_SECURE_OUT_OF_RANGE;
            }

#elif _ITERATOR_DEBUG_LEVEL == 1
            _SCL_SECURE_VALIDATE(this->_Getcont() != 0);
            _SCL_SECURE_VALIDATE_RANGE(this->_Valid((size_type)-1) <= 0);
#endif /* _ITERATOR_DEBUG_LEVEL */

            this->_Myoff = _VBITS - 1;
            --this->_Myptr;
        }
    }

    void _Inc()
    {
        // increment bit position
        if (this->_Myoff < _VBITS - 1)
            ++this->_Myoff;
        else {
            // move to next word
#if _ITERATOR_DEBUG_LEVEL == 2
            if (this->_Getcont() == 0 || 0 < this->_Valid(1)) {
                // report error
                _DEBUG_ERROR("vector<bool> iterator not incrementable");
                _SCL_SECURE_OUT_OF_RANGE;
            }

#elif _ITERATOR_DEBUG_LEVEL == 1
            _SCL_SECURE_VALIDATE(this->_Getcont() != 0);
            _SCL_SECURE_VALIDATE_RANGE(this->_Valid(1) <= 0);
#endif /* _ITERATOR_DEBUG_LEVEL */

            this->_Myoff = 0;
            ++this->_Myptr;
        }
    }
};

template<class _Alloc> inline
_Vb_const_iterator<_Alloc> operator+(
    typename _Alloc::difference_type _Off,
    _Vb_const_iterator<_Alloc> _Right)
{
    // return _Right + integer
    return (_Right += _Off);
}

template<class _Alloc>
struct _Is_checked_helper<_Vb_const_iterator<_Alloc> >
    : public true_type {
    // mark _Vb_const_iterator as checked
};

// CLASS _Vb_iterator
template<class _Alloc>
class _Vb_iterator
    : public _Vb_const_iterator<_Alloc>
{
    // iterator for mutable vector<bool>
public:
    typedef _Vb_const_iterator<_Alloc> _Mybase;
    typedef _Vb_iterator<_Alloc> _Mytype;

    typedef _Vb_reference<_Alloc> _Reft;
    typedef bool const_reference;

    typedef random_access_iterator_tag iterator_category;
    typedef _Bool value_type;
    typedef typename _Alloc::size_type size_type;
    typedef typename _Alloc::difference_type difference_type;
    typedef _Reft *pointer;
    typedef _Reft reference;

    _Vb_iterator()
    {
        // construct with null reference
    }

    _Vb_iterator(_Vbase *_Ptr, _Container_base *_Mypvbool)
        : _Mybase(_Ptr, _Mypvbool)
    {
        // construct with offset and pointer
    }

    reference operator*() const
    {
        // return (reference to) designated object
        return (_Reft(*this));
    }

    _Mytype& operator++()
    {
        // preincrement
        ++*(_Mybase *)this;
        return (*this);
    }

    _Mytype operator++(int)
    {
        // postincrement
        _Mytype _Tmp = *this;
        ++*this;
        return (_Tmp);
    }

    _Mytype& operator--()
    {
        // predecrement
        --*(_Mybase *)this;
        return (*this);
    }

    _Mytype operator--(int)
    {
        // postdecrement
        _Mytype _Tmp = *this;
        --*this;
        return (_Tmp);
    }

    _Mytype& operator+=(difference_type _Off)
    {
        // increment by integer
        *(_Mybase *)this += _Off;
        return (*this);
    }

    _Mytype operator+(difference_type _Off) const
    {
        // return this + integer
        _Mytype _Tmp = *this;
        return (_Tmp += _Off);
    }

    _Mytype& operator-=(difference_type _Off)
    {
        // decrement by integer
        return (*this += -_Off);
    }

    _Mytype operator-(difference_type _Off) const
    {
        // return this - integer
        _Mytype _Tmp = *this;
        return (_Tmp -= _Off);
    }

    difference_type operator-(const _Mybase& _Right) const
    {
        // return difference of iterators
        return (*(_Mybase *)this - _Right);
    }

    reference operator[](difference_type _Off) const
    {
        // subscript
        return (*(*this + _Off));
    }
};

template<class _Alloc> inline
_Vb_iterator<_Alloc> operator+(typename _Alloc::difference_type _Off,
                               _Vb_iterator<_Alloc> _Right)
{
    // return _Right + integer
    return (_Right += _Off);
}

template<class _Alloc>
struct _Is_checked_helper<_Vb_iterator<_Alloc> >
    : public true_type {
    // mark _Vb_iterator as checked
};

// TEMPLATE CLASS _Vb_val
template<class _Alloc>
class _Vb_val
    : public _Container_base
{
    // base class for vector<bool> to hold data
public:
    typedef _STD vector<_Vbase, _Alloc> _Vectype;
    typedef typename _Vectype::_Alty _Alty;
    typedef typename _Alty::size_type size_type;

    _Vb_val(size_type _Count, const bool& _Val, const _Alloc& _Al = _Alloc())
        : _Myvec(_Nw(_Count), (_Vbase)(_Val ? -1 : 0), _Al)
    {
        // construct _Count * _Val elements with allocator _Al
        _Alloc_proxy();
        _Mysize = 0;
    }

    _Vb_val(const _Vb_val& _Right)
        : _Myvec(_Right._Myvec),
          _Mysize(_Right._Mysize)
    {
        // copy construct
        _Alloc_proxy();
    }

    _Vb_val(const _Vb_val& _Right, const _Alloc& _Al)
        : _Myvec(_Right._Myvec, _Al),
          _Mysize(_Right._Mysize)
    {
        // copy construct, allocator
        _Alloc_proxy();
    }

    _Vb_val(_Vb_val&& _Right)
        : _Myvec(_STD forward<_Vectype>(_Right._Myvec)),
          _Mysize(_Right._Mysize)
    {
        // move construct
        _Right._Mysize = 0;
        _Alloc_proxy();
    }

    _Vb_val(_Vb_val&& _Right, const _Alloc& _Al)
        : _Myvec(_STD forward<_Vectype>(_Right._Myvec), _Al),
          _Mysize(_Right._Mysize)
    {
        // move construct, allocator
        _Right._Mysize = 0;
        _Alloc_proxy();
    }

    ~_Vb_val() _NOEXCEPT {
        // destroy proxy
        _Free_proxy();
    }

#if _ITERATOR_DEBUG_LEVEL == 0
    void _Swap_alloc(_Vb_val&)
    {
        // do nothing
    }

    void _Alloc_proxy()
    {
        // do nothing
    }

    void _Free_proxy()
    {
        // do nothing
    }

#else /* _ITERATOR_DEBUG_LEVEL == 0 */
    void _Swap_alloc(_Vb_val& _Right)
    {
        // swap proxies to follow allocators in vector
        _Swap_adl(this->_Myproxy, _Right._Myproxy);
    }

    void _Alloc_proxy()
    {
        // allocate a proxy
        typename _Alty::template rebind<_Container_proxy>::other
        _Alproxy(_Myvec.get_allocator());
        this->_Myproxy = _Alproxy.allocate(1);
        _Alproxy.construct(this->_Myproxy, _Container_proxy());
        this->_Myproxy->_Mycont = this;
    }

    void _Free_proxy()
    {
        // destroy proxy
        typename _Alty::template rebind<_Container_proxy>::other
        _Alproxy(_Myvec.get_allocator());
        this->_Orphan_all();
        _Alproxy.destroy(this->_Myproxy);
        _Alproxy.deallocate(this->_Myproxy, 1);
        this->_Myproxy = 0;
    }
#endif /* _ITERATOR_DEBUG_LEVEL == 0 */

    static size_type _Nw(size_type _Count)
    {
        // return number of base words from number of bits
        return ((_Count + _VBITS - 1) / _VBITS);
    }

    _Vectype _Myvec;    // base vector of words
    typename _Alty::size_type _Mysize;  // current length of sequence
};

// CLASS vector<bool>

template<class _Alloc>
class vector<_Bool, _Alloc>
    : public _Vb_val<_Alloc>
{
    // varying size array of bits
public:
    typedef _STD vector<_Bool, _Alloc> _Myt;
    typedef _Vb_val<_Alloc> _Mybase;
    typedef typename _Mybase::_Alty _Alty;
    typedef typename _Mybase::_Vectype _Vectype;

    typedef typename _Alty::size_type size_type;
    typedef typename _Alty::difference_type difference_type;
    typedef _Bool _Ty;
    typedef _Alloc allocator_type;

    typedef _Vb_reference<_Alty> reference;
    typedef bool const_reference;
    typedef bool value_type;

    typedef reference _Reft;
    typedef _Vb_const_iterator<_Alty> const_iterator;
    typedef _Vb_iterator<_Alty> iterator;

    typedef iterator pointer;
    typedef const_iterator const_pointer;
    typedef _STD reverse_iterator<iterator> reverse_iterator;
    typedef _STD reverse_iterator<const_iterator> const_reverse_iterator;

    static const int _VBITS = _STD _VBITS;
    enum {_EEN_VBITS = _VBITS}; // helper for expression evaluator
    vector()
        : _Mybase(0, false)
    {
        // construct empty vector
    }

    explicit vector(const _Alloc& _Al)
        : _Mybase(0, false, _Al)
    {
        // construct empty vector, allocator
    }

    explicit vector(size_type _Count, const bool& _Val = false)
        : _Mybase(_Count, _Val)
    {
        // construct from _Count * _Val
        _Trim(_Count);
    }

    vector(size_type _Count, const bool& _Val, const _Alloc& _Al)
        : _Mybase(_Count, _Val, _Al)
    {
        // construct from _Count * _Val, allocator
        _Trim(_Count);
    }

    vector(const _Myt& _Right)
        : _Mybase(_Right)
    {
        // construct by copying _Right
    }

    vector(const _Myt& _Right, const _Alloc& _Al)
        : _Mybase(_Right, _Al)
    {
        // construct by copying _Right, allocator
    }

    template<class _Iter,
             class = typename enable_if<_Is_iterator<_Iter>::value,
                                        void>::type>
    vector(_Iter _First, _Iter _Last)
        : _Mybase(0, false)
    {
        // construct from [_First, _Last)
        _BConstruct(_First, _Last);
    }

    template<class _Iter,
             class = typename enable_if<_Is_iterator<_Iter>::value,
                                        void>::type>
    vector(_Iter _First, _Iter _Last, const _Alloc& _Al)
        : _Mybase(0, false, _Al)
    {
        // construct from [_First, _Last), allocator
        _BConstruct(_First, _Last);
    }

    template<class _Iter>
    void _BConstruct(_Iter _First, _Iter _Last)
    {
        // initialize from [_First, _Last), input iterators
        insert(begin(), _First, _Last);
    }

    vector(_Myt&& _Right)
        : _Mybase(_STD forward<_Myt>(_Right))
    {
        // move construct by moving _Right
    }

    vector(_Myt&& _Right, const _Alloc& _Al)
        : _Mybase(_STD forward<_Myt>(_Right), _Al)
    {
        // move construct by moving _Right, allocator
    }

    _Myt& operator=(_Myt&& _Right)
    {
        // assign by moving _Right
        if (this != &_Right) {
            // different, assign it
            clear();

            if (_Alty::propagate_on_container_move_assignment::value
                && this->get_allocator() != _Right.get_allocator()) {
                // assign vector, dumping proxy
                this->_Free_proxy();
                this->_Myvec = _STD move(_Right._Myvec);
                this->_Alloc_proxy();
            } else
                this->_Myvec = _STD move(_Right._Myvec);


            this->_Mysize = _Right._Mysize;
            _Right._Mysize = 0;
        }
        return (*this);
    }

    vector(_XSTD initializer_list<bool> _Ilist,
           const _Alloc& _Al = allocator_type())
        : _Mybase(0, false, _Al)
    {
        // construct from initializer_list
        insert(begin(), _Ilist.begin(), _Ilist.end());
    }

    _Myt& operator=(_XSTD initializer_list<bool> _Ilist)
    {
        // assign initializer_list
        assign(_Ilist.begin(), _Ilist.end());
        return (*this);
    }

    void assign(_XSTD initializer_list<bool> _Ilist)
    {
        // assign initializer_list
        assign(_Ilist.begin(), _Ilist.end());
    }

    iterator insert(const_iterator _Where,
                    _XSTD initializer_list<bool> _Ilist)
    {
        // insert initializer_list
        return (insert(_Where, _Ilist.begin(), _Ilist.end()));
    }

    ~vector() _NOEXCEPT {
        // destroy the object
        this->_Mysize = 0;
    }

    _Myt& operator=(const _Myt& _Right)
    {
        // assign from _Right
        this->_Mysize = _Right._Mysize;
        this->_Myvec = _Right._Myvec;
        return (*this);
    }

    void reserve(size_type _Count)
    {
        // determine new minimum length of allocated storage
        this->_Myvec.reserve(this->_Nw(_Count));
    }

    size_type capacity() const _NOEXCEPT
    {
        // return current length of allocated storage
        return (this->_Myvec.capacity() * _VBITS);
    }

    iterator begin() _NOEXCEPT {
        // return iterator for beginning of mutable sequence
        return (iterator((_Vbase *)this->_Myvec._Myfirst, this));
    }

    const_iterator begin() const _NOEXCEPT
    {
        // return iterator for beginning of nonmutable sequence
        return (const_iterator((_Vbase *)this->_Myvec._Myfirst, this));
    }

    iterator end() _NOEXCEPT {
        // return iterator for end of mutable sequence
        iterator _Tmp = begin();
        if (0 < this->_Mysize)
            _Tmp += this->_Mysize;
        return (_Tmp);
    }

    const_iterator end() const _NOEXCEPT
    {
        // return iterator for end of nonmutable sequence
        const_iterator _Tmp = begin();
        if (0 < this->_Mysize)
            _Tmp += this->_Mysize;
        return (_Tmp);
    }

    const_iterator cbegin() const _NOEXCEPT
    {
        // return iterator for beginning of nonmutable sequence
        return (((const _Myt *)this)->begin());
    }

    const_iterator cend() const _NOEXCEPT
    {
        // return iterator for end of nonmutable sequence
        return (((const _Myt *)this)->end());
    }

    const_reverse_iterator crbegin() const _NOEXCEPT
    {
        // return iterator for beginning of reversed nonmutable sequence
        return (((const _Myt *)this)->rbegin());
    }

    const_reverse_iterator crend() const _NOEXCEPT
    {
        // return iterator for end of reversed nonmutable sequence
        return (((const _Myt *)this)->rend());
    }

    void shrink_to_fit()
    {
        // reduce capacity
        if (this->_Myvec._Has_unused_capacity()) {
            // worth shrinking, do it
            _Myt _Tmp(*this);
            swap(_Tmp);
        }
    }

    iterator _Make_iter(const_iterator _Where)
    {
        // make iterator from const_iterator
        iterator _Tmp = begin();
        if (0 < this->_Mysize)
            _Tmp += _Where - begin();
        return (_Tmp);
    }

    reverse_iterator rbegin() _NOEXCEPT {
        // return iterator for beginning of reversed mutable sequence
        return (reverse_iterator(end()));
    }

    const_reverse_iterator rbegin() const _NOEXCEPT
    {
        // return iterator for beginning of reversed nonmutable sequence
        return (const_reverse_iterator(end()));
    }

    reverse_iterator rend() _NOEXCEPT {
        // return iterator for end of reversed mutable sequence
        return (reverse_iterator(begin()));
    }

    const_reverse_iterator rend() const _NOEXCEPT
    {
        // return iterator for end of reversed nonmutable sequence
        return (const_reverse_iterator(begin()));
    }

    void resize(size_type _Newsize, bool _Val = false)
    {
        // determine new length, padding with _Val elements as needed
        if (size() < _Newsize)
            _Insert_n(end(), _Newsize - size(), _Val);
        else if (_Newsize < size())
            erase(begin() + _Newsize, end());
    }

    size_type size() const _NOEXCEPT
    {
        // return length of sequence
        return (this->_Mysize);
    }

    size_type max_size() const _NOEXCEPT
    {
        // return maximum possible length of sequence
        const size_type _Maxsize = this->_Myvec.max_size();
        return (_Maxsize < (size_type)(-1) / _VBITS
                ? _Maxsize * _VBITS : (size_type)(-1));
    }

    bool empty() const _NOEXCEPT
    {
        // test if sequence is empty
        return (size() == 0);
    }

    _Alloc get_allocator() const _NOEXCEPT
    {
        // return allocator object for values
        return (this->_Myvec.get_allocator());
    }

    const_reference at(size_type _Off) const
    {
        // subscript nonmutable sequence with checking
        if (size() <= _Off)
            _Xran();
        return ((*this)[_Off]);
    }

    reference at(size_type _Off)
    {
        // subscript mutable sequence with checking
        if (size() <= _Off)
            _Xran();
        return ((*this)[_Off]);
    }

    const_reference operator[](size_type _Off) const
    {
        // subscript nonmutable sequence
        const_iterator _It = begin();
        _It._Advance(_Off);
        return (*_It);
    }

    reference operator[](size_type _Off)
    {
        // subscript mutable sequence
        iterator _It = begin();
        _It._Advance(_Off);
        return (*_It);
    }

    reference front()
    {
        // return first element of mutable sequence
        return (*begin());
    }

    const_reference front() const
    {
        // return first element of nonmutable sequence
        return (*begin());
    }

    reference back()
    {
        // return last element of mutable sequence
        return (*(end() - 1));
    }

    const_reference back() const
    {
        // return last element of nonmutable sequence
        return (*(end() - 1));
    }

    void push_back(const bool& _Val)
    {
        // insert element at end
        insert(end(), _Val);
    }

    void pop_back()
    {
        // erase element at end
        erase(end() - 1);
    }

    template<class _Iter>
    typename enable_if<_Is_iterator<_Iter>::value,
             void>::type
             assign(_Iter _First, _Iter _Last)
    {
        // assign [_First, _Last), input iterators
        erase(begin(), end());
        insert(begin(), _First, _Last);
    }

    void assign(size_type _Count, const bool& _Val)
    {
        // assign _Count * _Val
        erase(begin(), end());
        _Insert_n(begin(), _Count, _Val);
    }

    iterator insert(const_iterator _Where, const bool& _Val)
    {
        // insert _Val at _Where
        return (_Insert_n(_Where, (size_type)1, _Val));
    }

    iterator insert(const_iterator _Where, size_type _Count,
                    const bool& _Val)
    {
        // insert _Count * _Val at _Where
        return (_Insert_n(_Where, _Count, _Val));
    }

    template<class _Iter>
    typename enable_if<_Is_iterator<_Iter>::value,
             iterator>::type
             insert(const_iterator _Where, _Iter _First, _Iter _Last)
    {
        // insert [_First, _Last) at _Where
        size_type _Off = _Where - begin();
        _Insert(_Where, _First, _Last, _Iter_cat(_First));
        return (begin() + _Off);
    }

    template<class _Iter>
    void _Insert(const_iterator _Where, _Iter _First, _Iter _Last,
                 input_iterator_tag)
    {
        // insert [_First, _Last) at _Where, input iterators
        size_type _Off = _Where - begin();

        for (; _First != _Last; ++_First, ++_Off)
            insert(begin() + _Off, *_First);
    }

    template<class _Iter>
    void _Insert(const_iterator _Where,
                 _Iter _First, _Iter _Last,
                 forward_iterator_tag)
    {
        // insert [_First, _Last) at _Where, forward iterators
        _DEBUG_RANGE(_First, _Last);
        size_type _Count = 0;
        _Distance(_First, _Last, _Count);

        size_type _Off = _Insert_x(_Where, _Count);
        _STD copy(_First, _Last, begin() + _Off);
    }

    iterator erase(const_iterator _Where_arg)
    {
        // erase element at _Where
        iterator _Where = _Make_iter(_Where_arg);
        size_type _Off = _Where - begin();

#if _ITERATOR_DEBUG_LEVEL == 2
        if (end() <= _Where)
            _DEBUG_ERROR("vector<bool> erase iterator outside range");
        _STD copy(_Where + 1, end(), _Where);
        _Orphan_range(_Off, this->_Mysize);

#else /* _ITERATOR_DEBUG_LEVEL == 2 */
        _STD copy(_Where + 1, end(), _Where);
#endif /* _ITERATOR_DEBUG_LEVEL == 2 */

        _Trim(this->_Mysize - 1);
        return (begin() + _Off);
    }

    iterator erase(const_iterator _First_arg, const_iterator _Last_arg)
    {
        // erase [_First, _Last)
        iterator _First = _Make_iter(_First_arg);
        iterator _Last = _Make_iter(_Last_arg);
        size_type _Off = _First - begin();

        if (_First != _Last) {
            // worth doing, copy down over hole
#if _ITERATOR_DEBUG_LEVEL == 2
            if (_Last < _First || end() < _Last)
                _DEBUG_ERROR("vector<bool> erase iterator outside range");
            iterator _Next = _STD copy(_Last, end(), _First);
            size_type _Newsize = _Next - begin();
            _Orphan_range(_Newsize, this->_Mysize);
            _Trim(_Newsize);

#else /* _ITERATOR_DEBUG_LEVEL == 2 */
            iterator _Next = _STD copy(_Last, end(), _First);
            _Trim(_Next - begin());
#endif /* _ITERATOR_DEBUG_LEVEL == 2 */
        }
        return (begin() + _Off);
    }

    void clear() _NOEXCEPT {
        // erase all elements
        erase(begin(), end());
    }

    void flip() _NOEXCEPT {
        // toggle all elements
        for (typename _Vectype::iterator _Next = this->_Myvec.begin();
        _Next != this->_Myvec.end(); ++_Next)
            *_Next = (_Vbase)~*_Next;
        _Trim(this->_Mysize);
    }

    void swap(_Myt& _Right)
    {
        // exchange contents with right
        if (this == &_Right)
            ;   // same object, do nothing
        else if (this->get_allocator() == _Right.get_allocator()) {
            // same allocator, swap control information
            this->_Swap_all(_Right);
            this->_Myvec.swap(_Right._Myvec);
            _STD swap(this->_Mysize, _Right._Mysize);
        }

        else if (_Alty::propagate_on_container_swap::value) {
            // swap allocators and control information
            this->_Swap_alloc(_Right);
            this->_Myvec.swap(_Right._Myvec);
            _STD swap(this->_Mysize, _Right._Mysize);
        }

        else {
            // containers are incompatible
#if _ITERATOR_DEBUG_LEVEL == 2
            _DEBUG_ERROR("vector<bool> containers incompatible for swap");

#else /* ITERATOR_DEBUG_LEVEL == 2 */
            _XSTD terminate();
#endif /* ITERATOR_DEBUG_LEVEL == 2 */
        }
    }

    static void swap(reference _Left, reference _Right) _NOEXCEPT {
        // swap _Left and _Right vector<bool> elements
        bool _Val = _Left;  // NOT _STD swap

        _Left = _Right;
        _Right = _Val;
    }

    size_t hash() const
    {
        // hash bits to size_t value by pseudorandomizing transform
        return (_Hash_seq((const unsigned char *)this->_Myvec.data(),
                          this->_Myvec.size() * sizeof (_Vbase)));
    }

    iterator _Insert_n(const_iterator _Where,
                       size_type _Count, const bool& _Val)
    {
        // insert _Count * _Val at _Where
        size_type _Off = _Insert_x(_Where, _Count);
        _STD fill(begin() + _Off, begin() + (_Off + _Count), _Val);
        return (begin() + _Off);
    }

    size_type _Insert_x(const_iterator _Where, size_type _Count)
    {
        // make room to insert _Count elements at _Where
        size_type _Off = _Where - begin();

#if _ITERATOR_DEBUG_LEVEL == 2
        if (end() < _Where)
            _DEBUG_ERROR("vector<bool> insert iterator outside range");
        bool _Realloc = capacity() - size() < _Count;
#endif /* _ITERATOR_DEBUG_LEVEL == 2 */

        if (_Count == 0)
            ;
        else if (max_size() - size() < _Count)
            _Xlen();    // result too long
        else {
            // worth doing
            this->_Myvec.resize(this->_Nw(size() + _Count), 0);
            if (empty())
                this->_Mysize += _Count;
            else {
                // make room and copy down suffix
                iterator _Oldend = end();
                this->_Mysize += _Count;
                _STD copy_backward(begin() + _Off, _Oldend, end());
            }

#if _ITERATOR_DEBUG_LEVEL == 2
            _Orphan_range(_Realloc ? 0 : _Off, this->_Mysize);
#endif /* _ITERATOR_DEBUG_LEVEL == 2 */
        }
        return (_Off);
    }

#if _VECTOR_ORPHAN_RANGE
    void _Orphan_range(size_type _Offlo, size_type _Offhi) const
    {
        // orphan iterators within specified (inclusive) range
        typedef _Vb_iter_base<_Alty> _Myiterbase;

        _Lockit _Lock(_LOCK_DEBUG);
        _Vbase *_Base = (_Vbase *)this->_Myvec._Myfirst;

        const_iterator **_Pnext = (const_iterator **)this->_Getpfirst();
        if (_Pnext != 0)
            while (*_Pnext != 0) {
                // test offset from beginning of vector
                size_type _Off = _VBITS * ((*_Pnext)->_Myptr - _Base)
                                 + (*_Pnext)->_Myoff;
                if (_Off < _Offlo || _Offhi < _Off)
                    _Pnext = (const_iterator **)(*_Pnext)->_Getpnext();
                else {
                    // orphan the iterator
                    (*_Pnext)->_Clrcont();
                    *_Pnext = *(const_iterator **)(*_Pnext)->_Getpnext();
                }
            }
    }

#else /* _VECTOR_ORPHAN_RANGE */
    void _Orphan_range(size_type, size_type) const
    {
        // orphan iterators within specified (inclusive) range
    }
#endif /* _VECTOR_ORPHAN_RANGE */

    void _Trim(size_type _Size)
    {
        // trim base vector to exact length in bits
        if (max_size() < _Size)
            _Xlen();    // result too long
        size_type _Words = this->_Nw(_Size);

        if (_Words < this->_Myvec.size())
            this->_Myvec.erase(this->_Myvec.begin() + _Words,
                               this->_Myvec.end());
        this->_Mysize = _Size;
        _Size %= _VBITS;
        if (0 < _Size)
            this->_Myvec[_Words - 1] &= (_Vbase)((1 << _Size) - 1);
    }

    __declspec(noreturn) void _Xlen() const
    {
        // report a length_error
        _Xlength_error("vector<bool> too long");
    }

    __declspec(noreturn) void _Xran() const
    {
        // report an out_of_range error
        _Xout_of_range("invalid vector<bool> subscript");
    }
};

template<class _Alloc> inline
bool operator==(const vector<bool, _Alloc>& _Left,
                const vector<bool, _Alloc>& _Right)
{
    // test for vector equality
    return (_Left.size() == _Right.size()
            && equal(_Left._Myvec.begin(), _Left._Myvec.end(),
                     _Right._Myvec.begin()));
}

template<class _Alloc> inline
bool operator!=(const vector<bool, _Alloc>& _Left,
                const vector<bool, _Alloc>& _Right)
{
    // test for vector inequality
    return (!(_Left == _Right));
}

// TEMPLATE STRUCT SPECIALIZATION hash
template<class _Alloc>
struct hash<vector<_Bool, _Alloc> >
    : public unary_function<vector<_Bool, _Alloc>, size_t> {
    // hash functor
    typedef vector<_Bool, _Alloc> _Kty;

    size_t operator()(const _Kty& _Keyval) const
    {
        // hash _Keyval to size_t value by pseudorandomizing transform
        return (_Keyval.hash());
    }
};
_STD_END

#pragma pop_macro("new")
#pragma warning(pop)
#pragma pack(pop)
#endif /* RC_INVOKED */
#endif /* _VECTOR_ */

/*
 * This file is derived from software bearing the following
 * restrictions:
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Permission to use, copy, modify, distribute and sell this
 * software and its documentation for any purpose is hereby
 * granted without fee, provided that the above copyright notice
 * appear in all copies and that both that copyright notice and
 * this permission notice appear in supporting documentation.
 * Hewlett-Packard Company makes no representations about the
 * suitability of this software for any purpose. It is provided
 * "as is" without express or implied warranty.
 */

/*
 * Copyright (c) 1992-2012 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V6.00:0009 */

