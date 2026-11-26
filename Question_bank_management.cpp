//----------Question bank management system-----------------
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
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


//--------------------Structure for Section--------------------------------------
struct section_structure{
    int sec_id, sec_mark;
    string sec_name;
};



//---------------------Blueprint Structure---------------------------------------
struct qblueprint{
    int tot_mark,dur;
    string u_cov;
    string diff;
    vector<section_structure> sec;
};



//-------------------Structure of Subject---------------------------------------
struct subject_structure{
    int sub_code, sem;
    string sub_title, s_co, s_unit;
};



//-------------------Structure of Exam Schedule---------------------------------
struct exam_schedule{
    string exam_id;
    int sub_code;
    string paper_ref;
    string exam_date;
    string exam_time;
    string venue;
};



class Blueprint{
    vector<qblueprint> bluep; //-----blueprint as a rec
    vector<section_structure> sec_struct; // -----section structure as a rec => to be stored in blueprint
    qblueprint b;

    public:
    //-----------------create blueprint-----------------
        void createBlueprint(){
            ofstream bluepfile("Blueprint.txt", ios::app);
            b.sec.clear();
            cout<<"Enter the total marks: ";
            cin>>b.tot_mark;
            cout<<"Enter the total duration: ";
            cin>>b.dur;
            cout<<"Enter the unit coverage: ";
            cin.ignore(1000,'\n');
            getline(cin,b.u_cov);
            cout<<"Section Structure\n";
            cout<<"Enter the number of sections: ";
            int n;
            cin>>n;
            for(int i=0;i<n;i++){
                b.sec.push_back(createSection()); // =>dont forget to add clear 
            }
            cout<<"Enter the difficulty level: ";
            cin.ignore(1000,'\n');
            getline(cin,b.diff);
            cout<<"Blueprint details added Successfully!"<<endl;
            bluep.push_back(b);
            bluepfile<<b.tot_mark<<"|"<<b.dur<<"|"<<b.u_cov<<"|"<<b.diff<<endl;
            for(const auto &s : b.sec){
                bluepfile<<s.sec_id<<"|"<<s.sec_name<<"|"<<s.sec_mark<<endl;
            }
            bluepfile.close();
        }

        //------------------create section structure-----------------
        section_structure createSection(){
            section_structure s;
            cout<<"Enter the section ID: ";
            cin>>s.sec_id;
            cout<<"Enter the section name: ";
            cin.ignore(1000,'\n');
            getline(cin,s.sec_name);
            cout<<"Enter the section marks: ";
            cin>>s.sec_mark;
            cout<<"Section details added Successfully!"<<endl;
            return s;
        }
        //------------------display blueprint-----------------
        void displayBlueprint(){
            if(bluep.empty()){
                cout<<"\nNo blueprints found!\n";
                return;
            }
            for(size_t i=0;i<bluep.size();i++){
                const auto &bp = bluep[i];
                cout<<string(20,'-')<<endl;
                cout<<string(18,' ')<<"Total Marks: "<<bp.tot_mark<<endl;
                cout<<string(18,' ')<<"Total Duration: "<<bp.dur<<endl;
                cout<<string(10,' ')<<"Unit Coverage: "<<bp.u_cov<<endl;
                cout<<string(10,' ')<<"Difficulty Level: "<<bp.diff<<endl;
                for(const auto &s : bp.sec){
                    cout<<string(10,' ')<<"Section ["<<s.sec_id<<"] "<<s.sec_name<<" ("<<s.sec_mark<<" marks)\n";
                }
                cout<<string(2,'\n');
            }
        }    
            
};




//-------------------------------Subject Class------------------------------------------------
class Subject{
    vector<subject_structure> sub;
    public:
        void addSubject(){
            ofstream subfile("Subject.txt", ios::app);
            subject_structure s;
            cout<<"Enter the Subject Code: ";
            cin>>s.sub_code;
            cout<<"Enter the Subject Title: ";
            cin.ignore(1000,'\n');
            getline(cin,s.sub_title);
            cout<<"Enter the Semester: ";
            cin>>s.sem;
            cout<<"Enter the number of Units: ";
            cin.ignore(1000,'\n');
            getline(cin,s.s_unit);
            cout<<"Enter the Course Outcomes: ";
            getline(cin,s.s_co);
            subfile<<s.sub_code<<"|"<<s.sub_title<<"|"<<s.sem<<"|"<<s.s_unit<<"|"<<s.s_co<<endl;
            subfile.close();
            sub.push_back(s);
            cout<<"Subject added Successfully!\n";
        }

};












//-------------------------------Exam Schedule Class------------------------------------------
class ExamSchedule{
    vector<exam_schedule> schedules;
    public:
        //-----------------add exam schedule-----------------
        void addSchedule(){
            ofstream examsche("ExamSchedule.txt",ios::app);
            exam_schedule es;
            cout<<"Enter Exam ID: ";
            cin>>es.exam_id;
            cout<<"Enter Subject Code: ";
            cin>>es.sub_code;
            cout<<"Enter Assigned Paper Reference: ";
            cin.ignore(1000,'\n');
            getline(cin,es.paper_ref);
            cout<<"Enter Exam Date: ";
            getline(cin,es.exam_date);
            cout<<"Enter Exam Time: ";
            getline(cin,es.exam_time);
            cout<<"Enter Venue: ";
            getline(cin,es.venue);
            examsche<<es.exam_id<<" | "<<es.sub_code<<" | "<<es.paper_ref<<" | "<<es.exam_date<<" | "<<es.exam_time<<" | "<<es.venue<<endl;
            examsche.close();
            schedules.push_back(es);
            cout<<"\nExam schedule added Successfully!\n";
        }

        //-----------------display exam schedules-----------------
        void displaySchedules(){
            if(schedules.empty()){
                cout<<"\nNo exam schedules found!\n";
                return;
            }
            for(size_t i=0;i<schedules.size();i++){
                const auto &es = schedules[i];
                cout<<string(25,'-')<<endl;
                cout<<"Schedule #"<<(i+1)<<endl;
                cout<<"Exam ID: "<<es.exam_id<<endl;
                cout<<"Subject Code: "<<es.sub_code<<endl;
                cout<<"Paper Reference: "<<es.paper_ref<<endl;
                cout<<"Exam Date: "<<es.exam_date<<endl;
                cout<<"Exam Time: "<<es.exam_time<<endl;
                cout<<"Venue: "<<es.venue<<endl;
                cout<<string(25,'-')<<endl;
            }
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
            ofstream Qp("Question_bank.txt", ios::app);
            Id.push_back(a.qid);
            cout<<"Enter Question Text: ";
            cin.ignore(1000,'\n');
            getline(cin,a.qtext);
            cout<<"Enter Question Type: ";
            getline(cin,a.qtype);
            cout<<"Enter Mark: ";
            cin>>a.qmark;
            cout<<"Enter Question Difficulty level: ";
            cin.ignore(1000,'\n');
            getline(cin,a.qDiff);
            cout<<"Enter Question Unit: ";
            cin>>a.qunit;
            cout<<"Enter outcome: ";
            cin.ignore(1000,'\n');
            getline(cin,a.qOut);
            cout<<"Enter Reference answer: ";
            getline(cin,a.qRef);
            a.active = true;
            Qp<<a.qid<<"|"<<a.qtext<<"|"<<a.qtype<<"|"<<a.qmark<<"|"<<a.qDiff<<"|"<<a.qunit<<"|"<<a.qOut<<"|"<<a.qRef<<"|"<<a.active<<endl;
            cout<<"\nQuestion Added Successfully!";
            Qrec.push_back(a);
            Qp.close();
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
                cin.ignore(1000,'\n');
                getline(cin,q.qtext);
                cout<<"Enter new question type: ";
                getline(cin,q.qtype);
                cout<<"Enter new mark: ";
                cin>>q.qmark;
                cout<<"Enter new question difficulty level: ";
                cin.ignore(1000,'\n');
                getline(cin,q.qDiff);
                cout<<"Enter new question unit: ";
                cin>>q.qunit;
                cout<<"Enter new outcome: ";
                cin.ignore(1000,'\n');
                getline(cin,q.qOut);
                cout<<"Enter new reference answer: ";
                getline(cin,q.qRef);
                ofstream Qp("Question_bank.txt");
                for(const auto &ques : Qrec){ //------------------------------For adding all other records into the file(opened in write mode)-----------------------------
                    Qp<<ques.qid<<"|"<<ques.qtext<<"|"<<ques.qtype<<"|"<<ques.qmark<<"|"<<ques.qDiff<<"|"<<ques.qunit<<"|"<<ques.qOut<<"|"<<ques.qRef<<"|"<<ques.active<<endl;
                }
                Qp.close();
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
                ofstream Qp("Question_bank.txt");
                for(const auto &ques : Qrec){ //------------------------------For adding all other records into the file(opened in write mode)-----------------------------
                    Qp<<ques.qid<<"|"<<ques.qtext<<"|"<<ques.qtype<<"|"<<ques.qmark<<"|"<<ques.qDiff<<"|"<<ques.qunit<<"|"<<ques.qOut<<"|"<<ques.qRef<<"|"<<ques.active<<endl;
                }
                cout<<"\nQuestion deactivated successfully!";
                Qp.close();
                return;
            }
        }
        cout<<"\nQuestion not found!";
    }

    //-----------------filter questions by difficulty-----------------
    void Filter(){
        string diff;
        cout<<"Enter difficulty level to filter: ";
        cin.ignore(1000,'\n');
        getline(cin,diff);
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

//-------------------------------Main Function------------------------------------------------
int main(){
    Subject subj;
    Blueprint bp;
    qEdit qbank;
    ExamSchedule sched;
    int choice;

    do{
        cout<<"\n--- Examination & Question Bank Management System ---\n";
        cout<<"1. Add Subject\n";
        cout<<"2. Create Blueprint\n";
        cout<<"3. Display Blueprints\n";
        cout<<"4. Add Question\n";
        cout<<"5. Edit Question\n";
        cout<<"6. Search Question\n";
        cout<<"7. Deactivate Question\n";
        cout<<"8. Filter Questions by Difficulty\n";
        cout<<"9. Add Exam Schedule\n";
        cout<<"10. Display Exam Schedules\n";
        cout<<"0. Exit\n";
        cout<<"Enter your choice: ";
        cin>>choice;

        switch(choice){
            case 1: subj.addSubject(); break;
            case 2: bp.createBlueprint(); break;
            case 3: bp.displayBlueprint(); break;
            case 4: qbank.Add(); break;
            case 5: qbank.Edit(); break;
            case 6: qbank.Search(); break;
            case 7: qbank.Deactivate(); break;
            case 8: qbank.Filter(); break;
            case 9: sched.addSchedule(); break;
            case 10: sched.displaySchedules(); break;
            case 0: cout<<"Exiting...\n"; break;
            default: cout<<"Invalid choice! Please try again.\n"; break;
        }
    }while(choice != 0);

    return 0;
}