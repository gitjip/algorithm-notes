#include <iostream>
#include <cstring>
using namespace std;

const int MAX_SIZE = 1000;  // 伸展树最大节点数

class ArraySplayTree {
private:
    int key[MAX_SIZE];           // 存储节点键值
    int parent[MAX_SIZE];        // 父节点下标，-1表示无父节点
    int left[MAX_SIZE];          // 左孩子下标，-1表示无左孩子
    int right[MAX_SIZE];         // 右孩子下标，-1表示无右孩子
    bool is_left_child[MAX_SIZE];// 标记是否为父节点的左孩子
    int root;                    // 根节点下标
    int cnt;                     // 已使用节点数

    // 左旋操作
    void rotate_left(int x) {
        int y = parent[x];
        int T2 = left[x];

        if (T2 != -1) {
            parent[T2] = y;
            is_left_child[T2] = (left[y] == x);
        }
        right[y] = T2;

        parent[x] = parent[y];
        if (parent[y] != -1) {
            if (is_left_child[y]) {
                left[parent[y]] = x;
            } else {
                right[parent[y]] = x;
            }
            is_left_child[x] = is_left_child[y];
        } else {
            root = x;
            is_left_child[x] = false;
        }

        parent[y] = x;
        is_left_child[y] = true;
        left[x] = y;
    }

    // 右旋操作
    void rotate_right(int x) {
        int y = parent[x];
        int T2 = right[x];

        if (T2 != -1) {
            parent[T2] = y;
            is_left_child[T2] = (left[y] == x);
        }
        left[y] = T2;

        parent[x] = parent[y];
        if (parent[y] != -1) {
            if (is_left_child[y]) {
                left[parent[y]] = x;
            } else {
                right[parent[y]] = x;
            }
            is_left_child[x] = is_left_child[y];
        } else {
            root = x;
            is_left_child[x] = false;
        }

        parent[y] = x;
        is_left_child[y] = false;
        right[x] = y;
    }

    // 伸展操作：将x移到根
    void splay(int x) {
        while (parent[x] != -1) {
            int p = parent[x];
            if (parent[p] == -1) { // 单旋
                if (is_left_child[x]) rotate_right(x);
                else rotate_left(x);
            } else {
                int g = parent[p];
                if (is_left_child[p] == is_left_child[x]) { // zig-zig
                    if (is_left_child[p]) {
                        rotate_right(p);
                        rotate_right(x);
                    } else {
                        rotate_left(p);
                        rotate_left(x);
                    }
                } else { // zig-zag
                    if (is_left_child[x]) {
                        rotate_right(x);
                        rotate_left(x);
                    } else {
                        rotate_left(x);
                        rotate_right(x);
                    }
                }
            }
        }
    }

    // 合并两棵树：左树最大值 < 右树最小值
    int merge(int left_tree, int right_tree) {
        if (left_tree == -1) return right_tree;
        if (right_tree == -1) return left_tree;

        // 找左树的最右节点（最大值）
        int max_node = left_tree;
        while (right[max_node] != -1) {
            max_node = right[max_node];
        }
        splay(max_node); // 伸展为左树根
        // 合并右树到 max_node 的右子树
        right[max_node] = right_tree;
        parent[right_tree] = max_node;
        is_left_child[right_tree] = false;
        return max_node;
    }

public:
    ArraySplayTree() {
        memset(key, 0, sizeof(key));
        memset(parent, -1, sizeof(parent));
        memset(left, -1, sizeof(left));
        memset(right, -1, sizeof(right));
        memset(is_left_child, false, sizeof(is_left_child));
        root = -1;
        cnt = 0;
    }

    // 插入节点
    void insert(int k) {
        if (cnt >= MAX_SIZE) {
            cout << "树已满，无法插入！" << endl;
            return;
        }
        int new_node = cnt++;
        key[new_node] = k;

        if (root == -1) {
            root = new_node;
            return;
        }

        int curr = root;
        int p = -1;
        bool is_left = false;
        while (curr != -1) {
            p = curr;
            if (k < key[curr]) {
                curr = left[curr];
                is_left = true;
            } else {
                curr = right[curr];
                is_left = false;
            }
        }

        parent[new_node] = p;
        is_left_child[new_node] = is_left;
        if (is_left) left[p] = new_node;
        else right[p] = new_node;

        splay(new_node);
    }

    // 查找节点，找到返回下标，否则返回-1
    int find(int k) {
        int curr = root;
        while (curr != -1 && key[curr] != k) {
            if (k < key[curr]) curr = left[curr];
            else curr = right[curr];
        }
        if (curr != -1) splay(curr);
        return curr;
    }

    // 删除节点
    bool remove(int k) {
        int del_node = find(k);
        if (del_node == -1) {
            cout << "节点 " << k << " 不存在！" << endl;
            return false;
        }
        // 目标节点已伸展到根
        int left_sub = left[del_node];
        int right_sub = right[del_node];

        // 断开子树与删除节点的关系
        if (left_sub != -1) parent[left_sub] = -1;
        if (right_sub != -1) parent[right_sub] = -1;

        // 合并左右子树作为新根
        root = merge(left_sub, right_sub);
        return true;
    }

    // 中序遍历
    void inorder(int node) {
        if (node == -1) return;
        inorder(left[node]);
        cout << key[node] << " (left: " << boolalpha << is_left_child[node] << ") ";
        inorder(right[node]);
    }

    void inorder() {
        inorder(root);
        cout << endl;
    }
};

// 测试代码
int main() {
    ArraySplayTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(5);
    tree.insert(15);

    cout << "初始中序遍历：";
    tree.inorder();

    tree.remove(15);
    cout << "删除15后遍历：";
    tree.inorder();

    tree.remove(10);
    cout << "删除10后遍历：";
    tree.inorder();

    return 0;
}