using namespace std;

template <class _Compare, class _ForwardIterator>
unsigned
__sort31(_ForwardIterator __x, _ForwardIterator __y, _ForwardIterator __z, _Compare __c)
{
    unsigned __r = 0;
    if (!__c(*__y, *__x)) // if x <= y
    {
        if (!__c(*__z, *__y)) // if y <= z
            return __r;       // x <= y && y <= z
        // x <= y && y > z
        swap(*__y, *__z); // x <= z && y < z
        __r = 1;
        if (__c(*__y, *__x)) // if x > y
        {
            swap(*__x, *__y); // x < y && y <= z
            __r = 2;
        }
        return __r; // x <= y && y < z
    }
    if (__c(*__z, *__y)) // x > y, if y > z
    {
        swap(*__x, *__z); // x < y && y < z
        __r = 1;
        return __r;
    }
    swap(*__x, *__y);    // x > y && y <= z
    __r = 1;             // x < y && x <= z
    if (__c(*__z, *__y)) // if y > z
    {
        swap(*__y, *__z); // x <= y && y < z
        __r = 2;
    }
    return __r;
} // x <= y && y <= z

// stable, 3-6 compares, 0-5 swaps

template <class _Compare, class _ForwardIterator>
unsigned
__sort41(_ForwardIterator __x1, _ForwardIterator __x2, _ForwardIterator __x3,
         _ForwardIterator __x4, _Compare __c)
{
    unsigned __r = __sort31<_Compare>(__x1, __x2, __x3, __c);
    if (__c(*__x4, *__x3))
    {
        swap(*__x3, *__x4);
        ++__r;
        if (__c(*__x3, *__x2))
        {
            swap(*__x2, *__x3);
            ++__r;
            if (__c(*__x2, *__x1))
            {
                swap(*__x1, *__x2);
                ++__r;
            }
        }
    }
    return __r;
}

// stable, 4-10 compares, 0-9 swaps

template <class _Compare, class _ForwardIterator>
unsigned
__sort51(_ForwardIterator __x1, _ForwardIterator __x2, _ForwardIterator __x3,
         _ForwardIterator __x4, _ForwardIterator __x5, _Compare __c)
{
    unsigned __r = __sort41<_Compare>(__x1, __x2, __x3, __x4, __c);
    if (__c(*__x5, *__x4))
    {
        swap(*__x4, *__x5);
        ++__r;
        if (__c(*__x4, *__x3))
        {
            swap(*__x3, *__x4);
            ++__r;
            if (__c(*__x3, *__x2))
            {
                swap(*__x2, *__x3);
                ++__r;
                if (__c(*__x2, *__x1))
                {
                    swap(*__x1, *__x2);
                    ++__r;
                }
            }
        }
    }
    return __r;
}

template <class _Compare, class _RandomAccessIterator>
void __insertion_sort_31(_RandomAccessIterator __first, _RandomAccessIterator __last, _Compare __comp)
{
    typedef typename std::iterator_traits<_RandomAccessIterator>::value_type value_type;
    _RandomAccessIterator __j = __first + 2;
    __sort31<_Compare>(__first, __first + 1, __j, __comp);
    for (_RandomAccessIterator __i = __j + 1; __i != __last; ++__i)
    {
        if (__comp(*__i, *__j))
        {
            value_type __t(move(*__i));
            _RandomAccessIterator __k = __j;
            __j = __i;
            do
            {
                *__j = move(*__k);
                __j = __k;
            } while (__j != __first && __comp(__t, *--__k));
            *__j = move(__t);
        }
        __j = __i;
    }
}

template <class _Compare, class _RandomAccessIterator>
bool __insertion_sort_incomplete1(_RandomAccessIterator __first, _RandomAccessIterator __last, _Compare __comp)
{
    switch (__last - __first)
    {
    case 0:
    case 1:
        return true;
    case 2:
        if (__comp(*--__last, *__first))
            std::swap(*__first, *__last);
        return true;
    case 3:
        __sort31<_Compare>(__first, __first + 1, --__last, __comp);
        return true;
    case 4:
        __sort41<_Compare>(__first, __first + 1, __first + 2, --__last, __comp);
        return true;
    case 5:
        __sort51<_Compare>(__first, __first + 1, __first + 2, __first + 3, --__last, __comp);
        return true;
    }
    typedef typename std::iterator_traits<_RandomAccessIterator>::value_type value_type;
    _RandomAccessIterator __j = __first + 2;
    __sort31<_Compare>(__first, __first + 1, __j, __comp);
    const unsigned __limit = 8;
    unsigned __count = 0;
    for (_RandomAccessIterator __i = __j + 1; __i != __last; ++__i)
    {
        if (__comp(*__i, *__j))
        {
            value_type __t(std::move(*__i));
            _RandomAccessIterator __k = __j;
            __j = __i;
            do
            {
                *__j = std::move(*__k);
                __j = __k;
            } while (__j != __first && __comp(__t, *--__k));
            *__j = move(__t);
            if (++__count == __limit)
                return ++__i == __last;
        }
        __j = __i;
    }
    return true;
}

template <class _Compare, class _RandomAccessIterator>
void __sort1(_RandomAccessIterator __first, _RandomAccessIterator __last, _Compare __comp)
{
    // _Compare is known to be a reference type
    typedef typename std::iterator_traits<_RandomAccessIterator>::difference_type difference_type;
    const difference_type __limit = 30;
    while (true)
    {
    __restart:
        difference_type __len = __last - __first;
        switch (__len)
        {
        case 0:
        case 1:
            return;
        case 2:
            if (__comp(*--__last, *__first))
                std::swap(*__first, *__last);
            return;
        case 3:
            __sort31<_Compare>(__first, __first + 1, --__last, __comp);
            return;
        case 4:
            __sort41<_Compare>(__first, __first + 1, __first + 2, --__last, __comp);
            return;
        case 5:
            __sort51<_Compare>(__first, __first + 1, __first + 2, __first + 3, --__last, __comp);
            return;
        }
        if (__len <= __limit)
        {
            __insertion_sort_31<_Compare>(__first, __last, __comp);
            return;
        }
        // __len > 5
        _RandomAccessIterator __m = __first;
        _RandomAccessIterator __lm1 = __last;
        --__lm1;
        unsigned __n_swaps;
        {
            difference_type __delta;
            if (__len >= 1000)
            {
                __delta = __len / 2;
                __m += __delta;
                __delta /= 2;
                __n_swaps = __sort51<_Compare>(__first, __first + __delta, __m, __m + __delta, __lm1, __comp);
            }
            else
            {
                __delta = __len / 2;
                __m += __delta;
                __n_swaps = __sort31<_Compare>(__first, __m, __lm1, __comp);
            }
        }
        // *__m is median
        // partition [__first, __m) < *__m and *__m <= [__m, __last)
        // (this inhibits tossing elements equivalent to __m around unnecessarily)
        _RandomAccessIterator __i = __first;
        _RandomAccessIterator __j = __lm1;
        // j points beyond range to be tested, *__m is known to be <= *__lm1
        // The search going up is known to be guarded but the search coming down isn't.
        // Prime the downward search with a guard.
        if (!__comp(*__i, *__m)) // if *__first == *__m
        {
            // *__first == *__m, *__first doesn't go in first part
            // manually guard downward moving __j against __i
            while (true)
            {
                if (__i == --__j)
                {
                    // *__first == *__m, *__m <= all other elements
                    // Parition instead into [__first, __i) == *__first and *__first < [__i, __last)
                    ++__i; // __first + 1
                    __j = __last;
                    if (!__comp(*__first, *--__j)) // we need a guard if *__first == *(__last-1)
                    {
                        while (true)
                        {
                            if (__i == __j)
                                return; // [__first, __last) all equivalent elements
                            if (__comp(*__first, *__i))
                            {
                                swap(*__i, *__j);
                                ++__n_swaps;
                                ++__i;
                                break;
                            }
                            ++__i;
                        }
                    }
                    // [__first, __i) == *__first and *__first < [__j, __last) and __j == __last - 1
                    if (__i == __j)
                        return;
                    while (true)
                    {
                        while (!__comp(*__first, *__i))
                            ++__i;
                        while (__comp(*__first, *--__j))
                            ;
                        if (__i >= __j)
                            break;
                        swap(*__i, *__j);
                        ++__n_swaps;
                        ++__i;
                    }
                    // [__first, __i) == *__first and *__first < [__i, __last)
                    // The first part is sorted, sort the secod part
                    // __sort1<_Compare>(__i, __last, __comp);
                    __first = __i;
                    goto __restart;
                }
                if (__comp(*__j, *__m))
                {
                    swap(*__i, *__j);
                    ++__n_swaps;
                    break; // found guard for downward moving __j, now use unguarded partition
                }
            }
        }
        // It is known that *__i < *__m
        ++__i;
        // j points beyond range to be tested, *__m is known to be <= *__lm1
        // if not yet partitioned...
        if (__i < __j)
        {
            // known that *(__i - 1) < *__m
            // known that __i <= __m
            while (true)
            {
                // __m still guards upward moving __i
                while (__comp(*__i, *__m))
                    ++__i;
                // It is now known that a guard exists for downward moving __j
                while (!__comp(*--__j, *__m))
                    ;
                if (__i > __j)
                    break;
                swap(*__i, *__j);
                ++__n_swaps;
                // It is known that __m != __j
                // If __m just moved, follow it
                if (__m == __i)
                    __m = __j;
                ++__i;
            }
        }
        // [__first, __i) < *__m and *__m <= [__i, __last)
        if (__i != __m && __comp(*__m, *__i))
        {
            swap(*__i, *__m);
            ++__n_swaps;
        }
        // [__first, __i) < *__i and *__i <= [__i+1, __last)
        // If we were given a perfect partition, see if insertion sort is quick...
        if (__n_swaps == 0)
        {
            bool __fs = __insertion_sort_incomplete1<_Compare>(__first, __i, __comp);
            if (__insertion_sort_incomplete1<_Compare>(__i + 1, __last, __comp))
            {
                if (__fs)
                    return;
                __last = __i;
                continue;
            }
            else
            {
                if (__fs)
                {
                    __first = ++__i;
                    continue;
                }
            }
        }
        // sort smaller range with recursive call and larger with tail recursion elimination
        if (__i - __first < __last - __i)
        {
            __sort1<_Compare>(__first, __i, __comp);
            // __sort1<_Compare>(__i+1, __last, __comp);
            __first = ++__i;
        }
        else
        {
            __sort1<_Compare>(__i + 1, __last, __comp);
            // __sort1<_Compare>(__first, __i, __comp);
            __last = __i;
        }
    }
}

// This forwarder keeps the top call and the recursive calls using the same instantiation, forcing a reference _Compare
template <class _RandomAccessIterator, class _Compare>
void sort1(_RandomAccessIterator __first, _RandomAccessIterator __last, _Compare __comp)
{
    __sort1<_Compare>(__first, __last, __comp);
}
