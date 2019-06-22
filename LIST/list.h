//
// Created by gaporf on 22.06.19.
//

#ifndef LIST_LIST_H
#define LIST_LIST_H

#include <iterator>
#include <algorithm>

template<typename T>
struct list {
private:
    struct base_node;
public:
    struct const_iterator;

    struct iterator
            : std::iterator<std::bidirectional_iterator_tag, T, std::ptrdiff_t, T *, T &> {
        iterator() : p(nullptr) {}

        iterator(iterator const &rhs) : p(rhs.p) {}

        explicit iterator(base_node &rhs) : p(&rhs) {}

        iterator &operator++() {
            p = p->next();
            return *this;
        }

        iterator operator++(int) {
            auto old = *this;
            p = p->next();
            return old;
        }

        iterator &operator--() {
            p = p->prev();
            return *this;
        }

        iterator operator--(int) {
            auto old = *this;
            p = p->prev();
            return old;
        }

        bool operator==(iterator const &it) const {
            return p == it.p;
        }

        bool operator==(const_iterator const &it) const {
            return p == it.p;
        }

        bool operator!=(iterator const &it) const {
            return p != it.p;
        }

        bool operator!=(const_iterator const &it) const {
            return p != it.p;
        }

        T &operator*() const {
            return ((node * )(p))->value();
        }

        T *operator->() const {
            return &(((node * )(p))->value());
        }

        base_node *get_node() {
            return p;
        }

        friend const_iterator;

    private:
        base_node *p;
    };

    struct const_iterator
            : std::iterator<std::bidirectional_iterator_tag, T const, std::ptrdiff_t, T const *, T const &> {
        const_iterator() : p(nullptr) {}

        const_iterator(const_iterator const &rhs) : p(rhs.p) {}

        const_iterator(iterator const &rhs) : p(rhs.p) {}

        explicit const_iterator(base_node const &rhs) : p(&(const_cast<base_node &>(rhs))) {}

        const_iterator &operator++() {
            p = p->next();
            return *this;
        }

        const_iterator operator++(int) {
            auto old = *this;
            p = p->next();
            return old;
        }

        const_iterator &operator--() {
            p = p->prev();
            return *this;
        }

        const_iterator operator--(int) {
            auto old = *this;
            p = p->prev();
            return old;
        }

        bool operator==(const_iterator const &rhs) const {
            return p == rhs.p;
        }

        bool operator==(iterator const &rhs) const {
            return p == rhs.p;
        }

        bool operator!=(const_iterator const &rhs) const {
            return p != rhs.p;
        }

        bool operator!=(iterator const &rhs) const {
            return p != rhs.p;
        }

        T const &operator*() const {
            return ((node * )(p))->value();
        }

        T const *operator->() const {
            return &(((node * )(p))->value());
        }

        base_node *get_node() {
            return p;
        }

        friend iterator;

    private:
        base_node *p;
    };

    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    list() : fake(&fake, &fake) {}

    void copy(base_node const &src_fake, base_node &dst_fake) {
        auto it = src_fake.next();
        dst_fake.set_both(&dst_fake);
        auto jt = &dst_fake;
        try {
            while (it != &src_fake) {
                auto new_node = new node(((node * )(it))->value(), jt, &dst_fake);
                dst_fake.set_prev(new_node);
                jt->set_next(new_node);
                jt = new_node;
                it = it->next();
            }
        } catch (std::exception &e) {
            auto it = dst_fake.next();
            while (it != &dst_fake) {
                auto jt = it->next();
                delete static_cast<node *>(it);
                it = jt;
            }
            throw e;
        }
    }

    list(list const &rhs) : fake(nullptr, nullptr) {
        copy(rhs.fake, fake);
    }

    list &operator=(const list &rhs) {
        if (this != &rhs) {
            base_node new_fake(nullptr, nullptr);
            copy(rhs.fake, new_fake);
            for (auto it = fake.next(); it != &fake;) {
                auto jt = it->next();
                delete static_cast<node *>(it);
                it = jt;
            }
            fake = new_fake;
            fake.prev()->set_next(&fake);
            fake.next()->set_prev(&fake);
        }
        return *this;
    }

    ~list() {
        for (auto it = fake.next(); it != &fake;) {
            auto jt = it->next();
            delete static_cast<node *>(it);
            it = jt;
        }
    }

    bool empty() const {
        return fake.next() == &fake;
    }

    void clear() {
        for (auto it = fake.next(); it != &fake;) {
            auto *jt = it->next();
            delete static_cast<node *>(it);
            it = jt;
        }
        fake.set_both(&fake);
    }

    T const &front() const {
        return ((node * )(fake.next()))->value();
    }

    T &front() {
        return ((node * )(fake.next()))->value();
    }

    void push_front(T const &val) {
        if (fake.next() == &fake) {
            fake.set_both(new node(val, &fake, &fake));
        } else {
            auto head = fake.next(),
                    new_head = new node(val, &fake, head);
            head->set_prev(new_head);
            fake.set_next(new_head);
        }
    }

    void pop_front() {
        auto head = fake.next();
        auto new_head = head->next();
        delete static_cast<node *>(head);
        new_head->set_prev(&fake);
        fake.set_next(new_head);
    }

    T const &back() const {
        return ((node * )(fake.prev()))->value();
    }

    T &back() {
        return static_cast<node *>(fake.prev())->value();
    }

    void push_back(T const &val) {
        if (fake.next() == &fake) {
            fake.set_both(new node(val, &fake, &fake));
        } else {
            auto tail = fake.prev(),
                    new_tail = new node(val, tail, &fake);
            tail->set_next(new_tail);
            fake.set_prev(new_tail);
        }
    }

    void pop_back() {
        auto tail = fake.prev();
        auto new_tail = tail->prev();
        delete static_cast<node *>(tail);
        new_tail->set_next(&fake);
        fake.set_prev(new_tail);
    }

    iterator begin() {
        return iterator(*fake.next());
    }

    const_iterator begin() const {
        return const_iterator(*fake.next());
    }

    iterator end() {
        return iterator(fake);
    }

    const_iterator end() const {
        return const_iterator(fake);
    }

    reverse_iterator rbegin() {
        return reverse_iterator(end());
    }

    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(end());
    }

    reverse_iterator rend() {
        return reverse_iterator(begin());
    }

    const_reverse_iterator rend() const {
        return const_reverse_iterator(begin());
    }

    iterator insert(const_iterator pos, T const &val) {
        auto new_node = new node(val, pos.get_node()->prev(), pos.get_node());
        pos.get_node()->prev()->set_next(new_node);
        pos.get_node()->set_prev(new_node);
        return iterator(*new_node);
    }

    iterator erase(const_iterator pos) {
        auto prev_node = pos.get_node()->prev(),
                next_node = pos.get_node()->next();
        delete static_cast<node *>(pos.get_node());
        prev_node->set_next(next_node);
        next_node->set_prev(prev_node);
        return iterator(*next_node);
    }

    void splice(const_iterator pos, list &other, const_iterator first, const_iterator second) {
        auto prev_node = pos.get_node()->prev();
        prev_node->set_next(first.get_node());
        auto prev_first = first.get_node()->prev();
        prev_first->set_next(second.get_node());
        first.get_node()->set_prev(prev_node);
        second.get_node()->prev()->set_next(pos.get_node());
        pos.get_node()->set_prev(second.get_node()->prev());
        second.get_node()->set_prev(prev_first);
    }

    void swap(list<T> &rhs) {
        fake.swap(rhs.fake);
    }

private:
    struct base_node {
        base_node() : prev_(nullptr), next_(nullptr) {}

        base_node(base_node *prev, base_node *next) : prev_(prev), next_(next) {}

        base_node &operator=(base_node const &rhs) {
            prev_ = rhs.prev_;
            next_ = rhs.next_;
            return *this;
        }

        void swap(base_node &rhs) {
            auto *a = next_,
                *b = prev_,
                *c = rhs.next_,
                *d = rhs.prev_;
            std::swap(a->prev_, c->prev_);
            std::swap(b->next_, d->next_);
            std::swap(*this, rhs);
        }

        ~base_node() = default;

        base_node const *prev() const {
            return prev_;
        }

        base_node *prev() {
            return prev_;
        }

        base_node const *next() const {
            return next_;
        }

        base_node *next() {
            return next_;
        }

        void set_prev(base_node *prev) {
            prev_ = prev;
        }

        void set_next(base_node *next) {
            next_ = next;
        }

        void set_both(base_node *both) {
            next_ = prev_ = both;
        }

    private:
        base_node *prev_, *next_;
    };

    struct node : base_node {
        node(T const &val, base_node *prev, base_node *next) : base_node(prev, next),
                                                               value_(val) {}

        ~node() = default;

        T &value() {
            return value_;
        }

        T const &value() const {
            return value_;
        }

    private:
        T value_;
    };

    base_node fake;
};

template<typename D>
void swap(list<D> &a, list<D> &b) {
    a.swap(b);
}

#endif //LIST_LIST_H
