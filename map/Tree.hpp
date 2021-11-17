#ifndef TREE_HPP
#define TREE_HPP

#include "Node.hpp"
#include "../utils/utils.hpp"
#include "../utils/pair.hpp"


template <class Key, class Value, class Compare, class Alloc>
class Tree
{
    public:
        typedef typename Alloc::template rebind<Node<ft::pair<Key, Value> > >::other Node_allocator_type;

        Node_allocator_type         _alloc;
        Node<ft::pair<Key, Value> >   *_root;
        Node<ft::pair<Key, Value> >   *_end;
        Node<ft::pair<Key, Value> >   *_rend;
        int                         _size;

        Tree()
        {
            _alloc = Node_allocator_type();
            _root = NULL;
            _size = 0;
            _rend = _alloc.allocate(1);
            _alloc.construc(_rend);
            _end = _alloc.allocate(1);
            _alloc.construc(_end);
            _rend->right = _end;
            _end->parent = _rend;
        }

        void destroy(Node<ft::pair<Key, Value> > *node)
        {
            if (node->left)
                destroy(node->left);
            else if (node->right)
                destroy(node->right);
            _alloc.destroy(node);
            _alloc.deallocate(node, 1);
        }

        Node<ft::pair<Key, Value> >  *add(Key k, Value val)
        {
            ft::pair<Key, Value> pair = ft::make_pair(k, val);
            Node<ft::pair<Key, Value> > *node = _alloc.allocate(1);
            _alloc.construct(node, pair);
            add(_root, node);
            return node;
        }
        
        Node<ft::pair<Key, Value> > *add(Key k, Value val, Node<ft::pair<Key, Value> > *node)
        {
            ft::pair<Key, Value> pair = ft::make_pair(k, val);
            Node<ft::pair<Key, Value> > *newnode = _alloc.allocate(1);
            
            _alloc.construct(newnode, pair);
            add(node, newnode);
            return newnode;
        }

        void    add(Node<ft::pair<Key, Value> > *parent, Node<ft::pair<Key, Value> > *node)
        {
            if (parent == _rend || (parent != _end && Compare()(parent->_data.first, node->data.first)))
            {
                if (parent->_right == NULL)
                {
                    parent->_right = node;
                    node->_parent = parent;
                }
                else
                    add(parent->_right, node);
            }
            else
            {
                if (parent->_left == NULL)
                {
                    parent->_left = node;
                    node->_parent = parent;
                }
                else
                    add(parent->_left, node);
            }
            _root->check_balance(parent, &_root);
        }

        Node<ft::pair<Key, Value> > *find(Key k)
        {
            return (findIt(_root, k));
        }

        Node<ft::pair<Key, Value> > *findIt(Node<ft::pair<Key, Value> > *node, Key k)
        {
            if (node == NULL)
                return NULL;
            if (node != end && node != rend && node->_data.first == k)
                return node;
            if (node == end || compare()(k, node->_data.first))
            {
                if (node->_left)
                    return (findIt(node->_left, k));
                return NULL;
            }
            else
            {
                if (node->_right)
                    return (findIt(node->_right, k));
                return NULL;
            }
        }

        

};

#endif