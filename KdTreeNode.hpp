#ifndef KDTREENODE_HPP
#define KDTREENODE_HPP

using namespace std;
 
class kdTreeNode {
    
public:
     
    kdTreeNode();
    kdTreeNode(float _x, float _y);
    kdTreeNode(const kdTreeNode& orig);
    virtual ~kdTreeNode();
    kdTreeNode& operator=(const kdTreeNode &R);
    float getYInicial();
    void setYInicial(float y);
     
    float getX() const;
    float getY() const;
    bool getLevel() const;
    bool getBeenHere() const;
    
    kdTreeNode* getLeft() const;
    kdTreeNode* getRight() const;
    kdTreeNode* getParent() const;
     
    void setX(float _x);
    void setY(float _y);
    void setLevel(bool _lev);
    void setBeenHere(bool _here);
     
    void setLeft(kdTreeNode* newLeft);
    void setRight(kdTreeNode* newRight);
    void setParent(kdTreeNode* newParent);
     
    void printNodes();
    
    void clearFlags();
    
    void findPath(kdTreeNode *entry);
     
    void removeNode(kdTreeNode* entry, kdTreeNode* root);
    
    void insertNode(kdTreeNode* newNode, kdTreeNode* &root);
     
    void distributeSubtree(kdTreeNode* entry, kdTreeNode* root);
     
    void distributeTreeWithNewRoot(kdTreeNode* root, bool rootWasSet);
    
    double findDistanceBetweenTwoPoints(kdTreeNode* node1, kdTreeNode* node2); 
     
    kdTreeNode* findNewRoot(kdTreeNode* root);
    
    kdTreeNode* findClosestNode(kdTreeNode* entry);
     
    kdTreeNode* closestNodeInPath(kdTreeNode* entry, kdTreeNode* root);

    bool getYaContado();

    void setYaContado(bool flag);
    
private:
     
    float x;
    float y;
    bool level;
    bool beenHere;
    bool yaContado;
    float YInicial;
    
    kdTreeNode* left;
    kdTreeNode* right;
    kdTreeNode* parent;
 
};
   
#endif /* KDTREENODE_H */