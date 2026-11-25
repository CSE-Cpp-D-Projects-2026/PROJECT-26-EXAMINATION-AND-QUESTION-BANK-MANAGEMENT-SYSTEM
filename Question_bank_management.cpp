//----------Question bank management system-----------------
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;


//-------------------Question record structure---------------------------------
struct Question{
    string qid;
    string qtext;
    string qtype;
    int qmark;
    string qDiff;
    int qunit;
    string qOut;
    string qRef;
    bool active = true;
};


//---------------------Blueprint Structure---------------------------------------
struct qblueprint{
    int tot_mark,dur;
    string u_cov;
    string diff;
    vector<section_structure> sec;
};

//--------------------Structure for Section--------------------------------------
struct section_structure{
    int sec_id, sec_mark;
    string sec_name;
};

//-------------------Structure of Subject---------------------------------------
struct subject_structure{
    int sub_code, sem;
    string sub_title, s_co, s_unit;
};



class Blueprint{
    vector<qblueprint> bluep; //-----blueprint as a rec
    vector<section_structure> sec_struct; // -----section structure as a rec=> to be stored in blueprint
    qblueprint b;

    public:
    //-----------------create blueprint-----------------
        void createBlueprint(){
            cout<<"Enter the total marks: ";
            cin>>b.tot_mark;
            cout<<"Enter the total duration: ";
            cin>>b.dur;
            cout<<"Enter the unit coverage: ";
            getline(cin,b.u_cov);
            cout<<"Section Structure\n";
            cout<<"Enter the number of sections: ";
            int n;
            cin>>n;
            for(int i=0;i<n;i++){
                b.sec.push_back(createSection());
            }
            cout<<"Enter the difficulty level: ";
            cin>>b.diff;
            cout<<"Blueprint details added Successfully!"<<endl;
            bluep.push_back(b);
        }

        //------------------create section structure-----------------
        section_structure createSection(){
            section_structure s;
            cout<<"Enter the section ID: ";
            cin>>s.sec_id;
            cout<<"Enter the section name: ";
            cin>>s.sec_name;
            cout<<"Enter the section marks: ";
            cin>>s.sec_mark;
            cout<<"Section details added Successfully!"<<endl;
            return s;
        }
        //------------------display blueprint-----------------
        void displayBlueprint(){
            cout<<string(20,'-')<<endl;
            cout<<string(18,' ')<<"Total Marks: "<<b.tot_mark<<endl;
            cout<<string(18,' ')<<"Total Duration: "<<b.dur<<endl;
            cout<<string(10,' ')<<"Unit Coverage: "<<b.u_cov<<endl;
            cout<<string(2,'\n');
        }    
            
};




//-------------------------------Subject Class------------------------------------------------
class Subject{
    vector<subject_structure> sub;
    public:
        void addSubject(){
            subject_structure s;
            cout<<"Enter the Subject Code: ";
            cin>>s.sub_code;
            cout<<"Enter the Subject Title: ";
            cin>>s.sub_title;
            cout<<"Enter the Semester: ";
            cin>>s.sem;
            cout<<"Enter the number of Units: ";
            cin>>s.s_unit;
            cout<<"Enter the Course Outcomes: ";
            cin>>s.s_co;
            sub.push_back(s);
        }

};












//---------------Master Question bank class------------------------------------------------------------------
class Question_bank{
    protected:
    vector<string> Id;
};


//-----------------Question editing class--------------------------------------------------------------------

class qEdit : public Question_bank{
    Question a;
    vector<Question> Qrec;
    public:
    
    void Add(){
        while(true){
        cout<<"Enter question id: ";
        cin>>a.qid;
        if((find(Id.begin(),Id.end(),a.qid))!=Id.end()){
            cout<<"\nDuplicate Question ID!";
        }else{
            Id.push_back(a.qid);
            cout<<"Enter Question Text: ";
            getline(cin,a.qtext);
            cout<<"Enter Question Type: ";
            getline(cin,a.qtype);
            cout<<"Enter Mark: ";
            cin>>a.qmark;
            cout<<"Enter Question Difficulty level: ";
            cin>>a.qDiff;
            cout<<"Enter Question Unit: ";
            cin>>a.qunit;
            cout<<"Enter outcome: ";
            cin>>a.qOut;
            cout<<"Enter Reference answer: ";
            cin>>a.qRef;
            
            cout<<"\nQuestion Added Successfully!";
            Qrec.push_back(a);
            break;
        }
        }
    }
    void Edit(){
        cout<<"Enter question id to edit: ";
        string id;
        cin>>id;
        for(auto &q : Qrec){
            if(q.qid == id){
                cout<<"Enter new question text: ";
                getline(cin,q.qtext);
                cout<<"Enter new question type: ";
                getline(cin,q.qtype);
                cout<<"Enter new mark: ";
                cin>>q.qmark;
                cout<<"Enter new question difficulty level: ";
                cin>>q.qDiff;
                cout<<"Enter new question unit: ";
                cin>>q.qunit;
                cout<<"Enter new outcome: ";
                cin>>q.qOut;
                cout<<"Enter new reference answer: ";
                cin>>q.qRef;
                cout<<"\nQuestion edited successfully!";
                return;
            }
        }
        cout<<"\nQuestion not found!";
    }

    //----------------Search question by Id---------------
    void Search(){
        string id ;
        cout<<"Enter question id to search: ";
        cin>>id;
        for(const auto &q : Qrec){
            if(q.qid == id){
                cout<<"\nQuestion found!";
                cout<<"Question ID: "<<q.qid<<endl;
                cout<<"Question Text: "<<q.qtext<<endl;
                cout<<"Question Type: "<<q.qtype<<endl;
                cout<<"Mark: "<<q.qmark<<endl;
                cout<<"Question Difficulty: "<<q.qDiff<<endl;
                cout<<"Question Unit: "<<q.qunit<<endl;
                cout<<"Outcome: "<<q.qOut<<endl;
                cout<<"Reference Answer: "<<q.qRef<<endl;
                return;
            }
        }
        cout<<"\nQuestion not found!";
    }

    //-----------------deactivate question-----------------
    void Deactivate(){
        string id;
        cout<<"Enter question id to deactivate: ";
        cin>>id;
        for(auto &q : Qrec){
            if(q.qid == id){
                if(!q.active){
                    cout<<"\nQuestion is already deactivated!";
                    return;
                }
                q.active = false;
                cout<<"\nQuestion deactivated successfully!";
                return;
            }
        }
        cout<<"\nQuestion not found!";
    }

    //-----------------filter questions by difficulty-----------------
    void Filter(){
        string diff;
        cout<<"Enter difficulty level to filter: ";
        cin>>diff;
        cout<<"\nQuestions with difficulty level "<<diff<<":\n";
        for(const auto &q : Qrec){
            if(q.qDiff == diff){
                cout<<"Question ID: "<<q.qid<<endl;
                cout<<"Question Text: "<<q.qtext<<endl;
                cout<<"Question Type: "<<q.qtype<<endl;
                cout<<"Mark: "<<q.qmark<<endl;
                cout<<"Question Difficulty: "<<q.qDiff<<endl;
                cout<<"Question Unit: "<<q.qunit<<endl;
                cout<<"Outcome: "<<q.qOut<<endl;
                cout<<"Reference Answer: "<<q.qRef<<endl;
                cout<<"Active Status: "<<(q.active ? "Active" : "Inactive")<<endl;
                cout<<"\n";
            }
        }
    }
};











