#include<bits/stdc++.h>
using namespace std;


class rb {
public:
    int val;
    int col;
    rb* left;
    rb* right;
    rb* par;
    rb(int v) {
        val = v;
        col = 0;
        left = NULL;
        right = NULL;
        par = NULL;
    }

};

rb* r;


rb* rotate_left(rb* node)
    {
        rb* x = node->right;
        rb* y = node->left;
        x->left = node;
        node->right = y;
        node->par = x; // parent resetting is also important.
        if(y!=NULL)
            y->par = node;
        return(x);
    }
    //this function performs right rotation
    rb* rotate_right(rb* node)
    {
        rb* x = node->left;
        rb* y = x->right;
        x->right = node;
        node->left = y;
        node->par = x;
        if(y!=NULL)
            y->par = node;
        return(x);
    }

void preorder(rb* root) {
	if(!root)
		return;
	cout<<root->val<<" ";
	preorder(root->left);
	preorder(root->right);
}

int ll, lr, rl, rr;
rb* insert_helper(rb* root, int val) {
	bool conflict = false;
	if(root==NULL) {
    	rb* root = new rb(val);
    	return root;
    } else {
    	if(root->val>val) {
    		root->left = insert_helper(root->left, val);
    		root->left->par = root;
    		if(root->col==root->left->col && root->col==0) {
    			conflict = true;
    		}
    	} else {
    		root->right = insert_helper(root->right, val);
    		root->right->par = root;
    		if(root->col==root->right->col && root->col==0) {
    			conflict = true;
    		}
    	}
    }

    if(ll==1) {
    	root = rotate_left(root);
    	root->col = 1;
    	root->left->col=0;
    	ll=0;
    } else if(lr==1) {
    	root->left = rotate_left(root->left);
        root->left->par = root;
        root = rotate_right(root);
        root->col = 1;
    	root->right->col=0;


    	lr=0;
    } else if(rl==1) {
        root->right = rotate_right(root->right);
        root->right->par = root;
        root = rotate_left(root);
        root->col = 1;
    	root->left->col=0;

        rl=0;
    } else if(rr==1) {
        root = rotate_right(root);
        root->col = 1;
        root->right->col=0;
        rr=0;
    }

    if(conflict) {
    	if(root->par->left==root) {
    		if(root->par->right==NULL||root->par->right->col==1) {
    			if(root->left && root->left->col==0) {
    				rr=1;
    			} else if(root->right && root->right->col==0){
    				lr=1;
    			}

    		} else {
    			root->col=1;
    			root->par->right->col=1;
    			if(root->par!=r)
    			root->par->col=0;

    		}
    	} else {
    		if(root->par->left==NULL || root->par->left->col==1) {
    			if(root->left && root->left->col==0) {
    				rl=1;
    			} else if(root->right && root->right->col==0){
    				ll=1;
    			}

    		} else {
    			root->col=1;
    			root->par->left->col=1;
    			if(root->par!=r)
    			root->par->col=0;
    		}
    	}
    }
    return root;
}

rb* insert(rb* root, int val) {
    if(root==NULL) {
    	rb* root = new rb(val);
    	root->col=1;
    	return root;
    } else {
    	return insert_helper(root,val);
    }
    
}

int main() {
	vector<int>v{3,21,32,15};
	rb* root=NULL;
	r = NULL;
	for(auto &x:v) {
		ll=0, lr=0, rl=0, rr=0;
		root = insert(root, x);
		if(r==NULL)
			r = root;
        preorder(root);
        cout<<"\n";
	}
	return 0;
}