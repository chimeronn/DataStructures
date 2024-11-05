import java.util.Iterator;
import java.util.LinkedList;
import java.util.Queue;

public class AVLTree implements Iterable<Integer>{
    Node root;
    public AVLTree(Node root) {
        this.root = root;
    }

    public Node rightRotation(Node rotationRoot) {
        Node rootLeft = rotationRoot.left;

        rotationRoot.left = rootLeft.right;
        rootLeft.right = rotationRoot;

        rootLeft.height = 1 + Math.max(rootLeft.left.height, rootLeft.right.height);
        int leftHeight = 0;
        int rightHeight = 0;
        leftHeight = rotationRoot.left != null ? rotationRoot.left.height : 0;
        rightHeight = rotationRoot.right != null ? rotationRoot.right.height : 0;
        rotationRoot.height = 1 + Math.max(leftHeight, rightHeight);

        if(rotationRoot == root) {
            root = rootLeft;
        }
        return rootLeft;
    }

    public Node leftRotation(Node rotationRoot) {
        Node rootRight = rotationRoot.right;

        rotationRoot.right = rootRight.left;
        rootRight.left = rotationRoot;

        rootRight.height = 1 + Math.max(rootRight.left.height, rootRight.right.height);
        int leftHeight = 0;
        int rightHeight = 0;
        leftHeight = rotationRoot.left != null ? rotationRoot.left.height : 0;
        rightHeight = rotationRoot.right != null ? rotationRoot.right.height : 0;
        rotationRoot.height = 1 + Math.max(leftHeight, rightHeight);

        if(rotationRoot == root) {
            root = rootRight;
        }
        return rootRight;
    }

    public Node insert(int val, Node currNode) {
        if(currNode == null) {
            return new Node(val);
        }

        if(val < currNode.getVal()) {
            currNode.left = insert(val, currNode.left);
        } else if(val > currNode.getVal()){
            currNode.right = insert(val, currNode.right);
        } else {
            return currNode;
        }

        if(currNode.left != null && currNode.right == null) {
            currNode.height = currNode.left.height + 1;
        } else if(currNode.left == null && currNode.right != null) {
            currNode.height = currNode.right.height + 1;
        } else if(currNode.left == null) {
            currNode.height = 0;
        } else {
            currNode.height = 1 + Math.max(currNode.left.height, currNode.right.height);
        }

        int balance = currNode.balance();
        System.out.println(balance);
        if(balance > 1 && val < currNode.left.getVal()) {
            return rightRotation(currNode);
        } else if(balance < -1 && val > currNode.right.getVal()) {
            return leftRotation(currNode);
        } else if(balance > 1 && val > currNode.right.getVal()) {
            currNode.left = leftRotation(currNode.left);
            rightRotation(currNode);
        } else if(balance < -1 && val < currNode.right.getVal()){
            currNode.right = rightRotation(currNode.right);
            leftRotation(currNode);
        }
        return currNode;
    }

    @Override
    public Iterator iterator() {
        return new TreeIterator(root);
    }

    private class TreeIterator implements Iterator<Integer>{
        private Queue<Integer> q;
        private Node root;

        public TreeIterator(Node root) {
            q = new LinkedList<>();
            this.root = root;
            buildQueue(this.root);
        }

        private void buildQueue(Node curr) {
            if(curr == null) {
                return;
            }
            buildQueue(curr.left);
            q.add(curr.getVal());
            buildQueue(curr.right);
        }

        @Override
        public boolean hasNext() {
            return !q.isEmpty();
        }

        @Override
        public Integer next() {
            return q.poll();
        }
    }
}

class Node {
    private int val;
    public Node left;
    public Node right;
    public int height;

    public Node(int val) {
        this.val = val;
        height = 0;
        left = null;
        right = null;
    }

    public int balance() {
        if(left == null && right != null) {
            return -right.height - 1;
        } else if(left != null && right == null) {
            return left.height + 1;
        } else if(left == null) {
            return 0;
        }
        return left.height - right.height;
    }

    public int getVal() {
        return val;
    }
}
