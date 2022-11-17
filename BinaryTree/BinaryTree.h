#pragma once

#include <memory>
#include <iostream>

template<class T>
class BinaryTree
{
    struct Node
    {
        T _key = T();
        std::unique_ptr<Node> _left;
        std::unique_ptr<Node> _right;
    };

    std::unique_ptr<Node> _root;

public:
    BinaryTree() = default;
    ~BinaryTree() = default;
    BinaryTree(const BinaryTree &other);
    BinaryTree(BinaryTree &&other) noexcept;
    BinaryTree(const std::initializer_list<T> &list);
    BinaryTree& operator = (const BinaryTree &other);
    BinaryTree& operator = (BinaryTree &&other) noexcept;

    void preorder_print();
    void inorder_print();
    void postorder_print();

    void insert(const T& value);
    T find_max() ;
    T find_min();
    bool find(const T& value);
    bool isEmpty();

    void delete_node(const T& value);
    


private:
    void insert_p(const T& value, std::unique_ptr<Node>& ptr);
    void transfer(const std::unique_ptr<Node>& ptr);
    void delete_node_p(std::unique_ptr<Node>& ptr);

    void preorder_print_p(const std::unique_ptr<Node>& ptr);
    void inorder_print_p(const std::unique_ptr<Node>& ptr);
    void postorder_print_p(const std::unique_ptr<Node>& ptr);


   std::unique_ptr<Node>& find_max_p(std::unique_ptr<Node>& ptr);
   std::unique_ptr<Node>& find_min_p(std::unique_ptr<Node>& ptr);
   std::unique_ptr<Node>& find_p(const T& value, std::unique_ptr<Node>& ptr);
   std::unique_ptr<Node>& find_parent(std::unique_ptr<Node>& child, std::unique_ptr<Node>& ptr);
   std::unique_ptr<Node>& find_succsessor(std::unique_ptr<Node>& ptr);
};

template<class T>
BinaryTree<T>::BinaryTree(const BinaryTree& other)
{
    transfer(other._root);
}

template<class T>
BinaryTree<T>::BinaryTree(BinaryTree&& other) noexcept
{
    other._root.swap(_root);
    
}

template<class T>
BinaryTree<T>::BinaryTree(const std::initializer_list<T>& list)
{
    for (const auto& el : list)
    {
        insert_p(el, _root);
    }
}

template<class T>
BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree& other)
{
    BinaryTree copy(other);
    _root.swap(copy._root);
    return *this;


}

template<class T>
BinaryTree<T>& BinaryTree<T>::operator=(BinaryTree&& other) noexcept
{
    _root.swap(other._root);
    return *this;

}

template<class T>
void BinaryTree<T>::preorder_print()
{
    preorder_print_p(_root);
}

template<class T>
void BinaryTree<T>::inorder_print()
{
    inorder_print_p(_root);
}

template<class T>
void BinaryTree<T>::postorder_print()
{
    postorder_print_p(_root);
}

template<class T>
void BinaryTree<T>::insert(const T& value)
{
    insert_p(value, _root);
}

template<class T>
 T BinaryTree<T>::find_max()
{
   std::unique_ptr<Node> &ref = find_max_p(_root);

    if (ref != nullptr)
    {
        return ref->_key;
        
    }
    else
    {
        throw std::exception("Tree is empty");
    }

    
}

 template<class T>
 T BinaryTree<T>::find_min()
 {
     std::unique_ptr<Node>& ref = find_min_p(_root);

     if (ref == nullptr)
     {
         
         throw std::exception("Tree is empty");
         
     }
     else
     {
         return ref->_key;
         
     }
 }

 template<class T>
 bool BinaryTree<T>::find(const T& value)
 {
     if (find_p(value, _root) ==nullptr)
     {
         return false;
     }
     else
     {
         return true;
     }
 }

 template<class T>
 bool BinaryTree<T>::isEmpty()
 {
     return _root == nullptr;
 }

 template<class T>
 void BinaryTree<T>::delete_node(const T& value)
 {
     delete_node_p(find_p(value,_root));

 }


template<class T>
void BinaryTree<T>::insert_p(const T& value, std::unique_ptr<Node>& ptr)
{
    if (ptr == nullptr)
    {
        ptr = std::make_unique<Node>();
        ptr->_key = value;
    }
    else if (value < ptr->_key)
    {
        insert_p(value, ptr->_left);
    }
    else
    {
        insert_p(value, ptr->_right);
    }
}
template<class T>
void BinaryTree<T>::transfer(const std::unique_ptr<Node>& ptr)
{
    if (ptr != nullptr)
    {
        insert_p(ptr->_key,_root);
        transfer(ptr->_left);
        transfer(ptr->_right);

    }
}

template<class T>
void BinaryTree<T>::delete_node_p(std::unique_ptr<Node>& ptr)
{
    if (ptr == nullptr) {
        return;
    }
    else if (ptr->_left == nullptr && ptr->_right == nullptr)
    {
        ptr.reset();

    }
    else if (ptr->_left != nullptr && ptr->_right != nullptr)
    {
        std::unique_ptr<Node>& min = find_succsessor(ptr);
        ptr->_key = min->_key;
        delete_node_p(min);
    }

    else
    {
        std::unique_ptr<Node> tmp;
        if (ptr->_right != nullptr)
        {
            tmp = move(ptr->_right);
        }
        else
        {
            tmp = move(ptr->_left);
        }


        if (ptr != _root)
        {
            std::unique_ptr<Node>& parent = find_parent(ptr, _root);
            ptr.reset();
            if (parent->_left == ptr)
            {
                parent->_left = move(tmp);
            }
            else
            {
                parent->_right = move(tmp);
            }


        }
        else
        {
            ptr.reset();
            _root = move(tmp);
        }
    }
}

template<class T>
void BinaryTree<T>::preorder_print_p(const std::unique_ptr<Node>& ptr)
{
    if (ptr != nullptr) {
        std::cout << ptr->_key << std::endl;
        preorder_print_p(ptr->_left);
        preorder_print_p(ptr->_right);
    }
}

template<class T>
void BinaryTree<T>::inorder_print_p(const std::unique_ptr<Node>& ptr)
{
    if (ptr != nullptr) {
        inorder_print_p(ptr->_left);
        std::cout << ptr->_key << std::endl;
        inorder_print_p(ptr->_right);
    }
}

template<class T>
void BinaryTree<T>::postorder_print_p(const std::unique_ptr<Node>& ptr)
{
    if (ptr != nullptr) {
        postorder_print_p(ptr->_left);
        postorder_print_p(ptr->_right);
        std::cout << ptr->_key << std::endl;
    }
}

template<class T>
std::unique_ptr<typename BinaryTree<T>::Node>& BinaryTree<T>::find_max_p(std::unique_ptr<Node>& ptr) 
{
     if (ptr==nullptr||ptr->_right == nullptr)
    {
        return ptr;
    }
    find_max_p(ptr->_right);
}

template<class T>
std::unique_ptr<typename BinaryTree<T>::Node>& BinaryTree<T>::find_min_p(std::unique_ptr<Node>& ptr)
{
    if (ptr == nullptr || ptr->_left == nullptr)
    {
        return ptr;
    }
    find_min_p(ptr->_left);
}

template<class T>
std::unique_ptr<typename BinaryTree<T>::Node>& BinaryTree<T>::find_p(const T& value,  std::unique_ptr<Node>& ptr)
{

     if(ptr == nullptr||ptr->_key == value)
     {
         return ptr;
     }
     else if (value < ptr->_key)
     {

         find_p(value, ptr->_left);
     }
     else
     {
         find_p(value, ptr->_right);
     }
}

 template<class T>
 std::unique_ptr<typename BinaryTree<T>::Node>& BinaryTree<T>::find_parent(std::unique_ptr<Node>& child, std::unique_ptr<Node>& ptr)
 {
     if (ptr == nullptr)
     {
         throw std::exception("Tree is empty");
     }
     else if (ptr->_right == child || ptr->_left == child)
     {
         return ptr;
     }
     else if (child->_key < ptr->_key)
     {

         find_parent(child, ptr->_left);
     }
     else
     {
         find_parent(child, ptr->_right);
     }
 }

 template<class T>
 std::unique_ptr<typename BinaryTree<T>::Node>& BinaryTree<T>::find_succsessor(std::unique_ptr<Node>& ptr)
 {
     if (ptr==nullptr)
     {
         throw std::exception("Tree is empty");
     }
     else 
     {
         return find_min_p(ptr->_right);
     }
 }


