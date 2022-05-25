#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <queue>
#include <vector>
#include <stack>
using namespace std;


namespace ariel{

    class OrgChart {

        //Construction of node Which represents a person
        //With their help we will build our OrgChart
        struct Node{
            public:
            // the name of the node 
            string my_name;
            // All the people below him
            vector<Node*> persons;

            //std::move is used to indicate that an object may be "moved from"
            //allowing the efficient transfer of resources from object to another object.
            Node(string name){
             this->my_name = move(name);
             this->persons={}; 
            }  

            // copy constructor
            Node(string name, vector<Node*> persons_){
             this->my_name = move(name);
             this->persons= move(persons_); 
            }
            
        };

        public:
        Node* root;
        bool has_root;
        
        //constructor
        OrgChart(){
          this->root = nullptr;
          this->has_root=false;  
        }

        //copy constructor
        OrgChart(OrgChart &OrgChart1){
        this->root = OrgChart1.root;
        this->has_root = OrgChart1.has_root;
        }

        //take OrgChart1 copy him and afther delete him
        OrgChart(OrgChart &&OrgChart1) noexcept;
        
        // destructor
        ~OrgChart(){
        this->delete_the_Org(root);
        } 

        Node* get_the_Node(Node* root,string const & name);
        void check_how_mach() const;
        void delete_the_Org(Node * root);
        OrgChart& add_root(string const &change);
        OrgChart& add_sub(string const & name, string const &name_to_add);
        friend ostream& operator<<(ostream& os,const OrgChart &OrgChart1);
         //take OrgChart1 copy him and afther delete him
        OrgChart& operator=(OrgChart&& OrgChart1) noexcept;
        OrgChart& operator=(const OrgChart& OrgChart1);
        
        
        // my iterator //
        class Iterator{
        public:
        vector<Node*> vals;
        size_t sum; 

        
        //constructor
        Iterator(string const & type, Node* node){
        this->sum=0;
        if(node != nullptr){
        Build_iterator(type,node);
        }
        this->vals.push_back(nullptr);
        }
            
            
        void Build_iterator(string const &type, Node* node);
        string& operator*() const;
        string* operator->() const;
        Iterator& operator++();
        Iterator operator++(int);
        bool operator==(const Iterator& Iterator1) const;
        bool operator!=(const Iterator& iterator1) const;
        };

        Iterator begin_level_order()const;
        Iterator end_level_order() const;
        Iterator reverse_order() const;
        Iterator begin_reverse_order()const;
        Iterator begin_preorder() const;
        Iterator end_preorder() const;
        Iterator end() const;
        Iterator begin() const;
        
    };
    

}