#include "OrgChart.hpp"
const bool flag = false;

namespace ariel{

    //Adds a root to OrgChart
    OrgChart& OrgChart::add_root(string const &change){
        //If there is already a root
        if(root != nullptr){
         //Rename the existing root
         this->root->my_name = change;
         //If there is no root
        }else{
         //Will create new Node and put him in the root   
         this->root = new Node(change);
         this->has_root=true;  
        }
        return *this;
    }
     
    //Add a person under his boss
    OrgChart& OrgChart::add_sub(string const &name, string const &name_to_add){
        //If there are no people, it is not possible to lead under someone, an error
        if(this->has_root==flag){
            throw invalid_argument("there are no people, it is not possible to lead under someone");
        }
        //Finds the Node below which we want to add
        Node* curr = get_the_Node(this->root,name);
        // if the node is null
        if(curr == nullptr){
            throw invalid_argument("there are no people with this name");
        }
        //Will create new Node 
        Node * node_to_add = new Node {name_to_add};
        // add the new person
        curr->persons.push_back(node_to_add);
        return *this;
    }

   //Transferring one OrgChart to my OrgChart
    OrgChart& OrgChart::operator=(const OrgChart& OrgChart1){

        if(&OrgChart1 == this){
            return *this;
        }
        //delete my old OrgChart
        this->delete_the_Org(this->root);
        // add the root of the OrgChart that i get to my root
        this->root = new Node(OrgChart1.root->my_name, OrgChart1.root->persons);
        return *this; 
     }

   //The function deletes all the people below the Node we got
    void OrgChart::delete_the_Org(Node* root){
        //No Node null , we done 
        if(root == nullptr){
            return;
        }
         //Goes through all the people under the Node we got and deletes them   
        for (size_t i = 0; i< root->persons.size(); i++){
             //and send the function in recursion for each person
            delete_the_Org(root->persons.at(i));
                
        }
        // in the end delete the root
        delete root;
    }


     //Returns the existing NODE with the name we received
    OrgChart::Node* OrgChart::get_the_Node(Node* root,string const & name){
        //If the root we got from which we are looking for is the same as the vertex we are looking for
        //we will return it
        if(root->my_name == name){
            return root;
        }
        //If not, we will go through all the sons of the node we received 
        //and send the function in recursion for each person
        for (size_t i = 0; i < root->persons.size(); i++){
            Node * ans = this->get_the_Node(root->persons.at(i), name);
                if (ans != nullptr){
                    return ans;
                }
             }
        
        return nullptr;
    }
    
    // check that the OrgChart is not empty
    void OrgChart::check_how_mach()const{
        if(this->has_root == flag){ 
            throw invalid_argument("the root is empty");
        } 

    }
    
    //The function builds a new level_iterator
     OrgChart::Iterator OrgChart::begin_level_order() const{
        OrgChart::check_how_mach();
        return Iterator("level_order",this->root);
    }

    //The function builds a new level_iterator
    OrgChart::Iterator OrgChart::end_level_order() const{
        OrgChart::check_how_mach();
        return Iterator("level_order",nullptr);
    }

   //The function builds a new reverse_iterator
    OrgChart::Iterator OrgChart::reverse_order() const{
        OrgChart::check_how_mach();
        return Iterator("reverse_order", nullptr);
    }

     //The function builds a new reverse_iterator
     OrgChart::Iterator OrgChart::begin_reverse_order()const{
        OrgChart::check_how_mach();
        return Iterator("reverse_order", this->root);
    }

    //The function builds a new preorder_iterator    
    OrgChart::Iterator OrgChart::begin_preorder() const{
        OrgChart::check_how_mach();
        return Iterator("preorder", this->root);
    }

    //The function builds a new preorder_iterator 
    OrgChart::Iterator OrgChart::end_preorder() const{
        OrgChart::check_how_mach();
        return Iterator("preorder", nullptr);
    }

     //begin of the iterator of level order
    OrgChart::Iterator OrgChart::begin() const{
        return begin_level_order();
    }
    
     //end of the iterator of level order
    OrgChart::Iterator OrgChart::end() const{
        return end_level_order();
    }
    

    //Override of <<
    ostream& operator<<(ostream& os,const OrgChart &OrgChart1){
        os << "My OrgChart :"<<endl;
        for(auto const &node: OrgChart1){
            os<< node<< " ";
        } 
        os<< endl;
        return os;
    }

  

    //fill the vector of the iterator depending on the type of the order.
    void OrgChart::Iterator::Build_iterator(string const &type, Node* node){
       //The idea of ​​the function:
       //Every time I go over the first node I got and add all his sons and I do it again to the rest
       // take them and add their sons
        if(type == "level_order"){
            // save here the sorted person 
            queue<Node*> ans;
            // add the first
            ans.push(node);
            // As long as the queue is not empty
            //as long as there are people we have not passed over the people below them
            while(!ans.empty()){
                for (int i=0; i< ans.size(); i++){
                    // see the first person in the queue and save him
                    Node* curr = ans.front();
                    // save the order in the Iterator
                    this->vals.push_back(curr);
                    // save the sum of the peoples that below my person
                    size_t size = curr->persons.size();
                    // delete the person that i save 
                    ans.pop();
                    // add to the queue all the peoples that below my person
                    for(size_t j =0 ; j <size; j++){
                        // add to the ans all the peoples that below
                        ans.push(curr->persons.at(j));
                    }
                }
            }
        }
        
        //The idea of ​​the function:
        //Save the data in the reverse order in the list 
        //and each time you add the last to the iterator so we get the reverse order
        if(type == "reverse_order"){
            queue<Node*> ans;
            // save the order (afther that i take the person from the end to the begin)
            stack<Node*> help_stack;
            // add the first
            ans.push(node);
             // As long as the queue is not empty
            while(!ans.empty()){
                // see the first person in the queue and save him
                Node* curr= ans.front();
                // save the order in the list
                help_stack.push(curr);
                 // save the sum of the peoples that below my person
                int size = int(curr->persons.size())-1;
                // delete the person that i save 
                ans.pop();
                // add to the queue all the peoples that below my person form the end to begin
                for( int i=size ; i >= 0 ; i--){
                    ans.push(curr->persons.at((size_t)i));
                }
            }
            // As long as i have more person to add the Iterator
            // add in reverse
            while (!help_stack.empty()){
                // take the last person
                Node * current= help_stack.top();
                // delete the last 
                help_stack.pop();
                // add the last 
                vals.push_back(current);
                
            }
        }

        //The idea of ​​the function:
        //Reading the node, then reading its sub-tree
        //first the left sub-tree and then the right sub-tree.
        if(type=="preorder"){
            // save here the sorted person 
            stack<Node*> ans;
            // add the last
            ans.push(node);
             // As long as the stack is not empty
            while(!ans.empty()){
                // see the last person in the queue and save him
                Node* curr = ans.top();
               // save the order in the Iterator
                this->vals.push_back(curr);
                // save the sum of the peoples that below my person
                int size = int(curr->persons.size())-1;
                // selete the lest person from the stack
                ans.pop();
                // add to the stack all the peoples that below my person form the end to begin
                for(int i=size ; i>=0 ; i-- ){
                    ans.push(curr->persons.at((size_t)i));
                }               
            }
        } 
 
    }


    //Override of ->
    string* OrgChart::Iterator::operator->() const {
		return &(vals.at(this->sum)->my_name);
	}
    
    //Override of *
    string& OrgChart::Iterator::operator*() const {
		return vals.at(this->sum)->my_name;
	}

    //Override of ++x
    OrgChart::Iterator& OrgChart::Iterator::operator++(){
        this->sum++;
        return *this; 
    }

    //Override of x++
    OrgChart::Iterator OrgChart::Iterator::operator++(int){
        Iterator curr = *this;
        this->sum++;
        return curr; 
    }
              	
    //Override of ==
    bool OrgChart::Iterator::operator==(const Iterator& iterator1) const {
		return (vals.at(this->sum) == iterator1.vals.at(iterator1.sum));
	}

    //Override of !=
    bool OrgChart::Iterator::operator!=(const Iterator& iterator1) const {
		return !(vals.at(this->sum) == iterator1.vals.at(iterator1.sum));
	}


}