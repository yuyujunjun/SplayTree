#include <iostream>
#include"SplayTree.h"
using namespace std;
node insert(node root,int num)
{
    if(root==NULL){
        root=new tree;
        root->right=root->left=NULL;
        root->num=num;
        return root;
    }else if(num>root->num){
        root->right=insert(root->right,num);
        root->right->parent=root;
        return root;
    }else if(num<root->num){
        root->left=insert(root->left,num);
        root->left->parent=root;
        return root;
    }
}
void left_rotate(node p,node c)
{
    p->right=c->left;
    if(p->right)p->right->parent=p;
    c->left=p;
    c->parent=p->parent;
    p->parent=c;


}
void right_rotate(node p,node c){
    p->left=c->right;
    if(p->left)p->left->parent=p;
    c->right=p;
    c->parent=p->parent;
    p->parent=c;

}
node findLeft_Max(node root){
    if(!root)cout<<"没有数据呢，能不能长点心"<<endl;
    else {
        if(root->left){
            root=root->left;
            while(root->right){
                root=root->right;
            }
            return root;
        }
        else return NULL;

    }
}
node find(node root, int num)
{
    if(!root){
        cout<<"找不到欸，哭哭";
        return NULL;
    }else if(num>root->num){
        return find(root->right,num);
    }else if(num<root->num)
    {
        return find(root->left,num);
    }else if(num==root->num)return root;

}

void splay(node root,node current){
    if(!root||!current){
        cout<<"你怎么可以傻到splay空树或空结点呢，你走吧，我就当没你这个儿子";
        return ;
    }
    while(1){
        if(current->parent==NULL)break;
        else {
            node p=current->parent;
            node g=NULL;
            if(p)g=p->parent;
            node gg=NULL;
            if(g)gg=g->parent;
            if (current->num > root->num) {
                if (root->right == current) {
                    left_rotate(p, current);
                    root=root->parent;
                }else if(root->right->left==current){
                    right_rotate(p,current);
                    current->parent->right=current;
                    left_rotate(g,current);
                    if(gg!=NULL){
                        if(gg->right==g)gg->right=current;
                        else if(gg->left==g)gg->left=current;
                    }
                    if(!gg);
                    else if(!gg->parent)root=gg;
                    else root=gg->parent;
                }else if(root->right->right==current){
                    left_rotate(g,p);
                    if(gg){
                        if(gg->left==g)gg->left=p;
                        else if(gg->right==g)gg->right=p;
                    }
                    left_rotate(p,current);
                    if(gg){
                        if(gg->left==p)gg->left=current;
                        else if(gg->right==p)gg->right=current;
                    }///////////////////////////
                    if(!gg);
                    else if(!gg->parent)root=gg;
                    else root=gg->parent;
                }else root=root->right;
            }else if(current->num<root->num){
                if(root->left==current){
                    right_rotate(p,current);
                    root=root->parent;
                }else if(root->left->left==current){
                    right_rotate(g,p);
                    if(gg){
                        if(gg->right==g)gg->right=p;
                        else if(gg->left==g)gg->left=p;
                    }
                    right_rotate(p,current);
                    if(gg){
                        if(gg->right==p)gg->right=current;
                        else if(gg->left==p)gg->left=current;
                    }////////////////////////////////////////////
                    if(!gg);
                    else if(!gg->parent)root=gg;
                    else root=gg->parent;
                }else if(root->left->right==current){
                    left_rotate(p,current);
                    current->parent->left=current;
                    right_rotate(g,current);
                    if(gg){
                        if(gg->left==g)gg->left=current;
                        else if(gg->right==g)gg->right=current;
                    }
                    if(!gg);
                    else if(!gg->parent)root=gg;
                    else root=gg->parent;
                }else root=root->left;
            }
        }
    }
}
node del(node root,int num){
    if(!root){
        cout<<"傻逼你连树也没有删个球？";
    } else {
        node current=find(root,num);
        if(current){
            splay(root,current);
            if(!current->left){
                node delt=current;
                current=current->right;
                current->parent=NULL;
                delete delt;
                return current;
            }else if(root->left){
                node Left_Max=findLeft_Max(current);
                current->num=Left_Max->num;
                if(Left_Max->parent->right==Left_Max)Left_Max->parent->right=NULL;
                else if(Left_Max->parent->left==Left_Max)Left_Max->parent->left=NULL;
                if(Left_Max->left){
                    Left_Max->left->parent=Left_Max->parent;
                    if(Left_Max->parent->num<Left_Max->left->num)
                    Left_Max->parent->right=Left_Max->left;
                    else Left_Max->parent->left=Left_Max->left;
                }
                delete Left_Max;
                return current;
            }else  delete current;
        }

    }


}
void Print(node root){
    if(root){
        cout<<root->num<<" " ;
        if(root->left)Print(root->left);
        if(root->right)Print(root->right);
    }
}
int main() {
    int N;
    cin>>N;
    node tree=NULL;
    for(int i=0;i<N;i++)
    {
        int number;
        cin>>number;
        tree=insert(tree,number);
        tree->parent=NULL;
    }
    Print(tree);
    for(int i=0;i<N;i++)
    {
        int number;
        cin>>number;
        tree=del(tree,number);
        Print(tree);
    }

    std::cout << "Hello, World!" << std::endl;
    return 0;
}