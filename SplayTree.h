struct tree{
     struct tree* left;
     struct tree* right;
     struct tree* parent;
     int num;

};
typedef struct tree* node;
node insert(node root,int num);
void left_rotate(node p,node c);
void right_rotate(node p,node c);
void splay(node root,node current);
node del(node root,int num);
node find(node root,int num);
node findLeft_Max(node root);
void Print(node root);